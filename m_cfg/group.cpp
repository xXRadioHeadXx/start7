#include "group.h"
#include <QDebug>

MY_GROUP::MY_GROUP(QObject *parent) : QObject(parent)
{
    static int val=0;
    qDebug()<<"static int val: "<<val;
    id=val;

    val++;
}

long MY_GROUP::get_id()
{
    return id;
}

void MY_GROUP::sort()
{

    foreach(QString str,map.keys())
    {
        list.append(str);
    }

    int res=1;
    int cnt=0;
    while((res=1)&&(cnt<2000))
    {
        res=0;



        for(int i=0;i<list.count()-1;i++)
        {
            int id=map.value(list.at(i)).first;
            int id_next=map.value(list.at(i+1)).first;

            if(id>id_next)
            {
              res=1;
              list.move(i+1,i);
            }

        }
        cnt++;
    }
}


