#include <TreeModelUnitNode.h>
#include <SettingUtils.h>
#include <SignalSlotCommutator.h>

TreeModelUnitNode::TreeModelUnitNode(QObject *parent) :
QAbstractItemModel(parent),
sortOrder(Qt::AscendingOrder)
{
    rootItemUN = new UnitNode;
    rootItemUN->setLevel(0);

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(updUN()),
            this,
            SLOT(updateUNs()));
}

int TreeModelUnitNode::columnCount(const QModelIndex &parent) const
 {
     if (parent.isValid())
//         return static_cast<UnitNode*>(parent.internalPointer())->columnCount();
         return static_cast<UnitNode*>(parent.internalPointer())->columnCount();
     else
         return rootItemUN->columnCount();
//         return rootItemSortUN->columnCount();
 }

 QVariant TreeModelUnitNode::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     UnitNode *item = static_cast<UnitNode*>(index.internalPointer());

//     if(role == Qt::BackgroundRole)
//     {
//         return QVariant(QColor(Qt::lightGray));
//     }

     if(role == Qt::DecorationRole &&
        rootItemUN != item &&
        0 == index.column())
     {
         QPixmap pxm;
         switch(index.column())
         {
         case 0:
         {
             pxm = item->getPxm();
             break;
         }
         default:
         {
             break;
         }
         }
//         if(pxm.isNull())
//             return QVariant();
         return QVariant(pxm);
     }

     if(role == Qt::DisplayRole)
         return item->data(index.column());

     return QVariant();
 }

bool TreeModelUnitNode::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || value.toString().isEmpty())
        return false;

    if(Qt::EditRole == role)
    {
        UnitNode *item = static_cast<UnitNode*>(index.internalPointer());
        item->setName(value.toString());
        return true;
    }
    return false;
}

 Qt::ItemFlags TreeModelUnitNode::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return 0;

//     if(1 == index.column())
//     {
//         return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
//     }
//     else
     {
         return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
     }
 }

 QVariant TreeModelUnitNode::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
         return rootItemUN->data(section);

     return QVariant();
 }

 QModelIndex TreeModelUnitNode::index(int row, int column, const QModelIndex &parent)
             const
 {
     if (!hasIndex(row, column, parent))
         return QModelIndex();

//     UnitNode *parentItem;
     UnitNode *parentItem;

     if (!parent.isValid())
         parentItem = rootItemUN;
     else
         parentItem = static_cast<UnitNode*>(parent.internalPointer());

     UnitNode *childItem = parentItem->treeChild(row);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();
 }

 QModelIndex TreeModelUnitNode::parent(const QModelIndex &index) const
 {
     if (!index.isValid())
         return QModelIndex();

     UnitNode *childItem = static_cast<UnitNode*>(index.internalPointer());
     UnitNode *parentItem = childItem->getTreeParentUN();

     if (parentItem == rootItemUN)
         return QModelIndex();

     return createIndex(parentItem->treeRow(), 0, parentItem);
 }

 int TreeModelUnitNode::rowCount(const QModelIndex &parent) const
 {
     UnitNode *parentItem;
     if (parent.column() > 0)
         return 0;

     if (!parent.isValid())
         parentItem = rootItemUN;
     else
         parentItem = static_cast<UnitNode*>(parent.internalPointer());

     return parentItem->treeChildCount();
 }

 void TreeModelUnitNode::appendNewUNInStructure(QModelIndex &index, UnitNode* un)
 {
//Kak tebe takoe Ilon Mask
     qDebug()<<"appendNewUNInStructure";
    this->beginInsertRows(index.parent(),index.row(),index.row());
     UnitNode *parent= static_cast<UnitNode*>(index.internalPointer());

     parent->addTreeChild(un);
     parent->addChild(un);

     this->endInsertRows();


  //   parent->m_child_list.append(item);

 //    item->m_parent=parent;


//     this->beginResetModel();
//     this->createProxySortTree();//

//     this->endResetModel();
     return;

//     this->beginInsertRows(this->findeIndexUNL(un->unTreeParent),
//                           un->unTreeParent->listChilde.indexOf(un),
//                           un->unTreeParent->listChilde.indexOf(un));
//     this->endInsertRows();
 }

 void TreeModelUnitNode::updateUNStructure(UnitNode* un)
 {
     this->beginResetModel();
     this->createProxySortTree();
     this->endResetModel();
     return;

//     emit this->dataChanged(this->findeIndexUNL(un),
//                            this->findeIndexUNR(un));//3
 }

 UnitNode * TreeModelUnitNode::clickedUN(const QModelIndex &index)
 {
     if (!index.isValid())
         return nullptr;

     UnitNode *item = static_cast<UnitNode*>(index.internalPointer());
     if(item)
     {
         emit selectedUN(item);
         return item;
     }
     return nullptr;
 }

