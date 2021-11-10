#include "communicationtypewidget.h"
#include "ui_communicationtypewidget.h"

communicationTypeWidget::communicationTypeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::communicationTypeWidget)
{
    ui->setupUi(this);
}

communicationTypeWidget::~communicationTypeWidget()
{
    delete ui;
}

void communicationTypeWidget::get_options(UnitNode *unit)
{

}

void communicationTypeWidget::set_options(UnitNode *unit)
{
    unit->setUdpUse((ui->udpUse->currentText()=="UDP")?1:0);
    unit->setUdpAdress(ui->udpAdress->currentText());
    unit->setUdpPort(ui->udpPort->text().toInt());
    unit->setUdpTimeout(ui->udpTimeout->text().toInt());
}
