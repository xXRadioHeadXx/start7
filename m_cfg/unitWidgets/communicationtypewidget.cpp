#include "communicationtypewidget.h"
#include "ui_communicationtypewidget.h"
#include <QDebug>
#include <my_config.h>


communicationTypeWidget::communicationTypeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::communicationTypeWidget)
{
//    UnitWidget* wgt=dynamic_cast<UnitWidget*>(parent);

//    ID=wgt->getID();









    ui->setupUi(this);
    for(int i=1;i<256;i++)
    ui->Num3->addItem(QString::number(i));




}

communicationTypeWidget::~communicationTypeWidget()
{
    delete ui;
}

void communicationTypeWidget::get_options(UnitNode *unit,int ID)
{
if(this->isVisible()){

if(unit){

        ui->udpUse->setCurrentText((unit->getUdpUse()==1)?" UDP":"RS485");
         this->ui->UDP_RS485_stacked->setCurrentWidget((unit->getUdpUse()==1)?ui->UDP:ui->RS485);
        ui->udpAdress->setCurrentText(unit->getUdpAdress());
        ui->udpPort->setValue(unit->getUdpPort());
        ui->udpTimeout->setValue(unit->getUdpTimeout());

        ui->Num3->setCurrentText(QString::number(unit->getNum3()));

        ui->udpUse->setEnabled(false);
        ui->udpAdress->setEnabled(false);
        ui->udpPort->setEnabled(false);
        ui->Num3->setEnabled(false);




    }else{
        ui->udpUse->setCurrentText(" UDP");
        ui->udpAdress->setCurrentText("");
        ui->udpPort->setValue(4001);

        this->ui->udpTimeout->setMinimum(timeouts.value(ID));
        this->ui->udpTimeout->setValue(timeouts.value(ID));

        ui->Num3->setCurrentIndex(0);

        ui->udpUse->setEnabled(true);
        ui->udpAdress->setEnabled(true);
        ui->udpPort->setEnabled(true);
        ui->Num3->setEnabled(true);

    }
}

}

void communicationTypeWidget::set_options(UnitNode *unit)
{
    if(this->isVisible()){

    unit->setUdpUse((ui->udpUse->currentText()==" UDP")?1:0);
    unit->setUdpAdress(ui->udpAdress->currentText());
    unit->setUdpPort(ui->udpPort->text().toInt());
    unit->setUdpTimeout(ui->udpTimeout->text().toInt());
    unit->setNum3(ui->Num3->currentText().toInt());
    }
}







void communicationTypeWidget::setEnabled(bool val)
{
    ui->udpUse->setEnabled(val);
    ui->udpAdress->setEnabled(val);
    ui->udpPort->setEnabled(val);
    ui->Num3->setEnabled(val);
}

QString communicationTypeWidget::get_udpAdress()
{
    return ui->udpAdress->currentText();
}

void communicationTypeWidget::on_udpUse_currentTextChanged(const QString &arg1)
{
    if(arg1==" UDP")
     this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->UDP);
    else
    {

     this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    }
}
