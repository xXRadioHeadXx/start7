#ifndef MAP_H
#define MAP_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMap>
#include <QGraphicsItem>
#include <mydrawobject.h>
#include "mydrawobject.h"
#include "myscene.h"
#include <backgroundimage.h>
namespace Ui {
class Map;
}

class Map : public QMainWindow
{
    Q_OBJECT

public:
        explicit Map(QWidget *parent = 0);



    void Add(QString name,QPixmap pixmap,int x,int y);
    void find(int id);
    bool find(QString Name);
    void change_name(int id,QString name);
    void change_x_y(int id,int x,int y);
    void remove(int id);
    void set_supreme(int ID);
    void clear();
            bool set_map(QString path);
    ~Map();

public:
//   void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
//   void mouseMoveEvent(QMouseEvent *event) override;
//   void mouseReleaseEvent(QMouseEvent *event) override;
    myScene *scene;

public slots:
        void select(int ID);
private slots:
        void on_pushButton_clicked();

private:
    Ui::Map *ui;

    int cnt;
    QMap< int,MyDrawObject*> map;


    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;



    BackGroundImage *backimage;

signals:

   void this_is_patch_to_map(QString patch);
};

#endif // MAP_H
