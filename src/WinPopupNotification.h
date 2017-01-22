#ifndef _WIN_POPUP_NOTIFICATION_H_
#define _WIN_POPUP_NOTIFICATION_H_

#include <QWidget>

class QLabel;

class WinPopupNotification:
    public QWidget
{
    Q_OBJECT
public:
    WinPopupNotification(QWidget * = NULL);
    ~WinPopupNotification();

    QString text();
    void setText(const QString &);

    int timeout();
    void setTimeout(int);

    void display();

signals:
    void closed();
public slots:
    void close();

private:
    int nTimeout;
    QLabel * nText;

    void sizeAndPos();
};

#endif
