#include "my_treeview.h"
#include <QKeyEvent>
#include <QAbstractItemModel>
#include <QDebug>

My_treeView::My_treeView(QWidget *parent) : QTreeView(parent)
{

}

void My_treeView::keyPressEvent(QKeyEvent *event)
{
    QTreeView::keyPressEvent(event);
    switch(event->key())
    {
    case Qt::Key_Down:
     //qDebug()<<"[Down]";


  //   unit = static_cast<UnitNode*>(new_ind.internalPointer());

  //   this->get_option(unit);



    case Qt::Key_Up:
     //qDebug()<<"[Up]";

   //  unit = static_cast<UnitNode*>(new_ind.internalPointer());


   //  this->get_option(unit);
    emit new_current_index(this->currentIndex());


    break;
    }

}

void My_treeView::paintEvent(QPaintEvent *event)
{
   this->setColumnWidth(0,200);
    this->setColumnWidth(1,40);
    this->setColumnWidth(2,80);
    this->setColumnWidth(3,80);
 //   qDebug()<<this->width();
    if((this->columnWidth(0)+this->columnWidth(1)+this->columnWidth(2)+this->columnWidth(3))>this->width())
    {
        int wdt=this->width()-this->columnWidth(1)-this->columnWidth(2)-this->columnWidth(3);
        this->setColumnWidth(0,wdt);
    }

    QTreeView::paintEvent(event);
}
/**/
