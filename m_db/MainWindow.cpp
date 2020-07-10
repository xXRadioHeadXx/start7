#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <ComboBoxDelegate.h>
#include <TablePrint.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qApp->setFont(qApp->font());

    setBlockSignal(true);

    ui->dateEdit->setDate(QDate::currentDate());
//    ui->dateEdit->setTime(QTime::fromString("00:00.00", "hh:MM.ms"));

    ui->dateEdit_2->setDate(QDate::currentDate());
//    ui->dateEdit->setTime(QTime::fromString("23:59.99", "hh:MM.ms"));


    QMap<int, QString> mapObject = JourEntity::getMapTypeObject();
    for(int key : mapObject.keys()) {
        ui->comboBox_2->addItem(mapObject.value(key), key);
    }

    QMap<int, QString> mapConnectObject = JourEntity::getMapTypeConnectObject();
    for(int key : mapConnectObject.keys()) {
        ui->comboBox_9->addItem(mapConnectObject.value(key), key);
    }

    ui->comboBox->setCurrentIndex(0);

    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);

    ui->dateEdit->setVisible(false);
    ui->dateEdit_2->setVisible(false);

    ui->comboBox_2->setVisible(false);
    ui->comboBox_3->setVisible(false);
    ui->comboBox_6->setVisible(false);
    ui->comboBox_7->setVisible(false);
    ui->comboBox_8->setVisible(false);
    ui->comboBox_9->setVisible(false);

    m_dbManager = new DataBaseManager(this);

    this->modelMSG = new TableModelMSG(this);

    modelMSG->setFont(ui->tableView->font());

    ui->tableView->setModel(this->modelMSG);
    connect(this->modelMSG,
            SIGNAL(needScrollToBottom()),
            ui->tableView,
            SLOT(scrollToBottom()));
    setBlockSignal(false);

    modelMSG->castomUpdateListRecords(createCompositFilter());

    updComboBoxReason();
    updComboBoxTakenMeasures();

    ui->tableView->setItemDelegateForColumn(4, new ComboBoxDelegate("reason", this));
    ui->tableView->setItemDelegateForColumn(5, new ComboBoxDelegate("measures", this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    QMap<int, QString> mapEvent = JourEntity::getMapTypeEvent();
    switch((JourEntity::TypeObject)ui->comboBox_2->itemData(index).toInt()){
    case JourEntity::oSD: {
        ui->comboBox_3->clear();
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
        ui->comboBox_3->addItem("- " + mapEvent.value(JourEntity::eAlarmWorked), JourEntity::eAlarmWorked);
        ui->comboBox_3->addItem("- " + mapEvent.value(JourEntity::eAlarmOpening), JourEntity::eAlarmOpening);
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
        ui->comboBox_3->addItem("- " + mapEvent.value(JourEntity::eFaultNoConnect), JourEntity::eFaultNoConnect);
        ui->comboBox_3->addItem("- " + mapEvent.value(JourEntity::eFaultDK), JourEntity::eFaultDK);
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);
        ui->comboBox_3->addItem("- " + mapEvent.value(JourEntity::eCommandDK), JourEntity::eCommandDK);
        ui->comboBox_3->addItem("- " + mapEvent.value(JourEntity::eCommandUZMonolit), JourEntity::eCommandUZMonolit);
        ui->comboBox_3->addItem("- " + mapEvent.value(JourEntity::eCommandOperator), JourEntity::eCommandOperator);

        ui->label_8->setVisible(true);
        ui->label_9->setVisible(true);
        ui->label_10->setVisible(true);
        ui->label_11->setVisible(true);

        ui->comboBox_6->setVisible(true);
        ui->comboBox_7->setVisible(true);
        ui->comboBox_8->setVisible(true);
        ui->comboBox_9->setVisible(true);

        break;
    }
    case JourEntity::oIU: {
        ui->comboBox_3->clear();
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
        ui->comboBox_3->addItem("- " + mapEvent.value(JourEntity::eFaultNoConnect), JourEntity::eFaultNoConnect);
        ui->comboBox_3->addItem("- " + mapEvent.value(JourEntity::eFaultCommand), JourEntity::eFaultCommand);
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

        ui->label_8->setVisible(true);
        ui->label_9->setVisible(true);
        ui->label_10->setVisible(true);
        ui->label_11->setVisible(false);

        ui->comboBox_6->setVisible(true);
        ui->comboBox_7->setVisible(true);
        ui->comboBox_8->setVisible(true);
        ui->comboBox_9->setVisible(false);

        break;
    }
    default: {
        ui->comboBox_3->clear();
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eAllEvent), JourEntity::eAllEvent);
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eAlarm), JourEntity::eAlarm);
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eFault), JourEntity::eFault);
        ui->comboBox_3->addItem(mapEvent.value(JourEntity::eCommand), JourEntity::eCommand);

        ui->label_8->setVisible(false);
        ui->label_9->setVisible(false);
        ui->label_10->setVisible(false);
        ui->label_11->setVisible(false);

        ui->comboBox_6->setVisible(false);
        ui->comboBox_7->setVisible(false);
        ui->comboBox_8->setVisible(false);
        ui->comboBox_9->setVisible(false);

        break;
    }
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:{

        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_8->setVisible(false);
        ui->label_9->setVisible(false);
        ui->label_10->setVisible(false);
        ui->label_11->setVisible(false);

        ui->dateEdit->setVisible(false);
        ui->dateEdit_2->setVisible(false);

        ui->comboBox_2->setVisible(false);
        ui->comboBox_3->setVisible(false);
        ui->comboBox_6->setVisible(false);
        ui->comboBox_7->setVisible(false);
        ui->comboBox_8->setVisible(false);
        ui->comboBox_9->setVisible(false);

        break;
    }
    case 1:{

        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);

        ui->dateEdit->setDate(QDate::currentDate());
        ui->dateEdit->setVisible(true);
        ui->dateEdit_2->setDate(QDate::currentDate());
        ui->dateEdit_2->setVisible(true);

        ui->comboBox_2->setVisible(true);
        ui->comboBox_3->setVisible(true);

        ui->comboBox_2->setCurrentIndex(0);
        ui->comboBox_3->setCurrentIndex(0);

        break;
    }
    default:
        break;
    }
}

