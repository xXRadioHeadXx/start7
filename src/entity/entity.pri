QT += core 
CONFIG += c++14 -std=gnu++14 -std=c++14

include(../statewordparsers/statewordparsers.pri)

INCLUDEPATH += $$PWD/

SOURCES += \
    $$PWD/JourEntity.cpp \
    $$PWD/KeyGroup.cpp \
    $$PWD/Operator.cpp \
    $$PWD/TreeItem.cpp \
    $$PWD/TypeUnitNode.cpp \
    $$PWD/UnitNode.cpp \
#    $$PWD/MessageEntity.cpp \
    $$PWD/UnitNodeCFG.cpp \
    $$PWD/UnitNodeFactory.cpp \
    $$PWD/UnitNodeTreeItem.cpp

HEADERS += \
    $$PWD/JourEntity.h \
    $$PWD/KeyGroup.h \
    $$PWD/Operator.h \
    $$PWD/TreeItem.h \
    $$PWD/TypeUnitNode.h \
    $$PWD/UnitNode.h \
#    $$PWD/MessageEntity.h \
    $$PWD/UnitNodeCFG.h \
    $$PWD/UnitNodeFactory.h \
    $$PWD/UnitNodeTreeItem.h
