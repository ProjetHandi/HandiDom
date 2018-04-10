QT += \
    widgets

DISTFILES +=

unix|win32: LIBS += -lmysqlcppconn

SOURCES += \
    frame.cpp \
    contact.cpp \
    main.cpp

HEADERS += \
    contact.h \
    frame.h

CONFIG += c++11
