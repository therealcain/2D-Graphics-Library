///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This header contains a simple structure to hold the   //
// width and height of a shape or a window.              //
///////////////////////////////////////////////////////////

#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "utils.hpp"
#include "vector.hpp"

#include <iostream>

START_NAMESPACE

struct Geometry 
{
    unsigned int width;
    unsigned int height;
    
    // ------------------------------------------------------------ //

    Geometry() = default;
    ~Geometry() = default;

    constexpr Geometry(unsigned int width_, unsigned int height_)
        : width(width_), height(height_) {}

    // Copy Constructor
    constexpr Geometry(const Geometry& geometry)
        : width(geometry.width), height(geometry.height) {}

    // ------------------------------------------------------------ //

    // Just to ease on printing the geometry
    inline friend std::ostream& operator<<(std::ostream& os, const Geometry& geometry) 
    {
        os << "Width = " << geometry.width << " , Height = " << geometry.height;
        return os;
    }

}; // Geometry

END_NAMESPACE

#endif // GEOMETRY_HPP