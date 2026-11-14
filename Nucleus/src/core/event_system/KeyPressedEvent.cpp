//
// Created by ridham on 2026/01/01.
//

#include "KeyPressedEvent.h"

nucleus::KeyPressedEvent::KeyPressedEvent(KeyCode key)
    : m_KeyCode(key) {}

nucleus::EventType nucleus::KeyPressedEvent::GetEventType() const
{
    return EventType::KeyPressed;
}

const char* nucleus::KeyPressedEvent::GetName() const
{
    return "KeyPressedEvent";
}

nucleus::u32 nucleus::KeyPressedEvent::GetCategoryFlags() const
{
    return EventCategoryInput | EventCategoryKeyboard;
}

nucleus::KeyCode nucleus::KeyPressedEvent::GetKeyCode() const
{
    return m_KeyCode;
}