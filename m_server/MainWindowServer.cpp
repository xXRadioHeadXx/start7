#include "MainWindowServer.h"
#include "ui_MainWindowServer.h"

#include <ComboBoxDelegate.h>
#include <QCloseEvent>
#include <QMessageBox>
#include <QNetworkDatagram>
#include <QTimer>

#include <Port.h>
#include <SignalSlotCommutator.h>
#include <Utils.h>
#include <ServerSettingUtils.h>
#include <global.h>

#include <SWPRLM.h>
#include <SWPRLMC.h>
#include <SWPSDBLIP.h>
#include <SWPIUBLIP.h>
#include <SWPTGType0x31.h>
#include <ServerTableModelJour.h>
#include <QScrollBar>
#include "SWPTGSubType0x34.h"
#include "SWPTGType0x34.h"

MainWindowServer::MainWindowServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowServer)
{
    ui->setupUi(this);

    QString buildPrefix = "";

#ifdef QT_DEBUG
    buildPrefix = "b";
#else
    buildPrefix = "r";
#endif

    QDate date = QLocale(QLocale::C).toDate(QString(__DATE__).simplified(), QLatin1String("MMM d yyyy"));
    this->setWindowTitle(tr("Сервер") + " - " + buildPrefix + date.toString("dd.MM.yyyy"));

//    this->ruTranslator = new QTranslator(this);
//    this->ruTranslator->load("app_ru");

    ui->actionDataBase->setShortcut(QKeySequence("F3"));
    ui->actionSoundReset->setShortcut(QKeySequence("Esc"));
    ui->actionControl->setShortcut(QKeySequence("Ins"));//Qt::Key_Insert));

    m_dbManager = QSharedPointer<DataBaseManager>::create(this);

    m_alarmSwitchOffLogger = QSharedPointer<AlarmSwitchOffLogger>::create(this);

    DataBaseManager::setIdStartLastDuty();

    this->modelJour = QSharedPointer<ServerTableModelJour>::create(this);
    ui->tableView->setModel(modelJour.data());
    connect(this->modelJour.data(),
            SIGNAL(needScrollToBottom()),
            ui->tableView,
            SLOT(scrollToBottom()));

    modelTreeUN = QSharedPointer<ServerTreeModelUnitNode>::create(this);
    modelJour->setFont(ui->tableView->font());

    connect(ui->tableView->verticalScrollBar(),
            SIGNAL(valueChanged(int)),
            this,
            SLOT(verticalScrollBarJourValueChanged(int)));

    ui->treeView->setModel(modelTreeUN.data());

    this->modelTreeUN->createProxySortTree();

    DataBaseManager::setIdStartLastDuty();

    JourEntity msg;
    msg.setObject(tr("Оператор"));
    msg.setType(900);
    msg.setComment(tr("Программа запущена"));
    DataBaseManager::insertJourMsg(msg);

    modelJour->updateAllRecords();

    updComboBoxReason();
    updComboBoxTakenMeasures();

    ui->tableView->setItemDelegateForColumn(4, new ComboBoxDelegate("reason", this));
    ui->tableView->setItemDelegateForColumn(5, new ComboBoxDelegate("measures", this));

    m_portManager = QSharedPointer<PortManager>::create(m_dbManager, this);
    m_portManager->loadSettings();
//    preparePort("192.168.0.250", "4001", 0);
//    m_portManager->open(0);

    createDiagnosticTable();

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(updDataTreeUN()),
            this,
            SLOT(createDiagnosticTable()));

    connect(ui->treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeUNCustomMenuRequested(QPoint)));

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(startDKWait(int)),
            this,
            SLOT(startWaitProgressBar(int)));
    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(stopDKWait()),
            this,
            SLOT(stopWaitProgressBar()));
    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(endDKWait()),
            this,
            SLOT(stopWaitProgressBar()));

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(startLockWait(int)),
            this,
            SLOT(startWaitProgressBar(int)));
    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(stopLockWait()),
            this,
            SLOT(stopWaitProgressBar()));
    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(endLockWait()),
            this,
            SLOT(stopWaitProgressBar()));

    stopWaitProgressBar();
    connect(&quasiProgressBeat,
            SIGNAL(timeout()),
            this,
            SLOT(beatWaitProgressBar()));

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(changeSelectUN(QSharedPointer<UnitNode> )),
            this,
            SLOT(changeSelectUN(QSharedPointer<UnitNode> )));
    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(forcedNewDuty(bool)),
            this,
            SLOT(forcedNewDuty(bool)));

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(updateLabelOperator()),
            this,
            SLOT(initLabelOperator()));

    ui->treeView->resizeColumnToContents(0);

    ui->tableView->resizeColumnToContents(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    ui->tableView->resizeColumnToContents(3);
    ui->tableView->resizeColumnToContents(4);
    ui->tableView->resizeColumnToContents(5);
    ui->tableView->resizeColumnToContents(6);

    m_portManager->startStatusRequest();

    initLabelOperator();

    GraphTerminal::sendAbonentEventsAndStates(msg);

    preparePageCustomization(-1);

    m_alarmSwitchOffLogger->start();
}

MainWindowServer::~MainWindowServer()
{
    on_pushButtonAlarmReset_clicked();

    JourEntity msg;
    msg.setObject(tr("Оператор"));
    msg.setType(901);
    msg.setComment(tr("Программа остановлена"));
    DataBaseManager::insertJourMsg(msg);
    GraphTerminal::sendAbonentEventsAndStates(msg);

    delete ui;
}

void MainWindowServer::write()
{

    this->on_actionIncrease_triggered();

    return;

    m_portManager->startStatusRequest();
    return;

    QByteArray Data;
    Data.append(static_cast<quint8>(0xB5));
    Data.append(static_cast<quint8>(0xFF));
    Data.append(static_cast<char>(0x00));
    Data.append(static_cast<quint8>(0x22));
    Data.append(static_cast<quint8>(0x21));

    DataQueueItem itm(Data, QHostAddress("192.168.0.254"), 4001, 0);

    m_portManager->pushOverallWriteQueue(itm);
    m_portManager->write();
}

void MainWindowServer::updComboBoxReason() {
    updComboBox(DataBaseManager::getReasonGroup(), ui->comboBoxReason);
}

void MainWindowServer::updComboBoxTakenMeasures() {
    updComboBox(DataBaseManager::getMeasuresGroup(), ui->comboBoxTakenMeasures);
}

void MainWindowServer::updComboBox(QList<QString> lst, QComboBox * cmb) {
    cmb->clear();
    cmb->addItems(lst);
    cmb->setCurrentIndex(-1);
}

void MainWindowServer::tuneDefaultNeededStateWordTypeSelectedlUN() const {
    if(!selUN.isNull()) {
        if(TypeUnitNode::TG == selUN->getType() ||
           TypeUnitNode::SD_BL_IP == selUN->getType() ||
           TypeUnitNode::IU_BL_IP == selUN->getType()) {
            if(!selUN->getParentUN().isNull()) {
                selUN->getParentUN()->setNeededStateWordType(selUN->getParentUN()->getDefaultNeededStateWordType());
                selUN->getParentUN()->leftoversCounter.counter = 0;
                selUN->getParentUN()->leftoversCounter.divider = 1;
            }
        }
        selUN->setNeededStateWordType(selUN->getDefaultNeededStateWordType());
        selUN->leftoversCounter.counter = 0;
        selUN->leftoversCounter.divider = 1;
    }
}


void MainWindowServer::tuneNeededStateWordTypeSelectedlUN() const {
    if(!selUN.isNull()) {
        if(TypeUnitNode::TG == selUN->getType() ||
           TypeUnitNode::SD_BL_IP == selUN->getType() ||
           TypeUnitNode::IU_BL_IP == selUN->getType()) {
            if(!selUN->getParentUN().isNull()) {
                if(TypeUnitNode::TG_Base == selUN->getParentUN()->getType()) {
                    if(ui->groupBox_Customization->isVisible() && ui->groupBox_Diagnostics->isVisible()) { // настройка диагностика
                        selUN->getParentUN()->setNeededStateWordType(0x2A2C2E);
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 3;
                    } else if(ui->groupBox_Customization->isVisible() && !ui->groupBox_Diagnostics->isVisible()) { // настройка
                        selUN->getParentUN()->setNeededStateWordType(0x2C2E);
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 2;
                    } else if(!ui->groupBox_Customization->isVisible() && ui->groupBox_Diagnostics->isVisible()) { // диагностика
                        selUN->getParentUN()->setNeededStateWordType(/*0x2A2E*/0x2A2C2E);
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 2;
                    } else if(!ui->groupBox_Customization->isVisible() && !ui->groupBox_Diagnostics->isVisible()) { //
                        selUN->getParentUN()->setNeededStateWordType(selUN->getParentUN()->getDefaultNeededStateWordType());
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 1;
                    } else {
                        selUN->getParentUN()->setNeededStateWordType(selUN->getParentUN()->getDefaultNeededStateWordType());
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 1;
                    }

                } else if(TypeUnitNode::BL_IP == selUN->getParentUN()->getType()) {
                    selUN->getParentUN()->setNeededStateWordType(selUN->getParentUN()->getDefaultNeededStateWordType());
                    selUN->getParentUN()->leftoversCounter.counter = 0;
                    selUN->getParentUN()->leftoversCounter.divider = 1;
                } else {
                    selUN->getParentUN()->setNeededStateWordType(selUN->getParentUN()->getDefaultNeededStateWordType());
                    selUN->getParentUN()->leftoversCounter.counter = 0;
                    selUN->getParentUN()->leftoversCounter.divider = 1;
                }
            }
        } else if(TypeUnitNode::RLM_C == selUN->getType() ||
                  TypeUnitNode::RLM_KRL == selUN->getType()) {
            selUN->setNeededStateWordType(selUN->getDefaultNeededStateWordType());
            selUN->leftoversCounter.counter = 0;
            selUN->leftoversCounter.divider = 1;
        } else {
            selUN->setNeededStateWordType(selUN->getDefaultNeededStateWordType());
            selUN->leftoversCounter.counter = 0;
            selUN->leftoversCounter.divider = 1;
        }
    }
}

