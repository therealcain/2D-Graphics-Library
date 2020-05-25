#include "../../includes/draws/circle.hpp"

START_NAMESPACE

void Circle::set_position(const VectorI& pos) { 
    m_pos = pos;    
}

void Circle::set_position(int x, int y) { 
    m_pos = {x, y}; 
}

VectorI Circle::get_position() const { 
    return m_pos;   
}

// ------------------------------------------------------------ //

// Radius
void Circle::set_radius(float radius) { 
    m_radius = radius; 
}

float Circle::get_radius() const { 
    return m_radius;   
}

// ------------------------------------------------------------ //

// Color
void Circle::set_color(const Color& color) { 
    m_color = color; 
}

Color Circle::get_color() const { 
    return m_color;  
}

// ------------------------------------------------------------ //

// Fill
void Circle::set_fill(bool fill) { 
    m_fill = fill; 
}

bool Circle::get_fill() const { 
    return m_fill; 
}

END_NAMESPACE