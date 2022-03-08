#include "IniFileService.h"
#include "MessageBoxServer.h"
#include "ServerSettingUtils.h"

#include <QDebug>
#include "UnitNodeFactory.h"
#include "Utils.h"
#include "global.h"
#include <QTextCodec>
#include "TreeItem.h"
#include "SimpleIni.h"
#include <QStringList>
#include <QFile>
#include <QStorageInfo>



ServerSettingUtils::ServerSettingUtils()
{

}

//QList<QSharedPointer<UnitNode>> ServerSettingUtils::listTreeUnitNodes;
//QSet<QSharedPointer<UnitNode>> ServerSettingUtils::listMetaRealUnitNodes;
//QList<QSharedPointer<UnitNode>> ServerSettingUtils::sortedMetaRealUnitNodes;
//QSharedPointer<UnitNode> ServerSettingUtils::systemUnitNodes;

//QList<QSharedPointer<UnitNode> > ServerSettingUtils::getLinkedUI(QSharedPointer<UnitNode> un)
//{
//    QList<QSharedPointer<UnitNode> > result;

//    auto setMasterUN = un->getDoubles();
//    setMasterUN.insert(un);

//    QSet<QSharedPointer<UnitNode> > setSlaveUN;
//    for(const auto& m : as_const(setMasterUN)) {
//        for(const auto& c : as_const(m->listTreeChilds())) {
//            auto cun = c.dynamicCast<UnitNode>();
//            if(TypeUnitNodeEnum::IU_BL_IP == cun->getType()) {
//                setSlaveUN.insert(cun);
//                setSlaveUN.unite(cun->getDoubles());
//            }
//        }
//    }

//    setSlaveUN = setSlaveUN.intersect(ServerSettingUtils::getSetMetaRealUnitNodes());

//    result = setSlaveUN.values();

//    return result;
//}

//int ServerSettingUtils::linkDoubles(QSharedPointer<UnitNode> &un)
//{
//    int result = 0;
//    QSet<QSharedPointer<UnitNode>> tmp;
//    tmp.unite(QSet<QSharedPointer<UnitNode>>::fromList(getListTreeUnitNodes()));
//    tmp.unite(getSetMetaRealUnitNodes());
//    for(const QSharedPointer<UnitNode> &dblUN : as_const(tmp)) {
//        if(dblUN->getType() == un->getType() &&
//                dblUN->getUdpAdress() == un->getUdpAdress() &&
//                dblUN->getUdpPort() == un->getUdpPort() &&
////                dblUN->getNum3() == un->getNum3() &&
//                dblUN->getNum2() == un->getNum2() &&
//                dblUN->getNum1() == un->getNum1() &&
//                dblUN != un) {
//            un->setDoubles(dblUN->getDoubles());
//            un->setDoubles(dblUN);
//            dblUN->setDoubles(un->getDoubles());
//            dblUN->setDoubles(un);
//            result++;
//        }
//    }
//    return result;
//}

//QList<QSharedPointer<UnitNode> > ServerSettingUtils::loadTreeUnitNodes(QSharedPointer<UnitNode> root, QString fileName) {
////    qDebug() << "ServerSettingUtils::loadTreeUnitNodes -->";
//    if(!getListTreeUnitNodes().isEmpty()) {
//        getListTreeUnitNodes().clear();
//    }

//    int cntTrItm = IniFileService::getValueBySectionKey("TREE", "Count").toInt();

//    if(0 >= cntTrItm)
//        return getListTreeUnitNodes();

//    {
//        auto tmpUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::SYSTEM, root);

//        tmpUN->setType(TypeUnitNodeEnum::SYSTEM);
//        tmpUN->setNum1(0);
//        tmpUN->setNum2(0);
//        tmpUN->setNum3(0);
//        tmpUN->setLevel(0);
//        tmpUN->setName(QObject::tr("Система"));
//        tmpUN->setMetaNames("Obj_0");
//        tmpUN->setPublishedState(10);

//        ServerUnitNodeTreeItem::addTreeChildrenToParent(tmpUN, root);
//        root = tmpUN;
//        getListTreeUnitNodes().append(tmpUN);
//        ServerSettingUtils::setSystemUnitNodes(tmpUN);
//    }

