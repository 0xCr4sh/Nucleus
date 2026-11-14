//
// Created by ridham on 2026/01/02.
//

#pragma once

#include <nucleus/core/event_system/event.h>
#include <nucleus/core/event_system/KeyCodes.h>

namespace nucleus
{

    class KeyReleasedEvent final : public IEvent
    {
    public:
        explicit KeyReleasedEvent(KeyCode key);

        [[nodiscard]] EventType GetEventType() const override;
        [[nodiscard]] const char* GetName() const override;
        [[nodiscard]] u32 GetCategoryFlags() const override;

        [[nodiscard]] KeyCode GetKeyCode() const;

    private:
        KeyCode m_KeyCode;
    };

}