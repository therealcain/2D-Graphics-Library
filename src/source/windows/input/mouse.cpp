#include "../../../include/windows/input/mouse.hpp"

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
    static POINT last_p;
    CURSORINFO cursor_info { 0 };
    cursor_info.cbSize = sizeof(cursor_info);

    // Extracting the cursor position
    if(GetCursorInfo(&cursor_info))
    {
        // Extracting the window position
        RECT rect;
        GetWindowRect(renderer.m_hwnd, &rect);

        // Checks if the mouse is on the screen
        // ( I KNOW ITS NASTY ), but other functions were not handling from
        // the top position
        if(cursor_info.ptScreenPos.x       <= rect.right                &&
           rect.left                       <= cursor_info.ptScreenPos.x &&
           cursor_info.ptScreenPos.y       <= rect.bottom               &&
           rect.top                        <= cursor_info.ptScreenPos.y)
           {
               // updating the last position, so when the mouse leave the window
               // it would return the last position it was
               last_p = { cursor_info.ptScreenPos.x - rect.left, cursor_info.ptScreenPos.y - rect.top };
               
               return { last_p.x, last_p.y };
           }
    }

    return {last_p.x, last_p.y};
}

END_NAMESPACE