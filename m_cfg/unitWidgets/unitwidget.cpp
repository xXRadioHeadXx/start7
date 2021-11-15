#include "unitwidget.h"
#include "ui_unitwidget.h"
#include <QDebug>


UnitWidget::UnitWidget(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord)
{
    ID=0;
    ui->setupUi(this);

    this->comm=comm;
    this->coord=coord;
    coord_mode=coordinateWigget_mode::nothing;

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

  comm->setVisible(comm_is_needed?true:false);
  comm->get_options(unit,getID());

 // coord->setVisible(false);
  coord->set_mode(coord_mode);

  coord->get_options(unit);


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


