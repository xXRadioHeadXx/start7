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

private:
    Ui::MainWindow *ui;

    DataBaseManager *m_dbManager = nullptr;
    TableModelMSG *modelMSG = nullptr;
    QTimer timerUpd;

};
#endif // MAINWINDOW_H
