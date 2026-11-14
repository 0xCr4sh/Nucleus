//
// Created by ridham on 2026/01/02.
//

#pragma once

#include <nucleus/core/event_system/event.h>

namespace nucleus
{

    class WindowCloseEvent final : public IEvent
    {
    public:
        [[nodiscard]] EventType GetEventType() const override;
        [[nodiscard]] const char* GetName() const override;
        [[nodiscard]] u32 GetCategoryFlags() const override;
    };

}