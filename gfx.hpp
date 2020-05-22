// ----------------------------------------------------- //
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
// ----------------------------------------------------- //
// This is a very simple lightweight - straightforward   //
// implementation of a graphics library, support C++11   //
// and old hardware.                                     //
// ----------------------------------------------------- //
// You can check the documentation in my blog.           //
// ----------------------------------------------------- //
// Linux:                                                // 
// GCC: g++ main.cpp -lX11 -lGL                          //
// Clang: g++ main.cpp -lX11 -lGL                        //
// ------------                                          //
// Windows:                                              //
// MSVC: Just to build and run :)                        //
// MinGW: g++ main.cpp -lopengl32 -lglu32 -lgdi32        //
// ----------------------------------------------------- //
// If you don't planning on using the opengl             //
// functionalities and only using the input and window   //
// handlers, then you can define it before including     //
// this file:                                            //
// #define ONLY_OPENGL_CONTEXT                           //
// #include "gfx.hpp"                                    //
// ----------------------------------------------------- //

#ifndef GFX_HPP
#define GFX_HPP

// ----------------------------------------------------------- //

#define WINDOWS _WIN32
#define LINUX   __linux__
#define MSVC    _MSC_VER
#define MINGW   __MINGW32__

#if MINGW
#define _UNICODE
#define UNICODE
#endif // MINGW

// ----------------------------------------------------------- //

#if WINDOWS
#include <windows.h>
#define WINDOW_CLASS_NAME L"Window"
// OpenGL includes
#include <gl/GL.h> 
#include <gl/GLU.h> 
#if MSVC
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#endif // MSVC

// ----------------------------------------------------------- //

#elif LINUX
// namespace X 
// {
#include <unistd.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
// }
// OpenGL includes
#include <GL/gl.h> 
#include <GL/glu.h>
#include <GL/glx.h>
#endif // Linux

// ----------------------------------------------------------- //

// Standard libraries
#include <iostream>
#include <type_traits>
#include <stdexcept>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <chrono>

// ----------------------------------------------------------- //

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// ----------------------------------------------------------- //

#ifdef M_PI
constexpr double PI = M_PI;
#else
constexpr double PI = 3.14159265358979323;
#endif
constexpr double PI2 = PI * 2;

// ----------------------------------------------------------- //