void MainWindowServer::on_treeView_clicked(const QModelIndex &index)
{
    QSharedPointer<UnitNode>  sel = this->modelTreeUN->clickedUN(index);

    if(nullptr == sel) {
        ui->labelSelectedUN->clear();
        ui->labelSelectedUN->setVisible(false);
        return;
    }

    tuneDefaultNeededStateWordTypeSelectedlUN();
    selUN = sel;
    selIndex = index;

    tuneNeededStateWordTypeSelectedlUN();

    createDiagnosticTable();
    preparePageCustomization(selUN->getType());

    if(TypeUnitNode::GROUP == selUN->getType()) {
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getType()) + ": \"" + sel->getName() + "\"");
    } else if(TypeUnitNode::SD_BL_IP == selUN->getType() && 1 == selUN->getBazalt()) {//БЛ-IP УЗ: СД:{Num2} + ИУ:{Num2} Кан:{UdpAdress}::{UdpPort}
        ui->labelSelectedUN->setText(QString("БЛ-IP УЗ: СД:%1 + ИУ:%1").arg(sel->getNum2()) + " " + "Кан:" + sel->getUdpAdress() + "::" + QVariant(sel->getUdpPort()).toString());
    } else if(TypeUnitNode::SD_BL_IP == selUN->getType()) {
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getParentUN()->getType()) + " " + "Кан:" + sel->getUdpAdress() + "::" + QVariant(sel->getUdpPort()).toString() + " " + Utils::typeUNToStr(sel->getType()) + ":" + QVariant(sel->getNum2()).toString());
    } else if(TypeUnitNode::IU_BL_IP == selUN->getType()) {
        auto setUN = Utils::findeSetAutoOnOffUN(selUN);
        QString subStr;
        if(!setUN.isEmpty()) {
            subStr.append("(Авто %1с.)");
            subStr = subStr.arg(UnitNodeCFG::adamOffToMs(setUN.values().first()->getAdamOff()) / 1000);
        }
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getParentUN()->getType()) + " " + "Кан:" + sel->getUdpAdress() + "::" + QVariant(sel->getUdpPort()).toString() + " " + Utils::typeUNToStr(sel->getType()) + ":" + QVariant(sel->getNum2()).toString() + " " + subStr);
    } else
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getType()) + "\t" + sel->getName());
    ui->labelSelectedUN->setVisible(true);

}

void MainWindowServer::on_tableView_clicked(const QModelIndex &index)
{
    JourEntity sel = this->modelJour->clickedMsg(index);

    if(0 == sel.getId()) {
        ui->comboBoxReason->setCurrentIndex(-1);
        ui->comboBoxTakenMeasures->setCurrentIndex(-1);
        return;
    }

    selMsg = sel;

    if(sel.getReason().isEmpty() ) {
        ui->comboBoxReason->setCurrentIndex(-1);
    } else {
        ui->comboBoxReason->setEditText(sel.getReason());
    }

    if(sel.getMeasures().isEmpty()) {
        ui->comboBoxTakenMeasures->setCurrentIndex(-1);
    } else {
        ui->comboBoxTakenMeasures->setEditText(sel.getMeasures());
    }

    GraphTerminal::sendAbonentEventBook(sel);
}

void MainWindowServer::on_toolButtonReason_clicked()
{
    if(0 == selMsg.getId()) {
        return;
    }

    selMsg.setReason(ui->comboBoxReason->currentText());
    DataBaseManager::updateJourMsg_wS(selMsg);
    updComboBoxReason();
}

void MainWindowServer::on_toolButtonTakenMeasures_clicked()
{
    if(0 == selMsg.getId()) {
        return;
    }

    selMsg.setMeasures(ui->comboBoxTakenMeasures->currentText());
    DataBaseManager::updateJourMsg_wS(selMsg);
    updComboBoxTakenMeasures();
}

//QTranslator *MainWindowServer::getRuTranslator() const
//{
//    return ruTranslator;
//}

//void MainWindowServer::setRussian() /*noexcept*/
//{
//    emit this->setTranslator(ruTranslator);
//    ui->retranslateUi(this);
//}

//void MainWindowServer::on_pushButton_clicked()
//{
//    createDiagnosticTable();

//    write();
//}

void MainWindowServer::createDiagnosticTable()
{
    if(nullptr == this->selUN)
        ui->actionDiagnostics->setChecked(false);

    ui->groupBox_Diagnostics->setVisible(ui->actionDiagnostics->isChecked());

    if(!ui->groupBox_Diagnostics->isVisible())
        return;

    if(nullptr == this->selUN)
        return;

    if(TypeUnitNode::IU_BL_IP == selUN->getType() ||
            TypeUnitNode::SD_BL_IP == selUN->getType() ||
            TypeUnitNode::RLM_KRL == selUN->getType() ||
            TypeUnitNode::RLM_C == selUN->getType() ||
            TypeUnitNode::TG == selUN->getType() ||
            TypeUnitNode::DD_T4K_M == selUN->getType() ||
            TypeUnitNode::DD_SOTA == selUN->getType() ||
            TypeUnitNode::Y4_SOTA == selUN->getType() ||
            TypeUnitNode::BOD_SOTA == selUN->getType() ||
            TypeUnitNode::BOD_T4K_M == selUN->getType() ||
            TypeUnitNode::Y4_T4K_M == selUN->getType())
        ui->groupBox_Diagnostics->setVisible(true);
    else
        ui->groupBox_Diagnostics->setVisible(false);

    if(!ui->groupBox_Diagnostics->isVisible())
        return;

//    ui->tableWidget->clear();
    ui->tableWidget_Diagnostic->verticalHeader()->hide();
    ui->tableWidget_Diagnostic->horizontalHeader()->hide();

    if(TypeUnitNode::RLM_KRL == selUN->getType())
        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: РИФ-РЛМ(КРП),Трасса"));
    else if(TypeUnitNode::RLM_C == selUN->getType())
        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: РИФ-РЛМ-С"));
    else if(TypeUnitNode::TG == selUN->getType()) {
        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: Точка/Гарда"));
    } else if(TypeUnitNode::DD_SOTA == selUN->getType() || TypeUnitNode::DD_T4K_M == selUN->getType())
        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: ДД Точка-М/Гарда, ДД Сота"));
    else if(TypeUnitNode::Y4_SOTA == selUN->getType() || TypeUnitNode::BOD_SOTA == selUN->getType())
        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: Сота/Сота-М"));
    else if(TypeUnitNode::BOD_T4K_M == selUN->getType() || TypeUnitNode::Y4_T4K_M == selUN->getType())
        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: Точка-М/Гарда-М"));
    else if(TypeUnitNode::SD_BL_IP == selUN->getType() || TypeUnitNode::IU_BL_IP == selUN->getType())
        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: БЛ-IP"));

    Utils::fillDiagnosticTable(ui->tableWidget_Diagnostic, this->selUN);

    auto contentSize = Utils::getQTableWidgetContentSize(ui->tableWidget_Diagnostic);
    ui->tableWidget_Diagnostic->setMaximumHeight(contentSize.height());
}

void MainWindowServer::on_pushButtonAlarmReset_clicked()
{
    this->m_portManager->requestAlarmReset();
    {
        JourEntity msgOn;
        msgOn.setObject(tr("Оператор"));
        msgOn.setType(135);
        msgOn.setComment(tr("Послана ком. Сброс тревог"));
        DataBaseManager::insertJourMsg_wS(msgOn);
        GraphTerminal::sendAbonentEventsAndStates(msgOn);
    }

    DataBaseManager::resetAllFlags_wS();

    {
        JourEntity msgOn;
        msgOn.setObject(tr("Оператор"));
        msgOn.setType(903);
        msgOn.setComment(tr("Выполнен сброс тревог"));
        msgOn.setFlag(0);
        DataBaseManager::insertJourMsg_wS(msgOn);
        GraphTerminal::sendAbonentEventsAndStates(msgOn);
    }
}

