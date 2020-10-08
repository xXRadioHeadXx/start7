#ifndef BACKGROUNDIMAGE_H
#define BACKGROUNDIMAGE_H


#include <QGraphicsItem>

#include <QObject>
#include<QGraphicsSceneMouseEvent>
#include<QCursor>

class BackGroundImage : public QGraphicsItem
{
public:

   BackGroundImage();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    float x1,y1,x2,y2;
    QPixmap pixmap;



private:

};

#endif // BACKGROUNDIMAGE_H
