#include "../../../includes/linux/input/mouse.hpp"

#include <X11/X.h>

START_NAMESPACE

bool Mouse::button_pressed(Renderer& renderer, Button button)
{
    return renderer.button_pressed == static_cast<unsigned int>(button);
}

VectorI Mouse::motion(Renderer& renderer)
{
    return renderer.mouse_pos;
}

END_NAMESPACE