///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
/////////////////////////////////////////////////////////// 
// This header contains the user shapes, you specify few //
// vertices and build up a polygon, or connected / or    //
// not connected lines.                                  //
/////////////////////////////////////////////////////////// 

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "../util/util.hpp"
#include "../util/vector.hpp"
#include "../util/color.hpp"
#include "../util/vertex.hpp"

#include "transformation.hpp"

#include <vector>
#include <algorithm>
#include <initializer_list>

START_NAMESPACE

class Shape : public Transformation
{
public:
    // Add vertexes
    void add_vertex(const std::initializer_list<Vertex>& vertexes);
    void add_vertex(const Vertex& vertex);

    // ------------------------------------------------------------ //

    // Get vertexes
    const std::vector<Vertex>& get_vertexes() const;

    // ------------------------------------------------------------ //

    // Fill
    void set_fill(bool fill);
    bool get_fill() const;

    // ------------------------------------------------------------ //

    // Connection
    void set_connection(bool connect);
    bool get_connection() const;

    // ------------------------------------------------------------ //

#ifdef GFX_ACCESS_EVERYTHING
public:
#else
private:
#endif
    std::vector<Vertex> m_vertex;
    bool m_fill;
    bool m_connect;

    friend class GLFunctions;
}; // Shape

END_NAMESPACE

#endif // SHAPE_HPP