#ifndef MAINWINDOWSERVER_H
#define MAINWINDOWSERVER_H

#include <QMainWindow>
#include "AlarmSwitchOffLogger.h"
//#include <QDebug>
#include <QTableWidget>

#include "ServerTreeModelUnitNode.h"
#include "PortManager.h"
#include "DataBaseManager.h"
#include "ServerTableModelJour.h"
#include "AuthenticationDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowServer; }
QT_END_NAMESPACE

class QLabel;
class MainWindowServer : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowServer(QWidget *parent = nullptr);
    ~MainWindowServer();
    void setRussian();

//    QTranslator *getRuTranslator() const;

    void tuneNeededStateWordTypeSelectedlUN() const;
    void tuneDefaultNeededStateWordTypeSelectedlUN() const;
public slots:
    void write();
    void updComboBoxReason();
    void updComboBoxTakenMeasures();
    void updComboBox(QList<QString> lst, QComboBox *cmb);
    void createDiagnosticTable();

    void fillPageTGAtPointInput(int ci);
private slots:
    void on_treeView_clicked(const QModelIndex &index);

//    void on_tableView_clicked(const QModelIndex &index);

    void on_toolButtonReason_clicked();

    void on_toolButtonTakenMeasures_clicked();

//    void on_pushButton_clicked();

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

    void changeSelectUN(QSharedPointer<UnitNode> un);

    void preparePageCustomization(int typeUN);
    void preparePageRLM(QSharedPointer<UnitNode> un);
    void preparePagePoint(int typeUN);
    void preparePageSota1(int typeUN);
    void preparePageSota2(int typeUN);

    void fillPageRLM();
    void fillPageTG();
    void fillPageSota1(int typeUN);
    void fillPageSota2(int typeUN);

    void on_actionCustomization_triggered();

    void on_pushButton_ReadCustomization_clicked();

    void on_pushButton_WriteCustomization_clicked();

    void verticalScrollBarJourValueChanged(int value);

//    void on_comboBox_RLMEdge_currentIndexChanged(int index);

//    void on_comboBox_RLMCondition_currentIndexChanged(int index);

//    void on_comboBox_RLMTactPeriod_currentIndexChanged(int index);

    void initLabelOperator();

    void updateLabelCount();

    void tableView_repairSelection();
    void tableView_selectionChanged();
    void tableView_saveSelection();

    void changLabelClientCounter(int);
protected:
    void closeEvent(QCloseEvent * event);


//    void resizeEvent(QResizeEvent *e = nullptr) noexcept;

private:
    Ui::MainWindowServer *ui;

    QSharedPointer<QLabel> m_labelClientCounter;

    QSharedPointer<PortManager> m_portManager;
    QSharedPointer<DataBaseManager> m_dbManager;
    QSharedPointer<AlarmSwitchOffLogger> m_alarmSwitchOffLogger;
    QSharedPointer<ServerTableModelJour> modelJour;
    QSharedPointer<ServerTreeModelUnitNode> modelTreeUN;

    QSharedPointer<UnitNode> selUN;
    QModelIndex selIndex;
    JourEntity selMsg;
    QList<JourEntity> listSelMsg;
//    QTranslator *ruTranslator;

    QTimer quasiProgressBeat;
    int waitIntervalProgressBar;
    float wasIntervalProgressBar;

    QList<QPair<int, int> > fontSize = {{8, 18}, {10, 20}, {12, 21}, {14, 29}, {16, 30}, {18, 31}};

    QString unSqlSelect;
    int beginSelectRow = 2147483647, endSelectRow = -1;

    QString getUnSqlSelect() const;
    void setUnSqlSelect(const QString &value);

    int checkNecessarilyReasonMeasureFill();
signals:
//    void setTranslator(QTranslator *ts);
//    void resetTranslator(QTranslator *ts);
};

#endif // MAINWINDOWSERVER_H
