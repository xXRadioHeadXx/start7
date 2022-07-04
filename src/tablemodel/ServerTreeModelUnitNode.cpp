#include "ServerTreeModelUnitNode.h"
#include "../src/utils/ServerSettingUtils.h"
#include "../src/utils/SignalSlotCommutator.h"
#include <QPixmap>
#include "../src/utils/TopologyService.h"

SubTypeApp ServerTreeModelUnitNode::getTypeApp() const
{
    return typeApp;
}

void ServerTreeModelUnitNode::setTypeApp(const SubTypeApp &value)
{
    typeApp = value;
}

ServerTreeModelUnitNode::ServerTreeModelUnitNode(QObject *parent) :
    QAbstractItemModel(parent),
    sortOrder(Qt::AscendingOrder),
    rootItemUN(TopologyService::getTreeRootUnitNodes())
{
//    rootItemUN = QSharedPointer<UnitNode>::create();
    rootItemUN->setLevel(0); //rootItemUN->treeParent().isNull();


    connect(&SignalSlotCommutator::instance(),
            SIGNAL(updUN()),
            this,
            SLOT(updateUNs()));
}

ServerTreeModelUnitNode::~ServerTreeModelUnitNode()
{

}

int ServerTreeModelUnitNode::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QSharedPointer<UnitNode> ServerTreeModelUnitNode::getTreeUnitNodes(UnitNode*target) const
{
    for(QSharedPointer<UnitNode> un : listItemUN) {
        if(target == un.data()) {
            return un;
        }
    }
    return QSharedPointer<UnitNode>();
}


int ServerTreeModelUnitNode::sizeHintForRow(int /*row*/) const
{
    return 12;
}

 QVariant ServerTreeModelUnitNode::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     UnitNode * item = static_cast<UnitNode*>(index.internalPointer());

//     if(role == Qt::BackgroundRole)
//     {
//         return QVariant(QColor(Qt::lightGray));
//     }

     if(role == Qt::DecorationRole &&
        rootItemUN != item)
     {
         QPixmap pxm;
         switch(index.column())
         {
//         case 0:
//         {

//             break;
//         }
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
//         if(!pxm.isNull())
//             pxm = pxm.scaled(20,20);

         return QVariant(pxm);
     }

     if(role == Qt::DisplayRole)
         return item->dataTreeColumn(index.column());

     return QVariant();
 }

bool ServerTreeModelUnitNode::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || value.toString().isEmpty())
        return false;

    if(Qt::EditRole == role)
    {
        UnitNode*item = static_cast<UnitNode*>(index.internalPointer());
        item->setName(value.toString());
        return true;
    }
    return false;
}

 Qt::ItemFlags ServerTreeModelUnitNode::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return Qt::NoItemFlags;

     if (typeApp==SubTypeApp::configurator) //если конфигуратор
     {
         auto un = static_cast<UnitNode*>(index.internalPointer());

         if(TypeUnitNodeEnum::SYSTEM != un->getType()){
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
         } else {
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
         }
     }

     return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
 }

 QVariant ServerTreeModelUnitNode::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
         switch(section) {
         case 0:
             return "";
         case 1:
             return tr("Имя");
         default:
             return QVariant();
         }
     }

     return QVariant();
 }

 QModelIndex ServerTreeModelUnitNode::index(int row, int column, const QModelIndex &parent)
             const
 {
     if (!hasIndex(row, column, parent))
         return QModelIndex();

//     UnitNode*parentItem;
     QSharedPointer<UnitNode> parentItem;

     if (!parent.isValid())
         parentItem = rootItemUN;
     else
         parentItem = getTreeUnitNodes(static_cast<UnitNode*>(parent.internalPointer()));

     QSharedPointer<UnitNode> childItem = qSharedPointerCast<UnitNode>(parentItem->treeChild(row));
     if (childItem)
         return createIndex(row, column, childItem.data());
     else
         return QModelIndex();
 }

 QModelIndex ServerTreeModelUnitNode::parent(const QModelIndex &index) const
 {
     if (!index.isValid())
         return QModelIndex();

     QSharedPointer<UnitNode> childItem = getTreeUnitNodes(static_cast<UnitNode*>(index.internalPointer()));
     QSharedPointer<UnitNode> parentItem = qSharedPointerCast<UnitNode>(childItem->treeParent());

     if (parentItem == rootItemUN)
         return QModelIndex();

     return createIndex(parentItem->treeChildIndex(), 0, parentItem.data());
 }

 int ServerTreeModelUnitNode::rowCount(const QModelIndex &parent) const
 {
     QSharedPointer<UnitNode> parentItem;
     if (parent.column() > 1)
         return 0;

     if (!parent.isValid())
         parentItem = rootItemUN;
     else
         parentItem = getTreeUnitNodes(static_cast<UnitNode*>(parent.internalPointer()));

     return parentItem->treeChildCount();
 }

