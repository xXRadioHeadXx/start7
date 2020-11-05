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
#include <SettingUtils.h>

MainWindowServer::MainWindowServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowServer)
{
    ui->setupUi(this);

    QDate date = QLocale(QLocale::C).toDate(QString(__DATE__).simplified(), QLatin1String("MMM d yyyy"));
    this->setWindowTitle(trUtf8("Сервер") + " - " + date.toString("dd.MM.yyyy"));

//    this->ruTranslator = new QTranslator(this);
//    this->ruTranslator->load("app_ru");

    ui->actionDataBase->setShortcut(QKeySequence("F3"));
    ui->actionSoundReset->setShortcut(QKeySequence("Esc"));
    ui->actionControl->setShortcut(QKeySequence("Ins"));//Qt::Key_Insert));

    m_dbManager = new DataBaseManager(this);
    DataBaseManager::setIdStartLastDuty();

    this->modelMSG = new TableModelMSG(this);
    ui->tableView->setModel(this->modelMSG);
    connect(this->modelMSG,
            SIGNAL(needScrollToBottom()),
            ui->tableView,
            SLOT(scrollToBottom()));

    this->modelTreeUN = new TreeModelUnitNode(this);
    modelMSG->setFont(ui->tableView->font());

    ui->treeView->setModel(this->modelTreeUN);

    this->modelTreeUN->createProxySortTree();

    DataBaseManager::setIdStartLastDuty();

    JourEntity msg;
    msg.setObject(trUtf8("Оператор"));
    msg.setType(900);
    msg.setComment(trUtf8("Программа запущена"));
    DataBaseManager::insertJourMsg(msg);

    modelMSG->updateAllRecords();

    updComboBoxReason();
    updComboBoxTakenMeasures();

    ui->tableView->setItemDelegateForColumn(4, new ComboBoxDelegate("reason", this));
    ui->tableView->setItemDelegateForColumn(5, new ComboBoxDelegate("measures", this));

    m_portManager = new PortManager(this, this->m_dbManager);
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
            SIGNAL(autoOnOffIU(UnitNode *)),
            m_portManager,
            SLOT(requestAutoOnOffIUCommand(UnitNode *)));

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(changeSelectUN(UnitNode *)),
            this,
            SLOT(changeSelectUN(UnitNode *)));

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
}

MainWindowServer::~MainWindowServer()
{
    JourEntity msg;
    msg.setObject(trUtf8("Оператор"));
    msg.setType(901);
    msg.setComment(trUtf8("Программа остановлена"));
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
    Data.append((quint8)0xB5);
    Data.append((quint8)0xFF);
    Data.append((char)0x00);
    Data.append((quint8)0x22);
    Data.append((quint8)0x21);

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


void MainWindowServer::on_treeView_clicked(const QModelIndex &index)
{
    UnitNode * sel = this->modelTreeUN->clickedUN(index);

    if(nullptr == sel) {
        ui->labelSelectedUN->clear();
        return;
    }

    selUN = sel;
    selIndex = index;

    createDiagnosticTable();

    if(TypeUnitNode::GROUP == selUN->getType()) {
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getType()) + ": \"" + sel->getName() + "\"");
    } else if(TypeUnitNode::SD_BL_IP == selUN->getType() || TypeUnitNode::IU_BL_IP == selUN->getType()) {
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getParentUN()->getType()) + " " + "Кан:" + sel->getUdpAdress() + "::" + QVariant(sel->getUdpPort()).toString() + " " + Utils::typeUNToStr(sel->getType()) + ":" + QVariant(sel->getNum2()).toString());
    } else
        ui->labelSelectedUN->setText(Utils::typeUNToStr(sel->getType()) + "\t" + sel->getName());

}

void MainWindowServer::on_tableView_clicked(const QModelIndex &index)
{
    JourEntity * sel = this->modelMSG->clickedMsg(index);

    if(nullptr == sel) {
        ui->comboBoxReason->setCurrentIndex(-1);
        ui->comboBoxTakenMeasures->setCurrentIndex(-1);
        return;
    }

    selMsg = sel;

    if(sel->getReason().isEmpty() ) {
        ui->comboBoxReason->setCurrentIndex(-1);
    } else {
        ui->comboBoxReason->setEditText(sel->getReason());
    }

    if(sel->getMeasures().isEmpty()) {
        ui->comboBoxTakenMeasures->setCurrentIndex(-1);
    } else {
        ui->comboBoxTakenMeasures->setEditText(sel->getMeasures());
    }
}

