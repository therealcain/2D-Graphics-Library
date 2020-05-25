#include "src/includes/gfx"

class Win 
    : public gfx::Renderer, 
             gfx::GLFunctions
{
private:
    gfx::Sprite sprite;

public:
    Win() 
        : gfx::Renderer(500, 500),
          gfx::GLFunctions(get_renderer())
    {
        /* ON START */
        sprite.create("image.png", gfx::Geometry(100, 100), gfx::VectorI(30, 30));
    }

    void on_update() override
    {
        clear();
        start();

        if(gfx::Mouse::button_pressed(get_renderer(), gfx::Mouse::Button::ScrollUp))
            sprite.set_scale(sprite.get_scale().x + 0.1, sprite.get_scale().y + 0.1);
        else if(gfx::Mouse::button_pressed(get_renderer(), gfx::Mouse::Button::ScrollDown))
            sprite.set_scale(sprite.get_scale().x - 0.1, sprite.get_scale().y - 0.1);

        std::cout << sprite.get_scale() << std::endl;

        draw(sprite);

        // gfx::VectorUI mouse_pos = gfx::Mouse::motion(get_renderer());
        // sprite.set_position(mouse_pos);

        double framerate = get_framerate();
        set_title(std::to_string(framerate) + " ms");

        swap_buffers();
    }
};

GFX_MAKE_MAIN(Win)