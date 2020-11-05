#ifndef MYDRAWOBJECT_H
#define MYDRAWOBJECT_H
#include <QGraphicsItem>

#include <QObject>
#include<QGraphicsSceneMouseEvent>
#include<QCursor>

class MyDrawObject : public QGraphicsItem
{
public:
    int ID;
    QString Name;
   MyDrawObject(QString Name,QPixmap pixmap);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    float x1,y1,x2,y2;
    QImage image;
    bool supreme;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:

};

#endif // MYDRAWOBJECT_H
