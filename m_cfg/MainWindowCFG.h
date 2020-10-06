#ifndef MAINWINDOWCFG_H
#define MAINWINDOWCFG_H

#include <QMainWindow>
#include <TreeModelUnitNode.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowCFG; }
QT_END_NAMESPACE

class MainWindowCFG : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindowCFG *ui;

    TreeModelUnitNode *modelTreeUN = nullptr;

    void select_unit(QModelIndex index);
    bool change_unit(QModelIndex index);
    bool add_unit();
    bool delete_unit();


    QString Type_from_int_to_string(int Type);

    int selected_type;

    QModelIndex current_index;

public:
    MainWindowCFG(QWidget *parent = nullptr);
    ~MainWindowCFG();

    bool load(QString patch);

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
};
#endif // MAINWINDOWCFG_H
