//
// Created by ridham on 2026/01/03.
//

#include "MouseScrolledEvent.h"


namespace nucleus {
    MouseScrolledEvent::MouseScrolledEvent(f64 MouseX, f64 MouseY, f64 OffsetX, f64 OffsetY)
        : m_MouseX(MouseX), m_MouseY(MouseY), m_OffsetX(OffsetX), m_OffsetY(OffsetY) {}
    EventType MouseScrolledEvent::GetEventType() const
    {
        return EventType::MouseScrolled;
    }

    const char* MouseScrolledEvent::GetName() const
    {
        return "MouseScrolledEvent";
    }

    u32 MouseScrolledEvent::GetCategoryFlags() const
    {
        return EventCategoryInput | EventCategoryMouse;
    }

    f64 MouseScrolledEvent::GetMouseX() const
    {
        return m_MouseX;
    }

    f64 MouseScrolledEvent::GetMouseY() const
    {
        return m_MouseY;
    }

    f64 MouseScrolledEvent::GetScrollOffsetX() const
    {
        return m_OffsetX;
    }

    f64 MouseScrolledEvent::GetScrollOffsetY() const
    {
        return m_OffsetY;
    }

    bool MouseScrolledEvent::IsScrollUp() const
    {
        return m_OffsetY > 0.0;
    }

    bool MouseScrolledEvent::IsScrollDown() const
    {
        return m_OffsetY < 0.0;
    }
}