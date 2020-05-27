///////////////////////////////////////////////////////////
// Copyright 2020, Eviatar Mor, All rights reserved.     //
// https://therealcain.github.io/website/                //
///////////////////////////////////////////////////////////

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "../utils/utils.hpp"
#include "../utils/vector.hpp"
#include "../utils/color.hpp"

#include "transformation.hpp"

#include <vector>

START_NAMESPACE

// Forward Declaration
class Renderer;

class Sprite : public Transformation
{
public:
    // Create
    Sprite() = default;
    Sprite(const std::string& path, const VectorI& position);
    Sprite(const std::string& path, int x, int y);
    Sprite(const std::string& path, const Geometry& geometry, const VectorI& position);
    Sprite(const std::string& path, unsigned int width, unsigned int height, int x, int y);
    ~Sprite();

    // ------------------------------------------------------------ //

    // Create
    void create(const std::string& path, const VectorI& position);
    void create(const std::string& path, int x, int y);
    void create(const std::string& path, const Geometry& geometry, const VectorI& position);
    void create(const std::string& path, unsigned int width, unsigned int height, int x, int y);

    // ------------------------------------------------------------ //

    // Size
    void set_size(const Geometry& size);
    void set_size(unsigned int x, unsigned int y);
    const Geometry& get_size() const;
    const Geometry& get_texture_size() const;

    // ------------------------------------------------------------ //

    // Position
    void set_position(const VectorI& pos);
    void set_position(int x, int y);
    const VectorI& get_position() const;

    // ------------------------------------------------------------ //

    // Pixels
    void set_pixel(const VectorUI& position, Color& color);
    void set_pixel(const VectorUI& position, Color&& color);
    void set_pixel(unsigned int x, unsigned int y, Color& color);
    void set_pixel(unsigned int x, unsigned int y, Color&& color);

    Color get_pixel(const Renderer& renderer, const VectorUI& position);
    Color get_pixel(const Renderer& renderer, unsigned int x, unsigned int y);

    // ------------------------------------------------------------ //

#ifdef GFX_ACCESS_EVERYTHING
public:
#else
private:
#endif
    unsigned int id;
    VectorI m_position;
    Geometry m_geometry;
    Geometry original_geometry;
    
    friend class GLFunctions;
}; // Sprite

END_NAMESPACE

#endif // SPRITE_HPP