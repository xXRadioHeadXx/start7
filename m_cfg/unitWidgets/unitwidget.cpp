#include "unitwidget.h"
#include "ui_unitwidget.h"
#include <QDebug>

UnitWidget::UnitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitWidget)
{
    ID=0;
    ui->setupUi(this);

}

UnitWidget::~UnitWidget()
{
    delete ui;
}

int UnitWidget::getID()
{
    return ID;
}

void UnitWidget::get_option(UnitNode *unit)
{

}

void UnitWidget::set_option(UnitNode *unit)
{
  qDebug()<<"UnitWidget::set_option";
  ui->communicationType->set_options(unit);
}


