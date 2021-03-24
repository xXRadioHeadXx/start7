#include "ssoi_port_widget.h"
#include "ui_ssoi_port_widget.h"
#include <QDebug>

ssoi_port_widget::ssoi_port_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ssoi_port_widget)
{
    ui->setupUi(this);

    this->ui->SsoiM_PortNum->addItem(" ВЫКЛ"," ВЫКЛ");


     for(int i(1), n(100); i < n; i++)
     {
      //   //qDebug()<<"i= "<<i;
         QString str(" COM%1");
         str = str.arg(i);
         this->ui->SsoiM_PortNum->addItem(str,str);
     }

     default_options();



}

ssoi_port_widget::~ssoi_port_widget()
{
    delete ui;
}

void ssoi_port_widget::set_SsoiMOprosVariant_interface(int index)
{
    switch(index)
    {

    case 0:
    this->ui->stackedWidget->setCurrentWidget(this->ui->OprosVariant_1);
    break;

    case 1:
    this->ui->stackedWidget->setCurrentWidget(this->ui->OprosVariant_2);
    break;

    case 2:
    this->ui->stackedWidget->setCurrentWidget(this->ui->OprosVariant_3);
    break;
    }
}

void ssoi_port_widget::set_SsoiM_PortNum(int val)
{
  this->ui->SsoiM_PortNum->setCurrentIndex(val);

}

int ssoi_port_widget::get_SsoiM_PortNum()
{
  return this->ui->SsoiM_PortNum->currentIndex();
}

void ssoi_port_widget::set_SsoiM_Interval(int val)
{
this->ui->SsoiM_Interval->setValue(val);
}

int ssoi_port_widget::get_SsoiM_Interval()
{
return this->ui->SsoiM_Interval->value();
}

void ssoi_port_widget::set_SsoiM_Interval_(int val)
{
this->ui->SsoiM_Interval_->setValue(val);
}

int ssoi_port_widget::get_SsoiM_Interval_m()
{
return this->ui->SsoiM_Interval_->value();
}

void ssoi_port_widget::set_SsoiM_MaxErrCnt(int val)
{
this->ui->SsoiM_MaxErrCnt->setValue(val);
}

int ssoi_port_widget::get_SsoiM_MaxErrCnt()
{
    return this->ui->SsoiM_MaxErrCnt->value();
}

void ssoi_port_widget::default_options()
{
    this->ui->SsoiM_PortNum->setCurrentText(" ВЫКЛ");
    this->ui->SsoiM_Interval->setValue(1500);
    this->ui->SsoiM_Interval_->setValue(100);
    this->ui->SsoiM_MaxErrCnt->setValue(2);
}


