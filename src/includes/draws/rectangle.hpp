///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This header contains a rectangle shape.               //
///////////////////////////////////////////////////////////

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "../util/util.hpp"
#include "../util/vector.hpp"
#include "../util/geometry.hpp"
#include "../util/color.hpp"

#include "transformation.hpp"

#include <stdexcept>

START_NAMESPACE

class Rectangle : public Transformation
{
public:
    // Position
    void set_position(const VectorI& pos);
    void set_position(int x, int y);
    const VectorI& get_position() const;

    // ------------------------------------------------------------ //

    // Size
    void set_size(const Geometry& size);
    void set_size(unsigned int x, unsigned int y);
    const Geometry& get_size() const;

    // ------------------------------------------------------------ //

    // Color
    void set_color(const Color& color);
    const Color& get_color() const;

    // ------------------------------------------------------------ //

    // Fill
    void set_fill(bool fill);
    bool get_fill() const;

    // ------------------------------------------------------------ //

#ifdef GFX_ACCESS_EVERYTHING
public:
#else
private:
#endif
    VectorI m_pos;
    Geometry m_size;
    Color m_color;
    bool m_fill;

    friend class GLFunctions;
}; // Rectangle

END_NAMESPACE

#endif // RECTANGLE_HPP