#include "../../include/linux/renderer.hpp"

START_NAMESPACE

Renderer::Renderer(const Geometry& geometry, const std::string& title)
    : m_geometry(geometry)
{
    create();
    set_title(title);
}

Renderer::Renderer(const Geometry& geometry)
    : m_geometry(geometry)
{
    create();
}

Renderer::Renderer(unsigned int width, unsigned int height, const std::string& title)
    : m_geometry(width, height)
{
    create();
    set_title(title);
}

Renderer::Renderer(unsigned int width, unsigned int height)
    : m_geometry(width, height)
{
    create();
}

// Destructor
Renderer::~Renderer()
{
    // Destroying the window and closing connection to X Server
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

// ------------------------------------------------------------ //

Renderer& Renderer::get_renderer() noexcept
{
    return *this;
}

// ------------------------------------------------------------ //

void Renderer::set_title(const std::string& title)
{
    // Changing the title variable into the title argument
    XStoreName(display, window, title.c_str());
    XChangeProperty(
        display, 
        window, 
        XInternAtom(display, "_NET_WM_NAME", false), 
        XInternAtom(display, "UTF8_STRING", false), 
        8, 
        PropModeReplace, 
        reinterpret_cast<unsigned char*>(const_cast<char*>(title.c_str())), 
        title.size());

    m_title = title;
}

const std::string& Renderer::get_title() const noexcept
{
    return m_title;
}

// ------------------------------------------------------------ //

const Geometry& Renderer::get_geometry() const noexcept
{
    return m_geometry;
}

// ------------------------------------------------------------ //

bool Renderer::is_running() noexcept
{
    start_ticks = std::chrono::high_resolution_clock::now();
    handle_events();
    return running;
}

// ------------------------------------------------------------ //

void Renderer::close() noexcept {
    running = false;
}

// ------------------------------------------------------------ //

void Renderer::swap_buffers() noexcept {
    glXSwapBuffers(display, window);
}

// ------------------------------------------------------------ //

double Renderer::get_framerate() const
{
    using namespace std::chrono;

    high_resolution_clock::time_point current_ticks = high_resolution_clock::now();

    auto delta_ticks = duration_cast<duration<double>>(current_ticks - start_ticks);

    if (delta_ticks.count() > 0)
        return CLOCKS_PER_SEC / delta_ticks.count();

    return 0.0;
}

bool Renderer::is_focused() const {
    return focused;
}

// ------------------------------------------------------------ //

void Renderer::create() noexcept
{
    init_members();
    create_opengl_context();
    init_events();
    
    running = true;
}

// ------------------------------------------------------------ //

void Renderer::init_members() noexcept
{ 
    // Connecting to the X server and making sure
    // everything was OK
    display = XOpenDisplay(nullptr);
    abort_null(display, "Display couldn't to be created!");

    // getting the current screen
    screen = DefaultScreenOfDisplay(display);
    screen_id = DefaultScreen(display);
}

// ------------------------------------------------------------ //

void Renderer::create_opengl_context() noexcept
{
    // This is basically similar to the attributes
    // above of the Renderers version
    GLint glxAttribs[] = {
        GLX_RGBA,
        GLX_DOUBLEBUFFER,
        GLX_DEPTH_SIZE,     24,
        GLX_STENCIL_SIZE,   8,
        GLX_RED_SIZE,       8,
        GLX_GREEN_SIZE,     8,
        GLX_BLUE_SIZE,      8,
        GLX_SAMPLE_BUFFERS, 0,
        GLX_SAMPLES,        0,
        None
    };

    // Visual type for the screen
    vi = glXChooseVisual(display, 0, glxAttribs);
    abort_null(vi, "Window couldn't to create!");

    // Setting all of the Renderer attributes
    XSetWindowAttributes window_attribs;
    window_attribs.border_pixel = BlackPixel(display, screen_id);
    window_attribs.background_pixel = WhitePixel(display, screen_id);
    window_attribs.override_redirect = true;
    window_attribs.colormap = XCreateColormap(display, RootWindow(display, screen_id), vi->visual, AllocNone);
    window_attribs.event_mask = ExposureMask;

    // Finally, Creating the Window with the opengl context
    window = XCreateWindow(
        display, 
        RootWindow(display, screen_id), 
        0, 0, 
        m_geometry.width, m_geometry.height, 
        0, 
        vi->depth,
        InputOutput, 
        vi->visual, 
        CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, 
        &window_attribs);

    context = glXCreateContext(display, vi, nullptr, true);
    glXMakeCurrent(display, window, context);

    // Making sure the window cannot be scaled down or up
    XSizeHints hints;
    hints.min_width = m_geometry.width;
    hints.min_height = m_geometry.height;
    hints.max_width = m_geometry.width;
    hints.max_height = m_geometry.height;
    XSetWMNormalHints(display, window, &hints);

    std::cout << "[LINUX] GL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "[LINUX] GL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "[LINUX] GL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "[LINUX] GL Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

// ------------------------------------------------------------ //

void Renderer::init_events() noexcept
{
    // Process the window close event with the destructor
    del_window = XInternAtom(display, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(display, window, &del_window, 1);

    // The only events i'm going to use
    // are checking if a button has been pressed
    // or if the mouse was moved
    XSelectInput(display, window, PointerMotionMask | ButtonPressMask | KeyPressMask | FocusChangeMask);

    // Clears the entire Renderer and making sure 
    // Nothing is being displayed
    XClearWindow(display, window);

    // Raise the Renderer on top of the stack.
    XMapRaised(display, window);
}

void Renderer::handle_events() noexcept
{
    button_pressed = 0;
    
    // Clening all of the pending events
    // and extract only the mouse position
    while (XPending(display))
    {
        XCheckWindowEvent(display, window, 1, &ev);
        XNextEvent(display, &ev);

        // When user in the window
        if(ev.type == FocusIn) 
            focused = true;
        else if(ev.type == FocusOut)
            focused = false;

        // The other events will only work if
        // the window is focused
        if(focused == true)
        {
            // Exit the window
            if(ev.type == ClientMessage)
            {
                running = false;
                return;
            }

            // Mouse is moving
            else if (ev.type == MotionNotify)
            {
                mouse_pos.x = ev.xmotion.x;
                mouse_pos.y = ev.xmotion.y;
            }

            // Mouse button
            else if(ev.type == ButtonPress)
                button_pressed = ev.xbutton.button;
        }

        XFlush(display);
    }
}

END_NAMESPACE