#include "MainWindowServer.h"
#include "ui_MainWindowServer.h"

#include "ComboBoxDelegate.h"
#include <QCloseEvent>
#include <QNetworkDatagram>
#include <QTimer>
#include <QHeaderView>

#include "Port.h"
#include "SignalSlotCommutator.h"
#include "Utils.h"
#include "ServerSettingUtils.h"
#include "global.h"

#include "swprlm/SWPRLMType0x31.h"
#include "swprlmc/SWPRLMCType0x31.h"
#include "swpblip/SWPSDBLIPType0x41.h"
#include "swpblip/SWPIUBLIPType0x41.h"
#include "swptg/SWPTGType0x31.h"
#include "ServerTableModelJour.h"
#include <IniFileService.h>
#include <MessageBoxServer.h>
#include <QScrollBar>
#include "TopologyService.h"
#include "swptg/SWPTGSubType0x34.h"
#include "swptg/SWPTGType0x34.h"
#include "swpssoiblip/SWPSSOISDBLIPType0x41.h"
#include "swpssoiblip/SWPSSOIIUBLIPType0x41.h"
#include "swpt4k/SWPT4KBODType0x34.h"
#include "swpt4k/SWPT4KDDType0x34.h"
#include "swpt4k/SWPT4KDDCType0x34.h"
#include "swpt4k/SWPT4KDDCFType0x34.h"
#include "swpsota/SWPSOTABODType0x34.h"
#include "swpsota/SWPSOTADDType0x34.h"
#include "swpsota/SWPSOTADDFType0x34.h"


#include "SoundAdjuster.h"

#include "UnitNodeFactory.h"

MainWindowServer::MainWindowServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowServer)
{
    ui->setupUi(this);  

#ifdef QT_DEBUG
    auto action = new QPushButton("Read Pass", this);
    action->setCheckable(true);
    action->setChecked(Port::readPass);
    connect(action, &QPushButton::clicked, this,  [](auto ch){
        qDebug() << "Port::readPass = " << Port::readPass << " ch = " << ch;
        Port::readPass = ch;
        qDebug() << "Port::readPass = " << Port::readPass << " ch = " << ch;
    });
    ui->horizontalLayout->addWidget(action);
#endif


    QString buildPrefix = "";

#ifdef QT_DEBUG
    buildPrefix = "b";
#else
    buildPrefix = "r";
#endif

    QDate date = QLocale(QLocale::C).toDate(QString(__DATE__).simplified(), QLatin1String("MMM d yyyy"));
    this->setWindowTitle(tr("Сервер") + " - " + buildPrefix + "." + date.toString("dd.MM.yyyy"));

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
    modelJour->setForegroundRoleFlag(SwitchOffCondition::RegularOn);
    modelJour->setDecorationRoleFlag(SwitchOffCondition::RegularOn);
    modelJour->setEnabledReasonMeasure(true);

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

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(updDataTreeUN()),
            this,
            SLOT(createDiagnosticTable()));

    connect(ui->treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeUNCustomMenuRequested(QPoint)));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(startDKWait(int)),
            this,
            SLOT(startWaitProgressBar(int)));
    connect(&SignalSlotCommutator::instance(),
            SIGNAL(stopDKWait()),
            this,
            SLOT(stopWaitProgressBar()));
    connect(&SignalSlotCommutator::instance(),
            SIGNAL(endDKWait()),
            this,
            SLOT(stopWaitProgressBar()));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(startLockWait(int)),
            this,
            SLOT(startWaitProgressBar(int)));
    connect(&SignalSlotCommutator::instance(),
            SIGNAL(startLockWait(int,int)),
            this,
            SLOT(startWaitProgressBar(int,int)));
    connect(&SignalSlotCommutator::instance(),
            SIGNAL(stopLockWait()),
            this,
            SLOT(stopWaitProgressBar()));
    connect(&SignalSlotCommutator::instance(),
            SIGNAL(endLockWait()),
            this,
            SLOT(stopWaitProgressBar()));

    stopWaitProgressBar();
    connect(&quasiProgressBeat,
            SIGNAL(timeout()),
            this,
            SLOT(beatWaitProgressBar()));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(changeSelectUN(QSharedPointer<UnitNode>)),
            this,
            SLOT(changeSelectUN(QSharedPointer<UnitNode>)));
    connect(&SignalSlotCommutator::instance(),
            SIGNAL(forcedNewDuty(bool)),
            this,
            SLOT(forcedNewDuty(bool)));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(updateLabelOperator()),
            this,
            SLOT(initLabelOperator()));

    connect(&SignalSlotCommutator::instance(),
              SIGNAL(enable_updateListRecords()),
              this,
              SLOT(enable_updateListRecords()));

    ui->treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->treeView->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    ui->treeView->setStyleSheet("QTreeView::item{ height: 21px; margin: 0px 15px 0px 15px; padding: 0px; border-image: none;}");/*border:1px*/

    //    ui->tableView->setColumnWidth(0,50);
        ui->tableView->setColumnWidth(1,100);
        ui->tableView->setColumnWidth(2,180);
        ui->tableView->setColumnWidth(3,150);
        ui->tableView->setColumnWidth(4,100);
        ui->tableView->setColumnWidth(5,100);
        ui->tableView->setColumnWidth(6,100);

        if(!modelJour->getListJour().isEmpty())
            ui->tableView->verticalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        else
        ui->tableView->setColumnWidth(0,50);
     /*   ui->tableView->resizeColumnToContents(1);
     ui->tableView->resizeColumnToContents(2);
        ui->tableView->resizeColumnToContents(3);
        ui->tableView->resizeColumnToContents(4);
        ui->tableView->resizeColumnToContents(5);
        ui->tableView->resizeColumnToContents(6);
    */

    m_portManager->startStatusRequest();

    initLabelOperator();

    GraphTerminal::sendAbonentEventsAndStates(msg);

    preparePageCustomization();

    m_alarmSwitchOffLogger->start();

    {
        // Now add the line to the splitter handle
        // Note: index 0 handle is always hidden, index 1 is between the two widgets
        QSplitterHandle *handle = ui->splitter_TreeVsJour->handle(1);
        QHBoxLayout *layout = new QHBoxLayout(handle);
        layout->setSpacing(0);
        layout->setMargin(0);

        QFrame *line = new QFrame(handle);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setMaximumHeight(50);
        layout->addWidget(line, 0, Qt::AlignHCenter);
    }

    {
        // Now add the line to the splitter handle
        // Note: index 0 handle is always hidden, index 1 is between the two widgets
        QSplitterHandle *handle = ui->splitter_TreeVsCustomization->handle(1);
        QHBoxLayout *layout = new QHBoxLayout(handle);
        layout->setSpacing(0);
        layout->setMargin(0);

        QFrame *line = new QFrame(handle);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setMaximumWidth(50);
        layout->addWidget(line, 0, Qt::AlignVCenter);
    }

    {
        // Now add the line to the splitter handle
        // Note: index 0 handle is always hidden, index 1 is between the two widgets
        QSplitterHandle *handle = ui->splitter_JourVsDiagnostics->handle(1);
        QHBoxLayout *layout = new QHBoxLayout(handle);
        layout->setSpacing(0);
        layout->setMargin(0);

        QFrame *line = new QFrame(handle);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setMaximumWidth(50);
        layout->addWidget(line, 0, Qt::AlignVCenter);
    }

    connect(ui->comboBox_PointInput, SIGNAL(currentIndexChanged(int)), this, SLOT(fillPageTGAtPointInput(int)));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(insNewJourMSG(uint32_t)),
            this,
            SLOT(updateLabelCount()));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(insNewJourMSG(JourEntity)),
            this,
            SLOT(updateLabelCount()));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(insNewJourMSG()),
            this,
            SLOT(updateLabelCount()));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(updJourMSG(uint32_t)),
            this,
            SLOT(updateLabelCount()));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(updJourMSG()),
            this,
            SLOT(updateLabelCount()));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(updAllJourMSG()),
            this,
            SLOT(updateLabelCount()));

    connect(modelJour.data(),
            SIGNAL(dataChangedReason(JourEntity)),
            this,
            SLOT(updateLabelCount()));

    connect(modelJour.data(),
            SIGNAL(dataChangedMeasures(JourEntity)),
            this,
            SLOT(updateLabelCount()));


    updateLabelCount();

    connect(
      ui->tableView->selectionModel(),
      SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
      SLOT(tableView_selectionChanged())
     );    
    connect(
      modelJour.data(),
      SIGNAL(recalcSelectedMsg()),
      SLOT(tableView_selectionChanged())
     );

    m_labelClientCounter = QSharedPointer<QLabel>::create(statusBar());
    statusBar()->addWidget(m_labelClientCounter.data());
    connect(&SignalSlotCommutator::instance(), SIGNAL(changeCountIntegrationAbonent(int)), this, SLOT(changLabelClientCounter(int)));

//    SoundAdjuster::instance().init();


    connect(ui->splitter_TreeVsCustomization,
            SIGNAL(splitterMoved(int,int)),
            SLOT(splitterMovedSlot()));

    connect(ui->splitter_JourVsDiagnostics,
            SIGNAL(splitterMoved(int,int)),
            SLOT(splitterMovedSlot()));

    connect(ui->treeView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,
            SLOT(treeView_selectionChanged(QItemSelection,QItemSelection)));


    qDebug() << "ServerSettingUtils::checkAuditAdm -->" << ServerSettingUtils::checkAuditAdm();
}

void MainWindowServer::splitterMovedSlot(){
    qDebug() << "Customization" << ui->groupBox_Customization->size();
    qDebug() << "Diagnostic" << ui->tableWidget_Diagnostic->size() << ui->groupBox_Diagnostics->size();

}


MainWindowServer::~MainWindowServer()
{
    on_pushButtonResetFlags_clicked();

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
    Data.append(static_cast<uint8_t>(0xB5));
    Data.append(static_cast<uint8_t>(0xFF));
    Data.append(static_cast<char>(0x00));
    Data.append(static_cast<uint8_t>(0x22));
    Data.append(static_cast<uint8_t>(0x21));

    DataQueueItem itm(Data, QHostAddress("192.168.0.254"), 4001, 0);

    m_portManager->pushOverallWriteQueue(itm);
    m_portManager->write();
}

void MainWindowServer::updComboBoxReason() {
    updComboBox(ServerSettingUtils::getReasonTemplate(), ui->comboBoxReason);
}

void MainWindowServer::updComboBoxTakenMeasures() {
    updComboBox(ServerSettingUtils::getMeasureTemplate(), ui->comboBoxTakenMeasures);
}

void MainWindowServer::updComboBox(QList<QString> lst, QComboBox * cmb) {
    cmb->clear();
    cmb->addItems(lst);
    cmb->setCurrentIndex(-1);
}

