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

    QString cmd;
    if(db.driverName()=="QMYSQL"){
         cmd="show databases";
    }
    if(db.driverName()=="QPSQL"){


         cmd="SELECT datname FROM pg_database";
    }
    qDebug()<<"cmd "<<cmd;
      query.prepare(cmd);



    query.exec();

    databases.clear();
    int cnt=0;
    ui->database_tableWidget->setRowCount(0);
    while(query.next())
    {

        QString db_name=query.value(0).toString();
        qDebug()<<db_name;
        if((db_name=="rif_db0")||
           (db_name=="rif_db1")||
           (db_name=="rif_db2")||
           (db_name=="rif_db3"))
        {
                    qDebug()<<".";
            databases.append(query.value(0).toString());
            cnt=this->ui->database_tableWidget->rowCount();
            this->ui->database_tableWidget->insertRow(cnt);
            this->ui->database_tableWidget->setItem(cnt,0, new QTableWidgetItem(query.value(0).toString()));

        }


    }



qDebug()<<"[/find_rif_db]";
}


//

void DBform::on_add_DB_pushButton_clicked()
{
    emit create_db(this->ui->comboBox->currentText());
}

void DBform::on_drop_BD_pushButton_clicked()
{
    emit drop_db(this->ui->database_tableWidget->currentItem()->text());

}

void DBform::on_use_DB_pushButton_clicked()
{
    emit use_db(this->ui->database_tableWidget->currentItem()->text());
}
