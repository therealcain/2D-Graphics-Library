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

#include "../utils/utils.hpp"
#include "../utils/vector.hpp"
#include "../utils/color.hpp"
#include "../utils/vertex.hpp"

#include "transformation.hpp"

#include <vector>
#include <algorithm>
#include <initializer_list>

START_NAMESPACE

class Shape : public Transformation
{
public:
    // Add Vertices
    void add_vertex(const std::initializer_list<Vertex>& vertices);
    void add_vertex(const Vertex& vertex);
    void add_vertex();

    // ------------------------------------------------------------ //

    // Update Vertices
    void update_vertex(const Vertex& vertex, size_t position);

    // ------------------------------------------------------------ //

    // Get vertexes
    const std::vector<Vertex>& get_vertices() const;

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