void MainWindowServer::treeUNCustomMenuRequested(QPoint pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
    if (!index.isValid()) {
        this->selUN = nullptr;
        selIndex = QModelIndex();
        return;
    }
    QSharedPointer<UnitNode>  sel = this->modelTreeUN->clickedUN(index);
    if(nullptr == sel)
        return;

    this->selUN = sel;
    selIndex = index;

    /* Create an object context menu */
    QMenu * menu = new QMenu(ui->treeView);
    /* Set the actions to the menu */

//        menu->addAction(ui->actionTest);

    if(sel->treeChildCount()) {
        if(!ui->treeView->isExpanded(selIndex) || selUN->getMetaNames().contains("Obj_0"))
            menu->addAction(ui->actionExpandUNTree);
        if(ui->treeView->isExpanded(selIndex) || selUN->getMetaNames().contains("Obj_0"))
            menu->addAction(ui->actionCollapseUNTree);
    }

    bool isDebug;
#ifdef QT_DEBUG
    isDebug = true;
#else
    isDebug = false;
#endif

    if(selUN.isNull()) {
        return;
    } else if(TypeUnitNode::SD_BL_IP == sel->getType()) {

        if(sel->isEditableControl() && 1 != sel->getBazalt()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
        } else if(sel->isEditableOnOff() && 1 == sel->swpSDBLIP().isOn() && 1 != sel->getBazalt()) {
            menu->addAction(ui->actionUNOff);
        } else if(sel->isEditableOnOff() && 1 == sel->swpSDBLIP().isOff() && 1 != sel->getBazalt()) {
            menu->addAction(ui->actionUNOn);
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionClose);
            menu->addAction(ui->actionOpen);
            menu->addSeparator();
        } else if(0 != sel->getBazalt() && (1 == sel->swpSDBLIP().isAlarm())) {
            menu->addAction(ui->actionClose);
            menu->addSeparator();
        } else if(0 != sel->getBazalt() && (1 == sel->swpSDBLIP().isNorm())) {
            menu->addAction(ui->actionOpen);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        } else if(0 == sel->getBazalt() && 0 != sel->getDK()) {
            menu->addAction(ui->actionDK);
        }

    } else if(TypeUnitNode::IU_BL_IP == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpIUBLIP().isOn())) {
            menu->addAction(ui->actionUNOff);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpIUBLIP().isOff())) {
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        } else if(0 == sel->getBazalt() && 0 != sel->getDK()) {
            menu->addAction(ui->actionDK);
        }

    } else if(TypeUnitNode::RLM_C == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpRLMC().isOn())) {
            menu->addAction(ui->actionUNOff);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpRLMC().isOff())) {
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        }

        if(0 == sel->getBazalt() && 0 != sel->getDK()) {
            menu->addAction(ui->actionDK);
        } else if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        }

    } else if(TypeUnitNode::RLM_KRL == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpRLM().isOn())) {
            menu->addAction(ui->actionUNOff);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpRLM().isOff())) {
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        } else if(0 == sel->getBazalt() && 0 != sel->getDK()) {
            menu->addAction(ui->actionDK);
        }

    } else if(TypeUnitNode::TG == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        }/* else if(sel->isEditableOnOff() && (1 == sel->swpTGType0x31().isOn())) {
            menu->addAction(ui->actionUNOff);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpTGType0x31().isOff())) {
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        }*/

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        } else if(0 == sel->getBazalt() && 0 != sel->getDK()) {
            menu->addAction(ui->actionDK);
        }

    }

    if(!sel->getName().isEmpty() && !(TypeUnitNode::SYSTEM == sel->getType() || TypeUnitNode::GROUP == sel->getType())) {
        menu->addAction(ui->actionUNSqlSelect);
        setUnSqlSelect(QString("SELECT id, cdate, mdate, objectid, object, comment, reason, measures, operator, operatorid, status, direction, type, flag, d1, d2, d3, d4, objecttype FROM public.jour where object = \'%1\' ORDER BY id").arg(sel->getName()));
    }

    /* Call the context menu */
//        menu->popup(ui->treeView->viewport()->mapToGlobal(pos));


    menu->exec(ui->treeView->viewport()->mapToGlobal(pos));
}

void MainWindowServer::on_actionDK_triggered()
{
    this->m_portManager->requestDK(this->selUN);
}

void MainWindowServer::stopWaitProgressBar()
{
    quasiProgressBeat.stop();
    ui->progressBarDKWait->setValue(0);
    waitIntervalProgressBar = 0;
    wasIntervalProgressBar = 0.0;
    ui->progressBarDKWait->setVisible(false);
}

void MainWindowServer::beatWaitProgressBar()
{
    wasIntervalProgressBar += 100.0;
    float val = (( wasIntervalProgressBar / (float)waitIntervalProgressBar) * 100.0);
    ui->progressBarDKWait->setValue((int)val % 101);
    if(100 == ui->progressBarDKWait->value() || 0 == ui->progressBarDKWait->value())
        ui->progressBarDKWait->setVisible(false);
    else
        ui->progressBarDKWait->setVisible(true);
}

void MainWindowServer::startWaitProgressBar(int interval)
{
    stopWaitProgressBar();
    waitIntervalProgressBar = interval;
    wasIntervalProgressBar = 0.0;
    quasiProgressBeat.start(100);
    ui->progressBarDKWait->setVisible(false);
}

void MainWindowServer::on_actionRifDKOverall_triggered()
{
    this->m_portManager->requestDK();
}

void MainWindowServer::on_actionExpandUNTree_triggered()
{
    if(selUN.isNull())
        return;

    QModelIndex index = selIndex;

    if(selUN->getMetaNames().contains("Obj_0")) {
        ui->treeView->expandAll();
        return;
    } else if(index.isValid() && 0 != selUN->treeChildCount())
        ui->treeView->expand(index);
}

void MainWindowServer::on_actionCollapseUNTree_triggered()
{
    if(selUN.isNull())
        return;

    QModelIndex index = selIndex;

    if(selUN->getMetaNames().contains("Obj_0")) {
        ui->treeView->collapseAll();
        return;
    } else if(index.isValid() && 0 != selUN->treeChildCount())
        ui->treeView->collapse(index);
}

void MainWindowServer::on_actionUNOn_triggered()
{
    if(selUN.isNull())
        return;

    const auto& setUn = Utils::findeSetAutoOnOffUN(selUN);
    if(setUn.isEmpty())
        this->m_portManager->requestOnOffCommand(false, selUN, true);
    else
        this->m_portManager->requestAutoOnOffIUCommand(false, setUn.values().first());
}

void MainWindowServer::on_actionUNOff_triggered()
{
    if(selUN.isNull())
        return;
    if(TypeUnitNode::RLM_C == selUN->getType() ||
       TypeUnitNode::RLM_KRL == selUN->getType() ||
       TypeUnitNode::TG == selUN->getType()) {
        int ret = QMessageBox::question(this, tr("Предупреждение"),
                                       tr("Вы действительно хотите отключить устройство?"),
                                       QMessageBox::Ok | QMessageBox::Cancel,
                                       QMessageBox::Ok);

        if(QMessageBox::Ok != ret) {
            return;
        }
    }
    this->m_portManager->requestOnOffCommand(false, selUN, false);
}

void MainWindowServer::on_actionControl_triggered()
{
    if(selUN.isNull())
        return;


    if(!selUN->isEditableControl())
        return;

    QString strQuestion;
    if(selUN->getControl())
        strQuestion = tr("Убрать контроль?");
    else
        strQuestion = tr("Восстановить контроль?");

    int ret = QMessageBox::question(this, tr("Предупреждение"),
                                   strQuestion,
                                   QMessageBox::Ok | QMessageBox::Cancel,
                                   QMessageBox::Ok);

    if(QMessageBox::Ok == ret) {
        selUN->setControl(!selUN->getControl());

        JourEntity msgOn;
        msgOn.setObject(selUN->getName());
        msgOn.setObjecttype(selUN->getType());
        msgOn.setD1(selUN->getNum1());
        msgOn.setD2(selUN->getNum2());
        msgOn.setD3(selUN->getNum3());
        msgOn.setDirection(selUN->getUdpAdress());
        msgOn.setType((selUN->getControl() ? 137 : 136));
        msgOn.setComment(tr("Контроль ") + (selUN->getControl() ? tr("Вкл") : tr("Выкл")));
        DataBaseManager::insertJourMsg_wS(msgOn);
        GraphTerminal::sendAbonentEventsAndStates(selUN, msgOn);

//        if(selUN->getControl()) {
//            selUN->setStatus1(Status::Uncnown);
//            selUN->setStatus2(Status::Uncnown);
//        }
//        if(selUN->getControl())
//            GraphTerminal::sendAbonentEventsAndStates(selUN);
    }
}

void MainWindowServer::closeEvent(QCloseEvent * event)
{
    int ret = QMessageBox::warning(this, tr("Предупреждение"),
                                   tr("Завершить работу и выйти из программы?"),
                                   QMessageBox::Ok | QMessageBox::Cancel,
                                   QMessageBox::Ok);

    if(QMessageBox::Ok == ret) {
        event->accept();
    } else {
        event->ignore();
    }
    //Здесь код
}

QString MainWindowServer::getUnSqlSelect() const
{
    return unSqlSelect;
}

void MainWindowServer::setUnSqlSelect(const QString &value)
{
    unSqlSelect = value;
}

