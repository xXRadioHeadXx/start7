QT += core

CONFIG += c++17

INCLUDEPATH += $$PWD/

SOURCES += \
#    $$PWD/AppTranslator.cpp \
    $$PWD/AlarmSwitchOffLogger.cpp \
    $$PWD/Icons.cpp \
#    $$PWD/ProcessDKWaiter.cpp \
    $$PWD/Icons_cfg.cpp \
    $$PWD/RunGuard.cpp \
    $$PWD/SettingUtils.cpp \
#    $$PWD/TablePrint.cpp \
    $$PWD/Utils.cpp \
#    $$PWD/ConfirmationAdmissionWaiter.cpp \
#    $$PWD/StatusRequester.cpp \
    $$PWD/SignalSlotCommutator.cpp \
    $$PWD/control.cpp
#    $$PWD/OnOffIUWaiter.cpp

HEADERS += \
#    $$PWD/AbstractRequester.h \
#    $$PWD/AppTranslator.h \
    $$PWD/AlarmSwitchOffLogger.h \
    $$PWD/Icons.h \
#    $$PWD/ProcessDKWaiter.h \
    $$PWD/Icons_cfg.h \
    $$PWD/RunGuard.h \
    $$PWD/SettingUtils.h \
#    $$PWD/TablePrint.h \
    $$PWD/Utils.h \
#    $$PWD/ConfirmationAdmissionWaiter.h \
#    $$PWD/StatusRequester.h \
    $$PWD/SignalSlotCommutator.h \
    $$PWD/control.h
#    $$PWD/OnOffIUWaiter.h
