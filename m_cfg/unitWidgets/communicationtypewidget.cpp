#include "communicationtypewidget.h"
#include "ui_communicationtypewidget.h"
#include <unitWidgets/unitwidget.h>

communicationTypeWidget::communicationTypeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::communicationTypeWidget)
{
    UnitWidget* wgt=dynamic_cast<UnitWidget*>(parent);
    ID=wgt->getID();



    ui->setupUi(this);
    for(int i=1;i<256;i++)
    ui->Num3->addItem(QString::number(i));



}

communicationTypeWidget::~communicationTypeWidget()
{
    delete ui;
}

void communicationTypeWidget::get_options(UnitNode *unit)
{
if(unit){
    ui->udpUse->setCurrentText(QString::number(unit->getUdpUse()));
    ui->udpAdress->setCurrentText(unit->getUdpAdress());
    ui->udpPort->setValue(unit->getUdpPort());
    ui->udpTimeout->setValue(unit->getUdpTimeout());
    ui->Num3->setCurrentText(QString::number(unit->getNum3()));
}else{
    ui->udpUse->setCurrentText(" UDP");
    ui->udpAdress->setCurrentText("");
    ui->udpPort->setValue(4001);
    ui->udpTimeout->setValue(unit->getUdpTimeout());



    this->ui->udpTimeout->setMinimum(ID);
    this->ui->udpTimeout->setValue(ID);

    ui->Num3->setCurrentText(0);

}

}

void communicationTypeWidget::set_options(UnitNode *unit)
{
    unit->setUdpUse((ui->udpUse->currentText()==" UDP")?1:0);
    unit->setUdpAdress(ui->udpAdress->currentText());
    unit->setUdpPort(ui->udpPort->text().toInt());
    unit->setUdpTimeout(ui->udpTimeout->text().toInt());
    unit->setNum3(ui->Num3->currentText().toInt());
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
