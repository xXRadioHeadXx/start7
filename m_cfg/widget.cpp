#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    model = new rif_widget_model();
    this->ui->tableView->setModel(model);
    rif_widget_delegate* dlgt = new rif_widget_delegate(this);
    this->ui->tableView->setItemDelegate(dlgt);




}

Widget::~Widget()
{
    delete ui;
}

