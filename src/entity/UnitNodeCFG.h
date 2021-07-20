#ifndef UNITNODECFG_H
#define UNITNODECFG_H

#include <QObject>

enum TypeUnitNode {
    SYSTEM = -1, //Система
    GROUP = 0, //Группа
    KL = 2, //Концентратор КЛ1
    SD_BL_IP = 11,//СД БЛ-IP
    IU_BL_IP = 12,//ИУ БЛ-IP 
    TG_Base = 110,      //Точка/Гарда родитель рессивер
    TG = 10,      //Точка/Гарда
    RLM_KRL = 1, //РИФ-РЛМ/КРЛ/Трасса
    RLM_C = 111, //РИФ- РЛМ-С
    STRAZH_IP = 24, //Страж IP
    ONVIF = 25, //ONVIF камера
    BOD_T4K_M = 26,//БОД Точка-М/Гарда
    Y4_T4K_M = 27,//Участок Точка-М/Гарда
    DD_T4K_M = 28,//ДД Точка-М/Гарда
    BOD_SOTA =29,//БОД Сота
    Y4_SOTA = 30,//Участок Сота
    DD_SOTA = 31,//ДД Сота
    NET_DEV = 200,//Сетевое устройство
    BL_IP = 0xFF, //БЛ IP

    SSOI_SD = 3, //ССОИ СД
    SSOI_IU = 4, //ССОИ ИУ
    ADAM = 7, //Адам
    TOROS = 8, //Торос
    DEVLINE = 32, //камера DevLine
    RASTRMTV =42, //камера РАСТР-М-ТВ
    INFO_TABLO = 71 //информационное табло
};

class UnitNodeCFG : public QObject
{
    Q_OBJECT
private:
    int Type=TypeUnitNode::SYSTEM;
    int Num1=-1;//=0
    int Num2;//=0
    int Num3;//=0
    int Level;//=1
    QString Name;//=250
    int IconVisible;//=0
    int X;//=40
    int Y;//=40
    int DK=1;
    int Bazalt=0;
    int Metka;//=0
    int Razriv;//=0
    int AdamOff;//=0
    int AlarmMsgOn;//=0
    int ConnectBlock;//=0
    int OutType;//=0
    int asoosd_kk;//=0
    int asoosd_nn;//=0
    QString Description;//=
    int lan = 0;//=0
    int lon = 0;//=0
    int UdpUse;//=0
    QString UdpAdress;//=
    int UdpPort;//=0
    int UdpTimeout = 50;
    int Metka1Time_0;//=0
    int Metka1Time_1;//=0
    int Metka2Time_0;//=0
    int Metka2Time_1;//=0
    int Metka3Time_0;//=0
    int Metka3Time_1;//=0
    int Metka4Time_0;//=0
    int Metka4Time_1;//=0
    int MetkaDopuskTime_0;//=0
    int MetkaDopuskTime_1;//=1

    QString Icon1Path;
    QString Icon2Path;
    QString Icon3Path;
    QString Icon4Path;

    int timeIntervalStatusRequest = 70;

    bool control = true;
public:

    explicit UnitNodeCFG(const UnitNodeCFG* parent = nullptr);
    explicit UnitNodeCFG(const UnitNodeCFG & parent);
    virtual ~UnitNodeCFG();

    virtual UnitNodeCFG & operator=(const UnitNodeCFG& );

    virtual int getType() const final;
    virtual void setType(int value) /*final*/;

    virtual int getNum1() const final;
    virtual void setNum1(int value) final;

    virtual int getNum2() const final;
    virtual void setNum2(int value) final;

    virtual int getNum3() const final;
    virtual void setNum3(int value) final;

    virtual int getLevel() const final;
    virtual void setLevel(int value) final;

    virtual QString getName() const final;
    virtual void setName(const QString &value) final;

    virtual int getIconVisible() const final;
    virtual void setIconVisible(int value) final;

    virtual int getX() const final;
    virtual void setX(int value) final;

    virtual int getY() const final;
    virtual void setY(int value) final;

    virtual int getDK() const final;
    virtual void setDK(int value) final;

    virtual int getBazalt() const final;
    virtual void setBazalt(int value) /*final*/;

    virtual int getMetka() const final;
    virtual void setMetka(int value) final;

    virtual int getRazriv() const final;
    virtual void setRazriv(int value) final;

    virtual int getAdamOff() const final;
    virtual void setAdamOff(int value) final;

    virtual int getAlarmMsgOn() const final;
    virtual void setAlarmMsgOn(int value) final;

    virtual int getConnectBlock() const final;
    virtual void setConnectBlock(int value) final;

    virtual int getOutType() const final;
    virtual void setOutType(int value) final;

    virtual int getAsoosd_kk() const final;
    virtual void setAsoosd_kk(int value) final;

    virtual int getAsoosd_nn() const final;
    virtual void setAsoosd_nn(int value) final;

    virtual QString getDescription() const final;
    virtual void setDescription(const QString &value) final;

    virtual int getLan() const final;
    virtual void setLan(int value) final;

    virtual int getLon() const final;
    virtual void setLon(int value) final;

    virtual int getUdpUse() const final;
    virtual void setUdpUse(int value) final;

    virtual QString getUdpAdress() const final;
    virtual void setUdpAdress(const QString &value) final;

    virtual QString getDirection() const final;


    virtual int getUdpPort() const final;
    virtual void setUdpPort(int value) final;

    virtual int getUdpTimeout() const final;
    virtual void setUdpTimeout(int value) /*final*/;

    virtual int getMetka1Time_0() const final;
    virtual void setMetka1Time_0(int value) final;

    virtual int getMetka1Time_1() const final;
    virtual void setMetka1Time_1(int value) final;

    virtual int getMetka2Time_0() const final;
    virtual void setMetka2Time_0(int value) final;

    virtual int getMetka2Time_1() const final;
    virtual void setMetka2Time_1(int value) final;

    virtual int getMetka3Time_0() const final;
    virtual void setMetka3Time_0(int value) final;

    virtual int getMetka3Time_1() const final;
    virtual void setMetka3Time_1(int value) final;

    virtual int getMetka4Time_0() const final;
    virtual void setMetka4Time_0(int value) final;

    virtual int getMetka4Time_1() const final;
    virtual void setMetka4Time_1(int value) final;

    virtual int getMetkaDopuskTime_0() const final;
    virtual void setMetkaDopuskTime_0(int value) final;

    virtual int getMetkaDopuskTime_1() const final;
    virtual void setMetkaDopuskTime_1(int value) final;

    virtual int getTimeIntervalStatusRequest() const final;
    virtual void setTimeIntervalStatusRequest(int value) final;

    virtual bool getControl() const final;
    virtual void setControl(bool value) final;

    static int adamOffToMs(int adamOff);

    virtual QString getIcon1Path() const final;
    virtual void setIcon1Path(const QString &value) final;

    virtual QString getIcon2Path() const final;
    virtual void setIcon2Path(const QString &value) final;

    virtual QString getIcon3Path() const final;
    virtual void setIcon3Path(const QString &value) final;

    virtual QString getIcon4Path() const final;
    virtual void setIcon4Path(const QString &value) final;

    virtual QString toString() const final;

};

#endif // UNITNODECFG_H
