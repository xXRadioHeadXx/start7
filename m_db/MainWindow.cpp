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
    case JourEntity::TypeObject::SD:
    case JourEntity::TypeObject::SDBLIP: {
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
    case JourEntity::TypeObject::IU:
    case JourEntity::TypeObject::IUBLIP: {
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
