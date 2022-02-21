#ifndef MAINWINDOWCFG_H
#define MAINWINDOWCFG_H

#include <QMainWindow>
#include <TreeModelUnitNode.h>
#include <QErrorMessage>
#include "operator_form.h"
#include "edit_unit_widget.h"
#include <dbform.h>
#include "comport.h"
#include "sqlunit.h"
#include <QHostInfo>
#include <QStandardItem>
//#include <libudev.h>
//#include <mntent.h>
#include "ssoi_widget.h"
#include <QTimer>
#include <delegate.h>
#include <rif_widget_model.h>
#include <rif_widget_delegate.h>
#include <QMessageBox>
#include <my_settings.h>
#include <unitfinder.h>

#include <unitWidgets/widget_iu_bl_ip.h>
#include <unitWidgets/widget_sd_bl_ip.h>
#include <unitWidgets/widget_group.h>
#include <unitWidgets/widget_adam.h>

#include <unitWidgets/widget_kl.h>
#include <unitWidgets/widget_tg.h>
#include <unitWidgets/widget_rlm_krl.h>
#include <unitWidgets/widget_rlm_c.h>
#include <unitWidgets/widget_adam.h>
#include <unitWidgets/widget_strazh_ip.h>
#include <unitWidgets/widget_onvif.h>
#include <unitWidgets/widget_bod_t4k_m.h>
#include <unitWidgets/widget_bod_sota.h>
#include <unitWidgets/widget_y4_sota.h>
#include <unitWidgets/widget_y4_t4k_m.h>
#include <unitWidgets/widget_dd_sota.h>
#include <unitWidgets/widget_dd_t4k_m.h>
#include <unitWidgets/widget_devline.h>
#include <unitWidgets/widget_net_dev.h>
#include <unitWidgets/widget_ssoi_iu.h>
#include <unitWidgets/widget_ssoi_sd.h>
#include <unitWidgets/widget_toros.h>
#include <unitWidgets/widget_rastrmtv.h>
#include <unitWidgets/widget_info_tablo.h>
#include <unitWidgets/widget_tg.h>
#include <unitWidgets/widget_ssoi_ip_sd.h>
#include <unitWidgets/widget_ssoi_ip_iu.h>

#include <unitWidgets/widget_adam.h>
#include <unitWidgets/widget_adam.h>
#include <unitWidgets/widget_adam.h>
#include <unitWidgets/widget_adam.h>
#include <unitWidgets/widget_adam.h>
#include <unitWidgets/widget_adam.h>
#include <unitWidgets/widget_adam.h>
#include <unitWidgets/widget_adam.h>
#include <unitWidgets/widget_adam.h>
#include <my/my_config.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowCFG; }
QT_END_NAMESPACE

enum op_tbl {
    Add = 1,
    Edit = 2,
    Delete = 3
};









class MainWindowCFG : public QMainWindow
{
    Q_OBJECT
private:    

    template< class T >
   void add( T* a);



    Widget_GROUP* w_GROUP;
    Widget_SD_BL_IP* w_SD_BL_IP;
    Widget_IU_BL_IP* w_IU_BL_IP ;

    Widget_KL* w_KL;

    Widget_TG* w_TG ;
    Widget_RLM_KRL* w_RLM_KRL;
    Widget_RLM_C* w_RLM_C;
    Widget_STRAZH_IP* w_STRAZH_IP;
    Widget_ONVIF* w_ONVIF;
    Widget_BOD_T4K_M* w_BOD_T4K_M;
    Widget_Y4_T4K_M* w_Y4_T4K_M;
    Widget_DD_T4K_M* w_DD_T4K_M;
    Widget_BOD_SOTA* w_BOD_SOTA;
    Widget_Y4_SOTA* w_Y4_SOTA;
    Widget_DD_SOTA* w_DD_SOTA;
    Widget_NET_DEV* w_NET_DEV;


