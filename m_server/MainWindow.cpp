#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <ComboBoxDelegate.h>
#include <QCloseEvent>
#include <QMessageBox>
#include <QNetworkDatagram>
#include <QTimer>

#include <Port.h>
#include <SignalSlotCommutator.h>
#include <Utils.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->ruTranslator = new QTranslator(this);
//    this->ruTranslator->load("app_ru");

    ui->actionDataBase->setShortcut(QKeySequence("F3"));
    ui->actionSoundReset->setShortcut(QKeySequence("Esc"));
    ui->actionControl->setShortcut(QKeySequence("Ins"));//Qt::Key_Insert));

    m_dbManager = new DataBaseManager(this);

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

    JourEntity msg;
    msg.setObject(trUtf8("Оператор"));
    msg.setType(900);
    msg.setComment(trUtf8("Программа запущена"));
    DataBaseManager::insertJourMsg_wS(msg);

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
            SLOT(startDKWait(int)));
    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(stopDKWait()),
            this,
            SLOT(stopDKWait()));
    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(endDKWait()),
            this,
            SLOT(stopDKWait()));
    stopDKWait();
    connect(&quasiProgressBeat,
            SIGNAL(timeout()),
            this,
            SLOT(beatDKWait()));
    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(autoOnOffIU(UnitNode *)),
            m_portManager,
            SLOT(requestAutoOnOffIUCommand(UnitNode *)));

    ui->treeView->resizeColumnToContents(0);

    ui->tableView->resizeColumnToContents(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    ui->tableView->resizeColumnToContents(3);
    ui->tableView->resizeColumnToContents(4);
    ui->tableView->resizeColumnToContents(5);
    ui->tableView->resizeColumnToContents(6);

    m_portManager->startStatusRequest();
}

MainWindow::~MainWindow()
{
    JourEntity msg;
    msg.setObject(trUtf8("Оператор"));
    msg.setType(901);
    msg.setComment(trUtf8("Программа остановлена"));
    DataBaseManager::insertJourMsg(msg);

    delete ui;
}

