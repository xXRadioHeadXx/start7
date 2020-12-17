#ifndef MAINWINDOWCFG_H
#define MAINWINDOWCFG_H

#include <QMainWindow>
#include <TreeModelUnitNode.h>
#include "map.h"
#include <QErrorMessage>
#include "operator_form.h"
#include <dbform.h>
#include "comport.h"
#include "sqlunit.h"
#include <QHostInfo>
#include <QStandardItem>

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
    Ui::MainWindowCFG *ui;

    QSqlDatabase db_mysql;
    QSqlDatabase db_psql;

    TreeModelUnitNode *modelTreeUN = nullptr;

    QErrorMessage dialog;

    QList<ComPort*> comports;


    QList<Operator*> operators;
    int opt_tbl_request;
    void operator_add(Operator*);
    void operator_edit(Operator*);
    void operator_delete();

    void update_operators_table();

    QString get_unit_name(int type);


    SQLunit MySQL_unit;
    SQLunit Postgre_unit;

    QMenu* menu;

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

    int val_for_setAdamoff;

    int operators_use;


    bool can_i_add_or_not(int type_parrent, int type_child);
    bool pass_to_add(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_SD_BL_IP(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_IU_BL_IP(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_BOD_SOTA(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_Y4_SOTA(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_DD_SOTA(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_BOD_T4K_M(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_Y4_T4K_M(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_DD_T4K_M(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_TG(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_RLM_KRL(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_RLM_C(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_KL(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_ONVIF(UnitNode *unit, UnitNode *parrent);
    bool pass_to_add_STRAZH_IP(UnitNode *unit, UnitNode *parrent);
    bool pass_to_add_NET_DEV(UnitNode *unit, UnitNode *parrent);

    bool add_unit();
    bool change_unit();
    bool delete_unit();

    void show_the_tree();

    void get_option(UnitNode *unit);

    void get_option_GROUP(UnitNode *unit);
    void get_option_SD_BL_IP(UnitNode *unit);
    void get_option_IU_BL_IP(UnitNode *unit);
    void get_option_TG(UnitNode *unit);
    void get_option_RLM_KRL(UnitNode *unit);
    void get_option_RLM_C(UnitNode *unit);
    void get_option_BOD_T4K_M(UnitNode *unit);
    void get_option_Y4_T4K_M(UnitNode *unit);
    void get_option_DD_T4K_M(UnitNode *unit);
    void get_option_BOD_SOTA(UnitNode *unit);
    void get_option_Y4_SOTA(UnitNode *unit);
    void get_option_DD_SOTA(UnitNode *unit);
    void get_option_BL_IP(UnitNode *unit);
    void get_option_KL(UnitNode *unit);
    void get_option_ONVIF(UnitNode *unit);
    void get_option_STRAZH_IP(UnitNode *unit);
    void get_option_NET_DEV(UnitNode *unit);

    void load_other_options_from_ini_file(QString patch);


    void get_PARAMS(QString filename);
    void set_PARAMS(QString filename);
    void default_PARAMS();
    QMap <int,QString> map_PARAMS_PlanType;
    QMap <int,QString> map_PARAMS_SoundType;
    QMap <int,QString> map_PARAMS_AutoStart;

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

    void get_SOLID(QString filename);
    void set_SOLID(QString filename);
    void default_SOLID();

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

    void get_PORT(QString filename);
    void set_PORT(QString filename);
    void default_PORT();

    void get_OPERATORS(QString filename);
    void set_OPERATORS(QString filename);
    void default_OPERATORS();

    void get_ASOOSD(QString filename);
    void set_ASOOSD(QString filename);
    void default_ASOOSD();











    bool set_option(UnitNode *unit,UnitNode *parent);

    void set_option_GROUP(UnitNode *unit);
    void set_option_SD_BL_IP(UnitNode *unit);
    void set_option_IU_BL_IP(UnitNode *unit);
    void set_option_TG(UnitNode *unit);
    void set_option_RLM_KRL(UnitNode *unit);
    void set_option_RLM_C(UnitNode *unit);
    void set_option_BOD_T4K_M(UnitNode *unit);
    void set_option_Y4_T4K_M(UnitNode *unit);
    void set_option_DD_T4K_M(UnitNode *unit,UnitNode *parent);
    void set_option_BOD_SOTA(UnitNode *unit);
    void set_option_Y4_SOTA(UnitNode *unit);
    void set_option_DD_SOTA(UnitNode *unit,UnitNode *parent);
    void set_option_BL_IP(UnitNode *unit);
    void set_option_KL(UnitNode *unit);
    void set_option_ONVIF(UnitNode *unit);
    void set_option_STRAZH_IP(UnitNode *unit);
    void set_option_NET_DEV(UnitNode *unit);



    void save_ini(QString path);
    void save_option(QSettings* settings,UnitNode*  unit);
    void save_option_SD_BL_IP(QSettings* settings,UnitNode*  unit);
    void save_option_BOD_SOTA(QSettings* settings,UnitNode*  unit);

    QString Type_from_int_to_string(int Type);
    int     Type_from_string_to_int(QString Type);

    bool this_name_is_free(QString Name);

    void update_map();

    int selected_type;

    QModelIndex current_index;

    QString str_GROUP;
    QString str_KL;
    QString str_SD_BL_IP;
    QString str_IU_BL_IP;
    QString str_TG;
    QString str_RLM_KRL;
    QString str_RLM_C;
    QString str_BOD_T4K_M;
    QString str_Y4_T4K_M;
    QString str_DD_T4K_M;
    QString str_BOD_SOTA;
    QString str_Y4_SOTA;
    QString str_DD_SOTA;
    QString str_ONVIF;
    QString str_STRAZH_IP;
    QString str_NET_DEV;

    QString str_RIF_RLM;
    QString str_RIF_RLM_24;
    QString str_RIF_RLM_B;
    QString str_RIF_KRL;
    QString str_Razriv;
    QString str_trassa1l;

public:
    MainWindowCFG(QWidget *parent = nullptr);
    ~MainWindowCFG();

    bool load(QString patch);

    Map map;

    operator_form op_f;
    DBform db_f;



private slots:

    void unitNameChanged(QStandardItem*);

    void setDK();
    void YZ_MONOLIT();
    void setAlarmMsgOn();

    void setAdamOff();

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


    void select(QString Name);

    void set_x_y(QString Name,int x,int y);

    void on_treeView_clicked(const QModelIndex &index);
    void on_uType_combobox_currentTextChanged(const QString &arg1);

    void on_pushButton_4_clicked();
    void on_actionCreate_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_treeView_activated(const QModelIndex &index);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_7_clicked();
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
    void on_RifPort_comboBox_currentIndexChanged(int index);
    void on_RifPortSpeed_comboBox_currentTextChanged(const QString &arg1);
    void on_RifPortInterval_doubleSpinBox_valueChanged(const QString &arg1);


   void on_UDP_RS485_combobox_currentTextChanged(const QString &arg1);
   void on_SQL_find_server_pushButton_clicked();
   void on_SQL_connect_pushButton_clicked();

   void create_db(QString db_name);
   void drop_db(QString db_name);
   void use_db(QString db_name);
};
#endif // MAINWINDOWCFG_H