void MainWindowServer::tuneDefaultNeededStateWordTypeSelectedlUN() const {
    if(!selUN.isNull()) {
        if(TypeUnitNodeEnum::TG == selUN->getType() ||
           TypeUnitNodeEnum::SD_BL_IP == selUN->getType() ||
           TypeUnitNodeEnum::IU_BL_IP == selUN->getType()) {
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
        if(TypeUnitNodeEnum::TG == selUN->getType()
        || TypeUnitNodeEnum::SD_BL_IP == selUN->getType()
        || TypeUnitNodeEnum::IU_BL_IP == selUN->getType()
        || TypeUnitNodeEnum::SSOI_SD_BL_IP == selUN->getType()
        || TypeUnitNodeEnum::SSOI_IU_BL_IP == selUN->getType()
        || TypeUnitNodeEnum::BOD_T4K_M == selUN->getType()
        || TypeUnitNodeEnum::Y4_T4K_M == selUN->getType()
        || TypeUnitNodeEnum::DD_T4K_M == selUN->getType()
        || TypeUnitNodeEnum::BOD_SOTA == selUN->getType()
        || TypeUnitNodeEnum::Y4_SOTA == selUN->getType()
        || TypeUnitNodeEnum::DD_SOTA == selUN->getType()) {
            if(!selUN->getParentUN().isNull()) {
                if(TypeUnitNodeEnum::TG_Base == selUN->getParentUN()->getType()) {
                    if(ui->groupBox_Customization->isVisible() && ui->groupBox_Diagnostics->isVisible()) { // настройка диагностика
                        selUN->getParentUN()->setNeededStateWordType(0x2A2C2E); // 32 & 34 & 33
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 3;
                    } else if(ui->groupBox_Customization->isVisible() && !ui->groupBox_Diagnostics->isVisible()) { // настройка
                        selUN->getParentUN()->setNeededStateWordType(0x2C2E); // 34 & 33
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 2;
                    } else if(!ui->groupBox_Customization->isVisible() && ui->groupBox_Diagnostics->isVisible()) { // диагностика
                        selUN->getParentUN()->setNeededStateWordType(/*0x2A2E*/0x2A2C2E); // 32 & 34 & 33
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 3;
                    } else if(!ui->groupBox_Customization->isVisible() && !ui->groupBox_Diagnostics->isVisible()) { //
                        selUN->getParentUN()->setNeededStateWordType(selUN->getParentUN()->getDefaultNeededStateWordType());
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 1;
                    } else {
                        selUN->getParentUN()->setNeededStateWordType(selUN->getParentUN()->getDefaultNeededStateWordType());
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 1;
                    }

                } else if(TypeUnitNodeEnum::BL_IP == selUN->getParentUN()->getType()) {
                    if(!ui->groupBox_Customization->isVisible() && ui->groupBox_Diagnostics->isVisible()) { // диагностика
                        selUN->getParentUN()->setNeededStateWordType(0x2225); // 41 & 42
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 2;
                    } else {
                        selUN->getParentUN()->setNeededStateWordType(selUN->getParentUN()->getDefaultNeededStateWordType());
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 1;
                    }
                } else if(TypeUnitNodeEnum::SSOI_BL_IP == selUN->getParentUN()->getType()) {
                    if(!ui->groupBox_Customization->isVisible() && ui->groupBox_Diagnostics->isVisible()) { // диагностика
                        selUN->getParentUN()->setNeededStateWordType(0x2225); // 41 & 42
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 2;
                    } else {
                        selUN->getParentUN()->setNeededStateWordType(selUN->getParentUN()->getDefaultNeededStateWordType());
                        selUN->getParentUN()->leftoversCounter.counter = 0;
                        selUN->getParentUN()->leftoversCounter.divider = 1;
                    }
                } else if(TypeUnitNodeEnum::BOD_T4K_M == selUN->getType()
                       || TypeUnitNodeEnum::BOD_SOTA == selUN->getType()) {
                    auto reciver = TopologyService::findReciver(selUN);
                    reciver->setNeededStateWordType(reciver->getDefaultNeededStateWordType());
                    reciver->leftoversCounter.counter = 0;
                    reciver->leftoversCounter.divider = 1;
                 } else if(TypeUnitNodeEnum::Y4_T4K_M == selUN->getType()
                        || TypeUnitNodeEnum::Y4_SOTA == selUN->getType()) {
                    auto reciver = TopologyService::findReciver(selUN);
                    reciver->setNeededStateWordType(reciver->getDefaultNeededStateWordType());
                    reciver->leftoversCounter.counter = 0;
                    reciver->leftoversCounter.divider = 1;
                 } else if(TypeUnitNodeEnum::DD_T4K_M == selUN->getType()
                        || TypeUnitNodeEnum::DD_SOTA == selUN->getType()) {
                    auto reciver = TopologyService::findReciver(selUN);
                    if(ui->groupBox_Customization->isVisible() && ui->groupBox_Diagnostics->isVisible()) { // настройка диагностика
                        reciver->setNeededStateWordType(0x2C2D2E); // 32 & 33
                        reciver->leftoversCounter.counter = 0;
                        reciver->leftoversCounter.divider = 7;
                        reciver->setInterrogationUN(selUN);
                    } else if(ui->groupBox_Customization->isVisible() && !ui->groupBox_Diagnostics->isVisible()) { // настройка
                        reciver->setNeededStateWordType(0x2C2E); // 32 & 33
                        reciver->leftoversCounter.counter = 0;
                        reciver->leftoversCounter.divider = 6;
                        reciver->setInterrogationUN(selUN);
                    } else if(!ui->groupBox_Customization->isVisible() && ui->groupBox_Diagnostics->isVisible()) { // диагностика
                        reciver->setNeededStateWordType(0x2D2E); // 32 & 33
                        reciver->leftoversCounter.counter = 0;
                        reciver->leftoversCounter.divider = 2;
                        reciver->setInterrogationUN(selUN);
                    } else {
                        reciver->setNeededStateWordType(reciver->getDefaultNeededStateWordType());
                        reciver->leftoversCounter.counter = 0;
                        reciver->leftoversCounter.divider = 1;
                    }
                } else {
                    selUN->getParentUN()->setNeededStateWordType(selUN->getParentUN()->getDefaultNeededStateWordType());
                    selUN->getParentUN()->leftoversCounter.counter = 0;
                    selUN->getParentUN()->leftoversCounter.divider = 1;
                }
            }
        } else if(TypeUnitNodeEnum::RLM_C == selUN->getType() ||
                  TypeUnitNodeEnum::RLM_KRL == selUN->getType()) {
            selUN->setNeededStateWordType(selUN->getDefaultNeededStateWordType());
            selUN->leftoversCounter.counter = 0;
            selUN->leftoversCounter.divider = 1;
        } else if(TypeUnitNodeEnum::BOD_T4K_M == selUN->getType()
               || TypeUnitNodeEnum::Y4_T4K_M == selUN->getType()
               || TypeUnitNodeEnum::BOD_SOTA == selUN->getType()
               || TypeUnitNodeEnum::Y4_SOTA == selUN->getType()) {
            auto reciver = TopologyService::findReciver(selUN);
            selUN->setNeededStateWordType(selUN->getDefaultNeededStateWordType());
            selUN->leftoversCounter.counter = 0;
            selUN->leftoversCounter.divider = 1;
            reciver->setInterrogationUN(QSharedPointer<UnitNode>(nullptr));
        } else if(TypeUnitNodeEnum::DD_T4K_M == selUN->getType()
               || TypeUnitNodeEnum::DD_SOTA == selUN->getType()) {
            auto reciver = TopologyService::findReciver(selUN);
            if(ui->groupBox_Customization->isVisible() && ui->groupBox_Diagnostics->isVisible()) { // настройка диагностика
                reciver->setNeededStateWordType(0x2C2D2E); // 32 & 33
                reciver->leftoversCounter.counter = 0;
                reciver->leftoversCounter.divider = 7;
                reciver->setInterrogationUN(selUN);
            } else if(ui->groupBox_Customization->isVisible() && !ui->groupBox_Diagnostics->isVisible()) { // настройка
                reciver->setNeededStateWordType(0x2C2D); // 32 & 33
                reciver->leftoversCounter.counter = 0;
                reciver->leftoversCounter.divider = 6;
                reciver->setInterrogationUN(selUN);
            } else if(!ui->groupBox_Customization->isVisible() && ui->groupBox_Diagnostics->isVisible()) { // диагностика
                reciver->setNeededStateWordType(0x2D2E); // 32 & 33
                reciver->leftoversCounter.counter = 0;
                reciver->leftoversCounter.divider = 2;
                reciver->setInterrogationUN(selUN);
            } else {
                reciver->setNeededStateWordType(reciver->getDefaultNeededStateWordType());
                reciver->leftoversCounter.counter = 0;
                reciver->leftoversCounter.divider = 1;
            }
        } else {
           selUN->setNeededStateWordType(selUN->getDefaultNeededStateWordType());
           selUN->leftoversCounter.counter = 0;
           selUN->leftoversCounter.divider = 1;
       }
    }
}

void MainWindowServer::treeView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    QModelIndexList indexes = selected.indexes();

    if(indexes.isEmpty()) {
        ui->labelSelectedUN->clear();
        ui->labelSelectedUN->setVisible(false);
        return;
    }

    const QModelIndex &index = indexes.first();

    QSharedPointer<UnitNode> sel = this->modelTreeUN->clickedUN(index);

    if(sel.isNull()) {
        ui->labelSelectedUN->clear();
        ui->labelSelectedUN->setVisible(false);
        return;
    }

    tuneDefaultNeededStateWordTypeSelectedlUN();
    selUN = sel;
    selIndex = index;

    tuneNeededStateWordTypeSelectedlUN();

    createDiagnosticTable();
    preparePageCustomization();



    if(TypeUnitNodeEnum::GROUP == selUN->getType()) {
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getType()) + ": \"" + sel->getName() + "\"");
    } else if(TypeUnitNodeEnum::SD_BL_IP == selUN->getType() && 1 == selUN->getBazalt()) {//БЛ-IP УЗ: СД:{Num2} + ИУ:{Num2} Кан:{UdpAdress}::{UdpPort}
        ui->labelSelectedUN->setText(QString("БЛ-IP УЗ:  СД:%1 + ИУ:%1").arg(sel->getNum2())
                                     + "  "
                                     + "Кан:"
                                     + sel->getUdpAdress()
                                     + "::"
                                     + QVariant(sel->getUdpPort()).toString()
                                     + QString(" %1").arg(Utils::outTypeToString(sel->getOutType())));
    } else if(TypeUnitNodeEnum::SD_BL_IP == selUN->getType()) {
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getParentUN()->getType())
                                     + "  "
                                     + "Кан:"
                                     + sel->getUdpAdress()
                                     + "::"
                                     + QVariant(sel->getUdpPort()).toString()
                                     + "  "
                                     + Utils::typeUNToStr(sel->getType())
                                     + ":"
                                     + QVariant(sel->getNum2()).toString()
                                     + QString(" %1").arg(Utils::outTypeToString(sel->getOutType()))
                                     );
    } else if(TypeUnitNodeEnum::IU_BL_IP == selUN->getType()) {
        auto setUN = Utils::findeSetAutoOnOffUN(selUN);
        QString subStr;
        if(!setUN.isEmpty()) {
            subStr.append("(Авто %1с.)");
            subStr = subStr.arg(UnitNodeCFG::adamOffToMs(as_const(setUN.values()).first()->getAdamOff()) / 1000);
        }
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getParentUN()->getType())
                                     + "  "
                                     + "Кан:"
                                     + sel->getUdpAdress()
                                     + "::"
                                     + QVariant(sel->getUdpPort()).toString()
                                     + "  "
                                     + Utils::typeUNToStr(sel->getType())
                                     + ":"
                                     + QVariant(sel->getNum2()).toString()
                                     + "  "
                                     + subStr
                                     );
    } else if(TypeUnitNodeEnum::RLM_KRL == selUN->getType()) {
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getType())
                                     + ":"
                                     + QString::number(sel->getNum1())
                                     + "  "
                                     + "Кан:"
                                     + sel->getUdpAdress()
                                     + "::"
                                     + QString::number(sel->getUdpPort())
                                     + QString(" %1").arg(Utils::outTypeToString(sel->getOutType()))
                                     );
    } else if(TypeUnitNodeEnum::RLM_C == selUN->getType()) {
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getType())
                                     + ":"
                                     + QString::number(sel->getNum1())
                                     + "  "
                                     + "Кан:"
                                     + sel->getUdpAdress()
                                     + "::"
                                     + QString::number(sel->getUdpPort())
                                     + QString(" %1").arg(Utils::outTypeToString(sel->getOutType()))
                                     );
    } else if(TypeUnitNodeEnum::TG == selUN->getType()) {
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getType())
                                     + ":" + QString::number(sel->getNum1())
                                     + "  "
                                     + "ЧЭ:"
                                     + QString::number(sel->getNum2())
                                     + "  "
                                     + "Кан:"
                                     + sel->getUdpAdress()
                                     + "::"
                                     + QString::number(sel->getUdpPort())
                                     + QString(" %1").arg(Utils::outTypeToString(sel->getOutType()))
                                     );
    } else if(TypeUnitNodeEnum::SSOI_SD_BL_IP == selUN->getType() && 1 == selUN->getBazalt()) {//БЛ-IP УЗ: СД:{Num2} + ИУ:{Num2} Кан:{UdpAdress}::{UdpPort}





        ui->labelSelectedUN->setText(QString("ССОИ БЛ-IP УЗ:  СД:%1 + ИУ:%1").arg(sel->getNum2())
                                     + "  "
                                     + QString("Адрес:%1").arg(sel->getNum1())
                                     + "  "
                                     + "Кан:"
                                     + sel->getUdpAdress()
                                     + "::"
                                     + QVariant(sel->getUdpPort()).toString()
                                     + QString(" %1").arg(Utils::outTypeToString(sel->getOutType())));
    } else if(TypeUnitNodeEnum::SSOI_SD_BL_IP == selUN->getType()) {

        QString sd=QVariant(sel->getNum2()).toString();
        if(sel->getNum2()==9)
            sd="Вскрытие";
        else
            sd=QVariant(sel->getNum2()).toString();

        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getParentUN()->getType())
                                     + "  "
                                     + QString("Адрес:%1").arg(sel->getNum1())
                                     + "  "
                                     + "Кан:"
                                     + sel->getUdpAdress()
                                     + "::"
                                     + QVariant(sel->getUdpPort()).toString()
                                     + "  "
                                     + Utils::typeUNToStr(sel->getType())
                                     + ":"
                                     + sd
                                     + QString(" %1").arg(Utils::outTypeToString(sel->getOutType()))
                                     );
    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == selUN->getType()) {
        auto setUN = Utils::findeSetAutoOnOffUN(selUN);
        QString subStr;
        if(!setUN.isEmpty()) {
            subStr.append("(Авто %1с.)");
            subStr = subStr.arg(UnitNodeCFG::adamOffToMs(as_const(setUN.values()).first()->getAdamOff()) / 1000);
        }
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getParentUN()->getType())
                                     + "  "
                                     + QString("Адрес:%1").arg(sel->getNum1())
                                     + "  "
                                     + "Кан:"
                                     + sel->getUdpAdress()
                                     + "::"
                                     + QVariant(sel->getUdpPort()).toString()
                                     + "  "
                                     + Utils::typeUNToStr(sel->getType())
                                     + ":"
                                     + QVariant(sel->getNum2()).toString()
                                     + "  "
                                     + subStr
                                     );
    } else {
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getType()) + "\t" + sel->getName());
    }
    ui->labelSelectedUN->setVisible(true);

}

void MainWindowServer::tableView_saveSelection()
{
    beginSelectRow = 2147483647;
    endSelectRow = -1;

    if(nullptr == ui || nullptr == ui->tableView || nullptr == ui->tableView->selectionModel())
        return;

    for(auto index : as_const(ui->tableView->selectionModel()->selectedRows())) {
        endSelectRow = qMax(endSelectRow, index.row());
        beginSelectRow = qMin(beginSelectRow, index.row());
    }
}

void MainWindowServer::changLabelClientCounter(int value)
{
    if(0 >= value) {
        m_labelClientCounter->setText("");
        m_labelClientCounter->setVisible(false);
        return;
    }
    m_labelClientCounter->setVisible(true);
    m_labelClientCounter->setText(tr("Клиентов: ") + QString::number(value));
}

void MainWindowServer::tableView_repairSelection()
{
    if(modelJour.isNull() || -1 == beginSelectRow || 2147483647 == endSelectRow)
        return;

    QModelIndex topLeft = modelJour->index(beginSelectRow, 0, QModelIndex());
    QModelIndex bottomRight = modelJour->index(endSelectRow, modelJour->columnCount() - 1, QModelIndex());
    auto selectionModel = ui->tableView->selectionModel();
    auto selection = selectionModel->selection();
    selection.select(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::Select | QItemSelectionModel::Rows);
}