// void TreeModelUnitNode::appendNewUNInStructure(QModelIndex &index, UnitNode* un)
// {
//     //qDebug() << "TreeModelUnitNode::appendNewUNInStructure(" << index << ", " << un << ") -->";
//     UnitNode*parent = static_cast<UnitNode*>(index.internalPointer());

//     this->beginInsertRows(index.parent(), index.row(), index.row());
//     parent->addTreeChild(un);
//     parent->addChild(un);
//     this->endInsertRows();

//     //qDebug() << "TreeModelUnitNode::appendNewUNInStructure() <--";

//     return;
// }

//  void TreeModelUnitNode::appendNewUNInStructure(UnitNode* /*un*/)
//  {
//      this->beginResetModel();
//      this->createProxySortTree();//
//      this->endResetModel();
//      return;

// //     this->beginInsertRows(this->findeIndexUNL(un->unTreeParent),
// //                           un->unTreeParent->listChilde.indexOf(un),
// //                           un->unTreeParent->listChilde.indexOf(un));
// //     this->endInsertRows();
//  }

// void TreeModelUnitNode::updateUNStructure(UnitNode* /*un*/)
// {
//     this->beginResetModel();
//     this->createProxySortTree();
//     this->endResetModel();
//     return;

////     emit this->dataChanged(this->findeIndexUNL(un),
////                            this->findeIndexUNR(un));//3
// }

 QSharedPointer<UnitNode> ServerTreeModelUnitNode::clickedUN(const QModelIndex &index)
 {
     if (!index.isValid())
         return nullptr;

     QSharedPointer<UnitNode> item = getTreeUnitNodes(static_cast<UnitNode*>(index.internalPointer()));
     if(item)
     {
         emit selectedUN(item);
         return item;
     }
     return QSharedPointer<UnitNode>();
 }

QModelIndex ServerTreeModelUnitNode::findeIndexUNL(UnitNode*tc,
                                             UnitNode*parentTC)
{
    return this->findeIndexUN(tc, 0, parentTC);
}

QModelIndex ServerTreeModelUnitNode::findeIndexUNR(UnitNode*tc,
                                             UnitNode*parentTC)
{
    return this->findeIndexUN(tc, 4, parentTC);///2
}

QModelIndex ServerTreeModelUnitNode::findeIndexUN(UnitNode*tc)
{
    return findeIndexUN(tc, 0);
}

QModelIndex ServerTreeModelUnitNode::findeIndexUN(UnitNode*tc,
                                            int lr,
                                            UnitNode*parentTC)
{
     QModelIndex index;

     if (0 == parentTC)
     {
         parentTC = rootItemUN.data();
         if(parentTC == tc)
         {
//             //qDebug() << "findeIndexUN false 1";
             return index;
         }
     }

     for(int i(0), n(parentTC->treeChildCount()); i < n; i++)
     {
         if (parentTC->treeChild(i) == tc)
         {
             return createIndex(i, lr, tc);
         }
         else
         {
             index = this->findeIndexUN(tc,
                                        lr,
                                        static_cast<UnitNode *>(parentTC->treeChild(i).data()));///1
             if(index.isValid())
             {
           //      //qDebug() << "findeIndexUN " << index;
                 return index;
             }
         }

     }
  //   //qDebug() << "findeIndexUN false 2";
     return index;
}


//void TreeModelUnitNode::moveUNStructure(UnitNode*objPtr,
//                                        UnitNode*sourceParent,
//                                        int sourceChild,
//                                        UnitNode*destinationParent,
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

void ServerTreeModelUnitNode::updateUNs()
{
    emit this->dataChanged(QModelIndex(), QModelIndex());
    SignalSlotCommutator::emitUpdDataTreeUN();
//    emit this->updatedUNs();
    return;
}

void ServerTreeModelUnitNode::loadSettings(QString fileName)
{
    Q_UNUSED(fileName)
    this->beginResetModel();
//    listItemUN = ServerSettingUtils::loadTreeUnitNodes(rootItemUN, fileName);
//    TopologyService::loadTreeUnitNodes();
    listItemUN = TopologyService::getListTreeUnitNodes();
    this->endResetModel();
}