//QModelIndex TreeModelUnitNode::findeIndexUNL(UnitNode *un,
//                                             UnitNode *parentUN)
//{
//    return this->findeIndexUN(un, 0, parentUN);
//}

QModelIndex TreeModelUnitNode::findeIndexUNL(UnitNode *tc,
                                             UnitNode *parentTC)
{
    return this->findeIndexUN(tc, 0, parentTC);
}

//QModelIndex TreeModelUnitNode::findeIndexUNR(UnitNode *un,
//                                             UnitNode *parentUN)
//{
//    return this->findeIndexUN(un, 4, parentUN);///2
//}

QModelIndex TreeModelUnitNode::findeIndexUNR(UnitNode *tc,
                                             UnitNode *parentTC)
{
    return this->findeIndexUN(tc, 4, parentTC);///2
}


//QModelIndex TreeModelUnitNode::findeIndexUN(UnitNode *un,
//                                            int lr,
//                                            UnitNode *parentUN)
//{
//     QModelIndex index;

//     if (0 == parentUN)
//     {
//         parentUN = rootItemUN;
//         if(parentUN == un)
//         {
//             qDebug() << "findeIndexUN false 1";
//             return index;
//         }
//     }

//     for(int i(0), n(un->childCount()); i < n; i++)
//     {
//         if (parentUN->child(i) == un)
//         {
//             return createIndex(i, lr, un);
//         }
//         else
//         {
//             index = this->findeIndexUN(un,
//                                        lr,
//                                        parentUN);///1
//             if(index.isValid())
//             {
//                 qDebug() << "findeIndexUN " << index;
//                 return index;
//             }
//         }

//     }
//     qDebug() << "findeIndexUN false 2";
//     return index;
//}

QModelIndex TreeModelUnitNode::findeIndexUN(UnitNode *tc)
{
    return findeIndexUN(tc, 0);
}

QModelIndex TreeModelUnitNode::findeIndexUN(UnitNode *tc,
                                            int lr,
                                            UnitNode *parentTC)
{
     QModelIndex index;

     if (0 == parentTC)
     {
         parentTC = rootItemUN;
         if(parentTC == tc)
         {
             qDebug() << "findeIndexUN false 1";
             return index;
         }
     }

     for(int i(0), n(tc->treeChildCount()); i < n; i++)
     {
         if (parentTC->treeChild(i) == tc)
         {
             return createIndex(i, lr, tc);
         }
         else
         {
             index = this->findeIndexUN(tc,
                                        lr,
                                        parentTC);///1
             if(index.isValid())
             {
                 qDebug() << "findeIndexUN " << index;
                 return index;
             }
         }

     }
     qDebug() << "findeIndexUN false 2";
     return index;
}


//void TreeModelUnitNode::moveUNStructure(UnitNode *objPtr,
//                                        UnitNode *sourceParent,
//                                        int sourceChild,
//                                        UnitNode *destinationParent,
//                                        int destinationChild)
//{
//    this->beginResetModel();
//    this->createProxySortTree();
//    this->endResetModel();
//    return;
//}

//сортировка
//void TreeModelUnitNode::sort(int column, Qt::SortOrder order)
//{

//}

void TreeModelUnitNode::updateUNs()
{
    emit this->dataChanged(QModelIndex(), QModelIndex());
    SignalSlotCommutator::getInstance()->emitUpdDataTreeUN();
//    emit this->updatedUNs();
    return;
}

void TreeModelUnitNode::loadSettings(QString fileName)
{  
    listItemUN = SettingUtils::loadTreeUnitNodes(rootItemUN, fileName);
}

