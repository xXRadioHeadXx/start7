#include "MainWindow.h"
#include "ui_MainWindow.h"

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
        ui->comboBox_2->addItem(mapConnectObject.value(key), key);
    }

    ui->comboBox->setCurrentIndex(0);

    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(false);

    ui->dateEdit->setVisible(false);
    ui->dateEdit_2->setVisible(false);

    ui->comboBox_2->setVisible(false);
    ui->comboBox_3->setVisible(false);
    ui->comboBox_6->setVisible(false);
    ui->comboBox_7->setVisible(false);
    ui->comboBox_8->setVisible(false);

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
    switch(ui->comboBox_2->itemData(index).toInt()){
    case JourEntity::TypeObject::oSD:
    case JourEntity::TypeObject::oSDBLIP: {
        ui->comboBox_3->clear();
        ui->comboBox_3->addItem(mapEvent.value(0), 0);
        ui->comboBox_3->addItem(mapEvent.value(1), 1);
        ui->comboBox_3->addItem("- " + mapEvent.value(2), 2);
        ui->comboBox_3->addItem("- " + mapEvent.value(3), 3);
        ui->comboBox_3->addItem(mapEvent.value(4), 4);
        ui->comboBox_3->addItem("- " + mapEvent.value(5), 5);
        ui->comboBox_3->addItem("- " + mapEvent.value(6), 6);
        ui->comboBox_3->addItem(mapEvent.value(8), 8);
        ui->comboBox_3->addItem("- " + mapEvent.value(9), 9);
        ui->comboBox_3->addItem("- " + mapEvent.value(10), 10);
        ui->comboBox_3->addItem("- " + mapEvent.value(11), 11);

        ui->label_8->setVisible(true);
        ui->label_9->setVisible(true);
        ui->label_10->setVisible(true);

        ui->comboBox_6->setVisible(true);
        ui->comboBox_7->setVisible(true);
        ui->comboBox_8->setVisible(true);

        break;
    }
    case JourEntity::TypeObject::oIU:
    case JourEntity::TypeObject::oIUBLIP: {
        ui->comboBox_3->clear();
        ui->comboBox_3->addItem(mapEvent.value(0), 0);
        ui->comboBox_3->addItem(mapEvent.value(4), 4);
        ui->comboBox_3->addItem("- " + mapEvent.value(5), 5);
        ui->comboBox_3->addItem("- " + mapEvent.value(7), 7);
        ui->comboBox_3->addItem(mapEvent.value(8), 8);

        ui->label_8->setVisible(true);
        ui->label_9->setVisible(true);
        ui->label_10->setVisible(true);

        ui->comboBox_6->setVisible(true);
        ui->comboBox_7->setVisible(true);
        ui->comboBox_8->setVisible(true);

        break;
    }
    default: {
        ui->comboBox_3->clear();
        ui->comboBox_3->addItem(mapEvent.value(0), 0);
        ui->comboBox_3->addItem(mapEvent.value(1), 1);
        ui->comboBox_3->addItem(mapEvent.value(4), 4);
        ui->comboBox_3->addItem(mapEvent.value(8), 8);

        ui->label_8->setVisible(false);
        ui->label_9->setVisible(false);
        ui->label_10->setVisible(false);

        ui->comboBox_6->setVisible(false);
        ui->comboBox_7->setVisible(false);
        ui->comboBox_8->setVisible(false);

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

        ui->dateEdit->setVisible(false);
        ui->dateEdit_2->setVisible(false);

        ui->comboBox_2->setVisible(false);
        ui->comboBox_3->setVisible(false);
        ui->comboBox_6->setVisible(false);
        ui->comboBox_7->setVisible(false);
        ui->comboBox_8->setVisible(false);

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

QString MainWindow::createObjectFilter() {
    QString sqlFlt;

    sqlFlt = "(" + sqlFlt + ")";
    return sqlFlt;
}

QString MainWindow::createObjectFilter() {
    QString sqlFlt;

    switch( ui->comboBox_2->currentIndex() ) {
    case 1: {
        sqlFlt += " (objecttype=3 OR objecttype=33)";  /* СД */
        if(0 != ui->comboBox_6->currentIndex())
            sqlFlt += " AND d1=" + QString::number(ui->comboBox_6->currentIndex());
        if(0 != ui->comboBox_7->currentIndex())
            sqlFlt += " AND d2=" + QString::number(ui->comboBox_7->currentIndex());
        if(0 != ui->comboBox_8->currentIndex())
            sqlFlt += " AND d3=" + QString::number(ui->comboBox_8->currentIndex());
        break;
    }
    case 2: {
        sqlFlt += " (objecttype=4 OR objecttype=43)";  /* ИУ */
        if(0 != ui->comboBox_6->currentIndex())
            sqlFlt += " AND d1=" + QString::number(ui->comboBox_6->currentIndex());
        if(0 != ui->comboBox_7->currentIndex())
            sqlFlt += " AND d2=" + QString::number(ui->comboBox_7->currentIndex());
        if(0 != ui->comboBox_8->currentIndex())
            sqlFlt += " AND d3=" + QString::number(ui->comboBox_8->currentIndex());
        break;
    }
    case 3: {
        sqlFlt += "objecttype=1";
        break;
    }
    case 4: {
        sqlFlt += "objecttype=2";
        break;
    }
    case 5: {
        sqlFlt += "objecttype=8";
        break;
    }
    case 6: {
        sqlFlt += "objecttype=9";
        break;
    }
    case 7: {
        sqlFlt += "objecttype=91";
        break;
    }
    case 8: {
        sqlFlt += "objecttype=21";
        break;
    }
    case 9: {
        sqlFlt += "objecttype=10";
        break;
    }
    case 10: {
        sqlFlt += "objecttype=7";
        break;
    }
    case 11: {
        sqlFlt += "objecttype=11";
        break;
    }
    case 12: {
        sqlFlt += "objecttype=12";
        break;
    }
//            case 13: sqlFlt += " AND objecttype=14"; break;
//            case 14: sqlFlt += " AND objecttype=17"; break;
    case 13: {
        sqlFlt += "objecttype=111";
        break;
    }
    case 14: {
        sqlFlt += "objecttype=26";
        break;
    }
    case 15: {
        sqlFlt += "objecttype=28";
        break;
    }
    case 16: {
        sqlFlt += "objecttype=29";
        break;
    }
    case 17: {
        sqlFlt += "objecttype=31";
        break;
    }
    default:
        break;
    }
    sqlFlt = "(" + sqlFlt + ")";
    return sqlFlt;
}

QString MainWindow::createDateFilter() {
    QString sqlFlt = "(cdate >= to_timestamp(" + ui->dateEdit->date().toString("YYYY-MM-DD 00:00:00.00") + ", 'YYYY-MM-DD HH24:MI:SS.MS') AND cdate <= to_timestamp(" + ui->dateEdit_2->date().toString("YYYY-MM-DD 23:59:59.99") + ", 'YYYY-MM-DD HH24:MI:SS.MS'))";
    return sqlFlt;
}

QString MainWindow::createCompositFilter() {
    QString sqlFlt = "SELECT * FROM jour WHERE event_code=902";

    if(0 != ui->comboBox->currentIndex())
        return sqlFlt;

    sqlFlt += createDateFilter();

    if(!sqlFlt.isEmpty())
        sqlFlt += " AND ";

}
