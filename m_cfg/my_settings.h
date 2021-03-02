#ifndef MY_SETTINGS_H
#define MY_SETTINGS_H

#include <QObject>
#include <group.h>



class My_settings : public QObject
{
    Q_OBJECT
public:

    explicit My_settings(QObject *parent = nullptr);
    explicit My_settings(QString filepathy,QObject *parent = nullptr);

    void save_ini(QString filepath);

    void set_value(QString field, QByteArray value);
    QByteArray value(QString field);

    void beginGroup(QString group);
    void endGroup();



private:
    QMap<QString,MY_GROUP*> map;
    QString current_group;

signals:

};

#endif // MY_SETTINGS_H
