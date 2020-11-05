#include "map.h"
#include "ui_map.h"
#include <QDebug>
#include <QDrag>
#include <QFileDialog>



Map::Map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);

    cnt=0;

backimage=new BackGroundImage();

    scene = new myScene(this);
    ui->graphicsView->setScene(scene);
 backimage->setPos(0,0);
    scene->addItem(backimage);


set_map(":/icons/map.jpg");



    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);








   // rectangle = scene->addRect(100, 0, 80, 100, outlinePen, blueBrush);

    // addEllipse(x,y,w,h,pen,brush)
    //ellipse = scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);

  //  text = scene->addText("bogotobogo.com", QFont("Arial", 20) );
    // movable text
   // text->setFlag(QGraphicsItem::ItemIsMovable);
connect(this->scene,SIGNAL(select(int)),this,SLOT(select(int)));

}

void Map::Add(QString name,QPixmap pixmap,int x,int y)
{

    MyDrawObject *object=new MyDrawObject(name,pixmap);



    scene->addItem(object);
    object->setPos(x,y);



    foreach (QGraphicsItem* object, scene->items())

    {
    if(object->Type==MyDrawObject::Type)
    {
   //     qDebug()<<"object->Type==MyDrawObject.Type";

    }



    //  qDebug() << key << ":" ;

    }








}

void Map::find(int id)
{
    foreach (int key, map.keys())

    {

    if(id==key)
    {
        qDebug() <<"Найден  "<< key ;
    set_supreme(id);
    }
    }

}

bool Map::find(QString Name)
{
    foreach (QGraphicsItem* item, scene->items())
    {
        MyDrawObject *obj=dynamic_cast< MyDrawObject *>(item);
    if(obj)

        {
           if(obj->Name==Name)
               return true;
        }
    }
    return false;
}

void Map::change_name(int id,QString name)
{
    qDebug()<<"[1]";
    foreach (QGraphicsItem* item, scene->items())
    {
        MyDrawObject *obj=dynamic_cast< MyDrawObject *>(item);
    if(obj)
    {

          //MyDrawObject *obj=qgraphicsitem_cast<MyDrawObject*>(object);

             qDebug()<<"[2]"<<" ID "<<obj->ID;
     //   qDebug()<<"object->Type==MyDrawObject.Type";
         if(obj->ID==id)
            {
                 qDebug()<<"[3]"<<" ID "<<id;
            obj->Name=name;
    qDebug()<<"[3][1]";
            }
    }
    }
        qDebug()<<"[4]";
}

void Map::change_x_y(int id, int x, int y)
{
    foreach (QGraphicsItem* object, scene->items())
    if(object->Type==MyDrawObject::Type)
    {
   //     qDebug()<<"object->Type==MyDrawObject.Type";
         if(qgraphicsitem_cast<MyDrawObject*>(object)->ID==id)
            {
          object->setPos(x,y);
          scene->update();

            }
    }
}

void Map::remove(int id)
{
    foreach (QGraphicsItem* object, scene->items())

    {
    if(object->Type==MyDrawObject::Type)
    {
   //     qDebug()<<"object->Type==MyDrawObject.Type";
         if(qgraphicsitem_cast<MyDrawObject*>(object)->ID==id)
            {
            qDebug()<<"Удаляю";
                      scene->removeItem(object);
    scene->update();
            }
    }



    //  qDebug() << key << ":" ;

    }


}

void Map::set_supreme(int ID)
{
    foreach (QGraphicsItem* item, scene->items())

    {
        MyDrawObject *obj=dynamic_cast< MyDrawObject *>(item);
    if(obj)

             {
                if(obj->ID==ID)
                {
                    qDebug()<<"[SUPREME]";
                  obj->supreme=true;
                }
                else
                {
                obj->supreme=false;
                }


            }
    }
    scene->update();


}

void Map::clear()
{
    qDebug()<<"[clear]";
    foreach (QGraphicsItem* item, scene->items())

    {
        MyDrawObject *obj=dynamic_cast< MyDrawObject *>(item);
    if(obj)
   //     qDebug()<<"object->Type==MyDrawObject.Type";
             {
            qDebug()<<"Удаляю";
                      scene->removeItem(obj);

            }
    }
    qDebug()<<scene->items().count();

  //  if(!backimage->pixmap.isNull())
 //   scene->addItem(this->backimage);
 //   if(!scene->map_picture.isNull())
 //    scene->addPixmap(scene->map_picture);


   qDebug()<<"[clear PROFIT]";
}

bool Map::set_map(QString patch)
{
qDebug()<<"set_map(QString patch)]"<<patch;
        if(!QPixmap(patch).isNull())
        {
            qDebug()<<"[set_map PROFIT]";
            backimage->pixmap=QPixmap(patch);


qDebug()<<"------------------------------QRECT "<<backimage->pixmap.rect().x() <<backimage->pixmap.rect().y();

this->scene->X=backimage->pixmap.width();
this->scene->Y=backimage->pixmap.height();
            this->scene->setSceneRect( backimage->pixmap.rect());



this->scene->update();


         return true;



        }

qDebug()<<"[set_map FALSE]";

        return false;

}

Map::~Map()
{
    delete ui;}

void Map::select(int ID)
{
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!";
}


/*
void Map::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<".";
    QGraphicsItem *item=scene->itemAt(event->pos().x(),event->pos().y(),QTransform());
    if(item->Type==MyDrawObject::Type)
    {
        qDebug()<<"[PROFIT]";

    }
}

void Map::mouseMoveEvent(QMouseEvent *event)
{

}

void Map::mouseReleaseEvent(QMouseEvent *event)
{

}
*/

void Map::on_pushButton_clicked()
{

    QString path=QFileDialog::getOpenFileName(this, "open file","");
    qDebug() << "App path : " << qApp->applicationDirPath();
   QString appPath =   qApp->applicationDirPath();
QDir dir(appPath);
QString local_path=dir.relativeFilePath(path);

qDebug()<<"[local path] "<<local_path;

     if(this->set_map(local_path))
       emit this_is_patch_to_map(local_path);



//    this->scene->addPixmap(map_picture);



}