//    for(int index = 0; index < cntTrItm; index++)
//    {
//        QString strGroup("Obj_%1");
//        strGroup = strGroup.arg(index + 1);

////        qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " parse";

//        auto tmpUN = IniFileService::makeSharedUnitNodeBySection(strGroup);
//        if(!tmpUN.isNull()) {

//            tmpUN->setPublishedState(10);

//            if(!tmpUN->getName().isEmpty())
//            {
////                qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " parse successfully " << tmpUN->toString();
////                qDebug() << tmpUN->metaName << tmpUN->toString();
//                getListTreeUnitNodes().append(QSharedPointer<UnitNode>(tmpUN));
//                bool key = true;
//                for (auto rit = getListTreeUnitNodes().rbegin(); rit != getListTreeUnitNodes().rend(); ++rit) {
//                    if((*rit)->getLevel() < tmpUN->getLevel())
//                    {
//                        ServerUnitNodeTreeItem::addTreeChildrenToParent(tmpUN, (*rit));
//                        key = false;
//                        break;
//                    }
//                }

//                if(key) {
//                    ServerUnitNodeTreeItem::addTreeChildrenToParent(tmpUN, root);
//                }

//                //Double паходим дубли
//                ServerSettingUtils::linkDoubles(tmpUN);

//                key = false;

//                if(!tmpUN->getDoubles().isEmpty()) {

//                    QSharedPointer<UnitNode> posybleParent;
//                    for(const auto& dbl : as_const(tmpUN->getDoubles().values())) {
//                        auto posybleParent = TopologyService::findReciver(dbl);
//                        if(!posybleParent.isNull()) {
//                            tmpUN->setParentUN(posybleParent);
////                            qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " set parrent " << tmpUN->toString() << " parent " << tmpUN->getParentUN()->toString();
//                            break;
//                        }
//                    }
//                } else if(tmpUN->getDoubles().isEmpty() &&
//                          (TypeUnitNodeEnum::RLM_C == tmpUN->getType() ||
//                           TypeUnitNodeEnum::RLM_KRL == tmpUN->getType())) {

////                    tmpUN->addChild(tmpUN);
//                    tmpUN->setParentUN(tmpUN);
////                    qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " insert " << tmpUN->toString() << " parent " << tmpUN->getParentUN()->toString();
//                    insertMetaRealUnitNodes(tmpUN);

//                } else if(tmpUN->getDoubles().isEmpty() &&
//                        (TypeUnitNodeEnum::SD_BL_IP == tmpUN->getType() ||
//                        TypeUnitNodeEnum::IU_BL_IP == tmpUN->getType())) {
//                    key = true;

//                    QSharedPointer<UnitNode> tmpParentUN;
//                    // find reciver in meta set
//                    for(auto& parentUN : sortMetaRealUnitNodes()) {
//                        if(parentUN->getType() == TypeUnitNodeEnum::BL_IP &&
//                           parentUN->getUdpAdress() == tmpUN->getUdpAdress() &&
//                           parentUN->getUdpPort() == tmpUN->getUdpPort()) {
//                            tmpParentUN = parentUN;
//                            break;
//                        }
//                    }
//                    // create reciver
//                    if(tmpParentUN.isNull()){
//                        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BL_IP);
//                        tmpParentUN->setType(TypeUnitNodeEnum::BL_IP);
//                        tmpParentUN->setUdpAdress(tmpUN->getUdpAdress());
//                        tmpParentUN->setUdpPort(tmpUN->getUdpPort());
//                        tmpParentUN->setName("MetaBLIP");
//                        tmpParentUN->setNum1(static_cast<uint8_t>(0xFF));
//                        tmpParentUN->setControl(false);
//                        tmpParentUN->setMetaEntity(1);

//                        tmpParentUN->setPublishedState(10);
//
//                        insertMetaRealUnitNodes(tmpParentUN);
//                        ServerSettingUtils::linkDoubles(tmpParentUN);
//                    }

//                    tmpParentUN->addChild(tmpUN);
//                    tmpUN->setParentUN(tmpParentUN);

////                    qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " insert " << tmpUN->toString() << " parent " << tmpUN->getParentUN()->toString();
//                    insertMetaRealUnitNodes(tmpUN);

