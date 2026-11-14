
/**
 * @file event.h
 * @brief Base event interface and event classification definitions.
 *
 * @details
 * Defines the fundamental event types, event categories, and abstract
 * Event class used by the Nucleus event system.
 *
 * All events dispatched through the EventBus must derive from Event.
 * Derived event classes provide their own type identification, name,
 * and category information.
 *
 * @author Ridham
 * @date 2026-11-12
 *
 * @bug No known bugs.
 *
 * @copyright (c) 2026 Ridham
 */

#ifndef NUCLEUS_EVENT_H
#define NUCLEUS_EVENT_H

#include <nucleus/types/numericalAliases.h>
#include <nucleus/export.h>

namespace nucleus {

    /**
     * @brief Identifies the concrete type of an event.
     *
     * @details
     * Used to distinguish between different event types at runtime.
     * Each event type should have a unique enumerator.
     *
     * The None value represents the absence of a specific event type.
     */
    enum class NUCLEUS_API EventType : u32
    {
        None = 0,

        WindowClose,
        WindowResize,

        KeyPressed,
        KeyReleased,
        KeyRepeated,

        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    /**
     * @brief Defines event categories using bit flags.
     *
     * @details
     * Events can belong to multiple categories simultaneously.
     * Categories are represented as individual bits, allowing them
     * to be combined using bitwise OR operations.
     *
     * This allows events to be classified independently of their
     * concrete EventType.
     */
    enum EventCategory : u32
    {
        EventCategoryNone        = 0,
        EventCategoryApplication = 1 << 0,
        EventCategoryInput       = 1 << 1,
        EventCategoryKeyboard    = 1 << 2,
        EventCategoryMouse       = 1 << 3,
        EventCategoryMouseButton = 1 << 4
    };

    /**
     * @brief Abstract base class for all Nucleus events.
     *
     * @details
     * Provides a common interface for event identification,
     * categorization, and propagation control.
     *
     * Concrete event classes must implement the virtual identification
     * and categorization functions.
     *
     * The handled flag indicates whether an event has been consumed.
     * Event dispatchers can use this flag to stop further propagation
     * once an event has been handled.
     *
     * Events are non-owning with respect to the objects that receive
     * them. Their lifetime must remain valid throughout dispatch.
     */
    class NUCLEUS_API IEvent
    {
    public:

        /**
         * @brief Virtual destructor.
         *
         * Ensures proper destruction of derived event objects through
         * a base Event pointer.
         */
        virtual ~IEvent() = default;

        /**
         * @brief Indicates whether this event has been handled.
         *
         * @details
         * Event listeners can set this to true to indicate that they
         * have consumed the event.
         *
         * Dispatchers may stop propagating the event when this flag
         * becomes true.
         */
        bool handled = false;

        /**
         * @brief Retrieves the concrete event type.
         *
         * @return EventType Identifying the event.
         */
        [[nodiscard]] virtual EventType GetEventType() const = 0;

        /**
         * @brief Retrieves the event's human-readable name.
         *
         * @return Null-terminated event name.
         */
        [[nodiscard]] virtual const char* GetName() const = 0;

        /**
         * @brief Retrieves the categories this event belongs to.
         *
         * @return Combined EventCategory bit flags.
         */
        [[nodiscard]] virtual u32 GetCategoryFlags() const = 0;

        /**
         * @brief Checks whether the event belongs to a category.
         *
         * @param category Category flag to check.
         * @return True if the event belongs to the specified category.
         *
         * @note Multiple categories can be checked by combining
         *       their flags using bitwise OR.
         */
        [[nodiscard]] bool IsInCategory(const EventCategory category) const
        {
            return GetCategoryFlags() & category;
        }

    };

}

#endif // NUCLEUS_EVENT_H
