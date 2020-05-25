///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
/////////////////////////////////////////////////////////// 
// This header contains the mouse input functionalities. //
///////////////////////////////////////////////////////////

#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "../renderer.hpp"
#include "../../util/util.hpp"

#include <windows.h>

START_NAMESPACE

class Mouse
{
public:
    // This class does not need to be initialized.
    // Users need to access it's functions directly
    // because all of the functions are static
    Mouse() = delete;

    // ------------------------------------------------------------ //

    // All of the possible mouse buttons
    enum class Button
    {
        Left = VK_LBUTTON, Middle = VK_MBUTTON, Right = VK_RBUTTON,
        ScrollUp = 0x100, ScrollDown = 0x101 // This values i made up
    }; // Button

    // ------------------------------------------------------------ //

    // Check which button on the mouse was clicked
    static bool button_pressed(Renderer& renderer, Button button);

    // Return the position of the mouse on the window
    static VectorI motion(Renderer& renderer);

}; // Mouse

END_NAMESPACE

#endif // MOUSE_HPP