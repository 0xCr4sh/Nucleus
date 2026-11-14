//
// Created by ridham on 2026/01/03.
//

#pragma once

#include <nucleus/core/event_system/event.h>

namespace nucleus
{

    class MouseMovedEvent final : public IEvent
    {
    public:
        explicit MouseMovedEvent(f64 mouseX, f64 mouseY, f64 dx, f64 dy);

        [[nodiscard]] EventType GetEventType() const override;
        [[nodiscard]] const char* GetName() const override;
        [[nodiscard]] u32 GetCategoryFlags() const override;

        [[nodiscard]] f64 getMouseX() const;
        [[nodiscard]] f64 getMouseY() const;
        [[nodiscard]] f64 getMouseDX() const;
        [[nodiscard]] f64 getMouseDY() const;

    private:
        f64 m_MouseX = 0.0, m_MouseY = 0.0, m_dx = 0.0, m_dy = 0.0;
    };

}