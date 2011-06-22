#-------------------------------------------------
#
# Project created by QtCreator 2011-06-18T13:59:44
#
#-------------------------------------------------

QT       += core gui declarative phonon

TARGET = untitled
TEMPLATE = app
target.path=/usr/local/bin
INSTALLS=target

SOURCES += main.cpp \
    Drummer.cpp

HEADERS  += \
    Drummer.hpp

OTHER_FILES += \
    Pad.qml \
    ExitButton.qml \
    Loop.qml \
    Slider.qml \
    screen.qml \
    Sound.qml \
    MainWindow.qml \
    arrow.png

RESOURCES += \
    resources.qrc