void MainWindow::write()
{
//    for(int i = 0, n = 1; i < n; i++)
//        qDebug() << "tv h(" << i << ")=" << ui->treeView->columnWidth(i);

//    for(int i = 0, n = 7; i < n; i++)
//        qDebug() << "tv h(" << i << ")=" << ui->tableView->columnWidth(i);

//    return;

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

void MainWindow::updComboBoxReason() {
    updComboBox(DataBaseManager::getReasonGroup(), ui->comboBoxReason);
}

void MainWindow::updComboBoxTakenMeasures() {
    updComboBox(DataBaseManager::getMeasuresGroup(), ui->comboBoxTakenMeasures);
}

void MainWindow::updComboBox(QList<QString> lst, QComboBox * cmb) {
    cmb->clear();
    cmb->addItems(lst);
    cmb->setCurrentIndex(-1);
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
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

void MainWindow::on_tableView_clicked(const QModelIndex &index)
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

void MainWindow::on_toolButtonReason_clicked()
{
    if(nullptr == selMsg) {
        return;
    }

    selMsg->setReason(ui->comboBoxReason->currentText());
    DataBaseManager::updateJourMsg_wS(*selMsg);
    updComboBoxReason();
}

void MainWindow::on_toolButtonTakenMeasures_clicked()
{
    if(nullptr == selMsg) {
        return;
    }

    selMsg->setMeasures(ui->comboBoxTakenMeasures->currentText());
    DataBaseManager::updateJourMsg_wS(*selMsg);
    updComboBoxTakenMeasures();
}

QTranslator *MainWindow::getRuTranslator() const
{
    return ruTranslator;
}

void MainWindow::setRussian() /*noexcept*/
{
    emit this->setTranslator(ruTranslator);
    ui->retranslateUi(this);
}

void MainWindow::on_pushButton_clicked()
{
    createDiagnosticTable();

    write();
}

void MainWindow::createDiagnosticTable()
{
    if(nullptr == this->selUN)
        ui->actionDiagnostics->setChecked(false);

    ui->groupBox_4->setVisible(ui->actionDiagnostics->isChecked());

    if(!ui->groupBox_4->isVisible())
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

void MainWindow::on_pushButtonAlarmReset_clicked()
{
    this->m_portManager->requestAlarmReset();
    JourEntity msgOn;
    msgOn.setObject("Оператор");
    msgOn.setType(135);
    msgOn.setComment(trUtf8("Послана ком. Сброс тревог"));
    DataBaseManager::insertJourMsg_wS(msgOn);

}

void MainWindow::treeUNCustomMenuRequested(QPoint pos)
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
        if(TypeUnitNode::SD_BL_IP == selUN->getType())
            menu->addAction(ui->actionControl);
        menu->addSeparator();
        if(TypeUnitNode::SD_BL_IP == sel->getType() && ((Status::Off == sel->getStatus2()) && (Status::Uncnown == sel->getStatus1()))) {
            menu->addAction(ui->actionUNOn);
        } else if(TypeUnitNode::SD_BL_IP == sel->getType() && !((Status::Off == sel->getStatus2()) && (Status::Uncnown == sel->getStatus1()))) {
            menu->addAction(ui->actionUNOff);
        } else if(TypeUnitNode::IU_BL_IP == sel->getType() && Status::On == sel->getStatus1()) {
            menu->addAction(ui->actionUNOff);
        } else if(TypeUnitNode::IU_BL_IP == sel->getType() && Status::Off == sel->getStatus1()) {
            menu->addAction(ui->actionUNOn);
        }
//        menu->addAction(ui->actionOnOff);
//        menu->addAction(ui->actionClose);
        menu->addSeparator();
        if(0 != sel->getDK() && (TypeUnitNode::SD_BL_IP == sel->getType() || TypeUnitNode::IU_BL_IP == sel->getType()))
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
        /* Call the context menu */
//        menu->popup(ui->treeView->viewport()->mapToGlobal(pos));
        menu->exec(ui->treeView->viewport()->mapToGlobal(pos));
    } else {
        this->selUN = nullptr;
        selIndex = QModelIndex();
    }
}

void MainWindow::on_actionDK_triggered()
{
    this->m_portManager->requestDK(this->selUN);
}

void MainWindow::stopDKWait()
{
    quasiProgressBeat.stop();
    ui->progressBarDKWait->setValue(0);
    ui->progressBarDKWait->setVisible(false);
}

void MainWindow::beatDKWait()
{
    ui->progressBarDKWait->setVisible(true);
    ui->progressBarDKWait->setValue((ui->progressBarDKWait->value() + (dkWaitInterval / (100 * 100))) % 101);
    if(100 == ui->progressBarDKWait->value())
        ui->progressBarDKWait->setVisible(false);
}

void MainWindow::startDKWait(int interval)
{
    stopDKWait();
    ui->progressBarDKWait->setVisible(true);
    dkWaitInterval = interval;
    quasiProgressBeat.start(100);
}

void MainWindow::on_actionRifDKOverall_triggered()
{
    this->m_portManager->requestDK();
}

void MainWindow::on_actionExpandUNTree_triggered()
{
    if(nullptr == selUN)
        return;

    QModelIndex index = selIndex;

    if(index.isValid() && 0 != selUN->treeChildCount())
        ui->treeView->expand(index);
}

void MainWindow::on_actionCollapseUNTree_triggered()
{
    if(nullptr == selUN)
        return;

    QModelIndex index = selIndex;

    if(index.isValid() && 0 != selUN->treeChildCount())
        ui->treeView->collapse(index);
}

void MainWindow::on_actionUNOn_triggered()
{
    if(nullptr == selUN)
        return;
    this->m_portManager->requestOnOffCommand(selUN, true);
}

void MainWindow::on_actionUNOff_triggered()
{
    if(nullptr == selUN)
        return;
    this->m_portManager->requestOnOffCommand(selUN, false);
}

void MainWindow::on_actionControl_triggered()
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
    }
}

void MainWindow::closeEvent(QCloseEvent * event)
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

void MainWindow::on_actionTest_triggered()
{
    if(nullptr == selUN)
        return;
    this->m_portManager->requestAutoOnOffIUCommand(selUN);
}

void MainWindow::on_actionDiagnostics_triggered()
{
    createDiagnosticTable();
}

void MainWindow::on_actionIncrease_triggered()
{
    QFont font = modelMSG->getFont();
    font.setPointSize(font.pointSize() + 5);
    modelMSG->setFont(font);
    ui->tableView->update();

    qDebug() << font;

}

void MainWindow::on_actionReduce_triggered()
{
    QFont font = modelMSG->getFont();
    font.setPointSize(font.pointSize() - 5);
    modelMSG->setFont(font);
    ui->tableView->update();

    qDebug() << font;
}
