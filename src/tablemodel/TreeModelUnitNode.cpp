#include <TreeModelUnitNode.h>
#include <SettingUtils.h>
#include <SignalSlotCommutator.h>
//#include <control.h>

SubTypeApp TreeModelUnitNode::getTypeApp() const
{
    return typeApp;
}

void TreeModelUnitNode::setTypeApp(const SubTypeApp &value)
{
    typeApp = value;
}

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

int TreeModelUnitNode::sizeHintForRow(int /*row*/) const
{
    return 12;
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
             (
        0 == index.column()||
        1 == index.column()||
        2 == index.column()
             ))
     {

         QPixmap pxm;
         switch(index.column())
         {
         case 0:
         {
             UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
             pxm = item->getPxm(typeApp,index.column());
              if(!pxm.isNull())
             return QVariant(pxm);
             break;
         }
         case 1:
         {
             UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
             if(un->getDK()==1)
             pxm = item->getPxm(typeApp,index.column());
              if(!pxm.isNull())
             return QVariant(pxm);
             break;
         }
         case 2:
         {
             UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
             if(un->getAlarmMsgOn()==1)
             pxm = item->getPxm(typeApp,index.column());
              if(!pxm.isNull())
             return QVariant(pxm);
             break;
         }

         default:
         {
             break;
         }

         }
     //    if(!pxm.isNull())
     //        pxm = pxm.scaled(17,17);


     }

     if(role == Qt::DisplayRole)
         return item->data(index.column());



     if(role == Qt::BackgroundRole)
     {
         if(item->getBroken())
              return QVariant(QColor("#FEBC9F"));


         foreach(QModelIndex ind, list_Equals_for_chanell)
         {
         if(ind.parent()==index.parent()&&
            ind.row()==index.row())
              return QVariant(QColor(Qt::green));
         }

         foreach(QModelIndex ind, list_Equals)
         {
             if(ind.parent()==index.parent()&&
                ind.row()==index.row())
              return QVariant(QColor(204, 255, 255, 255));
         }



         return QVariant(QColor(Qt::white));


     }

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
         return Qt::NoItemFlags;

     if (typeApp==SubTypeApp::configurator) //если конфигуратор
     {
         auto un = static_cast<UnitNode*>(index.internalPointer());

         if(TypeUnitNode::SYSTEM != un->getType()){
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
         } else {
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
         }
     }

     return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
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
     //qDebug() << "TreeModelUnitNode::appendNewUNInStructure(" << index << ", " << un << ") -->";
     UnitNode *parent = static_cast<UnitNode*>(index.internalPointer());

     this->beginInsertRows(index.parent(), index.row(), index.row());
     parent->addTreeChild(un);
     parent->addChild(un);
     this->endInsertRows();

     //qDebug() << "TreeModelUnitNode::appendNewUNInStructure() <--";

     return;
 }

  void TreeModelUnitNode::appendNewUNInStructure(UnitNode* /*un*/)
  {
      this->beginResetModel();
      this->createProxySortTree();//
      this->endResetModel();
      return;

 //     this->beginInsertRows(this->findeIndexUNL(un->unTreeParent),
 //                           un->unTreeParent->listChilde.indexOf(un),
 //                           un->unTreeParent->listChilde.indexOf(un));
 //     this->endInsertRows();
  }

 void TreeModelUnitNode::updateUNStructure(UnitNode* /*un*/)
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

QModelIndex TreeModelUnitNode::findeIndexUNL(UnitNode *tc,
                                             UnitNode *parentTC)
{
    return this->findeIndexUN(tc, 0, parentTC);
}

void TreeModelUnitNode::updateModel()
{
    this->beginResetModel();
    this->endResetModel();
}

QModelIndex TreeModelUnitNode::findeIndexUNR(UnitNode *tc,
                                             UnitNode *parentTC)
{
    return this->findeIndexUN(tc, 4, parentTC);///2
}

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
                                        parentTC->treeChild(i));///1
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

bool TreeModelUnitNode::loadSettings(QString fileName)
{
    this->beginResetModel();


    listItemUN= SettingUtils::loadTreeUnitNodes(this,rootItemUN, fileName);

    this->endResetModel();

     return true;





}

void TreeModelUnitNode::makeEmptyTree()
{
    this->beginResetModel();
    listItemUN = SettingUtils::loadEmptyTree(rootItemUN);
    this->endResetModel();
}

void TreeModelUnitNode::getListFromModel(QList<UnitNode *> &list, UnitNode* parentTC) const
{
    if(nullptr == parentTC) {
        list.clear();
        parentTC = rootItemUN;
    }

    for(int i(0), n(parentTC->treeChildCount()); i < n; i++)
    {
        auto un = parentTC->treeChild(i);
        un->setMetaNames(QString("Obj_%1").arg(list.count()));
        list.append(un);
        if(0 < un->treeChildCount())
            getListFromModel(list, un);
    }
}

bool TreeModelUnitNode::deleteUnit(QModelIndex index)
{
    //qDebug()<<"TreeModelUnitNode::deleteUnit(" << index << ") -->";

    if(this->parent(index).isValid()) {
        this->beginRemoveRows(index.parent(),index.row(),index.row());
        UnitNode *parent = static_cast<UnitNode*>(this->parent(index).internalPointer());
        parent->deleteChild(index.row());
        //emit dataChanged(index,index);
        this->endRemoveRows();
        emit dataChanged(index,index);
        //qDebug()<<"TreeModelUnitNode::deleteUnit() <-- true";
        return true;
    } else
        //qDebug()<<"TreeModelUnitNode::deleteUnit() <-- false";

    return false;
}

bool TreeModelUnitNode::moveUNUp(QModelIndex index)
{
    if(index.row()>0) {
        UnitNode * un = static_cast<UnitNode*>(index.internalPointer());
        UnitNode * parent = un->getTreeParentUN();
        QModelIndex parent_ind = this->parent(index);

        this->beginMoveRows(parent_ind,
                            index.row(),
                            index.row(),
                            parent_ind,
                            (index.row() - 1));

      //  this->moveRow(parent_ind,index.row(),parent_ind,(index.row()-1));
        parent->moveTreeChildUNUp(un);

        this->endMoveRows();
        return true;
    }

    return false;
 //  this->beginMoveRows()
 //   //    parent->move_up(index.row());
 //   this->endResetModel();
}

bool TreeModelUnitNode::moveUNDown(QModelIndex index)
{
    if(index.row() < (this->rowCount(this->parent(index)) - 1)) {
        UnitNode * un = static_cast<UnitNode*>(index.internalPointer());
        UnitNode * parent = un->getTreeParentUN();
        QModelIndex parent_ind = this->parent(index);

        this->beginMoveRows(parent_ind,
                            index.row(),
                            index.row(),
                            parent_ind,
                            (index.row() + 2));

      //  this->moveRow(parent,index.row(),parent,(index.row()-1));
        parent->moveTreeChildUNDown(un);

        this->endMoveRows();
        return true;
    }
    return false;
}

void TreeModelUnitNode::createProxySortTree()
{

//    this->beginResetModel();
    loadSettings();

    sortingListItemUN();

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
