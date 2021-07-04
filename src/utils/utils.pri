QT += core multimedia

CONFIG += c++14 -std=gnu++14 -std=c++14

INCLUDEPATH += $$PWD/

SOURCES += \
#    $$PWD/AppTranslator.cpp \
    $$PWD/AlarmSwitchOffLogger.cpp \
    $$PWD/ConvertUTF.c \
    $$PWD/Icons.cpp \
#    $$PWD/ProcessDKWaiter.cpp \
    $$PWD/Icons_cfg.cpp \
    $$PWD/RunGuard.cpp \
#    $$PWD/TablePrint.cpp \
    $$PWD/ServerSettingUtils.cpp \
#    $$PWD/SettingUtils.cpp \
    $$PWD/Sheduler.cpp \
    $$PWD/ShedulerNewDuty.cpp \
    $$PWD/SoundAdjuster.cpp \
    $$PWD/Utils.cpp \
#    $$PWD/ConfirmationAdmissionWaiter.cpp \
#    $$PWD/StatusRequester.cpp \
    $$PWD/SignalSlotCommutator.cpp
#    $$PWD/OnOffIUWaiter.cpp

HEADERS += \
#    $$PWD/AbstractRequester.h \
#    $$PWD/AppTranslator.h \
    $$PWD/AlarmSwitchOffLogger.h \
    $$PWD/ConvertUTF.h \
    $$PWD/Icons.h \
#    $$PWD/ProcessDKWaiter.h \
    $$PWD/Icons_cfg.h \
    $$PWD/RunGuard.h \
#    $$PWD/TablePrint.h \
    $$PWD/ServerSettingUtils.h \
#    $$PWD/SettingUtils.h \
    $$PWD/Sheduler.h \
    $$PWD/ShedulerNewDuty.h \
    $$PWD/SimpleIni.h \
    $$PWD/SoundAdjuster.h \
    $$PWD/Utils.h \
#    $$PWD/ConfirmationAdmissionWaiter.h \
#    $$PWD/StatusRequester.h \
    $$PWD/SignalSlotCommutator.h
#    $$PWD/OnOffIUWaiter.h
