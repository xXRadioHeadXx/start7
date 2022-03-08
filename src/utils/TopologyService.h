#ifndef TOPOLOGYSERVICE_H
#define TOPOLOGYSERVICE_H

#include "TopologyServiceImpl.h"
#include <template/SingletonTemplate.h>

class TopologyService : public TopologyServiceImpl, public SingletonTemplate<TopologyService>
{
private:
    virtual void afterConstructInitializationImpl() override;

    static const auto self();
public:
    TopologyService();
    virtual ~TopologyService() {
    }


    static QList<QSharedPointer<UnitNode> > &getListTreeUnitNodes();
    static QSet<QSharedPointer<UnitNode>> &getSetMetaRealUnitNodes();
    static QList<QSharedPointer<UnitNode>> &getSortedMetaRealUnitNodes();
    static QSharedPointer<UnitNode> &getSystemUnitNodes();
    static QSharedPointer<UnitNode> &getTreeRootUnitNodes();

    static int linkDoubles(QSharedPointer<UnitNode> &un);
    static QSet<QSharedPointer<UnitNode>>::iterator insertMetaRealUnitNodes(const QSharedPointer<UnitNode> &value);
    static QList<QSharedPointer<UnitNode> > getLinkedUI(QSharedPointer<UnitNode> un);
    static QSharedPointer<UnitNode> getMetaRealUnitNodes(const QSharedPointer<UnitNode> &target);
    static QSharedPointer<UnitNode> getMetaRealUnitNodes(UnitNode*);
    static void systemUnitNodesSetDkInvolvedFalse();
    static QSharedPointer<UnitNode> getTreeUnitNodes(UnitNode* target);

    static QSharedPointer<UnitNode> findReciver(QSharedPointer<UnitNode> subReciver);
    static QSet<QSharedPointer<UnitNode>> findChild(QSharedPointer<UnitNode> parent);
    static QSet<QSharedPointer<UnitNode>> findChildByType(int type, QSharedPointer<UnitNode> parent);
    static QSharedPointer<UnitNode> findParentByType(int type, QSharedPointer<UnitNode> parent);

};

#endif // TOPOLOGYSERVICE_H
