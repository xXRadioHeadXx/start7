#include "ssoiwidget.h"
#include "ui_ssoiwidget.h"
#include <qDebug>;

SSOIwidget::SSOIwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SSOIwidget)
{
    ui->setupUi(this);



    l_Version.insert(1,Version_1);
    l_Version.insert(2,Version_2);
    foreach (QString str, l_Version)
    {
    this->ui->Version->addItem(str);

    }

    l_SsoiAutoDkUse.insert(1,SsoiAutoDkUse_0);
    l_SsoiAutoDkUse.insert(2,SsoiAutoDkUse_1);
    foreach (QString str, l_SsoiAutoDkUse)
    {
    this->ui->SsoiAutoDkUse->addItem(str);

    }

    l_SsoiMOprosVariant.insert(0,SsoiMOprosVariant_0);
    l_SsoiMOprosVariant.insert(1,SsoiMOprosVariant_1);
    l_SsoiMOprosVariant.insert(2,SsoiMOprosVariant_2);
    foreach (QString str, l_SsoiMOprosVariant)
    {
    this->ui->SsoiMOprosVariant->addItem(str);

    }

}

SSOIwidget::~SSOIwidget()
{
    delete ui;
}

void SSOIwidget::default_options()
{

}

void SSOIwidget::set_Version(int val)
{
    qDebug()<<"Version "<<val;
    QString str=l_Version.value(val);
    qDebug()<<str;
this->ui->Version->setCurrentText(l_Version.value(val));
}

int SSOIwidget::get_Version()
{
return l_Version.key(this->ui->Version->currentText());
}

void SSOIwidget::set_SsoiM_PortNum1(int val)
{
this->ui->SSOI_M_Port_widget_1->set_SsoiM_PortNum(val);
}

int SSOIwidget::get_SsoiM_PortNum1()
{

}

void SSOIwidget::set_SsoiM_Interval1(int val)
{

}

int SSOIwidget::get_SsoiM_Interval1()
{

}

void SSOIwidget::set_SsoiM_Interval_1(int val)
{

}

void SSOIwidget::set_SsoiM_MaxErrCnt1(int val)
{

}

int SSOIwidget::get_SsoiM_MaxErrCnt1()
{

}

void SSOIwidget::set_SsoiM_PortNum2(int val)
{

}

int SSOIwidget::get_SsoiM_PortNum2()
{

}

void SSOIwidget::set_SsoiM_Interval2(int val)
{

}

int SSOIwidget::get_SsoiM_Interval2()
{

}

void SSOIwidget::set_SsoiM_Interval_2(int val)
{

}

void SSOIwidget::set_SsoiM_MaxErrCnt2(int val)
{

}

int SSOIwidget::get_SsoiM_MaxErrCnt2()
{

}

void SSOIwidget::set_SsoiM_PortNum3(int val)
{

}

int SSOIwidget::get_SsoiM_PortNum3()
{

}

void SSOIwidget::set_SsoiM_Interval3(int val)
{

}

int SSOIwidget::get_SsoiM_Interval3()
{

}

void SSOIwidget::set_SsoiM_Interval_3(int val)
{

}

void SSOIwidget::set_SsoiM_MaxErrCnt3(int val)
{

}

int SSOIwidget::get_SsoiM_MaxErrCnt3()
{

}

void SSOIwidget::set_SsoiM_PortNum4(int val)
{

}

int SSOIwidget::get_SsoiM_PortNum4()
{

}

void SSOIwidget::set_SsoiM_Interval4(int val)
{

}

int SSOIwidget::get_SsoiM_Interval4()
{

}

void SSOIwidget::set_SsoiM_Interval_4(int val)
{

}

void SSOIwidget::set_SsoiM_MaxErrCnt4(int val)
{

}

int SSOIwidget::get_SsoiM_MaxErrCnt4()
{

}

void SSOIwidget::on_Version_currentIndexChanged(const QString &arg1)
{
    if(arg1==Version_1)
    {
    this->ui->stackedWidget->setCurrentWidget(this->ui->SSOI);
    this->ui->SsoiMOprosVariant->setVisible(false);
    this->ui->lbl_SsoiMOprosVariant->setVisible(false);


    }
    else
    if(arg1==Version_2)
    {
    this->ui->stackedWidget->setCurrentWidget(this->ui->SSOI_M);
    this->ui->SsoiMOprosVariant->setVisible(true);
    this->ui->lbl_SsoiMOprosVariant->setVisible(true);
    }

}



void SSOIwidget::on_SsoiMOprosVariant_currentIndexChanged(const QString &arg1)
{
    int val = l_SsoiMOprosVariant.key(arg1);
    this->ui->SSOI_M_Port_widget_1->set_SsoiMOprosVariant_interface(val);
    this->ui->SSOI_M_Port_widget_2->set_SsoiMOprosVariant_interface(val);
    this->ui->SSOI_M_Port_widget_3->set_SsoiMOprosVariant_interface(val);
    this->ui->SSOI_M_Port_widget_4->set_SsoiMOprosVariant_interface(val);
}
