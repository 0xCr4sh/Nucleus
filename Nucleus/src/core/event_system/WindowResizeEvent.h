//
// Created by ridham on 2026/01/02.
//

#pragma once

#include <nucleus/core/event_system/event.h>

namespace nucleus
{

    class WindowResizeEvent final : public IEvent
    {
    public:
        explicit WindowResizeEvent(u32 width, u32 height);

        [[nodiscard]] EventType GetEventType() const override;
        [[nodiscard]] const char* GetName() const override;
        [[nodiscard]] u32 GetCategoryFlags() const override;

        [[nodiscard]] u32 GetWidth() const;
        [[nodiscard]] u32 GetHeight() const;

    private:
        u32 m_Width = 0, m_Height = 0;
    };

}