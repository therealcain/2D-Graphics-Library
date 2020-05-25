#include "../../../include/linux/input/keyboard.hpp"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

START_NAMESPACE

bool Keyboard::key_pressed(Key key)
{
    return key_pressed(static_cast<unsigned int>(key));
}

bool Keyboard::key_pressed(unsigned int key)
{
    // Creating a display that is never going to 
    // be used other than fetching the keys
    // because i don't want the user to
    // be dependant on the renderer window.
    Display* dpy = XOpenDisplay(":0");

    // All of the logical keys that the user
    // can press at once.
    char keys_return[32];

    // Getting all of the keycodes
    XQueryKeymap(dpy, keys_return);
    KeyCode kc2 = XKeysymToKeycode(dpy, key);

    // Yes it's nasty, it's just checking if the correct
    // value was pressed, by checking it's bits correctly.
    bool is_pressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));

    // Closing the display, because it's finished fetching the keys.
    XCloseDisplay(dpy);

    return is_pressed;
}

END_NAMESPACE