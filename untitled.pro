#-------------------------------------------------
#
# Project created by QtCreator 2011-06-18T13:59:44
#
#-------------------------------------------------

QT       += core gui declarative

TARGET = untitled
TEMPLATE = app
target.path=/usr/local/bin
INSTALLS=target


SOURCES += main.cpp \
    Drummer.cpp

HEADERS  += \
    Drummer.hpp
unix {
    INCLUDEPATH += "$$(IADP_SDK_DIR_MEEGO)Cpp\include"
    LIBS += -lxml2\
            -lpthread
    LIBS += "$$(IADP_SDK_DIR_MEEGO)Cpp\lib\libadpruntime.a"\ 
        "$$(IADP_SDK_DIR_MEEGO)Cpp\lib\libadpcore.a"\ 
        "$$(IADP_SDK_DIR_MEEGO)Cpp\lib\libxerces-c.a"\ 
        "$$(IADP_SDK_DIR_MEEGO)Cpp\lib\libxml-security-c.a"\ 
        "$$(IADP_SDK_DIR_MEEGO)Cpp\lib\libcrypto.a" 
}

OTHER_FILES += \
    Pad.qml \
    main.qml \
    ExitButton.qml

RESOURCES += \
    resources.qrc
