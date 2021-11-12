#include "unitwidget.h"
#include "ui_unitwidget.h"
#include <QDebug>


UnitWidget::UnitWidget(QWidget *parent, communicationTypeWidget *comm)
{
    ID=0;
    ui->setupUi(this);

    this->comm=comm;
    comm->setEnabled(true);
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
  qDebug()<<"UnitWidget::get_option";
  comm->setVisible(true);
  comm->get_options(unit,getID());

  if(unit){
        get_from(unit);
        setEnabled(false);

  }else{
        get_default();
        setEnabled(true);


  }

}

void UnitWidget::set_option(UnitNode *unit)
{
  qDebug()<<"UnitWidget::set_option";

}


