#ifndef UNITNODE_H
#define UNITNODE_H

#include <QObject>
#include <QSet>
#include <QVariant>
#include <SWPBLIP.h>
#include <SWPRLM.h>
#include <SWPRLMC.h>
#include <SWPSDBLIP.h>
#include <SWPTGType0x31.h>
#include <SWPTGType0x34.h>
#include <SWPTGType0x33.h>
#include <SWPTGType0x32.h>

enum SubTypeApp {
    any = 0x00,
    server = 0x01,
    database = 0x02,
    configurator = 0x03
};

enum Status {
    Uncnown = 0x00,
    On = 0x01,
    Off = 0x02,
    Was = 0x04,
    Not = 0x08,
    Alarm = 0x10,
    Norm = 0x20,
    NoConnection = 0x40,
    Exists = 0x80
};

enum TypeUnitNode {
    SYSTEM = -1, //Система
    GROUP = 0, //Группа
    KL = 2, //Концентратор КЛ1
    SD_BL_IP = 11,//СД БЛ-IP
    IU_BL_IP = 12,//ИУ БЛ-IP 
    TG = 10,      //Точка/Гарда 
    RLM_KRL = 1, //РИФ-РЛМ/КРЛ/Трасса
    RLM_C = 111, //РИФ- РЛМ-С
    STRAZH_IP = 24, //Страж IP
    ONVIF = 25, //ONVIF камера
    BOD_T4K_M = 26,//БОД Точка-М/Гарда-М
    Y4_T4K_M = 27,//Участок Точка-М/Гарда-М
    DD_T4K_M = 28,//ДД Точка-М/Гарда-М
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
    INFO_TABLO = 71, //информационное табло

    SSOI_IP_SD = 44, //ССОИ СД
    SSOI_IP_IU = 45 //ССОИ ИУ
};

static QMap <int,int> timeouts{
{TypeUnitNode::GROUP, 0},
{TypeUnitNode::KL ,70 },
{TypeUnitNode::SD_BL_IP ,10 },
{TypeUnitNode::IU_BL_IP ,10 },
{TypeUnitNode::TG ,100 },
{TypeUnitNode::RLM_KRL ,70 },
{TypeUnitNode::RLM_C ,70 },
{TypeUnitNode::STRAZH_IP ,0 },
{TypeUnitNode::ONVIF ,0 },
{TypeUnitNode::BOD_T4K_M ,220 },
{TypeUnitNode::Y4_T4K_M ,0 },
{TypeUnitNode::DD_T4K_M ,0 },
{TypeUnitNode::BOD_SOTA ,320 },
{TypeUnitNode::Y4_SOTA ,0 },
{TypeUnitNode::DD_SOTA ,0 },
{TypeUnitNode::NET_DEV ,0 },

{TypeUnitNode::SSOI_SD ,0 },
{TypeUnitNode::SSOI_IU ,0 },
{TypeUnitNode::ADAM ,0 },
{TypeUnitNode::TOROS ,70 },
{TypeUnitNode::DEVLINE ,0 },
{TypeUnitNode::RASTRMTV ,0 },
{TypeUnitNode::INFO_TABLO ,0 },

};



enum DKCiclStatus {
    DKIgnore = 0,
    DKReady = 1,
    DKNorm = 2,
    DKWasAlarn = 3,
    DKWas = 4,
    DKDone = 5,
    DKWrong = -1
};

class UnitNode : public QObject
{
    Q_OBJECT



private:


    bool broken;
    QString brokeInfo;

    int neededStateWordType = 0;
    QByteArray stateWord;
    QByteArray stateWordType0x31;
    QByteArray stateWordType0x32;
    QByteArray stateWordType0x33;
    QByteArray stateWordType0x34;
    QSet<UnitNode *> doubles; //[Obj_1]
    QSet<QString> metaNames; //[Obj_1]
    int Type;//=0
    int Num1;//=0
    int Num2;//=0
    int Num3;//=0
    int Level;//=1
    QString Name;//=250
    int IconVisible;//=0
    int X;//=40
    int Y;//=40
    int DK;//=1
    int Bazalt;//=0
    int Metka;//=0
    int Razriv;//=0
    int AdamOff;//=0
    int AlarmMsgOn;//=0
    int ConnectBlock;//=0
    int OutType;//=0
    int asoosd_kk;//=0
    int asoosd_nn;//=0
    QString Description;//=
    float lan = 0;//=0
    float lon = 0;//=0
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