    Widget_SSOI_SD* w_SSOI_SD;
    Widget_SSOI_IU* w_SSOI_IU;
    Widget_ADAM* w_ADAM;
    Widget_TOROS* w_TOROS;
    Widget_DEVLINE* w_DEVLINE;
    Widget_RASTRMTV* w_RASTRMTV;
    Widget_INFO_TABLO* w_INFO_TABLO;

    Widget_SSOI_IP_SD* w_SSOI_IP_SD;
    Widget_SSOI_IP_IU* w_SSOI_IP_IU;

    QList<UnitWidget*> l_UnitWidgets;


QMap <QString, SerNum_Name> mSerNum_Name;


  bool eventFilter(QObject *obj, QEvent *event);

    Delegate* dlgt;

    QRegExpValidator* validator;

    UnitWidget* current_wgt();

    bool compare(UnitNode* unit,UnitNode* un);

    int cfg_type;


    QTimer *timer;

    QString last_ini_patch;

    My_settings* my;

    Ui::MainWindowCFG *ui;

    QSqlDatabase db_mysql;
    QSqlDatabase db_psql;

    TreeModelUnitNode *modelTreeUN = nullptr;

    QMessageBox dialog;

    QRegExpValidator *ipValidator;

    rif_widget_model* rif_model ;
    rif_widget_delegate* rif_dlgt;

    UnitFinder* unitFinder_f;

    QList<Operator*> operators;
    int opt_tbl_request;
    void operator_add(Operator*);
    void operator_edit(Operator*);
    void operator_delete();

    void SSOI_SD_set_values_from_combobox(UnitNode *unit); //красота требует жертв. - в один комбобокс сваливаем разные настройки.
    void SSOI_SD_set_combobox_value_from(UnitNode *unit); //красота требует жертв - в один комбобокс сваливаем разные настройки.

    void SD_BL_IP_set_values_from_combobox(UnitNode *unit); //красота требует жертв. - в один комбобокс сваливаем разные настройки.
    void SD_BL_IP_set_combobox_value_from(UnitNode *unit); //красота требует жертв - в один комбобокс сваливаем разные настройки.


    QString XOR_Crypt(QString in,QString key);

    void update_operators_table();

    QString get_unit_name(int type);






    void expandChildren(const QModelIndex &index);
    void collapseChildren(const QModelIndex &index);

    void object_menu_change(int type);
    void object_menu_set_settings_default(int type);
    void object_menu_set_settings_from(UnitNode *unit);


    void RS485_UDP_set_default_with_timeout(int timeout);
    void RS485_UDP_set_from_unit(UnitNode *unit);
    void RS485_UDP_set_enabled_for_edit(bool enable);

    void Name_update();

    void func_to_edit_unit();

    QString get_dd(UnitNode* unit);
    QString get_y4(UnitNode* unit);
//    QList<udev_device*> listDevices();

    SQLunit MySQL_unit;
    SQLunit Postgre_unit;

    QMenu* menu;

    QAction* action_open_edit_menu;
    QAction* action_setDK;
    QAction* action_YZ_MONOLIT;
    QAction* action_setAlarmMsgOn;

    QMenu*  menuAdamOff;
    QAction* action_setAdamOff_off;
    QAction* action_setAdamOff_5_sec;
    QAction* action_setAdamOff_10_sec;
    QAction* action_setAdamOff_30_sec;
    QAction* action_setAdamOff_1_min;
    QAction* action_setAdamOff_5_min;
    QAction* action_setAdamOff_10_min;
    QAction* action_setAdamOff_20_min;
    QAction* action_setAdamOff_30_min;
    QAction* action_setAdamOff_1_hour;

    QAction* action_open_device_tree;
    QAction *action_close_device_tree;

    int val_for_setAdamoff;

    int operators_use;


    bool can_i_add_or_not(int type_parrent, int type_child);


    bool add_unit();
    bool change_unit();
    bool delete_unit();

    void show_the_tree();

    void get_option(UnitNode *unit);
    bool set_option(UnitNode *unit,UnitNode *parent);


    void get_option_GROUP(UnitNode *unit);
    void set_option_GROUP(UnitNode *unit);


    void get_option_SD_BL_IP(UnitNode *unit);
    void set_option_SD_BL_IP(UnitNode *unit);



