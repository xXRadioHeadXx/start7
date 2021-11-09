#include "unitwidget.h"
#include "ui_unitwidget.h"

UnitWidget::UnitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitWidget)
{
    ui->setupUi(this);
}

UnitWidget::~UnitWidget()
{
    delete ui;
}
