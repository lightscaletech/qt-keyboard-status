#include "KeyboardEvents.h"

#include <QDir>
#include <QString>
#include <QStringList>
#include <QSocketNotifier>
#include <QDebug>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <libevdev-1.0/libevdev/libevdev.h>

#include "KeyboardState.h"

KeyboardEvents::KeyboardEvents(KeyboardState * kState, QObject * parent):
    QObject(parent)
{
    keyboardState = kState;
    capsOn = keyboardState->getCapslock();
    numOn = keyboardState->getNumlock();
    int fd = findKeyboard();
    if(!fd) return;
    libevdev_new_from_fd(fd, &dev);
    QSocketNotifier * sn =  new QSocketNotifier(fd, QSocketNotifier::Read, this);
    connect(sn, &QSocketNotifier::activated,
            this, &KeyboardEvents::activated);
}

KeyboardEvents::~KeyboardEvents()
{
    if(dev) libevdev_free(dev);
}

void KeyboardEvents::activated(int)
{
    struct input_event ev;
    int rc = 0;
    do
    {
        bool res;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        if(rc == -EAGAIN) break;
        if(ev.type == EV_KEY && ev.value == 0 &&
           (ev.code == KEY_CAPSLOCK || ev.code == KEY_NUMLOCK))
        {
            if(capsOn != (res = keyboardState->getCapslock()))
            {
                capsOn = res;
                capslockChanged(res);
            }
            if(numOn != (res = keyboardState->getNumlock()))
            {
                numOn = res;
                numlockChanged(res);
            }
        }
    } while (rc == 0 || rc == 1);
}

bool KeyboardEvents::isKeyboard(const int fd)
{
    struct libevdev *dev = NULL;
    libevdev_new_from_fd(fd, &dev);

    if(libevdev_has_event_type(dev, EV_KEY) &&
       libevdev_has_event_code(dev, EV_KEY, KEY_ENTER) &&
       libevdev_has_event_code(dev, EV_KEY, KEY_BACKSPACE) &&
       libevdev_has_event_code(dev, EV_KEY, KEY_A))
    {
        libevdev_free(dev);
        return true;
    }

    libevdev_free(dev);
    return false;
}

int KeyboardEvents::findKeyboard()
{
    QString base("/dev/input/");
    QDir dir(base);
    QStringList filters;
    filters << "event*";
    QStringList files = dir.entryList(filters, QDir::System | QDir::Files,
                                      QDir::Name);
    int file = 0;
    QString path;
    for(auto it = files.begin(); it != files.end(); it++)
    {
        path = base + *it;
        file = open(path.toLatin1().data(),
                    O_NONBLOCK | O_RDONLY, 0);
        if(isKeyboard(file)) return file;
        close(file);
    }
    return -1;
}
