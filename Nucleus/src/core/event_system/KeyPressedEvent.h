//
// Created by ridham on 2026/01/01.
//

#pragma once

#include <nucleus/core/event_system/event.h>
#include <nucleus/core/event_system/KeyCodes.h>

namespace nucleus
{

    class KeyPressedEvent final : public IEvent
    {
    public:
        explicit KeyPressedEvent(KeyCode key);

        [[nodiscard]] EventType GetEventType() const override;
        [[nodiscard]] const char* GetName() const override;
        [[nodiscard]] u32 GetCategoryFlags() const override;

        [[nodiscard]] KeyCode GetKeyCode() const;

    private:
        KeyCode m_KeyCode;
    };

}