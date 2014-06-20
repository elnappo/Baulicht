TEMPLATE = app
CONFIG += console
QT -= gui
QT += dbus

SOURCES += \
    main.cpp \
    dbus/baulicht.cpp \
    dbus/blink.cpp \
    dbus/text.cpp \
    output/pluginmanager.cpp \
    baulichtexecutor.cpp \
    output/onoff_gpio.cpp \
    dbus/settings.cpp

HEADERS += \
    output/morse.h \
    output/flipdot.h \
    output/output.h \
    dbus/baulicht.h \
    dbus/blink.h \
    dbus/text.h \
    output/pluginmanager.h \
    baulichtexecutor.h \
    output/onoff_gpio.h \
    dbus/settings.h


