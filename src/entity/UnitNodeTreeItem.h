#ifndef UNITNODETREEITEM_H
#define UNITNODETREEITEM_H

#include <TreeItem.h>
#include <UnitNode.h>

typedef QSharedPointer<UnitNode> RefClassUN;
class UnitNodeTreeItem : public virtual TreeItem<RefClassUN>
{
public:
    UnitNodeTreeItem(RefClassUN component, TreeItem<RefClassUN> * parent = nullptr) : TreeItem<RefClassUN>(component, parent) {
        setComponent(component);
        setTreePparent(parent);
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
