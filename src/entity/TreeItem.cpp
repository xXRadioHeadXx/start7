#include "TreeItem.h"

#include <QVariant>
#include <list>

TreeItem::TreeItem() /*:
    QObject(nullptr)*/
{
}

TreeItem::TreeItem(QSharedPointer<TreeItem> parent) /*:
    QObject(parent.data())*/
{
    setTreePparent(parent);
}

TreeItem::~TreeItem()
{
}

QSharedPointer<TreeItem> TreeItem::treeParent() const
{
    return treePparentItem;
}

void TreeItem::setTreePparent(QSharedPointer<TreeItem> value)
{
    treePparentItem = value;
}

std::list<QSharedPointer<TreeItem> > TreeItem::listTreeChilds() const
{
    return treeChildItems;
}

void TreeItem::setListTreeChilds(const std::list<QSharedPointer<TreeItem> > &list)
{
    treeChildItems = list;
}

QSharedPointer<TreeItem> TreeItem::treeChild(int index) const
{
    if(index < 0 || treeChildItems.size() <= index)
        return QSharedPointer<TreeItem>(nullptr);

    auto it = treeChildItems.begin();
    it = std::next(it, index);

    return *it;
}

QSharedPointer<TreeItem>  TreeItem::takeTreeChild(int index)
{
    if(index < 0 || treeChildItems.size() <= index)
        return QSharedPointer<TreeItem>();

    auto it = treeChildItems.begin();
    it = std::next(it, index);
    auto result = *it;
    treeChildItems.erase(it);
    return result;

}

QSharedPointer<TreeItem> TreeItem::takeTreeChild(QSharedPointer<TreeItem> child)
{
    for(int index = 0, n = treeChildItems.size(); index < n; index++) {
        auto it = treeChildItems.begin();
        it = std::next(it, index);
        auto result = *it;
        if(result == child) {
            treeChildItems.erase(it);
            return result;
        }
    }
    return QSharedPointer<TreeItem>();
}

int TreeItem::treeChildCount() const
{
    return treeChildItems.size();
}

int TreeItem::treeChildIndex() const
{
    if(treePparentItem.isNull())
        return -1;

    for(int index = 0, n = treePparentItem->treeChildItems.size(); index < n; index++) {
        auto it = treeChildItems.begin();
        it = std::next(it, index);
        auto result = *it;
        if(result.data() == (this)) {
            return index;
        }
    }

    return 0;
}

bool TreeItem::isRootTreeItem() const
{
    return treeParent().isNull();
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
    if (position < 0 || position >= treeChildItems.size())
        return false;

    auto it = treeChildItems.begin();
    it = std::next(it, position);
    treeChildItems.insert(it, child);
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

TreeItem & TreeItem::operator=(const TreeItem & copy)
{
    setTreePparent(copy.treeParent());
    setListTreeChilds(copy.listTreeChilds());
    return *this;
}
