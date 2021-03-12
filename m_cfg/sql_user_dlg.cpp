#include "sql_user_dlg.h"
#include "ui_sql_user_dlg.h"

sql_User_dlg::sql_User_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sql_User_dlg)
{
    ui->setupUi(this);
}

sql_User_dlg::~sql_User_dlg()
{
    delete ui;
}
