#ifndef MAINWINDOWSERVER_H
#define MAINWINDOWSERVER_H

#include <QMainWindow>
//#include <QUdpSocket>
#include <QDebug>
#include <QTableWidget>

#include <TreeModelUnitNode.h>
#include <PortManager.h>
#include <DataBaseManager.h>
#include <TableModelMSG.h>
#include <AuthenticationDialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowServer; }
QT_END_NAMESPACE

class MainWindowServer : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowServer(QWidget *parent = nullptr);
    ~MainWindowServer();
    void setRussian();

//    QTranslator *getRuTranslator() const;

public slots:
    void write();
    void updComboBoxReason();
    void updComboBoxTakenMeasures();
    void updComboBox(QList<QString> lst, QComboBox *cmb);
    void createDiagnosticTable();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_toolButtonReason_clicked();

    void on_toolButtonTakenMeasures_clicked();

    void on_pushButton_clicked();

    void on_pushButtonAlarmReset_clicked();

    void treeUNCustomMenuRequested(QPoint pos);

    void on_actionDK_triggered();

    void startWaitProgressBar(int interval);

    void beatWaitProgressBar();

    void stopWaitProgressBar();


    void on_actionRifDKOverall_triggered();

    void on_actionExpandUNTree_triggered();

    void on_actionCollapseUNTree_triggered();

    void on_actionUNOn_triggered();

    void on_actionUNOff_triggered();

    void on_actionControl_triggered();

    void on_actionTest_triggered();

    void on_actionDiagnostics_triggered();

    void on_actionIncrease_triggered();

    void on_actionReduce_triggered();

    void on_actionNewScheme_triggered();
    void forcedNewDuty(bool out);

    void on_actionOpen_triggered();

    void on_actionClose_triggered();

    void lockOpenClose(bool val);

    void on_actionDataBase_triggered();

    void on_actionUNSqlSelect_triggered();

    void changeSelectUN(UnitNode * un);

    void preparePageCustomization(int typeUN);
    void preparePageRLM(const UnitNode *un);
    void preparePagePoint(int typeUN);
    void preparePageSota1(int typeUN);
    void preparePageSota2(int typeUN);

    void fillPageRLM();
    void fillPagePoint(int typeUN);
    void fillPageSota1(int typeUN);
    void fillPageSota2(int typeUN);

    void on_actionCustomization_triggered();

    void on_pushButton_ReadCustomization_clicked();

    void on_pushButton_WriteCustomization_clicked();

protected:
    void closeEvent(QCloseEvent * event);

//    void resizeEvent(QResizeEvent *e = nullptr) noexcept;

private:
    Ui::MainWindowServer *ui;

    PortManager *m_portManager = nullptr;
    DataBaseManager *m_dbManager = nullptr;
    TableModelMSG *modelMSG = nullptr;
    TreeModelUnitNode *modelTreeUN = nullptr;

    UnitNode * selUN = nullptr;
    QModelIndex selIndex;
    JourEntity selMsg = nullptr;
//    QTranslator *ruTranslator;

    QTimer quasiProgressBeat;
    int waitIntervalProgressBar;
    float wasIntervalProgressBar;

    QList<QPair<int, int> > fontSize = {{8, 18}, {10, 20}, {12, 21}, {14, 29}, {16, 30}, {18, 31}};

    QString unSqlSelect;

    QString getUnSqlSelect() const;
    void setUnSqlSelect(const QString &value);

    void initLabelOperator();
signals:
//    void setTranslator(QTranslator *ts);
//    void resetTranslator(QTranslator *ts);
};

#endif // MAINWINDOWSERVER_H
