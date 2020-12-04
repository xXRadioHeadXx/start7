#include "dbform.h"
#include "ui_dbform.h"
#include <QSqlQuery>
#include <QDebug>

DBform::DBform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBform)
{
    ui->setupUi(this);
}

DBform::~DBform()
{
    delete ui;
}

//при открытии формы нужно найти в QSqlDatabase db
// и отобразить в таблице все бд с названием rif_bd0 (1,2,3)
void DBform::find_rif_db(QSqlDatabase db)
{
qDebug()<<"[find_rif_db]";
 //   SELECT name FROM system.databases
    QSqlQuery query(db);

 //   query.exec("SELECT name FROM system.databases");
    query.prepare("show databases");
    query.exec();


    while(query.next())
        qDebug()<<query.value(0).toString();
qDebug()<<"[/find_rif_db]";
}

void DBform::on_pushButton_4_clicked()
{
    emit create_db(this->ui->comboBox->currentText());
}
