#include "mydrawobject.h"
#include <QDebug>
#include <QPainter>






MyDrawObject::MyDrawObject(int id,QString Name,QPixmap pixmap)
{
    this->supreme=0;
this->ID=id;
    this->Name=Name;
    this->image=pixmap.toImage();
}

QRectF MyDrawObject::boundingRect() const
{



return QRectF(0,0,42,42);
}

void MyDrawObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(this->supreme)
    {
painter->setBrush(Qt::yellow);
    painter->drawRect(QRectF(0,0,35,48));
}
    painter->setBrush(Qt::white);
    painter->drawImage(2,2,image);

    painter->drawRect(QRectF(2,32,31,14));
    painter->drawText(4,43,this->Name);
   // painter->drawEllipse(QRectF(0, 0, 10, 10));
}

void MyDrawObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//QGraphicsItem::mousePressEvent(event);
//qDebug()<<" Press";
}

void MyDrawObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

//qDebug()<<" Move";

this->setPos(mapToScene(event->pos()));

}

void MyDrawObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//qDebug()<<" Release";
}