    void get_option_IU_BL_IP(UnitNode *unit);
    void set_option_IU_BL_IP(UnitNode *unit);



    void get_option_TG(UnitNode *unit);
    void set_option_TG(UnitNode *unit);


    void get_option_RLM_KRL(UnitNode *unit);
    void set_option_RLM_KRL(UnitNode *unit);




    void get_option_RLM_C(UnitNode *unit);
    void set_option_RLM_C(UnitNode *unit);




    void get_option_BOD_T4K_M(UnitNode *unit);
    void set_option_BOD_T4K_M(UnitNode *unit);


    void get_option_Y4_T4K_M(UnitNode *unit);
    void set_option_Y4_T4K_M(UnitNode *unit, UnitNode* parrent);


    void get_option_DD_T4K_M(UnitNode *unit);
    void set_option_DD_T4K_M(UnitNode *unit,UnitNode *parent);


    void get_option_BOD_SOTA(UnitNode *unit);
    void set_option_BOD_SOTA(UnitNode *unit);


    void get_option_Y4_SOTA(UnitNode *unit);
    void set_option_Y4_SOTA(UnitNode *unit, UnitNode* parrent);


    void get_option_DD_SOTA(UnitNode *unit);
    void set_option_DD_SOTA(UnitNode *unit,UnitNode *parent);


    void get_option_BL_IP(UnitNode *unit);
    void set_option_BL_IP(UnitNode *unit);

    void get_option_KL(UnitNode *unit);
    void set_option_KL(UnitNode *unit);


    void get_option_ONVIF(UnitNode *unit);
    void set_option_ONVIF(UnitNode *unit);


    void get_option_STRAZH_IP(UnitNode *unit);
    void set_option_STRAZH_IP(UnitNode *unit);


    void get_option_NET_DEV(UnitNode *unit);
    void set_option_NET_DEV(UnitNode *unit);


    void get_option_SSOI_SD(UnitNode *unit);
    void set_option_SSOI_SD(UnitNode *unit);


    void get_option_SSOI_IU(UnitNode *unit);
    void set_option_SSOI_IU(UnitNode *unit);


    void get_option_ADAM(UnitNode *unit);
    void set_option_ADAM(UnitNode *unit);


    void get_option_TOROS(UnitNode *unit);
    void set_option_TOROS(UnitNode *unit);


    void get_option_DEVLINE(UnitNode *unit);
    void set_option_DEVLINE(UnitNode *unit);


    void get_option_RASTRMTV(UnitNode *unit);
    void set_option_RASTRMTV(UnitNode *unit);


    void get_option_INFO_TABLO(UnitNode *unit);
    void set_option_INFO_TABLO(UnitNode *unit);


    void TABLO_Num2_set(int val);
    int TABLO_Num2_get();

    bool setUdpTimeout_for_BL_IP(UnitNode *unit);

    bool setUdpTimeout_for_TG(UnitNode *unit);

    bool setUdpTimeout_for_KL(UnitNode *unit);

    bool setUdpTimeout_for_BOD_SOTA(UnitNode *unit);














    void load_other_options_from_ini_file(QString patch);


    void get_PARAMS(QString filename);
    void set_PARAMS(QString filename);
    void default_PARAMS();
    QMap <int,QString> map_PARAMS_PlanType;
    QMap <int,QString> map_PARAMS_SoundType;
    QMap <int,QString> map_PARAMS_AutoStart;

    void default_options();

    void get_RIF(QString filename);
    void set_RIF(QString filename);
    void default_RIF();

    void get_SSOI(QString filename);
    void set_SSOI(QString filename);
    void default_SSOI();

    void get_RASTRMTV(QString filename);
    void set_RASTRMTV(QString filename);
    void default_RASTRMTV();

    void get_INTEGRATION(QString filename);
    void set_INTEGRATION(QString filename);
    void default_INTEGRATION();
        QMap <int,QString> map_INTEGRATION_Use;

    void get_SQL(QString filename);
    void set_SQL(QString filename);
    void default_SQL();

