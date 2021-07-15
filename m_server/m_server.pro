QT       += core gui widgets network sql

TARGET = m_server
TEMPLATE = app

#greaterThan(QT_MAJOR_VERSION, 4): QT +=

CONFIG += c++14 -std=gnu++14 -std=c++14
#CONFIG += console

#Application version
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_BUILD = 0



OBJECTS_DIR = obj
MOC_DIR = moc
RCC_DIR = rcc
UI_DIR = ui

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
            "VERSION_MINOR=$$VERSION_MINOR"\
            "VERSION_BUILD=$$VERSION_BUILD"\
            QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}

include(../src/port/port.pri)
include(../src/entity/entity.pri)
include(../src/tablemodel/tablemodel.pri)
include(../src/utils/utils.pri)
include(../src/database/database.pri)
include(../src/requester/requester.pri)
include(../src/template/template.pri)
include(../src/qcron/qcron.pri)
include(../src/global.pri)

SOURCES += \
    AuthenticationDialog.cpp \
    MainWindowServer.cpp \
    main.cpp

HEADERS += \
    ../src/global.h \
    AuthenticationDialog.h \
    MainWindowServer.h

FORMS += \
    AuthenticationDialog.ui \
    MainWindowServer.ui

CODECFORSRC     = UTF-8

TRANSLATIONS += app_ru.ts \
                app_ru.qm

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
