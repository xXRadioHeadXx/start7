#include "AuthenticationDialog.h"
#include "ui_AuthenticationDialog.h"

AuthenticationDialog::AuthenticationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthenticationDialog)
{
    ui->setupUi(this);
}

AuthenticationDialog::~AuthenticationDialog()
{
    delete ui;
}