    void get_RASTR(QString filename);
    void set_RASTR(QString filename);
    void default_RASTR();


    void get_ADAM4068(QString filename);
    void set_ADAM4068(QString filename);
    void default_ADAM4068();

    void get_TABLO(QString filename);
    void set_TABLO(QString filename);
    void default_TABLO();

    void get_RASTRMSSOI(QString filename);
    void set_RASTRMSSOI(QString filename);
    void default_RASTRMSSOI();

    void get_BACKUP(QString filename);
    void set_BACKUP(QString filename);
    void default_BACKUP();
    QMap <int,QString> map_BACKUP_MaxBdStringCnt;


    void get_PORT(QString filename);
    void set_PORT(QString filename);
    void default_PORT();

    void get_OPERATORS(QString filename);
    void set_OPERATORS(QString filename);
    void default_OPERATORS();

    void get_ASOOSD(QString filename);
    void set_ASOOSD(QString filename);
    void default_ASOOSD();


















    void save_ini(QString path);
    void save_option(QSettings* settings,UnitNode*  unit);
    void save_option_SD_BL_IP(QSettings* settings,UnitNode*  unit);
    void save_option_BOD_SOTA(QSettings* settings,UnitNode*  unit);



    bool this_name_is_free(QString Name);



    void update_rif_comport_table();

    int selected_type;

    QModelIndex current_index;


    QString str_system;
    QString str_system_RIF=          "РИФ+";
    QString str_system_SSOI=       "ССОИ-М";




QMap <int,QString> m_RLM_KRL_type{
{0,str_RIF_RLM},
{1,str_RIF_RLM_24},
{2,str_RIF_RLM_B},
{3,str_RIF_KRL},
{4,str_Razriv},
{5,str_trassa1l},
};












QMap <int,QString> m_ASOOSD_use{
{0,"ВЫКЛ"},
{1,"ВКЛ"},
};

    QMap <int,QString> SSOI_IU_Num3{
{1 , "ИУ1"},
{2 , "ИУ2" },
{3 , "ИУ3" },
{4 , "ВК1" },
{5 , "ВК2" },
{6 , "ВК3" },
};

    QMap <int,QString> SSOI_SD_Num3{
{1 , "1"},
{2 , "2" },
{3 , "3" },
{4 , "4" },
{5 , "5" },
{6 , "6" },
{7 , "7" },
{8 , "8" },
{9 , "Вскрытие" },
};



public:
    MainWindowCFG(QWidget *parent = nullptr);
    ~MainWindowCFG();

    bool load(QString patch);

 void show_equals(UnitNode* un);

    operator_form op_f;
    DBform* db_f;

    edit_unit_widget unit_wgt;

public slots:
    void updateName(QString);

    void from_rastr_widget(QString);


private slots:



    void  clear_list_equals();

    void next();
    void prev();

    void finder_next();
    void finder_prev();

    void find_from_options(QList<QString>);

    void double_unit_slot(UnitNode* un);

    void slot_to_get_options(QModelIndex index);
    void update();

    void unitNameChanged(QStandardItem*);

    void setDK();
    void YZ_MONOLIT();
    void setAlarmMsgOn();

    bool set_AdamOff_for_all_IU_BL_IP_instances(UnitNode* un);

    void setAdamOff();

    void keyPressEvent ( QKeyEvent * event ) override;



    void setAdamOff_off();
    void setAdamOff_5_sec();
    void setAdamOff_10_sec();
    void setAdamOff_30_sec();
    void setAdamOff_1_min();
    void setAdamOff_5_min();
    void setAdamOff_10_min();
    void setAdamOff_20_min();
    void setAdamOff_30_min();
    void setAdamOff_1_hour();


    void open_edit_menu();

    void open_device_tree();
    void close_device_tree();


    void select(QString Name);

    void set_x_y(QString Name,int x,int y);

    void on_treeView_clicked(const QModelIndex &index);



    void on_actionCreate_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_treeView_activated(const QModelIndex &index);
    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();
    void on_pushButton_moveUp_clicked();
    void on_pushButton_moveDown_clicked();

