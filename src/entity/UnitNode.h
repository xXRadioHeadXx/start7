#ifndef UNITNODE_H
#define UNITNODE_H

#include <QObject>
#include <QSet>
#include <QVariant>
#include <QQueue>
#include <QHostAddress>
#include "UnitNodeCFG.h"
#include "UnitNodeTreeItem.h"
#include "SWP.h"
#include "ManagerSingleMsg.h"

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
    DKWasAlarm = 3,
    DKWas = 4,
    DKDone = 5,
    DKWrong = -1
};



class SWPSSOIBLIPType0x41;
class SWPSSOISDBLIPType0x41;
class SWPSSOIIUBLIPType0x41;
class SWPSSOIBLIPType0x42;
class SWPSSOISDBLIPType0x42;
class SWPBLIPType0x41;
class SWPBLIPType0x42;
class SWPRLMType0x31;
class SWPRLMCType0x31;
class SWPSDBLIPType0x41;
class SWPSDBLIPType0x42;
class SWPIUBLIPType0x41;
class SWPTGType0x31;
class SWPTGType0x34;
class SWPTGType0x33;
class SWPTGType0x32;
class SWPT4KBODType0x32;
class SWPT4KBODType0x33;
class DataQueueItem;

class UnitNode :
        /*public UnitNodeCFG
      , */public UnitNodeTreeItem
{
    Q_OBJECT
private:
    int clearedAlarm = -1;
    int defaultNeededStateWordType = 0x22;
    int neededStateWordType = 0x22;

    std::map<const uint8_t, StateWord> stateWords;

    QSet<QSharedPointer<UnitNode> > doubles; //[Obj_1]
    QSet<QString> metaNames; //[Obj_1]

    QSharedPointer<UnitNode> parentUN = QSharedPointer<UnitNode>(nullptr); //родительское устройство
    QList<QSharedPointer<UnitNode> > listChilde; //список детей
    QSharedPointer<UnitNode> interrogationUN = QSharedPointer<UnitNode>(nullptr); //родительское устройство


    int timeIntervalStatusRequest = 70;

    int dkStatus = DKCiclStatus::DKIgnore;
    bool dkInvolved = false;
    bool isAutoDkInvolved = false;
    bool waitAutoCommand = false;


    int countStatusConnectRequesterWaitAnswer = 0;
    int maxCountStatusConnectRequesterWaitAnswer = 400;
    int timeStatusConnectRequesterWaitAnswer = 0;

    int publishedState = -1;

    int metaEntity = 0;

    QQueue<DataQueueItem> queueMsg;

    QList<QSharedPointer<ManagerSingleMsg>> queueManagersSingleMsg;

    bool needPostponeQueueMsg = false;

    std::function<void()> updateStateConditionReactor;

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
    virtual bool operator>(const UnitNode& ) const;

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

    virtual QPixmap getPxm() const;

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

    StateWord getStateWord(const uint8_t key) const;
    void setStateWord(const uint8_t key, const StateWord &value);

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


    const SWPSDBLIPType0x41 swpSDBLIPType0x41() const; // {return SWPSDBLIP(getStateWord(), getNum2());}
    const SWPIUBLIPType0x41 swpIUBLIPType0x41() const; // {return SWPIUBLIP(getStateWord(), getNum2());}
    const SWPBLIPType0x41 swpBLIPType0x41() const; // {return SWPBLIP(getStateWord());}
    const SWPSSOIBLIPType0x41 swpSSOIBLIPType0x41() const;// {return SWPSSOIBLIPType0x41(getStateWord(0x41u));}
    const SWPSSOISDBLIPType0x41 swpSSOISDBLIPType0x41() const;// {return SWPSSOISDBLIPType0x41(getStateWord(0x41u), getNum2());}
    const SWPSSOIIUBLIPType0x41 swpSSOIIUBLIPType0x41() const;// {return SWPSSOIIUBLIPType0x41(getStateWord(0x41u), getNum2());}
    const SWPSSOIBLIPType0x42 swpSSOIBLIPType0x42() const;// {return SWPSSOIBLIPType0x42(getStateWord(0x42u));}
    const SWPSSOISDBLIPType0x42 swpSSOISDBLIPType0x42() const;// {return SWPSSOISDBLIPType0x42(getStateWord(0x42u), getNum2());}
    const SWPBLIPType0x42 swpBLIPType0x42() const;
    const SWPSDBLIPType0x42 swpSDBLIPType0x42() const;
    const SWPRLMType0x31 swpRLMType0x31() const; // {return SWPRLM(getStateWord());}
    const SWPRLMCType0x31 swpRLMCType0x31() const; // {return SWPRLMC(getStateWord());}
    const SWPTGType0x31 swpTGType0x31() const; // {return SWPTGType0x31(getStateWord());}
    const SWPTGType0x34 swpTGType0x34() const; // {return SWPTGType0x34(getStateWord(0x34u));}
    const SWPTGType0x33 swpTGType0x33() const; // {return SWPTGType0x33(getStateWord(0x33u));}
    const SWPTGType0x32 swpTGType0x32() const; // {return SWPTGType0x32(getStateWord(0x32u));}
    const SWPT4KBODType0x32 swpT4KBODType0x32() const;// {return SWPT4KBODType0x32(getStateWord(0x32u));}
    const SWPT4KBODType0x33 swpT4KBODType0x33() const;// {return SWPT4KBODType0x33(getStateWord(0x33u));}


    virtual bool operator<(const UnitNode &rhs) const final{
        if(getUdpAdress() < rhs.getUdpAdress())
            return true;
        else if(getUdpAdress() > rhs.getUdpAdress())
            return false;
        else if(getType() < rhs.getType())
            return true;
        else if(getType() > rhs.getType())
            return false;
        else if(getNum1() < rhs.getNum1())
            return true;
        else if(getNum1() > rhs.getNum1())
            return false;
        else if(getNum2() < rhs.getNum2())
            return true;
        else if(getNum2() > rhs.getNum2())
            return false;
        else if(getNum3() < rhs.getNum3())
            return true;
        else if(getNum3() > rhs.getNum3())
            return false;
        else if(getName() < rhs.getName())
            return true;
        else if(getName() > rhs.getName())
            return false;
        else if(getLevel() < rhs.getLevel())
            return true;
        else if(getLevel() > rhs.getLevel())
            return false;

        return false;
    }

    friend bool operator<(const UnitNode &lhs, const UnitNode &rhs) {
        if(lhs.getUdpAdress() < rhs.getUdpAdress())
            return true;
        else if(lhs.getUdpAdress() > rhs.getUdpAdress())
            return false;
        else if(lhs.getType() < rhs.getType())
            return true;
        else if(lhs.getType() > rhs.getType())
            return false;
        else if(lhs.getNum1() < rhs.getNum1())
            return true;
        else if(lhs.getNum1() > rhs.getNum1())
            return false;
        else if(lhs.getNum2() < rhs.getNum2())
            return true;
        else if(lhs.getNum2() > rhs.getNum2())
            return false;
        else if(lhs.getNum3() < rhs.getNum3())
            return true;
        else if(lhs.getNum3() > rhs.getNum3())
            return false;
        else if(lhs.getName() < rhs.getName())
            return true;
        else if(lhs.getName() > rhs.getName())
            return false;
        else if(lhs.getLevel() < rhs.getLevel())
            return true;
        else if(lhs.getLevel() > rhs.getLevel())
            return false;

        return false;
    }

    friend bool operator<(const QSharedPointer<UnitNode> &lhs, const QSharedPointer<UnitNode> &rhs) {
        if(lhs->getUdpAdress() < rhs->getUdpAdress())
            return true;
        else if(lhs->getUdpAdress() > rhs->getUdpAdress())
            return false;
        else if(lhs->getType() < rhs->getType())
            return true;
        else if(lhs->getType() > rhs->getType())
            return false;
        else if(lhs->getNum1() < rhs->getNum1())
            return true;
        else if(lhs->getNum1() > rhs->getNum1())
            return false;
        else if(lhs->getNum2() < rhs->getNum2())
            return true;
        else if(lhs->getNum2() > rhs->getNum2())
            return false;
        else if(lhs->getNum3() < rhs->getNum3())
            return true;
        else if(lhs->getNum3() > rhs->getNum3())
            return false;
        else if(lhs->getName() < rhs->getName())
            return true;
        else if(lhs->getName() > rhs->getName())
            return false;
        else if(lhs->getLevel() < rhs->getLevel())
            return true;
        else if(lhs->getLevel() > rhs->getLevel())
            return false;

        return false;
    }

    virtual int operator-(const UnitNode &rhs) const final{
        if(getUdpAdress() < rhs.getUdpAdress())
            return -1;
        else if(getUdpAdress() > rhs.getUdpAdress())
            return +1;
        else if(getType() < rhs.getType())
            return -1;
        else if(getType() > rhs.getType())
            return +1;
        else if(getNum1() < rhs.getNum1())
            return -1;
        else if(getNum1() > rhs.getNum1())
            return +1;
        else if(getNum2() < rhs.getNum2())
            return -1;
        else if(getNum2() > rhs.getNum2())
            return +1;
        else if(getNum3() < rhs.getNum3())
            return -1;
        else if(getNum3() > rhs.getNum3())
            return +1;
        else if(getName() < rhs.getName())
            return -1;
        else if(getName() > rhs.getName())
            return +1;
        else if(getLevel() < rhs.getLevel())
            return -1;
        else if(getLevel() > rhs.getLevel())
            return +1;

        return 0;
    }

    friend bool operator-(const UnitNode &lhs, const UnitNode &rhs) {
        if(lhs.getUdpAdress() < rhs.getUdpAdress())
            return -1;
        else if(lhs.getUdpAdress() > rhs.getUdpAdress())
            return +1;
        else if(lhs.getType() < rhs.getType())
            return -1;
        else if(lhs.getType() > rhs.getType())
            return +1;
        else if(lhs.getNum1() < rhs.getNum1())
            return -1;
        else if(lhs.getNum1() > rhs.getNum1())
            return +1;
        else if(lhs.getNum2() < rhs.getNum2())
            return -1;
        else if(lhs.getNum2() > rhs.getNum2())
            return +1;
        else if(lhs.getNum3() < rhs.getNum3())
            return -1;
        else if(lhs.getNum3() > rhs.getNum3())
            return +1;
        else if(lhs.getName() < rhs.getName())
            return -1;
        else if(lhs.getName() > rhs.getName())
            return +1;
        else if(lhs.getLevel() < rhs.getLevel())
            return -1;
        else if(lhs.getLevel() > rhs.getLevel())
            return +1;

        return 0;
    }

    friend bool operator-(const QSharedPointer<UnitNode> &lhs, const QSharedPointer<UnitNode> &rhs) {
        if(lhs->getUdpAdress() < rhs->getUdpAdress())
            return -1;
        else if(lhs->getUdpAdress() > rhs->getUdpAdress())
            return +1;
        else if(lhs->getType() < rhs->getType())
            return -1;
        else if(lhs->getType() > rhs->getType())
            return +1;
        else if(lhs->getNum1() < rhs->getNum1())
            return -1;
        else if(lhs->getNum1() > rhs->getNum1())
            return +1;
        else if(lhs->getNum2() < rhs->getNum2())
            return -1;
        else if(lhs->getNum2() > rhs->getNum2())
            return +1;
        else if(lhs->getNum3() < rhs->getNum3())
            return -1;
        else if(lhs->getNum3() > rhs->getNum3())
            return +1;
        else if(lhs->getName() < rhs->getName())
            return -1;
        else if(lhs->getName() > rhs->getName())
            return +1;
        else if(lhs->getLevel() < rhs->getLevel())
            return -1;
        else if(lhs->getLevel() > rhs->getLevel())
            return +1;

        return 0;
    }

    virtual bool equale(const QString &udpAddress, const int num1) const final{

        if(TypeUnitNodeEnum::BL_IP != getType()
        && TypeUnitNodeEnum::SSOI_BL_IP != getType()
        && TypeUnitNodeEnum::RLM_C != getType()
        && TypeUnitNodeEnum::RLM_KRL != getType()
        && TypeUnitNodeEnum::TG_Base != getType()
        && TypeUnitNodeEnum::BOD_T4K_M != getType())
            return false;

        const auto& hostSender = QHostAddress(udpAddress);
        const auto& hostSelf = QHostAddress(getUdpAdress());

        if(!hostSelf.isEqual(hostSender))
            return false;
        else if(getNum1() != num1)
            return false;

        return true;
    }

    virtual bool equale(const UnitNode &rhs) const final{
        if(getUdpAdress() != rhs.getUdpAdress())
            return false;
        else if(getType() != rhs.getType())
            return false;
        else if(getNum1() != rhs.getNum1())
            return false;
        else if(getNum2() != rhs.getNum2())
            return false;

        return true;
    }

    virtual bool equale(const QSharedPointer<UnitNode> &rhs) const final{
        if(getUdpAdress() != rhs->getUdpAdress())
            return false;
        else if(getType() != rhs->getType())
            return false;
        else if(getNum1() != rhs->getNum1())
            return false;
        else if(getNum2() != rhs->getNum2())
            return false;

        return true;
    }

    friend bool equale(const UnitNode &lhs, const UnitNode &rhs) {
        if(lhs.getUdpAdress() != rhs.getUdpAdress())
            return false;
        else if(lhs.getType() != rhs.getType())
            return false;
        else if(lhs.getNum1() != rhs.getNum1())
            return false;
        else if(lhs.getNum2() != rhs.getNum2())
            return false;

        return true;
    }

    friend bool equale(const QSharedPointer<UnitNode> &lhs, const QSharedPointer<UnitNode> &rhs) {
        if(lhs->getUdpAdress() != rhs->getUdpAdress())
            return false;
        else if(lhs->getType() != rhs->getType())
            return false;
        else if(lhs->getNum1() != rhs->getNum1())
            return false;
        else if(lhs->getNum2() != rhs->getNum2())
            return false;

        return true;
    }


public:

    const QList<QSharedPointer<ManagerSingleMsg>> &getListManagersSingleMsg();
    bool pushBackUniqManagerSingleMsg(const QSharedPointer<ManagerSingleMsg> &mngr);
    QSharedPointer<ManagerSingleMsg> takeFirstManagerSingleMsg();
    QSharedPointer<ManagerSingleMsg> getFirstManagerSingleMsg();

    const QQueue<DataQueueItem> &getQueueMsg();
    void pushUniqQueueMsg(const DataQueueItem &msg);
    DataQueueItem pullQueueMsg();


    void decrementCountStatusConnectRequesterWaitAnswer();
    int getPublishedState() const;
    void setPublishedState(int newPublishedState);

    int getMetaEntity() const;
    void setMetaEntity(int newMetaEntity);

    std::map<const uint8_t, StateWord> getStateWords() const;
    void setStateWords(const std::map<const uint8_t, StateWord> &value);

    bool getIsAutoDkInvolved() const;
    void setIsAutoDkInvolved(bool newIsAutoDkInvolved);

    bool getWaitAutoCommand() const;
    void setWaitAutoCommand(bool newWaitAutoCommand);
    bool takeResetWaitAutoCommand();

    void calkStateUN(QString &comment, int &code) const;

    bool getNeedPostponeQueueMsg() const;
    void setNeedPostponeQueueMsg(bool newNeedPostponeQueueMsg);

    std::function<void ()> getUpdateStateConditionReactor() const;
    void setUpdateStateConditionReactor(const std::function<void ()> &value);
    void callUpdateStateConditionReactor();

    int getTimeStatusConnectRequesterWaitAnswer() const;
    void setTimeStatusConnectRequesterWaitAnswer(int newTimeStatusConnectRequesterWaitAnswer);
    void resetTimeStatusConnectRequesterWaitAnswer();
    void incrementTimeStatusConnectRequesterWaitAnswer(int incrementDelay);
    void decrementTimeStatusConnectRequesterWaitAnswer(int decrementDelay);


    void setDefaultNeededStateWordType(int value);

    QSharedPointer<UnitNode> getInterrogationUN() const;
    void setInterrogationUN(QSharedPointer<UnitNode> newInterrogationUN);

    bool isClearedAlarm() const;
    int getClearedAlarm() const;
    void setClearedAlarm(int newClearedAlarm);
    void resetClearedAlarm();


protected :

};