    UnitNode *parentUN = nullptr; //родительское устройство
    QList<UnitNode*> listChilde; //список детей

    UnitNode *treeParentUN = nullptr;
    QList<UnitNode*> listTreeChilde;


    int timeIntervalStatusRequest = 70;

    quint8 status1 = Status::Uncnown;
    quint8 status2 = Status::Uncnown;
    int dkStatus = DKCiclStatus::DKIgnore;
    bool dkInvolved = false;
    bool visible = false;
    bool control = true;

    int countSCRWA = 0;
    int maxCountSCRWA = 400;

private:
    bool editableControl = false;
    void matchEditableControl();

    bool editableOnOff = false;
    void matchEditableOnOff();

    bool needsPreamble = false;
    void matchNeedsPreamble();


public:

     void show();

    explicit UnitNode(UnitNode *parent = nullptr);
    explicit UnitNode(const UnitNode & parent);
    QVariant data(int column) const noexcept;

    UnitNode & operator=(const UnitNode& );

    void addTreeChild(UnitNode *tc) noexcept;

    void moveTreeChildUNUp(UnitNode * childUN);
    void moveTreeChildUNDown(UnitNode * childUN);

    void addChild(UnitNode *tc) noexcept;
    UnitNode* treeChild(int num) noexcept;
    QList<UnitNode*> treeChild() noexcept;
    UnitNode* child(int num) noexcept;
    int treeChildCount() const noexcept;
    int childCount() const noexcept;
    int treeRow() const noexcept;
    int columnCount() const noexcept;

    QSet<QString> getMetaNames() const;
    void resetMetaNames(const QString &value);
    void setMetaNames(const QString &value);
    void setMetaNames(const QSet<QString> &value);

    int getType() const;
    void setType(int value);



    int getNum1() const;
    void setNum1(int value);

    int getNum2() const;
    void setNum2(int value);

    int getNum3() const;
    void setNum3(int value);

    int getLevel() const;
    void setLevel(int value);

    QString getName() const;
    bool setName(const QString &value);

    int getIconVisible() const;
    void setIconVisible(int value);

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getDK() const;
    void setDK(int value);

    int getBazalt() const;
    void setBazalt(int value);

    int getMetka() const;
    void setMetka(int value);

    int getRazriv() const;
    void setRazriv(int value);

    int getAdamOff() const;
    void setAdamOff(int value);

    int getAlarmMsgOn() const;
    void setAlarmMsgOn(int value);

    int getConnectBlock() const;
    void setConnectBlock(int value);

    int getOutType() const;
    void setOutType(int value);

    int getAsoosd_kk() const;
    void setAsoosd_kk(int value);

    int getAsoosd_nn() const;
    void setAsoosd_nn(int value);

    QString getDescription() const;
    void setDescription(const QString &value);

    double getLan() const;
    void setLan(double value);

    double getLon() const;
    void setLon(double value);

    int getUdpUse() const;
    void setUdpUse(int value);

    QString getUdpAdress() const;
    void setUdpAdress(const QString &value);

    int getUdpPort() const;
    void setUdpPort(int value);

    int getUdpTimeout() const;
    void setUdpTimeout(int value);

    int getMetka1Time_0() const;
    void setMetka1Time_0(int value);

    int getMetka1Time_1() const;
    void setMetka1Time_1(int value);

    int getMetka2Time_0() const;
    void setMetka2Time_0(int value);

    int getMetka2Time_1() const;
    void setMetka2Time_1(int value);

    int getMetka3Time_0() const;
    void setMetka3Time_0(int value);

    int getMetka3Time_1() const;
    void setMetka3Time_1(int value);

    int getMetka4Time_0() const;
    void setMetka4Time_0(int value);

    int getMetka4Time_1() const;
    void setMetka4Time_1(int value);

    int getMetkaDopuskTime_0() const;
    void setMetkaDopuskTime_0(int value);

    int getMetkaDopuskTime_1() const;
    void setMetkaDopuskTime_1(int value);

    UnitNode *getParentUN() const;
    void setParentUN(UnitNode *value);

