//
// Created by ridham on 2026/01/02.
//

#include "KeyRepeatedEvent.h"

nucleus::KeyRepeatedEvent::KeyRepeatedEvent(KeyCode key)
    : m_KeyCode(key) {}

nucleus::EventType nucleus::KeyRepeatedEvent::GetEventType() const
{
    return EventType::KeyRepeated;
}

const char* nucleus::KeyRepeatedEvent::GetName() const
{
    return "KeyRepeatedEvent";
}

uint32_t nucleus::KeyRepeatedEvent::GetCategoryFlags() const
{
    return EventCategoryInput | EventCategoryKeyboard;
}

nucleus::KeyCode nucleus::KeyRepeatedEvent::GetKeyCode() const
{
    return m_KeyCode;
}