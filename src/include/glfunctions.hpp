///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This header file is handling few OpenGL functions to  //
// allow the user to draw stuff on screen, without the   //
// need to take care of the viewport, clearing buffers   //
// etc...                                                //
///////////////////////////////////////////////////////////

#ifndef GLFUNCTIONS_HPP
#define GLFUNCTIONS_HPP

#include "utils/utils.hpp"
#include "utils/color.hpp"
#include "draws/rectangle.hpp"
#include "draws/circle.hpp"
#include "draws/shape.hpp"
#include "draws/sprite.hpp"

#ifdef _WIN32
#include "windows/renderer.hpp"
#elif  __linux__
#include "linux/renderer.hpp"
#endif

START_NAMESPACE

class GLFunctions
{
public:
    GLFunctions(Renderer& renderer);

    // ------------------------------------------------------------ //

    // Clearing the screen with black color
    void clear() noexcept;
    // Clearing the screen with a specific color
    void clear(const Color& color) noexcept;

    // ------------------------------------------------------------ //

    // This is starting the screen with a 
    // scene to be drawn to
    void start() noexcept;

    // ------------------------------------------------------------ //

    // Drawing a rectangle
    void draw(const Rectangle& rectangle) noexcept;
    void draw(const Circle& circle);
    void draw(const Shape& shape) noexcept;
    void draw(const Sprite& sprite) noexcept;

    // ------------------------------------------------------------ //

private:
    Renderer& m_renderer;
}; // GLFunctions

END_NAMESPACE

#endif // GLFUNCTIONS_HPP