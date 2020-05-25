///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
/////////////////////////////////////////////////////////// 
// This header contains the keyboard input               //
// functionalities.                                      //
///////////////////////////////////////////////////////////

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "../../utils/utils.hpp"

#include <X11/keysym.h>

START_NAMESPACE

class Keyboard
{
public:
    // This class does not need to be initialized.
    // Users need to access it's functions directly
    // because all of the functions are static
    Keyboard() = delete;

    // ------------------------------------------------------------ //

    // All of the possible keys that this library support
    enum class Key
    {
         // Alphabetic
        A = XK_A, B = XK_B, C = XK_C, D = XK_D,
        E = XK_E, F = XK_F, G = XK_G, H = XK_H,
        I = XK_I, J = XK_J, K = XK_K, L = XK_L,
        M = XK_M, N = XK_N, O = XK_O, P = XK_P,
        Q = XK_Q, R = XK_R, S = XK_S, T = XK_T,
        U = XK_U, V = XK_V, W = XK_W, X = XK_X,
        Y = XK_Y, Z = XK_Z,
        // Arrows
        LeftArrow = XK_Left, RightArrow = XK_Right,
        UpArrow = XK_Up, DownArrow = XK_Down,
        // Numpad Numbers
        Numpad0 = XK_KP_0, Numpad1 = XK_KP_1,
        Numpad2 = XK_KP_2, Numpad3 = XK_KP_3,
        Numpad4 = XK_KP_4, Numpad5 = XK_KP_5,
        Numpad6 = XK_KP_6, Numpad7 = XK_KP_7,
        Numpad8 = XK_KP_8, Numpad9 = XK_KP_9,
        // Numbers
        Num0 = XK_0, Num1 = XK_1, Num2 = XK_2,
        Num3 = XK_3, Num4 = XK_4, Num5 = XK_5,
        Num6 = XK_6, Num7 = XK_7, Num8 = XK_8,
        Num9 = XK_9,
        // F's
        F1 = XK_F1, F2 = XK_F2, F3 = XK_F3,
        F4 = XK_F4, F5 = XK_F5, F6 = XK_F6,
        F7 = XK_F7, F8 = XK_F8, F9 = XK_F9,
        F10 = XK_F10, F11 = XK_F11, F12 = XK_F12,
        // Other
        LShift = XK_Shift_L, RShift = XK_Shift_R
    };

    // ------------------------------------------------------------ //

    // Returns true if a key was pressed
    static bool key_pressed(Key key);
    // Has an option for ascii codes
    static bool key_pressed(unsigned int key);
}; // Keyboard

END_NAMESPACE

#endif // KEYBOARD_HPP