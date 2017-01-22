#ifndef _KEYBOARD_STATE_H_
#define _KEYBOARD_STATE_H_

#include <QObject>

struct _XDisplay;
typedef struct _XDisplay Display;

class KeyboardState: public QObject
{
public:
    KeyboardState(QObject * = NULL);
    ~KeyboardState();

    bool getCapslock();
    bool getNumlock();
private:
    unsigned getXkbIndicator();
    Display * display;
};

#endif
