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
     qDebug()<<"[Down]";


  //   unit = static_cast<UnitNode*>(new_ind.internalPointer());

  //   this->get_option(unit);



    case Qt::Key_Up:
     qDebug()<<"[Up]";

   //  unit = static_cast<UnitNode*>(new_ind.internalPointer());


   //  this->get_option(unit);
    emit new_current_index(this->currentIndex());


    break;
    }

}
/**/
