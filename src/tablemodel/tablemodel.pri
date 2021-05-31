QT += core
CONFIG += c++14 -std=gnu++14 -std=c++14

INCLUDEPATH += $$PWD/

SOURCES += \
    $$PWD/ComboBoxDelegate.cpp \
    $$PWD/ServerTableModelJour.cpp \
    $$PWD/ServerTreeModelUnitNode.cpp \
#    $$PWD/TreeModelUnitNode.cpp \
    $$PWD/TableModelMSG.cpp

HEADERS += \
    $$PWD/ComboBoxDelegate.h \
    $$PWD/ServerTableModelJour.h \
    $$PWD/ServerTreeModelUnitNode.h \
#    $$PWD/TreeModelUnitNode.h \
    $$PWD/TableModelMSG.h