    void on_treeView_customContextMenuRequested(const QPoint &pos);

    void on_operators_use_combobox_currentTextChanged(const QString &arg1);



    void on_add_operator_button_clicked();

    void on_tableWidget_cellClicked(int row, int column);
    void on_delete_operator_button_clicked();


    void get_from_op_f(QString FN, QString N1, QString N2, QString ps);
    void on_change_operator_button_clicked();



   void on_SQL_find_server_pushButton_clicked();
   void on_SQL_connect_pushButton_clicked();

   void create_db(QString db_name);
   void drop_db(QString db_name);
   void use_db(QString db_name);
   void on_INTEGRATION_pushButton_clicked();
   void on_BACKUP_pushButton_clicked();




   void on_uType_combobox_activated(const QString &arg1);
   void on_SQL_type_comboBox_currentTextChanged(const QString &arg1);

   void on_INTEGRATION_DevLine_pushButton_clicked();
   void on_pushButton_6_clicked();
   void on_devline_xy_pushButton_clicked();
   void on_uType_combobox_currentTextChanged(const QString &arg1);

   void on_pushButton_3_clicked();
   void on_findButton_reset_clicked();
   void on_findButton_prev_clicked();
   void on_pushButton_next_clicked();
   void on_IU_BL_IP_num_combobox_currentIndexChanged(int index);
   void on_ADAM_Num1_currentIndexChanged(const QString &arg1);
   void on_ADAM_Num2_currentIndexChanged(const QString &arg1);
   void on_TABLO_Num2_currentIndexChanged(const QString &arg1);
   void on_KL_adress_combobox_currentIndexChanged(const QString &arg1);
   void on_KL_CD_combobox_currentIndexChanged(const QString &arg1);
   void on_RLM_C_adress_combobox_currentIndexChanged(const QString &arg1);
   void on_RLM_KRL_adress_combobox_currentIndexChanged(const QString &arg1);
   void on_NET_DEV_IP_combobox_currentTextChanged(const QString &arg1);
   void on_BOD_SOTA_M_adress_combobox_currentIndexChanged(int index);
   void on_U4_Sota_M_combobox_currentIndexChanged(int index);
   void on_DD_Sota_M_combobox_currentIndexChanged(const QString &arg1);
   void on_SSOI_IU_Num1_currentIndexChanged(const QString &arg1);
   void on_SSOI_IU_Num2_currentIndexChanged(const QString &arg1);
   void on_SSOI_IU_Num3_currentTextChanged(const QString &arg1);
   void on_SSOI_SD_Num1_currentIndexChanged(const QString &arg1);
   void on_SSOI_SD_Num2_currentIndexChanged(const QString &arg1);
   void on_SSOI_SD_Num3_currentIndexChanged(const QString &arg1);
   void on_SSOI_SD_OutType_currentIndexChanged(const QString &arg1);
   void on_DEVLINE_Num1_valueChanged(double arg1);
   void on_DEVLINE_OutType_currentIndexChanged(const QString &arg1);
   void on_ONVIF_IPaddr_combobox_currentTextChanged(const QString &arg1);
   void on_STRAZH_IP__IPaddr_combobox_currentTextChanged(const QString &arg1);
   void on_TOROS_Num1_currentIndexChanged(int index);
   void on_BOD_T4K_M_adress_combobox_currentIndexChanged(int index);
   void on_Y4_T4K_M_combobox_currentIndexChanged(int index);
   void on_DD_T4K_M_combobox_currentIndexChanged(int index);
   void on_TG_adress_combobox_currentIndexChanged(int index);
   void on_TG_U4_4A_combobox_currentIndexChanged(int index);
   void on_edit_unit_button_clicked();
   void on_ipadress_combobox_currentTextChanged(const QString &arg1);
   void on_RASTRMTV_Num3_currentIndexChanged(int index);
   void on_RLM_KRL_type_comboBox_currentIndexChanged(const QString &arg1);
   void on_findButton_clicked();
};
#endif // MAINWINDOWCFG_H
