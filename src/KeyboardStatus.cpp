#include <QApplication>
#include "KeyboardState.h"
#include "KeyboardEvents.h"
#include "TrayIcon.h"
#include "PopUpManager.h"

int main(int ac, char * av[])
{
    QApplication app(ac, av);
    KeyboardState * ks = new KeyboardState();
    KeyboardEvents * ke = new KeyboardEvents(ks);
    TrayIcon * ti = new TrayIcon(ks, ke);
    PopUpManager * pm = new PopUpManager(ke);

    int r = app.exec();

    delete ks;
    delete ke;
    delete ti;
    delete pm;

    return r;
}
