#include "operator_form.h"
#include "ui_operator_form.h"
#include <QDebug>

operator_form::operator_form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::operator_form)
{
    ui->setupUi(this);
}

operator_form::~operator_form()
{
    delete ui;
}


void operator_form::on_buttonBox_clicked(QAbstractButton *button)
{
    if((QPushButton *)button== ui->buttonBox->button(QDialogButtonBox::Ok) ){

        QString FN = this->ui->FN_lineedit->text();
        QString N1 = this->ui->N1_lineedit->text();
        QString N2 = this->ui->N2_lineedit->text();
        QString PW = this->ui->PW_lineedit->text();

        emit res(FN,N1,N2,PW);
         // HERE GOES MY CODE
        }
}
