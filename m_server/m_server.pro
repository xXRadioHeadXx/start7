QT       += core gui widgets network sql

#greaterThan(QT_MAJOR_VERSION, 4): QT +=

CONFIG += c++11
#CONFIG += console

OBJECTS_DIR = obj
MOC_DIR = moc

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


include(../src/port/port.pri)
include(../src/entity/entity.pri)
include(../src/tablemodel/tablemodel.pri)
include(../src/utils/utils.pri)
include(../src/database/database.pri)

SOURCES += \
#    AppTranslator.cpp \
#    DataBaseManager.cpp \
#    Icons.cpp \
#    SettingUtils.cpp \
#    Utils.cpp \
#    entity/UnitNode.cpp \
#    entity/MessageEntity.cpp \
    main.cpp \
    MainWindow.cpp #\
#    port/ConfirmationAdmissionWaiter.cpp \
#    port/Port.cpp \
#    port/PortFactory.cpp \
#    port/PortManager.cpp \
#    port/StatusRequester.cpp \
#    SignalSlotCommutator.cpp #\
#    tablemodel/TableModelMSG.cpp \
#    proxyfunc.cpp \
#    tablemodel/TreeModelUnitNode.cpp

HEADERS += \
#    AppTranslator.h \
#    DataBaseManager.h \
#    Icons.h \
#    SettingUtils.h \
#    Utils.h \
#    entity/UnitNode.h \
#    entity/MessageEntity.h \
    MainWindow.h #\
#    port/AbstractPort.h \
#    port/AbstractPortFactory.h \
#    port/ConfirmationAdmissionWaiter.h \
#    port/DataQueueItem.h \
#    port/Port.h \
#    port/PortFactory.h \
#    port/PortManager.h \
##    proxyfunc.h \
#    port/StatusRequester.h \
#    SignalSlotCommutator.h #\
#    tablemodel/TableModelMSG.h \
#    tablemodel/TreeModelUnitNode.h

FORMS += \
    mainwindow.ui

#TRANSLATIONS += app_ru.ts \
#                app_ru.qm

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
