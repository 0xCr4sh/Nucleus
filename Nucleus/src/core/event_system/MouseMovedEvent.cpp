//
// Created by ridham on 2026/01/03.
//

#include "MouseMovedEvent.h"

namespace nucleus {
    MouseMovedEvent::MouseMovedEvent(f64 mouseX, f64 mouseY, f64 dx, f64 dy)
    : m_MouseX(mouseX), m_MouseY(mouseY), m_dx(dx), m_dy(dy) {}

    EventType MouseMovedEvent::GetEventType() const
    {
        return EventType::MouseMoved;
    }

    const char* MouseMovedEvent::GetName() const
    {
        return "MouseMovedEvent";
    }

    u32 MouseMovedEvent::GetCategoryFlags() const
    {
        return EventCategoryInput | EventCategoryMouse;
    }

    f64 MouseMovedEvent::getMouseX() const
    {
        return m_MouseX;
    }

    f64 MouseMovedEvent::getMouseY() const
    {
        return m_MouseY;
    }

    f64 MouseMovedEvent::getMouseDX() const
    {
        return m_dx;
    }

    f64 MouseMovedEvent::getMouseDY() const
    {
        return m_dy;
    }
}