//                } else if(tmpUN->getDoubles().isEmpty() &&
//                          TypeUnitNodeEnum::TG == tmpUN->getType()) {
//                    // find reciver in meta set
//                    QSharedPointer<UnitNode> tmpParentUN;// = UnitNodeFactory::make(TypeUnitNode::BL_IP);
//                    for(QSharedPointer<UnitNode> parentUN : as_const(getSetMetaRealUnitNodes().values())) {
//                        if(parentUN->getType() == TypeUnitNodeEnum::TG_Base &&
//                           parentUN->getUdpAdress() == tmpUN->getUdpAdress() &&
//                           parentUN->getUdpPort() == tmpUN->getUdpPort() &&
//                           parentUN->getNum1() == tmpUN->getNum1()) {
//                            tmpParentUN = parentUN;
//                            break;
//                        }
//                    }
//                    // create reciver
//                    if(tmpParentUN.isNull()){
//                        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::TG_Base);
////                        *(tmpParentUN.data()) = *(tmpUN.data());

//                        tmpParentUN->setType(TypeUnitNodeEnum::TG_Base);
//                        tmpParentUN->setUdpAdress(tmpUN->getUdpAdress());
//                        tmpParentUN->setUdpPort(tmpUN->getUdpPort());
//                        tmpParentUN->setNum1(tmpUN->getNum1());
//                        tmpParentUN->setNum2(0);
//                        tmpParentUN->setNum3(0);

//                        tmpParentUN->setName("MetaTG_" + QString::number(tmpParentUN->getNum1()));
//                        tmpParentUN->setControl(false);
//                        tmpParentUN->setMetaEntity(1);

//                        tmpParentUN->setPublishedState(10);

//                        insertMetaRealUnitNodes(tmpParentUN);
//                        ServerSettingUtils::linkDoubles(tmpParentUN);
//                    }

//                    tmpParentUN->addChild(tmpUN);
//                    tmpUN->setParentUN(tmpParentUN);

////                    qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " insert " << tmpUN->toString() << " parent " << tmpUN->getParentUN()->toString();
//                    insertMetaRealUnitNodes(tmpUN);
//                } else {
////                    qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " not insert " << tmpUN->toString();
//                }

//            }
//        }
//    }

////    for(const auto& un : ServerSettingUtils::getSetMetaRealUnitNodes()) {
//    for(auto it = ServerSettingUtils::sortMetaRealUnitNodes().begin(); it != ServerSettingUtils::sortMetaRealUnitNodes().end();) {
//        const auto& un = *it;
//        if(TypeUnitNodeEnum::SD_BL_IP == un->getType() &&
//           !un->getParentUN().isNull() &&
//           1 <= un->getNum2() && 4 >= un->getNum2()) {
//            QSharedPointer<UnitNode> parent = un->getParentUN();
//            bool needAddUI = true;

//            for(int i = 0, n = parent->childCount(); i < n; i++) {
//                auto unChild = parent->child(i);
//                if(!unChild.isNull() &&
//                   TypeUnitNodeEnum::IU_BL_IP == unChild->getType() &&
//                   un->getNum2() == unChild->getNum2() &&
//                   un->getUdpPort() == unChild->getUdpPort() &&
//                   un->getUdpAdress() == unChild->getUdpAdress()) {
//                    needAddUI = false;
//                    break;
//                }
//            }

//            if(needAddUI) {
//                auto newMetaUnIuBlIp = UnitNodeFactory::makeShare(TypeUnitNodeEnum::IU_BL_IP, parent);
//                newMetaUnIuBlIp->setNum2(un->getNum2());
//                newMetaUnIuBlIp->setUdpPort(un->getUdpPort());
//                newMetaUnIuBlIp->setUdpAdress(un->getUdpAdress());
//                newMetaUnIuBlIp->setUdpTimeout(un->getUdpTimeout());
//                newMetaUnIuBlIp->setNum1(un->getNum1());
//                newMetaUnIuBlIp->setStateWord(0x41u, un->getStateWord(0x41u));

