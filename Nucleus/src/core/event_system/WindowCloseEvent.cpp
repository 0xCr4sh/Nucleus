//
// Created by ridham on 2026/01/02.
//

#include "WindowCloseEvent.h"

namespace nucleus {
    EventType WindowCloseEvent::GetEventType() const
    {
        return EventType::WindowClose;
    }

    const char* WindowCloseEvent::GetName() const
    {
        return "WindowCloseEvent";
    }

    u32 WindowCloseEvent::GetCategoryFlags() const
    {
        return EventCategoryApplication;
    }
}