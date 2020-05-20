#include "gfx.hpp"

int main()
{
    gfx::Renderer window(gfx::VectorUI(800, 600));
    window.set_title("window!!");

    gfx::Texture tuxTex = window.load_texture("tux.png");

    while (window.is_running())
    {
        window.clear();

        auto pos = gfx::Mouse::motion(window);

        window.draw_texture(tuxTex, gfx::VectorUI(pos.x, pos.y), { 150, 150 });

        window.show();
    }
}