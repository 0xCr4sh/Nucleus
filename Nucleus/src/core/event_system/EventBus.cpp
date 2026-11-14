/**
* @file eventbus.cpp
 * @brief Implementation of the EventBus dispatching and subscription management.
 *
 * @details
 * Implements the non-template functionality of the EventBus, including
 * subscriber removal, deferred operation processing, and publish-depth
 * management.
 *
 * ## PublishGuard
 * Implements the RAII mechanism used to track active Publish() operations.
 * The publishing depth is incremented when a publishing operation begins
 * and decremented when it completes.
 *
 * When the outermost publishing operation finishes, pending subscription
 * requests and unsubscription requests are processed.
 *
 * ## Subscription management
 * Provides the implementation for removing subscribers from their
 * corresponding event-type lists.
 *
 * Unsubscription requests made during event dispatch are queued and
 * processed after the outermost publishing operation completes.
 *
 * ## Deferred operations
 * Pending subscription requests are executed individually. A failure
 * during one deferred subscription is caught and logged so that remaining
 * requests can still be processed.
 *
 * Pending removals are processed after pending subscriptions, ensuring
 * that a subscriber registered and subsequently scheduled for removal
 * during the same publishing chain does not remain registered.
 *
 * @note This implementation assumes single-threaded access to EventBus.
 *
 * @author Ridham
 * @date 2026-11-12
 */

#include <nucleus/core/event_system/eventbus.h>
#include <core/logging/LogInternal.h>

nucleus::EventBus::PublishGuard::PublishGuard(EventBus& bus)
    : m_Bus(bus) {

    ++m_Bus.m_PublishDepth;
}

nucleus::EventBus::PublishGuard::~PublishGuard() noexcept {
    --m_Bus.m_PublishDepth;

    if (m_Bus.m_PublishDepth == 0) {
        m_Bus.ProcessPendingSubscriptionRequests();
        m_Bus.ProcessPendingRemovals();
    }

}


void nucleus::EventBus::Unsubscribe(std::type_index type, u64 id) {
    if (!m_Subscribers.contains(type)) {
        return;
    }

    if (m_PublishDepth > 0) {
        m_PendingRemovals.push_back({.type = type, .id = id});
        return;
    }

    m_Subscribers[type].get()->RemoveSubscriber(id);
}

void nucleus::EventBus::RemoveSubscriberFromList(std::type_index type, u64 id) {
    auto it = m_Subscribers.find(type);

    if (it == m_Subscribers.end())
        return;

    it->second->RemoveSubscriber(id);
}

void nucleus::EventBus::ProcessPendingRemovals() {
    if (m_PendingRemovals.empty())
        return;

    for (const auto& [type, id] : m_PendingRemovals) {
        RemoveSubscriberFromList(type, id);
    }

    m_PendingRemovals.clear();
}

void nucleus::EventBus::ProcessPendingSubscriptionRequests() {
    for (auto& pendingRequest : m_PendingSubscriptionRequests) {
        try {
            pendingRequest.Action();
        }
        catch (const std::bad_alloc& e) {
            NUC_CORE_CRITICAL("Failed to process a deferred subscription. std::bad_alloc exception: ", e.what());
        }
        catch (...) {
            NUC_CORE_CRITICAL("Failed to process a deferred subscription.");
        }
    }

    m_PendingSubscriptionRequests.clear();
}