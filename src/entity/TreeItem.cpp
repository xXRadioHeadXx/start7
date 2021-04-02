#include "TreeItem.h"

#include <QVariant>

TreeItem::TreeItem()
{
}

TreeItem::TreeItem(QSharedPointer<TreeItem> parent)
{
    setTreePparent(parent);
}

TreeItem::~TreeItem()
{
}

QSharedPointer<TreeItem> TreeItem::treeParent()
{
    return treePparentItem;
}

void TreeItem::setTreePparent(QSharedPointer<TreeItem> value)
{
    treePparentItem = value;
}

QList<QSharedPointer<TreeItem> > &TreeItem::listTreeChilds()
{
    return treeChildItems;
}

QSharedPointer<TreeItem> TreeItem::treeChild(int index)
{
    if(index < 0 || treeChildItems.size() <= index)
        return nullptr;

    return treeChildItems.value(index);
}

QSharedPointer<TreeItem>  TreeItem::takeTreeChild(int index)
{
    if(index < 0 || treeChildItems.size() <= index)
        return QSharedPointer<TreeItem>();

    return treeChildItems.takeAt(index);
}

QSharedPointer<TreeItem> TreeItem::takeTreeChild(QSharedPointer<TreeItem> child)
{
    for(int index = 0, n = treeChildItems.size(); index < n; index++) {
        if(treeChildItems.at(index) == child) {
            return treeChildItems.takeAt(index);
        }
    }
    return QSharedPointer<TreeItem>();
}

int TreeItem::treeChildCount() const
{
    return treeChildItems.count();
}

int TreeItem::treeChildIndex() const
{
    if(treePparentItem.isNull())
        return 0;

    for(int index = 0, n = treePparentItem->treeChildItems.size(); index < n; index++) {
        if(treePparentItem->treeChildItems.at(index).data() == (this)) {
            return index;
        }
    }

    return 0;
}

int TreeItem::treeColumnCount() const
{
    return 0;
}

QVariant TreeItem::data(int column) const
{
    Q_UNUSED(column)
    return QVariant();
}

bool TreeItem::insertTreeChildren(int position, QSharedPointer<TreeItem> child)
{
    if (position < 0 || position > treeChildItems.size())
        return false;

    treeChildItems.insert(position, child);
    return true;
}

void TreeItem::addTreeChildren(QSharedPointer<TreeItem> child)
{
    treeChildItems.push_back(child);
}

bool TreeItem::removeTreeChildren(int index)
{
    auto child = takeTreeChild(index);
    if(child.isNull())
        return false;

    return true;
}

bool TreeItem::removeTreeChildren(QSharedPointer<TreeItem> child)
{
    child = takeTreeChild(child);
    if(child.isNull())
        return false;

    return true;
}

void TreeItem::removeAllTreeChildren()
{
    treeChildItems.clear();
}

bool TreeItem::setData(int column, const QVariant &value)
{
    Q_UNUSED(column)
    Q_UNUSED(value)
    return false;
}
