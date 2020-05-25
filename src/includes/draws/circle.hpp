///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
/////////////////////////////////////////////////////////// 
// This header contains a circle shape.                  //
///////////////////////////////////////////////////////////

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "../util/util.hpp"
#include "../util/vector.hpp"
#include "../util/color.hpp"

#include "transformation.hpp"

#include <stdexcept>

START_NAMESPACE

class Circle : public Transformation
{
public:
    // Position
    void set_position(const VectorI& pos);
    void set_position(int x, int y);
    VectorI get_position() const;

    // ------------------------------------------------------------ //

    // Radius
    void set_radius(float radius);
    float get_radius() const;

    // ------------------------------------------------------------ //

    // Color
    void set_color(const Color& color);
    Color get_color() const;

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
    float m_radius;
    Color m_color;
    bool m_fill;

    friend class GLFunctions;
}; // Circle

END_NAMESPACE

#endif // CIRCLE_HPP