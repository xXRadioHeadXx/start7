#include "edit_unit_widget.h"
#include "ui_edit_unit_widget.h"

edit_unit_widget::edit_unit_widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_unit_widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
}

edit_unit_widget::~edit_unit_widget()
{
    delete ui;
}
