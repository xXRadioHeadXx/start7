#include "ssoiwidget.h"
#include "ui_ssoiwidget.h"
#include <QDebug>;

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

    l_SsoiAutoDkUse.insert(0,SsoiAutoDkUse_0);
    l_SsoiAutoDkUse.insert(1,SsoiAutoDkUse_1);
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

    this->default_options();

}

SSOIwidget::~SSOIwidget()
{
    delete ui;
}
/*
Version=2

SsoiM_PortNum1=0
SsoiM_Interval1=1500
SsoiM_Interval_1=100
SsoiM_MaxErrCnt1=2

SsoiM_PortNum2=0
SsoiM_Interval2=1500
SsoiM_Interval_2=100
SsoiM_MaxErrCnt2=2

SsoiM_PortNum3=0
SsoiM_Interval3=1500
SsoiM_Interval_3=100
SsoiM_MaxErrCnt3=2

SsoiM_PortNum4=0
SsoiM_Interval4=1500
SsoiM_Interval_4=100
SsoiM_MaxErrCnt4=2

SsoiAutoDkUse=0
SsoiMOprosVariant=0
SsoiFixNewWarning=0
SsoiM_PortSpeed=4800
 */
void SSOIwidget::default_options()
{


this->set_Version(1);


this->ui->SSOI_Port_widget->default_options();
this->ui->SSOI_M_Port_widget_1->default_options();
this->ui->SSOI_M_Port_widget_2->default_options();
this->ui->SSOI_M_Port_widget_3->default_options();
this->ui->SSOI_M_Port_widget_4->default_options();

this->set_SsoiAutoDkUse(0);
this->set_SsoiMOprosVariant(0);
this->set_SsoiFixNewWarning(0);


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
return this->ui->SSOI_M_Port_widget_1->get_SsoiM_PortNum();
}

void SSOIwidget::set_SsoiM_Interval1(int val)
{
this->ui->SSOI_M_Port_widget_1->set_SsoiM_Interval(val);
}

int SSOIwidget::get_SsoiM_Interval1()
{
return this->ui->SSOI_M_Port_widget_1->get_SsoiM_Interval();
}

void SSOIwidget::set_SsoiM_Interval_1(int val)
{
    this->ui->SSOI_M_Port_widget_1->set_SsoiM_Interval_(val);
}

int SSOIwidget::get_SsoiM_Interval_1()
{
return this->ui->SSOI_M_Port_widget_1->get_SsoiM_Interval_m();
}



void SSOIwidget::set_SsoiM_MaxErrCnt1(int val)
{
this->ui->SSOI_M_Port_widget_1->set_SsoiM_MaxErrCnt(val);
}

int SSOIwidget::get_SsoiM_MaxErrCnt1()
{
return this->ui->SSOI_M_Port_widget_1->get_SsoiM_MaxErrCnt();
}



void SSOIwidget::set_SsoiM_PortNum2(int val)
{
this->ui->SSOI_M_Port_widget_2->set_SsoiM_PortNum(val);
}

int SSOIwidget::get_SsoiM_PortNum2()
{
return this->ui->SSOI_M_Port_widget_2->get_SsoiM_PortNum();
}

void SSOIwidget::set_SsoiM_Interval2(int val)
{
this->ui->SSOI_M_Port_widget_2->set_SsoiM_Interval(val);
}

int SSOIwidget::get_SsoiM_Interval2()
{
return this->ui->SSOI_M_Port_widget_2->get_SsoiM_Interval();
}

void SSOIwidget::set_SsoiM_Interval_2(int val)
{
    this->ui->SSOI_M_Port_widget_2->set_SsoiM_Interval_(val);
}

int SSOIwidget::get_SsoiM_Interval_2()
{
return this->ui->SSOI_M_Port_widget_2->get_SsoiM_Interval_m();
}

void SSOIwidget::set_SsoiM_MaxErrCnt2(int val)
{
this->ui->SSOI_M_Port_widget_2->set_SsoiM_MaxErrCnt(val);
}

int SSOIwidget::get_SsoiM_MaxErrCnt2()
{
return this->ui->SSOI_M_Port_widget_2->get_SsoiM_MaxErrCnt();
}

void SSOIwidget::set_SsoiM_PortNum3(int val)
{
this->ui->SSOI_M_Port_widget_3->set_SsoiM_PortNum(val);
}

int SSOIwidget::get_SsoiM_PortNum3()
{
return this->ui->SSOI_M_Port_widget_3->get_SsoiM_PortNum();
}

