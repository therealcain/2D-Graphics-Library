///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This header contains a 2D vector structure to hold    //
// the x,y of any arithmetic type, with a few operator   //
// overloads.                                            //
///////////////////////////////////////////////////////////

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils.hpp"

#include <type_traits>
#include <iostream>

START_NAMESPACE

// Forward declaration
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
struct Vector;

// ------------------------------------------------------------ //

// Type Definitions
typedef Vector<signed int>   VectorI;
typedef Vector<unsigned int> VectorUI;
typedef Vector<float>        VectorF;

// ------------------------------------------------------------ //

// A vector of any possible arithmetic type
template<typename T, typename>
struct Vector
{
    T x;
    T y;

    // ------------------------------------------------------------ //

    constexpr Vector() 
        : x(0), y(0) {}
    ~Vector() = default;

    constexpr Vector(T X, T Y)
        : x(X), y(Y) {}

    template<typename U>
    constexpr Vector(const Vector<U>& vector)
        : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)) {}
    
    // ------------------------------------------------------------ //

    // Operator overloads
    template<typename U>
    Vector<T>& operator=(const Vector<U>& rhs) 
    {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    template<typename U>
    Vector<T>& operator+(const Vector<U>& rhs) 
    {
        x += static_cast<T>(rhs.x);
        y += static_cast<T>(rhs.y);
        
        return *this;
    }   

    template<typename U>
    Vector<T>& operator-(const Vector<U>& rhs)
    {
        x -= static_cast<T>(rhs.x);
        y -= static_cast<T>(rhs.y);
        
        return *this;
    }

    template<typename U>
    Vector<T>& operator*(const Vector<U>& rhs) 
    {
        x *= static_cast<T>(rhs.x);
        y *= static_cast<T>(rhs.y);
        
        return *this;
    }   

    template<typename U>
    Vector<T>& operator/(const Vector<U>& rhs)
    {
        x /= static_cast<T>(rhs.x);
        y /= static_cast<T>(rhs.y);
        
        return *this;
    }

    template<typename U>
    Vector<T>& operator+=(const Vector<U>& rhs) 
    {
        x += static_cast<T>(rhs.x);
        y += static_cast<T>(rhs.y);
        
        return *this;
    }   

    template<typename U>
    Vector<T>& operator-=(const Vector<U>& rhs)
    {
        x -= static_cast<T>(rhs.x);
        y -= static_cast<T>(rhs.y);
        
        return *this;
    }

    template<typename U>
    Vector<T>& operator*=(const Vector<U>& rhs) 
    {
        x *= static_cast<T>(rhs.x);
        y *= static_cast<T>(rhs.y);
        
        return *this;
    }   

    template<typename U>
    Vector<T>& operator/=(const Vector<U>& rhs)
    {
        x /= static_cast<T>(rhs.x);
        y /= static_cast<T>(rhs.y);
        
        return *this;
    }

    template<typename U>
    constexpr bool operator==(const Vector<U>& rhs) const {
        return (x == rhs.x && y == rhs.y);
    }

    template<typename U>
    constexpr bool operator!=(const Vector<U>& rhs) const {
        return !(x == rhs.x && y == rhs.y);
    }

    // ------------------------------------------------------------ //

    // Just to ease on printing the vector
    inline friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) 
    {
        os << "X = " << vector.x << " , Y = " << vector.y;
        return os;
    }
}; // Vector

END_NAMESPACE

#endif // VECTOR_HPP