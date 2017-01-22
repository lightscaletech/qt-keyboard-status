#ifndef _TRAY_ICON_H_
#define _TRAY_ICON_H_

#include <QSystemTrayIcon>

class KeyboardState;
class KeyboardEvents;

class TrayIcon: public QSystemTrayIcon
{
Q_OBJECT
public:
    TrayIcon(KeyboardState *, KeyboardEvents *, QObject * = NULL);
    ~TrayIcon();
public slots:
    void keyEvent(bool);
private:
    KeyboardState * keyboardState;
    KeyboardEvents * keyboardEvents;

    void changeIcon(const QString &);
    void setCurrentIcon();
};

#endif
