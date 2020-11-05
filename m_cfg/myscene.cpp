#include "myscene.h"
#include <QDebug>
#include "mydrawobject.h"
#include <QGraphicsView>
#include <QFlag>
#include <QFlags>
#include <QPixmap>

myScene::myScene(QObject *parent)
{


 //   map_item-
 //   this->map_picture=QPixmap(":/icons/map.jpg");



//this->addPixmap(map_picture);

 //   this->setSceneRect(map_picture.rect());

   // set_map(":/icons/map.jpg");

}

/*
bool myScene::set_map(QString patch)
{

    map_picture=patch;

    if(!map_picture.isNull())
    {

   qDebug()<<"count items "<< this->items().count();

  this->addPixmap(map_picture);
  //        this->setBackgroundBrush(QBrush(QImage(patch)));

   this->setSceneRect( map_picture.rect());






return true;

    }


    return false;
}
*/

myScene::~myScene()
{

}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  qDebug()<<"[mousePressEvent]";

  QList<QGraphicsItem *> items=this->items(event->scenePos());
 // qDebug()<<items.count();
  int res=0;
  foreach (QGraphicsItem *item,items)
  {
      MyDrawObject *obj=dynamic_cast< MyDrawObject *>(item);
  if(obj)
  {
       qDebug()<<"[1]";
      res=1;
     //  Foo *foo = dynamic_cast<Foo *>(base);
      MyDrawObject *obj=dynamic_cast< MyDrawObject *>(item);
             qDebug()<<"[2]";
      emit select(obj->Name);
  //    qDebug()<<"[PROFIT]";
    item->setFlag(QGraphicsItem::ItemIsSelectable,true);
           qDebug()<<"[3]";
      item->setSelected(true);
  //     qDebug()<<"item->isSelected   "<<item->isSelected();
      QList<QGraphicsItem *> selecteditems=this->selectedItems();
                 qDebug()<<"[4]";
  //    qDebug()<<"selectedItems   "<<selecteditems.count();
this->update();
  }
  }


    /*
          foreach( int value, list )

          {

            qDebug() << "Item value: " << value;

          }
      */

}

void myScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> items=this->selectedItems();
    qDebug()<<"количество "<<items.count();
    foreach (QGraphicsItem *item,items)
    {
        MyDrawObject *obj=dynamic_cast< MyDrawObject *>(item);
    if(obj)
    {

     //   qDebug()<<"[PROFIT]";

        int x =event->scenePos().x();
        int y =event->scenePos().y();

       qDebug()<<"Координаты: "<<x<<" "<<y<< X<<" "<<this->Y;

        if(!((x>(this->X-item->boundingRect().x()))||(x<0)||(y>(this->Y-item->boundingRect().y()))||(y<0)))
    {
        item->setPos(event->scenePos());
                this->update();
        emit point(obj->Name,x,y);

  //->setPos(mapToScene(event->pos()));
   }
        else
            qDebug()<<"[!!!!!!!!!]";
    }
}
}

void myScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> items=this->selectedItems();
    qDebug()<<items.count();
    foreach (QGraphicsItem *item,items)
    {
        MyDrawObject *obj=dynamic_cast< MyDrawObject *>(item);
    if(obj)
    {
      //  qDebug()<<"[PROFIT]";
        item->setSelected(false);
        int x =event->scenePos().x();
        int y =event->scenePos().y();


        emit point(obj->Name,x,y);
        this->update();
    }
  //->setPos(mapToScene(event->pos()));

    }
 //   qDebug()<<"Release";
}