void MainWindowServer::tableView_selectionChanged()
{
    selMsg = JourEntity();
    listSelMsg.clear();

    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    auto listJour = modelJour->listIndexsToListJours(selectedRows);

    if(1 == listJour.size()) {
        selMsg = listJour.first();
        listSelMsg = listJour;

        modelJour->selectOnedMsg(selMsg);

        ui->comboBoxReason->setCurrentIndex(-1);
        ui->comboBoxReason->setEditable(true);
        ui->comboBoxReason->setEditText(selMsg.getReason());

        ui->comboBoxTakenMeasures->setCurrentIndex(-1);
        ui->comboBoxTakenMeasures->setEditable(true);
        ui->comboBoxTakenMeasures->setEditText(selMsg.getMeasures());

        GraphTerminal::sendAbonentEventBook(selMsg);
        return;

    } else if(1 < listJour.size()) {
        selMsg = JourEntity();
        listSelMsg = listJour;
        ui->comboBoxReason->setEditText("");
        ui->comboBoxTakenMeasures->setEditText("");
    } else {
        selMsg = JourEntity();
        listSelMsg.clear();
        ui->comboBoxReason->setEditText("");
        ui->comboBoxTakenMeasures->setEditText("");
    }
}

void MainWindowServer::on_toolButtonReason_clicked()
{
    tableView_saveSelection();

    QSet<int> setId;
    for(const auto& j : as_const(listSelMsg)) {
        setId.insert(j.getId());
    }
    DataBaseManager::updateJourMsgFieldById("reason", ui->comboBoxReason->currentText(), setId);
    if(1 < setId.size()) {
        modelJour->updateAllRecords();
    } else {
        for(const auto& id : as_const(setId)) {
            SignalSlotCommutator::emitUpdJourMSG(id);
        }
    }
    tableView_selectionChanged();
    updateLabelCount();

    tableView_repairSelection();
}

void MainWindowServer::on_toolButtonTakenMeasures_clicked()
{
    tableView_saveSelection();

    QSet<int> setId;
    for(const auto& j : as_const(listSelMsg)) {
        setId.insert(j.getId());
    }
    DataBaseManager::updateJourMsgFieldById("measures", ui->comboBoxTakenMeasures->currentText(), setId);
    if(1 < setId.size()) {
        modelJour->updateAllRecords();
    } else {
        for(const auto& id : as_const(setId)) {
            SignalSlotCommutator::emitUpdJourMSG(id);
        }
    }
    tableView_selectionChanged();
    updateLabelCount();

    tableView_repairSelection();
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

    if(!ui->groupBox_Diagnostics->isVisible()) {
        ui->groupBox_Diagnostics->setMinimumSize(0,0);
        ui->groupBox_Diagnostics->setMaximumSize(16777215,16777215);
        return;
    }

    if(nullptr == this->selUN) {
        ui->groupBox_Diagnostics->setMinimumSize(0,0);
        ui->groupBox_Diagnostics->setMaximumSize(16777215,16777215);
        return;
    }

    if(TypeUnitNodeEnum::IU_BL_IP == selUN->getType()
    || TypeUnitNodeEnum::SD_BL_IP == selUN->getType()
    || TypeUnitNodeEnum::SSOI_IU_BL_IP == selUN->getType()
    || TypeUnitNodeEnum::SSOI_SD_BL_IP == selUN->getType()
    || TypeUnitNodeEnum::RLM_KRL == selUN->getType()
    || TypeUnitNodeEnum::RLM_C == selUN->getType()
    || TypeUnitNodeEnum::TG == selUN->getType()
    || TypeUnitNodeEnum::DD_T4K_M == selUN->getType()
    || TypeUnitNodeEnum::DD_SOTA == selUN->getType()
    || TypeUnitNodeEnum::Y4_SOTA == selUN->getType()
    || TypeUnitNodeEnum::BOD_SOTA == selUN->getType()
    || TypeUnitNodeEnum::BOD_T4K_M == selUN->getType()
    || TypeUnitNodeEnum::Y4_T4K_M == selUN->getType())
        ui->groupBox_Diagnostics->setVisible(true);
    else
        ui->groupBox_Diagnostics->setVisible(false);

    if(!ui->groupBox_Diagnostics->isVisible()) {
        ui->groupBox_Diagnostics->setMinimumSize(0,0);
        ui->groupBox_Diagnostics->setMaximumSize(16777215,16777215);
        return;
    }

//    ui->tableWidget->clear();
    ui->tableWidget_Diagnostic->verticalHeader()->hide();
    ui->tableWidget_Diagnostic->horizontalHeader()->hide();

    QString titleDiagnostic = "";
    if(TypeUnitNodeEnum::RLM_KRL == selUN->getType()) {
        titleDiagnostic = tr("Диагностика: РИФ-РЛМ(КРП),Трасса");
//        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: РИФ-РЛМ(КРП),Трасса"));
        ui->groupBox_Diagnostics->setMaximumHeight(315);
    } else if(TypeUnitNodeEnum::RLM_C == selUN->getType()) {
        titleDiagnostic = tr("Диагностика: РИФ-РЛМ-С");
//        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: РИФ-РЛМ-С"));
        ui->groupBox_Diagnostics->setMaximumHeight(435);
    } else if(TypeUnitNodeEnum::TG == selUN->getType()) {
        titleDiagnostic = tr("Диагностика: Точка/Гарда");
//        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: Точка/Гарда"));
        ui->groupBox_Diagnostics->setMaximumHeight(765);
    } else if(TypeUnitNodeEnum::DD_SOTA == selUN->getType()) {
        titleDiagnostic = tr("Диагностика: ДД Сота");
//        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: ДД Точка-М/Гарда, ДД Сота"));
        ui->groupBox_Diagnostics->setMaximumHeight(465);
    } else if(TypeUnitNodeEnum::DD_T4K_M == selUN->getType()) {
        titleDiagnostic = tr("Диагностика: ДД Точка-М/Гарда");
//        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: ДД Точка-М/Гарда, ДД Сота"));
        ui->groupBox_Diagnostics->setMaximumHeight(465);
    } else if(TypeUnitNodeEnum::Y4_SOTA == selUN->getType()
           || TypeUnitNodeEnum::BOD_SOTA == selUN->getType()) {
        titleDiagnostic = tr("Диагностика: Сота/Сота-М");
//        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: Сота/Сота-М"));
        ui->groupBox_Diagnostics->setMaximumHeight(645);
    } else if(TypeUnitNodeEnum::BOD_T4K_M == selUN->getType()
           || TypeUnitNodeEnum::Y4_T4K_M == selUN->getType()) {
        titleDiagnostic = tr("Диагностика: Точка-М/Гарда-М");
//        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: Точка-М/Гарда-М"));
        ui->groupBox_Diagnostics->setMaximumHeight(705);
    } else if(TypeUnitNodeEnum::SD_BL_IP == selUN->getType()
           || TypeUnitNodeEnum::IU_BL_IP == selUN->getType()) {
        titleDiagnostic = tr("Диагностика: БЛ-IP");
//        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: БЛ-IP"));
        ui->groupBox_Diagnostics->setMaximumHeight(495);
    } else if(TypeUnitNodeEnum::SSOI_SD_BL_IP == selUN->getType()
           || TypeUnitNodeEnum::SSOI_IU_BL_IP == selUN->getType()) {
        titleDiagnostic = tr("Диагностика: ССОИ БЛ-IP");
//        ui->groupBox_Diagnostics->setTitle(tr("Диагностика: ССОИ БЛ-IP"));
        ui->groupBox_Diagnostics->setMaximumHeight(525);
    }

#ifdef QT_DEBUG
    QTime time;
    for(const auto& sw : selUN->getStateWords()) {
        time = qMax(time, sw.second.getCdate().time());
    }
    titleDiagnostic += time.toString("hh:mm:ss.zzz");
#endif

    ui->groupBox_Diagnostics->setTitle(titleDiagnostic);

    Utils::fillDiagnosticTable(ui->tableWidget_Diagnostic, this->selUN);

//    if(0 < ui->tableWidget_Diagnostic->rowCount() && 0 < ui->tableWidget_Diagnostic->columnCount()) {
//        ui->tableWidget_Diagnostic->resizeColumnsToContents();
//        ui->tableWidget_Diagnostic->resizeRowsToContents();
//        qDebug() << "tableWidget_Diagnostic -->";
//        for(auto i = 0; i < ui->tableWidget_Diagnostic->columnCount(); i++) {
//            qDebug() << "c" << i << "s" <<  ui->tableWidget_Diagnostic->columnWidth(i);
//        }
//        qDebug() << "tableWidget_Diagnostic <--";
//    }


    auto contentSize = Utils::getQTableWidgetContentSize(ui->tableWidget_Diagnostic);
//    ui->tableWidget_Diagnostic->setMinimumSize(contentSize);
//    ui->tableWidget_Diagnostic->setMaximumHeight(contentSize.height() + 15);
}

void MainWindowServer::on_pushButtonResetFlags_clicked()
{

    if(0 != checkNecessarilyReasonMeasureFill()) {
        MessageBoxServer::infoAllRequiredFieldsInTheDatabaseAreNotFilledIn();
        return;
    }

    const auto& tmpSet = TopologyService::getSortedMetaRealUnitNodes();
    for(const auto& un : tmpSet) {
        un->resetClearedAlarm();
    }

    this->m_portManager->requestResetFlags();
//    {
//        JourEntity msgOn;
//        msgOn.setObject(tr("Оператор"));
//        msgOn.setType(135);
//        msgOn.setComment(tr("Послана ком. Сброс тревог"));
//        DataBaseManager::insertJourMsg_wS(msgOn);
//        GraphTerminal::sendAbonentEventsAndStates(msgOn);
//    }

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
        this->selUN = QSharedPointer<UnitNode>(nullptr);
        selIndex = QModelIndex();
        return;
    }
    QSharedPointer<UnitNode>  sel = this->modelTreeUN->clickedUN(index);
    if(sel.isNull())
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
    } else if(TypeUnitNodeEnum::SSOI_SD_BL_IP == sel->getType()) {
        if(sel->isEditableControl() && 1 != sel->getBazalt()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

//        if(isDebug) { //! debug
//            menu->addAction(ui->actionUNOff);
//            menu->addAction(ui->actionUNOn);
//        } else if(sel->isEditableOnOff() && 1 == sel->swpSSOISDBLIPType0x41().isOn() && 1 != sel->getBazalt() && 9 > sel->getNum2()) {
//            menu->addAction(ui->actionUNOff);
//        } else if(sel->isEditableOnOff() && 1 == sel->swpSSOISDBLIPType0x41().isOff() && 1 != sel->getBazalt() && 9 > sel->getNum2()) {
//            menu->addAction(ui->actionUNOn);
//        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionClose);
            menu->addAction(ui->actionOpen);
            menu->addSeparator();
        } else if(0 != sel->getBazalt() && 1 == sel->swpSSOISDBLIPType0x41().isInAlarm() && 9 > sel->getNum2()) {
            menu->addAction(ui->actionClose);
            menu->addSeparator();
        } else if(0 != sel->getBazalt() && 1 == sel->swpSSOISDBLIPType0x41().isInNorm() && 9 > sel->getNum2()) {
            menu->addAction(ui->actionOpen);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        } else if(0 == sel->getBazalt() && 0 != sel->getDK() && 9 > sel->getNum2()) {
            menu->addAction(ui->actionDK);
        }

    } else if(TypeUnitNodeEnum::SD_BL_IP == sel->getType()) {

        if(sel->isEditableControl() && 1 != sel->getBazalt()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
        } else if(sel->isEditableOnOff() && 1 == sel->swpSDBLIPType0x41().isOn() && 1 != sel->getBazalt()) {
            menu->addAction(ui->actionUNOff);
        } else if(sel->isEditableOnOff() && 1 == sel->swpSDBLIPType0x41().isOff() && 1 != sel->getBazalt()) {
            menu->addAction(ui->actionUNOn);
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionClose);
            menu->addAction(ui->actionOpen);
            menu->addSeparator();
        } else if(0 != sel->getBazalt() && (1 == sel->swpSDBLIPType0x41().isAlarm())) {
            menu->addAction(ui->actionClose);
            menu->addSeparator();
        } else if(0 != sel->getBazalt() && (1 == sel->swpSDBLIPType0x41().isNorm())) {
            menu->addAction(ui->actionOpen);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        } else if(0 == sel->getBazalt() && 0 != sel->getDK()) {
            menu->addAction(ui->actionDK);
        }

    } else if(TypeUnitNodeEnum::IU_BL_IP == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpIUBLIPType0x41().isOn())) {
            menu->addAction(ui->actionUNOff);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpIUBLIPType0x41().isOff())) {
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        } else if(0 == sel->getBazalt() && 0 != sel->getDK()) {
            menu->addAction(ui->actionDK);
        }

    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && 1 == sel->swpSSOIIUBLIPType0x41().isOn()) {
            menu->addAction(ui->actionUNOff);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && 1 == sel->swpSSOIIUBLIPType0x41().isOff()) {
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        } else if(0 == sel->getBazalt() && 0 != sel->getDK()) {
            menu->addAction(ui->actionDK);
        }

    } else if(TypeUnitNodeEnum::RLM_C == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpRLMCType0x31().isOn())) {
            menu->addAction(ui->actionUNOff);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpRLMCType0x31().isOff())) {
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        }

        menu->addAction(ui->actionDK);

    } else if(TypeUnitNodeEnum::RLM_KRL == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpRLMType0x31().isOn())) {
            menu->addAction(ui->actionUNOff);
            menu->addSeparator();
        } else if(sel->isEditableOnOff() && (1 == sel->swpRLMType0x31().isOff())) {
            menu->addAction(ui->actionUNOn);
            menu->addSeparator();
        }

        menu->addAction(ui->actionDK);

    } else if(TypeUnitNodeEnum::TG == sel->getType()) {

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

        menu->addAction(ui->actionDK);

    } else if(TypeUnitNodeEnum::BOD_T4K_M == sel->getType()
           || TypeUnitNodeEnum::BOD_SOTA == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionClose);
            menu->addAction(ui->actionOpen);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        } else if(0 != sel->getDK()) {
            menu->addAction(ui->actionDK);
        }

    } else if(TypeUnitNodeEnum::Y4_T4K_M == sel->getType()
              || TypeUnitNodeEnum::Y4_SOTA == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionClose);
            menu->addAction(ui->actionOpen);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        }

    } else if(TypeUnitNodeEnum::DD_T4K_M == sel->getType()
              || TypeUnitNodeEnum::DD_SOTA == sel->getType()) {

        if(sel->isEditableControl()) {
            menu->addAction(ui->actionControl);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionUNOff);
            menu->addAction(ui->actionUNOn);
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionClose);
            menu->addAction(ui->actionOpen);
            menu->addSeparator();
        }

        if(isDebug) { //! debug
            menu->addAction(ui->actionDK);
        }

    }

    if(!sel->getName().isEmpty() && !(TypeUnitNodeEnum::SYSTEM == sel->getType() || TypeUnitNodeEnum::GROUP == sel->getType())) {
        menu->addAction(ui->actionUNSqlSelect);
        setUnSqlSelect(QString("SELECT id, cdate, mdate, objectid, object, comment, reason, measures, operator, operatorid, status, direction, type, flag, d1, d2, d3, d4, objecttype FROM public.jour where object = \'%1\' ORDER BY id").arg(sel->getName()));

        setUnArgSelect(QStringList({
                                       QString("-type %1").arg(sel->getType())
                                     , QString("-num1 %1").arg(sel->getNum1())
                                     , QString("-num2 %1").arg(sel->getNum2())
                                     , QString("-num3 %1").arg(sel->getNum3())
                                     , QString("-outType %1").arg(sel->getOutType())
                                     , QString("-adamOff %1").arg(sel->getAdamOff())
                                     , QString("-bazalt %1").arg(sel->getBazalt())
                                     , QString("-ip %1").arg(sel->getUdpAdress())
                                     , QString("-databasename %1").arg(DataBaseManager::getHostName())
                                     , QString("-username %1").arg(DataBaseManager::getUserName())
                                     , QString("-password %1").arg(DataBaseManager::getPassword())
                                     , QString("-port %1").arg(DataBaseManager::getPort())
                                   }).join(" "));
    }

    /* Call the context menu */
