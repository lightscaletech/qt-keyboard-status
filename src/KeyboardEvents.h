#ifndef _KEYBOARD_EVENTS_H_
#define _KEYBOARD_EVENTS_H_

#include <QObject>

class KeyboardState;

class KeyboardEvents: public QObject
{
Q_OBJECT
public:
    KeyboardEvents(KeyboardState *, QObject * = NULL);
    ~KeyboardEvents();

signals:
    void capslockChanged(bool);
    void numlockChanged(bool);

public slots:
    void activated(int);

private:
    bool isKeyboard(const int);
    int findKeyboard();

    bool capsOn = false;
    bool numOn = false;
    KeyboardState * keyboardState;
    struct libevdev * dev = NULL;
};

#endif
