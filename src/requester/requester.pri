QT += core

CONFIG += c++14 -std=gnu++14 -std=c++14

INCLUDEPATH += $$PWD/

SOURCES += \
    $$PWD/AbstractRequester.cpp \
    $$PWD/MultiUNStatusConnectRequester.cpp \
    $$PWD/ProcessDKWaiter.cpp \
    $$PWD/ConfirmationAdmissionWaiter.cpp \
#    $$PWD/StatusConnectRequester.cpp \
    $$PWD/LockWaiter.cpp \
    $$PWD/OnOffIUWaiter.cpp

HEADERS += \
    $$PWD/AbstractRequester.h \
    $$PWD/MultiUNStatusConnectRequester.h \
    $$PWD/ProcessDKWaiter.h \
    $$PWD/ConfirmationAdmissionWaiter.h \
#    $$PWD/StatusConnectRequester.h \
    $$PWD/LockWaiter.h \
    $$PWD/OnOffIUWaiter.h