//        menu->popup(ui->treeView->viewport()->mapToGlobal(pos));

#ifdef QT_DEBUG
    auto action = new QAction("Alarm To IU", this);
    connect(action, &QAction::triggered, this,  [sel](){

        QSet<QSharedPointer<UnitNode>> tmpSet;
        if(TypeUnitNodeEnum::TG == sel->getType()
        || TypeUnitNodeEnum::RLM_C == sel->getType()
        || TypeUnitNodeEnum::RLM_KRL == sel->getType()
        || (TypeUnitNodeEnum::SD_BL_IP == sel->getType() && 1 != sel->getBazalt())
        || (TypeUnitNodeEnum::SSOI_SD_BL_IP == sel->getType() && 1 != sel->getBazalt())
                ) {
            tmpSet.insert(sel);
        }
        for(const auto& un : as_const(sel->listTreeChilds())) {
            const auto un1 = qSharedPointerCast<UnitNode>(un);
            if(TypeUnitNodeEnum::TG == un1->getType()
            || TypeUnitNodeEnum::RLM_C == un1->getType()
            || TypeUnitNodeEnum::RLM_KRL == un1->getType()
            || (TypeUnitNodeEnum::SD_BL_IP == un1->getType() && 1 != un1->getBazalt())
            || (TypeUnitNodeEnum::SSOI_SD_BL_IP == un1->getType() && 1 != un1->getBazalt())
                    ) {
                tmpSet.insert(qSharedPointerCast<UnitNode>(un));
            }
        }
        for(const auto& un : tmpSet) {
            for(const auto& iuun : as_const(TopologyService::getLinkedUI(un))) {
                qDebug() << "Alarm To " <<iuun->toString() << "IU From " << un->toString();
                SignalSlotCommutator::emitAutoOnOffIU(true, false, qSharedPointerCast<UnitNode>(iuun));
            }
        }
    });
    menu->addAction(action);
#endif

    menu->exec(ui->treeView->viewport()->mapToGlobal(pos));
}

void MainWindowServer::on_actionDK_triggered()
{
    this->m_portManager->requestDK(false, false, this->selUN);
    ui->treeView->resizeColumnToContents(0);
}

void MainWindowServer::stopWaitProgressBar()
{
    qDebug() << "MainWindowServer::stopWaitProgressBar()";
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
    if(0 == ui->progressBarDKWait->value()) {
        ui->progressBarDKWait->setVisible(false);
    } else if(100 == ui->progressBarDKWait->value()) {
            ui->progressBarDKWait->setVisible(false);
            quasiProgressBeat.stop();
    } else {
        ui->progressBarDKWait->setVisible(true);
    }
}

void MainWindowServer::startWaitProgressBar(int interval)
{
    stopWaitProgressBar();
    qDebug() << "MainWindowServer::startWaitProgressBar(" << interval << ")";
    waitIntervalProgressBar = interval;
    wasIntervalProgressBar = 0.0;
    quasiProgressBeat.start(100);
    ui->progressBarDKWait->setVisible(false);
}

void MainWindowServer::startWaitProgressBar(int interval, int startInterval)
{
    qDebug() << "MainWindowServer::startWaitProgressBar(" << interval << "," << startInterval << ")";
    quasiProgressBeat.stop();
    waitIntervalProgressBar = interval;
    wasIntervalProgressBar = startInterval;
    float val = (( wasIntervalProgressBar / (float)waitIntervalProgressBar) * 100.0);
    ui->progressBarDKWait->setValue((int)val % 101);
    if(100 == ui->progressBarDKWait->value() || 0 == ui->progressBarDKWait->value())
        ui->progressBarDKWait->setVisible(false);
    else
        ui->progressBarDKWait->setVisible(true);
    quasiProgressBeat.start(100);
}

void MainWindowServer::on_actionRifDKOverall_triggered()
{
    this->m_portManager->requestDK(false, false);
    if(!TopologyService::getSystemUnitNodes().isNull())
        TopologyService::getSystemUnitNodes()->setDkInvolved(true);
    ui->treeView->resizeColumnToContents(0);
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

    if((TypeUnitNodeEnum::SD_BL_IP == selUN->getType() && 1 != selUN->getBazalt()) ||
       (TypeUnitNodeEnum::SSOI_SD_BL_IP == selUN->getType() && 1 != selUN->getBazalt()) ||
       TypeUnitNodeEnum::RLM_C == selUN->getType() ||
       TypeUnitNodeEnum::RLM_KRL == selUN->getType() ||
       TypeUnitNodeEnum::TG == selUN->getType()) {
        if(!ServerSettingUtils::checkDialogAuditAdm())
            return;
    }

    const auto& setUn = Utils::findeSetAutoOnOffUN(selUN);
    if(setUn.isEmpty())
        this->m_portManager->requestOnOffCommand(false, false, selUN, true);
    else {
        const auto& un = setUn.values().first();
        this->m_portManager->requestAutoOnOffIUCommand(false, false, un);
    }
}

void MainWindowServer::on_actionUNOff_triggered()
{
    if(selUN.isNull())
        return;

    if((TypeUnitNodeEnum::SSOI_SD_BL_IP == selUN->getType() && 1 != selUN->getBazalt()) ||
       (TypeUnitNodeEnum::SD_BL_IP == selUN->getType() && 1 != selUN->getBazalt()) ||
       TypeUnitNodeEnum::RLM_C == selUN->getType() ||
       TypeUnitNodeEnum::RLM_KRL == selUN->getType() ||
       TypeUnitNodeEnum::TG == selUN->getType()) {
        if(!ServerSettingUtils::checkDialogAuditAdm())
            return;
    }

    if(TypeUnitNodeEnum::RLM_C == selUN->getType() ||
       TypeUnitNodeEnum::RLM_KRL == selUN->getType() ||
       TypeUnitNodeEnum::TG == selUN->getType()) {
        int ret = MessageBoxServer::questionDoYouReallyWantToDisconnectTheDevice();

        if(QMessageBox::Ok != ret) {
            return;
        }
    }
    this->m_portManager->requestOnOffCommand(false, false, selUN, false);
}

void MainWindowServer::on_actionControl_triggered()
{
    if(selUN.isNull())
        return;


    if(!selUN->isEditableControl())
        return;

//    QString strQuestion;
    int ret = 0;
    if(selUN->getControl())
        ret = MessageBoxServer::questionRemoveTheControl();
    else
        ret = MessageBoxServer::questionRestoreControl();

    if(QMessageBox::Ok == ret) {
        selUN->setControl(!selUN->getControl());

        JourEntity msgOn;
        msgOn.setObject(selUN->getName());
        msgOn.setObjecttype(selUN->getType());
        msgOn.setD1(selUN->getNum1());
        msgOn.setD2(selUN->getNum2());
        msgOn.setD3(selUN->getNum3());
        msgOn.setD4(selUN->getOutType());
        msgOn.setDirection(selUN->getDirection());
        msgOn.setType((selUN->getControl() ? 137 : 136));
        msgOn.setComment(tr("Контроль ") + (selUN->getControl() ? tr("Вкл") : tr("Выкл")));
        msgOn.setParams(selUN->makeJson());

        if(TypeUnitNodeEnum::BOD_T4K_M == selUN->getType()
                || TypeUnitNodeEnum::Y4_T4K_M == selUN->getType()
                || TypeUnitNodeEnum::BOD_SOTA == selUN->getType()
                || TypeUnitNodeEnum::Y4_SOTA == selUN->getType()) {
            for(const auto &un : as_const(TopologyService::findChild(selUN))) {
                un->setControl(!un->getControl());
                if(un->getControl()) {
                    un->setPublishedState(-1);
                }
                un->updDoubl();
            }
        }

        if(!selUN->getName().isEmpty() && 1 != selUN->getMetaEntity()) {
            DataBaseManager::insertJourMsg_wS(msgOn);
            GraphTerminal::sendAbonentEventsAndStates(selUN, msgOn);
        }

        if(selUN->getControl()) {
            GraphTerminal::sendAbonentEventsAndStates(selUN);
            selUN->setPublishedState(-1);
        }
        selUN->updDoubl();
    }
}

void MainWindowServer::closeEvent(QCloseEvent * event)
{
    int ret = MessageBoxServer::questionShutDownAndExitTheProgram();

    if(0 != checkNecessarilyReasonMeasureFill()) {
        MessageBoxServer::infoAllRequiredFieldsInTheDatabaseAreNotFilledIn();
        event->ignore();
        return;
    }

    if(QMessageBox::Ok == ret) {
        event->accept();
    } else {
        event->ignore();
    }
    //Здесь код
}

const QString &MainWindowServer::getUnArgSelect() const
{
    return unArgSelect;
}

