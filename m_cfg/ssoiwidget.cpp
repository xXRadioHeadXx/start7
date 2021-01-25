#include "ssoiwidget.h"
#include "ui_ssoiwidget.h"

SSOIwidget::SSOIwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SSOIwidget)
{
    ui->setupUi(this);
}

SSOIwidget::~SSOIwidget()
{
    delete ui;
}

void SSOIwidget::default_options()
{

}
