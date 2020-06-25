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

private:
    Ui::MainWindow *ui;

    DataBaseManager *m_dbManager = nullptr;
    TableModelMSG *modelMSG = nullptr;
    QTimer timerUpd;

    QString createCompositFilter();
    QString createDateFilter();
    QString createObjectFilter();



};
#endif // MAINWINDOW_H
