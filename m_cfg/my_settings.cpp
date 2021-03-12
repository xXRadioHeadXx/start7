#include "my_settings.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QPair>

My_settings::My_settings(QObject *parent)
{
    current_group="";
}

My_settings::My_settings(QString filepath, QObject *parent)
{
    current_group="";

   QFile file(filepath);
   if(file.open(QIODevice::ReadOnly))
   {
      QDataStream stream(&file);    // read the data serialized from the file
      /*
      [   91
      =   61
         10
         13
         10
      ]   93
              */
      QString str;
      QMap<QString,QByteArray> fields;
      QList<QByteArray> list;
      QList<QByteArray> list1;
      QByteArray key;
      QByteArray val;
      QByteArray ar;
      int flag=0;
      int fl1=0;


       while(!file.atEnd())
                   {
                   flag=0;
           quint8 data;

                      stream >> data;
//                          qDebug()<<(char)data<<" "<<data;
                      if((data==13)||(data==10))
                          flag=1;

                     if(flag==0)
                     {
                        ar.append(data);
                     }
                     else
                     {
                        if(ar.size()>0)
                        list.append(ar);

                        QString str=QString::fromLocal8Bit(ar);
                        if(ar.size()>0)
//                          qDebug()<<"fl "<<flag<<" "<<str<<"            "<<ar.toHex();



                         str.clear();




                              if(ar.size()>0)
                              {

                                  int res=0;
                                  for(int i=0;i<ar.size();i++)
                                   {



                                      if((quint8)ar.at(i)==61)
                                          res=1;
                                      else
                                      if(res==0)
                                      {
                                         key.append(ar[i]);
                                      }
                                      else
                                      {
                                          val.append(ar[i]);
                                       }



                                   }
                           //      qDebug()<<"key "<<QString::fromUtf8(key);
                           //      qDebug()<< "val "<<" "<<QString::fromUtf8(val)<<" "<<val.toHex();

                              //    fields.insert(QString::fromUtf8(key),val);

                                 list1.append(val);
                                 key.clear();
                                 val.clear();
                          }
                          ar.clear();
                      }
                   }

   //    qDebug()<<"----------------------------------------------------------";

       QString str_group;

   //   MY_GROUP group[100];
      long cnt_group=0;
      int field=0;
   //   qDebug()<<"sz "<<list.size();
     foreach(QByteArray val,list)
       {
     //       qDebug()<< "ar "<<" "<<QString::fromUtf8(val)<<" "<<val.toHex();
            //check for GROUP
            if(((quint8)val[0]==91)&&((quint8)val[val.size()-1])==93)
            {
                field=0;

      //       qDebug()<<"----------------------------";


                str_group=QString::fromUtf8(val);
                str_group.replace("[","");
                str_group.replace("]","");


                MY_GROUP* gr=new MY_GROUP(this);


         //       qDebug()<<"id "<<gr->get_id();

                map.insert(str_group,gr);

                cnt_group++;

            //    qDebug()<<"id "<<map.last()->get_id();

           //     qDebug()<<"GROUP "<<str_group<<" id "<<map.last()->get_id();
          //      qDebug()<<"GROUP "<<str_group<<" id "<<map.value(str_group)->get_id();
            }
              else
            {

                QByteArray src;
                QByteArray key;

          //      qDebug()<<map.value(str_group)->map.size();

                int res=0;
                for(int i=0;i<val.size();i++)
                {
                    if((quint8)val.at(i)==61)
                    res=1;
                    else
                    if(res==0)
                    key.append(val[i]);
                    else
                    src.append(val[i]);
                }

                map.value(str_group)->map.insert(QString::fromUtf8(key), qMakePair(field,src));
           //     qDebug()<<"[+]";
            }
            field++;

       }
    }
   qDebug()<<"size"<<map.size();

   QList<MY_GROUP*> list;
   foreach(MY_GROUP* val,map.values())
   {
       list.append(val);
   }
//qDebug()<<"[1]";
   for (int i = 0; i <list.count(); ++i)
   {
     qDebug()<<map.key(list.at(i))<<"  id= "<<list.at(i)->get_id();

   }
//qDebug()<<"[2]";
/**/
}