void MainWindowServer::setUnArgSelect(const QString &newUnArgSelect)
{
    unArgSelect = newUnArgSelect;
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

void MainWindowServer::updateLabelCount()
{
    if(modelJour.isNull())
        return;

    int needReason = IniFileService::getValueBySectionKey("PostgresSQL", "P1", "0").toInt();
    int needMeasure = IniFileService::getValueBySectionKey("PostgresSQL", "P2", "0").toInt();
    if(0 != needReason || 0 != needMeasure) {

        int countReason = 0;
        int countMeasure = 0;

        auto listJour = modelJour->getListJour();
        for(const auto& ji : as_const(listJour)) {
            if(0 != needReason && ServerSettingUtils::getPriorityJoutTyper().contains(ji.getType()) && ji.getReason().isEmpty()) {
                countReason++;
            }
            if (0 != needMeasure && ServerSettingUtils::getPriorityJoutTyper().contains(ji.getType()) && ji.getMeasures().isEmpty()) {
                countMeasure++;
            }
        }

        if (0 != needReason) {
            ui->labelCountReason->setText(QString::number(countReason));
            ui->labelCountReason->setVisible(true);
        } else {
            ui->labelCountReason->setText("");
            ui->labelCountReason->setVisible(false);
        }

        if (0 != needMeasure) {
            ui->labelCountTakenMeasures->setText(QString::number(countMeasure));
            ui->labelCountTakenMeasures->setVisible(true);
        } else {
            ui->labelCountTakenMeasures->setText("");
            ui->labelCountTakenMeasures->setVisible(false);
        }

    } else {
        ui->labelCountReason->setText("");
        ui->labelCountTakenMeasures->setText("");
        ui->labelCountReason->setVisible(false);
        ui->labelCountTakenMeasures->setVisible(false);
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

    ui->treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->treeView->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);


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

    ui->treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->treeView->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    ui->tableView->verticalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
//    ui->tableView->resizeColumnToContents(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    ui->tableView->resizeColumnToContents(3);
    ui->tableView->resizeColumnToContents(4);
    ui->tableView->resizeColumnToContents(5);
    ui->tableView->resizeColumnToContents(6);

    ui->tableView->update();
}

int MainWindowServer::checkNecessarilyReasonMeasureFill() {
    if(modelJour.isNull())
        return -1;

    int needReason = IniFileService::getValueBySectionKey("PostgresSQL", "P1", "0").toInt();
    int needMeasure = IniFileService::getValueBySectionKey("PostgresSQL", "P2", "0").toInt();
    if(0 != needReason || 0 != needMeasure) {

        int countReason = 0;
        int countMeasure = 0;

        auto listJour = modelJour->getListJour();
        for(const auto& ji : as_const(listJour)) {
            if(0 != needReason && ServerSettingUtils::getPriorityJoutTyper().contains(ji.getType()) && ji.getReason().isEmpty()) {
                countReason++;
            }
            if (0 != needMeasure && ServerSettingUtils::getPriorityJoutTyper().contains(ji.getType()) && ji.getMeasures().isEmpty()) {
                countMeasure++;
            }
        }

        if ((0 != needReason && 0 != countReason) || (0 != needMeasure && 0 != countMeasure)) {
//            MessageBoxServer::infoAllRequiredFieldsInTheDatabaseAreNotFilledIn();
            return countReason + countMeasure;
        }

    }

    return 0;
}

void MainWindowServer::on_actionNewScheme_triggered()
{
    int ret = MessageBoxServer::questionStartANewShift();

    if(QMessageBox::Ok == ret) {

        if(0 != checkNecessarilyReasonMeasureFill()) {
            MessageBoxServer::infoAllRequiredFieldsInTheDatabaseAreNotFilledIn();
            return;
        }

        AuthenticationDialog ad;
        if(0 != ad.getInitialResult()) {
            if(QDialog::Accepted != ad.exec()) {
                MessageBoxServer::infoErrorInSelectingTheOperatorOfTheComplex();
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
    if(!selUN.isNull() && !selUN->getName().isEmpty() && !(TypeUnitNodeEnum::SYSTEM == selUN->getType() || TypeUnitNodeEnum::GROUP == selUN->getType())) {
        QStringList sl({
                                       codec->fromUnicode(QString("-type")), codec->fromUnicode(QString::number(selUN->getType()))
                                     , codec->fromUnicode(QString("-num1")), codec->fromUnicode(QString::number(selUN->getNum1()))
                                     , codec->fromUnicode(QString("-num2")), codec->fromUnicode(QString::number(selUN->getNum2()))
                                     , codec->fromUnicode(QString("-num3")), codec->fromUnicode(QString::number(selUN->getNum3()))
                                     , codec->fromUnicode(QString("-outType")), codec->fromUnicode(QString::number(selUN->getOutType()))
                                     , codec->fromUnicode(QString("-adamOff")), codec->fromUnicode(QString::number(selUN->getAdamOff()))
                                     , codec->fromUnicode(QString("-bazalt")), codec->fromUnicode(QString::number(selUN->getBazalt()))
                                     , codec->fromUnicode(QString("-ip")), codec->fromUnicode(QString(selUN->getDirection()))
                                     , codec->fromUnicode(QString("-databasename")), codec->fromUnicode(QString(DataBaseManager::getHostName()))
                                     , codec->fromUnicode(QString("-username")), codec->fromUnicode(QString(DataBaseManager::getUserName()))
                                     , codec->fromUnicode(QString("-password")), codec->fromUnicode(QString(DataBaseManager::getPassword()))
                                     , codec->fromUnicode(QString("-port")), codec->fromUnicode(QString(DataBaseManager::getPort()))
                                   });
        process->start(file, QStringList() << sl);
        return;

    }

    process->start(file, QStringList() << codec->fromUnicode(getUnArgSelect()));

//    process->start(file, QStringList() << codec->fromUnicode("-sql") << codec->fromUnicode("\"" + getUnSqlSelect() + "\""));
}

void MainWindowServer::changeSelectUN(QSharedPointer<UnitNode> un)
{
    if(nullptr == un)
        return;
    QModelIndex index = this->modelTreeUN->findeIndexUN(un.data());
    ui->treeView->setCurrentIndex(index);
}

void MainWindowServer::preparePageCustomization()
{

    if(!ui->actionCustomization->isChecked()) {
        ui->groupBox_Customization->setVisible(false);
        ui->groupBox_Customization->setMinimumSize(0,0);
        ui->groupBox_Customization->setMaximumSize(16777215,16777215);
        return;
    }

    if(selUN.isNull()) {
        ui->groupBox_Customization->setVisible(false);
        ui->groupBox_Customization->setMinimumSize(0,0);
        ui->groupBox_Customization->setMaximumSize(16777215,16777215);
        return;
    }

    if(!ServerSettingUtils::checkDialogAuditAdm()) {
        ui->actionCustomization->setChecked(false);
        on_actionCustomization_triggered();
        return;
    }

    switch (selUN->getType()) {
    case TypeUnitNodeEnum::RLM_KRL:
    case TypeUnitNodeEnum::RLM_C:
        preparePageRLM(selUN);
        ui->stackedWidget->setCurrentIndex(0);
        ui->groupBox_Customization->setMinimumWidth(345);
        ui->groupBox_Customization->setMaximumHeight(140);
        ui->groupBox_Customization->setMinimumHeight(140);
        break;
    case TypeUnitNodeEnum::TG:
        preparePagePoint();
        ui->stackedWidget->setCurrentIndex(3);
        ui->groupBox_Customization->setMinimumWidth(310);
        ui->groupBox_Customization->setMaximumHeight(165);
        ui->groupBox_Customization->setMinimumHeight(165);
        break;
    case TypeUnitNodeEnum::DD_SOTA:
        preparePageSOTA();
        ui->stackedWidget->setCurrentIndex(1);
        ui->groupBox_Customization->setMinimumWidth(330);
        ui->groupBox_Customization->setMaximumHeight(275);
        ui->groupBox_Customization->setMinimumHeight(275);
        break;
    case TypeUnitNodeEnum::DD_T4K_M:
        preparePageT4KDD();
        ui->stackedWidget->setCurrentIndex(2);
        ui->groupBox_Customization->setMinimumWidth(330);
        ui->groupBox_Customization->setMaximumHeight(560);
        ui->groupBox_Customization->setMinimumHeight(310);
        break;
    default:
        ui->groupBox_Customization->setMinimumSize(0,0);
        ui->groupBox_Customization->setMaximumSize(16777215,16777215);
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

    if(TypeUnitNodeEnum::RLM_C == un->getType()) {
        for(int i = 0, n = 5; i < n; i++) {
            ui->comboBox_RLMTactPeriod->addItem(QString(tr("Такт") + " %1").arg(i + 1), i);
        }
    } else if(TypeUnitNodeEnum::RLM_KRL == un->getType() &&
              (0 == un->getAdamOff() ||
               1 == un->getAdamOff())) {
        for(int i = 0, n = 4; i < n; i++) {
            ui->comboBox_RLMTactPeriod->addItem(QString(tr("Такт") + " %1").arg(i + 1), i);
        }
    } else if(TypeUnitNodeEnum::RLM_KRL == un->getType() &&
              (3 == un->getAdamOff() ||
              2 == un->getAdamOff())) {
        for(int i = 0, n = 2; i < n; i++) {
            ui->comboBox_RLMTactPeriod->addItem(QString(tr("Такт") + " %1").arg(i + 1), i);
        }
    } else if(TypeUnitNodeEnum::RLM_KRL == un->getType() &&
              4 == un->getAdamOff()) {
        for(int i = 0, n = 4; i < n; i++) {
            ui->comboBox_RLMTactPeriod->addItem(QString(tr("УШ") + " %1").arg(i + 1), i);
        }
    }

    if(TypeUnitNodeEnum::RLM_KRL == un->getType() &&
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
    if(TypeUnitNodeEnum::RLM_C == un->getType() ||
       (TypeUnitNodeEnum::RLM_KRL == un->getType() &&
        (0 == un->getAdamOff() ||
         1 == un->getAdamOff() ||
         2 == un->getAdamOff()))) {
        ui->comboBox_RLMCondition->addItem(tr("Основной"), 0);
        ui->comboBox_RLMCondition->addItem(tr("Дополнительный"), 1);
    } else if(TypeUnitNodeEnum::RLM_KRL == un->getType() &&
               3 == un->getAdamOff()) {
        ui->comboBox_RLMCondition->addItem(tr("Нормальный"), 0);
        ui->comboBox_RLMCondition->addItem(tr("Помехозащищенный"), 1);
    } else if(TypeUnitNodeEnum::RLM_KRL == un->getType() &&
               4 == un->getAdamOff()) {
        ui->comboBox_RLMCondition->addItem(tr("Настройка"), 0);
        ui->comboBox_RLMCondition->addItem(tr("Работа"), 1);
    } else if(TypeUnitNodeEnum::RLM_KRL == un->getType() &&
              5 == un->getAdamOff()) {
        ui->comboBox_RLMCondition->addItem(tr("Медленный"), 0);
        ui->comboBox_RLMCondition->addItem(tr("Быстрый"), 1);
    }
    if(TypeUnitNodeEnum::RLM_C == un->getType()) {
        ui->comboBox_RLMCondition->addItem(tr("Ползущий (Плз)"), 2);
        ui->comboBox_RLMCondition->addItem(tr("2-й ярус (2Яр)"), 3);
    }
    ui->comboBox_RLMCondition->setEnabled(true);

    ui->comboBox_RLMEdge->clear();
    ui->comboBox_RLMEdge->setEnabled(false);
    ui->comboBox_RLMEdge->setEditable(false);
    ui->comboBox_RLMEdge->addItem(tr("Неопределено"));
    if(TypeUnitNodeEnum::RLM_C == un->getType()) {
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
    } else if(TypeUnitNodeEnum::RLM_KRL == un->getType() &&
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
    } else if(TypeUnitNodeEnum::RLM_KRL == un->getType() &&
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
    } else if(TypeUnitNodeEnum::RLM_KRL == un->getType() &&
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

void MainWindowServer::preparePagePoint()
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
    ui->spinBox_PointFlt1Edge->setMaximum(49999);
    ui->spinBox_PointFlt1Edge->setMinimum(0);
    ui->spinBox_PointFlt1Edge->setEnabled(true);

    ui->spinBox_PointFlt2Edge->clear();
    ui->spinBox_PointFlt2Edge->setEnabled(false);
    ui->spinBox_PointFlt2Edge->setValue(0);
    ui->spinBox_PointFlt2Edge->setMaximum(49999);
    ui->spinBox_PointFlt2Edge->setMinimum(0);
    ui->spinBox_PointFlt2Edge->setEnabled(true);

    ui->spinBox_PointFlt3Edge->clear();
    ui->spinBox_PointFlt3Edge->setEnabled(false);
    ui->spinBox_PointFlt3Edge->setValue(0);
    ui->spinBox_PointFlt3Edge->setMaximum(49999);
    ui->spinBox_PointFlt3Edge->setMinimum(0);
    ui->spinBox_PointFlt3Edge->setEnabled(true);

    fillPageTG();
}

void MainWindowServer::preparePageSOTA()
{
    ui->comboBox_SOTADDF1OnOff->clear();
    ui->comboBox_SOTADDF1OnOff->setEnabled(false);
    ui->comboBox_SOTADDF1OnOff->setEditable(false);
    ui->comboBox_SOTADDF1OnOff->addItem(tr("Выкл"), 0);
    ui->comboBox_SOTADDF1OnOff->addItem(tr("Вкл"), 1);
    ui->comboBox_SOTADDF1OnOff->setEnabled(true);

    ui->comboBox_SOTADDF2OnOff->clear();
    ui->comboBox_SOTADDF2OnOff->setEnabled(false);
    ui->comboBox_SOTADDF2OnOff->setEditable(false);
    ui->comboBox_SOTADDF2OnOff->addItem(tr("Выкл"), 0);
    ui->comboBox_SOTADDF2OnOff->addItem(tr("Вкл"), 1);
    ui->comboBox_SOTADDF2OnOff->setEnabled(true);

    ui->spinBox_SOTADDF1Threshold->clear();
    ui->spinBox_SOTADDF1Threshold->setEnabled(false);
    ui->spinBox_SOTADDF1Threshold->setValue(0);
    ui->spinBox_SOTADDF1Threshold->setMaximum(65535);
    ui->spinBox_SOTADDF1Threshold->setMinimum(0);
    ui->spinBox_SOTADDF1Threshold->setEnabled(true);

    ui->spinBox_SOTADDF2Threshold->clear();
    ui->spinBox_SOTADDF2Threshold->setEnabled(false);
    ui->spinBox_SOTADDF2Threshold->setValue(0);
    ui->spinBox_SOTADDF2Threshold->setMaximum(65535);
    ui->spinBox_SOTADDF2Threshold->setMinimum(0);
    ui->spinBox_SOTADDF2Threshold->setEnabled(true);

    ui->comboBox_SOTADDF1TimeImpact->clear();
    ui->comboBox_SOTADDF1TimeImpact->setEnabled(false);
    ui->comboBox_SOTADDF1TimeImpact->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_SOTADDF1TimeImpact->addItem(QString::number((float)(i + 1.0f) * 0.1f, 'f', 1), (float)(i + 1.0f) * 0.1f);
    }
    ui->comboBox_SOTADDF1TimeImpact->setEnabled(true);

    ui->comboBox_SOTADDF2TimeImpact->clear();
    ui->comboBox_SOTADDF2TimeImpact->setEnabled(false);
    ui->comboBox_SOTADDF2TimeImpact->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_SOTADDF2TimeImpact->addItem(QString::number((float)(i + 1.0f) * 0.1f, 'f', 1), (float)(i + 1.0f) * 0.1f);
    }
    ui->comboBox_SOTADDF2TimeImpact->setEnabled(true);


    ui->comboBox_SOTADDF1CountImpact->clear();
    ui->comboBox_SOTADDF1CountImpact->setEnabled(false);
    ui->comboBox_SOTADDF1CountImpact->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_SOTADDF1CountImpact->addItem(QString("%1").arg(i + 1), i + 1);
    }
    ui->comboBox_SOTADDF1CountImpact->setEnabled(true);

    ui->comboBox_SOTADDF2CountImpact->clear();
    ui->comboBox_SOTADDF2CountImpact->setEnabled(false);
    ui->comboBox_SOTADDF2CountImpact->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_SOTADDF2CountImpact->addItem(QString("%1").arg(i + 1), i + 1);
    }
    ui->comboBox_SOTADDF2CountImpact->setEnabled(true);

    ui->spinBox_SOTADDF1DurationOvercoming->clear();
    ui->spinBox_SOTADDF1DurationOvercoming->setEnabled(false);
    ui->spinBox_SOTADDF1DurationOvercoming->setValue(0);
    ui->spinBox_SOTADDF1DurationOvercoming->setMaximum(100);
    ui->spinBox_SOTADDF1DurationOvercoming->setMinimum(0);
    ui->spinBox_SOTADDF1DurationOvercoming->setEnabled(true);

    ui->spinBox_SOTADDF2DurationOvercoming->clear();
    ui->spinBox_SOTADDF2DurationOvercoming->setEnabled(false);
    ui->spinBox_SOTADDF2DurationOvercoming->setValue(0);
    ui->spinBox_SOTADDF2DurationOvercoming->setMaximum(100);
    ui->spinBox_SOTADDF2DurationOvercoming->setMinimum(0);
    ui->spinBox_SOTADDF2DurationOvercoming->setEnabled(true);
}

void MainWindowServer::preparePageT4KDD()
{
    //C1
    ui->comboBox_T4KDDC1F1OnOff->clear();
    ui->comboBox_T4KDDC1F1OnOff->setEnabled(false);
    ui->comboBox_T4KDDC1F1OnOff->setEditable(false);
    ui->comboBox_T4KDDC1F1OnOff->addItem(tr("Выкл"), 0);
    ui->comboBox_T4KDDC1F1OnOff->addItem(tr("Вкл"), 1);
    ui->comboBox_T4KDDC1F1OnOff->setEnabled(true);

    ui->comboBox_T4KDDC1F2OnOff->clear();
    ui->comboBox_T4KDDC1F2OnOff->setEnabled(false);
    ui->comboBox_T4KDDC1F2OnOff->setEditable(false);
    ui->comboBox_T4KDDC1F2OnOff->addItem(tr("Выкл"), 0);
    ui->comboBox_T4KDDC1F2OnOff->addItem(tr("Вкл"), 1);
    ui->comboBox_T4KDDC1F2OnOff->setEnabled(true);

    ui->spinBox_T4KDDC1F1Threshold->clear();
    ui->spinBox_T4KDDC1F1Threshold->setEnabled(false);
    ui->spinBox_T4KDDC1F1Threshold->setValue(0);
    ui->spinBox_T4KDDC1F1Threshold->setMaximum(65535);
    ui->spinBox_T4KDDC1F1Threshold->setMinimum(0);
    ui->spinBox_T4KDDC1F1Threshold->setEnabled(true);

    ui->spinBox_T4KDDC1F2Threshold->clear();
    ui->spinBox_T4KDDC1F2Threshold->setEnabled(false);
    ui->spinBox_T4KDDC1F2Threshold->setValue(0);
    ui->spinBox_T4KDDC1F2Threshold->setMaximum(65535);
    ui->spinBox_T4KDDC1F2Threshold->setMinimum(0);
    ui->spinBox_T4KDDC1F2Threshold->setEnabled(true);

    ui->comboBox_T4KDDC1F1TimeImpact->clear();
    ui->comboBox_T4KDDC1F1TimeImpact->setEnabled(false);
    ui->comboBox_T4KDDC1F1TimeImpact->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_T4KDDC1F1TimeImpact->addItem(QString::number((float)(i + 1.0f) * 0.1f, 'f', 1), (float)(i + 1.0f) * 0.1f);
    }
    ui->comboBox_T4KDDC1F1TimeImpact->setEnabled(true);

    ui->comboBox_T4KDDC1F2TimeImpact->clear();
    ui->comboBox_T4KDDC1F2TimeImpact->setEnabled(false);
    ui->comboBox_T4KDDC1F2TimeImpact->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_T4KDDC1F2TimeImpact->addItem(QString::number((float)(i + 1.0f) * 0.1f, 'f', 1), (float)(i + 1.0f) * 0.1f);
    }
    ui->comboBox_T4KDDC1F2TimeImpact->setEnabled(true);


    ui->comboBox_T4KDDC1F1CountImpact->clear();
    ui->comboBox_T4KDDC1F1CountImpact->setEnabled(false);
    ui->comboBox_T4KDDC1F1CountImpact->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_T4KDDC1F1CountImpact->addItem(QString("%1").arg(i + 1), i + 1);
    }
    ui->comboBox_T4KDDC1F1CountImpact->setEnabled(true);

    ui->comboBox_T4KDDC1F2CountImpact->clear();
    ui->comboBox_T4KDDC1F2CountImpact->setEnabled(false);
    ui->comboBox_T4KDDC1F2CountImpact->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_T4KDDC1F2CountImpact->addItem(QString("%1").arg(i + 1), i + 1);
    }
    ui->comboBox_T4KDDC1F2CountImpact->setEnabled(true);

    ui->spinBox_T4KDDC1F1DurationOvercoming->clear();
    ui->spinBox_T4KDDC1F1DurationOvercoming->setEnabled(false);
    ui->spinBox_T4KDDC1F1DurationOvercoming->setValue(0);
    ui->spinBox_T4KDDC1F1DurationOvercoming->setMaximum(100);
    ui->spinBox_T4KDDC1F1DurationOvercoming->setMinimum(0);
    ui->spinBox_T4KDDC1F1DurationOvercoming->setEnabled(true);

    ui->spinBox_T4KDDC1F2DurationOvercoming->clear();
    ui->spinBox_T4KDDC1F2DurationOvercoming->setEnabled(false);
    ui->spinBox_T4KDDC1F2DurationOvercoming->setValue(0);
    ui->spinBox_T4KDDC1F2DurationOvercoming->setMaximum(100);
    ui->spinBox_T4KDDC1F2DurationOvercoming->setMinimum(0);
    ui->spinBox_T4KDDC1F2DurationOvercoming->setEnabled(true);

    ui->comboBox_T4KDDWeakeningC1->clear();
    ui->comboBox_T4KDDWeakeningC1->setEnabled(false);
    ui->comboBox_T4KDDWeakeningC1->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_T4KDDWeakeningC1->addItem(QString("%1").arg(i + 1), i + 1);
    }
    ui->comboBox_T4KDDWeakeningC1->setEnabled(true);

    //C2
    ui->comboBox_T4KDDC2F1OnOff->clear();
    ui->comboBox_T4KDDC2F1OnOff->setEnabled(false);
    ui->comboBox_T4KDDC2F1OnOff->setEditable(false);
    ui->comboBox_T4KDDC2F1OnOff->addItem(tr("Выкл"), 0);
    ui->comboBox_T4KDDC2F1OnOff->addItem(tr("Вкл"), 1);
    ui->comboBox_T4KDDC2F1OnOff->setEnabled(true);

    ui->comboBox_T4KDDC2F2OnOff->clear();
    ui->comboBox_T4KDDC2F2OnOff->setEnabled(false);
    ui->comboBox_T4KDDC2F2OnOff->setEditable(false);
    ui->comboBox_T4KDDC2F2OnOff->addItem(tr("Выкл"), 0);
    ui->comboBox_T4KDDC2F2OnOff->addItem(tr("Вкл"), 1);
    ui->comboBox_T4KDDC2F2OnOff->setEnabled(true);

    ui->spinBox_T4KDDC2F1Threshold->clear();
    ui->spinBox_T4KDDC2F1Threshold->setEnabled(false);
    ui->spinBox_T4KDDC2F1Threshold->setValue(0);
    ui->spinBox_T4KDDC2F1Threshold->setMaximum(65535);
    ui->spinBox_T4KDDC2F1Threshold->setMinimum(0);
    ui->spinBox_T4KDDC2F1Threshold->setEnabled(true);

    ui->spinBox_T4KDDC2F2Threshold->clear();
    ui->spinBox_T4KDDC2F2Threshold->setEnabled(false);
    ui->spinBox_T4KDDC2F2Threshold->setValue(0);
    ui->spinBox_T4KDDC2F2Threshold->setMaximum(65535);
    ui->spinBox_T4KDDC2F2Threshold->setMinimum(0);
    ui->spinBox_T4KDDC2F2Threshold->setEnabled(true);

    ui->comboBox_T4KDDC2F1TimeImpact->clear();
    ui->comboBox_T4KDDC2F1TimeImpact->setEnabled(false);
    ui->comboBox_T4KDDC2F1TimeImpact->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_T4KDDC2F1TimeImpact->addItem(QString::number((float)(i + 1.0f) * 0.1f, 'f', 1), (float)(i + 1.0f) * 0.1f);
    }
    ui->comboBox_T4KDDC2F1TimeImpact->setEnabled(true);

    ui->comboBox_T4KDDC2F2TimeImpact->clear();
    ui->comboBox_T4KDDC2F2TimeImpact->setEnabled(false);
    ui->comboBox_T4KDDC2F2TimeImpact->setEditable(false);
    for(int i = 0, n = 40; i < n; i++) {
        ui->comboBox_T4KDDC2F2TimeImpact->addItem(QString::number((float)(i + 1.0f) * 0.1f, 'f', 1), (float)(i + 1.0f) * 0.1f);
    }
    ui->comboBox_T4KDDC2F2TimeImpact->setEnabled(true);


    ui->comboBox_T4KDDC2F1CountImpact->clear();
    ui->comboBox_T4KDDC2F1CountImpact->setEnabled(false);
    ui->comboBox_T4KDDC2F1CountImpact->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_T4KDDC2F1CountImpact->addItem(QString("%1").arg(i + 1), i + 1);
    }
    ui->comboBox_T4KDDC2F1CountImpact->setEnabled(true);

    ui->comboBox_T4KDDC2F2CountImpact->clear();
    ui->comboBox_T4KDDC2F2CountImpact->setEnabled(false);
    ui->comboBox_T4KDDC2F2CountImpact->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_T4KDDC2F2CountImpact->addItem(QString("%1").arg(i + 1), i + 1);
    }
    ui->comboBox_T4KDDC2F2CountImpact->setEnabled(true);

    ui->spinBox_T4KDDC2F1DurationOvercoming->clear();
    ui->spinBox_T4KDDC2F1DurationOvercoming->setEnabled(false);
    ui->spinBox_T4KDDC2F1DurationOvercoming->setValue(0);
    ui->spinBox_T4KDDC2F1DurationOvercoming->setMaximum(100);
    ui->spinBox_T4KDDC2F1DurationOvercoming->setMinimum(0);
    ui->spinBox_T4KDDC2F1DurationOvercoming->setEnabled(true);

    ui->spinBox_T4KDDC2F2DurationOvercoming->clear();
    ui->spinBox_T4KDDC2F2DurationOvercoming->setEnabled(false);
    ui->spinBox_T4KDDC2F2DurationOvercoming->setValue(0);
    ui->spinBox_T4KDDC2F2DurationOvercoming->setMaximum(100);
    ui->spinBox_T4KDDC2F2DurationOvercoming->setMinimum(0);
    ui->spinBox_T4KDDC2F2DurationOvercoming->setEnabled(true);

    ui->comboBox_T4KDDWeakeningC2->clear();
    ui->comboBox_T4KDDWeakeningC2->setEnabled(false);
    ui->comboBox_T4KDDWeakeningC2->setEditable(false);
    for(int i = 0, n = 10; i < n; i++) {
        ui->comboBox_T4KDDWeakeningC2->addItem(QString("%1").arg(i + 1), i + 1);
    }
    ui->comboBox_T4KDDWeakeningC2->setEnabled(true);
}

