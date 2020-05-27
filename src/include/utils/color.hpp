///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This header contains the color sRGBA, with a few      //
// operator overloads.                                   //
///////////////////////////////////////////////////////////

#ifndef COLOR_HPP
#define COLOR_HPP

#include "utils.hpp"

#include <iostream>

START_NAMESPACE

struct Color
{
private:
    static constexpr auto MAX_COLORS = 255;

    // ------------------------------------------------------------ //

public:
    unsigned int r; // Red
    unsigned int g; // Green
    unsigned int b; // Blue
    unsigned int a; // Alpha aka Opacity

    // ------------------------------------------------------------ //

    // Constructors
    constexpr Color()
        : r(0), g(0), b(0), a(MAX_COLORS) {}
    constexpr Color(unsigned int red, unsigned int green, unsigned int blue)
        : r(red   >= MAX_COLORS ? MAX_COLORS : red), 
          g(green >= MAX_COLORS ? MAX_COLORS : green), 
          b(blue  >= MAX_COLORS ? MAX_COLORS : blue), 
          a(MAX_COLORS) {}
    constexpr Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
        : r(red   >= MAX_COLORS ? MAX_COLORS : red), 
          g(green >= MAX_COLORS ? MAX_COLORS : green), 
          b(blue  >= MAX_COLORS ? MAX_COLORS : blue), 
          a(alpha >= MAX_COLORS ? MAX_COLORS : alpha) {}

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    constexpr Color(T red, T green, T blue, T alpha)
        : r(static_cast<unsigned int>(red   >= MAX_COLORS ? MAX_COLORS : red)), 
          g(static_cast<unsigned int>(green >= MAX_COLORS ? MAX_COLORS : green)), 
          b(static_cast<unsigned int>(blue  >= MAX_COLORS ? MAX_COLORS : blue)), 
          a(static_cast<unsigned int>(alpha >= MAX_COLORS ? MAX_COLORS : alpha)) {}

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    constexpr Color(T red, T green, T blue)
        : r(static_cast<unsigned int>(red   >= MAX_COLORS ? MAX_COLORS : red)), 
          g(static_cast<unsigned int>(green >= MAX_COLORS ? MAX_COLORS : green)), 
          b(static_cast<unsigned int>(blue  >= MAX_COLORS ? MAX_COLORS : blue)) {}


    // Copy Constructor
    constexpr Color(const Color& color)
        : r(color.r), g(color.g), b(color.b), a(color.a) {}

    // Destructor
    ~Color() = default;

    // ------------------------------------------------------------ //

    // Operator overloads
    Color& operator+(const Color& rhs);
    Color& operator-(const Color& rhs);
    Color& operator+=(const Color& rhs);
    Color& operator-=(const Color& rhs);
    Color& operator=(const Color& color);

    constexpr bool operator==(const Color& rhs) const {
        return (r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);
    }

    constexpr bool operator!=(const Color& rhs) const {
        return !(r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);
    }

    // ------------------------------------------------------------ //

    // Just to ease on printing the color
    inline friend std::ostream& operator<<(std::ostream& os, const Color& color) 
    {
        os << "R = " << color.r << " , G = " << color.g << " , B = " << color.b << " , A = " << color.a;
        return os;
    }
};

END_NAMESPACE

#endif // COLOR_HPP