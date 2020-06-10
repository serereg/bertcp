TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ..\serverApp.cpp

INCLUDEPATH += ..\

HEADERS += \
    ..\Common.h \
    ..\Exception.h \
    ..\Message.h \
    ..\Server.h

LIBS += -lwsock32
