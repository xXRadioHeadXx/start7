#ifndef MAINWINDOWCFG_H
#define MAINWINDOWCFG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowCFG; }
QT_END_NAMESPACE

class MainWindowCFG : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindowCFG *ui;

public:
    MainWindowCFG(QWidget *parent = nullptr);
    ~MainWindowCFG();

private slots:

};
#endif // MAINWINDOWCFG_H
