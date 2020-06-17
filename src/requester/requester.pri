QT += core

CONFIG += c++11

INCLUDEPATH += $$PWD/

SOURCES += \
    $$PWD/ProcessDKWaiter.cpp \
    $$PWD/ConfirmationAdmissionWaiter.cpp \
    $$PWD/StatusRequester.cpp \
    $$PWD/OnOffIUWaiter.cpp

HEADERS += \
    $$PWD/AbstractRequester.h \
    $$PWD/ProcessDKWaiter.h \
    $$PWD/ConfirmationAdmissionWaiter.h \
    $$PWD/StatusRequester.h \
    $$PWD/OnOffIUWaiter.h
