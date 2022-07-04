#include "ServerUnitNodeTreeItem.h"

#include <QVariant>
#include "../src/utils/ServerSettingUtils.h"
#include <QSharedPointer>

int ServerUnitNodeTreeItem::treeColumnCount() const
{
    return 1;
}

QVariant ServerUnitNodeTreeItem::data(int column) const
{
    Q_UNUSED(column)
    return QVariant();
}

bool ServerUnitNodeTreeItem::insertTreeChildrenToParent(int position, QSharedPointer<ServerUnitNodeTreeItem> child, QSharedPointer<ServerUnitNodeTreeItem> parent)
{
//    for(int i = 0, n = ServerSettingUtils::getListTreeUnitNodes().size(); i < n; i++) {
//        qSharedPointerCast<ServerUnitNodeTreeItem>(ServerSettingUtils::getListTreeUnitNodes().at(i));
//    }
//    for(auto un : ServerSettingUtils::getListTreeUnitNodes()) {
//        un.data()->removeTreeChildren(child);
//        if(qStatic_Cast<ServerUnitNodeTreeItem>(un.data())->removeTreeChildren(child)) {
//            break;
//        }
//    }
    child->setTreePparent(parent);
    return parent->insertTreeChildren(position, child);
}

void ServerUnitNodeTreeItem::addTreeChildrenToParent(QSharedPointer<ServerUnitNodeTreeItem> child, QSharedPointer<ServerUnitNodeTreeItem> parent)
{
//    for(auto un : ServerSettingUtils::getListTreeUnitNodes()) {
//        if(qSharedPointerCast<ServerUnitNodeTreeItem>(un)->removeTreeChildren(child)) {
//            break;
//        }
//    }
    child->setTreePparent(parent);
    parent->addTreeChildren(child);
}
