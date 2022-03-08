#ifndef UNITNODETREEITEM_H
#define UNITNODETREEITEM_H

#include "TreeItem.h"
#include "UnitNodeCFG.h"

class UnitNodeTreeItem : public TreeItem, public UnitNodeCFG
{
public:
    explicit UnitNodeTreeItem(QSharedPointer<UnitNodeTreeItem> parent) :
        TreeItem(parent)
      , UnitNodeCFG(static_cast<UnitNodeCFG*>(parent.data()))
    {
    }

    explicit UnitNodeTreeItem() :
        TreeItem()
    {
    }


    ~UnitNodeTreeItem() {
        while(0 < treeChildCount()) {
            removeTreeChildren(0);
        }
    }

    virtual int treeColumnCount() const override;
    virtual QVariant data(int column) const override;

};

#endif // UNITNODETREEITEM_H