void MainWindowServer::initLabelOperator()
{
    if(Operator::getApprovedOperator().isNull()) {
        ui->labelOperator->clear();
        ui->labelOperator->setVisible(false);
    } else {
        ui->labelOperator->clear();
        ui->labelOperator->setVisible(true);
        ui->labelOperator->setText(tr("Оператор") + ": " + Operator::getApprovedOperator().getOperatorLableText());
    }
}

void MainWindowServer::on_actionTest_triggered()
{
    if(selUN.isNull())
        return;
    Utils::findeSetAutoOnOffUN(selUN);
}

void MainWindowServer::on_actionDiagnostics_triggered()
{
    createDiagnosticTable();

    tuneNeededStateWordTypeSelectedlUN();
}

void MainWindowServer::on_actionIncrease_triggered()
{
    QFont font = modelJour->getFont();
    int currentIndexFont = 0;

    for(int n = fontSize.size(); currentIndexFont < n; currentIndexFont++)
        if(font.pointSize() == fontSize.at(currentIndexFont).first)
            break;

    if(currentIndexFont + 1 >= fontSize.size())
        return;

    font.setPointSize(fontSize.at(currentIndexFont + 1).first);
    modelJour->setFont(font);

    ui->tableView->verticalHeader()->setMinimumHeight(fontSize.at(currentIndexFont + 1).second);
    ui->tableView->verticalHeader()->setDefaultSectionSize(fontSize.at(currentIndexFont + 1).second);

    ui->treeView->resizeColumnToContents(0);

    ui->tableView->resizeColumnToContents(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    ui->tableView->resizeColumnToContents(3);
    ui->tableView->resizeColumnToContents(4);
    ui->tableView->resizeColumnToContents(5);
    ui->tableView->resizeColumnToContents(6);

    ui->tableView->update();
}

void MainWindowServer::on_actionReduce_triggered()
{
    QFont font = modelJour->getFont();
    int currentIndexFont = 0;

    for(int n = fontSize.size(); currentIndexFont < n; currentIndexFont++)
        if(font.pointSize() == fontSize.at(currentIndexFont).first)
            break;

    if(0 > currentIndexFont - 1)
        return;

    font.setPointSize(fontSize.at(currentIndexFont - 1).first);
    modelJour->setFont(font);

    ui->tableView->verticalHeader()->setMinimumHeight(fontSize.at(currentIndexFont - 1).second);
    ui->tableView->verticalHeader()->setDefaultSectionSize(fontSize.at(currentIndexFont - 1).second);

    ui->treeView->resizeColumnToContents(0);

    ui->tableView->resizeColumnToContents(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    ui->tableView->resizeColumnToContents(3);
    ui->tableView->resizeColumnToContents(4);
    ui->tableView->resizeColumnToContents(5);
    ui->tableView->resizeColumnToContents(6);

    ui->tableView->update();
}

void MainWindowServer::on_actionNewScheme_triggered()
{
    int ret = QMessageBox::question(this, tr("Предупреждение"),
                                   tr("Начать новую смену?"),
                                   QMessageBox::Ok | QMessageBox::Cancel,
                                   QMessageBox::Ok);

    if(QMessageBox::Ok == ret) {

        if(0 != ServerSettingUtils::getValueSettings("P1", "PostgresSQL").toInt() || 0 != ServerSettingUtils::getValueSettings("P2", "PostgresSQL").toInt()) {
            QString sql = " select * from jour where flag != 0 ";
            QList<JourEntity> tmpLs = DataBaseManager::getQueryMSGRecord(sql);

            if(tmpLs.size()) {
                QMessageBox::warning(this, tr("Ошибка"),
                                     tr("Не заполнены все обязательные поля в базе данных!"));
                return;
            }

        }

        AuthenticationDialog ad;
        if(0 != ad.getInitialResult()) {
            if(QDialog::Accepted != ad.exec()) {
                QMessageBox::warning(this, QObject::tr("Ошибка"),
                                     QObject::tr("Ошибка выбора оператора комплекса!"));
                return;
            }
        }

        forcedNewDuty(true);
    }
}

void MainWindowServer::forcedNewDuty(bool out)
{
    JourEntity msg;
    msg.setObject(tr("Оператор"));
    msg.setType(902);
    if(out) {
        msg.setComment(tr("Начата новая смена"));
        msg.setType(902);
    } else {
        msg.setComment(tr("Удал. ком. Начата новая смена"));
        msg.setType(1902);
    }
    msg.setFlag(0);

    QString sql = " update public.jour set flag = 0 where flag != 0 ;";
    DataBaseManager::executeQuery(sql);

    DataBaseManager::insertJourMsg_wS(msg);
    GraphTerminal::sendAbonentEventsAndStates(msg);

    DataBaseManager::setIdStartLastDuty();

    modelJour->updateAllRecords();

    initLabelOperator();
}

void MainWindowServer::on_actionOpen_triggered()
{
    lockOpenClose(true);
}

void MainWindowServer::on_actionClose_triggered()
{
    lockOpenClose(false);
}

void MainWindowServer::lockOpenClose(bool val)
{
    if(selUN.isNull())
        return;
    this->m_portManager->lockOpenCloseCommand(false, selUN, val);
}

void MainWindowServer::on_actionDataBase_triggered()
{
    QProcess *process = new QProcess(this);
    QString file = QString( QCoreApplication::applicationDirPath() + "/m_db" );
#if (defined (_WIN32) || defined (_WIN64))
    // windows code
    file.append(".exe");
#endif
    process->start(file, QStringList());
}

void MainWindowServer::on_actionUNSqlSelect_triggered()
{
    QProcess *process = new QProcess(this);
    QString file = QString( QCoreApplication::applicationDirPath() + "/m_db" );

#if (defined (_WIN32) || defined (_WIN64))
    // windows code
    file.append(".exe");
#endif

//    file.append(" -sql \"" + getUnSqlSelect() + "\"");
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
//    codec->fromUnicode("-sql");
//    codec->fromUnicode("\"" + getUnSqlSelect() + "\"");
    process->start(file, QStringList() << codec->fromUnicode("-sql") << codec->fromUnicode("\"" + getUnSqlSelect() + "\""));
}

void MainWindowServer::changeSelectUN(QSharedPointer<UnitNode> un)
{
    if(nullptr == un)
        return;
    QModelIndex index = this->modelTreeUN->findeIndexUN(un.data());
    ui->treeView->setCurrentIndex(index);
}

void MainWindowServer::preparePageCustomization(int /*typeUN*/)
{
    ui->groupBox_Customization->setVisible(false);

    if(!ui->actionCustomization->isChecked())
        return;

    if(selUN.isNull())
        return;

    switch (selUN->getType()) {
    case TypeUnitNode::RLM_KRL:
    case TypeUnitNode::RLM_C:
        preparePageRLM(selUN);
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget->setMaximumHeight(140);
        break;
    case TypeUnitNode::TG:
        preparePagePoint(selUN->getType());
        ui->stackedWidget->setCurrentIndex(3);
        ui->stackedWidget->setMaximumHeight(185);
        break;
    case TypeUnitNode::DD_SOTA:
        preparePageSota1(selUN->getType());
        ui->stackedWidget->setCurrentIndex(1);
        ui->stackedWidget->setMaximumHeight(200);
        break;
    case TypeUnitNode::DD_T4K_M:
        preparePageSota2(selUN->getType());
        ui->stackedWidget->setCurrentIndex(2);
        ui->stackedWidget->setMaximumHeight(200);
        break;
    default:
        ui->groupBox_Customization->setVisible(false);
        return;
    }

    ui->groupBox_Customization->setVisible(true);
}

void MainWindowServer::preparePageRLM(const QSharedPointer<UnitNode>  un)
{
    ui->comboBox_RLMTactPeriod->clear();
    ui->comboBox_RLMTactPeriod->setEnabled(false);
    ui->comboBox_RLMTactPeriod->setEditable(false);
    ui->comboBox_RLMTactPeriod->addItem(tr("Неопределено"), -1);

    if(TypeUnitNode::RLM_C == un->getType()) {
        for(int i = 0, n = 5; i < n; i++) {
            ui->comboBox_RLMTactPeriod->addItem(QString(tr("Такт") + " %1").arg(i + 1), i);
        }
    } else if(TypeUnitNode::RLM_KRL == un->getType() &&
              (0 == un->getAdamOff() ||
               1 == un->getAdamOff())) {
        for(int i = 0, n = 4; i < n; i++) {
            ui->comboBox_RLMTactPeriod->addItem(QString(tr("Такт") + " %1").arg(i + 1), i);
        }
    } else if(TypeUnitNode::RLM_KRL == un->getType() &&
              (3 == un->getAdamOff() ||
              2 == un->getAdamOff())) {
        for(int i = 0, n = 2; i < n; i++) {
            ui->comboBox_RLMTactPeriod->addItem(QString(tr("Такт") + " %1").arg(i + 1), i);
        }
    } else if(TypeUnitNode::RLM_KRL == un->getType() &&
              4 == un->getAdamOff()) {
        for(int i = 0, n = 4; i < n; i++) {
            ui->comboBox_RLMTactPeriod->addItem(QString(tr("УШ") + " %1").arg(i + 1), i);
        }
    }

    if(TypeUnitNode::RLM_KRL == un->getType() &&
       5 == un->getAdamOff()) {
        ui->comboBox_RLMTactPeriod->setEnabled(false);
        ui->comboBox_RLMTactPeriod->setItemData(0, 0);
    } else {
        ui->comboBox_RLMTactPeriod->setEnabled(true);
    }


    ui->comboBox_RLMCondition->clear();
    ui->comboBox_RLMCondition->setEnabled(false);
    ui->comboBox_RLMCondition->setEditable(false);
    ui->comboBox_RLMCondition->addItem(tr("Неопределено"), -1);
    if(TypeUnitNode::RLM_C == un->getType() ||
       (TypeUnitNode::RLM_KRL == un->getType() &&
        (0 == un->getAdamOff() ||
         1 == un->getAdamOff() ||
         2 == un->getAdamOff()))) {
        ui->comboBox_RLMCondition->addItem(tr("Основной"), 0);
        ui->comboBox_RLMCondition->addItem(tr("Дополнительный"), 1);
    } else if(TypeUnitNode::RLM_KRL == un->getType() &&
               3 == un->getAdamOff()) {
        ui->comboBox_RLMCondition->addItem(tr("Нормальный"), 0);
        ui->comboBox_RLMCondition->addItem(tr("Помехозащищенный"), 1);
    } else if(TypeUnitNode::RLM_KRL == un->getType() &&
               4 == un->getAdamOff()) {
        ui->comboBox_RLMCondition->addItem(tr("Настройка"), 0);
        ui->comboBox_RLMCondition->addItem(tr("Работа"), 1);
    } else if(TypeUnitNode::RLM_KRL == un->getType() &&
              5 == un->getAdamOff()) {
        ui->comboBox_RLMCondition->addItem(tr("Медленный"), 0);
        ui->comboBox_RLMCondition->addItem(tr("Быстрый"), 1);
    }
    if(TypeUnitNode::RLM_C == un->getType()) {
        ui->comboBox_RLMCondition->addItem(tr("Ползущий (Плз)"), 2);
        ui->comboBox_RLMCondition->addItem(tr("2-й ярус (2Яр)"), 3);
    }
    ui->comboBox_RLMCondition->setEnabled(true);

    ui->comboBox_RLMEdge->clear();
    ui->comboBox_RLMEdge->setEnabled(false);
    ui->comboBox_RLMEdge->setEditable(false);
    ui->comboBox_RLMEdge->addItem(tr("Неопределено"));
    if(TypeUnitNode::RLM_C == un->getType()) {
        for(int i = 0, n = 6; i < n; i++) {
            if(0 == i) {
                ui->comboBox_RLMEdge->addItem(QString(".%1 (" + tr("самый груб.") + ")").arg(i + 1), (float)(((float)i + 1.0)/10.0));
            } else {
                ui->comboBox_RLMEdge->addItem(QString(".%1").arg(i + 1), (float)(((float)i + 1.0)/10.0));
            }
        }
        for(int i = 0, n = 10; i < n; i++) {
            if(0 == i) {
                ui->comboBox_RLMEdge->addItem(QString("%1 (" + tr("грубый") + ")").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            } else if(9 <= i) {
                ui->comboBox_RLMEdge->addItem(QString("%1 (" + tr("чувств") + ")").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            } else {
                ui->comboBox_RLMEdge->addItem(QString("%1").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            }
        }
    } else if(TypeUnitNode::RLM_KRL == un->getType() &&
              1 == un->getAdamOff()) {
        for(int i = 0, n = 6; i < n; i++) {
            if(0 == i) {
                ui->comboBox_RLMEdge->addItem(QString(".%1 (" + tr("самый груб.") + ")").arg(i + 1), (float)(((float)i + 1.0)/10.0));
            } else {
                ui->comboBox_RLMEdge->addItem(QString(".%1").arg(i + 1), (float)(((float)i + 1.0)/10.0));
            }
        }
        for(int i = 0, n = 10; i < n; i++) {
            if(0 == i) {
                ui->comboBox_RLMEdge->addItem(QString("%1 (" + tr("груб.") + ")").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            } else if(9 <= i) {
                ui->comboBox_RLMEdge->addItem(QString("%1 (" + tr("чувств.") + ")").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            } else {
                ui->comboBox_RLMEdge->addItem(QString("%1").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            }
        }
    } else if(TypeUnitNode::RLM_KRL == un->getType() &&
              (0 == un->getAdamOff() ||
               2 == un->getAdamOff() ||
               4 == un->getAdamOff() ||
               5 == un->getAdamOff())) {
        for(int i = 0, n = 6; i < n; i++) {
            ui->comboBox_RLMEdge->addItem(tr("01 (груб.)"), (float)(((float)i + 1.0)/10.0));
        }
        for(int i = 0, n = 10; i < n; i++) {
            if(0 == i) {
                ui->comboBox_RLMEdge->addItem(QString("%1 (" + tr("грубый") + ")").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            } else if(9 <= i) {
                ui->comboBox_RLMEdge->addItem(QString("%1 (" + tr("чувств") + ")").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            } else {
                ui->comboBox_RLMEdge->addItem(QString("%1").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            }
        }
    } else if(TypeUnitNode::RLM_KRL == un->getType() &&
              3 == un->getAdamOff()) {
        for(int i = 0, n = 6; i < n; i++) {
            ui->comboBox_RLMEdge->addItem(tr("01 (груб.) (Режим Линейный)"), (float)(((float)i + 1.0)/10.0));
        }
        for(int i = 0, n = 10; i < n; i++) {
            if(0 == i) {
                ui->comboBox_RLMEdge->addItem(QString("%1 (" + tr("груб.") +") (" + tr("Режим Линейный") + ")").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            } else if(0 < i && 5 > i) {
                ui->comboBox_RLMEdge->addItem(QString("%1 (" + tr("Режим Линейный)")).arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            } else if(5 <= i && 9 > i) {
                ui->comboBox_RLMEdge->addItem(QString("%1 (" + tr("Режим Объёмный)")).arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            } else if(9 == i) {
                ui->comboBox_RLMEdge->addItem(QString("%1 (" + tr("чув.") +") (" + tr("Режим Объёмный") + ")").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            } else {
                ui->comboBox_RLMEdge->addItem(QString("%1").arg(i + 1, 2, 10, QLatin1Char('0')), (float)((float)i + 1.0));
            }
        }
    }
    ui->comboBox_RLMEdge->setEnabled(true);

    fillPageRLM();
}

void MainWindowServer::preparePagePoint(int /*typeUN*/)
{
    ui->comboBox_PointInput->clear();
    ui->comboBox_PointInput->setEnabled(false);
    ui->comboBox_PointInput->setEditable(false);
    for(int i = 0, n = 4; i < n; i++) {
        ui->comboBox_PointInput->addItem(QString::number(i + 1), i + 1);
    }
    ui->comboBox_PointInput->setEnabled(true);

    ui->checkBox_PointFlt1->setCheckState(Qt::Unchecked);
    ui->checkBox_PointFlt2->setCheckState(Qt::Unchecked);
    ui->checkBox_PointFlt3->setCheckState(Qt::Unchecked);

    ui->spinBox_PointFlt1Edge->clear();
    ui->spinBox_PointFlt1Edge->setEnabled(false);
    ui->spinBox_PointFlt1Edge->setValue(0);
    ui->spinBox_PointFlt1Edge->setMaximum(50001);
    ui->spinBox_PointFlt1Edge->setMinimum(0);
    ui->spinBox_PointFlt1Edge->setEnabled(true);

    ui->spinBox_PointFlt2Edge->clear();
    ui->spinBox_PointFlt2Edge->setEnabled(false);
    ui->spinBox_PointFlt2Edge->setValue(0);
    ui->spinBox_PointFlt2Edge->setMaximum(50001);
    ui->spinBox_PointFlt2Edge->setMinimum(0);
    ui->spinBox_PointFlt2Edge->setEnabled(true);

    ui->spinBox_PointFlt3Edge->clear();
    ui->spinBox_PointFlt3Edge->setEnabled(false);
    ui->spinBox_PointFlt3Edge->setValue(0);
    ui->spinBox_PointFlt3Edge->setMaximum(50001);
    ui->spinBox_PointFlt3Edge->setMinimum(0);
    ui->spinBox_PointFlt3Edge->setEnabled(true);

    fillPageTG();
}

void MainWindowServer::preparePageSota1(int typeUN)
{
    if(0 == typeUN)
        return;

    ui->comboBox_Sota1F1->clear();
    ui->comboBox_Sota1F1->setEnabled(false);
    ui->comboBox_Sota1F1->setEditable(false);
    ui->comboBox_Sota1F1->addItems({tr("Выкл"), tr("Вкл")});
    ui->comboBox_Sota1F1->setEnabled(true);

    ui->comboBox_Sota1F2->clear();
    ui->comboBox_Sota1F2->setEnabled(false);
    ui->comboBox_Sota1F2->setEditable(false);
    ui->comboBox_Sota1F2->addItems({tr("Выкл"), tr("Вкл")});
    ui->comboBox_Sota1F2->setEnabled(true);

    ui->spinBox_Sota1EdgeF1->clear();
    ui->spinBox_Sota1EdgeF1->setEnabled(false);
    ui->spinBox_Sota1EdgeF1->setValue(0);
    ui->spinBox_Sota1EdgeF1->setMaximum(65535);
    ui->spinBox_Sota1EdgeF1->setMinimum(0);
    ui->spinBox_Sota1EdgeF1->setEnabled(true);

    ui->spinBox_Sota1EdgeF2->clear();
    ui->spinBox_Sota1EdgeF2->setEnabled(false);
    ui->spinBox_Sota1EdgeF2->setValue(0);
    ui->spinBox_Sota1EdgeF2->setMaximum(65535);
    ui->spinBox_Sota1EdgeF2->setMinimum(0);
    ui->spinBox_Sota1EdgeF2->setEnabled(true);

    ui->comboBox_Sota1TimeAffectF1->clear();
    ui->comboBox_Sota1TimeAffectF1->setEnabled(false);
    ui->comboBox_Sota1TimeAffectF1->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_Sota1TimeAffectF1->addItem(QString::number((double)(i + 1.0) * 0.1, 'f', 1));
    }
    ui->comboBox_Sota1TimeAffectF1->setEnabled(true);

    ui->comboBox_Sota1TimeAffectF2->clear();
    ui->comboBox_Sota1TimeAffectF2->setEnabled(false);
    ui->comboBox_Sota1TimeAffectF2->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_Sota1TimeAffectF2->addItem(QString::number((double)(i + 1.0) * 0.1, 'f', 1));
    }
    ui->comboBox_Sota1TimeAffectF2->setEnabled(true);


    ui->comboBox_Sota1CountAffectF1->clear();
    ui->comboBox_Sota1CountAffectF1->setEnabled(false);
    ui->comboBox_Sota1CountAffectF1->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_Sota1CountAffectF1->addItem(QString("%1").arg(i + 1));
    }
    ui->comboBox_Sota1CountAffectF1->setEnabled(true);

    ui->comboBox_Sota1CountAffectF2->clear();
    ui->comboBox_Sota1CountAffectF2->setEnabled(false);
    ui->comboBox_Sota1CountAffectF2->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_Sota1CountAffectF2->addItem(QString("%1").arg(i + 1));
    }
    ui->comboBox_Sota1CountAffectF2->setEnabled(true);

    ui->spinBox_Sota1DurationF1->clear();
    ui->spinBox_Sota1DurationF1->setEnabled(false);
    ui->spinBox_Sota1DurationF1->setValue(0);
    ui->spinBox_Sota1DurationF1->setMaximum(100);
    ui->spinBox_Sota1DurationF1->setMinimum(0);
    ui->spinBox_Sota1DurationF1->setEnabled(true);

    ui->spinBox_Sota1DurationF2->clear();
    ui->spinBox_Sota1DurationF2->setEnabled(false);
    ui->spinBox_Sota1DurationF2->setValue(0);
    ui->spinBox_Sota1DurationF2->setMaximum(100);
    ui->spinBox_Sota1DurationF2->setMinimum(0);
    ui->spinBox_Sota1DurationF2->setEnabled(true);
}

void MainWindowServer::preparePageSota2(int typeUN)
{
    if(0 == typeUN)
        return;

    //C1
    ui->comboBox_Sota2C1F1->clear();
    ui->comboBox_Sota2C1F1->setEnabled(false);
    ui->comboBox_Sota2C1F1->setEditable(false);
    ui->comboBox_Sota2C1F1->addItems({tr("Выкл"), tr("Вкл")});
    ui->comboBox_Sota2C1F1->setEnabled(true);

    ui->comboBox_Sota2C1F2->clear();
    ui->comboBox_Sota2C1F2->setEnabled(false);
    ui->comboBox_Sota2C1F2->setEditable(false);
    ui->comboBox_Sota2C1F2->addItems({tr("Выкл"), tr("Вкл")});
    ui->comboBox_Sota2C1F2->setEnabled(true);

    ui->spinBox_Sota2EdgeC1F1->clear();
    ui->spinBox_Sota2EdgeC1F1->setEnabled(false);
    ui->spinBox_Sota2EdgeC1F1->setValue(0);
    ui->spinBox_Sota2EdgeC1F1->setMaximum(65535);
    ui->spinBox_Sota2EdgeC1F1->setMinimum(0);
    ui->spinBox_Sota2EdgeC1F1->setEnabled(true);

    ui->spinBox_Sota2EdgeC1F2->clear();
    ui->spinBox_Sota2EdgeC1F2->setEnabled(false);
    ui->spinBox_Sota2EdgeC1F2->setValue(0);
    ui->spinBox_Sota2EdgeC1F2->setMaximum(65535);
    ui->spinBox_Sota2EdgeC1F2->setMinimum(0);
    ui->spinBox_Sota2EdgeC1F2->setEnabled(true);

    ui->comboBox_Sota2TimeAffectC1F1->clear();
    ui->comboBox_Sota2TimeAffectC1F1->setEnabled(false);
    ui->comboBox_Sota2TimeAffectC1F1->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_Sota2TimeAffectC1F1->addItem(QString::number((double)(i + 1.0) * 0.1, 'f', 1));
    }
    ui->comboBox_Sota2TimeAffectC1F1->setEnabled(true);

    ui->comboBox_Sota2TimeAffectC1F2->clear();
    ui->comboBox_Sota2TimeAffectC1F2->setEnabled(false);
    ui->comboBox_Sota2TimeAffectC1F2->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_Sota2TimeAffectC1F2->addItem(QString::number((double)(i + 1.0) * 0.1, 'f', 1));
    }
    ui->comboBox_Sota2TimeAffectC1F2->setEnabled(true);


    ui->comboBox_Sota2CountAffectC1F1->clear();
    ui->comboBox_Sota2CountAffectC1F1->setEnabled(false);
    ui->comboBox_Sota2CountAffectC1F1->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_Sota2CountAffectC1F1->addItem(QString("%1").arg(i + 1));
    }
    ui->comboBox_Sota2CountAffectC1F1->setEnabled(true);

    ui->comboBox_Sota2CountAffectC1F2->clear();
    ui->comboBox_Sota2CountAffectC1F2->setEnabled(false);
    ui->comboBox_Sota2CountAffectC1F2->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_Sota2CountAffectC1F2->addItem(QString("%1").arg(i + 1));
    }
    ui->comboBox_Sota2CountAffectC1F2->setEnabled(true);

    ui->spinBox_Sota2DurationC1F1->clear();
    ui->spinBox_Sota2DurationC1F1->setEnabled(false);
    ui->spinBox_Sota2DurationC1F1->setValue(0);
    ui->spinBox_Sota2DurationC1F1->setMaximum(100);
    ui->spinBox_Sota2DurationC1F1->setMinimum(0);
    ui->spinBox_Sota2DurationC1F1->setEnabled(true);

    ui->spinBox_Sota2DurationC1F2->clear();
    ui->spinBox_Sota2DurationC1F2->setEnabled(false);
    ui->spinBox_Sota2DurationC1F2->setValue(0);
    ui->spinBox_Sota2DurationC1F2->setMaximum(100);
    ui->spinBox_Sota2DurationC1F2->setMinimum(0);
    ui->spinBox_Sota2DurationC1F2->setEnabled(true);

    ui->comboBox_Sota2WeakeningC1->clear();
    ui->comboBox_Sota2WeakeningC1->setEnabled(false);
    ui->comboBox_Sota2WeakeningC1->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_Sota2WeakeningC1->addItem(QString("%1").arg(i + 1));
    }
    ui->comboBox_Sota2WeakeningC1->setEnabled(true);

    //C2
    ui->comboBox_Sota2C2F1->clear();
    ui->comboBox_Sota2C2F1->setEnabled(false);
    ui->comboBox_Sota2C2F1->setEditable(false);
    ui->comboBox_Sota2C2F1->addItems({tr("Выкл"), tr("Вкл")});
    ui->comboBox_Sota2C2F1->setEnabled(true);

    ui->comboBox_Sota2C2F2->clear();
    ui->comboBox_Sota2C2F2->setEnabled(false);
    ui->comboBox_Sota2C2F2->setEditable(false);
    ui->comboBox_Sota2C2F2->addItems({tr("Выкл"), tr("Вкл")});
    ui->comboBox_Sota2C2F2->setEnabled(true);

    ui->spinBox_Sota2EdgeC2F1->clear();
    ui->spinBox_Sota2EdgeC2F1->setEnabled(false);
    ui->spinBox_Sota2EdgeC2F1->setValue(0);
    ui->spinBox_Sota2EdgeC2F1->setMaximum(65535);
    ui->spinBox_Sota2EdgeC2F1->setMinimum(0);
    ui->spinBox_Sota2EdgeC2F1->setEnabled(true);

    ui->spinBox_Sota2EdgeC2F2->clear();
    ui->spinBox_Sota2EdgeC2F2->setEnabled(false);
    ui->spinBox_Sota2EdgeC2F2->setValue(0);
    ui->spinBox_Sota2EdgeC2F2->setMaximum(65535);
    ui->spinBox_Sota2EdgeC2F2->setMinimum(0);
    ui->spinBox_Sota2EdgeC2F2->setEnabled(true);

    ui->comboBox_Sota2TimeAffectC2F1->clear();
    ui->comboBox_Sota2TimeAffectC2F1->setEnabled(false);
    ui->comboBox_Sota2TimeAffectC2F1->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_Sota2TimeAffectC2F1->addItem(QString::number((double)(i + 1.0) * 0.1, 'f', 1));
    }
    ui->comboBox_Sota2TimeAffectC2F1->setEnabled(true);

    ui->comboBox_Sota2TimeAffectC2F2->clear();
    ui->comboBox_Sota2TimeAffectC2F2->setEnabled(false);
    ui->comboBox_Sota2TimeAffectC2F2->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_Sota2TimeAffectC2F2->addItem(QString::number((double)(i + 1.0) * 0.1, 'f', 1));
    }
    ui->comboBox_Sota2TimeAffectC2F2->setEnabled(true);


    ui->comboBox_Sota2CountAffectC2F1->clear();
    ui->comboBox_Sota2CountAffectC2F1->setEnabled(false);
    ui->comboBox_Sota2CountAffectC2F1->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_Sota2CountAffectC2F1->addItem(QString("%1").arg(i + 1));
    }
    ui->comboBox_Sota2CountAffectC2F1->setEnabled(true);

    ui->comboBox_Sota2CountAffectC2F2->clear();
    ui->comboBox_Sota2CountAffectC2F2->setEnabled(false);
    ui->comboBox_Sota2CountAffectC2F2->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_Sota2CountAffectC2F2->addItem(QString("%1").arg(i + 1));
    }
    ui->comboBox_Sota2CountAffectC2F2->setEnabled(true);

    ui->spinBox_Sota2DurationC2F1->clear();
    ui->spinBox_Sota2DurationC2F1->setEnabled(false);
    ui->spinBox_Sota2DurationC2F1->setValue(0);
    ui->spinBox_Sota2DurationC2F1->setMaximum(100);
    ui->spinBox_Sota2DurationC2F1->setMinimum(0);
    ui->spinBox_Sota2DurationC2F1->setEnabled(true);

    ui->spinBox_Sota2DurationC2F2->clear();
    ui->spinBox_Sota2DurationC2F2->setEnabled(false);
    ui->spinBox_Sota2DurationC2F2->setValue(0);
    ui->spinBox_Sota2DurationC2F2->setMaximum(100);
    ui->spinBox_Sota2DurationC2F2->setMinimum(0);
    ui->spinBox_Sota2DurationC2F2->setEnabled(true);

    ui->comboBox_Sota2WeakeningC2->clear();
    ui->comboBox_Sota2WeakeningC2->setEnabled(false);
    ui->comboBox_Sota2WeakeningC2->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_Sota2WeakeningC2->addItem(QString("%1").arg(i + 1));
    }
    ui->comboBox_Sota2WeakeningC2->setEnabled(true);
}

void MainWindowServer::fillPageRLM()
{
    if(selUN.isNull())
        return;
    if(TypeUnitNode::RLM_C != selUN->getType() && TypeUnitNode::RLM_KRL != selUN->getType())
        return;
    else if(TypeUnitNode::RLM_C == selUN->getType()) {
        qDebug() << "MainWindowServer::fillPageRLM(" << selUN->toString() << ") -->";
        qDebug() << "StateWord " << selUN->getStateWord().toHex();
        qDebug() << "clockPeriod " << selUN->swpRLMC().clockPeriod();
        qDebug() << "modeProcessing " << selUN->swpRLMC().modeProcessing();
        qDebug() << "threshold " << selUN->swpRLMC().threshold();

        int tmpIndex = 0;
        tmpIndex = ui->comboBox_RLMTactPeriod->findData(selUN->swpRLMC().clockPeriod());
        ui->comboBox_RLMTactPeriod->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);

        tmpIndex = ui->comboBox_RLMCondition->findData(selUN->swpRLMC().modeProcessing());
        ui->comboBox_RLMCondition->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);

        tmpIndex = ui->comboBox_RLMEdge->findData(selUN->swpRLMC().threshold());
        ui->comboBox_RLMEdge->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);
        qDebug() << "MainWindowServer::fillPageRLM(" << selUN->toString() << ") <--";

        return;
    } else if(TypeUnitNode::RLM_KRL == selUN->getType()) {
        qDebug() << "MainWindowServer::fillPageRLM(" << selUN->toString() << ") -->";
        qDebug() << "StateWord " << selUN->getStateWord().toHex();
        qDebug() << "clockPeriod " << selUN->swpRLM().clockPeriod();
        qDebug() << "modeProcessing " << selUN->swpRLM().modeProcessing();
        qDebug() << "threshold " << selUN->swpRLM().threshold();

        int tmpIndex = 0;
        tmpIndex = ui->comboBox_RLMTactPeriod->findData(selUN->swpRLM().clockPeriod());
        ui->comboBox_RLMTactPeriod->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);

        tmpIndex = ui->comboBox_RLMCondition->findData(selUN->swpRLM().modeProcessing());
        ui->comboBox_RLMCondition->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);

        tmpIndex = ui->comboBox_RLMEdge->findData(selUN->swpRLM().threshold());
        ui->comboBox_RLMEdge->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);
        qDebug() << "MainWindowServer::fillPageRLM(" << selUN->toString() << ") <--";

        return;
    }


}

