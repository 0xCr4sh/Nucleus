//
// Created by ridham on 2026/01/03.
//

#include "MouseButtonPressedEvent.h"


namespace nucleus {
    MouseButtonPressedEvent::MouseButtonPressedEvent(MouseButton Button, f64 MouseX, f64 MouseY)
    : m_Button(Button), m_MouseX(MouseX), m_MouseY(MouseY) {}

    EventType MouseButtonPressedEvent::GetEventType() const
    {
        return EventType::MouseButtonPressed;
    }

    const char* MouseButtonPressedEvent::GetName() const
    {
        return "MouseButtonPressedEvent";
    }

    u32 MouseButtonPressedEvent::GetCategoryFlags() const
    {
        return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton;
    }

    f64 MouseButtonPressedEvent::GetMouseX() const
    {
        return m_MouseX;
    }

    f64 MouseButtonPressedEvent::GetMouseY() const
    {
        return m_MouseY;
    }

    MouseButton MouseButtonPressedEvent::GetMouseButton() const
    {
        return m_Button;
    }
}