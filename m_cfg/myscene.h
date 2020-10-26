#ifndef MYSCENE_H
#define MYSCENE_H


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>

class myScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit myScene(QObject *parent = 0);
        QPixmap map_picture;
int X;
int Y;

    ~myScene();

private:
    QPointF     previousPoint;      // The coordinates of the previous point

private:
    // Для рисования используем события мыши
   void mousePressEvent(QGraphicsSceneMouseEvent * event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);



signals:
    void select(int ID);
    void point(int ID,int x,int y);
};


#endif // MYSCENE_H
