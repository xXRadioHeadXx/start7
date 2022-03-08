#ifndef TOPOLOGYSERVICEIMPL_H
#define TOPOLOGYSERVICEIMPL_H

#include <template/AfterConstructInitialization.h>

#include <QSet>
#include <QSharedPointer>

class UnitNode;
class TopologyServiceImpl :  public AfterConstructInitialization{
private:
    void inclusiveDouble(QSharedPointer<UnitNode> un);
    void inclusiveBLIPSD(QSharedPointer<UnitNode> un);
    void inclusiveBLIPIU(QSharedPointer<UnitNode> un);
    void inclusiveSSOIBLIPSD(QSharedPointer<UnitNode> un);
    void inclusiveSSOIBLIPIU(QSharedPointer<UnitNode> un);
    void inclusiveRLM(QSharedPointer<UnitNode> un);
    void inclusiveTG(QSharedPointer<UnitNode> un);
    void inclusiveBOD_T4K_M(QSharedPointer<UnitNode> un);
    void inclusiveY4_T4K_M(QSharedPointer<UnitNode> un);
    void inclusiveDD_T4K_M(QSharedPointer<UnitNode> un);

    bool inclusiveMetaBLIP();
    bool inclusiveMetaBLIPSD();
    bool inclusiveMetaBLIPSD(QSharedPointer<UnitNode> parent);
    bool inclusiveMetaBLIPIU();
    bool inclusiveMetaBLIPIU(QSharedPointer<UnitNode> parent);

    bool inclusiveMetaSSOIBLIP();
    bool inclusiveMetaSSOIBLIPSD();
    bool inclusiveMetaSSOIBLIPSD(QSharedPointer<UnitNode> parent);
    bool inclusiveMetaSSOIBLIPIU();
    bool inclusiveMetaSSOIBLIPIU(QSharedPointer<UnitNode> parent);

    bool inclusiveMetaRLM();

    bool inclusiveMetaBaseTG();
    bool inclusiveMetaTG();
    bool inclusiveMetaTG(QSharedPointer<UnitNode> parent);


//    bool inclusiveMetaBOD_T4K_M(QSharedPointer<UnitNode> un);
//    bool inclusiveMetaY4_T4K_M(QSharedPointer<UnitNode> un);
//    bool inclusiveMetaDD_T4K_M();
//    bool inclusiveMetaDD_T4K_M(QSharedPointer<UnitNode> un);

protected:
    QList<QSharedPointer<UnitNode>> listTreeUnitNodes;
    QSet<QSharedPointer<UnitNode>> listMetaRealUnitNodes;
    QList<QSharedPointer<UnitNode>> sortedMetaRealUnitNodes;
    QSharedPointer<UnitNode> systemUnitNodes;
    QSharedPointer<UnitNode> treeRootUnitNodes;

    void loadTreeUnitNodes();
    void addTreeChildrenToParent(QSharedPointer<UnitNode> child, QSharedPointer<UnitNode> parent);

public:
    TopologyServiceImpl();

    int linkDoubles(QSharedPointer<UnitNode> &un) const;
    QSet<QSharedPointer<UnitNode>>::iterator insertMetaRealUnitNodes(const QSharedPointer<UnitNode> &value);
    QList<QSharedPointer<UnitNode> > getLinkedUI(QSharedPointer<UnitNode> un) const;
    QSharedPointer<UnitNode> getMetaRealUnitNodes(const QSharedPointer<UnitNode> &target) const;
    QSharedPointer<UnitNode> getMetaRealUnitNodes(UnitNode*) const;
    void systemUnitNodesSetDkInvolvedFalse();
    QSharedPointer<UnitNode> getTreeUnitNodes(UnitNode* target) const;
    QSharedPointer<UnitNode> findReciver(QSharedPointer<UnitNode> reciver) const;
    QSet<QSharedPointer<UnitNode>> findChild(QSharedPointer<UnitNode> parent) const;
    QSet<QSharedPointer<UnitNode>> findChildByType(int type, QSharedPointer<UnitNode> parent) const;
    QSharedPointer<UnitNode> findParentByType(int type, QSharedPointer<UnitNode> parent) const;


    virtual ~TopologyServiceImpl() {
    }

};

#endif // TOPOLOGYSERVICEIMPL_H
