#ifndef TYPEUNITNODE_H
#define TYPEUNITNODE_H

#include <QMap>
#include <QMap>
#include <QSet>
#include <QString>
#include <QString>
#include "template/SingletonTemplate.h"
#include "KeyGroup.h"



class TypeUnitNode : public AfterConstructInitialization {
private:
    int intTitle;
    QString stringTitle;

    QSet<int> intSinonims;
    QSet<QString> stringSinonims;

    int intSubTitle;
    QSet<int> intSubSinonims;

    QMap<QString, bool> inclusiveGroups;

public:

protected:
    void setIntTitle(int newIntTitle);
    void setStringTitle(const QString &newStringTitle);
    void setIntSinonims(const QSet<int> &newIntSinonims);
    void setStringSinonims(const QSet<QString> &newStringSinonims);
    void setIntSubTitle(int newIntSubTitle);
    void setInclusiveGroups(const QMap<QString, bool> &newInclusiveGroups);
    void setIntSubSinonims(const QSet<int> &newIntSubSinonims);

public:
    int getIntTitle() const;
    const QString &getStringTitle() const;
    const QSet<int> &getIntSinonims() const;
    const QSet<QString> &getStringSinonims() const;
    int getIntSubTitle() const;
    const QMap<QString, bool> &getInclusiveGroups() const;
    const QSet<int> &getIntSubSinonims() const;

    virtual ~TypeUnitNode();

    operator int();
    operator QString();
    inline bool operator==(const int& rhs){ return getIntSinonims().contains(rhs); }
    inline bool operator!=(const int& rhs){ return !(*this == rhs); }
    inline bool operator==(const QString& rhs){ return getStringSinonims().contains(rhs); }
    inline bool operator!=(const QString& rhs){ return !(*this == rhs); }
    inline bool operator==(const TypeUnitNode& rhs){ return rhs.getIntSinonims().contains(getIntTitle()); }
    inline bool operator!=(const TypeUnitNode& rhs){ return !(*this == rhs); }

};

class SystemTypeUnitNode : public TypeUnitNode, public SingletonTemplate<SystemTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    SystemTypeUnitNode() {}
    virtual ~SystemTypeUnitNode(){
    }
};
class GroupTypeUnitNode : public TypeUnitNode, public SingletonTemplate<GroupTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    GroupTypeUnitNode() {}
    virtual ~GroupTypeUnitNode(){
    }
};

class BLIPSDTypeUnitNode : public TypeUnitNode, public SingletonTemplate<BLIPSDTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    BLIPSDTypeUnitNode() {}
    virtual ~BLIPSDTypeUnitNode(){
    };
};

class BLIPUZMonolitTypeUnitNode : public TypeUnitNode, public SingletonTemplate<BLIPUZMonolitTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    BLIPUZMonolitTypeUnitNode() {}
    virtual ~BLIPUZMonolitTypeUnitNode(){
    };
};

class BLIPBlockSvazyTypeUnitNode : public TypeUnitNode, public SingletonTemplate<BLIPUZMonolitTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    BLIPBlockSvazyTypeUnitNode() {}
    virtual ~BLIPBlockSvazyTypeUnitNode(){
    };
};

class BLIPIUTypeUnitNode : public TypeUnitNode, public SingletonTemplate<BLIPIUTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    BLIPIUTypeUnitNode() {}
    virtual ~BLIPIUTypeUnitNode(){
    };
};

class BLIPSSOISDTypeUnitNode : public TypeUnitNode, public SingletonTemplate<BLIPSSOISDTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    BLIPSSOISDTypeUnitNode() {}
    virtual ~BLIPSSOISDTypeUnitNode(){
    };
};

class BLIPSSOIIUTypeUnitNode : public TypeUnitNode, public SingletonTemplate<BLIPSSOIIUTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    BLIPSSOIIUTypeUnitNode() {}
    virtual ~BLIPSSOIIUTypeUnitNode(){
    };
};

