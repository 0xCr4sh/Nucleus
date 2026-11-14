//
// Created by ridham on 2026/01/02.
//

#include "WindowResizeEvent.h"


namespace nucleus {

    WindowResizeEvent::WindowResizeEvent(u32 width, u32 height)
        : m_Width(width), m_Height(height) {}

    EventType WindowResizeEvent::GetEventType() const
    {
        return EventType::WindowResize;
    }

    const char* WindowResizeEvent::GetName() const
    {
        return "WindowResizeEvent";
    }


    u32 WindowResizeEvent::GetCategoryFlags() const
    {
        return EventCategoryApplication;
    }

    u32 WindowResizeEvent::GetHeight() const
    {
        return m_Height;
    }

    u32 WindowResizeEvent::GetWidth() const
    {
        return m_Width;
    }
}