//void TreeModelUnitNode::makeEmptyTree()
//{
//    this->beginResetModel();
//    listItemUN = SettingUtils::loadEmptyTree(rootItemUN);
//    this->endResetModel();
//}

//void TreeModelUnitNode::getListFromModel(QList<UnitNode*> &list, UnitNode* parentTC) const
//{
//    if(nullptr == parentTC) {
//        list.clear();
//        parentTC = rootItemUN.data();
//    }

//    for(int i(0), n(parentTC->treeChildCount()); i < n; i++)
//    {
//        auto un = parentTC->treeChild(i).data();
//        un->setMetaNames(QString("Obj_%1").arg(list.count()));
//        list.append(un);
//        if(0 < un->treeChildCount())
//            getListFromModel(list, un);
//    }
//}

//bool TreeModelUnitNode::deleteUnit(QModelIndex index)
//{
//    //qDebug()<<"TreeModelUnitNode::deleteUnit(" << index << ") -->";

//    if(this->parent(index).isValid()) {
//        this->beginRemoveRows(index.parent(),index.row(),index.row());
//        UnitNode*parent = static_cast<UnitNode*>(this->parent(index).internalPointer());
//        parent->deleteChild(index.row());
//        //emit dataChanged(index,index);
//        this->endRemoveRows();
//        emit dataChanged(index,index);
//        //qDebug()<<"TreeModelUnitNode::deleteUnit() <-- true";
//        return true;
//    } else
//        //qDebug()<<"TreeModelUnitNode::deleteUnit() <-- false";

//    return false;
//}

//bool TreeModelUnitNode::moveUNUp(QModelIndex index)
//{
//    if(index.row()>0) {
//        UnitNode* un = static_cast<UnitNode*>(index.internalPointer());
//        UnitNode* parent = un->getTreeParentUN();
//        QModelIndex parent_ind = this->parent(index);

//        this->beginMoveRows(parent_ind,
//                            index.row(),
//                            index.row(),
//                            parent_ind,
//                            (index.row() - 1));

//      //  this->moveRow(parent_ind,index.row(),parent_ind,(index.row()-1));
//        parent->moveTreeChildUNUp(un);

//        this->endMoveRows();
//        return true;
//    }
//    return false;
// //  this->beginMoveRows()
// //   //    parent->move_up(index.row());
// //   this->endResetModel();
//}

//bool TreeModelUnitNode::moveUNDown(QModelIndex index)
//{
//    if(index.row() < (this->rowCount(this->parent(index)) - 1)) {
//        UnitNode* un = static_cast<UnitNode*>(index.internalPointer());
//        UnitNode* parent = un->getTreeParentUN();
//        QModelIndex parent_ind = this->parent(index);

//        this->beginMoveRows(parent_ind,
//                            index.row(),
//                            index.row(),
//                            parent_ind,
//                            (index.row() + 2));

//      //  this->moveRow(parent,index.row(),parent,(index.row()-1));
//        parent->moveTreeChildUNDown(un);

//        this->endMoveRows();
//        return true;
//    }
//    return false;
//}

void ServerTreeModelUnitNode::createProxySortTree()
{

//    this->beginResetModel();
    loadSettings();

    sortingListItemUN();

}

void ServerTreeModelUnitNode::sortingListItemUN()
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
                    listItemUN.swap(j, j + 1);
//                    UnitNode*temp = listItemUN[j]; //change for elements
//                    listItemUN[j] = listItemUN[j + 1];
//                    listItemUN[j + 1] = temp;
                }
            }
            if(Qt::DescendingOrder == sortOrder)
            {
                if(listItemUN[j]->getName().compare(listItemUN[j + 1]->getName()) < 0)
                {
                    listItemUN.swap(j, j + 1);
//                    UnitNode*temp = listItemUN[j]; //change for elements
//                    listItemUN[j] = listItemUN[j + 1];
//                    listItemUN[j + 1] = temp;
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
//                        UnitNode*temp = listItemUN[j]; //change for elements
//                        listItemUN[j] = listItemUN[j + 1];
//                        listItemUN[j + 1] = temp;
//                    }
//                }
//                if(Qt::DescendingOrder == sortOrder)
//                {
//                    if(listItemUN[j]->_numNode() < listItemUN[j + 1]->_numNode())
//                    {
//                        UnitNode*temp = listItemUN[j]; //change for elements
//                        listItemUN[j] = listItemUN[j + 1];
//                        listItemUN[j + 1] = temp;
//                    }
//                }
//            }

//        }
//    }
}
