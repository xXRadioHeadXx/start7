#ifndef UNITNODE_H
#define UNITNODE_H

#include <QObject>
#include <QSet>
#include <QVariant>
#include <DataQueueItem.h>
#include <QQueue>
#include <UnitNodeCFG.h>
#include <ServerUnitNodeTreeItem.h>

enum SubTypeApp {
    any = 0x00,
    server = 0x01,
    database = 0x02,
    configurator = 0x03
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

class SWPBLIP;
class SWPRLM;
class SWPRLMC;
class SWPSDBLIP;
class SWPIUBLIP;
class SWPTGType0x31;
class SWPTGType0x34;
class SWPTGType0x33;
class SWPTGType0x32;
class DataQueueItem;

class UnitNode :
        /*public UnitNodeCFG
      , */public ServerUnitNodeTreeItem
{
    Q_OBJECT
private:
    int defaultNeededStateWordType = 0x22;
    int neededStateWordType = 0x22;
    QByteArray stateWord;
    QByteArray stateWordType0x31;
    QByteArray stateWordType0x32;
    QByteArray stateWordType0x33;
    QByteArray stateWordType0x34;
    QSet<QSharedPointer<UnitNode> > doubles; //[Obj_1]
    QSet<QString> metaNames; //[Obj_1]

    QSharedPointer<UnitNode> parentUN; //родительское устройство
    QList<QSharedPointer<UnitNode> > listChilde; //список детей

    int timeIntervalStatusRequest = 70;

    int dkStatus = DKCiclStatus::DKIgnore;
    bool dkInvolved = false;

    int countStatusConnectRequesterWaitAnswer = 0;
    int maxCountStatusConnectRequesterWaitAnswer = 400;

private:

    bool editableControl = false;
    void matchEditableControl();

    bool editableOnOff = false;
    void matchEditableOnOff();

    bool needsPreamble = false;
    void matchNeedsPreamble();


public:

    struct LeftoversCounter{
        int counter = 0;
        int divider = 2;
        int mod() {return counter % divider;};
        void increment() {counter++; if(counter >= divider) counter = 0;};
    };
    LeftoversCounter leftoversCounter;

    explicit UnitNode(const QSharedPointer<UnitNode> parent = QSharedPointer<UnitNode>());
    explicit UnitNode(const UnitNode & parent);
    virtual ~UnitNode();

    virtual void setType(int value) final;
    virtual void setBazalt(int value) final;
    virtual void setUdpTimeout(int value) final;

    QVariant dataTreeColumn(int column) const;

    virtual UnitNode & operator=(const UnitNode& );

    void addChild(QSharedPointer<UnitNode> tc) noexcept;
    QSharedPointer<UnitNode>  child(int num) noexcept;
    int childCount() const noexcept;

    QSet<QString> getMetaNames() const;
    void resetMetaNames(const QString &value);
    void setMetaNames(const QString &value);
    void setMetaNames(const QSet<QString> &value);

    QSharedPointer<UnitNode> getParentUN() const;
    void setParentUN(QSharedPointer<UnitNode> value);

    QList<QSharedPointer<UnitNode> > getListChilde() const;

    QPixmap getPxm(SubTypeApp type = SubTypeApp::server);

//    int calcDkStatus() const;
    int getDkStatus() const;
    void setDkStatus(int value);

    bool getDkInvolved() const;
    void setDkInvolved(bool value);

    QSet<QSharedPointer<UnitNode> > getDoubles() const;
    void setDoubles(const QSet<QSharedPointer<UnitNode> > &value);
    void setDoubles(QSharedPointer<UnitNode> value);

    void updDoubl();

    void deleteChild(int row);

    void deleteAll();

    static int adamOffToMs(int adamOff);



    QByteArray getStateWord() const;
    void setStateWord(const QByteArray &value);

    virtual int isConnected() const;
    virtual int calcDKStatus() const {return DKCiclStatus::DKIgnore;}

    bool isEditableControl() const;    

    bool isEditableOnOff() const;

    bool isNeedsPreamble() const;

    int getCountStatusConnectRequesterWaitAnswer() const;
    void setCountStatusConnectRequesterWaitAnswer(int value);

    int getMaxCountStatusConnectRequesterWaitAnswer() const;
    void setMaxCountStatusConnectRequesterWaitAnswer(int value);

    void resetCountStatusConnectRequesterWaitAnswer();
    void incrementCountStatusConnectRequesterWaitAnswer();

    int getNeededStateWordType() const;
    void setNeededStateWordType(int value);

    int getDefaultNeededStateWordType() const;

    static QSharedPointer<UnitNode> findReciver(QSharedPointer<UnitNode> reciver);

    QByteArray getStateWordType0x31() const;
    void setStateWordType0x31(const QByteArray &value);

    QByteArray getStateWordType0x34() const;
    void setStateWordType0x34(const QByteArray &value);

    QByteArray getStateWordType0x33() const;
    void setStateWordType0x33(const QByteArray &value);

    QByteArray getStateWordType0x32() const;
    void setStateWordType0x32(const QByteArray &value);

    const SWPSDBLIP swpSDBLIP() const; // {return SWPSDBLIP(getStateWord(), getNum2());}
    const SWPIUBLIP swpIUBLIP() const; // {return SWPIUBLIP(getStateWord(), getNum2());}
    const SWPBLIP swpBLIP() const; // {return SWPBLIP(getStateWord());}
    const SWPRLM swpRLM() const; // {return SWPRLM(getStateWord());}
    const SWPRLMC swpRLMC() const; // {return SWPRLMC(getStateWord());}
    const SWPTGType0x31 swpTGType0x31() const; // {return SWPTGType0x31(getStateWord());}
    const SWPTGType0x34 swpTGType0x34() const; // {return SWPTGType0x34(getStateWordType0x34());}
    const SWPTGType0x33 swpTGType0x33() const; // {return SWPTGType0x33(getStateWordType0x33());}
    const SWPTGType0x32 swpTGType0x32() const; // {return SWPTGType0x32(getStateWordType0x32());}

public:
    QQueue<DataQueueItem> queueMsg;


protected :
    void setDefaultNeededStateWordType(int value);

public slots:

signals:

};

class UnitNode_SYSTEM : public UnitNode {
public:
    explicit UnitNode_SYSTEM(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_SYSTEM(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_SYSTEM() {}
};
class UnitNode_GROUP : public UnitNode {
public:
    explicit UnitNode_GROUP(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_GROUP(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_GROUP() {}
};
class UnitNode_KL : public UnitNode {
public:
    explicit UnitNode_KL(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_KL(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_KL() {}
};
class UnitNode_SD_BL_IP : public UnitNode {
public:
    explicit UnitNode_SD_BL_IP(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_SD_BL_IP(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_SD_BL_IP() {}
    virtual int calcDKStatus() const;
};
class UnitNode_IU_BL_IP : public UnitNode {
public:
    explicit UnitNode_IU_BL_IP(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_IU_BL_IP(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_IU_BL_IP() {}
};
class UnitNode_TG : public UnitNode {
public:
    explicit UnitNode_TG(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {
        setDefaultNeededStateWordType(0x2E);
        setNeededStateWordType(getDefaultNeededStateWordType());
    }
    explicit UnitNode_TG(const UnitNode & parent) : UnitNode(parent) {
        setDefaultNeededStateWordType(0x2E);
        setNeededStateWordType(getDefaultNeededStateWordType());
    }
    virtual ~UnitNode_TG() {}
    virtual int calcDKStatus() const;
};
class UnitNode_RLM_KRL : public UnitNode {
public:
    explicit UnitNode_RLM_KRL(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_RLM_KRL(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_RLM_KRL() {}
    virtual int calcDKStatus() const;
};
class UnitNode_RLM_C : public UnitNode {
public:
    explicit UnitNode_RLM_C(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_RLM_C(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_RLM_C() {}
    virtual int calcDKStatus() const;

};
class UnitNode_BOD_T4K_M : public UnitNode {
public:
    explicit UnitNode_BOD_T4K_M(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_BOD_T4K_M(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_BOD_T4K_M() {}
};
class UnitNode_Y4_T4K_M : public UnitNode {
public:
    explicit UnitNode_Y4_T4K_M(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_Y4_T4K_M(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_Y4_T4K_M() {}
};
class UnitNode_DD_T4K_M : public UnitNode {
public:
    explicit UnitNode_DD_T4K_M(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_DD_T4K_M(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_DD_T4K_M() {}
};
class UnitNode_BOD_SOTA : public UnitNode {
public:
    explicit UnitNode_BOD_SOTA(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_BOD_SOTA(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_BOD_SOTA() {}
};
class UnitNode_Y4_SOTA : public UnitNode {
public:
    explicit UnitNode_Y4_SOTA(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_Y4_SOTA(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_Y4_SOTA() {}
};
class UnitNode_DD_SOTA : public UnitNode {
public:
    explicit UnitNode_DD_SOTA(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_DD_SOTA(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_DD_SOTA() {}
};
class UnitNode_BL_IP : public UnitNode {
public:
    explicit UnitNode_BL_IP(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_BL_IP(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_BL_IP() {}
    virtual int isExistDK() const;
    virtual int isWasAlarm() const;
};

#endif // UNITNODE_H
