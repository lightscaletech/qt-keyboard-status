TEMPLATE = app

QT += gui
QT += widgets

CONFIG += c++11
CONFIG += link_pkgconfig
LIBS += -lX11

PKGCONFIG += libevdev

# Output
TARGET = bin/KeyboardStatus
OBJECTS_DIR = obj
QMAKE_CXXFLAGS += -ggdb
MOC_DIR = moc

# Input
RESOURCES = resources.qrc

HEADERS += src/PopUpManager.h
SOURCES += src/PopUpManager.cpp

HEADERS += src/WinPopupNotification.h
SOURCES += src/WinPopupNotification.cpp

HEADERS += src/TrayIcon.h
SOURCES += src/TrayIcon.cpp

HEADERS += src/KeyboardState.h
SOURCES += src/KeyboardState.cpp

HEADERS += src/KeyboardEvents.h
SOURCES += src/KeyboardEvents.cpp

SOURCES += src/KeyboardStatus.cpp

target.path = /usr/local/bin

INSTALLS += target
