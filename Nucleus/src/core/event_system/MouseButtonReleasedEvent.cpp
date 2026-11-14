//
// Created by ridham on 2026/01/03.
//

#include "MouseButtonReleasedEvent.h"

namespace nucleus {
    MouseButtonReleasedEvent::MouseButtonReleasedEvent(MouseButton Button, f64 MouseX, f64 MouseY)
    : m_Button(Button), m_MouseX(MouseX), m_MouseY(MouseY) {}

    EventType MouseButtonReleasedEvent::GetEventType() const
    {
        return EventType::MouseButtonReleased;
    }

    const char* MouseButtonReleasedEvent::GetName() const
    {
        return "MouseButtonReleasedEvent";
    }

    u32 MouseButtonReleasedEvent::GetCategoryFlags() const
    {
        return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton;
    }

    f64 MouseButtonReleasedEvent::GetMouseX() const
    {
        return m_MouseX;
    }

    f64 MouseButtonReleasedEvent::GetMouseY() const
    {
        return m_MouseY;
    }

    MouseButton MouseButtonReleasedEvent::GetMouseButton() const
    {
        return m_Button;
    }
}