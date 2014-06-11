TEMPLATE = app
CONFIG += console
QT -= gui
QT += dbus

LIBS += $$PWD/../3rdParty/BBBIOlib/BBBio_lib/libBBBio.a

SOURCES += \
    main.cpp \
    dbus/baulicht.cpp \
    dbus/blink.cpp \
    dbus/text.cpp \
    output/pluginmanager.cpp \
    output/Morse.cpp \
    baulichtexecutor.cpp

HEADERS += \
    output/morse.h \
    output/flipdot.h \
    output/output.h \
    dbus/baulicht.h \
    dbus/blink.h \
    dbus/text.h \
    output/pluginmanager.h \
    baulichtexecutor.h


