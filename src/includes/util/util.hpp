///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This header is probably going to be used from all of  //
// the other headers, because it's contains essential    //
// information of the namespaces.                        //
///////////////////////////////////////////////////////////

#ifndef UTIL_HPP
#define UTIL_HPP

#include <cmath>
#include <iostream>

#define START_NAMESPACE namespace gfx {
#define END_NAMESPACE }

#ifdef __GNUC__
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
// This is inline because i didn't want to create
// implementation file for single function
inline void abort_null(void* ptr, const std::string& str)
{
    if(ptr == nullptr)
    {
        std::cout << str << std::endl;
        abort();
    }
}

// Map color to opengl color format
constexpr float rgba_to_gl(unsigned int color) {
    return color / 255.f;
}

END_NAMESPACE

#endif // UTIL_HPP