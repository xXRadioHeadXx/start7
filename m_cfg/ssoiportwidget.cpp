#include "ssoiportwidget.h"
#include "ui_ssoiportwidget.h"

SSOIPortWidget::SSOIPortWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SSOIPortWidget)
{
    ui->setupUi(this);

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
