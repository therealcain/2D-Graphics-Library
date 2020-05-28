#include "../src/include/gfx"
#include <vector>
#include <random>

class Win 
    : public gfx::Renderer, 
             gfx::GLFunctions
{
private:
    static constexpr int WIDTH      = 800;
    static constexpr int HEIGHT     = 600;
    static constexpr int RECT_WIDTH = 10;
    std::vector<gfx::Rectangle> rects;

    int random_number(int max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, max);

        return dist(mt);
    }

public:
    Win() 
        : gfx::Renderer(WIDTH, HEIGHT),
          gfx::GLFunctions(get_renderer())
    {
        for(int x = 0; x < WIDTH; x += RECT_WIDTH + 2)
        {
            rects.push_back({});
            auto& rref = rects[rects.size() - 1];
            
            int randnum = random_number(HEIGHT);

            rref.set_position(x, 0);
            rref.set_size(RECT_WIDTH, randnum);
            rref.set_color(gfx::Color(200, 100, 0));
            rref.set_fill(true);
        }
    }

    void on_update() override
    {
        clear();
        start();

        for(auto& r : rects)
            draw(r);

        // Bubble sort algorithm
        static unsigned int i = 0;
        while (i < rects.size() - 1)
        {
            for (unsigned int j = 0; j < rects.size() - i - 1; j++)
            {
                std::string title = "Iteration I: " + std::to_string(i) + 
                                    "  J: "         + std::to_string(j);
                set_title(title);

                rects[j].set_color(gfx::Color(200, 200, 200));

                if (rects[j].get_size().height > rects[j + 1].get_size().height)
                {
                    auto temp = rects[j].get_size();

                    rects[j].set_size(rects[j + 1].get_size());
                    rects[j + 1].set_size(temp);
                }

                clear();
                start();
                for(auto& r : rects)
                        draw(r);
                swap_buffers();

                // Back to default color
                rects[j].set_color(gfx::Color(200, 100, 0));
            }

            i++;
        }

        swap_buffers();
    }
};

int main() {   
    gfx::construct_windows<Win>();
}