#include "../../include/utils/color.hpp"

START_NAMESPACE

Color& Color::operator+(const Color& rhs)
{
    r = ((r + rhs.r) >= MAX_COLORS) ? MAX_COLORS : (r + rhs.r);
    g = ((g + rhs.r) >= MAX_COLORS) ? MAX_COLORS : (g + rhs.g);
    b = ((b + rhs.b) >= MAX_COLORS) ? MAX_COLORS : (b + rhs.b);
    a = ((a + rhs.a) >= MAX_COLORS) ? MAX_COLORS : (a + rhs.a);
    
    return *this;
}   

Color& Color::operator-(const Color& rhs) 
{
    r = ((r - rhs.r) <= 0) ? 0 : (r - rhs.r);
    g = ((g - rhs.r) <= 0) ? 0 : (g - rhs.g);
    b = ((b - rhs.b) <= 0) ? 0 : (b - rhs.b);
    a = ((a - rhs.a) <= 0) ? 0 : (a - rhs.a);

    return *this;
}

Color& Color::operator+=(const Color& rhs)
{
    r = ((r + rhs.r) >= MAX_COLORS) ? MAX_COLORS : (r + rhs.r);
    g = ((g + rhs.r) >= MAX_COLORS) ? MAX_COLORS : (g + rhs.g);
    b = ((b + rhs.b) >= MAX_COLORS) ? MAX_COLORS : (b + rhs.b);
    a = ((a + rhs.a) >= MAX_COLORS) ? MAX_COLORS : (a + rhs.a);
    
    return *this;
}   

Color& Color::operator-=(const Color& rhs)
{
    r = ((r - rhs.r) <= 0) ? 0 : (r - rhs.r);
    g = ((g - rhs.r) <= 0) ? 0 : (g - rhs.g);
    b = ((b - rhs.b) <= 0) ? 0 : (b - rhs.b);
    a = ((a - rhs.a) <= 0) ? 0 : (a - rhs.a);
    
    return *this;
}

Color& Color::operator=(const Color& color)
{
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;

    return *this;   
}

END_NAMESPACE