///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This header includes all of the essential headers for //
// this library, also it defines few macros for the      //
// user.                                                 //
///////////////////////////////////////////////////////////

#ifndef GFX_HPP
#define GFX_HPP

// Link all of the windows libraries
#ifdef _WIN32
#include "windows/input/keyboard.hpp"
#include "windows/input/mouse.hpp"
#include "windows/renderer.hpp"
// link to Visual Studio opengl and glu
#ifdef _MSC_VER
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#endif // _MSC_VER

// ------------------------------------------------------------ //

// Link all of the linux libraries
#elif __linux__ // #endif _WIN32
#include "linux/input/keyboard.hpp"
#include "linux/input/mouse.hpp"
#include "linux/renderer.hpp"
#endif // __linux__

// ------------------------------------------------------------ //

#include "glfunctions.hpp"
#include "construction.hpp"

#include "utils/vector.hpp"
#include "utils/geometry.hpp"
#include "utils/color.hpp"
#include "utils/vertex.hpp"

#include "draws/rectangle.hpp"
#include "draws/circle.hpp"
#include "draws/shape.hpp"
#include "draws/sprite.hpp"


#endif // GFX_HPP