class KLTypeUnitNode : public TypeUnitNode, public SingletonTemplate<KLTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    KLTypeUnitNode() {}
    virtual ~KLTypeUnitNode(){
    };
};
class TGTypeUnitNode : public TypeUnitNode, public SingletonTemplate<TGTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    TGTypeUnitNode() {}
    virtual ~TGTypeUnitNode(){
    };
};
class RLMKRLTypeUnitNode : public TypeUnitNode, public SingletonTemplate<RLMKRLTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    RLMKRLTypeUnitNode() {}
    virtual ~RLMKRLTypeUnitNode(){
    };
};
class RLMCTypeUnitNode : public TypeUnitNode, public SingletonTemplate<RLMCTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    RLMCTypeUnitNode() {}
    virtual ~RLMCTypeUnitNode(){
    };
};
class STRAZHIPTypeUnitNode : public TypeUnitNode, public SingletonTemplate<STRAZHIPTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    STRAZHIPTypeUnitNode() {}
    virtual ~STRAZHIPTypeUnitNode(){
    };
};
class NETDEVTypeUnitNode : public TypeUnitNode, public SingletonTemplate<NETDEVTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    NETDEVTypeUnitNode() {}
    virtual ~NETDEVTypeUnitNode(){
    };
};
class ONVIFTypeUnitNode : public TypeUnitNode, public SingletonTemplate<ONVIFTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    ONVIFTypeUnitNode() {}
    virtual ~ONVIFTypeUnitNode(){
    };
};
class BODT4KMTypeUnitNode : public TypeUnitNode, public SingletonTemplate<BODT4KMTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    BODT4KMTypeUnitNode() {}
    virtual ~BODT4KMTypeUnitNode(){
    };
};
class Y4T4KMTypeUnitNode : public TypeUnitNode, public SingletonTemplate<Y4T4KMTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    Y4T4KMTypeUnitNode() {}
    virtual ~Y4T4KMTypeUnitNode(){
    };
};
class DDT4KMTypeUnitNode : public TypeUnitNode, public SingletonTemplate<DDT4KMTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    DDT4KMTypeUnitNode() {}
    virtual ~DDT4KMTypeUnitNode(){
    };
};
class BODSOTATypeUnitNode : public TypeUnitNode, public SingletonTemplate<BODSOTATypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    BODSOTATypeUnitNode() {}
    virtual ~BODSOTATypeUnitNode(){
    };
};
class Y4SOTATypeUnitNode : public TypeUnitNode, public SingletonTemplate<Y4SOTATypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    Y4SOTATypeUnitNode() {}
    virtual ~Y4SOTATypeUnitNode(){
    };
};
class DDSOTATypeUnitNode : public TypeUnitNode, public SingletonTemplate<DDSOTATypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    DDSOTATypeUnitNode() {}
    virtual ~DDSOTATypeUnitNode(){
    };
};
class RIFRLMTypeUnitNode : public TypeUnitNode, public SingletonTemplate<RIFRLMTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    RIFRLMTypeUnitNode() {}
    virtual ~RIFRLMTypeUnitNode(){
    };
};
class RIFRLM24TypeUnitNode : public TypeUnitNode, public SingletonTemplate<RIFRLM24TypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
   RIFRLM24TypeUnitNode() {}
    virtual ~RIFRLM24TypeUnitNode(){
    };
};
class RIFRLMBTypeUnitNode : public TypeUnitNode, public SingletonTemplate<RIFRLMBTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    RIFRLMBTypeUnitNode() {}
    virtual ~RIFRLMBTypeUnitNode(){
    };
};
class RIFKRLTypeUnitNode : public TypeUnitNode, public SingletonTemplate<RIFKRLTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    RIFKRLTypeUnitNode() {}
    virtual ~RIFKRLTypeUnitNode(){
    };
};
class RazrivTypeUnitNode : public TypeUnitNode, public SingletonTemplate<RazrivTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    RazrivTypeUnitNode() {}
    virtual ~RazrivTypeUnitNode(){
    };
};
class Trassa1lTypeUnitNode : public TypeUnitNode, public SingletonTemplate<Trassa1lTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    Trassa1lTypeUnitNode() {}
    virtual ~Trassa1lTypeUnitNode(){
    };
};
class SSOISDTypeUnitNode : public TypeUnitNode, public SingletonTemplate<SSOISDTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
   SSOISDTypeUnitNode() {}
    virtual ~SSOISDTypeUnitNode(){
    };
};
class SSOIIUTypeUnitNode : public TypeUnitNode, public SingletonTemplate<SSOIIUTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    SSOIIUTypeUnitNode() {}
    virtual ~SSOIIUTypeUnitNode(){
    };
};
class ADAMTypeUnitNode : public TypeUnitNode, public SingletonTemplate<ADAMTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    ADAMTypeUnitNode() {}
    virtual ~ADAMTypeUnitNode(){
    };
};
class TorosTypeUnitNode : public TypeUnitNode, public SingletonTemplate<TorosTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    TorosTypeUnitNode() {}
    virtual ~TorosTypeUnitNode(){
    };
};
class DEVLINESDTypeUnitNode : public TypeUnitNode, public SingletonTemplate<DEVLINESDTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    DEVLINESDTypeUnitNode() {}
    virtual ~DEVLINESDTypeUnitNode(){
    };
};
class RASTRMTVTypeUnitNode : public TypeUnitNode, public SingletonTemplate<RASTRMTVTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    RASTRMTVTypeUnitNode() {}
    virtual ~RASTRMTVTypeUnitNode(){
    };
};
class INFOTABLOTypeUnitNode : public TypeUnitNode, public SingletonTemplate<INFOTABLOTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    INFOTABLOTypeUnitNode() {}
    virtual ~INFOTABLOTypeUnitNode(){
    };
};
class AllTypeUnitNode : public TypeUnitNode, public SingletonTemplate<AllTypeUnitNode> {
protected:
    virtual void afterConstructInitializationImpl() override;
public:
    AllTypeUnitNode() {}
    virtual ~AllTypeUnitNode(){
    }
};

