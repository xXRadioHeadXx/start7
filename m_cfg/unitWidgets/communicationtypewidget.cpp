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
