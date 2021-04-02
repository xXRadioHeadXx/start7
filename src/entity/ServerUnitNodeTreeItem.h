#ifndef SERVERUNITNODETREEITEM_H
#define SERVERUNITNODETREEITEM_H

#include <TreeItem.h>

class ServerUnitNodeTreeItem : public TreeItem
{
public:
    explicit ServerUnitNodeTreeItem(QSharedPointer<TreeItem> parent) :
        TreeItem(parent)
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
