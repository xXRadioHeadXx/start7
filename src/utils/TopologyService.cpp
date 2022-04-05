#include "TopologyService.h"
#include "IniFileService.h"
#include "UnitNodeFactory.h"
#include "global.h"

TopologyService::TopologyService()
{
    treeRootUnitNodes = QSharedPointer<UnitNode>(new UnitNode());
}

void TopologyService::afterConstructInitializationImpl()
{
    loadTreeUnitNodes();
}

const auto TopologyService::self()
{
    return dynamic_cast<TopologyServiceImpl *>(&TopologyService::instance());
}

QList<QSharedPointer<UnitNode> > &TopologyService::getListTreeUnitNodes()
{
    return TopologyService::instance().listTreeUnitNodes;
}

QSet<QSharedPointer<UnitNode> > &TopologyService::getSetMetaRealUnitNodes()
{
    return TopologyService::instance().listMetaRealUnitNodes;
}

QList<QSharedPointer<UnitNode> > &TopologyService::getSortedMetaRealUnitNodes()
{
    return TopologyService::instance().sortedMetaRealUnitNodes;
}

QSharedPointer<UnitNode> &TopologyService::getSystemUnitNodes()
{
    return TopologyService::instance().systemUnitNodes;
}

QSharedPointer<UnitNode> &TopologyService::getTreeRootUnitNodes()
{
    return TopologyService::instance().treeRootUnitNodes;
}

int TopologyService::linkDoubles(QSharedPointer<UnitNode> &un)
{
    return TopologyService::self()->linkDoubles(un);
}

QSet<QSharedPointer<UnitNode>>::iterator TopologyService::insertMetaRealUnitNodes(const QSharedPointer<UnitNode> &value) {
    return TopologyService::self()->insertMetaRealUnitNodes(value);
}

QList<QSharedPointer<UnitNode> > TopologyService::getLinkedUI(QSharedPointer<UnitNode> un)
{
    return TopologyService::self()->getLinkedUI(un);
}

QSharedPointer<UnitNode> TopologyService::getMetaRealUnitNodes(const QSharedPointer<UnitNode> &target)
{
    return TopologyService::self()->getMetaRealUnitNodes(target);
}

QSharedPointer<UnitNode> TopologyService::getMetaRealUnitNodes(UnitNode* target)
{
    return TopologyService::self()->getMetaRealUnitNodes(target);
}

void TopologyService::systemUnitNodesSetDkInvolvedFalse()
{
    return TopologyService::self()->systemUnitNodesSetDkInvolvedFalse();
}

QSharedPointer<UnitNode> TopologyService::getTreeUnitNodes(UnitNode* target)
{
    return TopologyService::self()->getTreeUnitNodes(target);
}

QSharedPointer<UnitNode> TopologyService::findReciver(QSharedPointer<UnitNode> reciver)
{
    return TopologyService::self()->findReciver(reciver);
}

QSet<QSharedPointer<UnitNode>> TopologyService::findChild(QSharedPointer<UnitNode> parent) {
    return TopologyService::self()->findChild(parent);
}

QSet<QSharedPointer<UnitNode>> TopologyService::findChildByType(int type, QSharedPointer<UnitNode> parent) {
    return TopologyService::self()->findChildByType(type, parent);
}

QSharedPointer<UnitNode> TopologyService::findParentByType(int type, QSharedPointer<UnitNode> parent)
{
    return TopologyService::self()->findParentByType(type, parent);
}

QSet<QSharedPointer<UnitNode> > TopologyService::findeSetAutoOnOffUN(const QSharedPointer<UnitNode> &un)
{
    return TopologyService::self()->findeSetAutoOnOffUN(un);
}