void SSOIwidget::set_SsoiM_Interval3(int val)
{
this->ui->SSOI_M_Port_widget_3->set_SsoiM_Interval(val);
}

int SSOIwidget::get_SsoiM_Interval3()
{
return this->ui->SSOI_M_Port_widget_3->get_SsoiM_Interval();
}

void SSOIwidget::set_SsoiM_Interval_3(int val)
{
    this->ui->SSOI_M_Port_widget_3->set_SsoiM_Interval_(val);
}

int SSOIwidget::get_SsoiM_Interval_3()
{
return this->ui->SSOI_M_Port_widget_3->get_SsoiM_Interval_m();
}

void SSOIwidget::set_SsoiM_MaxErrCnt3(int val)
{
this->ui->SSOI_M_Port_widget_3->set_SsoiM_MaxErrCnt(val);
}

int SSOIwidget::get_SsoiM_MaxErrCnt3()
{
return this->ui->SSOI_M_Port_widget_3->get_SsoiM_MaxErrCnt();
}


void SSOIwidget::set_SsoiM_PortNum4(int val)
{
this->ui->SSOI_M_Port_widget_4->set_SsoiM_PortNum(val);
}

int SSOIwidget::get_SsoiM_PortNum4()
{
return this->ui->SSOI_M_Port_widget_4->get_SsoiM_PortNum();
}

void SSOIwidget::set_SsoiM_Interval4(int val)
{
this->ui->SSOI_M_Port_widget_4->set_SsoiM_Interval(val);
}

int SSOIwidget::get_SsoiM_Interval4()
{
return this->ui->SSOI_M_Port_widget_4->get_SsoiM_Interval();
}

void SSOIwidget::set_SsoiM_Interval_4(int val)
{
    this->ui->SSOI_M_Port_widget_4->set_SsoiM_Interval_(val);
}

int SSOIwidget::get_SsoiM_Interval_4()
{
return this->ui->SSOI_M_Port_widget_4->get_SsoiM_Interval_m();
}

void SSOIwidget::set_SsoiM_MaxErrCnt4(int val)
{
this->ui->SSOI_M_Port_widget_4->set_SsoiM_MaxErrCnt(val);
}

int SSOIwidget::get_SsoiM_MaxErrCnt4()
{
    return this->ui->SSOI_M_Port_widget_4->get_SsoiM_MaxErrCnt();
}

void SSOIwidget::set_SsoiAutoDkUse(int val)
{
 this->ui->SsoiAutoDkUse->setCurrentText(l_SsoiAutoDkUse.value(val));
}

int SSOIwidget::get_SsoiAutoDkUse()
{
 return l_SsoiAutoDkUse.key( this->ui->SsoiAutoDkUse->currentText());
}

void SSOIwidget::set_SsoiMOprosVariant(int val)
{
    switch(val)
    {
        case 0:
        case 1:
        case 2:
        this->ui->SsoiMOprosVariant->setCurrentText(l_SsoiMOprosVariant.value(val));
        break;

        default:
        dialog.showMessage("SsoiMOprosVariant неприемлемое значение либо отсутствует");
        dialog.exec();
        break;



    }

}

int SSOIwidget::get_SsoiMOprosVariant()
{
   return  l_SsoiMOprosVariant.key(this->ui->SsoiMOprosVariant->currentText());
}

void SSOIwidget::set_SsoiFixNewWarning(int val)
{
    switch(val)
    {
    case 0:
    this->ui->SsoiFixNewWarning_val_0->setChecked(true);
    break;

    case 1:
    this->ui->SsoiFixNewWarning_val_1->setChecked(true);
    break;

    default:
        dialog.showMessage("SsoiFixNewWarning неприемлемое значение либо отсутствует");
        dialog.exec();
    break;
    }
}

int SSOIwidget::get_SsoiFixNewWarning()
{
 if(this->ui->SsoiFixNewWarning_val_0->isChecked())
     return 0;
 if(this->ui->SsoiFixNewWarning_val_1->isChecked())
     return 1;

 return -1;


}

void SSOIwidget::on_Version_currentIndexChanged(const QString &arg1)
{
    if(arg1==Version_1)
    {
    this->ui->stackedWidget->setCurrentWidget(this->ui->SSOI);
        this->ui->SSOI_Port_widget->set_SsoiMOprosVariant_interface(1);
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

void SSOIwidget::set_SsoiM_PortSpeed(int value)
{
    SsoiM_PortSpeed = value;
}

int SSOIwidget::get_SsoiM_PortSpeed() const
{
    return SsoiM_PortSpeed;
}
