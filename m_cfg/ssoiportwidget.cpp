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
