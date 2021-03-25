QT += core

CONFIG += c++17

INCLUDEPATH += $$PWD/

SOURCES += \
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