//                newMetaUnIuBlIp->setName("MetaIU_" + QString::number(newMetaUnIuBlIp->getNum2()));
//                newMetaUnIuBlIp->setControl(false);
//                newMetaUnIuBlIp->setMetaEntity(1);
//                newMetaUnIuBlIp->setPublishedState(10);

//                parent->addChild(newMetaUnIuBlIp);
//                newMetaUnIuBlIp->setParentUN(parent);
////                qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- meta insert " << newMetaUnIuBlIp->toString() << " parent " << newMetaUnIuBlIp->getParentUN()->toString();
//                insertMetaRealUnitNodes(newMetaUnIuBlIp);
//                ServerSettingUtils::linkDoubles(newMetaUnIuBlIp);
//                it = ServerSettingUtils::sortMetaRealUnitNodes().begin();
//                continue;
//            }
//        }
//        ++it;
//    }

////    for(const auto& un : ServerSettingUtils::sortMetaRealUnitNodes()) {
//    for(auto it = ServerSettingUtils::sortMetaRealUnitNodes().begin(); it != ServerSettingUtils::sortMetaRealUnitNodes().end();) {
//        const auto& un = *it;
//        if(!TopologyService::findReciver(un).isNull()) {
//            ++it;
//            continue;
//        }

//        const auto& doubles = un->getDoubles().values();

//        QSharedPointer<UnitNode> possibleParent;
//        for(const auto& dbl : doubles) {
//            possibleParent = TopologyService::findReciver(dbl);
//            if(!possibleParent.isNull())
//                break;
//        }

//        if(possibleParent.isNull()) {
//            if(TypeUnitNodeEnum::SD_BL_IP == un->getType()
//            || TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
//                possibleParent = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BL_IP);
//                possibleParent->setType(TypeUnitNodeEnum::BL_IP);
//                possibleParent->setUdpAdress(un->getUdpAdress());
//                possibleParent->setUdpPort(un->getUdpPort());
//                possibleParent->setName("MetaBLIP");
//                possibleParent->setNum1(static_cast<uint8_t>(0xFF));
//                possibleParent->setControl(false);
//                possibleParent->setMetaEntity(1);
//            } else if (TypeUnitNodeEnum::TG == un->getType()) {
//                possibleParent = UnitNodeFactory::makeShare(TypeUnitNodeEnum::TG_Base);
//                possibleParent->setType(TypeUnitNodeEnum::TG_Base);
//                possibleParent->setUdpAdress(un->getUdpAdress());
//                possibleParent->setUdpPort(un->getUdpPort());
//                possibleParent->setNum1(un->getNum1());
//                possibleParent->setNum2(0);
//                possibleParent->setNum3(0);
//                possibleParent->setName("MetaTG_" + QString::number(un->getNum1()));
//                possibleParent->setControl(false);
//                possibleParent->setMetaEntity(1);
//            } else if (TypeUnitNodeEnum::RLM_C == un->getType()
//                    || TypeUnitNodeEnum::RLM_KRL == un->getType()) {
//                possibleParent = un;
//            }
//        }

//        if(!possibleParent.isNull()) {
//            possibleParent->setPublishedState(10);
//            insertMetaRealUnitNodes(possibleParent);
//            ServerSettingUtils::linkDoubles(possibleParent);
//            un->setParentUN(possibleParent);
//            for(const auto& dbl : doubles) {
//                dbl->setParentUN(possibleParent);
//            }
//            it = ServerSettingUtils::sortMetaRealUnitNodes().begin();
//            continue;
//        }
//        ++it;
//    }

////    std::sort(ServerSettingUtils::listTreeUnitNodes.begin(), ServerSettingUtils::listTreeUnitNodes.end());
////    for(auto un : getListTreeUnitNodes())
////        qDebug() << un->toString();
////    for(auto un : getSetMetaRealUnitNodes())
////        qDebug() << un->toString();

//    qDebug() << "ServerSettingUtils::loadTreeUnitNodes <--";

//    return getListTreeUnitNodes();
//}

//QList<QSharedPointer<UnitNode> > ServerSettingUtils::loadEmptyTree(QSharedPointer<UnitNode> root)
//{
//    if(!getListTreeUnitNodes().isEmpty()) {
//   //     for(UnitNode*un : getListTreeUnitNodes())
//   //         delete un;
//        getListTreeUnitNodes().clear();
//        root->removeAllTreeChildren();
//    }




