#include "findunitform.h"
#include "ui_findunitform.h"

findUnitForm::findUnitForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findUnitForm)
{
    ui->setupUi(this);
}

findUnitForm::~findUnitForm()
{
    delete ui;
}
