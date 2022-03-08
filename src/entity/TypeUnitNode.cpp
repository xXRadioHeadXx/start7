#include "TypeUnitNode.h"

#include <QMap>
#include <QSet>

//int TypeUnitNode::intTitle = -1;
//QString TypeUnitNode::stringTitle = "";

//QSet<int> TypeUnitNode::intSinonims = {};
//QSet<QString> TypeUnitNode::stringSinonims = {};

//int TypeUnitNode::intSubTitle = -1;
//QSet<int> TypeUnitNode::intSubSinonims = {};

//QMap<QString, bool> TypeUnitNode::inclusiveGroups = {};



void SystemTypeUnitNode::afterConstructInitializationImpl()
{
    //qDebug() << "TypeUnitNode::init";
    setIntTitle(-1);
    setStringTitle("Система");
    setIntSinonims({-1});
    setStringSinonims({"Система"});
    QMap<QString, bool> map;
    map.insert("ObjectGroup", false);
    setInclusiveGroups(map);
    setIntSubTitle(-1);
    setIntSubSinonims({-1});
}

TypeUnitNode::~TypeUnitNode()
{

}

TypeUnitNode::operator int()
{
    return getIntTitle();
}

TypeUnitNode::operator QString()
{
    return getStringTitle();
}

int TypeUnitNode::getIntTitle() const
{
    return intTitle;
}

void TypeUnitNode::setIntTitle(int newIntTitle)
{
    intTitle = newIntTitle;
}

const QString &TypeUnitNode::getStringTitle() const
{
    return stringTitle;
}

void TypeUnitNode::setStringTitle(const QString &newStringTitle)
{
    stringTitle = newStringTitle;
}

const QSet<int> &TypeUnitNode::getIntSinonims() const
{
    return intSinonims;
}

void TypeUnitNode::setIntSinonims(const QSet<int> &newIntSinonims)
{
    intSinonims = newIntSinonims;
}

const QSet<QString> &TypeUnitNode::getStringSinonims() const
{
    return stringSinonims;
}

void TypeUnitNode::setStringSinonims(const QSet<QString> &newStringSinonims)
{
    stringSinonims = newStringSinonims;
}

const QMap<QString, bool> &TypeUnitNode::getInclusiveGroups() const
{
    return inclusiveGroups;
}

void TypeUnitNode::setInclusiveGroups(const QMap<QString, bool> &newInclusiveGroups)
{
    inclusiveGroups = newInclusiveGroups;
}

int TypeUnitNode::getIntSubTitle() const
{
    return intSubTitle;
}

void TypeUnitNode::setIntSubTitle(int newIntSubTitle)
{
    intSubTitle = newIntSubTitle;
}

const QSet<int> &TypeUnitNode::getIntSubSinonims() const
{
    return intSubSinonims;
}

void TypeUnitNode::setIntSubSinonims(const QSet<int> &newIntSubSinonims)
{
    intSubSinonims = newIntSubSinonims;
}

