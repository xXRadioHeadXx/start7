#ifndef MAINWINDOWCFG_H
#define MAINWINDOWCFG_H

#include <QMainWindow>
#include <TreeModelUnitNode.h>
#include "map.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowCFG; }
QT_END_NAMESPACE

class MainWindowCFG : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindowCFG *ui;

    TreeModelUnitNode *modelTreeUN = nullptr;

    bool can_i_add_or_not(int type_parrent, int type_child);
    bool add_unit();
    bool delete_unit();

    void get_option(QModelIndex index);

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


    bool set_option(QModelIndex index);

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
    void set_option_DD_SOTA(UnitNode *unit);
    void set_option_BL_IP(UnitNode *unit);



    QString Type_from_int_to_string(int Type);

    int selected_type;

    QModelIndex current_index;

public:
    MainWindowCFG(QWidget *parent = nullptr);
    ~MainWindowCFG();

    bool load(QString patch);

    Map map;

private slots:

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
    void on_UdpUse_checkBox_stateChanged(int arg1);
};
#endif // MAINWINDOWCFG_H