    UnitNode *getTreeParentUN() const;
    void setTreeParentUN(UnitNode *value);

    int getTimeIntervalStatusRequest() const;
    void setTimeIntervalStatusRequest(int value);

    QList<UnitNode *> getListTreeChilde() const;
    QList<UnitNode *> getListChilde() const;

    quint8 getStatus1() const;
    void setStatus1(const quint8 &value);

    quint8 getStatus2() const;
    void setStatus2(const quint8 &value);

    QPixmap getPxm(SubTypeApp type = SubTypeApp::server);
    QPixmap getPxm(SubTypeApp type,int column);
//    int calcDkStatus() const;
    int getDkStatus() const;
    void setDkStatus(int value);

    bool getDkInvolved() const;
    void setDkInvolved(bool value);

    QSet<UnitNode *> getDoubles() const;
    void setDoubles(const QSet<UnitNode *> &value);
    void setDoubles(UnitNode *value);

    void updDoubl();

    bool getControl() const;
    void setControl(bool value);

    void deleteChild(int row);

    void deleteAll();

    static int adamOffToMs(int adamOff);



    QByteArray getStateWord() const;
    void setStateWord(const QByteArray &value);

    //
//    virtual quint8 mask() const {return 0;};
//    virtual int isAlarm() const {return -1;};
//    virtual int isInAlarm() const {return -1;};
//    virtual int isOutAlarm() const {return -1;};
//    virtual int isNorm() const {return -1;};
//    virtual int isWasDK() const {return -1;};
//    virtual int isExistDK() const {return -1;};
//    virtual int isWasAlarm() const {return -1;};
//    virtual int isOn() const {return -1;}
//    virtual int isOff() const {return -1;}
    virtual int isConnected() const;
    virtual int calcDKStatus() const {return DKCiclStatus::DKIgnore;}
//    //
//    virtual double voltage() const {return -1.0;};
//    virtual int synchronization() const {return -1;};
//    virtual int isExternalSynchronization() const {return -1;};
//    virtual int isInternalSynchronization() const {return -1;};
//    virtual float threshold() const {return -1.0;};
//    virtual int clockPeriod() const {return -1;};
//    virtual int modeProcessing() const {return -1;};
//    virtual int lowLevl() const {return -1;};
//    virtual int isOpened() const {return -1;};
//    virtual int isInOpened() const {return -1;};
//    virtual int isOutOpened() const {return -1;};
//    virtual int isWasOpened() const {return -1;};

    //

    QString getIcon1Path() const;
    void setIcon1Path(const QString &value);

    QString getIcon2Path() const;
    void setIcon2Path(const QString &value);

    QString getIcon3Path() const;
    void setIcon3Path(const QString &value);

    QString getIcon4Path() const;
    void setIcon4Path(const QString &value);

    virtual QString toString() const;


    bool isEditableControl() const;    

    bool isEditableOnOff() const;

    bool isNeedsPreamble() const;

    int getCountSCRWA() const;
    void setCountSCRWA(int value);

    int getMaxCountSCRWA() const;
    void setMaxCountSCRWA(int value);

    QByteArray getStateWordType0x31() const;
    void setStateWordType0x31(const QByteArray &value);

    QByteArray getStateWordType0x34() const;
    void setStateWordType0x34(const QByteArray &value);

    QByteArray getStateWordType0x33() const;
    void setStateWordType0x33(const QByteArray &value);

    int getNeededStateWordType() const;
    void setNeededStateWordType(int value);

    QByteArray getStateWordType0x32() const;
    void setStateWordType0x32(const QByteArray &value);

    const SWPSDBLIP swpSDBLIP() const {return SWPSDBLIP(getStateWord(), getNum2());}
    const SWPIUBLIP swpIUBLIP() const {return SWPIUBLIP(getStateWord(), getNum2());}
    const SWPBLIP swpBLIP() const {return SWPBLIP(getStateWord());}
    const SWPRLM swpRLM() const {return SWPRLM(getStateWord());}
    const SWPRLMC swpRLMC() const {return SWPRLMC(getStateWord());}
    const SWPTGType0x31 swpTGType0x31() const {return SWPTGType0x31(getStateWord());}
    const SWPTGType0x34 swpTGType0x34() const {return SWPTGType0x34(getStateWordType0x34());}
    const SWPTGType0x33 swpTGType0x33() const {return SWPTGType0x33(getStateWordType0x33());}
    const SWPTGType0x32 swpTGType0x32() const {return SWPTGType0x32(getStateWordType0x32());}


