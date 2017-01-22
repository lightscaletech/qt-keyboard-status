#ifndef _POP_UP_MANAGER_H_
#define _POP_UP_MANAGER_H_

#include <QObject>
#include <QString>

class KeyboardEvents;
class WinPopupNotification;

class PopUpManager: public QObject
{
public:
    PopUpManager(KeyboardEvents *, QObject * = NULL);
    ~PopUpManager();

public slots:
    void capslockChange(bool);
    void numlockChange(bool);
    void popupClosing();

private:
    KeyboardEvents * keyboardEvents;
    WinPopupNotification * popup;

    QString onText(bool);
    void popupText(const QString &);
};

#endif
