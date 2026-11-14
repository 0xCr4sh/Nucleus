//
// Created by ridham on 2026/01/02.
//

#include "KeyReleasedEvent.h"

nucleus::KeyReleasedEvent::KeyReleasedEvent(KeyCode key)
    : m_KeyCode(key) {}

nucleus::EventType nucleus::KeyReleasedEvent::GetEventType() const
{
    return EventType::KeyReleased;
}

const char* nucleus::KeyReleasedEvent::GetName() const
{
    return "KeyReleasedEvent";
}

uint32_t nucleus::KeyReleasedEvent::GetCategoryFlags() const
{
    return EventCategoryInput | EventCategoryKeyboard;
}

nucleus::KeyCode nucleus::KeyReleasedEvent::GetKeyCode() const
{
    return m_KeyCode;
}