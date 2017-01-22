#include "TrayIcon.h"

#include "KeyboardState.h"
#include "KeyboardEvents.h"

TrayIcon::TrayIcon(KeyboardState * kb, KeyboardEvents * ke, QObject * parent):
    QSystemTrayIcon(parent)
{
    keyboardState = kb;
    keyboardEvents = ke;

    setCurrentIcon();

    connect(keyboardEvents, &KeyboardEvents::capslockChanged,
            this, &TrayIcon::keyEvent);
    connect(keyboardEvents, &KeyboardEvents::numlockChanged,
            this, &TrayIcon::keyEvent);
}

TrayIcon::~TrayIcon(){}

void TrayIcon::keyEvent(bool)
{
    setCurrentIcon();
}

void TrayIcon::changeIcon(const QString & ico)
{
    setIcon(QIcon(QPixmap(ico)));
    show();
}

void TrayIcon::setCurrentIcon()
{
    bool capsOn = keyboardState->getCapslock();
    bool numOn = keyboardState->getNumlock();

    if(!capsOn && !numOn) return hide();
    if(capsOn && !numOn) return changeIcon(":/trayicons/caps");
    if(!capsOn && numOn) return changeIcon(":/trayicons/num");
    if(capsOn && numOn) return changeIcon(":/trayicons/both");
}
