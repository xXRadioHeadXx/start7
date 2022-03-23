QT       += core gui widgets printsupport network sql

TARGET = m_cfg
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

OBJECTS_DIR = obj
MOC_DIR = moc
RCC_DIR = rcc
UI_DIR = ui

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
include(../m_cfg/unitWidgets/unitWidgets.pri)
include(../m_cfg/my/my.pri)

SOURCES += \
    MainWindowCFG.cpp \
    adam_widget.cpp \
    add_sql_user_form.cpp \
    adm_aud_combobox.cpp \
    admaud_widget.cpp \
    admkeygenerator.cpp \
    backgroundimage.cpp \
    comport.cpp \
    dbform.cpp \
    delegate.cpp \
    edit_unit_widget.cpp \
    findunitform.cpp \
    first_dialog.cpp \
    group.cpp \
    main.cpp \
    model_unit_params.cpp \
    my_doublespinbox.cpp \
    my_settings.cpp \
    my_treeview.cpp \
    mydrawobject.cpp \
    operator_form.cpp \
    qdevicewatcher.cpp \
    qdevicewatcher_linux.cpp \
    qdevicewatcher_win32.cpp \
    rastr_widget.cpp \
    rif_widget_delegate.cpp \
    rif_widget_model.cpp \
    sql_user_dlg.cpp \
    sqlunit.cpp \
    ssoi_port_widget.cpp \
    ssoi_widget.cpp \
    tablo_widget.cpp \
    unit_finder_delegate.cpp \
    unit_parametr.cpp \
    unitfinder.cpp



HEADERS += \
    MainWindowCFG.h \
    adam_widget.h \
    add_sql_user_form.h \
    adm_aud_combobox.h \
    admaud_widget.h \
    admkeygenerator.h \
    backgroundimage.h \
    comport.h \
    dbform.h \
    delegate.h \
#    delegate_unit_finder.h \
    edit_unit_widget.h \
    findunitform.h \
    first_dialog.h \
    group.h \
    adm_aud_combobox.h \
    model_unit_params.h \
#    my_config.h \
    my_doublespinbox.h \
    my_settings.h \
    my_treeview.h \
    mydrawobject.h \
    operator_form.h \
    qdevicewatcher.h \
    qdevicewatcher_p.h \
    rastr_widget.h \
    rif_widget_delegate.h \
    rif_widget_model.h \
    sql_user_dlg.h \
    sqlunit.h \
    ssoi_port_widget.h \
    ssoi_widget.h \
    tablo_widget.h \
    unit_finder_delegate.h \
    unit_parametr.h \
    unitfinder.h



FORMS += \
    MainWindowCFG.ui \
    adam_widget.ui \
    add_sql_user_form.ui \
    admaud_widget.ui \
    dbform.ui \
    edit_unit_widget.ui \
    findunitform.ui \
    first_dialog.ui \
    operator_form.ui \
    rastr_widget.ui \
    sql_user_dlg.ui \
    ssoi_port_widget.ui \
    ssoi_widget.ui \
    tablo_widget.ui \
    unitfinder.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    my_cfg_resources.qrc

#LIBS += -lusb-1.0

DISTFILES += \
    icons/info_tablo.png \
    my/my.pri \
    unitWidgets/unitWidgets.pri
