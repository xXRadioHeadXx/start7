QT += core
CONFIG += c++17

include(../statewordparsers/statewordparsers.pri)

INCLUDEPATH += $$PWD/

SOURCES += \
    $$PWD/JourEntity.cpp \
    $$PWD/Operator.cpp \
    $$PWD/ServerUnitNodeTreeItem.cpp \
    $$PWD/TreeItem.cpp \
    $$PWD/UnitNode.cpp \
#    $$PWD/MessageEntity.cpp \
    $$PWD/UnitNodeCFG.cpp \
    $$PWD/UnitNodeFactory.cpp

HEADERS += \
    $$PWD/JourEntity.h \
    $$PWD/Operator.h \
    $$PWD/ServerUnitNodeTreeItem.h \
    $$PWD/TreeItem.h \
    $$PWD/UnitNode.h \
#    $$PWD/MessageEntity.h \
    $$PWD/UnitNodeCFG.h \
    $$PWD/UnitNodeFactory.h
