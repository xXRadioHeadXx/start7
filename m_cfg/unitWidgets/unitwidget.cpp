#include "unitwidget.h"
#include "ui_unitwidget.h"

UnitWidget::UnitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitWidget)
{
    ID=0;
    ui->setupUi(this);

}

UnitWidget::~UnitWidget()
{
    delete ui;
}

int UnitWidget::getID()
{
    return ID;
}
