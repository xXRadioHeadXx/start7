#include "ssoiwidget.h"
#include "ui_ssoiwidget.h"

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
