#include "rastr_adam_widget.h"
#include "ui_rastr_adam_widget.h"

RASTR_ADAM_Widget::RASTR_ADAM_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RASTR_ADAM_Widget)
{
    ui->setupUi(this);
}

RASTR_ADAM_Widget::~RASTR_ADAM_Widget()
{
    delete ui;
}
