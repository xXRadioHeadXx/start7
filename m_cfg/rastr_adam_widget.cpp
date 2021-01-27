#include "rastr_adam_widget.h"
#include "ui_rastr_adam_widget.h"

RASTR_ADAM_Widget::RASTR_ADAM_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RASTR_ADAM_Widget)
{
    ui->setupUi(this);




    this->ui->ADAM__Port->addItem(" ВЫКЛ"," ВЫКЛ");
    this->ui->RASTR__Port->addItem(" ВЫКЛ"," ВЫКЛ");
    this->ui->SOLID__Port->addItem(" ВЫКЛ"," ВЫКЛ");
   // this->ui->ADA




     for(int i(1), n(100); i < n; i++)
     {
      //   qDebug()<<"i= "<<i;
         QString str(" COM%1");
         str = str.arg(i);
         this->ui->ADAM__Port->addItem(str,str);
         this->ui->RASTR__Port->addItem(str,str);
         this->ui->SOLID__Port->addItem(str,str);
     }
/**/

    l_Use.insert(0,Use_0);
    l_Use.insert(1,Use_1);
    l_Use.insert(2,Use_2);
    foreach (QString str, l_Use)
    {
    this->ui->Use->addItem(str);

    }

    l_AutoDkPeriod.insert(0,AutoDkPeriod_0);
    l_AutoDkPeriod.insert(10,AutoDkPeriod_10);
    foreach (QString str, l_AutoDkPeriod)
    {
    this->ui->AutoDkPeriod->addItem(str);

    }

    l_ThermostatUse.insert(0,ThermostatUse_0);
    l_ThermostatUse.insert(1,ThermostatUse_1);
    foreach (QString str, l_ThermostatUse)
    {
    this->ui->ThermostatUse->addItem(str);
    this->ui->dtInfoToJpg->addItem(str);

    }
    this->default_options();

}

RASTR_ADAM_Widget::~RASTR_ADAM_Widget()
{
    delete ui;
}

void RASTR_ADAM_Widget::default_options()
{
    this->ui->Use->setCurrentIndex(0);
    this->ui->Name->setText("localhost");
    this->ui->KeepAliveInterval->setValue(20);
    this->ui->Port->setValue(1972);
    this->ui->Port2->setValue(1974);
    this->ui->AutoDkPeriod->setCurrentIndex(0);
    this->ui->ThermostatUse->setCurrentIndex(0);
    this->ui->dtInfoToJpg->setCurrentIndex(0);

    this->ui->ADAM__Port->setCurrentIndex(0);
    this->ui->RASTR__Port->setCurrentIndex(0);
    this->ui->SOLID__Port->setCurrentIndex(0);

    this->ui->ADAM__Interval->setValue(100);
}

int RASTR_ADAM_Widget::getUse() const
{
    return  l_Use.key(this->ui->Use->currentText());
}

void RASTR_ADAM_Widget::setUse(int value)
{

        this->ui->Use->setCurrentText(l_Use.value(value));

}

QString RASTR_ADAM_Widget::getName() const
{
    return this->ui->Name->text();
}

void RASTR_ADAM_Widget::setName(const QString &value)
{
    this->ui->Name->setText(value);
}

int RASTR_ADAM_Widget::getPort() const
{
    return this->ui->Port->value();
}

void RASTR_ADAM_Widget::setPort(int value)
{
    this->ui->Port->setValue(value);
}

int RASTR_ADAM_Widget::getPort2() const
{
    return this->ui->Port2->value();
}

void RASTR_ADAM_Widget::setPort2(int value)
{
    this->ui->Port2->setValue(value);
}

int RASTR_ADAM_Widget::getKeepAliveInterval() const
{
    return  this->ui->KeepAliveInterval->value();
}
void RASTR_ADAM_Widget::setKeepAliveInterval(int value)
{
   this->ui->KeepAliveInterval->setValue(value);
}

int RASTR_ADAM_Widget::getThermostatUse() const
{

    return l_ThermostatUse.key(this->ui->ThermostatUse->currentText());
}

void RASTR_ADAM_Widget::setThermostatUse(int value)
{
    this->ui->ThermostatUse->setCurrentText(l_ThermostatUse.value(value));
}

int RASTR_ADAM_Widget::getDtInfoToJpg() const
{
   return l_ThermostatUse.key(this->ui->dtInfoToJpg->currentText());
}

void RASTR_ADAM_Widget::setDtInfoToJpg(int value)
{
    this->ui->dtInfoToJpg->setCurrentText(l_ThermostatUse.value(value));
}

int RASTR_ADAM_Widget::getAutoDkPeriod() const
{
    return l_AutoDkPeriod.key(this->ui->AutoDkPeriod->currentText());
}

void RASTR_ADAM_Widget::setAutoDkPeriod(int value)
{
    this->ui->AutoDkPeriod->setCurrentText(l_AutoDkPeriod.value(value));
}

int RASTR_ADAM_Widget::getRASTR__Port() const
{
  return this->ui->RASTR__Port->currentIndex();
}

void RASTR_ADAM_Widget::setRASTR__Port(int value)
{
  this->ui->RASTR__Port->setCurrentIndex(value);
}

int RASTR_ADAM_Widget::getSOLID__Port() const
{
  return this->ui->SOLID__Port->currentIndex();
}

void RASTR_ADAM_Widget::setSOLID__Port(int value)
{
  this->ui->SOLID__Port->setCurrentIndex(value);
}

int RASTR_ADAM_Widget::getADAM__Port() const
{
  return this->ui->ADAM__Port->currentIndex();
}

void RASTR_ADAM_Widget::setADAM__Port(int value)
{
  this->ui->ADAM__Port->setCurrentIndex(value);
}

int RASTR_ADAM_Widget::getADAM__Interval() const
{
    return this->ui->ADAM__Interval->value();
}

void RASTR_ADAM_Widget::setADAM__Interval(int value)
{
    this->ui->ADAM__Interval->setValue(value);
}

QString RASTR_ADAM_Widget::getRASTRMSSOI__SerNum() const
{
    return RASTRMSSOI__SerNum;
}

void RASTR_ADAM_Widget::setRASTRMSSOI__SerNum(const QString &value)
{
    RASTRMSSOI__SerNum = value;
}

int RASTR_ADAM_Widget::getRASTRMSSOI__Speed() const
{
    return RASTRMSSOI__Speed;
}

void RASTR_ADAM_Widget::setRASTRMSSOI__Speed(int value)
{
    RASTRMSSOI__Speed = value;
}

int RASTR_ADAM_Widget::getRASTRMSSOI__Timeout() const
{
    return RASTRMSSOI__Timeout;
}

void RASTR_ADAM_Widget::setRASTRMSSOI__Timeout(int value)
{

}