namespace gfx
{
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // --------------------- UTILITY ----------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // A vector of any possible arithmetic type
    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    struct Vector
    {
        T x;
        T y;

        Vector() = default;
        Vector(T X, T Y)
            : x(X), y(Y) {}

        // Just to ease on printing the vector
        inline friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
            os << "X: " << vec.x << " Y:" << vec.y;
            return os;
        }
    }; // Vector

    // Type definitions
    using VectorI  = Vector<int>;
    using VectorUI = Vector<uint32_t>;
    using VectorF  = Vector<float>;

    // A very simple function that going to ease on casting vector
    // to another vector of another type.
    // there is no need for SFINAE here because Vector<T> is going
    // to check the type anyway.
    template<typename T, typename U>
    inline Vector<T> vector_cast(const Vector<U>& src) {
        return Vector<T>(static_cast<T>(src.x), static_cast<T>(src.y));
    }

    // ----------------------------------------------------------- //

    // Color structure made of RGBA
    // R - Red
    // G - Green
    // B - Blue
    // A - Alpha
    struct Color
    {
        uint16_t R;
        uint16_t G;
        uint16_t B;
        uint16_t A;

        Color() = default;
        Color(uint16_t red, uint16_t green, uint16_t blue)
            : R(red), G(green), B(blue), A(1) {}
        Color(uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha)
            : R(red), G(green), B(blue), A(alpha) {}

        // Just to ease on printing the color
        inline friend std::ostream& operator<<(std::ostream& os, const Color& color) {
            os << "R: " << color.R << " G:" << color.G << " B:" << color.B << " A:" << color.A;
            return os;
        }
    }; // Color

    // Color codes
    Color ColorBlack = { 0  , 0  , 0  , 1 };
    Color ColorRed = { 255, 0  , 0  , 1 };
    Color ColorGreen = { 0  , 255, 0  , 1 };
    Color ColorBlue = { 0  , 0  , 255, 1 };
    Color ColorWhite = { 255, 255, 255, 1 };

    // ----------------------------------------------------------- //

    // This structure is holding the ID of the texture
    // This could probably have more functions in the future
    struct Texture
    {
    protected:
        uint32_t id;

        friend class Renderer;
    };

    // ----------------------------------------------------------- //

    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // --------------------- Renderer ---------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    class Renderer
    {
    public:
        // Creates a Renderer with a given size
        explicit Renderer(const VectorUI& Size)
            : running(true), size(Size)
        {
#if WINDOWS
            create_window_windows();
            hdc = GetDC(hwnd);
#elif LINUX
            create_window_linux();
#endif
        }

        // ----------------------------------------------------------- //

        // This function handling the events and returns
        // if the window is still running in order
        // to let the while loop continue
        // Also this function handling the opengl buffer
        // and setting the projection to 2 dimensional
        bool is_running() noexcept
        {
#if !ONLY_OPENGL_CONTEXT
            // Clearing the buffers
            glClear(GL_COLOR_BUFFER_BIT);

            // Changing the viewport to screen size
            glViewport(0, 0, size.x, size.y);

            // Changing the scene to orthogonal projection
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, size.x, size.y, 0, -1, 1);

            // The matrix of all of the objects are going to be 
            // treated as the model view
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
#endif // !ONLY_OPENGL_CONTEXT

            // This is for calculating the frame time 
            // from each update
            start_ticks = std::chrono::high_resolution_clock::now();

#if WINDOWS
            return check_events_windows();
#elif LINUX
            return check_events_linux();
#endif
            return false;
        }

        // ----------------------------------------------------------- //

        // Clearing the screen with a specific color
        inline void clear(const Color& color) {
            // This function expect a value between 0 to 1
            glClearColor(color.R / 255.f, color.G / 255.f, color.B / 255.f, 1);
        }
        // Clearing the screen to default value which is black
        inline void clear() {
            glClearColor(0, 0, 0, 1);
        }

        // ----------------------------------------------------------- //

        // Swapping the render pipeline buffers
        // to draw anything
#if !ONLY_OPENGL_CONTEXT

        inline void show() noexcept
#else
        // This is changing the name for more 
        // understandable name for people that wants
        // to understand a little bit better
        inline void swap_buffers() noexcept
#endif // !ONLY_OPENGL_CONTEXT
        {
#if WINDOWS
            SwapBuffers(hdc);
#elif LINUX
            glXSwapBuffers(display, window);
#endif
        }

        // ----------------------------------------------------------- //

        // Force an exit from the window
        inline void exit() {
            running = false;
        }

        // ----------------------------------------------------------- //

        // Change the title of the window
        void set_title(const std::string& title) noexcept
        {
#if WINDOWS
            std::wstring converted_title(title.begin(), title.end());

            // SetWindowText is expecting wide characters string
            SetWindowText(hwnd, converted_title.c_str());
#elif LINUX
            XStoreName(display, window, title.c_str());
#endif
        }

        // ----------------------------------------------------------- //

        // This function should be used at the end of 
        // the renderer loop in order to benchmark
        // and calculate the frame time correctly.
        float get_frame_time() noexcept
        {
            using namespace std::chrono;

            high_resolution_clock::time_point current_ticks = high_resolution_clock::now();
            
            auto delta_ticks = duration_cast<duration<double>>(current_ticks - start_ticks);

            if ( delta_ticks.count() > 0)
                return CLOCKS_PER_SEC / delta_ticks.count();

            return 0.0;
        }

        // ----------------------------------------------------------- //