void TreeModelUnitNode::createProxySortTree()
{

//    this->beginResetModel();
    loadSettings();

    sortingListItemUN();

//    //добавление новых в sortProxyListItemTC -->
//    for(int i(0), n(listItemUN.size()); i < n; i++)
//    {
//        bool appendKey(true);
//        for(int j(0); j < sortProxyListItemTC.size(); j++)
//        {
//            if(listItemUN.at(i) == sortProxyListItemTC.at(j)->m_un)
//            {
//                appendKey = false;
//                break;
//            }
//        }

//        if(appendKey)
//        {
//            UnitNode *newTC(new UnitNode);
//            newTC->insertUN(0, listItemUN.at(i));

//            sortProxyListItemTC.append(newTC);
//        }
//    }
//    //добавление новых в sortProxyListItemTC <--

//    //добавление новых в sortProxyListParentItemTC -->
//    for(int i(0), n(sortProxyListItemTC.size()); i < n; i++)
//    {
//        bool appendKey(true);
//        for(int j(0); j < sortProxyListParentItemTC.size(); j++)
//        {
//            if(sortProxyListParentItemTC.at(j)->numArea == sortProxyListItemTC.at(i)->numArea)
//            {
//                appendKey = false;
//                break;
//            }
//        }
//        if(appendKey)
//        {
//            UnitNode *newTC(new UnitNode);
//            newTC->insertUN(sortProxyListItemTC.at(i)->numArea, 0);
//            newTC->treeParent = this->rootItemSortUN;
//            this->rootItemSortUN->appendChild(newTC);

//            sortProxyListParentItemTC.append(newTC);
//        }
//    }
//    //добавление новых в sortProxyListParentItemTC <--

//    //удаление из sortProxyListParentItemTC -->
//    for(int i(0); i < sortProxyListParentItemTC.size(); i++)
//    {
//        bool removeKey(true);
//        for(int j(0); j < sortProxyListItemTC.size(); j++)
//        {
//            if(sortProxyListParentItemTC.at(i)->numArea == sortProxyListItemTC.at(j)->numArea)
//            {
//                removeKey = false;
//                break;
//            }
//        }
//        if(removeKey)
//        {
//            sortProxyListParentItemTC.at(i)->treeParent = nullptr;
//            sortProxyListParentItemTC.at(i)->listChilde.clear();
//            sortProxyListParentItemTC.removeAt(i);
//        }
//    }
//    //удаление из sortProxyListParentItemTC <--
//    //добавление sortProxyListItemTC к sortProxyListParentItemTC -->
//    for(int i(0); i < sortProxyListParentItemTC.size(); i++)
//    {
//        for(int j(0); j < sortProxyListItemTC.size(); j++)
//        {
//            if(sortProxyListParentItemTC.at(i)->numArea == sortProxyListItemTC.at(j)->numArea)
//            {
//                sortProxyListItemTC.at(j)->treeParent = sortProxyListParentItemTC.at(i);
//                sortProxyListParentItemTC.at(i)->appendChild(sortProxyListItemTC.at(j));
//            }
//        }
//    }
//    //добавление sortProxyListItemTC к sortProxyListParentItemTC <--
////    this->endResetModel();
}

void TreeModelUnitNode::sortingListItemUN()
{
    //сортировка по имени
    for(int i(0), n(listItemUN.size()); i < n - 1; i++)
    {
        for(int j(0); j < n - i - 1; j++)
        {
            if(Qt::AscendingOrder == sortOrder)
            {
                if(listItemUN[j]->getName().compare(listItemUN[j + 1]->getName()) > 0)
                {
                    UnitNode *temp = listItemUN[j]; //change for elements
                    listItemUN[j] = listItemUN[j + 1];
                    listItemUN[j + 1] = temp;
                }
            }
            if(Qt::DescendingOrder == sortOrder)
            {
                if(listItemUN[j]->getName().compare(listItemUN[j + 1]->getName()) < 0)
                {
                    UnitNode *temp = listItemUN[j]; //change for elements
                    listItemUN[j] = listItemUN[j + 1];
                    listItemUN[j + 1] = temp;
                }
            }
        }
    }
    //сортировка по номерам устр
//    for(int i(0), n(listItemUN.size()); i < n - 1; i++)
//    {
//        for(int j(0); j < n - i - 1; j++)
//        {
//            if(listItemUN[j]->_numArea() == listItemUN[j + 1]->_numArea())
//            {
//                if(Qt::AscendingOrder == sortOrder)
//                {
//                    if(listItemUN[j]->_numNode() > listItemUN[j + 1]->_numNode())
//                    {
//                        UnitNode *temp = listItemUN[j]; //change for elements
//                        listItemUN[j] = listItemUN[j + 1];
//                        listItemUN[j + 1] = temp;
//                    }
//                }
//                if(Qt::DescendingOrder == sortOrder)
//                {
//                    if(listItemUN[j]->_numNode() < listItemUN[j + 1]->_numNode())
//                    {
//                        UnitNode *temp = listItemUN[j]; //change for elements
//                        listItemUN[j] = listItemUN[j + 1];
//                        listItemUN[j + 1] = temp;
//                    }
//                }
//            }

//        }
//    }
}
