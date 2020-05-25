///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
/////////////////////////////////////////////////////////// 
// This header contains the keyboard input               //
// functionalities.                                      //
///////////////////////////////////////////////////////////

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#pragma once

#include <windows.h>

#include "../../util/util.hpp"

START_NAMESPACE

class Keyboard
{
public:
    // This class does not need to be initialized.
    // Users need to access it's functions directly
    // because all of the functions are static
    Keyboard() = delete;

    // All of the possible keys that this library support
    enum class Key
    {
        // Alphabetic
        A = 0x41, B = 0x42, C = 0x43, D = 0x44,
        E = 0x45, F = 0x46, G = 0x47, H = 0x48,
        I = 0x49, J = 0x4A, K = 0x4B, L = 0x4C,
        M = 0x4D, N = 0x4E, O = 0x4F, P = 0x50,
        Q = 0x51, R = 0x52, S = 0x53, T = 0x54,
        U = 0x55, V = 0x56, W = 0x57, X = 0x58,
        Y = 0x59, Z = 0x5A,
        // Arrows
        LeftArrow = VK_LEFT, RightArrow = VK_RIGHT,
        UpArrow = VK_UP, DownArrow = VK_DOWN,
        // Numpad Numbers
        Numpad0 = VK_NUMPAD0, Numpad1 = VK_NUMPAD1,
        Numpad2 = VK_NUMPAD2, Numpad3 = VK_NUMPAD3,
        Numpad4 = VK_NUMPAD4, Numpad5 = VK_NUMPAD5,
        Numpad6 = VK_NUMPAD6, Numpad7 = VK_NUMPAD7,
        Numpad8 = VK_NUMPAD8, Numpad9 = VK_NUMPAD9,
        // Numbers
        Num0 = 0x30, Num1 = 0x31, Num2 = 0x32,
        Num3 = 0x33, Num4 = 0x34, Num5 = 0x35,
        Num6 = 0x36, Num7 = 0x37, Num8 = 0x38,
        Num9 = 0x39,
        // F's
        F1 = VK_F1, F2 = VK_F2, F3 = VK_F3,
        F4 = VK_F4, F5 = VK_F5, F6 = VK_F6,
        F7 = VK_F7, F8 = VK_F8, F9 = VK_F9,
        F10 = VK_F10, F11 = VK_F11, F12 = VK_F12,
        // Other
        LShift = VK_LSHIFT, RShift = VK_RSHIFT
    };

    // Has an option for ascii codes
    static bool key_pressed(unsigned int key);
    // Returns true if a key was pressed
    static bool key_pressed(Key key);
}; // Keyboard

END_NAMESPACE

#endif // KEYBOARD_HPP