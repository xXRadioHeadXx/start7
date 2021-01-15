#include "backgroundimage.h"
#include<QPainter>

BackGroundImage::BackGroundImage()
{
pixmap=QPixmap(":/icons/map.jpg");
}


QRectF BackGroundImage::boundingRect() const
{
return QRectF(0,0,pixmap.width(),pixmap.height());
}

void BackGroundImage::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->drawPixmap(0,0,pixmap.width(),pixmap.height(),pixmap);


}
