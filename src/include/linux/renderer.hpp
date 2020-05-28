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

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

#include <GL/glx.h>

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
    void create() noexcept;

    // Initialize all of the class members
    void init_members() noexcept;

    // Creates an OpenGL context
    void create_opengl_context() noexcept;

    // Initializing all of the events and open the window
    void init_events() noexcept;

    // Handle all of the events
    void handle_events() noexcept;

// ------------------------------------------------------------ //

// Let the user access all of the members if he wants to
// in order to gain full access
#ifdef GFX_ACCESS_EVERYTHING
public:
#else
private:
#endif
    // All of the variables to access X Server window
    Display* display;
    Window   window;
    Atom     del_window;
    Screen*  screen;
    int screen_id;

    // These are changing the window context to OpenGL
    XVisualInfo* vi;
    GLXContext context;

    // Events handler
    XEvent ev;

private: // This is never being accessed no matter what
    // This is the mouse handlers that fetched from the
    // window events handler
    VectorI mouse_pos; 
    unsigned int button_pressed;

    friend class Mouse;
    friend class Keyboard;
    friend class GLFunctions;
}; // Renderer

END_NAMESPACE

#endif // RENDERER_HPP