#if !ONLY_OPENGL_CONTEXT
        // ------------- DRAWING --------------------- //
        // Drawing a pixel at a specific position with a 
        // particular color.
        void draw_pixel(const VectorUI& position, const Color& color)
        {
            glColor4ub(color.R, color.G, color.B, color.A);

            glBegin(GL_POINTS);
            glVertex2f(position.x, position.y);
            glEnd();

            glColor4f(1.f, 1.f, 1.f, 1.f);
        }

        // Drawing a line from starting position to end position 
        // in a specific color
        void draw_line(const VectorUI& start_pos, const VectorUI& end_pos, const Color& color) const noexcept
        {
            glColor4ub(color.R, color.G, color.B, color.A);

            glBegin(GL_LINES);
            glVertex2f(start_pos.x, start_pos.y);
            glVertex2f(end_pos.x, end_pos.y);
            glEnd();

            glColor4f(1.f, 1.f, 1.f, 1.f);
        }

        // Drawing a rectangle at position with a specific size
        // in a specific color
        void draw_rectangle(const VectorUI& position, const VectorUI& size, const Color& color, bool fill)  const noexcept
        {
            glColor4ub(color.R, color.G, color.B, color.A);

            glBegin(fill ? GL_QUADS : GL_LINE_LOOP);
            glVertex2f(position.x, position.y);
            glVertex2f(position.x + size.x, position.y);
            glVertex2f(position.x + size.x, position.y + size.y);
            glVertex2f(position.x, position.y + size.y);
            glEnd();

            glColor4f(1.f, 1.f, 1.f, 1.f);
        }

        // Drawing a circle at position with a specific radius
        // in a specific color
        void draw_circle(const VectorUI& position, double radius, const Color& color, bool fill) const noexcept
        {
            glColor4ub(color.R, color.G, color.B, color.A);

            if (fill)
            {
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(position.x, position.y);
                for (int i = 0; i <= 20; i++)
                {
                    Vector<float> temp;
                    temp.x = position.x + (radius * cosf(i * PI2 / 20));
                    temp.y = position.y + (radius * sinf(i * PI2 / 20));

                    glVertex2f(temp.x, temp.y);
                }
                glEnd();
            }
            else
            {
                constexpr int segments = 100;

                glBegin(GL_LINE_LOOP);
                for (int i = 0; i < segments; i++)
                {
                    float theta = PI2 * i / segments;

                    Vector<float> temp;
                    temp.x = radius * cosf(theta);
                    temp.y = radius * sinf(theta);

                    glVertex2f(position.x + temp.x, position.y + temp.y);
                }
                glEnd();
            }

            glColor4f(1.f, 1.f, 1.f, 1.f);
        }

        // Loading the texture from the file using stb
        Texture load_texture(const std::string& filename) const
        {
            Texture tex;
            unsigned char* data;
            int nr_channels;
            int width;
            int height;

            // Fetching all of the data from the image
            data = stbi_load(filename.c_str(), &width, &height, &nr_channels, 0);

            if (data)
            {
                // Creating a texture based on this data
                glGenTextures(1, &tex.id);
                glBindTexture(GL_TEXTURE_2D, tex.id);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                // Cleaning data because the data already passed 
                // to opengl
                stbi_image_free(data);
            }
            else
                throw std::runtime_error("Failed to load texture!");

            return tex;
        }

        // Drawing a texture with position and size
        void draw_texture(Texture& texture, const VectorUI& position, const VectorUI& size)
        {
            // Telling OpenGL that we are going to render
            // 2D Texture
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture.id);

            // Rendering all of the texture as a rectangle
            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex2f(position.x, position.y);
            glTexCoord2f(1, 0);
            glVertex2f(position.x + size.x, position.y);
            glTexCoord2f(1, 1);
            glVertex2f(position.x + size.x, position.y + size.y);
            glTexCoord2f(0, 1);
            glVertex2f(position.x, position.y + size.y);
            glEnd();

            // All of the other shapes that coming after this 
            // function are not going to be a texture
            // So OpenGL would be able to draw them correctly.
            glDisable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
#endif // !ONLY_OPENGL_CONTEXT

        // ----------------------------------------------------------- //

        // This is calling all of the clean ups
        ~Renderer()
        {
#if WINDOWS
            destroy_window_windows();
#elif LINUX
            destroy_window_linux();
#endif
        }

    private: // Functions
        // ----------------------------------------------------------- //
        // --------------------- WINDOWS ----------------------------- //
        // ----------------------------------------------------------- // 
        // This function creates a win32 window
        void create_window_windows()
        {
#if WINDOWS
            // Creating the window size
            RECT rc;
            rc.top = 0;
            rc.left = 0;
            rc.right = size.x;
            rc.bottom = size.y;

            // Making sure the window can be initialized 
            // with the given size
            if (!AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false))
                throw std::runtime_error("[WINDOWS] Failed to create Windows window!");

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
            hwnd = CreateWindow(WINDOW_CLASS_NAME, L"", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
                rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, instance, nullptr);

            // Make sure window has not failed
            if (hwnd == nullptr)
                throw std::runtime_error("[WINDOWS] Failed to create Windows window!");

            // Changing the window attributes
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG>(this));

            ShowWindow(hwnd, SW_SHOW);
            UpdateWindow(hwnd);
