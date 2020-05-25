#include "../../../include/windows/input/keyboard.hpp"

START_NAMESPACE

bool Keyboard::key_pressed(unsigned int key)
{
    return GetKeyState(key) & 0x8000;
}

bool Keyboard::key_pressed(Key key)
{
    return key_pressed(static_cast<unsigned int>(key));
}

END_NAMESPACE