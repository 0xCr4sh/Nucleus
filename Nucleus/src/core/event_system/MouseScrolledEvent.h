//
// Created by ridham on 2026/01/03.
//

#pragma once

#include <nucleus/core/event_system/event.h>

namespace nucleus
{

    class MouseScrolledEvent final : public IEvent
    {
    public:
        explicit MouseScrolledEvent(f64 MouseX, f64 MouseY, f64 OffsetX, f64 OffsetY);

        [[nodiscard]] EventType GetEventType() const override;
        [[nodiscard]] const char* GetName() const override;
        [[nodiscard]] u32 GetCategoryFlags() const override;

        [[nodiscard]] f64 GetMouseX() const;
        [[nodiscard]] f64 GetMouseY() const;
        [[nodiscard]] f64 GetScrollOffsetX() const;
        [[nodiscard]] f64 GetScrollOffsetY() const;

        [[nodiscard]] bool IsScrollUp() const;
        [[nodiscard]] bool IsScrollDown() const;

    private:
        f64 m_MouseX = 0.0, m_MouseY = 0.0;
        f64 m_OffsetX = 0.0, m_OffsetY = 0.0;
    };

}