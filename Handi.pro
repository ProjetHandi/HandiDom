QT += \
    widgets \
    serialport \
    sql

SOURCES += \
    frame.cpp \
    contact.cpp \
    main.cpp \
    communication.cpp

HEADERS += \
    contact.h \
    frame.h \
    communication.h

CONFIG += c++11

INSTALLS        = target
target.files    = Phone
target.path     = /home/pi/handi
