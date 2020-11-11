#ifndef TREEMODELUNITNODE_H
#define TREEMODELUNITNODE_H

#include <QAbstractItemModel>
#include <UnitNode.h>
#include "DataBaseManager.h"

class TreeModelUnitNode : public QAbstractItemModel
{
    Q_OBJECT

    SubTypeApp typeApp = SubTypeApp::server;
public:
    explicit TreeModelUnitNode(QObject *parent = nullptr);



    Qt::SortOrder sortOrder = Qt::AscendingOrder;
    UnitNode *rootItemUN;
    QList<UnitNode*> listItemUN;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row,
                      int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int sizeHintForRow(int row) const;

//    QModelIndex findeIndexUNL(UnitNode *un,
//                              UnitNode *parentUN = nullptr);
    QModelIndex findeIndexUNL(UnitNode *tc,
                              UnitNode *parentTC = nullptr);

//    QModelIndex findeIndexUNR(UnitNode *un,
//                              UnitNode *parentUN = nullptr);
    QModelIndex findeIndexUNR(UnitNode *tc,
                              UnitNode *parentTC = nullptr);

//    QModelIndex findeIndexUN(UnitNode *un,
//                             int rl,
//                             UnitNode *parent = nullptr);
    QModelIndex findeIndexUN(UnitNode *tc,
                             int rl,
                             UnitNode *parentTC = nullptr);
    QModelIndex findeIndexUN(UnitNode *tc);


    void createProxySortTree();
    void sortingListItemUN();
    void loadSettings(QString fileName = "rifx.ini");

    void makeEmptyTree(void);
    void getListFromModel(QList<UnitNode *> &list, UnitNode* parentTC = nullptr) const;

    bool deleteUnit(QModelIndex index);

    bool move_up(QModelIndex index);

    bool move_down(QModelIndex index);


    SubTypeApp getTypeApp() const;
    void setTypeApp(const SubTypeApp &value);

signals:
    void selectedUN(QList<UnitNode*> listUN);
    void selectedUN(UnitNode* un);
    void updatedUNs();

public slots:
    void updateUNs();
    void appendNewUNInStructure(UnitNode* un = nullptr);
    void appendNewUNInStructure(QModelIndex &index, UnitNode* un);
    void updateUNStructure(UnitNode* un = nullptr);
    UnitNode *clickedUN(const QModelIndex &index);
//    void moveUNStructure(UnitNode *objPtr,
//                         UnitNode *sourceParent,
//                         int sourceChild,
//                         UnitNode *destinationParent,
//                         int destinationChild);
    //сортировка
//    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);


};

#endif // TREEMODELUNITNODE_H