void MainWindowServer::fillPageRLM()
{
    if(selUN.isNull())
        return;
    if(TypeUnitNodeEnum::RLM_C != selUN->getType() && TypeUnitNodeEnum::RLM_KRL != selUN->getType())
        return;
    else if(TypeUnitNodeEnum::RLM_C == selUN->getType()) {
        qDebug() << "MainWindowServer::fillPageRLM(" << selUN->toString() << ") -->";
        qDebug() << "StateWord " << selUN->getStateWord(0x31u).getByteWord().toHex();
        qDebug() << "clockPeriod " << selUN->swpRLMCType0x31().clockPeriod();
        qDebug() << "modeProcessing " << selUN->swpRLMCType0x31().modeProcessing();
        qDebug() << "threshold " << selUN->swpRLMCType0x31().threshold();

        int tmpIndex = 0;
        tmpIndex = ui->comboBox_RLMTactPeriod->findData(selUN->swpRLMCType0x31().clockPeriod());
        ui->comboBox_RLMTactPeriod->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);

        tmpIndex = ui->comboBox_RLMCondition->findData(selUN->swpRLMCType0x31().modeProcessing());
        ui->comboBox_RLMCondition->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);

        tmpIndex = ui->comboBox_RLMEdge->findData(selUN->swpRLMCType0x31().threshold());
        ui->comboBox_RLMEdge->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);
        qDebug() << "MainWindowServer::fillPageRLM(" << selUN->toString() << ") <--";

        return;
    } else if(TypeUnitNodeEnum::RLM_KRL == selUN->getType()) {
        qDebug() << "MainWindowServer::fillPageRLM(" << selUN->toString() << ") -->";
        qDebug() << "StateWord " << selUN->getStateWord(0x31u).getByteWord().toHex();
        qDebug() << "clockPeriod " << selUN->swpRLMType0x31().clockPeriod();
        qDebug() << "modeProcessing " << selUN->swpRLMType0x31().modeProcessing();
        qDebug() << "threshold " << selUN->swpRLMType0x31().threshold();

        int tmpIndex = 0;
        tmpIndex = ui->comboBox_RLMTactPeriod->findData(selUN->swpRLMType0x31().clockPeriod());
        ui->comboBox_RLMTactPeriod->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);

        tmpIndex = ui->comboBox_RLMCondition->findData(selUN->swpRLMType0x31().modeProcessing());
        ui->comboBox_RLMCondition->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);

        tmpIndex = ui->comboBox_RLMEdge->findData(selUN->swpRLMType0x31().threshold());
        ui->comboBox_RLMEdge->setCurrentIndex(-1 == tmpIndex ? 0 : tmpIndex);
        qDebug() << "MainWindowServer::fillPageRLM(" << selUN->toString() << ") <--";

        return;
    }


}

