#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DataBaseManager.h>
#include <QMainWindow>
#include <TableModelMSG.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void updateListRecords();

    void on_pushButton_clicked();

    void on_toolButtonAddReason_clicked();

    void on_toolButtonAddTakenMeasures_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_toolButtonRemoveReason_clicked();

    void on_toolButtonRemoveTakenMeasures_clicked();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;

    bool blockSignal = true;
    DataBaseManager *m_dbManager = nullptr;
    TableModelMSG *modelMSG = nullptr;
    QTimer timerUpd;
    JourEntity * selMsg = nullptr;

    QString createCompositFilter();
    QString createDateFilter();
    QString createObjectFilter();
    QString createEventFilter();
    bool getBlockSignal() const;
    void setBlockSignal(bool value);
    void updComboBoxReason();
    void updComboBoxTakenMeasures();
    void updComboBox(QList<QString> lst, QComboBox * cmb);

};
#endif // MAINWINDOW_H