void GroupTypeUnitNode::afterConstructInitializationImpl()
{
    //qDebug() << "GroupTypeUnitNode::init";
    setIntTitle(0);
    setStringTitle("ГРУППА");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void BLIPSDTypeUnitNode::afterConstructInitializationImpl()
{
    //qDebug() << "BLIPSDTypeUnitNode::init";
    setIntTitle(11);
    setStringTitle("БЛ-IP СД");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void BLIPUZMonolitTypeUnitNode::afterConstructInitializationImpl()
{
    //qDebug() << "BLIPUZMonolitTypeUnitNode::init";
    setIntTitle(11);
    setIntSinonims({getIntTitle()});
    setIntSubTitle(8);
    setIntSubSinonims({getIntSubTitle()});
    setStringTitle("УЗ Монолит");
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void BLIPBlockSvazyTypeUnitNode::afterConstructInitializationImpl()
{
    //qDebug() << "BLIPUZMonolitTypeUnitNode::init";
    setIntTitle(11);
    setIntSinonims({getIntTitle()});
    setIntSubTitle(9);
    setIntSubSinonims({getIntSubTitle()});
    setStringTitle("УЗ Монолит");
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void BLIPSSOISDTypeUnitNode::afterConstructInitializationImpl()
{
    //qDebug() << "BLIPSSOISDTypeUnitNode::init";
    setIntTitle(44);
    setStringTitle("СД ССОИ-IP");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void BLIPSSOIIUTypeUnitNode::afterConstructInitializationImpl()
{
    //qDebug() << "BLIPSSOIIUTypeUnitNode::init";
    setIntTitle(45);
    setStringTitle("ИУ ССОИ-IP");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void BLIPIUTypeUnitNode::afterConstructInitializationImpl()
{
    //qDebug() << "BLIPIUTypeUnitNode::init";
    setIntTitle(12);
    setStringTitle("БЛ-IP ИУ");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void KLTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(2);
    setStringTitle("КЛ1 (концентратор) СД");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void TGTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(10);
    setStringTitle("Точка/Гарда");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void RLMKRLTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(1);
    setIntSubSinonims({0,1,2,3,4,5});
    setStringTitle("РИФ-РЛМ/КРЛ/Трасса");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void RLMCTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(111);
    setStringTitle("РИФ-РЛМ-С");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void STRAZHIPTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(24);
    setStringTitle("ТВ-камера+тепловиз.Страж");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void NETDEVTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(200);
    setStringTitle("Сетевое устройство");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}


void ONVIFTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(25);
    setStringTitle("ТВ-камера ONVIF");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void BODT4KMTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(26);
    setStringTitle("Точка-М/Гарда БОД");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void Y4T4KMTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(27);
    setStringTitle("Точка-М/Гарда Участок");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void DDT4KMTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(28);
    setStringTitle("Точка-М/Гарда ДД");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void BODSOTATypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(29);
    setStringTitle("Сота/Сота-М БОД");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void Y4SOTATypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(30);
    setStringTitle("Сота/Сота-М Участок");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void DDSOTATypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(31);
    setStringTitle("Сота/Сота-М ДД");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void RIFRLMTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(1);
    setIntSubTitle(0);
    setIntSubSinonims({getIntSubTitle()});
    setStringTitle("РИФ-РЛМ");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void RIFRLM24TypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(1);
    setIntSubTitle(1);
    setIntSubSinonims({getIntSubTitle()});
    setStringTitle("РИФ-РЛМ24");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void RIFRLMBTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(1);
    setIntSubTitle(2);
    setIntSubSinonims({getIntSubTitle()});
    setStringTitle("ИФ-РЛМ(Б)");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void RIFKRLTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(1);
    setIntSubTitle(3);
    setIntSubSinonims({getIntSubTitle()});
    setStringTitle("РИФ-КРЛ");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void RazrivTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(1);
    setIntSubTitle(4);
    setIntSubSinonims({getIntSubTitle()});
    setStringTitle("Разрыв");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void Trassa1lTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(1);
    setIntSubTitle(5);
    setIntSubSinonims({getIntSubTitle()});
    setStringTitle("Трасса-1л");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void SSOISDTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(3);
    setStringTitle("ССОИ СД");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void SSOIIUTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(4);
    setStringTitle("ССОИ ИУ");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void ADAMTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(7);
    setStringTitle("ADAM");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void TorosTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(8);
    setStringTitle("Торос");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
}

void DEVLINESDTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(32);
    setStringTitle("ТВ-камера DevLine");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void RASTRMTVTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(42);
    setStringTitle("ТВ-камера РАСТР-М-ТВ");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void INFOTABLOTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(71);
    setStringTitle("Информационное табло");
    setIntSinonims({getIntTitle()});
    setStringSinonims({getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", false}});
}

void AllTypeUnitNode::afterConstructInitializationImpl()
{
    setIntTitle(0);
    setStringTitle("Все");
    setIntSinonims({0,
                    SystemTypeUnitNode::instance().getIntTitle(),
                    GroupTypeUnitNode::instance().getIntTitle(),
                    BLIPSDTypeUnitNode::instance().getIntTitle(),
                    BLIPIUTypeUnitNode::instance().getIntTitle(),
                    BLIPSSOISDTypeUnitNode::instance().getIntTitle(),
                    BLIPSSOISDTypeUnitNode::instance().getIntTitle(),
                    KLTypeUnitNode::instance().getIntTitle(),
                    TGTypeUnitNode::instance().getIntTitle(),
                    RLMKRLTypeUnitNode::instance().getIntTitle(),
                    RLMCTypeUnitNode::instance().getIntTitle(),
                    STRAZHIPTypeUnitNode::instance().getIntTitle(),
                    NETDEVTypeUnitNode::instance().getIntTitle(),
                    ONVIFTypeUnitNode::instance().getIntTitle(),
                    BODT4KMTypeUnitNode::instance().getIntTitle(),
                    Y4T4KMTypeUnitNode::instance().getIntTitle(),
                    DDT4KMTypeUnitNode::instance().getIntTitle(),
                    BODSOTATypeUnitNode::instance().getIntTitle(),
                    Y4SOTATypeUnitNode::instance().getIntTitle(),
                    DDSOTATypeUnitNode::instance().getIntTitle(),
                    RIFRLMTypeUnitNode::instance().getIntTitle(),
                    RIFRLM24TypeUnitNode::instance().getIntTitle(),
                    RIFRLMBTypeUnitNode::instance().getIntTitle(),
                    RIFKRLTypeUnitNode::instance().getIntTitle(),
                    RazrivTypeUnitNode::instance().getIntTitle(),
                    Trassa1lTypeUnitNode::instance().getIntTitle(),
                    SSOISDTypeUnitNode::instance().getIntTitle(),
                    SSOIIUTypeUnitNode::instance().getIntTitle(),
                    ADAMTypeUnitNode::instance().getIntTitle(),
                    TorosTypeUnitNode::instance().getIntTitle(),
                    DEVLINESDTypeUnitNode::instance().getIntTitle(),
                    RASTRMTVTypeUnitNode::instance().getIntTitle(),
                    INFOTABLOTypeUnitNode::instance().getIntTitle()
                   });
    setStringSinonims({"Все",
                       SystemTypeUnitNode::instance().getStringTitle(),
                       GroupTypeUnitNode::instance().getStringTitle(),
                       BLIPSDTypeUnitNode::instance().getStringTitle(),
                       BLIPIUTypeUnitNode::instance().getStringTitle(),
                       BLIPSSOISDTypeUnitNode::instance().getStringTitle(),
                       BLIPSSOIIUTypeUnitNode::instance().getStringTitle(),
                       KLTypeUnitNode::instance().getStringTitle(),
                       TGTypeUnitNode::instance().getStringTitle(),
                       RLMKRLTypeUnitNode::instance().getStringTitle(),
                       RLMCTypeUnitNode::instance().getStringTitle(),
                       STRAZHIPTypeUnitNode::instance().getStringTitle(),
                       NETDEVTypeUnitNode::instance().getStringTitle(),
                       ONVIFTypeUnitNode::instance().getStringTitle(),
                       BODT4KMTypeUnitNode::instance().getStringTitle(),
                       Y4T4KMTypeUnitNode::instance().getStringTitle(),
                       DDT4KMTypeUnitNode::instance().getStringTitle(),
                       BODSOTATypeUnitNode::instance().getStringTitle(),
                       Y4SOTATypeUnitNode::instance().getStringTitle(),
                       DDSOTATypeUnitNode::instance().getStringTitle(),
                       RIFRLMTypeUnitNode::instance().getStringTitle(),
                       RIFRLM24TypeUnitNode::instance().getStringTitle(),
                       RIFRLMBTypeUnitNode::instance().getStringTitle(),
                       RIFKRLTypeUnitNode::instance().getStringTitle(),
                       RazrivTypeUnitNode::instance().getStringTitle(),
                       Trassa1lTypeUnitNode::instance().getStringTitle(),
                       SSOISDTypeUnitNode::instance().getStringTitle(),
                       SSOIIUTypeUnitNode::instance().getStringTitle(),
                       ADAMTypeUnitNode::instance().getStringTitle(),
                       TorosTypeUnitNode::instance().getStringTitle(),
                       DEVLINESDTypeUnitNode::instance().getStringTitle(),
                       RASTRMTVTypeUnitNode::instance().getStringTitle(),
                       INFOTABLOTypeUnitNode::instance().getStringTitle()});
    setInclusiveGroups({{"ObjectGroup", true}});
    setIntSubTitle(-1);
    setIntSubSinonims({0,1,2,3,4,5,6,7,8,9});
}

