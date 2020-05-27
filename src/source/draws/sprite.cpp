#include "../../include/draws/sprite.hpp"

#ifdef _WIN32
#include "../../include/windows/renderer.hpp"
#include <gl/gl.h>
#elif __linux__
#include "../../include/linux/renderer.hpp"
#include <GL/gl.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "../../external_libs/stb_image.h"

#include <memory>

START_NAMESPACE

// Create
Sprite::Sprite(const std::string& path, const VectorI& position) {
    create(path, Geometry(10, 10), position);
}

Sprite::Sprite(const std::string& path, int x, int y) {
    create(path, Geometry(10, 10), VectorI(x, y));
}

Sprite::Sprite(const std::string& path, const Geometry& geometry, const VectorI& position) {
    create(path, geometry, position);
}

Sprite::Sprite(const std::string& path, unsigned int width, unsigned int height, int x, int y) {
    create(path, Geometry(width, height), VectorI(x, y));
}

Sprite::~Sprite() {
    glDeleteTextures(1, &id);
}

// ------------------------------------------------------------ //

// Create
void Sprite::create(const std::string& path, const VectorI& position) {
    create(path, Geometry(10, 10), position);
}

void Sprite::create(const std::string& path, int x, int y) {
    create(path, Geometry(10, 10), VectorI(x, y));
}

void Sprite::create(const std::string& path, const Geometry& geometry, const VectorI& position) {
    create(path, geometry.width, geometry.height, position.x, position.y);
}

void Sprite::create(const std::string& path, unsigned int width, unsigned int height, int x, int y) 
{
    unsigned char* data;
    int nr_channels;

    int width_ = 0;
    int height_ = 0;

    // Fetching all of the data from the image
    data = stbi_load(path.c_str(), &width_, &height_, &nr_channels, 0);

    if (data)
    {
        // Creating a texture based on this data
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, 4, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Cleaning data because the data already passed 
        // to opengl
        stbi_image_free(data);


        m_geometry = {width, height};
        m_position = {x, y};
        original_geometry = {static_cast<unsigned int>(width_), static_cast<unsigned int>(height_)};
    }
    else
        throw std::logic_error("Failed to load texture!");
}

// ------------------------------------------------------------ //

// Size
void Sprite::set_size(const Geometry& size) {
    m_geometry = size;
}

void Sprite::set_size(unsigned int x, unsigned int y) {
    m_geometry = {x, y};
}

const Geometry& Sprite::get_size() const {
    return m_geometry;
}

const Geometry& Sprite::get_texture_size() const {
    return original_geometry;
}

// ------------------------------------------------------------ //

// Position
void Sprite::set_position(const VectorI& pos) {
    m_position = pos;
}

void Sprite::set_position(int x, int y) {
    m_position = {x, y};
}

const VectorI& Sprite::get_position() const {
    return m_position;
}

// ------------------------------------------------------------ //

void Sprite::set_pixel(const VectorUI& pos, Color& color) {
    set_pixel(pos.x, pos.y, std::move(color));
}   

void Sprite::set_pixel(const VectorUI& pos, Color&& color) {
    set_pixel(pos.x, pos.y, std::move(color));
}

void Sprite::set_pixel(unsigned int x, unsigned int y, Color& color) {
    set_pixel(x, y, std::move(color));
}

void Sprite::set_pixel(unsigned int x, unsigned int y, Color&& color) 
{
    GLfloat colors[4] = { 
        rgba_to_gl(color.r), 
        rgba_to_gl(color.g), 
        rgba_to_gl(color.b), 
        rgba_to_gl(color.a) 
    };

    glBindTexture(GL_TEXTURE_2D, id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, 1, 1, GL_RGBA, GL_FLOAT, &colors);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Color Sprite::get_pixel(const Renderer& renderer, const VectorUI& pos) {
    return get_pixel(renderer, pos.x, pos.y);
}

Color Sprite::get_pixel(const Renderer& renderer, unsigned int x, unsigned int y) {
    GLfloat colors[4];
    glReadPixels(
        x, renderer.get_geometry().height - y - 1, 
        1, 1,
        GL_RGBA,
        GL_FLOAT,
        &colors);
    
    return {gl_to_rgba(colors[0]), gl_to_rgba(colors[1]), gl_to_rgba(colors[2]), gl_to_rgba(colors[3])};
}

END_NAMESPACE