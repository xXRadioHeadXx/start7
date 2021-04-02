#include "TreeItem.h"

template<class T>
TreeItem<T>::TreeItem()
{
    setTreePparent(nullptr);
}

template<class T>
TreeItem<T>::TreeItem(T &data, TreeItem * parent)
{
    setComponent(data);
    setTreePparent(parent);
}

template<class T>
Q_OUTOFLINE_TEMPLATE  TreeItem<T>::~TreeItem()
{
    qDeleteAll(treeChildItems);
}

template<class T>
T TreeItem<T>::getComponent() const
{
    return getComponent;
}

template<class T>
void TreeItem<T>::setComponent(const T &value)
{
    this->component = value;
}

template<class T>
TreeItem<T> *TreeItem<T>::treeParent()
{
    return treePparentItem;
}

template<class T>
void TreeItem<T>::setTreePparent(TreeItem *value)
{
    treePparentItem = value;
}

template<class T>
TreeItem<T> * TreeItem<T>::treeChild(int index)
{
    if(index < 0 || treeChildItems.size() <= index)
        return nullptr;

    return treeChildItems.value(index);
}

template<class T>
TreeItem<T> * TreeItem<T>::treeChild(const T & component)
{
    for(auto child : treeChildItems) {
        if(child->getComponent() == component) {
            return child;
        }
    }
    return nullptr;
}

template<class T>
TreeItem<T> * TreeItem<T>::takeTreeChild(int index)
{
    if(index < 0 || treeChildItems.size() <= index)
        return nullptr;

    return treeChildItems.takeAt(index);
}

template<class T>
TreeItem<T> * TreeItem<T>::takeTreeChild(const T &component)
{
    for(int index = 0, n = treeChildItems.size(); index < n; index++) {
        if(treeChildItems.at(index)->getComponent() == component) {
            return treeChildItems.takeAt(index);
        }
    }
    return nullptr;
}

template<class T>
int TreeItem<T>::treeChildCount() const
{
    return treeChildItems.count();
}

template<class T>
int TreeItem<T>::treeChildIndex() const
{
    if (treePparentItem)
        return treePparentItem->treeChildItems.indexOf(const_cast<TreeItem *>(this));
    return 0;
}

template<class T>
int TreeItem<T>::treeColumnCount() const
{
    return 0;
}

template<class T>
QVariant TreeItem<T>::data(int column) const
{
    Q_UNUSED(column)
    return QVariant();
}

template<class T>
bool TreeItem<T>::insertTreeChildren(int position, const T & component)
{
    if (position < 0 || position > treeChildItems.size())
        return false;

    return insertTreeChildren(position, new TreeItem(component, this));
}

template<class T>
bool TreeItem<T>::insertTreeChildren(int position, TreeItem *child)
{
    if (position < 0 || position > treeChildItems.size())
        return false;

    child,setTreePparent(this);
    treeChildItems.insert(position, child);
    return true;
}

template<class T>
void TreeItem<T>::addTreeChildren(const T &component)
{
    addTreeChildren(new TreeItem(component, this));
}

template<class T>
void TreeItem<T>::addTreeChildren(TreeItem *child)
{
    child,setTreePparent(this);
    treeChildItems.push_back(child);
}

template<class T>
bool TreeItem<T>::removeTreeChildren(int index)
{
    auto child = takeTreeChild(index);
    if(nullptr == child)
        return false;

    return true;
}

template<class T>
bool TreeItem<T>::removeTreeChildren(const T &component)
{
    auto child = takeTreeChild(component);
    if(nullptr == child)
        return false;

    return true;

}

template<class T>
bool TreeItem<T>::setData(int column, const QVariant &value)
{
    return false;
}
