///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This header contains a very simple struct that is     //
// going to hold all of the vertices of a shape.         //
///////////////////////////////////////////////////////////

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "utils.hpp"
#include "color.hpp"
#include "vector.hpp"

START_NAMESPACE

struct Vertex
{
    VectorI position;
    Color color;

    Vertex() = default;
    Vertex(const VectorI& position_, const Color& color_)
        :  position(position_), color(color_) {}
}; // Vertex

END_NAMESPACE

#endif // VERTEX_HPP