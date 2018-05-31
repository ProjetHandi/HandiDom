QT += \
    widgets \
    serialport \
    sql

SOURCES += \
    frame.cpp \
    contact.cpp \
    main.cpp \
    communication.cpp \
    user.cpp \
    userframe.cpp

HEADERS += \
    contact.h \
    frame.h \
    communication.h \
    user.h \
    userframe.h

CONFIG += c++11

INSTALLS        = target
target.files    = Phone
target.path     = /home/pi/handi
