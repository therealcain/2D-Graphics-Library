#include "../src/include/gfx"

class Win 
    : public gfx::Renderer, 
             gfx::GLFunctions
{
private:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    gfx::Shape lines;

private:
    static int sign(int n)
    {
        if(n == 0)
            return 0;
        else if(n > 0)
            return 1;        
        return -1;
    }

    static void calc_edge_point(int x, int y, int& nx, int& ny)
    {
        int x_new = x;
        int y_new;

        if (y == 0) {
            y_new = 0;
            x_new = sign(x) * (WIDTH / 2);
        }
        else if (x == 0) {
            x_new = 0;
            y_new = sign(y) * (HEIGHT / 2);
        }
        else {
            y_new = sign(y) * (HEIGHT / 2);
            x_new = x * ((float)y_new / y);
        }

        nx = x_new;
        ny = y_new;
    }

public:
    Win() 
        : gfx::Renderer(WIDTH, HEIGHT),
          gfx::GLFunctions(get_renderer())
    {
        /* ON START */
        lines.add_vertex(gfx::Vertex(gfx::VectorI(WIDTH / 2, HEIGHT / 2), gfx::Color(255,255,164)));
        lines.add_vertex();
        lines.set_connection(false);
    }

    void on_update() override
    {
        clear();
        start();

        const gfx::VectorUI pos = gfx::VectorI(WIDTH / 2, HEIGHT / 2);
        gfx::VectorI mouse_pos = gfx::Mouse::motion(get_renderer());
        gfx::VectorI relative_pos = mouse_pos - pos;

        int x_new, y_new;
        calc_edge_point(relative_pos.x, relative_pos.y, x_new, y_new);

        gfx::VectorI next_pos(x_new, y_new);
        next_pos += pos;

        lines.update_vertex(gfx::Vertex(next_pos, gfx::Color(154,210,001)), 1);

        draw(lines);

        double framerate = get_framerate();
        set_title(std::to_string(framerate) + " ms");

        swap_buffers();
    }
};

int main() {   
    gfx::construct_windows<Win>();
}