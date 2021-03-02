#include "rastr_widget.h"
#include "ui_rastr_widget.h"
#include <QFileInfo>
#include <QFile>
#include <QHostInfo>
#include <QDir>
#include <QMessageBox>

RASTR_Widget::RASTR_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RASTR_Widget)
{
    ui->setupUi(this);





   // this->ui->ADA





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

RASTR_Widget::~RASTR_Widget()
{
    delete ui;
}

void RASTR_Widget::default_options()
{
    this->ui->Use->setCurrentIndex(0);
    this->ui->Name->setText("localhost");
    this->ui->KeepAliveInterval->setValue(20);
    this->ui->Port->setValue(1972);
    this->ui->Port2->setValue(1974);
    this->ui->AutoDkPeriod->setCurrentText(AutoDkPeriod_10);
    this->ui->ThermostatUse->setCurrentIndex(0);
    this->ui->dtInfoToJpg->setCurrentIndex(0);


}

int RASTR_Widget::getUse() const
{
    return  l_Use.key(this->ui->Use->currentText());
}

void RASTR_Widget::setUse(int value)
{

        this->ui->Use->setCurrentText(l_Use.value(value));

}

QString RASTR_Widget::getName() const
{
    return this->ui->Name->text();
}

void RASTR_Widget::setName(const QString &value)
{
    this->ui->Name->setText(value);
}

int RASTR_Widget::getPort() const
{
    return this->ui->Port->value();
}

void RASTR_Widget::setPort(int value)
{
    this->ui->Port->setValue(value);
}

int RASTR_Widget::getPort2() const
{
    return this->ui->Port2->value();
}

void RASTR_Widget::setPort2(int value)
{
    this->ui->Port2->setValue(value);
}

int RASTR_Widget::getKeepAliveInterval() const
{
    return  this->ui->KeepAliveInterval->value();
}
void RASTR_Widget::setKeepAliveInterval(int value)
{
   this->ui->KeepAliveInterval->setValue(value);
}

int RASTR_Widget::getThermostatUse() const
{

    return l_ThermostatUse.key(this->ui->ThermostatUse->currentText());
}

void RASTR_Widget::setThermostatUse(int value)
{
    this->ui->ThermostatUse->setCurrentText(l_ThermostatUse.value(value));
}

int RASTR_Widget::getDtInfoToJpg() const
{
   return l_ThermostatUse.key(this->ui->dtInfoToJpg->currentText());
}

void RASTR_Widget::setDtInfoToJpg(int value)
{
    this->ui->dtInfoToJpg->setCurrentText(l_ThermostatUse.value(value));
}

int RASTR_Widget::getAutoDkPeriod() const
{
    return l_AutoDkPeriod.key(this->ui->AutoDkPeriod->currentText());
}

void RASTR_Widget::setAutoDkPeriod(int value)
{
    this->ui->AutoDkPeriod->setCurrentText(l_AutoDkPeriod.value(value));
}


int RASTR_Widget::getSOLID__Port() const
{
return 0;
}

void RASTR_Widget::setSOLID__Port(int value)
{

}



QString RASTR_Widget::getRASTRMSSOI__SerNum() const
{
    return RASTRMSSOI__SerNum;
}

void RASTR_Widget::setRASTRMSSOI__SerNum(const QString &value)
{
    RASTRMSSOI__SerNum = value;
}

int RASTR_Widget::getRASTRMSSOI__Speed() const
{
    return RASTRMSSOI__Speed;
}

void RASTR_Widget::setRASTRMSSOI__Speed(int value)
{
    RASTRMSSOI__Speed = value;
}

int RASTR_Widget::getRASTRMSSOI__Timeout() const
{
    return RASTRMSSOI__Timeout;
}

void RASTR_Widget::setRASTRMSSOI__Timeout(int value)
{

}

void RASTR_Widget::on_Use_activated(const QString &arg1)
{
    if(arg1==Use_1)
    {

     QFileInfo info(rastrmtv_cfg__path());
     if(info.exists())
     {

     }
     else
     {
//         dialog.showMessage("Файл rastrmtv_cfg.ini не найден");
//         dialog.exec();
         QMessageBox::critical(0,"Ошибка","Файл rastrmtv_cfg.ini не найден");
         this->ui->Use->setCurrentIndex(0);


     }
    }
}

void RASTR_Widget::on_pushButton_clicked()
{
        this->ui->Name->setText(QHostInfo::localHostName());
}

QString RASTR_Widget::rastrmtv_cfg__path() const
{
    QString path=QDir::currentPath();
    path.append("/rastrmtv_cfg.ini");
    return path;
}
