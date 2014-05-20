TEMPLATE = app
CONFIG += console
QT -= gui
QT += dbus

SOURCES += \
    main.cpp \
    dbus/baulicht.cpp \
    dbus/blink.cpp \
    dbus/text.cpp \
    output/pluginmanager.cpp

HEADERS += \
    output/morse.h \
    output/flipdot.h \
    output/output.h \
    dbus/baulicht.h \
    dbus/blink.h \
    dbus/text.h \
    output/pluginmanager.h


