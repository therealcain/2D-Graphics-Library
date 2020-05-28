#ifndef PARENT_RENDERER_HPP
#define PARENT_RENDERER_HPP

#include "utils/utils.hpp"
#include "utils/geometry.hpp"

#include <chrono>
#include <atomic>

START_NAMESPACE

// Forward Declaration
class Renderer;

class ParentRenderer
{
public:
    // This function is being called every tick
    virtual void on_update() = 0;

// ------------------------------------------------------------ //

    // return a reference to itself
    virtual Renderer& get_renderer() = 0;

// ------------------------------------------------------------ //

    // Swapping both GPU buffers
    virtual void swap_buffers() = 0;

// ------------------------------------------------------------ //

    // Change the title of the window
    virtual void set_title(const std::string& title) = 0;
    // Get the title of the window
    const std::string& get_title() const;

// ------------------------------------------------------------ //

    // Get the width and height of the window
    const Geometry& get_geometry() const;

// ------------------------------------------------------------ //

    // Fetch the next event if it was failed
    // the program will shutdown
    virtual bool is_running() = 0;

// ------------------------------------------------------------ //

    // Forces a close on the window
    void close();

// ------------------------------------------------------------ //

    // Returning the framerate in ms
    double get_framerate() const;

// ------------------------------------------------------------ //

    // Returning if the current window is active
    bool is_focused() const;

// ------------------------------------------------------------ //

// Let the user access all of the members if he wants to
// in order to gain full access
#ifdef GFX_ACCESS_EVERYTHING
public:
#else
protected:
#endif
    // Window width and height
    Geometry m_geometry;
    
    // It's job is to get if the window is running
    bool running;

    // The window title
    std::string m_title;

// ------------------------------------------------------------ //

// This cannot be shared with the user
protected:
    // This is the frame rate ticks
    // It's cannot be touched from the user
    std::chrono::high_resolution_clock::time_point start_ticks;
    
    // Threading support
    std::atomic<bool> focused;
}; // ParentRenderer

END_NAMESPACE

#endif // PARENT_RENDERER_HPP