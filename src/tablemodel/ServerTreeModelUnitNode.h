#ifndef SERVERTREEMODELUNITNODE_H
#define SERVERTREEMODELUNITNODE_H

#include <QAbstractItemModel>
#include <UnitNode.h>
#include <QCoreApplication>

class UnitNode;
class DataBaseManager;
class ServerTreeModelUnitNode : public QAbstractItemModel
{
    Q_OBJECT

    SubTypeApp typeApp = SubTypeApp::server;
public:
    explicit ServerTreeModelUnitNode(QObject *parent = nullptr);



    Qt::SortOrder sortOrder = Qt::AscendingOrder;
    QSharedPointer<UnitNode> rootItemUN;
    QList<QSharedPointer<UnitNode> > listItemUN;

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

    QSharedPointer<UnitNode> getTreeUnitNodes(UnitNode* target) const;

    int sizeHintForRow(int row) const;

//    QModelIndex findeIndexUNL(UnitNode*un,
//                              UnitNode*parentUN = nullptr);
    QModelIndex findeIndexUNL(UnitNode*tc,
                              UnitNode*parentTC = nullptr);

//    QModelIndex findeIndexUNR(UnitNode*un,
//                              UnitNode*parentUN = nullptr);
    QModelIndex findeIndexUNR(UnitNode*tc,
                              UnitNode*parentTC = nullptr);

//    QModelIndex findeIndexUN(UnitNode*un,
//                             int rl,
//                             UnitNode*parent = nullptr);
    QModelIndex findeIndexUN(UnitNode*tc,
                             int rl,
                             UnitNode*parentTC = nullptr);
    QModelIndex findeIndexUN(UnitNode*tc);


    void createProxySortTree();
    void sortingListItemUN();
    void loadSettings(QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

//    void makeEmptyTree(void);
//    void getListFromModel(QList<UnitNode*> &list, UnitNode* parentTC = nullptr) const;

//    bool deleteUnit(QModelIndex index);

//    bool moveUNUp(QModelIndex index);

//    bool moveUNDown(QModelIndex index);


    SubTypeApp getTypeApp() const;
    void setTypeApp(const SubTypeApp &value);

signals:
    void selectedUN(QList<QSharedPointer<UnitNode> > listUN);
    void selectedUN(QSharedPointer<UnitNode> un);
    void updatedUNs();

public slots:
    void updateUNs();
//    void appendNewUNInStructure(UnitNode* un = nullptr);
//    void appendNewUNInStructure(QModelIndex &index, UnitNode* un);
//    void updateUNStructure(UnitNode* un = nullptr);
    QSharedPointer<UnitNode> clickedUN(const QModelIndex &index);
//    void moveUNStructure(UnitNode*objPtr,
//                         UnitNode*sourceParent,
//                         int sourceChild,
//                         UnitNode*destinationParent,
//                         int destinationChild);
    //сортировка
//    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);


};

#endif // SERVERTREEMODELUNITNODE_H
