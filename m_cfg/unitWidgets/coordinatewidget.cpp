#include "coordinatewidget.h"
#include "ui_coordinatewidget.h"

coordinateWidget::coordinateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::coordinateWidget)
{
    ui->setupUi(this);
}

coordinateWidget::~coordinateWidget()
{
    delete ui;
}
