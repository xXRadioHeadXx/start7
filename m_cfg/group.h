#ifndef MY_GROUP_H
#define MY_GROUPGROUP_H

#include <QObject>
#include<QMap>
#include<qDebug>

class MY_GROUP : public QObject
{
    Q_OBJECT
public:
    explicit MY_GROUP(QObject *parent = nullptr);
    long get_id();
    QMap<QString,QPair<int,QByteArray>> map;

    QList<QString> list;

    void sort();


    bool operator<(const MY_GROUP other) const {
        qDebug()<<"Сравнение "<<id<<" и другой "<<other.id;
           return id<other.id;
       }

private:
    long id;


signals:


};

#endif // MY_GROUP_H
