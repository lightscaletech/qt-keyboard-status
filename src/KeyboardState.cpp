#include "KeyboardState.h"
#include <X11/XKBlib.h>

KeyboardState::KeyboardState(QObject * parent):
    QObject(parent)
{
    display = XOpenDisplay((char *) 0);
}

KeyboardState::~KeyboardState()
{
    XCloseDisplay(display);
}

unsigned KeyboardState::getXkbIndicator()
{
    unsigned n;
    XkbGetIndicatorState(display, XkbUseCoreKbd, &n);
    return n;
}

bool KeyboardState::getCapslock()
{
    unsigned n = getXkbIndicator();
    return ((n & 1) > 0);
}

bool KeyboardState::getNumlock()
{
    unsigned n = getXkbIndicator();
    return ((n & 2) > 0);
}
