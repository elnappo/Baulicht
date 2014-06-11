TEMPLATE = app
CONFIG += console
QT -= gui
QT += dbus

#LIBS += $$PWD/../3rdParty/BBBIOlib/BBBio_lib/libBBBio.a

SOURCES += \
    main.cpp \
    dbus/baulicht.cpp \
    dbus/blink.cpp \
    dbus/text.cpp \
    output/pluginmanager.cpp \
    baulichtexecutor.cpp \
    ../3rdParty/BBBIOlib/BBBio_lib/BBBiolib_ADCTSC.c \
    ../3rdParty/BBBIOlib/BBBio_lib/BBBiolib_McSPI.c \
    ../3rdParty/BBBIOlib/BBBio_lib/BBBiolib_PWMSS.c \
    ../3rdParty/BBBIOlib/BBBio_lib/BBBiolib.c \
    output/onoff_gpio.cpp

HEADERS += \
    output/morse.h \
    output/flipdot.h \
    output/output.h \
    dbus/baulicht.h \
    dbus/blink.h \
    dbus/text.h \
    output/pluginmanager.h \
    baulichtexecutor.h \
    ../3rdParty/BBBIOlib/BBBio_lib/BBBiolib_ADCTSC.h \
    ../3rdParty/BBBIOlib/BBBio_lib/BBBiolib_McSPI.h \
    ../3rdParty/BBBIOlib/BBBio_lib/BBBiolib_PWMSS.h \
    ../3rdParty/BBBIOlib/BBBio_lib/BBBiolib.h \
    output/onoff_gpio.h


