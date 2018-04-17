QT += \
    widgets \
    serialport

DISTFILES +=

unix|win32: LIBS += -lmysqlcppconn

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
