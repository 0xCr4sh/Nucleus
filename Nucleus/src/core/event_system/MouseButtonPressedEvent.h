//
// Created by ridham on 2026/01/03.
//

#pragma once

#include <nucleus/core/event_system/event.h>
#include <nucleus/core/event_system/MouseButton.h>


namespace nucleus
{

    class MouseButtonPressedEvent final : public IEvent
    {
    public:
        explicit MouseButtonPressedEvent(MouseButton Button, f64 MouseX, f64 MouseY);

        [[nodiscard]] EventType GetEventType() const override;
        [[nodiscard]] const char* GetName() const override;
        [[nodiscard]] u32 GetCategoryFlags() const override;

        [[nodiscard]] f64 GetMouseX() const;
        [[nodiscard]] f64 GetMouseY() const;

        [[nodiscard]] MouseButton GetMouseButton() const;

    private:
        MouseButton m_Button;
        f64 m_MouseX = 0.0, m_MouseY = 0.0;
    };

}