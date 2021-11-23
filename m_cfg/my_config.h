#ifndef MY_CONFIG_H
#define MY_CONFIG_H
#include <QString>
#include <QMap>
#include <UnitNode.h>

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

struct SerNum_Name{
    QString SerNum;
    QString Name;
};



static QMap <int,QString> m_SSOI_SD_Num3{
{1 , "1"},
{2 , "2" },
{3 , "3" },
{4 , "4" },
{5 , "5" },
{6 , "6" },
{7 , "7" },
{8 , "8" },
{9 , "вскрытие" },
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

static QMap <int,QString> m_SSOI_IU_Num3{
{1 , "ИУ1"},
{2 , "ИУ2" },
{3 , "ИУ3" },
{4 , "ВК1" },
{5 , "ВК2" },
{6 , "ВК3" },
};

static QString str_NOTHING=          "";
static QString str_GROUP=          " ГРУППА";
static QString str_SD_BL_IP=       " БЛ-IP СД";
static QString str_IU_BL_IP=       " БЛ-IP ИУ";
static QString str_KL =            " КЛ1 (концентратор) СД";
static QString str_TG =            " Точка/Гарда";
static QString str_RLM_KRL =       " РИФ-РЛМ/КРЛ/Трасса";
static QString str_RLM_C =         " РИФ-РЛМ-С";
static QString str_STRAZH_IP =     " ТВ-камера+тепловиз.Страж";
static QString str_NET_DEV =       " Сетевое устройство";
static QString str_ONVIF =         " ТВ-камера ONVIF";
static QString str_BOD_T4K_M =     " Точка-М/Гарда БОД";
static QString str_Y4_T4K_M =      " Точка-М/Гарда Участок";
static QString str_DD_T4K_M =      " Точка-М/Гарда ДД";
static QString str_BOD_SOTA =      " Сота/Сота-М БОД";
static QString str_Y4_SOTA =       " Сота/Сота-М Участок";
static QString str_DD_SOTA =       " Сота/Сота-М ДД";

static QString str_RIF_RLM=        " РИФ-РЛМ";
static QString str_RIF_RLM_24=     " РИФ-РЛМ24";
static QString str_RIF_RLM_B=      " РИФ-РЛМ(Б)";
static QString str_RIF_KRL=        " РИФ-КРЛ";
static QString str_Razriv=         " Разрыв";
static QString str_trassa1l=       " Трасса-1л";

static QString str_SSOI_SD =       " ССОИ СД";
static QString str_SSOI_IU =       " ССОИ ИУ";
static QString str_ADAM =          " ADAM";
static QString str_TOROS =         " Торос";
static QString str_DEVLINE =       " ТВ-камера DevLine";
static QString str_RASTRMTV =      " ТВ-камера РАСТР-М-ТВ";
static QString str_INFO_TABLO =    " Информационное табло";

static QString str_SSOI_IP_SD =    " ССОИ IP СД";
static QString str_SSOI_IP_IU =    " ССОИ IP ИУ";

static QMap <int,QString> m_TypeUnitNode_d{
{-1, str_NOTHING},
{TypeUnitNode::GROUP, str_GROUP},
{TypeUnitNode::KL ,str_KL },
{TypeUnitNode::SD_BL_IP ,str_SD_BL_IP },
{TypeUnitNode::IU_BL_IP ,str_IU_BL_IP },
{TypeUnitNode::TG ,str_TG },
{TypeUnitNode::RLM_KRL ,str_RLM_KRL },
{TypeUnitNode::RLM_C ,str_RLM_C },
{TypeUnitNode::STRAZH_IP ,str_STRAZH_IP },
{TypeUnitNode::ONVIF ,str_ONVIF },
{TypeUnitNode::BOD_T4K_M ,str_BOD_T4K_M },
{TypeUnitNode::Y4_T4K_M ,str_Y4_T4K_M },
{TypeUnitNode::DD_T4K_M ,str_DD_T4K_M },
{TypeUnitNode::BOD_SOTA ,str_BOD_SOTA },
{TypeUnitNode::Y4_SOTA ,str_Y4_SOTA },
{TypeUnitNode::DD_SOTA ,str_DD_SOTA },
{TypeUnitNode::NET_DEV ,str_NET_DEV },

{TypeUnitNode::SSOI_SD ,str_SSOI_SD },
{TypeUnitNode::SSOI_IU ,str_SSOI_IU },
{TypeUnitNode::ADAM ,str_ADAM },
{TypeUnitNode::TOROS ,str_TOROS },
{TypeUnitNode::DEVLINE ,str_DEVLINE },
{TypeUnitNode::RASTRMTV ,str_RASTRMTV },
{TypeUnitNode::INFO_TABLO ,str_INFO_TABLO },
{TypeUnitNode::SSOI_IP_SD ,str_SSOI_IP_SD },
{TypeUnitNode::SSOI_IP_IU ,str_SSOI_IP_IU }
};

static QMap <int,QString> m_TypeUnitNode{
{TypeUnitNode::GROUP, str_GROUP},
{TypeUnitNode::KL ,str_KL },
{TypeUnitNode::SD_BL_IP ,str_SD_BL_IP },
{TypeUnitNode::IU_BL_IP ,str_IU_BL_IP },
{TypeUnitNode::TG ,str_TG },
{TypeUnitNode::RLM_KRL ,str_RLM_KRL },
{TypeUnitNode::RLM_C ,str_RLM_C },
{TypeUnitNode::STRAZH_IP ,str_STRAZH_IP },
{TypeUnitNode::ONVIF ,str_ONVIF },
{TypeUnitNode::BOD_T4K_M ,str_BOD_T4K_M },
{TypeUnitNode::Y4_T4K_M ,str_Y4_T4K_M },
{TypeUnitNode::DD_T4K_M ,str_DD_T4K_M },
{TypeUnitNode::BOD_SOTA ,str_BOD_SOTA },
{TypeUnitNode::Y4_SOTA ,str_Y4_SOTA },
{TypeUnitNode::DD_SOTA ,str_DD_SOTA },
{TypeUnitNode::NET_DEV ,str_NET_DEV },

{TypeUnitNode::SSOI_SD ,str_SSOI_SD },
{TypeUnitNode::SSOI_IU ,str_SSOI_IU },
{TypeUnitNode::ADAM ,str_ADAM },
{TypeUnitNode::TOROS ,str_TOROS },
{TypeUnitNode::DEVLINE ,str_DEVLINE },
{TypeUnitNode::RASTRMTV ,str_RASTRMTV },
{TypeUnitNode::INFO_TABLO ,str_INFO_TABLO },
{TypeUnitNode::SSOI_IP_SD ,str_SSOI_IP_SD },
{TypeUnitNode::SSOI_IP_IU ,str_SSOI_IP_IU }
};

static QMap <int,QString> m_RLM_KRL_type{
{0,str_RIF_RLM},
{1,str_RIF_RLM_24},
{2,str_RIF_RLM_B},
{3,str_RIF_KRL},
{4,str_Razriv},
{5,str_trassa1l},
};

static QList<QString> l_Unittype_rif={

    str_GROUP,
    str_SD_BL_IP,
    str_IU_BL_IP,
    str_KL,
    str_TG,
    str_RLM_KRL,
    str_RLM_C,
    str_STRAZH_IP,
    str_NET_DEV,
    str_ONVIF,
    str_BOD_T4K_M,
    str_Y4_T4K_M,
    str_DD_T4K_M,
    str_BOD_SOTA,
    str_Y4_SOTA,
    str_DD_SOTA,


    str_SSOI_SD,
    str_SSOI_IU,
    str_ADAM,
    str_TOROS,
    str_DEVLINE,
    str_RASTRMTV,
    str_INFO_TABLO,
    str_SSOI_IP_SD,
    str_SSOI_IP_IU
};

static QList<QString> l_Unittype_ssoi={


    str_GROUP,
    str_INFO_TABLO,
    str_SSOI_SD,
    str_SSOI_IU,
    str_RASTRMTV,


};

#endif // MY_CONFIG_H