static const QSet<const TypeUnitNode*> SetTypeUnitNode = {//&AllTypeUnitNode::instance(),
                                                    &SystemTypeUnitNode::instance(),
                                                    &GroupTypeUnitNode::instance(),
                                                    &BLIPSDTypeUnitNode::instance(),
                                                    &BLIPIUTypeUnitNode::instance(),
                                                    &BLIPSSOISDTypeUnitNode::instance(),
                                                    &BLIPSSOIIUTypeUnitNode::instance(),
                                                    &KLTypeUnitNode::instance(),
                                                    &TGTypeUnitNode::instance(),
                                                    &RLMKRLTypeUnitNode::instance(),
                                                    &RLMCTypeUnitNode::instance(),
                                                    &STRAZHIPTypeUnitNode::instance(),
                                                    &NETDEVTypeUnitNode::instance(),
                                                    &ONVIFTypeUnitNode::instance(),
                                                    &BODT4KMTypeUnitNode::instance(),
                                                    &Y4T4KMTypeUnitNode::instance(),
                                                    &DDT4KMTypeUnitNode::instance(),
                                                    &BODSOTATypeUnitNode::instance(),
                                                    &Y4SOTATypeUnitNode::instance(),
                                                    &DDSOTATypeUnitNode::instance(),
                                                    &RIFRLMTypeUnitNode::instance(),
                                                    &RIFRLM24TypeUnitNode::instance(),
                                                    &RIFRLMBTypeUnitNode::instance(),
                                                    &RIFKRLTypeUnitNode::instance(),
                                                    &RazrivTypeUnitNode::instance(),
                                                    &Trassa1lTypeUnitNode::instance(),
                                                    &SSOISDTypeUnitNode::instance(),
                                                    &SSOIIUTypeUnitNode::instance(),
                                                    &ADAMTypeUnitNode::instance(),
                                                    &TorosTypeUnitNode::instance(),
                                                    &DEVLINESDTypeUnitNode::instance(),
                                                    &RASTRMTVTypeUnitNode::instance(),
                                                    &INFOTABLOTypeUnitNode::instance(),
                                                    &BLIPUZMonolitTypeUnitNode::instance()
                                                   };


static const QMap<int, QString> MapOutTypeUnitNode = {{0,"не указан"},
                                                      {1,"РИФ-РЛМ"},
                                                      {2,"РИФ-КРЛ"},
                                                      {3,"РИФ-КРЛМ"},
                                                      {4,"РИФ-РЛМ-С"},
                                                      {5,"Трасса"},
                                                      {6,"Точка-Гарда"},
                                                      {7,"Разряд"},
                                                      {8,"УЗ Монолит"},
                                                      {9,"Блок связи"}};

#endif // TYPEUNITNODE_H
