/**
 * @file keyboardButton.h
 * @brief Brief explaination goes here...
 * @details Detailed explaination goes here...
 *
 * @author ridham
 * @date 2026-06-05
 *
 * @bug No known bugs
 *
 * @copyright (c) 2026
 */


#pragma once
#include <nucleus/types/numericalAliases.h>

namespace nucleus
{
    enum class KeyCode : u16
    {
        Unknown = 0,

        // Letters
        A, B, C, D, E, F, G, H, I, J,
        K, L, M, N, O, P, Q, R, S, T,
        U, V, W, X, Y, Z,

        // Number row
        Key0,
        Key1,
        Key2,
        Key3,
        Key4,
        Key5,
        Key6,
        Key7,
        Key8,
        Key9,

        // Symbols
        Space,
        Apostrophe,
        Comma,
        Minus,
        Period,
        Slash,
        Semicolon,
        Equal,
        LeftBracket,
        RightBracket,
        Backslash,
        GraveAccent,

        // Control
        Escape,
        Enter,
        Tab,
        Backspace,

        // Navigation
        Insert,
        Delete,
        Home,
        End,
        PageUp,
        PageDown,

        Up,
        Down,
        Left,
        Right,

        // Locks
        CapsLock,
        NumLock,
        ScrollLock,

        // Modifiers
        LeftShift,
        RightShift,

        LeftControl,
        RightControl,

        LeftCtrl  = LeftControl,
        RightCtrl = RightControl,

        LeftAlt,
        RightAlt,

        LeftSuper,
        RightSuper,

        LeftWin   = LeftSuper,
        RightWin  = RightSuper,

        Menu,

        // Function Keys
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        F25,

        // Numpad
        KP0,
        KP1,
        KP2,
        KP3,
        KP4,
        KP5,
        KP6,
        KP7,
        KP8,
        KP9,

        KPDecimal,
        KPDivide,
        KPMultiply,
        KPSubtract,
        KPAdd,
        KPEnter,
        KPEqual,

        // System
        PrintScreen,
        Pause,

        // International / OEM
        World1,
        World2,

        Count
    };
}