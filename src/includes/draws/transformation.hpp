///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////
// This header is going to be inherited from all of the  //
// shapes classes, because it can allow the user to      //
// manipulate shapes.                                    //
///////////////////////////////////////////////////////////

#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include "../util/util.hpp"
#include "../util/vector.hpp"
#include "../util/geometry.hpp"

START_NAMESPACE

class Transformation
{
public:
    Transformation();

    // ------------------------------------------------------------ //
    
    // Translating the translate matrix
    void set_translate(const VectorI& transform);
    void set_translate(int x, int y);
    const VectorI& get_translate() const;

    // ------------------------------------------------------------ //

    // Scaling the scale matrix
    void set_scale(const VectorF& scale);
    void set_scale(float x, float y);
    const VectorF& get_scale() const;

    // ------------------------------------------------------------ //

    // Rotate the rotation matrix
    void set_rotation(float degree);
    float get_rotation() const; 

    // ------------------------------------------------------------ //

#ifdef GFX_ACCESS_EVERYTHING
public:
#else
private:
#endif
    VectorI m_translate;
    VectorF m_scale;
    double m_degree;

    friend class GLFunctions;
};

END_NAMESPACE

#endif // TRANSFORMATION_HPP