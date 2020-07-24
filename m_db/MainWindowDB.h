#ifndef MAINWINDOWDB_H
#define MAINWINDOWDB_H

#include <DataBaseManager.h>
#include <QMainWindow>
#include <TableModelMSG.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowDB; }
QT_END_NAMESPACE

class MainWindowDB : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowDB(QWidget *parent = nullptr);
    ~MainWindowDB();


    QString getCurrentSqlQueryStr() const;

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

    void on_pushButton_4_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindowDB *ui;

    bool blockSignal = true;
    DataBaseManager *m_dbManager = nullptr;
    TableModelMSG *modelMSG = nullptr;
    QTimer timerUpd;
    JourEntity * selMsg = nullptr;
    QString currentSqlQueryStr;

    void setCurrentSqlQueryStr(const QString &value);
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
#endif // MAINWINDOWDB_H
