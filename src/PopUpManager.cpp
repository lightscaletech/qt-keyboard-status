#include "PopUpManager.h"

#include "KeyboardEvents.h"
#include "WinPopupNotification.h"

PopUpManager::PopUpManager(KeyboardEvents * ke, QObject * parent):
    QObject(parent),
    popup(NULL)
{
    keyboardEvents = ke;

    connect(ke, &KeyboardEvents::capslockChanged,
            this, &PopUpManager::capslockChange);
    connect(ke, &KeyboardEvents::numlockChanged,
            this, &PopUpManager::numlockChange);
}

PopUpManager::~PopUpManager(){}

void PopUpManager::popupClosing()
{
    popup = NULL;
}

void PopUpManager::popupText(const QString & text)
{
    if(popup) delete popup;

    popup = new WinPopupNotification();
    popup->setText(text);
    popup->display();
    connect(popup, &WinPopupNotification::closed,
            this, &PopUpManager::popupClosing);
}

QString PopUpManager::onText(bool on)
{
    if(on) return "ON";
    else return "OFF";
}

void PopUpManager::capslockChange(bool on)
{
    popupText(QString("Capslock: ") + onText(on));
}

void PopUpManager::numlockChange(bool on)
{
    popupText(QString("Numlock: ") + onText(on));
}
