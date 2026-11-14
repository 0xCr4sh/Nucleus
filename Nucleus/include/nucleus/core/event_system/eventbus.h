/**

* @file eventbus.h
* @brief Priority-based event dispatching system for the Nucleus Engine.
*
* This file provides the EventBus implementation used for communication
* between engine subsystems, game systems, and user code.
*
* The EventBus supports:
* * Type-safe event subscriptions
* * Priority-ordered event dispatch
* * Global event listeners
* * Safe nested event publishing
* * Deferred subscription and unsubscription during dispatch
*
* Subscribers are grouped by event type and invoked in descending priority
* order. Modifications to subscriber lists that occur during event dispatch
* are automatically deferred until the outermost publish operation completes,
* preventing iterator invalidation and ensuring deterministic behavior.
*
* Typical usage:
* @code
* EventBus bus;
*
* bus.Subscribe<KeyPressedEvent>(
* ```
  [](KeyPressedEvent& event)
  ```
* ```
  {
  ```
* ```
      // Handle event
  ```
* ```
  },
  ```
* ```
  EventPriority::Gameplay
  ```
* );
*
* KeyPressedEvent event;
* bus.Publish(event);
* @endcode
*
* @author ridham
* @date 2026-11-12
*/


#ifndef NUCLEUS_EVENTBUS_H
#define NUCLEUS_EVENTBUS_H

#include "event.h"
#include <nucleus/types/numericalAliases.h>
#include <nucleus/export.h>

#include <vector>
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <type_traits>
#include <concepts>
#include <utility>

namespace nucleus
{
    /**
     * @brief Dispatch priority categories.
     *
     * Higher numeric values execute before lower values.
     *
     * Example:
     * UI (255) -> Gameplay (96) -> World (64) -> Engine (32) -> System (0)
     */
    enum class NUCLEUS_API EventPriority : u8
    {
        // Lowest level — raw OS / platform stuff
        System      = 0,    // OS signals, window close, focus, resize
        Platform    = 16,   // GLFW / SDL / native platform events

        // Core engine systems
        Engine      = 32,   // Renderer, Audio, Resource manager
        Input       = 48,   // Keyboard, Mouse, Controller (processed)

        // Game-related layers
        World       = 64,   // Physics, ECS, collisions, scene graph
        Gameplay    = 96,   // Player, enemies, game logic

        // Presentation / overlay layers
        UI          = 255   // Menus, HUD, ImGui, overlays (always first)
    };

    using AllEvents = IEvent; // Event is the base class from which all events inherit


    /**
     * @brief Priority-based event dispatching system.
     *
     * The EventBus enables communication between engine systems, gameplay code,
     * and user-defined components through a type-safe publish/subscribe model.
     *
     * Subscribers are invoked in descending priority order. Modifications to
     * subscriber lists during event dispatch are deferred until all nested
     * publish operations have completed, ensuring safe iteration and
     * deterministic behavior.
     *
     * Features:
     * - Type-safe event subscriptions
     * - Priority-based dispatch ordering
     * - Global event listeners
     * - Deferred subscribe/unsubscribe operations
     * - Nested event publishing support
     */
    class NUCLEUS_API EventBus
    {
    public:
        EventBus() = default;
        ~EventBus() = default;




        /**
         * @brief Registers a callback for a specific event type.
         *
         * The callback will be invoked whenever an event of EventType is published.
         * If a publish operation is currently active, the subscription request is
         * deferred until dispatch completes.
         *
         * @tparam EventType Event type to subscribe to.
         * @param callback Function invoked when the event is dispatched.
         * @param priorityLevel Numeric priority level. Higher values execute first.
         *
         * @return Unique subscription identifier used for unsubscription.
         */
        template <typename EventType>
        requires std::derived_from<EventType, IEvent>
        u64 Subscribe(std::function<void(EventType&)> callback, u8 priorityLevel)
        {
            if (!callback)
                return 0;

            const u64 id = ++m_NextSubscriberID;

            Subscriber<EventType> newSubscriber(id, priorityLevel, std::move(callback));

            std::type_index type = typeid(EventType);

            if (!m_Subscribers.contains(type)) {
                m_Subscribers[type] = std::make_unique<SubscriberList<Subscriber<EventType>>>();
            }

            if (m_PublishDepth > 0) {
                m_PendingSubscriptionRequests.push_back({
                    [this, type, subscriber = std::move(newSubscriber)]() mutable{
                        static_cast<SubscriberList<Subscriber<EventType>>*>(
                            m_Subscribers[type].get()
                        )->PushSubscriber(std::move(subscriber));
                    }
                });
            }
            else {
                static_cast<SubscriberList<Subscriber<EventType>>*>(m_Subscribers[type].get())->PushSubscriber(std::move(newSubscriber));
            }

            return id;
        }

        /**
         * @brief Registers a callback using a predefined event priority.
         *
         * Convenience overload that accepts an EventPriority value instead of a raw
         * numeric priority.
         *
         * @tparam EventType Event type to subscribe to.
         * @param callback Function invoked when the event is dispatched.
         * @param priorityLevel Predefined event priority category.
         *
         * @return Unique subscription identifier used for unsubscription.
         */
        template <typename EventType>
        requires std::derived_from<EventType, IEvent>
        u64 Subscribe(std::function<void(EventType&)> callback, EventPriority priorityLevel) {
            return Subscribe<EventType>(
                std::move(callback),
                        static_cast<u8>(priorityLevel)
                    );
        }