void MainWindowServer::fillPageTG()
{
    if(selUN.isNull())
        return;
    if(TypeUnitNodeEnum::TG != selUN->getType() && TypeUnitNodeEnum::TG_Base != selUN->getType())
        return;

    int ci = selUN->getNum2();
    if(1 > ci || 4 < ci)
        return;


    qDebug() << "MainWindowServer::fillPageTG(" << selUN->toString() << ") -->";
    qDebug() << "StateWord " << selUN->getStateWord(0x34u).getByteWord().toHex();
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

void MainWindowServer::fillPageTGAtPointInput(int ci)
{
    ci++;
    if(selUN.isNull())
        return;
    if(TypeUnitNodeEnum::TG != selUN->getType() && TypeUnitNodeEnum::TG_Base != selUN->getType())
        return;
    if(1 > ci || 4 < ci)
        return;

    QSharedPointer<UnitNode> target;
    const QList<QSharedPointer<UnitNode> > tmpSet = TopologyService::getSortedMetaRealUnitNodes();
    for(const auto&  un : tmpSet) {
        if(TypeUnitNodeEnum::TG == un->getType() &&
           un->getUdpAdress() == selUN->getUdpAdress() &&
           un->getUdpPort() == selUN->getUdpPort() &&
           un->getNum1() == selUN->getNum1() &&
           un->getNum2() == ci) {
//            qDebug() << "PortManager::parcingStatusWord0x32 -- continue(1)";
            target = un;
            break;;
        }
    }

    if(target.isNull())
        return;


    qDebug() << "MainWindowServer::fillPageTG(" << target->toString() << ") -->";
    qDebug() << "StateWord " << target->getStateWord(0x34u).getByteWord().toHex();
    qDebug() << "input " << ci;

    auto swp = target->swpTGType0x34();

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

    qDebug() << "MainWindowServer::fillPageTG(" << target->toString() << ") <--";
}

void MainWindowServer::fillPageSOTADD()
{
    if(selUN.isNull())
        return;
    if(TypeUnitNodeEnum::DD_SOTA != selUN->getType())
        return;

    const auto &swp = selUN->swpSOTABODType0x34();

    auto index = ui->comboBox_SOTADDF1OnOff->findData(swp.dd().f(1).isOn());
    ui->comboBox_SOTADDF1OnOff->setCurrentIndex(index);

    index = ui->comboBox_SOTADDF2OnOff->findData(swp.dd().f(2).isOn());
    ui->comboBox_SOTADDF2OnOff->setCurrentIndex(index);

    ui->spinBox_SOTADDF1Threshold->setValue(swp.dd().f(1).threshold());
    ui->spinBox_SOTADDF2Threshold->setValue(swp.dd().f(2).threshold());

    index = ui->comboBox_SOTADDF1TimeImpact->findData(swp.dd().f(1).timeImpact());
    ui->comboBox_SOTADDF1TimeImpact->setCurrentIndex(index);

    index = ui->comboBox_SOTADDF2TimeImpact->findData(swp.dd().f(2).timeImpact());
    ui->comboBox_SOTADDF2TimeImpact->setCurrentIndex(index);

    index = ui->comboBox_SOTADDF1CountImpact->findData(swp.dd().f(1).countImpact());
    ui->comboBox_SOTADDF1CountImpact->setCurrentIndex(index);

    index = ui->comboBox_SOTADDF2CountImpact->findData(swp.dd().f(2).countImpact());
    ui->comboBox_SOTADDF2CountImpact->setCurrentIndex(index);

    ui->spinBox_SOTADDF1DurationOvercoming->setValue(swp.dd().f(1).durationOvercoming());
    ui->spinBox_SOTADDF2DurationOvercoming->setValue(swp.dd().f(2).durationOvercoming());
}

void MainWindowServer::fillPageT4KDD()
{
    if(selUN.isNull())
        return;
    if(TypeUnitNodeEnum::DD_T4K_M != selUN->getType())
        return;

    const auto &swp = selUN->swpT4KBODType0x34();

    auto index = ui->comboBox_T4KDDC1F1OnOff->findData(swp.dd().c(1).f(1).isOn());
    ui->comboBox_T4KDDC1F1OnOff->setCurrentIndex(index);

    index = ui->comboBox_T4KDDC1F2OnOff->findData(swp.dd().c(1).f(2).isOn());
    ui->comboBox_T4KDDC1F2OnOff->setCurrentIndex(index);

    ui->spinBox_T4KDDC1F1Threshold->setValue(swp.dd().c(1).f(1).threshold());
    ui->spinBox_T4KDDC1F2Threshold->setValue(swp.dd().c(1).f(2).threshold());

    index = ui->comboBox_T4KDDC1F1TimeImpact->findData(swp.dd().c(1).f(1).timeImpact());
    ui->comboBox_T4KDDC1F1TimeImpact->setCurrentIndex(index);

    index = ui->comboBox_T4KDDC1F2TimeImpact->findData(swp.dd().c(1).f(2).timeImpact());
    ui->comboBox_T4KDDC1F2TimeImpact->setCurrentIndex(index);

    index = ui->comboBox_T4KDDC1F1CountImpact->findData(swp.dd().c(1).f(1).countImpact());
    ui->comboBox_T4KDDC1F1CountImpact->setCurrentIndex(index);

    index = ui->comboBox_T4KDDC1F2CountImpact->findData(swp.dd().c(1).f(2).countImpact());
    ui->comboBox_T4KDDC1F2CountImpact->setCurrentIndex(index);

    ui->spinBox_T4KDDC1F1DurationOvercoming->setValue(swp.dd().c(1).f(1).durationOvercoming());
    ui->spinBox_T4KDDC1F2DurationOvercoming->setValue(swp.dd().c(1).f(2).durationOvercoming());

    index = ui->comboBox_T4KDDWeakeningC1->findData(swp.dd().c(1).weakening());
    ui->comboBox_T4KDDWeakeningC1->setCurrentIndex(index);

    index = ui->comboBox_T4KDDC2F1OnOff->findData(swp.dd().c(2).f(1).isOn());
    ui->comboBox_T4KDDC2F1OnOff->setCurrentIndex(index);

    index = ui->comboBox_T4KDDC2F2OnOff->findData(swp.dd().c(2).f(2).isOn());
    ui->comboBox_T4KDDC2F2OnOff->setCurrentIndex(index);

    ui->spinBox_T4KDDC2F1Threshold->setValue(swp.dd().c(2).f(1).threshold());
    ui->spinBox_T4KDDC2F2Threshold->setValue(swp.dd().c(2).f(2).threshold());

    index = ui->comboBox_T4KDDC2F1TimeImpact->findData(swp.dd().c(2).f(1).timeImpact());
    ui->comboBox_T4KDDC2F1TimeImpact->setCurrentIndex(index);

    index = ui->comboBox_T4KDDC2F2TimeImpact->findData(swp.dd().c(2).f(2).timeImpact());
    ui->comboBox_T4KDDC2F2TimeImpact->setCurrentIndex(index);

    index = ui->comboBox_T4KDDC2F1CountImpact->findData(swp.dd().c(2).f(1).countImpact());
    ui->comboBox_T4KDDC2F1CountImpact->setCurrentIndex(index);

    index = ui->comboBox_T4KDDC2F2CountImpact->findData(swp.dd().c(2).f(2).countImpact());
    ui->comboBox_T4KDDC2F2CountImpact->setCurrentIndex(index);

    ui->spinBox_T4KDDC2F1DurationOvercoming->setValue(swp.dd().c(2).f(1).durationOvercoming());
    ui->spinBox_T4KDDC2F2DurationOvercoming->setValue(swp.dd().c(2).f(2).durationOvercoming());

    index = ui->comboBox_T4KDDWeakeningC2->findData(swp.dd().c(2).weakening());
    ui->comboBox_T4KDDWeakeningC2->setCurrentIndex(index);
}

void MainWindowServer::on_actionCustomization_triggered()
{
    ui->actionCustomization->setChecked(ui->actionCustomization->isChecked());

    if(ui->actionCustomization->isChecked()) {
        if(!ServerSettingUtils::checkDialogAuditAdm())
            return;
    }
    preparePageCustomization();

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
    case TypeUnitNodeEnum::RLM_KRL:
    case TypeUnitNodeEnum::RLM_C:
        fillPageRLM(); //CurrentIndex(0);
        break;
    case TypeUnitNodeEnum::TG:
        fillPageTG(); //setCurrentIndex(3);
        break;
    case TypeUnitNodeEnum::DD_SOTA:
        fillPageSOTADD(); //CurrentIndex(1);
        break;
    case TypeUnitNodeEnum::DD_T4K_M:
        fillPageT4KDD(); //CurrentIndex(2);
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

    if(!ServerSettingUtils::checkDialogAuditAdm())
        return;

    switch (selUN->getType()) {
    case TypeUnitNodeEnum::RLM_KRL: {
        auto newStateWord = selUN->getStateWord(0x31u).getByteWord();
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

        newStateWord[0] = static_cast<uint8_t>(0x00);
//        //qDebug() << "prepare newStateWord " << newStateWord.toHex();

        {
            uint8_t cp = clockPeriod;
            cp = Utils::reverseBits(cp);
            cp = cp >> 6;
            clockPeriod = cp;
        }

        newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | (static_cast<uint8_t>(clockPeriod) << 5);
//        //qDebug() << "clockPeriod newStateWord " << newStateWord.toHex();

        if(Utils::treatAsEqual(10.0, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(0);
        } else if(Utils::treatAsEqual(09.0, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(1);
        } else if(Utils::treatAsEqual(08.0, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(2);
        } else if(Utils::treatAsEqual(07.0, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(3);
        } else if(Utils::treatAsEqual(06.0, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(4);
        } else if(Utils::treatAsEqual(05.0, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(5);
        } else if(Utils::treatAsEqual(04.0, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(6);
        } else if(Utils::treatAsEqual(03.0, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(7);
        } else if(Utils::treatAsEqual(02.0, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(8);
        } else if(Utils::treatAsEqual(01.0, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(9);
        } else if(Utils::treatAsEqual(00.6, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(10);
        } else if(Utils::treatAsEqual(00.5, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(11);
        } else if(Utils::treatAsEqual(00.4, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(12);
        } else if(Utils::treatAsEqual(00.3, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(13);
        } else if(Utils::treatAsEqual(00.2, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(14);
        } else if(Utils::treatAsEqual(00.1, threshold)) {
            newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | static_cast<uint8_t>(15);
        }
//        //qDebug() << "threshold newStateWord " << newStateWord.toHex();

        newStateWord[0] = static_cast<uint8_t>(newStateWord[0]) | (static_cast<uint8_t>(modeProcessing) << 4);
//        //qDebug() << "modeProcessing newStateWord " << newStateWord.toHex();

        auto copyUN = UnitNodeFactory::makeShare(*selUN);
        copyUN->setStateWord(0x31u, newStateWord);
        m_portManager->requestModeSensor(copyUN);

//        m_portManager->requestModeSensor(selUN, newStateWord);

        break;
    }
    case TypeUnitNodeEnum::RLM_C: {
        auto newStateWord = selUN->getStateWord(0x31u).getByteWord();
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

        newStateWord[2] = static_cast<uint8_t>(0x00);
        newStateWord[3] = static_cast<uint8_t>(0x00);

        newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | (static_cast<uint8_t>(clockPeriod) << 4);

        if(Utils::treatAsEqual(10.0, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(0);
        } else if(Utils::treatAsEqual(09.0, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(1);
        } else if(Utils::treatAsEqual(08.0, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(2);
        } else if(Utils::treatAsEqual(07.0, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(3);
        } else if(Utils::treatAsEqual(06.0, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(4);
        } else if(Utils::treatAsEqual(05.0, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(5);
        } else if(Utils::treatAsEqual(04.0, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(6);
        } else if(Utils::treatAsEqual(03.0, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(7);
        } else if(Utils::treatAsEqual(02.0, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(8);
        } else if(Utils::treatAsEqual(01.0, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(9);
        } else if(Utils::treatAsEqual(00.6, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(10);
        } else if(Utils::treatAsEqual(00.5, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(11);
        } else if(Utils::treatAsEqual(00.4, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(12);
        } else if(Utils::treatAsEqual(00.3, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(13);
        } else if(Utils::treatAsEqual(00.2, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(14);
        } else if(Utils::treatAsEqual(00.1, threshold)) {
            newStateWord[2] = static_cast<uint8_t>(newStateWord[2]) | static_cast<uint8_t>(15);
        }

        newStateWord[3] = static_cast<uint8_t>(newStateWord[3]) | static_cast<uint8_t>(modeProcessing);

        auto copyUN = UnitNodeFactory::makeShare(*selUN);
        copyUN->setStateWord(0x31u, newStateWord);
        m_portManager->requestModeSensor(copyUN);

//        m_portManager->requestModeSensor(selUN, newStateWord);

        break;
    }
    case TypeUnitNodeEnum::TG: {

        auto ci = static_cast<uint8_t>(ui->comboBox_PointInput->currentText().toInt() - 1);

        if(0 <= ci && 3 >= ci)
            ci = 0x00;

        auto newStateWord = selUN->swpTGType0x34().C(ci + 1).byteWord();

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

        newStateWord[1] = static_cast<uint8_t>(static_cast<uint16_t>(ui->spinBox_PointFlt1Edge->value() & 0x0000FF00) >> 8);
        newStateWord[2] = static_cast<uint8_t>(static_cast<uint16_t>(ui->spinBox_PointFlt1Edge->value() & 0x000000FF));

        newStateWord[3] = static_cast<uint8_t>(static_cast<uint16_t>(ui->spinBox_PointFlt2Edge->value() & 0x0000FF00) >> 8);
        newStateWord[4] = static_cast<uint8_t>(static_cast<uint16_t>(ui->spinBox_PointFlt2Edge->value() & 0x000000FF));

        newStateWord[5] = static_cast<uint8_t>(static_cast<uint16_t>(ui->spinBox_PointFlt3Edge->value() & 0x0000FF00) >> 8);
        newStateWord[6] = static_cast<uint8_t>(static_cast<uint16_t>(ui->spinBox_PointFlt3Edge->value() & 0x000000FF));

        auto copyUN = UnitNodeFactory::makeShare(*selUN);
        auto sw = copyUN->swpTGType0x34().byteWord();
        sw = sw.replace(7 * ci, 7, newStateWord);
        copyUN->setStateWord(0x34u, sw);
        m_portManager->requestModeSensor(copyUN);

//        m_portManager->requestModeSensor(selUN, newStateWord);

        break;
    }
    case TypeUnitNodeEnum::DD_SOTA: {
        auto newStateWord = selUN->getStateWord(0x34u).getByteWord();
        if(newStateWord.isEmpty()) {
//            //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked(ERROR) <--";
            return;
        }

        //swp.dd().f(1).isOn()
        if(1 == ui->comboBox_SOTADDF1OnOff->currentData().toInt()) {
            newStateWord[1] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b11111111);
        } else if(0 == ui->comboBox_SOTADDF1OnOff->currentData().toInt()) {
            newStateWord[1] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b01111111);
        }

        //swp.dd().f(2).isOn()
        if(1 == ui->comboBox_SOTADDF2OnOff->currentData().toInt()) {
            newStateWord[1] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b11111111);
        } else if(0 == ui->comboBox_SOTADDF2OnOff->currentData().toInt()) {
            newStateWord[1] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b01111111);
        }

        //swp.dd().f(1).threshold()
        if(0 <= ui->spinBox_SOTADDF1Threshold->value()) {
            newStateWord[2] = (static_cast<uint16_t>(ui->spinBox_SOTADDF1Threshold->value()) >> 8);
            newStateWord[3] = (static_cast<uint16_t>(ui->spinBox_SOTADDF1Threshold->value()) & 0x00FF);
        }

        //swp.dd().f(2).threshold()
        if(0 <= ui->spinBox_SOTADDF2Threshold->value()) {
            newStateWord[4] = (static_cast<uint16_t>(ui->spinBox_SOTADDF2Threshold->value()) >> 8);
            newStateWord[5] = (static_cast<uint16_t>(ui->spinBox_SOTADDF2Threshold->value()) & 0x00FF);
        }

        //swp.dd().f(1).timeImpact()
        if(0 <= ui->comboBox_SOTADDF1TimeImpact->currentData().toFloat()) {
            newStateWord[6] = (static_cast<uint8_t>(ui->comboBox_SOTADDF1TimeImpact->currentData().toFloat() * 10.0f));
        }

        //swp.dd().f(2).timeImpact()
        if(0 <= ui->comboBox_SOTADDF2TimeImpact->currentData().toFloat()) {
            newStateWord[7] = (static_cast<uint8_t>(ui->comboBox_SOTADDF2TimeImpact->currentData().toFloat() * 10.0f));
        }

        //swp.dd().f(1).countImpact()
        if(0 <= ui->comboBox_SOTADDF1CountImpact->currentData().toInt()) {
            newStateWord[8] = (static_cast<uint8_t>(ui->comboBox_SOTADDF1CountImpact->currentData().toInt()));
        }

        //swp.dd().f(2).countImpact()
        if(0 <= ui->comboBox_SOTADDF2CountImpact->currentData().toInt()) {
            newStateWord[9] = (static_cast<uint8_t>(ui->comboBox_SOTADDF2CountImpact->currentData().toInt()));
        }

        //swp.dd().f(1).durationOvercoming()
        if(0 <= ui->spinBox_SOTADDF1DurationOvercoming->value()) {
            newStateWord[10] = (static_cast<uint8_t>(ui->spinBox_SOTADDF1DurationOvercoming->value()));
        }

        //swp.dd().f(2).durationOvercoming()
        if(0 <= ui->spinBox_SOTADDF2DurationOvercoming->value()) {
            newStateWord[11] = (static_cast<uint8_t>(ui->spinBox_SOTADDF2DurationOvercoming->value()));
        }

        auto copyUN = UnitNodeFactory::makeShare(*selUN);
        copyUN->setStateWord(0x34u, newStateWord);
        m_portManager->requestModeSensor(copyUN);

        break;
    }
    case TypeUnitNodeEnum::DD_T4K_M: {
        auto newStateWord = selUN->getStateWord(0x34u).getByteWord();
        if(newStateWord.isEmpty()) {
//            //qDebug() << "MainWindowServer::on_pushButton_WriteCustomization_clicked(ERROR) <--";
            return;
        }

        //swp.dd().c(1).f(1).isOn()
        if(1 == ui->comboBox_T4KDDC1F1OnOff->currentData().toInt()) {
            newStateWord[1] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b11111111);
        } else if(0 == ui->comboBox_T4KDDC1F1OnOff->currentData().toInt()) {
            newStateWord[1] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b01111111);
        }

        //swp.dd().c(1).f(2).isOn()
        if(1 == ui->comboBox_T4KDDC1F2OnOff->currentData().toInt()) {
            newStateWord[1] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b11111111);
        } else if(0 == ui->comboBox_T4KDDC1F2OnOff->currentData().toInt()) {
            newStateWord[1] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b10111111);
        }

        //swp.dd().c(1).f(1).threshold()
        if(0 <= ui->spinBox_T4KDDC1F1Threshold->value()) {
            newStateWord[2] = (static_cast<uint16_t>(ui->spinBox_T4KDDC1F1Threshold->value()) >> 8);
            newStateWord[3] = (static_cast<uint16_t>(ui->spinBox_T4KDDC1F1Threshold->value()) & 0x00FF);
        }

        //swp.dd().c(1).f(2).threshold()
        if(0 <= ui->spinBox_T4KDDC1F2Threshold->value()) {
            newStateWord[4] = (static_cast<uint16_t>(ui->spinBox_T4KDDC1F2Threshold->value()) >> 8);
            newStateWord[5] = (static_cast<uint16_t>(ui->spinBox_T4KDDC1F2Threshold->value()) & 0x00FF);
        }

        //swp.dd().c(1).f(1).timeImpact()
        if(0 <= ui->comboBox_T4KDDC1F1TimeImpact->currentData().toFloat()) {
            newStateWord[6] = (static_cast<uint8_t>(ui->comboBox_T4KDDC1F1TimeImpact->currentData().toFloat() * 10.0f));
        }

        //swp.dd().c(1).f(2).timeImpact()
        if(0 <= ui->comboBox_T4KDDC1F2TimeImpact->currentData().toFloat()) {
            newStateWord[7] = (static_cast<uint8_t>(ui->comboBox_T4KDDC1F2TimeImpact->currentData().toFloat() * 10.0f));
        }

        //swp.dd().c(1).f(1).countImpact()
        if(0 <= ui->comboBox_T4KDDC1F1CountImpact->currentData().toInt()) {
            newStateWord[8] = (static_cast<uint8_t>(ui->comboBox_T4KDDC1F1CountImpact->currentData().toInt()));
        }

        //swp.dd().c(1).f(2).countImpact()
        if(0 <= ui->comboBox_T4KDDC1F2CountImpact->currentData().toInt()) {
            newStateWord[9] = (static_cast<uint8_t>(ui->comboBox_T4KDDC1F2CountImpact->currentData().toInt()));
        }

        //swp.dd().c(1).f(1).durationOvercoming()
        if(0 <= ui->spinBox_T4KDDC1F1DurationOvercoming->value()) {
            newStateWord[10] = (static_cast<uint8_t>(ui->spinBox_T4KDDC1F1DurationOvercoming->value()));
        }

        //swp.dd().c(1).f(2).durationOvercoming()
        if(0 <= ui->spinBox_T4KDDC1F2DurationOvercoming->value()) {
            newStateWord[11] = (static_cast<uint8_t>(ui->spinBox_T4KDDC1F2DurationOvercoming->value()));
        }

        //swp.dd().c(1).weakening()
        if(0 <= ui->comboBox_T4KDDWeakeningC1->currentData().toFloat()) {
            newStateWord[1] = (static_cast<uint8_t>(newStateWord.at(1)) & static_cast<uint16_t>(0xF0)) | (static_cast<uint8_t>(ui->comboBox_T4KDDWeakeningC1->currentData().toInt()) & static_cast<uint16_t>(0x0F));
        }

        //swp.dd().c(2).f(1).isOn()
        if(1 == ui->comboBox_T4KDDC2F1OnOff->currentData().toInt()) {
            newStateWord[12] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b11111111);
        } else if(0 == ui->comboBox_T4KDDC2F1OnOff->currentData().toInt()) {
            newStateWord[12] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b01111111);
        }

        //swp.dd().c(2).f(2).isOn()
        if(1 == ui->comboBox_T4KDDC2F2OnOff->currentData().toInt()) {
            newStateWord[12] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b11111111);
        } else if(0 == ui->comboBox_T4KDDC2F2OnOff->currentData().toInt()) {
            newStateWord[12] = (static_cast<uint8_t>(newStateWord.at(1)) & 0b10111111);
        }

        //swp.dd().c(2).f(1).threshold()
        if(0 <= ui->spinBox_T4KDDC2F1Threshold->value()) {
            newStateWord[13] = (static_cast<uint16_t>(ui->spinBox_T4KDDC2F1Threshold->value()) >> 8);
            newStateWord[14] = (static_cast<uint16_t>(ui->spinBox_T4KDDC2F1Threshold->value()) & 0x00FF);
        }

        //swp.dd().c(2).f(2).threshold()
        if(0 <= ui->spinBox_T4KDDC2F2Threshold->value()) {
            newStateWord[15] = (static_cast<uint16_t>(ui->spinBox_T4KDDC2F2Threshold->value()) >> 8);
            newStateWord[16] = (static_cast<uint16_t>(ui->spinBox_T4KDDC2F2Threshold->value()) & 0x00FF);
        }

        //swp.dd().c(2).f(1).timeImpact()
        if(0 <= ui->comboBox_T4KDDC2F1TimeImpact->currentData().toFloat()) {
            newStateWord[17] = (static_cast<uint8_t>(ui->comboBox_T4KDDC2F1TimeImpact->currentData().toFloat() * 10.0f));
        }

        //swp.dd().c(2).f(2).timeImpact()
        if(0 <= ui->comboBox_T4KDDC2F2TimeImpact->currentData().toFloat()) {
            newStateWord[18] = (static_cast<uint8_t>(ui->comboBox_T4KDDC2F2TimeImpact->currentData().toFloat() * 10.0f));
        }

        //swp.dd().c(2).f(1).countImpact()
        if(0 <= ui->comboBox_T4KDDC2F1CountImpact->currentData().toInt()) {
            newStateWord[19] = (static_cast<uint8_t>(ui->comboBox_T4KDDC2F1CountImpact->currentData().toInt()));
        }

        //swp.dd().c(2).f(2).countImpact()
        if(0 <= ui->comboBox_T4KDDC2F2CountImpact->currentData().toInt()) {
            newStateWord[20] = (static_cast<uint8_t>(ui->comboBox_T4KDDC2F2CountImpact->currentData().toInt()));
        }

        //swp.dd().c(2).f(1).durationOvercoming()
        if(0 <= ui->spinBox_T4KDDC2F1DurationOvercoming->value()) {
            newStateWord[21] = (static_cast<uint8_t>(ui->spinBox_T4KDDC2F1DurationOvercoming->value()));
        }

        //swp.dd().c(2).f(2).durationOvercoming()
        if(0 <= ui->spinBox_T4KDDC2F2DurationOvercoming->value()) {
            newStateWord[22] = (static_cast<uint8_t>(ui->spinBox_T4KDDC2F2DurationOvercoming->value()));
        }

        //swp.dd().c(2).weakening()
        if(0 <= ui->comboBox_T4KDDWeakeningC2->currentData().toFloat()) {
            newStateWord[12] = (static_cast<uint8_t>(newStateWord.at(12)) & static_cast<uint16_t>(0xF0)) | (static_cast<uint8_t>(ui->comboBox_T4KDDWeakeningC2->currentData().toInt()) & static_cast<uint16_t>(0x0F));
        }


        auto copyUN = UnitNodeFactory::makeShare(*selUN);
        copyUN->setStateWord(0x34u, newStateWord);
        m_portManager->requestModeSensor(copyUN);

        break;
    }
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

void MainWindowServer::on_pushButtonSoundAlarm_clicked()
{
    SoundAdjuster::playAlarm();

    JourEntity msg;
    msg.setObject(tr("Оператор"));
    msg.setType(905);
    msg.setComment(tr("Включен режим Тревога"));
    DataBaseManager::insertJourMsg_wS(msg);
}


void MainWindowServer::on_pushButtonSoundReset_clicked()
{
    SoundAdjuster::stop();
}

void MainWindowServer::enable_updateListRecords()
{
    qDebug()<<" ";
    qDebug()<<"MainWindowServer::enable_updateListRecords()";
    qDebug()<<" ";
    modelJour->enable_updateListRecords();
}

