#ifndef MY_CONFIG_H
#define MY_CONFIG_H
#include <QString>
#include <QMap>

class INameUpdater
{
    public:
        virtual ~INameUpdater() {}
        virtual void updateName(QString name) = 0;
};

class IDMaster
{
    public:
        virtual ~IDMaster() {}
        virtual int getID() = 0;
};

static const QMap <int,QString> m_SSOI_SD_OutType{
    {0,"не указан"},
    {1,"РИФ-РЛМ"},
    {2,"РИФ-КРЛ"},
    {3,"РИФ-КРЛМ"},
    {4,"РИФ-РЛМ-С"},
    {5,"Трасса"},
    {6,"Точка-Гарда"},
    {7,"Разряд"},
    {8,"УЗ Монолит"},
    {9,"Блок связи"},
};

static const QMap <int,QString> m_SD_BL_IP_OutType{
    {0,"не указан"},
    {1,"РИФ-РЛМ"},
    {2,"РИФ-КРЛ"},
    {3,"РИФ-КРЛМ"},
    {4,"РИФ-РЛМ-С"},
    {5,"Трасса"},
    {6,"Точка-Гарда"},
    {7,"Разряд"},
    {8,"УЗ Монолит"},
};

#endif // MY_CONFIG_H
