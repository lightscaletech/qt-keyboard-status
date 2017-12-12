#include "WinPopupNotification.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>

WinPopupNotification::WinPopupNotification(QWidget * parent):
    QWidget(parent,
            Qt::ToolTip |
            Qt::WindowStaysOnTopHint),
    nTimeout(1500)
{
    QVBoxLayout * layout = new QVBoxLayout();

    nText = new QLabel(this);

    layout->addWidget(nText);

    this->setLayout(layout);
}

WinPopupNotification::~WinPopupNotification()
{

}


QString WinPopupNotification::text(){ return nText->text(); }
void WinPopupNotification::setText(const QString & text){ this->nText->setText(text); }

int WinPopupNotification::timeout(){ return nTimeout; }
void WinPopupNotification::setTimeout(int timeout){ this->nTimeout = timeout; }

void WinPopupNotification::display()
{
    sizeAndPos();
    show();
    QTimer::singleShot(nTimeout, this, &WinPopupNotification::close);

}

void WinPopupNotification::close()
{
    hide();
    closed();
    this->deleteLater();
}

void WinPopupNotification::sizeAndPos()
{
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            nText->size(),
            QApplication::desktop()->availableGeometry())
        );
}
