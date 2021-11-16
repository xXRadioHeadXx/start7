#include "unitwidget.h"
#include "ui_unitwidget.h"
#include <QDebug>


UnitWidget::UnitWidget(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN, QModelIndex* current)
{
    ID=0;

    this->modelTreeUN=modelTreeUN;
    this->current=current;

    if(current->isValid()){
        qDebug()<<"+";
    }else{
        qDebug()<<"-";
    }

    this->comm=comm;
    this->coord=coord;
    coord_mode=coordinateWigget_mode::nothing;
    comm_is_needed=false;

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

    comm->set_options(unit);
    coord->set_options(unit);
    set_to(unit);
}

void UnitWidget::set_to(UnitNode *unit)
{
  qDebug()<<"UnitWidget::set_option";

}

void UnitWidget::setEnabled(bool val)
{
   comm->setEnabled(val);

   setEnabled_option_menu(val);
}


