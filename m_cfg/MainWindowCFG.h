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
    QString Type_from_int_to_string(int Type);

public:
    MainWindowCFG(QWidget *parent = nullptr);
    ~MainWindowCFG();

    bool load(QString patch);

private slots:

    void on_treeView_clicked(const QModelIndex &index);
};
#endif // MAINWINDOWCFG_H
