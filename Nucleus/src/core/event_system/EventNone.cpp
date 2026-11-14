/**
* @file eventbus.cpp
 * @brief Implementation of the EventNone event.
 *
 * @author Ridham
 * @date 2026-11-12
 */

#include "EventNone.h"

namespace nucleus {
    EventType EventNone::GetEventType() const {
        return EventType::None;
    }

    const char* EventNone::GetName() const
    {
        return "EventNone";
    }

    u32 EventNone::GetCategoryFlags() const
    {
        return EventCategoryNone;
    }
}