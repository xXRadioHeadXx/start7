QT += core xml
CONFIG += c++17

INCLUDEPATH += $$PWD/

SOURCES += \
    $$PWD/DataQueueItem.cpp \
    $$PWD/GraphTerminal.cpp \
    $$PWD/Port.cpp \
    $$PWD/PortFactory.cpp \
    $$PWD/PortManager.cpp \
    $$PWD/TcpServer.cpp

HEADERS += \
    $$PWD/AbstractPort.h \
    $$PWD/AbstractPortFactory.h \
    $$PWD/DataQueueItem.h \
    $$PWD/GraphTerminal.h \
    $$PWD/Port.h \
    $$PWD/PortFactory.h \
    $$PWD/PortManager.h \
    $$PWD/TcpServer.h
