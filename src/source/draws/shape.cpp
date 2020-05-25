#include "../../include/draws/shape.hpp"

START_NAMESPACE

void Shape::add_vertex(const std::initializer_list<Vertex>& vertices)
{
    for(const auto& vertex : vertices)
        m_vertex.push_back(vertex); 
}

void Shape::add_vertex(const Vertex& vertex) {
    m_vertex.push_back(vertex);
}

void Shape::add_vertex() {
    m_vertex.push_back(gfx::Vertex());
}

// ------------------------------------------------------------ //

void Shape::update_vertex(const Vertex& vertex, size_t position)
{
    if(position >= m_vertex.size())
        throw std::logic_error("Vertex position is incorrect!");

    m_vertex[position] = vertex;
}

// ------------------------------------------------------------ //

const std::vector<Vertex>& Shape::get_vertices() const {
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