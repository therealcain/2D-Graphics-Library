#include "../../includes/draws/rectangle.hpp"

START_NAMESPACE

// Position
void Rectangle::set_position(const VectorI& pos) { 
    m_pos = pos;    
}

void Rectangle::set_position(int x, int y) { 
    m_pos = {x, y}; 
}

const VectorI& Rectangle::get_position() const { 
    return m_pos;   
}

// ------------------------------------------------------------ //

// Size
void Rectangle::set_size(const Geometry& size) { 
    m_size = size;  
}

void Rectangle::set_size(unsigned int x, unsigned int y) { 
    m_size = {x,y}; 
}

const Geometry& Rectangle::get_size() const { 
    return m_size;  
}

// ------------------------------------------------------------ //

// Color
void Rectangle::set_color(const Color& color) { 
    m_color = color; 
}

const Color& Rectangle::get_color() const { 
    return m_color;  
}

// ------------------------------------------------------------ //

// Fill
void Rectangle::set_fill(bool fill) { 
    m_fill = fill; 
}

bool Rectangle::get_fill() const { 
    return m_fill; 
}

END_NAMESPACE