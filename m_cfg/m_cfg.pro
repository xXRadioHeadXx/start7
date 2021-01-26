QT       += core gui widgets printsupport network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
include(../src/requester/requester.pri)
include(../src/global.pri)

SOURCES += \
    MainWindowCFG.cpp \
    add_sql_user_form.cpp \
    admkeygenerator.cpp \
    backgroundimage.cpp \
    comport.cpp \
    dbform.cpp \
    main.cpp \
    map.cpp \
    mydrawobject.cpp \
    myscene.cpp \
    operator_form.cpp \
    rastr_adam_widget.cpp \
    sqlunit.cpp \
    ssoiportwidget.cpp \
    ssoiwidget.cpp \
    tablo_widget.cpp



HEADERS += \
    MainWindowCFG.h \
    add_sql_user_form.h \
    admkeygenerator.h \
    backgroundimage.h \
    comport.h \
    dbform.h \
    map.h \
    mydrawobject.h \
    myscene.h \
    operator_form.h \
    rastr_adam_widget.h \
    sqlunit.h \
    ssoiportwidget.h \
    ssoiwidget.h \
    tablo_widget.h



FORMS += \
    MainWindowCFG.ui \
    add_sql_user_form.ui \
    dbform.ui \
    map.ui \
    operator_form.ui \
    rastr_adam_widget.ui \
    ssoiportwidget.ui \
    ssoiwidget.ui \
    tablo_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    my_cfg_resources.qrc

#LIBS += -lusb-1.0
