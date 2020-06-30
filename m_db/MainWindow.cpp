#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <TablePrint.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    ui->tableView->setModel(this->modelMSG);
    connect(this->modelMSG,
            SIGNAL(needScrollToBottom()),
            ui->tableView,
            SLOT(scrollToBottom()));

    connect(&timerUpd, SIGNAL(timeout()), modelMSG, SLOT(updateListRecords()));
    timerUpd.setInterval(1000);
    timerUpd.start();
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

        ui->dateEdit->setVisible(true);
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
    return DataBaseManager::eventFlt((JourEntity::TypeEvent)ui->comboBox_3->currentData().toInt(),
                                     (JourEntity::TypeObject)ui->comboBox_2->currentData().toInt());
}

QString MainWindow::createObjectFilter() {
    return DataBaseManager::objectFlt((JourEntity::TypeObject)ui->comboBox_2->currentData().toInt(),
                                      ui->comboBox_6->currentIndex(),
                                      ui->comboBox_7->currentIndex(),
                                      ui->comboBox_8->currentIndex());
}

QString MainWindow::createDateFilter() {
    return DataBaseManager::dateFlt(ui->dateEdit->date(), ui->dateEdit_2->date());
}

QString MainWindow::createCompositFilter() {
    QString sqlFlt = "SELECT * FROM jour WHERE type=902";

    if(0 != ui->comboBox->currentIndex())
        return sqlFlt;

    sqlFlt = "SELECT * FROM jour WHERE ";

    QString sqlDateFlt = createDateFilter();
    QString sqlObjectFlt = createObjectFilter();
    QString sqlEventFlt = createEventFilter();

    if(!sqlFlt.isEmpty() && !sqlDateFlt.isEmpty())
        sqlFlt += " AND ";
    sqlFlt += sqlDateFlt;

    if(!sqlFlt.isEmpty() && !sqlObjectFlt.isEmpty())
        sqlFlt += " AND ";
    sqlFlt += sqlObjectFlt;

    if(!sqlFlt.isEmpty() && !sqlEventFlt.isEmpty())
        sqlFlt += " AND ";
    sqlFlt += sqlEventFlt;

    return sqlFlt;
}

void MainWindow::on_pushButton_3_clicked()
{
    TablePrint::createHtmlTableFromModel(ui->tableView);
}
