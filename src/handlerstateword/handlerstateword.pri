QT += core 
CONFIG += c++14 -std=gnu++14 -std=c++14

include(./31/31.pri)
include(./32/32.pri)
include(./33/33.pri)
include(./34/34.pri)
#include(./35/35.pri)
include(./41/41.pri)
include(./42/42.pri)

INCLUDEPATH += $$PWD/

HEADERS += \
    $$PWD/HandlerStateWordAbstract.h \
    $$PWD/ProcessingStateWordAbstract.h

SOURCES += \
    $$PWD/HandlerStateWordAbstract.cpp \
    $$PWD/ProcessingStateWordAbstract.cpp
