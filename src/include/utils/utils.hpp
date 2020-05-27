///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This header is probably going to be used from all of  //
// the other headers, because it's contains essential    //
// information of the namespaces.                        //
///////////////////////////////////////////////////////////

#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <iostream>

#define START_NAMESPACE namespace gfx {
#define END_NAMESPACE }

// C++11 does not support [[maybe_unused]]
#if defined(_GNUC__) || defined(__clang__) || defined(__MINGW32__)
#define GFX_UNUSED gnu::unused
#else
#define GFX_UNUSED
#endif

START_NAMESPACE

#ifdef M_PI
constexpr float PI = M_PI;
#else
constexpr float PI = 3.14159265358979323846;
#endif
constexpr float PI2 = PI * 2;

// Abort if pointer is null
extern void abort_null(void* ptr, const std::string& str);

// Map color to opengl color format
constexpr float rgba_to_gl(unsigned int color) {
    return color / 255.f;
}
// Map color from GL format to sRGBA color format
constexpr unsigned int gl_to_rgba(float color) {
    return static_cast<unsigned int>(color * 255);
}

END_NAMESPACE

#endif // UTILS_HPP