#include "../../includes/draws/shape.hpp"

START_NAMESPACE

void Shape::add_vertex(const std::initializer_list<Vertex>& vertexes)
{
    for(const auto& vertex : vertexes)
        m_vertex.push_back(vertex); 
}

void Shape::add_vertex(const Vertex& vertex) {
    m_vertex.push_back(vertex);
}

// ------------------------------------------------------------ //

const std::vector<Vertex>& Shape::get_vertexes() const {
    return m_vertex;
}

// ------------------------------------------------------------ //

void Shape::set_fill(bool fill){
    m_fill = fill;
}

bool Shape::get_fill() const { 
    return m_fill; 
}

// ------------------------------------------------------------ //

void Shape::set_connection(bool connect) { 
    m_connect = connect; 
}

bool Shape::get_connection() const { 
    return m_connect; 
}

END_NAMESPACE