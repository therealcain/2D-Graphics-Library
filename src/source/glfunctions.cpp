#include "../includes/glfunctions.hpp"

#ifdef _WIN32
#include <gl/GL.h> 
#include <gl/GLU.h> 
#elif __linux__
#include <GL/gl.h> 
#include <GL/glu.h>
#include <GL/glx.h>
#endif

START_NAMESPACE

GLFunctions::GLFunctions(Renderer& renderer)
    : m_renderer(renderer) {}

// ------------------------------------------------------------ //

void GLFunctions::clear() noexcept 
{
    // Clearing the buffers
    glClear(GL_COLOR_BUFFER_BIT);

    // This function expect a value between 0 to 1
    glClearColor(0.f, 0.f, 0.f, 1.f);
}

void GLFunctions::clear(const Color& color) noexcept
{
    // Clearing the buffers
    glClear(GL_COLOR_BUFFER_BIT);
    
    glClearColor(
        rgba_to_gl(color.r), 
        rgba_to_gl(color.g), 
        rgba_to_gl(color.b), 
        rgba_to_gl(color.a));
}

// ------------------------------------------------------------ //

void GLFunctions::start() noexcept
{    
    // Changing the viewport to screen size
    glViewport(0, 0, m_renderer.m_geometry.width, m_renderer.m_geometry.height);

    // Changing the scene to orthogonal projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_renderer.m_geometry.width, m_renderer.m_geometry.height, 0, -1, 1);

    // The matrix of all of the objects are going to be 
    // treated as the model view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// ------------------------------------------------------------ //

void GLFunctions::draw(const Rectangle& rect) noexcept
{
    glTranslatef(rect.m_translate.x, rect.m_translate.y, 0.f);
    glRotatef(rect.m_degree, 0.f, 0.f, 1.f);
    glScalef(rect.m_scale.x, rect.m_scale.y, 0.f);

    glColor4f(
        rgba_to_gl(rect.m_color.r),
        rgba_to_gl(rect.m_color.g),
        rgba_to_gl(rect.m_color.b),
        rgba_to_gl(rect.m_color.a)
    );

    // Draw the rectangle
    glBegin(rect.m_fill ? GL_QUADS : GL_LINE_LOOP);
    glVertex2f(rect.m_pos.x, rect.m_pos.y);
    glVertex2f(rect.m_pos.x + rect.m_size.width, rect.m_pos.y);
    glVertex2f(rect.m_pos.x + rect.m_size.width, rect.m_pos.y + rect.m_size.height);
    glVertex2f(rect.m_pos.x, rect.m_pos.y + rect.m_size.height);
    glEnd();

    // Reset all of the colors to allow
    // other sprites to be drawn with
    // another color
    glColor4f(1.f, 1.f, 1.f, 1.f);
}

void GLFunctions::draw(const Circle& circle)
{
    glTranslatef(circle.m_translate.x, circle.m_translate.y, 0.f);
    glRotatef(circle.m_degree, 0.f, 0.f, 1.f);
    glScalef(circle.m_scale.x, circle.m_scale.y, 0.f);

    glColor4f(
        rgba_to_gl(circle.m_color.r),
        rgba_to_gl(circle.m_color.g),
        rgba_to_gl(circle.m_color.b),
        rgba_to_gl(circle.m_color.a)
    );

    if (circle.m_fill)
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2i(circle.m_pos.x, circle.m_pos.y);
        for (int i = 0; i <= 20; i++)
        {
            VectorI temp;
            temp.x = circle.m_pos.x + (circle.m_radius * cosf(i * PI2 / 20.0));
            temp.y = circle.m_pos.y + (circle.m_radius * sinf(i * PI2 / 20.0));

            glVertex2i(temp.x, temp.y);
        }
        glEnd();
    }
    else
    {
        // Can be any other value
        constexpr int segments = 100;

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++)
        {
            float theta = PI2 * i / segments;

            VectorI temp;
            temp.x = static_cast<int>(circle.m_radius * cosf(theta));
            temp.y = static_cast<int>(circle.m_radius * sinf(theta));

            glVertex2i(circle.m_pos.x + temp.x, circle.m_pos.y + temp.y);
        }
        glEnd();
    }

    glColor4f(1.f, 1.f, 1.f, 1.f);
}

void GLFunctions::draw(const Shape& shape) noexcept
{
    glTranslatef(shape.m_translate.x, shape.m_translate.y, 0.f);
    glRotatef(shape.m_degree, 0.f, 0.f, 1.f);
    glScalef(shape.m_scale.x, shape.m_scale.y, 0.f);

    if(shape.m_connect)
    {
        if(shape.m_fill)
            glBegin(GL_POLYGON);
        else
            glBegin(GL_LINE_LOOP);
    }
    else
        glBegin(GL_LINE_STRIP);

    for(auto& s : shape.m_vertex)
    {
        glVertex2f(s.position.x, s.position.y);
        glColor4f(
            rgba_to_gl(s.color.r),
            rgba_to_gl(s.color.g),
            rgba_to_gl(s.color.b),
            rgba_to_gl(s.color.a)
        );
    }

    glEnd();
    
    glColor4f(1.f, 1.f, 1.f, 1.f);
}

void GLFunctions::draw(const Sprite& sprite) noexcept
{
    glTranslatef(sprite.m_translate.x, sprite.m_translate.y, 0.f);
    glRotatef(sprite.m_degree, 0.f, 0.f, 1.f);
    glScalef(sprite.m_scale.x, sprite.m_scale.y, 0.f);

    // Telling OpenGL that we are going to render
    // 2D Texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sprite.id);

    // Rendering all of the texture as a rectangle
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2i(sprite.m_position.x, sprite.m_position.y);
    glTexCoord2f(1, 0);
    glVertex2i(sprite.m_position.x + sprite.m_geometry.width, sprite.m_position.y);
    glTexCoord2f(1, 1);
    glVertex2i(sprite.m_position.x + sprite.m_geometry.width, sprite.m_position.y + sprite.m_geometry.height);
    glTexCoord2f(0, 1);
    glVertex2i(sprite.m_position.x, sprite.m_position.y + sprite.m_geometry.height);
    glEnd();

    // All of the other shapes that coming after this 
    // function are not going to be a texture
    // So OpenGL would be able to draw them correctly.
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

END_NAMESPACE