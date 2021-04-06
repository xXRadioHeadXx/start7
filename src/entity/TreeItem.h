#ifndef TREEITEM_H
#define TREEITEM_H


#include <QSharedPointer>

class TreeItem //: public virtual QObject
{
private:
    QList<QSharedPointer<TreeItem> > treeChildItems;
    QSharedPointer<TreeItem> treePparentItem;

public:
    explicit TreeItem();
    explicit TreeItem(QSharedPointer<TreeItem> parent);
    virtual ~TreeItem();

    QSharedPointer<TreeItem> treeParent() const;
    void setTreePparent(QSharedPointer<TreeItem>value);

    QList<QSharedPointer<TreeItem> > listTreeChilds() const;
    void setListTreeChilds(const QList<QSharedPointer<TreeItem> > & list);

    QSharedPointer<TreeItem> treeChild(int index) const;

    QSharedPointer<TreeItem> takeTreeChild(int index);
    QSharedPointer<TreeItem> takeTreeChild(QSharedPointer<TreeItem> child);

    int treeChildCount() const;

    virtual int treeColumnCount() const;
    virtual QVariant data(int column) const;

    bool insertTreeChildren(int position, QSharedPointer<TreeItem> child);

    void addTreeChildren(QSharedPointer<TreeItem> child);


    bool removeTreeChildren(int index);
    bool removeTreeChildren(QSharedPointer<TreeItem> child);
    void removeAllTreeChildren();


    int treeChildIndex() const;
    bool isRootTreeItem() const;


    bool setData(int column, const QVariant &value);

    virtual TreeItem & operator=(const TreeItem& copy);

};

#endif // TREEITEM_H
