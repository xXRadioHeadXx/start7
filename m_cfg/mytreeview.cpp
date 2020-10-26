#include "mytreeview.h"



MyTreeView::MyTreeView(QWidget *parent)
  : QTreeView(parent)
{
    this->setAcceptDrops(true);

this->setDragDropMode(QAbstractItemView::InternalMove);
this->setSelectionMode(QAbstractItemView::SingleSelection);
this->setDragEnabled(true);
this->setAcceptDrops(true);
this->setDropIndicatorShown(true);


}
