QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase core gui widgets printsupport network sql

TEMPLATE = app

#include(../src/port/port.pri)
#include(../src/entity/entity.pri)
#include(../src/tablemodel/tablemodel.pri)
#include(../src/utils/utils.pri)
#include(../src/database/database.pri)
#include(../src/requester/requester.pri)
#include(../src/global.pri)
#include(../m_cfg/unitWidgets/unitWidgets.pri)
#include(../m_cfg/my/my.pri)

SOURCES +=  tst_firsttest.cpp
