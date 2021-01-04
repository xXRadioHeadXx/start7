#include "add_sql_user_form.h"
#include "ui_add_sql_user_form.h"

add_SQL_user_form::add_SQL_user_form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_SQL_user_form)
{
    ui->setupUi(this);
}

add_SQL_user_form::~add_SQL_user_form()
{
    delete ui;
}
