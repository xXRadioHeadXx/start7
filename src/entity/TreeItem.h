#ifndef TREEITEM_H
#define TREEITEM_H


#include <QVector>
#include <QList>
#include <QVariant>

template < class T >
class TreeItem
{
public:
    explicit TreeItem();
    explicit TreeItem(T & component, TreeItem * parent = nullptr);
    ~TreeItem();

    T getComponent() const;
    void setComponent(const T &value);

    TreeItem<T> *treeParent();
    void setTreePparent(TreeItem *value);

    TreeItem<T> * treeChild(int index);
    TreeItem<T> * treeChild(const T & component);

    TreeItem<T> * takeTreeChild(int index);
    TreeItem<T> * takeTreeChild(const T & component);

    int treeChildCount() const;

    virtual int treeColumnCount() const;
    virtual QVariant data(int column) const;

    bool insertTreeChildren(int position, const T & component);
    bool insertTreeChildren(int position, TreeItem * child);

    void addTreeChildren(const T & component);
    void addTreeChildren(TreeItem * child);

    bool removeTreeChildren(int index);
    bool removeTreeChildren(const T & component);

    int treeChildIndex() const;

    bool setData(int column, const QVariant &value);

private:
    T component;
    QList<TreeItem *> treeChildItems;
    TreeItem * treePparentItem;
};

#endif // TREEITEM_H
