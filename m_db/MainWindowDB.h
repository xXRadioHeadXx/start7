#ifndef MAINWINDOWDB_H
#define MAINWINDOWDB_H

#include "DataBaseManager.h"
#include <QMainWindow>
#include "ServerTableModelJour.h"

#include "GraphTerminal.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowDB; }
QT_END_NAMESPACE

class MainWindowDB : public QMainWindow
{
    Q_OBJECT

private:
    QTimer beforeConstructotTimer;

    QString cmbStyleSheet =
            " QComboBox{ "
                " background: white; "
                " color: black; "
                " border-style: outset; "
                " border-width: 1px; "
                " border-radius: 2px; "
                " border-color: black; "
                " selection-color: black;"
            " } ";
    QString deStyleSheet =
            " QDateEdit{ "
                " background: white; "
                " color: black; "
                " border-style: outset; "
                " border-width: 1px; "
                " border-radius: 2px; "
                " border-color: black; "
            "} ";
    QString lvStyleSheet =
            " QListView::item{ "
                " height: 16px; "
            " } ";

    QSharedPointer<QValidator> regExpValidator255;
    QSharedPointer<QValidator> regExpValidator0_255;
    QSharedPointer<QValidator> regExpValidator1_225;
    QSharedPointer<QValidator> regExpValidator1_255;
    QSharedPointer<QValidator> regExpValidator1_3;
    QSharedPointer<QValidator> regExpValidator1_4;
    QSharedPointer<QValidator> regExpValidator0_7;
    QSharedPointer<QValidator> regExpValidator1_8;
    QSharedPointer<QValidator> regExpValidator1_8v;
    QSharedPointer<QValidator> regExpValidator1_26;
    QSharedPointer<QValidator> regExpValidator1_99;
    QSharedPointer<QValidator> regExpValidator1_100;
    QSharedPointer<QValidator> regExpValidatorIP;
    QSharedPointer<QValidator> regExpValidatorSSOIIU;

    QList<QPair<QString, int>> listCmbData0_255;
    QList<QPair<QString, int>> listCmbData1_225;
    QList<QPair<QString, int>> listCmbData1_255;
    QList<QPair<QString, int>> listCmbData1_3;
    QList<QPair<QString, int>> listCmbData1_4;
    QList<QPair<QString, int>> listCmbData0_7;
    QList<QPair<QString, int>> listCmbData1_8;
    QList<QPair<QString, int>> listCmbData1_8v;
    QList<QPair<QString, int>> listCmbData1_26;
    QList<QPair<QString, int>> listCmbData1_99;
    QList<QPair<QString, int>> listCmbData1_100;
    QList<QPair<QString, int>> listCmbDataSSOIIU;

   void applyStyleSheet();
   void initialiseValidators();
   void initialiseListCMB();

   void currentBLIPSDTypeUnitNode();
   void currentBLIPUZMonolitTypeUnitNode();
   void currentBLIPIUTypeUnitNode();
   void currentBLIPSSOISDTypeUnitNode();
   void currentBLIPSSOIIUTypeUnitNode();
   void currentKLTypeUnitNode();
   void currentTGTypeUnitNode();
   void currentRLMKRLTypeUnitNode();
   void currentRLMCTypeUnitNode();
   void currentBODT4KMTypeUnitNode();
   void currentY4T4KMTypeUnitNode();
   void currentDDT4KMTypeUnitNode();
   void currentBODSOTATypeUnitNode();
   void currentY4SOTATypeUnitNode();
   void currentDDSOTATypeUnitNode();
   void currentSSOISDTypeUnitNode();
   void currentSSOIIUTypeUnitNode();
   void currentADAMTypeUnitNode();
   void currentTorosTypeUnitNode();
   void currentDefaultTypeUnitNode();

   void initilaseCmbList(QComboBox *cmb, const QList<QPair<QString, int>> &list);
   void initilaseCmbValidator(QComboBox *cmb, const QSharedPointer<QValidator> &validator);
   void initilaseCmbValidator(QComboBox *cmb, QValidator const * validator);



public:
    MainWindowDB(QWidget *parent = nullptr);
    ~MainWindowDB();

    void setFromArgMap();

    QString getCurrentSqlQueryStr() const;

    void updSqlQueryStr(QString sql);

private slots:
    void beforeConstructot();

    void comboBox_TypeUN_currentIndexChanged(int index);

    void comboBox_TypeSearch_currentIndexChanged(int index);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void updateListRecords();

    void pushButton_UpdSelections_clicked();

    void on_toolButtonAddReason_clicked();

    void on_toolButtonAddTakenMeasures_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_toolButtonRemoveReason_clicked();

    void on_toolButtonRemoveTakenMeasures_clicked();

    void on_action_triggered();

    void on_pushButton_4_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void comboBox_IPAddress_editTextChanged(const QString &arg1);

private:
    Ui::MainWindowDB *ui;

    bool blockSignal = true;
    QSharedPointer<DataBaseManager> m_dbManager;
    QSharedPointer<ServerTableModelJour> modelJour = nullptr;
    QTimer timerUpd;
    JourEntity selMsg;
    QString currentSqlQueryStr;
    static QSharedPointer<GraphTerminal> graphTerminal;

    void setCurrentSqlQueryStr(const QString &value);
    QString createCompositFilter();
    QString createDateFilter();
    QString createObjectFilter();
    QString createEventFilter();
    QString createDirectionFilter();
    QString createNum1Filter();
    QString createNum2Filter();
    QString createNum3Filter();
    QString createOutFilter();
    QString createAdamOffFilter();
    bool getBlockSignal() const;
    void setBlockSignal(bool value);
    void updComboBoxReason();
    void updComboBoxTakenMeasures();
    void updComboBoxAddress();
    void updComboBoxNum1();
    void updComboBoxNum2();
    void updComboBoxNum3();
    void updComboBox(QList<QString> lst, QComboBox * cmb);
    static QSharedPointer<GraphTerminal> loadPortsTcpGraphTerminal(QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

    void signalSotConnect();
};
#endif // MAINWINDOWDB_H