//    {
//        auto tmpUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::SYSTEM, root);

//        tmpUN->setType(TypeUnitNodeEnum::SYSTEM);
//        tmpUN->setNum1(0);
//        tmpUN->setNum2(0);
//        tmpUN->setNum3(0);
//        tmpUN->setLevel(0);
//        tmpUN->setName(QObject::tr("Система"));
//        tmpUN->setMetaNames("Obj_0");

//        ServerUnitNodeTreeItem::addTreeChildrenToParent(tmpUN, root);
////        root = tmpUN;
//        getListTreeUnitNodes().append(tmpUN);


//    }

//      return getListTreeUnitNodes();
//}

//QList<QSharedPointer<UnitNode> > & ServerSettingUtils::getListTreeUnitNodes() {
//    return ServerSettingUtils::listTreeUnitNodes;
//}

//QSharedPointer<UnitNode> ServerSettingUtils::getTreeUnitNodes(UnitNode* target)
//{
//    for(QSharedPointer<UnitNode> & un : getListTreeUnitNodes()) {
//        if(target == un.data()) {
//            return un;
//        }
//    }
//    return QSharedPointer<UnitNode>();
//}

//const QList<QSharedPointer<UnitNode>> &ServerSettingUtils::sortMetaRealUnitNodes() {
//    return ServerSettingUtils::sortedMetaRealUnitNodes;
//}

//QSet<QSharedPointer<UnitNode>> & ServerSettingUtils::getSetMetaRealUnitNodes() {
//    return ServerSettingUtils::listMetaRealUnitNodes;
//}

//QSet<QSharedPointer<UnitNode>>::iterator ServerSettingUtils::insertMetaRealUnitNodes(const QSharedPointer<UnitNode> &value) {
////    qDebug() << "ServerSettingUtils::insertMetaRealUnitNodes";
//    auto it = ServerSettingUtils::listMetaRealUnitNodes.insert(value);
//    ServerSettingUtils::sortedMetaRealUnitNodes = ServerSettingUtils::listMetaRealUnitNodes.values();
//    std::sort(ServerSettingUtils::sortedMetaRealUnitNodes.begin(), ServerSettingUtils::sortedMetaRealUnitNodes.end());
//    return it;
//}

//QSharedPointer<UnitNode> ServerSettingUtils::getMetaRealUnitNodes(const QSharedPointer<UnitNode> &target)
//{
//    for(QSharedPointer<UnitNode> & un : getSetMetaRealUnitNodes().values()) {
//        if(target->equale(*un.data())) {
//            return un;
//        }
//    }
//    return QSharedPointer<UnitNode>();
//}

//QSharedPointer<UnitNode> ServerSettingUtils::getMetaRealUnitNodes(UnitNode* target)
//{
//    for(QSharedPointer<UnitNode> & un : getSetMetaRealUnitNodes().values()) {
//        if(target == un.data()) {
//            return un;
//        }
//    }
//    return QSharedPointer<UnitNode>();
//}

QVariant ServerSettingUtils::getValueSettings(const QString key, const QString group, const QString fileName) {
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

    CSimpleIniA ini;
    ini.LoadFile(fileName.toStdString().c_str());

    if(0 != ini.GetSection(group.toStdString().c_str())) {
        return codec->toUnicode(ini.GetValue(group.toStdString().c_str(), key.toStdString().c_str()));
    }
    return QVariant();
}

bool ServerSettingUtils::loadTreeUnitNodes(UnitNode*/*root*/, UnitNode*/*unit*/)
{
//    //qDebug()<<"SettingUtils::loadTreeUnitNodes";
    return true;
}

QSet<int>  ServerSettingUtils::priorityJoutTyper = {901,902, 20,21,22,23,25,905,1'007, 200,10, 904, 12,13,17,18, 110,111,112,113,11, 130,131/*,133*/,134,135,136,137,140,141,150,151,1'000,1'001,1'002,1'003,1'004,1'007/*,1133*/,1'136,1'137,1'902, 11,13};

