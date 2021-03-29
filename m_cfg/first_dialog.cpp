#include "first_dialog.h"
#include "ui_first_dialog.h"

First_Dialog::First_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::First_Dialog)
{
    ui->setupUi(this);
}

First_Dialog::~First_Dialog()
{
    delete ui;
}

void First_Dialog::on_pushButton_RIF_clicked()
{
//    emit rif();
//    this->close();
    this->setResult(1);
    this->close();
}

void First_Dialog::on_pushButton_SSOI_clicked()
{
this->setResult(2);
        this->close();
}