#endif
        }

#if WINDOWS
        // Windows events handling
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
                create_opengl_context_windows(hWnd);
                break;
                // Calling the default window procedure
            default:
                return DefWindowProc(hWnd, msg, wParam, lParam);
                break;
            }

            return 0;
        }
#endif
#if WINDOWS
        // Creating an opengl context window for windows
        static void create_opengl_context_windows(HWND hWnd) noexcept
        {
            PIXELFORMATDESCRIPTOR pfd = {
                sizeof(PIXELFORMATDESCRIPTOR), // Size
                1,                             // Version
                PFD_DRAW_TO_WINDOW |       // Buffer can draw to window
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
#endif

        // This function cleanning up the window memory
        void destroy_window_windows() noexcept
        {
#if WINDOWS
            // Clean up the window registers
            if (class_registered)
            {
                ReleaseDC(hwnd, hdc);
                UnregisterClassW(WINDOW_CLASS_NAME, instance);
                class_registered = false;
            }
#endif
        }
#if WINDOWS
        // This is going to be unused
        // it's here just to tell windows that
        // the window is going to be updated without
        // any stop
        static void CALLBACK force_update_windows() {}
#endif
        // Check all of the events for the window windows
        bool check_events_windows() noexcept
        {
#if WINDOWS
            // Extracting the message from the message handler
            // Right into this class memory so i can use it later
            // from other places
            if (GetMessage(&msg, nullptr, 0, 0) > 0)
            {
                // Call the unused update function every 1 miliseconds
                SetTimer(hwnd, 0, 1, reinterpret_cast<TIMERPROC>(&force_update_windows));

                // Translate virtual keys and send the message
                // to the window procedure
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                // Should be true unless window was interrupted
                // with the exit function
                return running;
            }
#endif
            return false;
        }

        // ----------------------------------------------------------- //
        // --------------------- LINUX ------------------------------- //
        // ----------------------------------------------------------- //
        // This function create an X11 window based on a size
        void create_window_linux()
        {
#if LINUX
            // Connecting to the X server and making sure
            // everything was OK
            display = XOpenDisplay(nullptr);
            if (display == nullptr)
                throw std::runtime_error("[LINUX] Could not open display!");

            // getting the current screen
            screen = DefaultScreenOfDisplay(display);
            screen_id = DefaultScreen(display);

            create_opengl_context_linux();

            // The only events i'm going to use
            // are checking if a button has been pressed
            // or if the mouse was moved
            XSelectInput(display, window, PointerMotionMask | ButtonPressMask);

            // Clears the entire window and making sure 
            // Nothing is being displayed
            XClearWindow(display, window);
            // Raise the window on top of the stack.
            XMapRaised(display, window);
#endif
        }

        // This function cleaning up the created window
        void destroy_window_linux() noexcept
        {
#if LINUX
            XDestroyWindow(display, window);
            XCloseDisplay(display);
#endif
        }

        // Fetch the next event if it was failed
        // the program will shutdown
        inline bool check_events_linux() noexcept
        {
#if LINUX
            XCheckWindowEvent(display, window, 1, &ev);

            return running;
#endif
            return false;
        }

        // Check if the opengl version is correct
        // if it's not throw an exception and stop the program
        void check_opengl_version_linux() const
        {
#if LINUX
            GLint majorGLX = 0;
            GLint minorGLX = 0;
            glXQueryVersion(display, &majorGLX, &minorGLX);

            if (majorGLX <= 1 && minorGLX < 2)
                throw std::runtime_error("[LINUX] GLX 1.2 or greater is required!");
#endif
        }

        // Creating an opengl context for X11
        void create_opengl_context_linux()
        {
#if LINUX
            check_opengl_version_linux();

            // This is basically similar to the attributes
            // above of the windows version
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

            // Making sure it's okay!
            if (vi == nullptr)
                throw std::runtime_error("[LINUX] No appropriate visual found!");
            else
                std::cout << "[LINUX] Visual " << reinterpret_cast<void*>(vi->visualid) << " selected!" << std::endl;

            // Setting all of the window attributes
            XSetWindowAttributes window_attribs;
            window_attribs.border_pixel = BlackPixel(display, screen_id);
            window_attribs.background_pixel = WhitePixel(display, screen_id);
            window_attribs.override_redirect = true;
            window_attribs.colormap = XCreateColormap(display, RootWindow(display, screen_id), vi->visual, AllocNone);
            window_attribs.event_mask = ExposureMask;

            // Finally, Creating the window with the opengl context
            window = XCreateWindow(display, RootWindow(display, screen_id), 0, 0, size.x, size.y, 0, vi->depth,
                InputOutput, vi->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &window_attribs);

            context = glXCreateContext(display, vi, nullptr, true);
            glXMakeCurrent(display, window, context);

            // Making sure the window cannot be scaled down or up
            XSizeHints hints;
            hints.min_width = size.x;
            hints.min_height = size.y;
            hints.max_width = size.x;
            hints.max_height = size.y;
            XSetWMNormalHints(display, window, &hints);

            std::cout << "[LINUX] GL Vendor: " << glGetString(GL_VENDOR) << std::endl;
            std::cout << "[LINUX] GL Renderer: " << glGetString(GL_RENDERER) << std::endl;
            std::cout << "[LINUX] GL Version: " << glGetString(GL_VERSION) << std::endl;
            std::cout << "[LINUX] GL Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
#endif
        }

#if !ONLY_OPENGL_CONTEXT
    private: // Variables
#else
    public: // Variables
#endif
#if WINDOWS
        HWND hwnd;
        HINSTANCE instance;
        MSG msg;
        HDC hdc;
        bool class_registered;
#elif LINUX
        Display* display;
        Window   window;
        Screen*  screen;
        int      screen_id;

        XVisualInfo* vi;
        GLXContext   context;

        XEvent ev;
#endif
        bool running;
        VectorUI size;

        // For calculating Framerate
        std::chrono::high_resolution_clock::time_point start_ticks;

        friend class Mouse;
    }; // Renderer

    // ----------------------------------------------------------- //

    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // --------------------- Mouse ------------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    class Mouse
    {
    public:
        // This class does not need to be initialized.
        // Users need to access it's functions directly
        // because all of the functions are static
        Mouse() = delete;

        // All of the possible mouse buttons
        enum class Button
        {
#if WINDOWS
            Left = VK_LBUTTON, Middle = VK_MBUTTON, Right = VK_RBUTTON,
            ScrollUp = 0x100, ScrollDown = 0x101 // This values i made up
#elif LINUX
            Left = 1, Middle = 2, Right = 3,
            ScrollUp = 4, ScrollDown = 5
#endif
        }; // Button

        // ----------------------------------------------------------- //

        // This function is returning if the button has been pressed
        // on both windows and linux
        static inline bool button_pressed(Renderer& renderer, Button button) noexcept
        {
#if WINDOWS 
            return button_pressed_windows(renderer, button);
#elif LINUX
            return button_pressed_linux(renderer, button);
#endif
            return false;
        }

        // This function is returning where the cursor is currently at
        // on both windows and linux
        static inline VectorI motion(Renderer& renderer) noexcept
        {
#if WINDOWS 
            return motion_windows(renderer);
#elif LINUX
            return motion_linux(renderer);
#endif
            return { 0, 0 };
        }

    private:
        // ----------------------------------------------------------- //
        // --------------------- WINDOWS ----------------------------- //
        // ----------------------------------------------------------- //
        // Check which button on the mouse was clicked
        static inline bool button_pressed_windows(Renderer& renderer, Button button) noexcept
        {
#if WINDOWS 
            if (button == Button::Left ||
                button == Button::Right ||
                button == Button::Middle)
            {
                return GetKeyState(int(button)) & 0x8000;
            }
            else // Scroll Buttons
            {
                int delta = static_cast<short>(HIWORD(renderer.msg.wParam));
                if (button == Button::ScrollDown)
                    return delta <= -120;
                else if (button == Button::ScrollUp)
                    return delta >= 120;
            }
#endif
            return false;
        }

        // Return the position of the mouse on the window
        static inline VectorI motion_windows(Renderer& renderer) noexcept
        {
#if WINDOWS
            POINT p;
            if (GetCursorPos(&p))
            {
                if (ScreenToClient(renderer.hwnd, &p))
                    return { p.x, p.y };
            }
#endif
            return { 0, 0 };
        }

        // ----------------------------------------------------------- //
        // --------------------- LINUX ------------------------------- //
        // ----------------------------------------------------------- //
        // Check which button on the mouse was clicked
        static inline bool button_pressed_linux(Renderer& renderer, Button button) noexcept
        {
#if LINUX
            auto& ev = renderer.ev;
            return (ev.type == ButtonPress) && (ev.xbutton.button == int(button));
#endif
            return false;
        }

        // Return the position of the mouse on the window
        static inline VectorI motion_linux(Renderer& renderer) noexcept
        {
#if LINUX
            // It's static because when the user is not 
            // the mouse then the MotionNotify event
            // is never called, thefore the vec would
            // return 0.
            // making it static forcing it return the 
            // last value that moved.
            static VectorI vec;

            // Clening all of the pending events
            // and extract only the mouse position
            while (XPending(renderer.display))
            {
                XNextEvent(renderer.display, &renderer.ev);

                if (renderer.ev.type == MotionNotify)
                {
                    vec.x = renderer.ev.xmotion.x;
                    vec.y = renderer.ev.xmotion.y;
                }

                XFlush(renderer.display);
            }

            return vec;
#endif
            return { 0, 0 };
        }

    }; // Mouse

    // ----------------------------------------------------------- //

    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // --------------------- Keyboard ---------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
    // ----------------------------------------------------------- //
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
#if WINDOWS
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
#elif LINUX
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
#endif
        }; // Key

        // ----------------------------------------------------------- //

        // This function return true if a key has indeed pressed
        // and return false if nothing was pressed
        static inline bool key_pressed(Key key) noexcept
        {
#if WINDOWS
            return key_pressed_windows(static_cast<uint32_t>(key));
#elif LINUX
            return key_pressed_linux(static_cast<uint32_t>(key));
#endif
            return false;
        }

        // This function is an overload to the function above
        // but checks a specific key that is not exists in the enum
        // If you want OS specific, you can just write -1 in one of the parameters.
        static inline bool key_pressed(uint32_t windows_key, uint32_t linux_key) noexcept
        {
#if WINDOWS
            return key_pressed_windows(windows_key);
#elif LINUX
            return key_pressed_linux(linux_key);
#endif
            return false;
        }


    private:
        // This function checks if a key pressed only on windows
        static inline bool key_pressed_windows(uint32_t key) noexcept
        {
#if WINDOWS
            return GetKeyState(key) & 0x8000;
#endif
            return false;
        }

        // This function checks if a key pressed only on linux
        static bool key_pressed_linux(uint32_t key) noexcept
        {
#if LINUX
            // Creating a display that is never going to 
            // be used other than fetching the keys
            // because i don't want the user to
            // be dependant on the renderer window.
            Display* dpy = XOpenDisplay(":0");

            // All of the logical keys that the user
            // can press at once.
            char keys_return[32];

            // Getting all of the keycodes
            XQueryKeymap(dpy, keys_return);
            KeyCode kc2 = XKeysymToKeycode(dpy, key);

            // Yes it's nasty, it's just checking if the correct
            // value was pressed, by checking it's bits correctly.
            bool is_pressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));

            // Closing the display, because it's finished fetching the keys.
            XCloseDisplay(dpy);

            return is_pressed;
#endif
            return false;
        }
    }; // Keyboard



} // gfx

#endif // GFX_HPP

// ----------------------------------------------------- //

// Fixed linux update to update automatically nonstop
// Fixed linux input lags
// Fixed windows update to update automatically nonstop
// Fixed support for MinGW
// Fixed windows lags after few seconds
// Replaced clock() with std::chrono
// NEED TO FIX: X11 Destroyed window bug.
// NEED TO ADD: Support for 64bit
