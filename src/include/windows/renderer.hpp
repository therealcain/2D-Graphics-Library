///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This file handling the window that is going to be     //
// displayed on the screen, and it's creating an OpenGL  //
// context for the user, with a little bit more          //
// extensions than "just creting the window".            //
///////////////////////////////////////////////////////////
// If you want to access all of the variables here from  //
// your code, make sure to add before including gfx.hpp: //
// #define GFX_ACCESS_EVERYTHING                         //
///////////////////////////////////////////////////////////

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../utils/utils.hpp"
#include "../utils/geometry.hpp"

#include "../parent_renderer.hpp"

#include <windows.h>

START_NAMESPACE

class Renderer : public ParentRenderer
{
public:
    // Constructors
    explicit Renderer(const Geometry& geometry);
    explicit Renderer(unsigned int width, unsigned int height);
    ~Renderer();

// ------------------------------------------------------------ //

public:
    void swap_buffers() override;

// ------------------------------------------------------------ //

    Renderer& get_renderer() override;

// ------------------------------------------------------------ //

    void set_title(const std::string& title) override;

// ------------------------------------------------------------ //

    bool is_running() override;

// ------------------------------------------------------------ //

private:
    // Calling all of the creation functions
    void create();

    // Initialize all of the class members
    void init_members();

    // Events handling
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // Creates an OpenGL context
    static void create_opengl_context(HWND hwnd) noexcept;

    // This is going to be unused, it's just telling
    // windows to never stop updating the screen
    static void CALLBACK force_update();

    // Handle all of the events
    bool handle_events() noexcept;

// ------------------------------------------------------------ //

// Let the user access all of the members if he wants to
// in order to gain full access
#ifdef GFX_ACCESS_EVERYTHING
public:
#else
private:
#endif
    // Window
    HWND m_hwnd;
    HINSTANCE instance;

    // Events
    MSG msg;

// This shouldn't be accessed from the user
private:
    // Class has been created
    bool class_registered;

    friend class Mouse;
    friend class GLFunctions;
}; // Renderer

END_NAMESPACE

#endif // RENDERER_HPP