void MainWindowServer::fillPageTG()
{
    if(selUN.isNull())
        return;
    if(TypeUnitNode::TG != selUN->getType() && TypeUnitNode::TG_Base != selUN->getType())
        return;

    int ci = selUN->getNum2();
    if(1 > ci || 4 < ci)
        return;


    qDebug() << "MainWindowServer::fillPageTG(" << selUN->toString() << ") -->";
    qDebug() << "StateWord " << selUN->getStateWordType0x34().toHex();
    qDebug() << "input " << ci;

    auto swp = selUN->swpTGType0x34();

    int tmpIndex = 0;
    tmpIndex = ui->comboBox_PointInput->findData(ci);
    ui->comboBox_PointInput->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);

    if(1 == swp.C(ci).isOnFlt1()) {
        ui->checkBox_PointFlt1->setChecked(true);
    } else if(1 == swp.C(ci).isOffFlt1()) {
        ui->checkBox_PointFlt1->setChecked(false);
    }

    if(1 == swp.C(ci).isOnFlt2()) {
        ui->checkBox_PointFlt2->setChecked(true);
    } else if(1 == swp.C(ci).isOffFlt2()) {
        ui->checkBox_PointFlt2->setChecked(false);
    }

    if(1 == swp.C(ci).isOnFlt3()) {
        ui->checkBox_PointFlt3->setChecked(true);
    } else if(1 == swp.C(ci).isOffFlt3()) {
        ui->checkBox_PointFlt3->setChecked(false);
    }

    ui->spinBox_PointFlt1Edge->setValue(swp.C(ci).thresholdFlt1());

    ui->spinBox_PointFlt2Edge->setValue(swp.C(ci).thresholdFlt2());

    ui->spinBox_PointFlt3Edge->setValue(swp.C(ci).thresholdFlt3());

    qDebug() << "MainWindowServer::fillPageTG(" << selUN->toString() << ") <--";
}

