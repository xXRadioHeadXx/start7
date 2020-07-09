QT += core

CONFIG += c++11

INCLUDEPATH += $$PWD/

SOURCES += \
    $$PWD/AppTranslator.cpp \
    $$PWD/Icons.cpp \
#    $$PWD/ProcessDKWaiter.cpp \
    $$PWD/SettingUtils.cpp \
#    $$PWD/TablePrint.cpp \
    $$PWD/Utils.cpp \
#    $$PWD/ConfirmationAdmissionWaiter.cpp \
#    $$PWD/StatusRequester.cpp \
    $$PWD/SignalSlotCommutator.cpp
#    $$PWD/OnOffIUWaiter.cpp

HEADERS += \
#    $$PWD/AbstractRequester.h \
    $$PWD/AppTranslator.h \
    $$PWD/Icons.h \
#    $$PWD/ProcessDKWaiter.h \
    $$PWD/SettingUtils.h \
#    $$PWD/TablePrint.h \
    $$PWD/Utils.h \
#    $$PWD/ConfirmationAdmissionWaiter.h \
#    $$PWD/StatusRequester.h \
    $$PWD/SignalSlotCommutator.h
#    $$PWD/OnOffIUWaiter.h
