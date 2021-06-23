#include "unitfinder.h"
#include "ui_unitfinder.h"
#include <QDebug>

UnitFinder::UnitFinder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitFinder)
{
    ui->setupUi(this);
    model=new Model_Unit_Params();
    qDebug()<<"rows: "<<model->rowCount();
    qDebug()<<"columns: "<<model->columnCount();

    this->ui->tableView->setModel(model);

}

UnitFinder::~UnitFinder()
{
    delete ui;
}
