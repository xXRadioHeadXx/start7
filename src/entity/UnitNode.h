#ifndef UNITNODE_H
#define UNITNODE_H

#include <QObject>
#include <QSet>
#include <QVariant>

enum SubTypeApp {
    Uncnown = 0x00,
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
    GROUP = 0,
    SD_BL_IP = 11,
    IU_BL_IP = 12,
    BL_IP = 0xFF
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
    int lan;//=0
    int lon;//=0
    int UdpUse;//=0
    QString UdpAdress;//=
    int UdpPort;//=0
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

public:

    explicit UnitNode(QObject *parent = nullptr);
    UnitNode(const UnitNode & parent);
    UnitNode(UnitNode *parent);
    QVariant data(int column) const noexcept;

    UnitNode & operator=(const UnitNode& );

    void addTreeChild(UnitNode *tc) noexcept;
    void addChild(UnitNode *tc) noexcept;
    UnitNode* treeChild(int num) noexcept;
    QList<UnitNode*> treeChild() noexcept;
    UnitNode* child(int num) noexcept;
    int treeChildCount() const noexcept;
    int childCount() const noexcept;
    int treeRow() const noexcept;
    int columnCount() const noexcept;

    QSet<QString> getMetaNames() const;
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
    void setName(const QString &value);

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

    int getLan() const;
    void setLan(int value);

    int getLon() const;
    void setLon(int value);

    int getUdpUse() const;
    void setUdpUse(int value);

    QString getUdpAdress() const;
    void setUdpAdress(const QString &value);

    int getUdpPort() const;
    void setUdpPort(int value);

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

    int calcDkStatus() const;
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

public slots:
    //    void emitIMUpd();

signals:
    //    void imUpd();
};

#endif // UNITNODE_H
