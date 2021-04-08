QT += core
CONFIG += c++17

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
