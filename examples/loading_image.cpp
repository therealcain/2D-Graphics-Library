#include "../src/include/gfx"
#include <string>

class Win 
    : public gfx::Renderer, 
             gfx::GLFunctions
{
private:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    gfx::Sprite spr;

public:
    Win() 
        : gfx::Renderer(WIDTH, HEIGHT),
          gfx::GLFunctions(get_renderer())
    {
        /* ON START */
        spr.create("cubes.png", 100, 100, WIDTH / 2, HEIGHT / 2);
    }

    void on_update() override
    {
        clear();
        start();

        draw(spr);

        auto mousepos = gfx::Mouse::motion(get_renderer());
        std::cout << spr.get_pixel(get_renderer(), mousepos) << std::endl;;

        if(gfx::Mouse::button_pressed(get_renderer(), gfx::Mouse::Button::Left))
        {
            for(size_t y = 0; y < spr.get_texture_size().height; y++)
            {
                for(size_t x = 0; x < spr.get_texture_size().width; x++)
                    spr.set_pixel(x, y, gfx::Color(100, 0, 255));
            }
        }

        double framerate = get_framerate();
        set_title(std::to_string(framerate) + " ms");

        swap_buffers();
    }
};

int main() {   
    gfx::construct_windows<Win>();
}