QString MainWindow::createEventFilter() {
    if(!ui->comboBox_3->isVisible())
        return "";
    return DataBaseManager::eventFlt((JourEntity::TypeEvent)ui->comboBox_3->currentData().toInt(),
                                     (JourEntity::TypeObject)ui->comboBox_2->currentData().toInt());
}

QString MainWindow::createObjectFilter() {
    if(!ui->comboBox_2->isVisible())
        return "";
    return DataBaseManager::objectFlt((JourEntity::TypeObject)ui->comboBox_2->currentData().toInt(),
                                      ui->comboBox_6->currentIndex(),
                                      ui->comboBox_7->currentIndex(),
                                      ui->comboBox_8->currentIndex());
}

QString MainWindow::createDateFilter() {
    if(!ui->dateEdit->isVisible() || !ui->dateEdit_2->isVisible())
        return "";
    return DataBaseManager::dateFlt(ui->dateEdit->date(), ui->dateEdit_2->date());
}

QString MainWindow::createCompositFilter() {
    QString sqlFlt = "SELECT * FROM jour ";

    if(0 == ui->comboBox->currentIndex()) {
        sqlFlt += " ORDER BY id ";
        return sqlFlt;
    }

    QString sqlDateFlt = createDateFilter();
    QString sqlObjectFlt = createObjectFilter();
    QString sqlEventFlt = createEventFilter();

    if(!sqlDateFlt.isEmpty() || !sqlObjectFlt.isEmpty() || !sqlEventFlt.isEmpty()) {
        sqlFlt += " WHERE ";

        QString sqlDopFlt;

        if(!sqlDopFlt.isEmpty() && !sqlDateFlt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlDateFlt;

        if(!sqlDopFlt.isEmpty() && !sqlObjectFlt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlObjectFlt;

        if(!sqlDopFlt.isEmpty() && !sqlEventFlt.isEmpty())
            sqlDopFlt += " AND ";
        sqlDopFlt += sqlEventFlt;

        sqlFlt += sqlDopFlt;
    }

    if(!sqlFlt.isEmpty())
        sqlFlt += " ORDER BY id ";

    return sqlFlt;
}

void MainWindow::on_pushButton_3_clicked()
{
    TablePrint::prepareTmpFileHtmlTableFromModel(ui->tableView);
    TablePrint::print();
}

void MainWindow::on_pushButton_2_clicked()
{
    TablePrint::prepareTmpFileHtmlTableFromModel(ui->tableView);
    TablePrint tp;
    tp.printPreview();
}

void MainWindow::updateListRecords()
{
    if(getBlockSignal())
        return;
    qDebug() << createCompositFilter();
    modelMSG->castomUpdateListRecords(createCompositFilter());
}

void MainWindow::on_pushButton_clicked()
{
    this->updateListRecords();
}

bool MainWindow::getBlockSignal() const
{
    return blockSignal;
}

void MainWindow::setBlockSignal(bool value)
{
    blockSignal = value;
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

void MainWindow::on_toolButtonAddReason_clicked()
{
    if(nullptr == selMsg) {
        return;
    }

    selMsg->setReason(ui->comboBoxReason->currentText());
    DataBaseManager::updateJourMsg_wS(*selMsg);
    updComboBoxReason();
}

void MainWindow::on_toolButtonAddTakenMeasures_clicked()
{
    if(nullptr == selMsg) {
        return;
    }

    selMsg->setMeasures(ui->comboBoxTakenMeasures->currentText());
    DataBaseManager::updateJourMsg_wS(*selMsg);
    updComboBoxTakenMeasures();
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

void MainWindow::on_toolButtonRemoveReason_clicked()
{
    if(nullptr == selMsg) {
        return;
    }

    selMsg->setReason("");
    DataBaseManager::updateJourMsg_wS(*selMsg);
    updComboBoxReason();
}

void MainWindow::on_toolButtonRemoveTakenMeasures_clicked()
{
    if(nullptr == selMsg) {
        return;
    }

    selMsg->setMeasures("");
    DataBaseManager::updateJourMsg_wS(*selMsg);
    updComboBoxTakenMeasures();
}

void MainWindow::on_action_triggered()
{
    this->close();
}
