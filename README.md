# qt-keyboard-status
Simple app that listens to evdev to display a popup with a tray icon when
capslock and numlock are togged.

## About
The app is designed to for keyboards or laptops that do not have any lights to
indicate when certain functions are engaged. It makes sense to run when you
start your window manager. I personally use openbox so I run the app in my
autostart.

This is only compatible with Linux.

## Install
Clone the repo.
Run qmake to create a make file.
``` shell
qmake
```
Run make to build the binary.
``` shell
make
```
Run make install to install the files into the system
``` shell
sudo make install
```

## Usage

``` shell
KeyboardStatus
```

Copyright (c) 2017 Lightscale Tech Ltd
