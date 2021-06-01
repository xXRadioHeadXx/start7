#ifndef SERVERUNITNODETREEITEM_H
#define SERVERUNITNODETREEITEM_H

#include "TreeItem.h"
#include "UnitNodeCFG.h"

class ServerUnitNodeTreeItem : public TreeItem, public UnitNodeCFG
{
public:
    explicit ServerUnitNodeTreeItem(QSharedPointer<ServerUnitNodeTreeItem> parent) :
        TreeItem(parent)
      , UnitNodeCFG(static_cast<UnitNodeCFG*>(parent.data()))
    {
    }

    explicit ServerUnitNodeTreeItem() :
        TreeItem()
    {
    }


    ~ServerUnitNodeTreeItem() {
        while(0 < treeChildCount()) {
            removeTreeChildren(0);
        }
    }

    virtual int treeColumnCount() const override;
    virtual QVariant data(int column) const override;

    static bool insertTreeChildrenToParent(int position, QSharedPointer<ServerUnitNodeTreeItem> child, QSharedPointer<ServerUnitNodeTreeItem> parent);
    static void addTreeChildrenToParent(QSharedPointer<ServerUnitNodeTreeItem> child, QSharedPointer<ServerUnitNodeTreeItem> parent);


};

#endif // SERVERUNITNODETREEITEM_H
