#include "unitfinder.h"
#include "ui_unitfinder.h"
#include <QDebug>
#include <QPushButton>

UnitFinder::UnitFinder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitFinder)
{
    ui->setupUi(this);
    model=new Model_Unit_Params();
    qDebug()<<"rows: "<<model->rowCount();
    qDebug()<<"columns: "<<model->columnCount();


    this->ui->tableView->setModel(model);

    delegate=new unit_finder_delegate();
    this->ui->tableView->setItemDelegate(delegate);

    for(int row = 0; row < model->rowCount(); row++) {


        QModelIndex idx2 = model->index(row,2,QModelIndex());
       this->ui->tableView->openPersistentEditor(idx2);
        //ui->tableView->setIndexWidget(idx2, new QPushButton);
        // set state to match data model value
        //ui->tableView->indexWidget(idx2);
        // this is a QWidget, not a QCheckbox, so setCheckState not available
    }



}

UnitFinder::~UnitFinder()
{
    delete ui;
}

QString UnitFinder::get_value(QString Name)
{
    for(int i = 0; i < model->rowCount(); i++) {
      if(model->data(model->index(i,0,QModelIndex()),Qt::DisplayRole).toString()==Name)
      {
        return model->data(model->index(i,1,QModelIndex()),Qt::DisplayRole).toString();
      }
    }
 return "ERROR";
}

void UnitFinder::on_pushButton_clicked()
{
    QList<QString> result;
    result.clear();
   for(int i = 0; i < model->rowCount(); i++) {
     if(model->data(model->index(i,2,QModelIndex()),Qt::DisplayRole).toBool())
     {
    //     qDebug()<<"активен: "<<model->data(model->index(i,0,QModelIndex()),Qt::DisplayRole).toString();
        qDebug()<<"активен: "<< model->data(model->index(i,0,QModelIndex()),Qt::DisplayRole).toString();
        qDebug()<<"активен: "<< model->data(model->index(i,1,QModelIndex()),Qt::DisplayRole).toString();
     result.append(model->data(model->index(i,0,QModelIndex()),Qt::DisplayRole).toString());

     }
   }
   qDebug()<<"----------------------------";
   foreach(QString value,result)
   {
       qDebug()<<value;
   }

   emit options_to_find(result);


}



void UnitFinder::on_prev_button_clicked()
{
    emit prev();
}

void UnitFinder::on_next_button_clicked()
{
    emit next();
}
