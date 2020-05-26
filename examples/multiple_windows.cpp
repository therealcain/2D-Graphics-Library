#include "../src/include/gfx"

class WinFirst
    : public gfx::Renderer, 
             gfx::GLFunctions
{
private:
    static constexpr int WIDTH = 400;
    static constexpr int HEIGHT = 400;
    gfx::Circle circle;

public:
    WinFirst() 
        : gfx::Renderer(WIDTH, HEIGHT),
          gfx::GLFunctions(get_renderer())
    {
        /* ON START */
        set_title("Hello from Window 1!");
        circle.set_color(gfx::Color(100, 140, 210));
        circle.set_radius(50);
        circle.set_fill(true);
    }

    void on_update() override
    {
        if(is_focused())
        {   
            clear();
            start();

            draw(circle);
            
            auto pos = gfx::Mouse::motion(get_renderer());
            circle.set_position(pos);

            if(gfx::Keyboard::key_pressed(gfx::Keyboard::Key::A))
                std::cout << "Window 1: A!!" << std::endl;

            swap_buffers();
        }
    }
};

class WinSecond
    : public gfx::Renderer, 
             gfx::GLFunctions
{
private:
    static constexpr int WIDTH = 400;
    static constexpr int HEIGHT = 400;
    gfx::Rectangle rect;

public:
    WinSecond() 
        : gfx::Renderer(WIDTH, HEIGHT),
          gfx::GLFunctions(get_renderer())
    {
        /* ON START */
        set_title("Hello from Window 2!");

        rect.set_size(100, 100);
        rect.set_color(gfx::Color(240, 180, 2));
        rect.set_fill(true);
    }

    void on_update() override
    {
        if(is_focused())
        {   
            clear();
            start();
            draw(rect);

            auto pos = gfx::Mouse::motion(get_renderer());
            rect.set_position(pos);

            if(gfx::Keyboard::key_pressed(gfx::Keyboard::Key::A))
                std::cout << "Window 2: A!!" << std::endl;

            swap_buffers();
        }
    }
};

int main() {   
    gfx::construct_windows<WinFirst, WinSecond>();
}