void My_settings::save_ini(QString filepath)
{
    QByteArray next_string;
    next_string.append(0x0D);
    next_string.append(0x0A);
    QFile file(filepath);



    auto write_group = [](QDataStream* stream, QString src)
    {
      QByteArray res=src.toLocal8Bit();

      res.clear();
      res.append(91);
      res.append(src);
      res.append(93);
      res.append(0x0D);
      res.append(0x0A);


      stream->writeRawData(res,res.size());
    };

    auto write_empty_string = [](QDataStream* stream)
    {
      QByteArray res;

      res.clear();
      res.append(0x0D);
      res.append(0x0A);


      stream->writeRawData(res,res.size());
    };

    auto write_field = [](QDataStream* stream, QString key, QByteArray val)
    {
      QByteArray res=key.toLocal8Bit();

      res.clear();
      res.append(key);
      res.append(61);
      res.append(val);
      res.append(0x0D);
      res.append(0x0A);

      stream->writeRawData(res,res.size());
    };


//Создадим QList из ключей map и отсортируем
    QList<MY_GROUP*> list;
    foreach(MY_GROUP* val,this->map.values())
    {
        list.append(val);
    }

 //   qDebug()<<"-- До сортировки ------------------------";

    int res=1;
    int cnt=0;
    while((res==1)&&(cnt<2000))
    {
    res=0;
    for (int i = 0; i <list.count()-1; ++i)
    {
      if(list.at(i)->get_id()<(list.at(i+1)->get_id()))
      {
         //     qDebug()<<map.key(list.at(i))<<" id "<<(list.at(i))->get_id()<<" pos "<<list.count(list.at(i))<<" меньше чем "<<map.key(list.at(i+1))<<" id "<<(list.at(i+1))->get_id()<<" pos "<<list.count((list.at(i))+1);
      }
      else
      {
         //  qDebug()<<map.key(list.at(i))<<" id "<<(list.at(i))->get_id()<<" pos "<<list.count(list.at(i))<<" больше чем "<<map.key(list.at(i+1))<<" id "<<(list.at(i+1))->get_id()<<" pos "<<list.count((list.at(i))+1);
           list.move(i+1,i);
           res=1;
      }
    }
     cnt++;
   //  qDebug()<<"-----------------cnt "<<cnt<<" res"<<res;
    }


    qDebug()<<"-- После сортировки ------------------------";

    for (int i = 0; i <list.count(); ++i)
    {
      qDebug()<<map.key(list.at(i))<<"  id= "<<list.at(i)->get_id();

    }
    qDebug()<<"-- После сортировки ------------------------";

    if(file.open(QIODevice::WriteOnly))
    {
       QDataStream stream(&file);
       for (int i = 0; i <list.count(); ++i)
       {
          write_group(&stream,map.key(list.at(i)));

          MY_GROUP* group=list.at(i);
          group->sort();
          for(int i=0;i<group->list.count();i++)
          {
          QString key=group->list.at(i);

          write_field(&stream,key,group->map.value(key).second);

          }
          write_empty_string(&stream);
       }
    }

    file.close();
}

void My_settings::set_value(QString field, QByteArray value)
{



qDebug()<<"[1]";
    int first=map.value(current_group)->map.value(field).first;
qDebug()<<"[2]";
    QByteArray ar;
qDebug()<<"[3]";
    ar.clear();
qDebug()<<"[4]";
    ar.append(value);
qDebug()<<"[5]";

MY_GROUP* mgroup=map.value(current_group);

    mgroup->map.remove(field);
qDebug()<<"[6]";
    mgroup->map.insert(field, qMakePair(first,ar));


}

QByteArray My_settings::value(QString field)
{
    QByteArray ar;
    ar.clear();
  if(current_group!="")
  {
      qDebug()<<"[1]";
      QByteArray ar =  map.value(current_group)->map.value(field).second;
      qDebug()<<"[2]";
      qDebug()<<QString::fromUtf8(ar);
      qDebug()<<"[3]";
      return ar;
  }

  return ar;
}

void My_settings::beginGroup(QString group)
{
    current_group=group;
}

void My_settings::endGroup()
{
    current_group="";
}


