//
// Created by ridham on 2026/04/20.
//

#pragma once
#include <nucleus/types/numericalAliases.h>

namespace nucleus
{
    enum class MouseButton : u8
    {
        Button0 = 0,   // Left
        Button1,       // Right
        Button2,       // Middle
        Button3,       // Back
        Button4,       // Forward
        Button5,
        Button6,
        Button7,
        Button8,

        Left   = Button0,
        Right  = Button1,
        Middle = Button2
    };

}