void MainWindowServer::fillPageSota1(int /*typeUN*/)
{

}

void MainWindowServer::fillPageSota2(int /*typeUN*/)
{

}

void MainWindowServer::on_actionCustomization_triggered()
{
    ui->actionCustomization->setChecked(ui->actionCustomization->isChecked());
    preparePageCustomization(-1);

    tuneNeededStateWordTypeSelectedlUN();
}

void MainWindowServer::on_pushButton_ReadCustomization_clicked()
{
    if(!ui->groupBox_Customization->isVisible())
        return;
    if(!ui->actionCustomization->isChecked())
        return;
    if(selUN.isNull())
        return;

    switch (selUN->getType()) {
    case TypeUnitNode::RLM_KRL:
    case TypeUnitNode::RLM_C:
        fillPageRLM(); //CurrentIndex(0);
        break;
    case TypeUnitNode::TG:
        fillPageTG(); //setCurrentIndex(3);
        break;
    case TypeUnitNode::DD_SOTA:
        fillPageSota1(selUN->getType()); //CurrentIndex(1);
        break;
    case TypeUnitNode::DD_T4K_M:
        fillPageSota2(selUN->getType()); //CurrentIndex(2);
        break;
    default:
        return;
    }
}

void MainWindowServer::on_pushButton_WriteCustomization_clicked()
{
//    //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked() -->";
    if(!ui->groupBox_Customization->isVisible()) {
//        //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked(ERROR) <--";
        return;
    }
    if(!ui->actionCustomization->isChecked()) {
//        //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked(ERROR) <--";
        return;
    }
    if(selUN.isNull()) {
//        //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked(ERROR) <--";
        return;
    }

    switch (selUN->getType()) {
    case TypeUnitNode::RLM_KRL: {
        auto newStateWord = selUN->getStateWord();
        if(newStateWord.isEmpty()) {
//            //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked(ERROR) <--";
            return;
        }

        auto clockPeriod = ui->comboBox_RLMTactPeriod->currentData().toInt();
//        //qDebug() << "clockPeriod --> " << clockPeriod;

        auto modeProcessing = ui->comboBox_RLMCondition->currentData().toInt();
//        //qDebug() << "modeProcessing --> " << modeProcessing;

        auto threshold = ui->comboBox_RLMEdge->currentData().toDouble();
//        //qDebug() << "threshold --> " << threshold;

        if(-1 == clockPeriod || -1 == modeProcessing || -1 == threshold) {
            //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked(ERROR) <--";
            return;
        }

//        //qDebug() << "original newStateWord " << newStateWord.toHex();

        newStateWord[0] = static_cast<quint8>(0x00);
//        //qDebug() << "prepare newStateWord " << newStateWord.toHex();

        {
            quint8 cp = clockPeriod;
            cp = Utils::reverseBits(cp);
            cp = cp >> 6;
            clockPeriod = cp;
        }

        newStateWord[0] = static_cast<quint8>(newStateWord[0]) | (static_cast<quint8>(clockPeriod) << 5);
//        //qDebug() << "clockPeriod newStateWord " << newStateWord.toHex();

        if(Utils::treatAsEqual(10.0, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(0);
        } else if(Utils::treatAsEqual(09.0, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(1);
        } else if(Utils::treatAsEqual(08.0, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(2);
        } else if(Utils::treatAsEqual(07.0, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(3);
        } else if(Utils::treatAsEqual(06.0, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(4);
        } else if(Utils::treatAsEqual(05.0, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(5);
        } else if(Utils::treatAsEqual(04.0, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(6);
        } else if(Utils::treatAsEqual(03.0, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(7);
        } else if(Utils::treatAsEqual(02.0, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(8);
        } else if(Utils::treatAsEqual(01.0, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(9);
        } else if(Utils::treatAsEqual(00.6, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(10);
        } else if(Utils::treatAsEqual(00.5, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(11);
        } else if(Utils::treatAsEqual(00.4, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(12);
        } else if(Utils::treatAsEqual(00.3, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(13);
        } else if(Utils::treatAsEqual(00.2, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(14);
        } else if(Utils::treatAsEqual(00.1, threshold)) {
            newStateWord[0] = static_cast<quint8>(newStateWord[0]) | static_cast<quint8>(15);
        }
//        //qDebug() << "threshold newStateWord " << newStateWord.toHex();

        newStateWord[0] = static_cast<quint8>(newStateWord[0]) | (static_cast<quint8>(modeProcessing) << 4);
//        //qDebug() << "modeProcessing newStateWord " << newStateWord.toHex();

        m_portManager->requestModeSensor(selUN, newStateWord);

        break;
    }
    case TypeUnitNode::RLM_C: {
        auto newStateWord = selUN->getStateWord();
        if(newStateWord.isEmpty()) {
//            //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked(ERROR) <--";
            return;
        }

        auto clockPeriod = ui->comboBox_RLMTactPeriod->currentData().toInt();
        auto modeProcessing = ui->comboBox_RLMCondition->currentData().toInt();
        auto threshold = ui->comboBox_RLMEdge->currentData().toDouble();

        if(-1 == clockPeriod || -1 == modeProcessing || -1 == threshold) {
//            //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked(ERROR) <--";
            return;
        }

        newStateWord[2] = static_cast<quint8>(0x00);
        newStateWord[3] = static_cast<quint8>(0x00);

        newStateWord[2] = static_cast<quint8>(newStateWord[2]) | (static_cast<quint8>(clockPeriod) << 4);

        if(Utils::treatAsEqual(10.0, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(0);
        } else if(Utils::treatAsEqual(09.0, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(1);
        } else if(Utils::treatAsEqual(08.0, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(2);
        } else if(Utils::treatAsEqual(07.0, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(3);
        } else if(Utils::treatAsEqual(06.0, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(4);
        } else if(Utils::treatAsEqual(05.0, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(5);
        } else if(Utils::treatAsEqual(04.0, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(6);
        } else if(Utils::treatAsEqual(03.0, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(7);
        } else if(Utils::treatAsEqual(02.0, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(8);
        } else if(Utils::treatAsEqual(01.0, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(9);
        } else if(Utils::treatAsEqual(00.6, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(10);
        } else if(Utils::treatAsEqual(00.5, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(11);
        } else if(Utils::treatAsEqual(00.4, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(12);
        } else if(Utils::treatAsEqual(00.3, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(13);
        } else if(Utils::treatAsEqual(00.2, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(14);
        } else if(Utils::treatAsEqual(00.1, threshold)) {
            newStateWord[2] = static_cast<quint8>(newStateWord[2]) | static_cast<quint8>(15);
        }

        newStateWord[3] = static_cast<quint8>(newStateWord[3]) | static_cast<quint8>(modeProcessing);

        m_portManager->requestModeSensor(selUN, newStateWord);

        break;
    }
    case TypeUnitNode::TG: {

        auto ci = static_cast<quint8>(ui->comboBox_PointInput->currentText().toInt() - 1);

        if(0 > ci || 3 < ci)
            ci = 0x00;

        auto newStateWord = selUN->swpTGType0x34().C(ci + 1).getStateWord();

        if(newStateWord.isEmpty() || 7 > newStateWord.size())
            newStateWord = newStateWord.fill(0x00, 7);

        newStateWord[0] = ((newStateWord.at(0) & 0xFC) | ci);

        newStateWord[0] = (newStateWord.at(0) & 0xFB);
        if(ui->checkBox_PointFlt1->isChecked())
            newStateWord[0] = newStateWord.at(0) | 0x04;

        newStateWord[0] = (newStateWord.at(0) & 0xF7);
        if(ui->checkBox_PointFlt2->isChecked())
            newStateWord[0] = newStateWord.at(0) | 0x08;

        newStateWord[0] = (newStateWord.at(0) & 0xEF);
        if(ui->checkBox_PointFlt3->isChecked())
            newStateWord[0] = newStateWord.at(0) | 0x10;

        newStateWord[1] = static_cast<quint8>(static_cast<quint16>(ui->spinBox_PointFlt1Edge->value() & 0x0000FF00) >> 8);
        newStateWord[2] = static_cast<quint8>(static_cast<quint16>(ui->spinBox_PointFlt1Edge->value() & 0x000000FF));

        newStateWord[3] = static_cast<quint8>(static_cast<quint16>(ui->spinBox_PointFlt2Edge->value() & 0x0000FF00) >> 8);
        newStateWord[4] = static_cast<quint8>(static_cast<quint16>(ui->spinBox_PointFlt2Edge->value() & 0x000000FF));

        newStateWord[5] = static_cast<quint8>(static_cast<quint16>(ui->spinBox_PointFlt3Edge->value() & 0x0000FF00) >> 8);
        newStateWord[6] = static_cast<quint8>(static_cast<quint16>(ui->spinBox_PointFlt3Edge->value() & 0x000000FF));

        m_portManager->requestModeSensor(selUN, newStateWord);

        break;
    }
    case TypeUnitNode::DD_SOTA:
        fillPageSota1(selUN->getType()); //CurrentIndex(1);
        break;
    case TypeUnitNode::DD_T4K_M:
        fillPageSota2(selUN->getType()); //CurrentIndex(2);
        break;
    default:
//        //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked(ERROR) <--";
        return;
    }
    //    //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked() <--";
}

void MainWindowServer::verticalScrollBarJourValueChanged(int value)
{
    if(value >= ui->tableView->verticalScrollBar()->maximum())
    {
        if(!modelJour->getNeedScroll()) {
            modelJour->setNeedScroll(true);
        }
    } else {
        modelJour->setNeedScroll(false);
    }
}

//void MainWindowServer::on_comboBox_RLMEdge_currentIndexChanged(int index)
//{
//    //qDebug() << "MainWindowServer::on_comboBox_RLMEdge_currentIndexChanged(" << index << ") -->";
//    //qDebug() << "itemText --> " << ui->comboBox_RLMEdge->itemText(index);
//    //qDebug() << "itemData --> " << ui->comboBox_RLMEdge->itemData(index);
//    //qDebug() << "MainWindowServer::on_comboBox_RLMEdge_currentIndexChanged(" << index << ") <--";
//}

//void MainWindowServer::on_comboBox_RLMCondition_currentIndexChanged(int index)
//{
//    //qDebug() << "MainWindowServer::on_comboBox_RLMCondition_currentIndexChanged(" << index << ") -->";
//    //qDebug() << "itemText --> " << ui->comboBox_RLMCondition->itemText(index);
//    //qDebug() << "itemData --> " << ui->comboBox_RLMCondition->itemData(index);
//    //qDebug() << "MainWindowServer::on_comboBox_RLMCondition_currentIndexChanged(" << index << ") <--";
//}

//void MainWindowServer::on_comboBox_RLMTactPeriod_currentIndexChanged(int index)
//{
//    //qDebug() << "MainWindowServer::on_comboBox_RLMTactPeriod_currentIndexChanged(" << index << ") -->";
//    //qDebug() << "itemText --> " << ui->comboBox_RLMTactPeriod->itemText(index);
//    //qDebug() << "itemData --> " << ui->comboBox_RLMTactPeriod->itemData(index);
//    //qDebug() << "MainWindowServer::on_comboBox_RLMTactPeriod_currentIndexChanged(" << index << ") <--";
//}
