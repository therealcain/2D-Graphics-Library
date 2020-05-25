#include "../../includes/windows/renderer.hpp"

#include <gl/GL.h> 
#include <gl/GLU.h> 

#define WINDOW_CLASS_NAME L"Window"

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
    // Clean up the window registers
    if (class_registered)
    {
        ReleaseDC(hwnd, hdc);
        UnregisterClassW(WINDOW_CLASS_NAME, instance);
        class_registered = false;
    }
}

// ------------------------------------------------------------ //

Renderer& Renderer::get_renderer() noexcept
{
    return *this;
}

// ------------------------------------------------------------ //

void Renderer::set_title(const std::string& title)
{
    std::wstring converted_title(title.begin(), title.end());

    // SetWindowText is expecting wide characters string
    SetWindowText(hwnd, converted_title.c_str());

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
    return handle_events();
}

// ------------------------------------------------------------ //

void Renderer::close() noexcept
{
    running = false;
}

// ------------------------------------------------------------ //

void Renderer::swap_buffers() noexcept
{
    SwapBuffers(hdc);
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

// ------------------------------------------------------------ //

void Renderer::create() noexcept
{
    init_members();
    hdc = GetDC(hwnd);

    glEnable(GL_MULTISAMPLE);
    
    running = true;
}

// ------------------------------------------------------------ //

void Renderer::init_members()
{ 
    // Making sure a class wasn't registered into
    // the memory
    if (!class_registered)
    {
        // Setting all of the settings of the window
        WNDCLASS wc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.hInstance = instance;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = WINDOW_CLASS_NAME;
        wc.style = 0;
        wc.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);

        // Register class into the memory
        RegisterClass(&wc);
        class_registered = true;
    }

    // Creating a static window with the give size
    hwnd = CreateWindow(
        WINDOW_CLASS_NAME, 
        L"", 
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE, 
        CW_USEDEFAULT, CW_USEDEFAULT,
        m_geometry.width, 
        m_geometry.height, 
        nullptr, 
        nullptr, 
        instance, 
        nullptr);

    // Make sure window has not failed
    abort_null(hwnd, "Window couldn't to create!");

    // Changing the window attributes
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG>(this));

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

LRESULT CALLBACK Renderer::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        // ON DESTROY it's removing the OpenGL context first
        // and then destroying the window
    case WM_DESTROY:
        wglDeleteContext(wglGetCurrentContext());
        DestroyWindow(hWnd);
        break;
        // ON CLOSE it's quiting the window
    case WM_CLOSE:
        wglDeleteContext(wglGetCurrentContext());
        PostQuitMessage(0);
        break;
        // ON STARTUP it's creating an OpenGL context
    case WM_CREATE:
        create_opengl_context(hWnd);
        break;
        // Calling the default window procedure
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }

    return 0;
}

// ------------------------------------------------------------ //

void Renderer::create_opengl_context(HWND hWnd) noexcept
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR), // Size
        1,                             // Version
        PFD_DRAW_TO_WINDOW |           // Buffer can draw to window
            PFD_SUPPORT_OPENGL |       // Buffer support OpenGL
            PFD_DOUBLEBUFFER,          // Has 2 Buffers
        PFD_TYPE_RGBA,                 // RGBA Pixel data
        32,                            // Color bits of the framebuffer
        0, 0, 0, 0, 0, 0, 0,           // Color bit planes
        0, 0, 0, 0, 0, 0,              // Color bit planes
        24,                            // bits for the Z buffer
        8,                             // bits for the stencil buffer
        0,                             // bits for the auxiliary buffes
        PFD_MAIN_PLANE,                // This is probably deprecated
                                        // Because early implementations 
                                        // of OpenGL used it
        0, 0, 0, 0                     // Color masks
    };

    HDC window_handle_to_device_context = GetDC(hWnd);

    // setting pixel format for the window context
    int window_pixel_format = ChoosePixelFormat(window_handle_to_device_context, &pfd);
    SetPixelFormat(window_handle_to_device_context, window_pixel_format, &pfd);

    // Creating the context
    HGLRC opengl_rendering_context = wglCreateContext(window_handle_to_device_context);
    wglMakeCurrent(window_handle_to_device_context, opengl_rendering_context);

    std::cout << "[WINDOWS] GL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "[WINDOWS] GL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "[WINDOWS] GL Version: " << glGetString(GL_VERSION) << std::endl;

    ReleaseDC(hWnd, window_handle_to_device_context);
}

// ------------------------------------------------------------ //

void CALLBACK Renderer::force_update() 
{
    // Unsued
}

bool Renderer::handle_events() noexcept
{
    // Extracting the message from the message handler
    // Right into this class memory so i can use it later
    // from other places
    if (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        // Call the unused update function every 1 miliseconds
        SetTimer(hwnd, 0, 1, reinterpret_cast<TIMERPROC>(&force_update));

        // Translate virtual keys and send the message
        // to the window procedure
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // Should be true unless window was interrupted
        // with the exit function
        return running;
    }

    return false;
}

END_NAMESPACE