#include "../../../includes/windows/input/mouse.hpp"

START_NAMESPACE

bool Mouse::button_pressed(Renderer& renderer, Button button)
{
    if (button == Button::Left ||
        button == Button::Right ||
        button == Button::Middle)
    {
        return GetKeyState(int(button)) & 0x8000;
    }
    else // Scroll Buttons
    {
        int delta = static_cast<short>(HIWORD(renderer.msg.wParam));
        if (button == Button::ScrollDown)
            return delta <= -120;
        else if (button == Button::ScrollUp)
            return delta >= 120;
    }

    return false;
}

VectorI Mouse::motion(Renderer& renderer)
{
    POINT p;
    if (GetCursorPos(&p))
    {
        if (ScreenToClient(renderer.hwnd, &p))
            return { p.x, p.y };
    }

    return { 0, 0 };
}

END_NAMESPACE