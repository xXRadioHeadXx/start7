QT += core 
CONFIG += c++14 -std=gnu++14 -std=c++14

#include(./blip/blip.pri)
include(./rlm/rlm.pri)
include(./rlmc/rlmc.pri)
#include(./sota/sota.pri)
#include(./ssoiblip/ssoiblip.pri)
#include(./t4k/t4k.pri)
include(./tg/tg.pri)

INCLUDEPATH += $$PWD/

HEADERS += \
    $$PWD/HandlerStateWord0x31.h \
    $$PWD/ProcessingStateWord0x31DK.h

SOURCES += \
    $$PWD/HandlerStateWord0x31.cpp \
    $$PWD/ProcessingStateWord0x31DK.cpp