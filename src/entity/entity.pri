QT += core
CONFIG += c++17

include(../statewordparsers/statewordparsers.pri)

INCLUDEPATH += $$PWD/

SOURCES += \
    $$PWD/JourEntity.cpp \
    $$PWD/Operator.cpp \
    $$PWD/UnitNode.cpp \
#    $$PWD/MessageEntity.cpp \
    $$PWD/UnitNodeFactory.cpp

HEADERS += \
    $$PWD/JourEntity.h \
    $$PWD/Operator.h \
    $$PWD/UnitNode.h \
#    $$PWD/MessageEntity.h \
    $$PWD/UnitNodeFactory.h
