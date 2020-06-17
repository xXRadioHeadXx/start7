QT += core
CONFIG += c++11

INCLUDEPATH += $$PWD/

SOURCES += \
    $$PWD/DataQueueItem.cpp \
    $$PWD/Port.cpp \
    $$PWD/PortFactory.cpp \
    $$PWD/PortManager.cpp \

HEADERS += \
    $$PWD/AbstractPort.h \
    $$PWD/AbstractPortFactory.h \
    $$PWD/DataQueueItem.h \
    $$PWD/Port.h \
    $$PWD/PortFactory.h \
    $$PWD/PortManager.h \
