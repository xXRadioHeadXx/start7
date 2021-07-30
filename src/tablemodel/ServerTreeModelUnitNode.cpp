#include "ServerTreeModelUnitNode.h"
#include "ServerSettingUtils.h"
#include "SignalSlotCommutator.h"
#include <QPixmap>

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
    sortOrder(Qt::AscendingOrder)
{
//    rootItemUN = QSharedPointer<UnitNode>::create();
    rootItemUN->setLevel(0); //rootItemUN->treeParent().isNull();


    connect(SignalSlotCommutator::getInstance(),
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
    return 1;
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
        rootItemUN != item &&
        0 == index.column())
     {
         QPixmap pxm;
         switch(index.column())
         {
         case 0:
         {
             pxm = item->getPxm(typeApp);
             break;
         }
         default:
         {
             break;
         }
         }
         if(!pxm.isNull())
             pxm = pxm.scaled(17,17);

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

         if(TypeUnitNode::SYSTEM != un->getType()){
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
     if (parent.column() > 0)
         return 0;

     if (!parent.isValid())
         parentItem = rootItemUN;
     else
         parentItem = getTreeUnitNodes(static_cast<UnitNode*>(parent.internalPointer()));

     return parentItem->treeChildCount();
 }

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

void ServerTreeModelUnitNode::updateUNs()
{
    emit this->dataChanged(QModelIndex(), QModelIndex());
    SignalSlotCommutator::getInstance()->emitUpdDataTreeUN();
//    emit this->updatedUNs();
    return;
}

void ServerTreeModelUnitNode::loadSettings(QString fileName)
{
    this->beginResetModel();
    listItemUN = ServerSettingUtils::loadTreeUnitNodes(rootItemUN, fileName);
    this->endResetModel();
}

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
                const auto &itl = std::next(listItemUN.begin(), j),
                           &itr = std::next(itl, 1);
                if((*itl)->getName().compare((*itr)->getName()) > 0)
                {
                    std::swap(*itl, *itr);
                }
            }
            if(Qt::DescendingOrder == sortOrder)
            {
                const auto &itl = std::next(listItemUN.begin(), j),
                           &itr = std::next(itl, 1);
                if((*itl)->getName().compare((*itr)->getName()) < 0)
                {
                    std::swap(*itl, *itr);
                }
            }
        }
    }
}