        /**
         * @brief Removes a previously registered subscriber.
         *
         * If event dispatch is currently active, the removal request is deferred
         * until all nested publish operations have completed.
         *
         * @tparam EventType Event type associated with the subscription.
         * @param id Subscription identifier returned by Subscribe().
         */
        template <typename EventType>
        requires std::derived_from<EventType, IEvent>
        void Unsubscribe(const u64 id) {
            Unsubscribe(typeid(EventType), id);
        }


        /**
         * @brief Removes a previously registered subscriber.
         *
         * If event dispatch is currently active, the removal request is deferred
         * until all nested publish operations have completed.
         *
         * @param type std::type_index associated with the subscription. (you can just pass typeid(EventType))
         * @param id Subscription identifier returned by Subscribe().
         */
        void Unsubscribe(std::type_index type, u64 id);

        /**
         * @brief Dispatches an event to all matching subscribers.
         *
         * Type-specific subscribers are invoked first in descending priority order.
         * Global event subscribers are then notified unless the event type is the
         * global event type itself.
         *
         * Event propagation stops immediately when event.handled becomes true.
         *
         * @tparam EventType Concrete event type being dispatched.
         * @param event Event instance to publish.
         */
        template <typename EventType>
        requires std::derived_from<EventType, IEvent>
        void Publish(EventType& event) {
            PublishGuard guard(*this);

            for (auto& typeSpecificSubscribers = GetSubscribers<EventType>(); const auto& subscriber : typeSpecificSubscribers)
            {
                if (event.handled) break;
                subscriber.Callback(event);
            }

            if constexpr (!std::is_same_v<EventType, AllEvents>) {
                for (const auto& globalSubscribers = GetSubscribers<AllEvents>(); const auto& subscriber : globalSubscribers) {
                    if (event.handled) break;
                    subscriber.Callback(event);
                }
            }

        }


    private:
        struct PendingRemoval
        {
            std::type_index type;
            u64 id;
        };

        struct PendingSubscriptionRequest
        {
            std::function<void()> Action;
        };

        u32 m_PublishDepth = 0;
        std::vector<PendingRemoval> m_PendingRemovals;
        std::vector<PendingSubscriptionRequest> m_PendingSubscriptionRequests;

        class PublishGuard
        {
        public:
            explicit PublishGuard(EventBus& bus);

            ~PublishGuard() noexcept;

        private:
            EventBus& m_Bus;
        };

        /**
         * @brief Stores callback and metadata for a single event subscriber.
         *
         * Each subscriber contains a unique identifier, dispatch priority,
         * and callback function associated with a specific event type.
         *
         * @tparam EventType Event type handled by the subscriber.
         */
        template <typename EventType>
        requires std::derived_from<EventType, IEvent>
        class Subscriber final
        {
        public:
            ~Subscriber() = default;
            Subscriber(const u64 id, const u8 priorityLevel, std::function<void(EventType&)> callback)
                : PriorityLevel(priorityLevel), ID(id), Callback(std::move(callback)) {}

            u8 PriorityLevel;
            u64 ID;
            std::function<void(EventType&)> Callback;
        };






        /**
         * @brief Type-erased interface for subscriber containers.
         *
         * Allows subscriber lists for different event types to be stored in a
         * single heterogeneous collection.
         */
        class ISubscriberList
        {
        public:
            virtual ~ISubscriberList() = default;
            virtual void RemoveSubscriber(u64 id) = 0;
        };






        /**
         * @brief Stores subscribers for a specific event type.
         *
         * Subscribers are maintained in descending priority order to ensure
         * deterministic event dispatch behavior.
         *
         * @tparam SubscriberType Subscriber implementation type.
         */
        template <typename SubscriberType>
        class SubscriberList final : public ISubscriberList
        {
        public:
            ~SubscriberList() override = default;
            SubscriberList() = default;

            void PushSubscriber(SubscriberType subscriber) // Passing by value so it works for both rvalue and lvalues
            {
                if (m_Subscribers.empty()) {
                    m_Subscribers.push_back(std::move(subscriber));
                    return;
                }

                size_t left = 0;
                size_t right = m_Subscribers.size();

                while (left < right) {
                    size_t middle = left + (right - left) / 2;

                    if (m_Subscribers[middle].PriorityLevel >= subscriber.PriorityLevel)
                        left = middle + 1;
                    else
                        right = middle;
                }

                m_Subscribers.insert(m_Subscribers.begin() + left, std::move(subscriber));
            }

            void RemoveSubscriber(u64 id) override
            {
                for (size_t i = 0; i < m_Subscribers.size(); i++)
                {
                    if (auto& subscriber = m_Subscribers[i]; subscriber.ID == id)
                    {
                        m_Subscribers.erase(m_Subscribers.begin() + i);
                        return;
                    }
                }
            }

            std::vector<SubscriberType>& getSubscriberArray()
            {
                return m_Subscribers;
            }

        private:
            std::vector<SubscriberType> m_Subscribers;

        };


        template<typename EventType>
        requires std::derived_from<EventType, IEvent>
        std::vector<Subscriber<EventType>>& GetSubscribers() {
            const std::type_index type = typeid(EventType);

            if (!m_Subscribers.contains(type))
            {
                m_Subscribers[type] = std::make_unique< SubscriberList<Subscriber<EventType>>>();
            }

            auto* list = static_cast<SubscriberList<Subscriber<EventType>>*>(m_Subscribers[type].get());

            return list->getSubscriberArray();
        }

        void RemoveSubscriberFromList(std::type_index type, u64 id);

        void ProcessPendingRemovals();

        void ProcessPendingSubscriptionRequests();


        std::unordered_map< std::type_index, std::unique_ptr<ISubscriberList> > m_Subscribers;
        u64 m_NextSubscriberID = 0;


        friend PublishGuard;
    };
}

#endif // NUCLEUS_EVENTBUS_H