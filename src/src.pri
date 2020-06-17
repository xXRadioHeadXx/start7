QT += core
CONFIG += c++11

INCLUDEPATH += $$PWD/

#SOURCES += \
#    $$PWD/DataBaseManager.cpp

#HEADERS += \
#    $$PWD/DataBaseManager.h

include(port/port.pri)
include(entity/entity.pri)
include(tablemodel/tablemodel.pri)
include(utils/utils.pri)
include(database/database.pri)
include(requester/requester.pri)
