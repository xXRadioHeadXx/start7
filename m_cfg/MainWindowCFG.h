#ifndef MAINWINDOWCFG_H
#define MAINWINDOWCFG_H

#include <QMainWindow>
#include <TreeModelUnitNode.h>
#include "map.h"
#include <QErrorMessage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowCFG; }
QT_END_NAMESPACE

class MainWindowCFG : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindowCFG *ui;

    TreeModelUnitNode *modelTreeUN = nullptr;

    QErrorMessage dialog;

    QString get_unit_name(int type);

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


    bool can_i_add_or_not(int type_parrent, int type_child);
    bool pass_to_add(UnitNode *unit, UnitNode* parrent);

    bool pass_to_add_SD_BL_IP(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_IU_BL_IP(UnitNode *unit, UnitNode* parrent);

    bool pass_to_add_BOD_SOTA(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_Y4_SOTA(UnitNode *unit, UnitNode* parrent);
    bool pass_to_add_DD_SOTA(UnitNode *unit, UnitNode* parrent);

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


    bool set_option(UnitNode *unit,UnitNode *parent);

    void set_option_GROUP(UnitNode *unit);
    void set_option_SD_BL_IP(UnitNode *unit);
    void set_option_IU_BL_IP(UnitNode *unit);
    void set_option_TG(UnitNode *unit);
    void set_option_RLM_KRL(UnitNode *unit);
    void set_option_RLM_C(UnitNode *unit);
    void set_option_BOD_T4K_M(UnitNode *unit);
    void set_option_Y4_T4K_M(UnitNode *unit);
    void set_option_DD_T4K_M(UnitNode *unit);
    void set_option_BOD_SOTA(UnitNode *unit);
    void set_option_Y4_SOTA(UnitNode *unit);
    void set_option_DD_SOTA(UnitNode *unit,UnitNode *parent);
    void set_option_BL_IP(UnitNode *unit);




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

public:
    MainWindowCFG(QWidget *parent = nullptr);
    ~MainWindowCFG();

    bool load(QString patch);

    Map map;

private slots:

    void setDK();
    void YZ_MONOLIT();
    void setAlarmMsgOn();

    void setAdamOff();


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
    void on_BOD_SOTA_M_type_combobox_currentTextChanged(const QString &arg1);
    void on_pushButton_9_clicked();
    void on_pushButton_moveUp_clicked();
    void on_pushButton_moveDown_clicked();
    void on_SD_BL_IP_UDP_RS485_combobox_currentTextChanged(const QString &arg1);
    void on_treeView_customContextMenuRequested(const QPoint &pos);
    void on_IU_BL_IP_UDP_RS485_combobox_currentTextChanged(const QString &arg1);
};
#endif // MAINWINDOWCFG_H
