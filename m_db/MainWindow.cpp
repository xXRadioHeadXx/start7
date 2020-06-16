#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