const QSet<int> &ServerSettingUtils::getPriorityJoutTyper()
{
    return priorityJoutTyper;
}

QStringList ServerSettingUtils::reasonTemplate([](){
    QString nameFile("comment.lst");
    if(!QFile::exists(nameFile))//(QCoreApplication::applicationDirPath() + "/" + nameFile))
        return QStringList();

    QFile file(nameFile);//(QCoreApplication::applicationDirPath() + "/" + nameFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QStringList();

    QStringList result;

    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    while (!file.atEnd()) {
        result.append(codec->toUnicode(file.readLine()).remove(QChar(0x0B)).remove(QChar(0x0A)));
    }

    return result;
}());

QStringList ServerSettingUtils::measureTemplate([](){
    QString nameFile("comment2.lst");
    if(!QFile::exists(nameFile))//QCoreApplication::applicationDirPath() + "/" + nameFile))
        return QStringList();

    QFile file(nameFile);//(QCoreApplication::applicationDirPath() + "/" + nameFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QStringList();

    QStringList result;

    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    while (!file.atEnd()) {
        result.append(codec->toUnicode(file.readLine()).remove(QChar(0x0B)).remove(QChar(0x0A)));
    }

    return result;
}());

const QStringList &ServerSettingUtils::getMeasureTemplate()
{
    return measureTemplate;
}

const QStringList &ServerSettingUtils::getReasonTemplate()
{
    return reasonTemplate;
}

//QSharedPointer<UnitNode> &ServerSettingUtils::getSystemUnitNodes()
//{
//    return systemUnitNodes;
//}

//void ServerSettingUtils::setSystemUnitNodes(const QSharedPointer<UnitNode> &newSystemUnitNodes)
//{
//    systemUnitNodes = newSystemUnitNodes;
//}

//void ServerSettingUtils::systemUnitNodesSetDkInvolvedFalse()
//{
//    for(const auto& un : ServerSettingUtils::sortMetaRealUnitNodes()) {
//        if(un->getDkInvolved())
//            return;
//    }
//    if(!ServerSettingUtils::getSystemUnitNodes().isNull())
//        ServerSettingUtils::getSystemUnitNodes()->setDkInvolved(false);
//}

bool ServerSettingUtils::checkAuditAdm() {
    qDebug() << "ServerSettingUtils::checkAuditAdm() -->";
    for (const auto& storage : as_const(QStorageInfo::mountedVolumes())) {
        const auto& rootPath = storage.rootPath();
        if(!rootPath.contains("/media/"))
            continue;

        QString fileName("auidit.adm");
        if(!QFileInfo::exists(rootPath + "/" + fileName))
            continue;

       if (storage.isReadOnly())
           qDebug() << "isReadOnly:" << storage.isReadOnly();

       qDebug() << "name:" << storage.name();
       qDebug() << "fileSystemType:" << storage.fileSystemType();
       qDebug() << "size:" << storage.bytesTotal()/1000/1000 << "MB";
       qDebug() << "availableSize:" << storage.bytesAvailable()/1000/1000 << "MB";

       QFile file(rootPath + "/" + fileName);
       if(file.open(QIODevice::ReadOnly)) {
           QDataStream in1(&file);    // read the data serialized from the file
           in1.setByteOrder(QDataStream::LittleEndian);
           double a;
           double b;
           double c;

           in1  >> b >> a >> c;
           file.close();

           if(c == a+b) {
               qDebug() << "ServerSettingUtils::checkAuditAdm <-- [true]";
               return true;
           } else {
               continue;
           }
       }
    }
    qDebug() << "ServerSettingUtils::checkAuditAdm <-- [false]";
#ifdef QT_DEBUG
    return true;
#endif
    return false;
}

bool ServerSettingUtils::checkDialogAuditAdm()
{
    bool result = ServerSettingUtils::checkAuditAdm();
    if(!result) {
        const auto ret = MessageBoxServer::questionInsertAdminKeyAndClickOK();
        if(QMessageBox::Ok == ret) {
            result = ServerSettingUtils::checkAuditAdm();
            if(!result) {
                MessageBoxServer::infoAdminKeyNotFound();
            }
        }
    }
#ifdef QT_DEBUG
    return true;
#endif
    return result;
}
