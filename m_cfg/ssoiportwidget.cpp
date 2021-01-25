#include "ssoiportwidget.h"
#include "ui_ssoiportwidget.h"
#include <qDebug>

SSOIPortWidget::SSOIPortWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SSOIPortWidget)
{
    ui->setupUi(this);

    this->ui->SsoiM_PortNum->addItem(" ВЫКЛ"," ВЫКЛ");


     for(int i(1), n(100); i < n; i++)
     {
      //   qDebug()<<"i= "<<i;
         QString str(" COM%1");
         str = str.arg(i);
         this->ui->SsoiM_PortNum->addItem(str,str);
     }

}

SSOIPortWidget::~SSOIPortWidget()
{
    delete ui;
}

void SSOIPortWidget::set_SsoiMOprosVariant_interface(int index)
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

void SSOIPortWidget::set_SsoiM_PortNum(int val)
{
  this->ui->SsoiM_PortNum->setCurrentIndex(val);
    qDebug()<<"-------------------------------------------------------------------val "<<val;
}

int SSOIPortWidget::get_SsoiM_PortNum()
{

}

void SSOIPortWidget::set_SsoiM_Interval(int val)
{

}

int SSOIPortWidget::get_SsoiM_Interval()
{

}

void SSOIPortWidget::set_SsoiM_Interval_(int val)
{

}

int SSOIPortWidget::get_SsoiM_Interval_()
{

}

void SSOIPortWidget::set_SsoiM_MaxErrCnt(int val)
{

}

int SSOIPortWidget::get_SsoiM_MaxErrCnt()
{

}


