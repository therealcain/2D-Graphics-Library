#include "../../include/windows/renderer.hpp"

#include <gl/GL.h> 
#include <gl/GLU.h> 

#include <string>

#define WINDOW_CLASS_NAME L"Window"

START_NAMESPACE

Renderer::Renderer(const Geometry& geometry)
{
    /*Parent*/ m_geometry = geometry;
    create();
}

Renderer::Renderer(unsigned int width, unsigned int height)
{
    /*Parent*/ m_geometry = {width, height};
    create();
}

Renderer::~Renderer()
{
    // Clean up the window registers
    if (class_registered)
    {
        UnregisterClassW(WINDOW_CLASS_NAME, instance);
        class_registered = false;
    }
}

// ------------------------------------------------------------ //

Renderer& Renderer::get_renderer() /*override*/ {
    return *this;
}

// ------------------------------------------------------------ //

void Renderer::set_title(const std::string& title) /*override*/
{
    std::wstring converted_title(title.begin(), title.end());

    // SetWindowText is expecting wide characters string
    SetWindowText(m_hwnd, converted_title.c_str());

    /*Parent*/ m_title = title;
}

// ------------------------------------------------------------ //

bool Renderer::is_running() /*override*/
{
    /*Parent*/ start_ticks = std::chrono::high_resolution_clock::now();
    return handle_events();
}

// ------------------------------------------------------------ //

void Renderer::swap_buffers() /*override*/
{
    HDC hdc = GetDC(m_hwnd);
    SwapBuffers(hdc);
    ReleaseDC(m_hwnd, hdc);
}

// ------------------------------------------------------------ //

void Renderer::create()
{
    init_members();
    
    /*Parent*/ running = true;
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

    // Creating a static window with the given size
    m_hwnd = CreateWindow(
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
    abort_null(m_hwnd, "Window couldn't to create!");

    // Changing the window attributes
    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG>(this));

    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);
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
    case WM_NOTIFY:
        std::cout << "notify" << std::endl;
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
    ReleaseDC(hWnd, window_handle_to_device_context);

    // This is for threading, to set on focus the last window
    SetFocus(hWnd);

    std::cout << "[WINDOWS] GL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "[WINDOWS] GL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "[WINDOWS] GL Version: " << glGetString(GL_VERSION) << std::endl;
}

// ------------------------------------------------------------ //

void CALLBACK Renderer::force_update() {
    // Unsued
}

bool Renderer::handle_events() noexcept
{
    // Extracting the message from the message handler
    // Right into this class memory so i can use it later
    // from other places
    if (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        HWND hwnd = GetFocus();

        if(hwnd != nullptr)
        {
            // Call the unused update function every 1 miliseconds
            SetTimer(m_hwnd, 0, 1, reinterpret_cast<TIMERPROC>(&force_update));

            // Translate virtual keys and send the message
            // to the window procedure
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            // The window is focused
            focused = true;
        }
        else
            focused = false;

        // Should be true unless window was interrupted
        // with the exit function
        return running;

    }

    return false;
}

END_NAMESPACE