    bool getBroken() const;
    void setBroken(bool value);

    QString getBrokeInfo() const;
    void setBrokeInfo(const QString &value);

public slots:

signals:

};

class UnitNode_SYSTEM : public UnitNode {
public:
    explicit UnitNode_SYSTEM(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_SYSTEM(const UnitNode & parent) : UnitNode(parent) {}
};
class UnitNode_GROUP : public UnitNode {
public:
    explicit UnitNode_GROUP(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_GROUP(const UnitNode & parent) : UnitNode(parent) {}
};
class UnitNode_KL : public UnitNode {
public:
    explicit UnitNode_KL(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_KL(const UnitNode & parent) : UnitNode(parent) {}
};
class UnitNode_SD_BL_IP : public UnitNode {
public:
    explicit UnitNode_SD_BL_IP(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_SD_BL_IP(const UnitNode & parent) : UnitNode(parent) {}
//    virtual quint8 mask() const;
//    virtual int isAlarm() const;
//    virtual int isInAlarm() const;
//    virtual int isNorm() const;
//    virtual int isWasAlarm() const;
//    virtual int isOn() const;
//    virtual int isOff() const;
    virtual int calcDKStatus() const {
        if(1 == swpSDBLIP().isWasAlarm() && 1 == swpSDBLIP().isAlarm()) {
            return DKCiclStatus::DKWasAlarn;
        } else if(1 == swpSDBLIP().isNorm() && 1 == swpSDBLIP().isWasAlarm()) {
            return DKCiclStatus::DKWas;
//            return DKCiclStatus::DKWrong;
        } else if(1 == swpSDBLIP().isAlarm()) {
            return DKCiclStatus::DKWrong;
//            return DKCiclStatus::DKWasAlarn;
        } else if(1 == swpSDBLIP().isOff()) {
            return DKCiclStatus::DKWrong;
        } else if(1 == swpSDBLIP().isNorm()) {
            return DKCiclStatus::DKNorm;
        }
        return DKCiclStatus::DKWrong;
    }
};
class UnitNode_IU_BL_IP : public UnitNode {
public:
    explicit UnitNode_IU_BL_IP(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_IU_BL_IP(const UnitNode & parent) : UnitNode(parent) {}

//    virtual quint8 mask() const;
//    virtual int isOutAlarm() const;
//    virtual int isOn() const;
//    virtual int isOff() const;
};
class UnitNode_TG : public UnitNode {
public:
    explicit UnitNode_TG(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_TG(const UnitNode & parent) : UnitNode(parent) {}
    virtual int calcDKStatus() const {
         SWPTGType0x31 swp = swpTGType0x31();
        if(1 == swp.isWasAlarm() && 1 == swp.isAlarm()) {
            return DKCiclStatus::DKWasAlarn;
        } else if(1 == swp.isNorm() && 1 == swp.isWasAlarm()) {
            return DKCiclStatus::DKWas;
//            return DKCiclStatus::DKWrong;
        } else if(1 == swp.isAlarm()) {
            return DKCiclStatus::DKWrong;
//            return DKCiclStatus::DKWasAlarn;
        } else if(1 == swp.isOff()) {
            return DKCiclStatus::DKWrong;
        } else if(1 == swp.isNorm()) {
            return DKCiclStatus::DKNorm;
        }
        return DKCiclStatus::DKWrong;
    }
};
class UnitNode_RLM_KRL : public UnitNode {
public:
    explicit UnitNode_RLM_KRL(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_RLM_KRL(const UnitNode & parent) : UnitNode(parent) {}
//    virtual float threshold() const;
//    virtual int modeProcessing() const;
//    virtual int clockPeriod() const;
//    virtual double voltage() const;
//    virtual int isOn() const;
//    virtual int isOff() const;
//    virtual int isAlarm() const;
//    virtual int isInAlarm() const;
//    virtual int isOutAlarm() const;
//    virtual int isNorm() const;
//    virtual int isWasAlarm() const;
//    virtual int isExistDK() const;
//    virtual int synchronization() const;
//    virtual int isWasDK() const;
//    virtual int isOpened() const;
//    virtual int isInOpened() const;
//    virtual int isWasOpened() const;
    virtual int calcDKStatus() const {
        if(1 == swpRLM().isWasAlarm() && 1 == swpRLM().isAlarm()) {
            return DKCiclStatus::DKWasAlarn;
        } else if(1 == swpRLM().isNorm() && 1 == swpRLM().isWasAlarm()) {
            return DKCiclStatus::DKWas;
//            return DKCiclStatus::DKWrong;
        } else if(1 == swpRLM().isAlarm()) {
            return DKCiclStatus::DKWrong;
//            return DKCiclStatus::DKWasAlarn;
        } else if(1 == swpRLM().isOff()) {
            return DKCiclStatus::DKWrong;
        } else if(1 == swpRLM().isNorm()) {
            return DKCiclStatus::DKNorm;
        }
        return DKCiclStatus::DKWrong;
    }


};
class UnitNode_RLM_C : public UnitNode {
public:
    explicit UnitNode_RLM_C(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_RLM_C(const UnitNode & parent) : UnitNode(parent) {}
//    virtual int isAlarm() const;
//    virtual int isInAlarm() const;
//    virtual int isOutAlarm() const;
//    virtual int isNorm() const;
//    virtual int isWasDK() const;
//    virtual int isExistDK() const;
//    virtual int isWasAlarm() const;
//    virtual int isOn() const;
//    virtual int isOff() const;
//    virtual double voltage() const;
//    virtual int synchronization() const;
//    virtual int isExternalSynchronization() const;
//    virtual int isInternalSynchronization() const;
//    virtual float threshold() const;
//    virtual int clockPeriod() const;
//    virtual int modeProcessing() const;
//    virtual int lowLevl() const;
    virtual int calcDKStatus() const {
        if(1 == swpRLMC().isWasAlarm() && 1 == swpRLMC().isAlarm()) {
            return DKCiclStatus::DKWasAlarn;
        } else if(1 == swpRLMC().isNorm() && 1 == swpRLMC().isWasAlarm()) {
            return DKCiclStatus::DKWas;
//            return DKCiclStatus::DKWrong;
        } else if(1 == swpRLMC().isAlarm()) {
            return DKCiclStatus::DKWrong;
//            return DKCiclStatus::DKWasAlarn;
        } else if(1 == swpRLMC().isOff()) {
            return DKCiclStatus::DKWrong;
        } else if(1 == swpRLMC().isNorm()) {
            return DKCiclStatus::DKNorm;
        }
        return DKCiclStatus::DKWrong;
    }

};
class UnitNode_BOD_T4K_M : public UnitNode {
public:
    explicit UnitNode_BOD_T4K_M(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_BOD_T4K_M(const UnitNode & parent) : UnitNode(parent) {}
};
class UnitNode_Y4_T4K_M : public UnitNode {
public:
    explicit UnitNode_Y4_T4K_M(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_Y4_T4K_M(const UnitNode & parent) : UnitNode(parent) {}
};
class UnitNode_DD_T4K_M : public UnitNode {
public:
    explicit UnitNode_DD_T4K_M(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_DD_T4K_M(const UnitNode & parent) : UnitNode(parent) {}
};
class UnitNode_BOD_SOTA : public UnitNode {
public:
    explicit UnitNode_BOD_SOTA(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_BOD_SOTA(const UnitNode & parent) : UnitNode(parent) {}
};
class UnitNode_Y4_SOTA : public UnitNode {
public:
    explicit UnitNode_Y4_SOTA(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_Y4_SOTA(const UnitNode & parent) : UnitNode(parent) {}
};
class UnitNode_DD_SOTA : public UnitNode {
public:
    explicit UnitNode_DD_SOTA(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_DD_SOTA(const UnitNode & parent) : UnitNode(parent) {}
};
class UnitNode_BL_IP : public UnitNode {
public:
    explicit UnitNode_BL_IP(UnitNode * parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_BL_IP(const UnitNode & parent) : UnitNode(parent) {}
    virtual int isExistDK() const;
    virtual int isWasAlarm() const;
};

#endif // UNITNODE_H