void MainWindowServer::on_toolButtonReason_clicked()
{
    if(nullptr == selMsg) {
        return;
    }

    selMsg->setReason(ui->comboBoxReason->currentText());
    DataBaseManager::updateJourMsg_wS(*selMsg);
    updComboBoxReason();
}

void MainWindowServer::on_toolButtonTakenMeasures_clicked()
{
    if(nullptr == selMsg) {
        return;
    }

    selMsg->setMeasures(ui->comboBoxTakenMeasures->currentText());
    DataBaseManager::updateJourMsg_wS(*selMsg);
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

void MainWindowServer::on_pushButton_clicked()
{
    createDiagnosticTable();

    write();
}

void MainWindowServer::createDiagnosticTable()
{
    if(nullptr == this->selUN)
        ui->actionDiagnostics->setChecked(false);

    ui->groupBox_4->setVisible(ui->actionDiagnostics->isChecked());

    if(!ui->groupBox_4->isVisible())
        return;

    if(nullptr == this->selUN)
        return;

    if(TypeUnitNode::IU_BL_IP == selUN->getType() ||
            TypeUnitNode::SD_BL_IP == selUN->getType())
        ui->groupBox_4->setVisible(true);
    else
        ui->groupBox_4->setVisible(false);

    if(!ui->groupBox_4->isVisible())
        return;

    ui->tableWidget->clear();
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();

    ui->groupBox_4->setTitle(trUtf8("Диагностика: БЛ-IP"));

    ui->tableWidget->setRowCount(15);
    ui->tableWidget->setColumnCount(3);

    Utils::fillDiagnosticTable(ui->tableWidget, this->selUN);
}

void MainWindowServer::on_pushButtonAlarmReset_clicked()
{
//    this->m_portManager->requestAlarmReset();
    JourEntity msgOn;
    msgOn.setObject(trUtf8("Оператор"));
    msgOn.setType(135);
    msgOn.setComment(trUtf8("Послана ком. Сброс тревог"));
    DataBaseManager::insertJourMsg_wS(msgOn);
    GraphTerminal::sendAbonentEventsAndStates(msgOn);

    DataBaseManager::resetAllFlags_wS();
}

void MainWindowServer::treeUNCustomMenuRequested(QPoint pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
    if (index.isValid()) {
        UnitNode * sel = this->modelTreeUN->clickedUN(index);
        this->selUN = sel;
        selIndex = index;


        /* Create an object context menu */
        QMenu * menu = new QMenu(ui->treeView);
        /* Set the actions to the menu */

//        menu->addAction(ui->actionTest);

        if(sel->treeChildCount()) {
            if(!ui->treeView->isExpanded(selIndex))
                menu->addAction(ui->actionExpandUNTree);
            if(ui->treeView->isExpanded(selIndex))
                menu->addAction(ui->actionCollapseUNTree);
        }
        if(0 == sel->getBazalt() && TypeUnitNode::SD_BL_IP == selUN->getType())
            menu->addAction(ui->actionControl);
        menu->addSeparator();
        if(0 == sel->getBazalt() && TypeUnitNode::SD_BL_IP == sel->getType() && ((Status::Off == sel->getStatus2()) && (Status::Uncnown == sel->getStatus1()))) {
            menu->addAction(ui->actionUNOn);
        } else if(0 == sel->getBazalt() && TypeUnitNode::SD_BL_IP == sel->getType() && !((Status::Off == sel->getStatus2()) && (Status::Uncnown == sel->getStatus1()))) {
            menu->addAction(ui->actionUNOff);
        } else if(TypeUnitNode::IU_BL_IP == sel->getType() && Status::On == sel->getStatus1()) {
            menu->addAction(ui->actionUNOff);
        } else if(TypeUnitNode::IU_BL_IP == sel->getType() && Status::Off == sel->getStatus1()) {
            menu->addAction(ui->actionUNOn);
        }
//        menu->addAction(ui->actionOnOff);
        if(0 != sel->getBazalt() && Status::Alarm == sel->getStatus1()) {
            menu->addAction(ui->actionClose);
        } else if(0 != sel->getBazalt() && Status::Norm == sel->getStatus1()) {
            menu->addAction(ui->actionOpen);
        }
        menu->addSeparator();
        if(0 == sel->getBazalt() && 0 != sel->getDK() && (TypeUnitNode::SD_BL_IP == sel->getType() || TypeUnitNode::IU_BL_IP == sel->getType()))
            menu->addAction(ui->actionDK);
        menu->addSeparator();
//        menu->addAction(ui->actionRemoteControlOn);
        menu->addSeparator();
//        if(TypeUnitNode::IU_BL_IP == sel->getType())
//            menu->addAction(ui->actionAllOff);
        menu->addSeparator();
//        menu->addAction(ui->actionRemoteControlOff);
//        menu->addAction(ui->actionGuardStamp);
//        menu->addAction(ui->actionConnectBlock_pdi);
//        menu->addAction(ui->actionOnOff);
//        QMenu * submenu = new QMenu(trUtf8("Изменить состояние"), menu);
//        submenu->addAction(ui->actionNormUN);
//        submenu->addAction(ui->actionAlarmUN);
//        submenu->addAction(ui->actionNoConnectUN);
//        menu->addMenu(submenu);
        if(!sel->getName().isEmpty() && !(TypeUnitNode::SYSTEM == sel->getType() || TypeUnitNode::GROUP == sel->getType())) {
            menu->addAction(ui->actionUNSqlSelect);
            setUnSqlSelect(QString("SELECT id, cdate, mdate, objectid, object, comment, reason, measures, operator, operatorid, status, direction, type, flag, d1, d2, d3, d4, objecttype FROM public.jour where object = '%1' ORDER BY id;").arg(sel->getName()));
        }

        /* Call the context menu */
//        menu->popup(ui->treeView->viewport()->mapToGlobal(pos));


        menu->exec(ui->treeView->viewport()->mapToGlobal(pos));
    } else {
        this->selUN = nullptr;
        selIndex = QModelIndex();
    }
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
    if(nullptr == selUN)
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
    if(nullptr == selUN)
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
    if(nullptr == selUN)
        return;
    this->m_portManager->requestOnOffCommand(selUN, true);
}

void MainWindowServer::on_actionUNOff_triggered()
{
    if(nullptr == selUN)
        return;
    this->m_portManager->requestOnOffCommand(selUN, false);
}

void MainWindowServer::on_actionControl_triggered()
{
    if(nullptr == selUN)
        return;


    if(TypeUnitNode::SD_BL_IP != selUN->getType())
        return;

    QString strQuestion;
    if(selUN->getControl())
        strQuestion = trUtf8("Убрать контроль?");
    else
        strQuestion = trUtf8("Восстановить контроль?");

    int ret = QMessageBox::question(this, trUtf8("Предупреждение"),
                                   strQuestion,
                                   QMessageBox::Ok | QMessageBox::Cancel,
                                   QMessageBox::Ok);

    if(QMessageBox::Ok == ret) {
        selUN->setControl(!selUN->getControl());

        JourEntity msgOn;
        msgOn.setObject(selUN->getName());
        msgOn.setType((selUN->getControl() ? 137 : 136));
        msgOn.setComment(trUtf8("Контроль ") + (selUN->getControl() ? trUtf8("Вкл") : trUtf8("Выкл")));
        DataBaseManager::insertJourMsg_wS(msgOn);
        GraphTerminal::sendAbonentEventsAndStates(selUN, msgOn);
    }
}

void MainWindowServer::closeEvent(QCloseEvent * event)
{
    int ret = QMessageBox::warning(this, trUtf8("Предупреждение"),
                                   trUtf8("Завершить работу и выйти из программы?"),
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
        ui->labelOperator->setText(trUtf8("Оператор") + ": " + Operator::getApprovedOperator().getOperatorLable());
    }
}

void MainWindowServer::on_actionTest_triggered()
{
    if(nullptr == selUN)
        return;
    this->m_portManager->requestAutoOnOffIUCommand(selUN);
}

void MainWindowServer::on_actionDiagnostics_triggered()
{
    createDiagnosticTable();
}

void MainWindowServer::on_actionIncrease_triggered()
{
    QFont font = modelMSG->getFont();
    int currentIndexFont = 0;

    for(int n = fontSize.size(); currentIndexFont < n; currentIndexFont++)
        if(font.pointSize() == fontSize.at(currentIndexFont).first)
            break;

    if(currentIndexFont + 1 >= fontSize.size())
        return;

    font.setPointSize(fontSize.at(currentIndexFont + 1).first);
    modelMSG->setFont(font);

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

    qDebug() << font;

}

void MainWindowServer::on_actionReduce_triggered()
{
    QFont font = modelMSG->getFont();
    int currentIndexFont = 0;

    for(int n = fontSize.size(); currentIndexFont < n; currentIndexFont++)
        if(font.pointSize() == fontSize.at(currentIndexFont).first)
            break;

    if(0 > currentIndexFont - 1)
        return;

    font.setPointSize(fontSize.at(currentIndexFont - 1).first);
    modelMSG->setFont(font);

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

    qDebug() << font;
}

void MainWindowServer::on_actionNewScheme_triggered()
{
    int ret = QMessageBox::question(this, trUtf8("Предупреждение"),
                                   trUtf8("Начать новую смену?"),
                                   QMessageBox::Ok | QMessageBox::Cancel,
                                   QMessageBox::Ok);

    if(QMessageBox::Ok == ret) {

        if(0 != SettingUtils::getValueSettings("P1", "MYSQL").toInt() || 0 != SettingUtils::getValueSettings("P2", "MYSQL").toInt()) {
            QString sql = " select * from jour where flag != 0 ";
            QList<JourEntity *> tmpLs = DataBaseManager::getQueryMSGRecord(sql);

            if(tmpLs.size()) {
                QMessageBox::warning(this, trUtf8("Ошибка"),
                                     trUtf8("Не заполнены все обязательные поля в базе данных!"));
                return;
            }

        }

        AuthenticationDialog ad;
        if(0 != ad.getInitialResult()) {
            if(QDialog::Accepted != ad.exec()) {
                QMessageBox::warning(this, QObject::trUtf8("Ошибка"),
                                     QObject::trUtf8("Ошибка выбора оператора комплекса!"));
                return;
            }
        }

        JourEntity msg;
        msg.setObject(trUtf8("Оператор"));
        msg.setType(902);
        msg.setComment(trUtf8("Начата новая смена"));
        msg.setFlag(0);

        QString sql = " update public.jour set flag = 0 where flag != 0 ;";
        DataBaseManager::executeQuery(sql);

        DataBaseManager::insertJourMsg_wS(msg);
        GraphTerminal::sendAbonentEventsAndStates(msg);

        DataBaseManager::setIdStartLastDuty();

        modelMSG->updateAllRecords();

        initLabelOperator();
    }
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
    if(nullptr == selUN)
        return;
    this->m_portManager->lockOpenCloseCommand(selUN, val);
}

void MainWindowServer::on_actionDataBase_triggered()
{
    QProcess *process = new QProcess(this);
    QString file = "m_db";
#if (defined (_WIN32) || defined (_WIN64))
    // windows code
    file.append(".exe");
#endif
    process->start(file);
}

void MainWindowServer::on_actionUNSqlSelect_triggered()
{
    QProcess *process = new QProcess(this);
    QString file = "m_db";

#if (defined (_WIN32) || defined (_WIN64))
    // windows code
    file.append(".exe");
#endif

    file.append(" -sql \"" + getUnSqlSelect() + "\"");
    process->start(file);
}

void MainWindowServer::changeSelectUN(UnitNode *un)
{
    QModelIndex index = this->modelTreeUN->findeIndexUN(un);
    ui->treeView->setCurrentIndex(index);
}