class UnitNode_SYSTEM : public UnitNode {
public:
    explicit UnitNode_SYSTEM(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_SYSTEM(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_SYSTEM() {}
    virtual QPixmap getPxm() const final;
};

class UnitNode_GROUP : public UnitNode {
public:
    explicit UnitNode_GROUP(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_GROUP(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_GROUP() {}
    virtual QPixmap getPxm() const final;
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
    virtual int calcDKStatus() const override;
    virtual QPixmap getPxm() const final;
};

class UnitNode_IU_BL_IP : public UnitNode {
public:
    explicit UnitNode_IU_BL_IP(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_IU_BL_IP(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_IU_BL_IP() {}
    virtual QPixmap getPxm() const final;

};

class UnitNode_SSOI_SD_BL_IP : public UnitNode {
public:
    explicit UnitNode_SSOI_SD_BL_IP(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_SSOI_SD_BL_IP(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_SSOI_SD_BL_IP() {}
    virtual int calcDKStatus() const override;
    virtual QPixmap getPxm() const final;
};

class UnitNode_SSOI_IU_BL_IP : public UnitNode {
public:
    explicit UnitNode_SSOI_IU_BL_IP(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_SSOI_IU_BL_IP(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_SSOI_IU_BL_IP() {}
    virtual QPixmap getPxm() const final;
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
    virtual int calcDKStatus() const override;
    virtual QPixmap getPxm() const final;
};

class UnitNode_RLM_KRL : public UnitNode {
public:
    explicit UnitNode_RLM_KRL(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_RLM_KRL(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_RLM_KRL() {}
    virtual int calcDKStatus() const override;
    virtual QPixmap getPxm() const final;
};

class UnitNode_RLM_C : public UnitNode {
public:
    explicit UnitNode_RLM_C(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_RLM_C(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_RLM_C() {}
    virtual int calcDKStatus() const override;
    virtual QPixmap getPxm() const final;
};

class UnitNode_BOD_T4K_M final : public UnitNode {

public:
    explicit UnitNode_BOD_T4K_M(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {
        setDefaultNeededStateWordType(0x20);
        setNeededStateWordType(getDefaultNeededStateWordType());
    }
    explicit UnitNode_BOD_T4K_M(const UnitNode & parent) : UnitNode(parent) {
        setDefaultNeededStateWordType(0x20);
        setNeededStateWordType(getDefaultNeededStateWordType());
    }
    virtual ~UnitNode_BOD_T4K_M() {}
    virtual QPixmap getPxm() const final;
    virtual int calcDKStatus() const override;

};

class UnitNode_Y4_T4K_M final : public UnitNode {
public:
    explicit UnitNode_Y4_T4K_M(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_Y4_T4K_M(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_Y4_T4K_M() {}
    virtual QPixmap getPxm() const final;
};

class UnitNode_DD_T4K_M final : public UnitNode {
public:
    explicit UnitNode_DD_T4K_M(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_DD_T4K_M(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_DD_T4K_M() {}
    virtual QPixmap getPxm() const final;
};

class UnitNode_BOD_SOTA : public UnitNode {
public:
    explicit UnitNode_BOD_SOTA(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {
        setDefaultNeededStateWordType(0x20);
        setNeededStateWordType(getDefaultNeededStateWordType());
    }
    explicit UnitNode_BOD_SOTA(const UnitNode & parent) : UnitNode(parent) {
        setDefaultNeededStateWordType(0x20);
        setNeededStateWordType(getDefaultNeededStateWordType());
    }
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
//    virtual int isWasAlarm() const;
};

class UnitNode_SSOI_BL_IP : public UnitNode {
public:
    explicit UnitNode_SSOI_BL_IP(const QSharedPointer<UnitNode> parent = nullptr) : UnitNode(parent) {}
    explicit UnitNode_SSOI_BL_IP(const UnitNode & parent) : UnitNode(parent) {}
    virtual ~UnitNode_SSOI_BL_IP() {}
    virtual int isExistDK() const;
//    virtual int isWasAlarm() const;
};

#endif // UNITNODE_H
