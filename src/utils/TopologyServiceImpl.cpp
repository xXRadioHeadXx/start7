#include "TopologyServiceImpl.h"
#include "../src/utils/IniFileService.h"
#include "../src/entity/UnitNodeFactory.h"
#include "../src/global.h"

TopologyServiceImpl::TopologyServiceImpl() :
    AfterConstructInitialization()
{
    treeRootUnitNodes = QSharedPointer<UnitNode>(new UnitNode());
}

void TopologyServiceImpl::loadTreeUnitNodes()
{
    qDebug() << "TopologyServiceImpl::loadTreeUnitNodes -->";
    auto root = treeRootUnitNodes;
    if(!listTreeUnitNodes.isEmpty()) {
        listTreeUnitNodes.clear();
    }

    int cntTrItm = IniFileService::getValueBySectionKey("TREE", "Count", "0").toInt();

    if(0 >= cntTrItm)
        return;

    {
        auto tmpUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::SYSTEM, root);

        tmpUN->setType(TypeUnitNodeEnum::SYSTEM);
        tmpUN->setNum1(0);
        tmpUN->setNum2(0);
        tmpUN->setNum3(0);
        tmpUN->setLevel(0);
        tmpUN->setName(QObject::tr("Система"));
        tmpUN->setMetaNames("Obj_0");
        tmpUN->setPublishedState(10);

        addTreeChildrenToParent(tmpUN, root);
        root = tmpUN;
        listTreeUnitNodes.append(tmpUN);
        systemUnitNodes = tmpUN;
    }

    for(int index = 0; index < cntTrItm; index++)
    {
        QString strGroup("Obj_%1");
        strGroup = strGroup.arg(index + 1);

//        qDebug() << "TopologyServiceImpl::loadTreeUnitNodes -- " << strGroup << " parse";

        auto tmpUN = IniFileService::makeSharedUnitNodeBySection(strGroup);
        if(!tmpUN.isNull()) {

            tmpUN->setPublishedState(10);

            if(!tmpUN->getName().isEmpty())
            {
//                qDebug() << "TopologyServiceImpl::loadTreeUnitNodes -- " << strGroup << " parse successfully " << tmpUN->toString();
//                qDebug() << tmpUN->metaName << tmpUN->toString();
                listTreeUnitNodes.append(QSharedPointer<UnitNode>(tmpUN));
                bool key = true;
                for (auto rit = listTreeUnitNodes.rbegin(); rit != listTreeUnitNodes.rend(); ++rit) {
                    if((*rit)->getLevel() < tmpUN->getLevel())
                    {
                        addTreeChildrenToParent(tmpUN, (*rit));
                        key = false;
                        break;
                    }
                }

                if(key) {
                    addTreeChildrenToParent(tmpUN, root);
                }

                //Double паходим дубли
                linkDoubles(tmpUN);

                if(!tmpUN->getDoubles().isEmpty()) {
                    inclusiveDouble(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && (TypeUnitNodeEnum::RLM_C == tmpUN->getType()
                        || TypeUnitNodeEnum::RLM_KRL == tmpUN->getType())) {
                    inclusiveRLM(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::IU_BL_IP == tmpUN->getType()) {
                    inclusiveBLIPIU(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::SD_BL_IP == tmpUN->getType()) {
                    inclusiveBLIPSD(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::SSOI_IU_BL_IP == tmpUN->getType()) {
                    inclusiveSSOIBLIPIU(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::SSOI_SD_BL_IP == tmpUN->getType()) {
                    inclusiveSSOIBLIPSD(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::TG == tmpUN->getType()) {
                    inclusiveTG(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::BOD_T4K_M == tmpUN->getType()) {
                    inclusiveBOD_T4K_M(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::Y4_T4K_M == tmpUN->getType()) {
                    inclusiveY4_T4K_M(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::DD_T4K_M == tmpUN->getType()) {
                    inclusiveDD_T4K_M(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::BOD_SOTA == tmpUN->getType()) {
                    inclusiveBOD_SOTA(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::Y4_SOTA == tmpUN->getType()) {
                    inclusiveY4_SOTA(tmpUN);
                } else if(tmpUN->getDoubles().isEmpty()
                       && TypeUnitNodeEnum::DD_SOTA == tmpUN->getType()) {
                    inclusiveDD_SOTA(tmpUN);
                } else {
//                    qDebug() << "TopologyServiceImpl::loadTreeUnitNodes -- " << strGroup << " not insert " << tmpUN->toString();
                }

            }
        }
    }

    while(inclusiveMetaBLIP());
    while(inclusiveMetaBLIPSD());
    while(inclusiveMetaBLIPIU());

    while(inclusiveMetaSSOIBLIP());
    while(inclusiveMetaSSOIBLIPSD());
    while(inclusiveMetaSSOIBLIPIU());

    while(inclusiveMetaRLM());

    while(inclusiveMetaBaseTG());
    while(inclusiveMetaTG());

//    std::sort(TopologyServiceImpl::listTreeUnitNodes.begin(), TopologyServiceImpl::listTreeUnitNodes.end());
//    for(auto un : getListTreeUnitNodes())
//        qDebug() << un->toString();
//    for(auto un : getSetMetaRealUnitNodes())
//        qDebug() << un->toString();

    qDebug() << "TopologyServiceImpl::loadTreeUnitNodes <--";

    return;
}

void TopologyServiceImpl::inclusiveDouble(QSharedPointer<UnitNode> un) {
    QSharedPointer<UnitNode> posybleParent;
    for(const auto& dbl : as_const(un->getDoubles())) {
        auto posybleParent = findReciver(dbl);
        if(!posybleParent.isNull()) {
            un->setParentUN(posybleParent);
            break;
        }
    }
}

void TopologyServiceImpl::inclusiveBLIPSD(QSharedPointer<UnitNode> un) {
    QSharedPointer<UnitNode> tmpParentUN;
    // find reciver in meta set
    for(const auto& parentUN : as_const(listMetaRealUnitNodes)) {
        if(parentUN->getType() == TypeUnitNodeEnum::BL_IP &&
           parentUN->getUdpAdress() == un->getUdpAdress() &&
           parentUN->getUdpPort() == un->getUdpPort()) {
            tmpParentUN = parentUN;
            break;
        }
    }
    // create reciver
    if(tmpParentUN.isNull()){
        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BL_IP);
        tmpParentUN->setType(TypeUnitNodeEnum::BL_IP);
        tmpParentUN->setUdpAdress(un->getUdpAdress());
        tmpParentUN->setUdpPort(un->getUdpPort());
        tmpParentUN->setName("MetaBLIP");
        tmpParentUN->setNum1(static_cast<uint8_t>(0xFF));
        tmpParentUN->setControl(false);
        tmpParentUN->setMetaEntity(1);

        tmpParentUN->setPublishedState(10);

        insertMetaRealUnitNodes(tmpParentUN);
        linkDoubles(tmpParentUN);
    }

    tmpParentUN->addChild(un);
    un->setParentUN(tmpParentUN);
    insertMetaRealUnitNodes(un);
}

void TopologyServiceImpl::inclusiveBLIPIU(QSharedPointer<UnitNode> un) {
    QSharedPointer<UnitNode> tmpParentUN;
    // find reciver in meta set
    for(const auto& parentUN : as_const(listMetaRealUnitNodes)) {
        if(parentUN->getType() == TypeUnitNodeEnum::BL_IP &&
           parentUN->getUdpAdress() == un->getUdpAdress() &&
           parentUN->getUdpPort() == un->getUdpPort()) {
            tmpParentUN = parentUN;
            break;
        }
    }
    // create reciver
    if(tmpParentUN.isNull()){
        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BL_IP);
        tmpParentUN->setType(TypeUnitNodeEnum::BL_IP);
        tmpParentUN->setUdpAdress(un->getUdpAdress());
        tmpParentUN->setUdpPort(un->getUdpPort());
        tmpParentUN->setName("MetaBLIP");
        tmpParentUN->setNum1(static_cast<uint8_t>(0xFF));
        tmpParentUN->setControl(false);
        tmpParentUN->setMetaEntity(1);

        tmpParentUN->setPublishedState(10);

        insertMetaRealUnitNodes(tmpParentUN);
        linkDoubles(tmpParentUN);
    }

    tmpParentUN->addChild(un);
    un->setParentUN(tmpParentUN);
    insertMetaRealUnitNodes(un);
}

void TopologyServiceImpl::inclusiveSSOIBLIPSD(QSharedPointer<UnitNode> un) {
//    qDebug() << "TopologyServiceImpl::inclusiveSSOIBLIPSD --> (" << un->toString() << ")";
    QSharedPointer<UnitNode> tmpParentUN;
    // find reciver in meta set
    for(const auto& parentUN : as_const(listMetaRealUnitNodes)) {
        if(parentUN->getType() == TypeUnitNodeEnum::SSOI_BL_IP &&
           parentUN->getNum1() == un->getNum1() &&
           parentUN->getUdpAdress() == un->getUdpAdress() &&
           parentUN->getUdpPort() == un->getUdpPort()) {
            tmpParentUN = parentUN;
            break;
        }
    }
    // create reciver
    if(tmpParentUN.isNull()){
        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::SSOI_BL_IP);
        tmpParentUN->setType(TypeUnitNodeEnum::SSOI_BL_IP);
        tmpParentUN->setUdpAdress(un->getUdpAdress());
        tmpParentUN->setUdpPort(un->getUdpPort());
        tmpParentUN->setName("MetaSSOIBLIP");
        tmpParentUN->setNum1(un->getNum1());
        tmpParentUN->setControl(false);
        tmpParentUN->setMetaEntity(1);

        tmpParentUN->setPublishedState(10);

        insertMetaRealUnitNodes(tmpParentUN);
        linkDoubles(tmpParentUN);
    }

    tmpParentUN->addChild(un);
    un->setParentUN(tmpParentUN);
    insertMetaRealUnitNodes(un);
//    qDebug() << "TopologyServiceImpl::inclusiveSSOIBLIPSD <--";
}

void TopologyServiceImpl::inclusiveSSOIBLIPIU(QSharedPointer<UnitNode> un) {
//    qDebug() << "TopologyServiceImpl::inclusiveSSOIBLIPIU --> (" << un->toString() << ")";
    QSharedPointer<UnitNode> tmpParentUN;
    // find reciver in meta set
    for(const auto& parentUN : as_const(listMetaRealUnitNodes)) {
        if(parentUN->getType() == TypeUnitNodeEnum::SSOI_BL_IP &&
           parentUN->getNum1() == un->getNum1() &&
           parentUN->getUdpAdress() == un->getUdpAdress() &&
           parentUN->getUdpPort() == un->getUdpPort()) {
            tmpParentUN = parentUN;
            break;
        }
    }
    // create reciver
    if(tmpParentUN.isNull()){
        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::SSOI_BL_IP);
        tmpParentUN->setType(TypeUnitNodeEnum::SSOI_BL_IP);
        tmpParentUN->setUdpAdress(un->getUdpAdress());
        tmpParentUN->setUdpPort(un->getUdpPort());
        tmpParentUN->setName("MetaSSOIBLIP");
        tmpParentUN->setNum1(un->getNum1());
        tmpParentUN->setControl(false);
        tmpParentUN->setMetaEntity(1);

        tmpParentUN->setPublishedState(10);

        insertMetaRealUnitNodes(tmpParentUN);
        linkDoubles(tmpParentUN);
    }

    tmpParentUN->addChild(un);
    un->setParentUN(tmpParentUN);
    insertMetaRealUnitNodes(un);
//    qDebug() << "TopologyServiceImpl::inclusiveSSOIBLIPIU <--";
}


bool TopologyServiceImpl::inclusiveMetaSSOIBLIP() {
    //возможное добавление

    QSharedPointer<UnitNode> possibleParent = nullptr;
    for(const auto& un : as_const(listMetaRealUnitNodes)) {
        if(un->getParentUN().isNull()
        && (TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
         || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType())) {
            possibleParent = UnitNodeFactory::makeShare(TypeUnitNodeEnum::SSOI_BL_IP);
            possibleParent->setType(TypeUnitNodeEnum::SSOI_BL_IP);
            possibleParent->setUdpAdress(un->getUdpAdress());
            possibleParent->setUdpPort(un->getUdpPort());
            possibleParent->setName("MetaSSOIBLIP");
            possibleParent->setNum1(un->getNum1());
            possibleParent->setControl(false);
            possibleParent->setMetaEntity(1);
        }
    }

    if(!possibleParent.isNull()) {
        for(const auto& un : as_const(listMetaRealUnitNodes)) {
            if(un->getParentUN().isNull()
            && (TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
             || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType())
            && possibleParent->getNum1() == un->getNum1()
            && possibleParent->getUdpAdress() == un->getUdpAdress()
            && possibleParent->getUdpPort() == un->getUdpPort()) {
                possibleParent->addChild(un);
                un->setParentUN(possibleParent);
            }
        }

        possibleParent->setPublishedState(10);
        insertMetaRealUnitNodes(possibleParent);
        linkDoubles(possibleParent);

        return true;
    }

    return false;
}

bool TopologyServiceImpl::inclusiveMetaSSOIBLIPSD() {
    //возможное добавление
    bool result = false;
    QSharedPointer<UnitNode> parent = nullptr;
    for(const auto& un : as_const(listMetaRealUnitNodes)) {
        if(un->getParentUN().isNull()
        && TypeUnitNodeEnum::SSOI_BL_IP == un->getType()) {
            parent = un;
            result = result || inclusiveMetaSSOIBLIPSD(parent);
        }
    }

    return result;
}

bool TopologyServiceImpl::inclusiveMetaSSOIBLIPSD(QSharedPointer<UnitNode> parent) {
    //возможное добавление
    if(parent.isNull())
        return false;

    bool result = false;
    for(const auto& num2 : {1,2,3,4,5,6,7,8,9}) {
        bool needAddSD = true;
        for(int i = 0, n = parent->childCount(); i < n; i++) {
            auto unChild = parent->child(i);
            if(!unChild.isNull() &&
               TypeUnitNodeEnum::SSOI_SD_BL_IP == unChild->getType() &&
               unChild->getNum2() == num2 &&
               parent->getUdpPort() == unChild->getUdpPort() &&
               parent->getUdpAdress() == unChild->getUdpAdress()) {
                needAddSD = false;
                break;
            }
        }

        if(needAddSD) {
            auto newMetaUnSdBlIp = UnitNodeFactory::makeShare(TypeUnitNodeEnum::SSOI_SD_BL_IP, parent);
            newMetaUnSdBlIp->setNum1(parent->getNum1());
            newMetaUnSdBlIp->setNum2(num2);
            newMetaUnSdBlIp->setUdpPort(parent->getUdpPort());
            newMetaUnSdBlIp->setUdpAdress(parent->getUdpAdress());
            newMetaUnSdBlIp->setUdpTimeout(parent->getUdpTimeout());
            newMetaUnSdBlIp->setStateWord(0x41u, parent->getStateWord(0x41u));

            newMetaUnSdBlIp->setName("MetaSSOISD_" + QString::number(newMetaUnSdBlIp->getNum2()));
            newMetaUnSdBlIp->setControl(false);
            newMetaUnSdBlIp->setMetaEntity(1);
            newMetaUnSdBlIp->setPublishedState(10);

            parent->addChild(newMetaUnSdBlIp);
            newMetaUnSdBlIp->setParentUN(parent);

            insertMetaRealUnitNodes(newMetaUnSdBlIp);
            linkDoubles(newMetaUnSdBlIp);

            result = true;
        }
    }
    return result;
}

bool TopologyServiceImpl::inclusiveMetaSSOIBLIPIU() {
    //возможное добавление
    bool result = false;
    QSharedPointer<UnitNode> parent = nullptr;
    for(const auto& un : as_const(listMetaRealUnitNodes)) {
        if(un->getParentUN().isNull()
        && TypeUnitNodeEnum::SSOI_BL_IP == un->getType()) {
            parent = un;
            result = result || inclusiveMetaSSOIBLIPIU(parent);
        }
    }
    return result;
}

bool TopologyServiceImpl::inclusiveMetaSSOIBLIPIU(QSharedPointer<UnitNode> parent) {
    //возможное добавление

    if(parent.isNull())
        return false;

    bool result = false;
    for(const auto& num2 : {1,2,3,4}) {
        bool needAddIU = true;
        for(int i = 0, n = parent->childCount(); i < n; i++) {
            auto unChild = parent->child(i);
            if(!unChild.isNull() &&
               TypeUnitNodeEnum::SSOI_IU_BL_IP == unChild->getType() &&
               unChild->getNum2() == num2 &&
               parent->getUdpPort() == unChild->getUdpPort() &&
               parent->getUdpAdress() == unChild->getUdpAdress()) {
                needAddIU = false;
                break;
            }
        }

        if(needAddIU) {
            auto newMetaUnIuBlIp = UnitNodeFactory::makeShare(TypeUnitNodeEnum::SSOI_IU_BL_IP, parent);
            newMetaUnIuBlIp->setNum2(num2);
            newMetaUnIuBlIp->setUdpPort(parent->getUdpPort());
            newMetaUnIuBlIp->setUdpAdress(parent->getUdpAdress());
            newMetaUnIuBlIp->setUdpTimeout(parent->getUdpTimeout());
            newMetaUnIuBlIp->setNum1(parent->getNum1());
            newMetaUnIuBlIp->setStateWord(0x41u, parent->getStateWord(0x41u));

            newMetaUnIuBlIp->setName("MetaSSOIIU_" + QString::number(newMetaUnIuBlIp->getNum2()));
            newMetaUnIuBlIp->setControl(false);
            newMetaUnIuBlIp->setMetaEntity(1);
            newMetaUnIuBlIp->setPublishedState(10);

            parent->addChild(newMetaUnIuBlIp);
            newMetaUnIuBlIp->setParentUN(parent);

            insertMetaRealUnitNodes(newMetaUnIuBlIp);
            linkDoubles(newMetaUnIuBlIp);

            result = true;
        }
    }
    return result;
}

void TopologyServiceImpl::inclusiveRLM(QSharedPointer<UnitNode> un) {
    un->setParentUN(un);
    insertMetaRealUnitNodes(un);
}

void TopologyServiceImpl::inclusiveTG(QSharedPointer<UnitNode> un) {
    // find reciver in meta set
    QSharedPointer<UnitNode> tmpParentUN;// = UnitNodeFactory::make(TypeUnitNode::BL_IP);
    for(const auto& parentUN : as_const(listMetaRealUnitNodes)) {
        if(parentUN->getType() == TypeUnitNodeEnum::TG_Base &&
           parentUN->getUdpAdress() == un->getUdpAdress() &&
           parentUN->getUdpPort() == un->getUdpPort() &&
           parentUN->getNum1() == un->getNum1()) {
            tmpParentUN = parentUN;
            break;
        }
    }
    // create reciver
    if(tmpParentUN.isNull()){
        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::TG_Base);

        tmpParentUN->setType(TypeUnitNodeEnum::TG_Base);
        tmpParentUN->setUdpAdress(un->getUdpAdress());
        tmpParentUN->setUdpPort(un->getUdpPort());
        tmpParentUN->setNum1(un->getNum1());
        tmpParentUN->setNum2(0);
        tmpParentUN->setNum3(0);

        tmpParentUN->setName("MetaTG_" + QString::number(tmpParentUN->getNum1()));
        tmpParentUN->setControl(false);
        tmpParentUN->setMetaEntity(1);

        tmpParentUN->setPublishedState(10);

       insertMetaRealUnitNodes(tmpParentUN);
       linkDoubles(tmpParentUN);
    }

    tmpParentUN->addChild(un);
    un->setParentUN(tmpParentUN);
    insertMetaRealUnitNodes(un);
}

void TopologyServiceImpl::inclusiveBOD_T4K_M(QSharedPointer<UnitNode> un) {
    un->setParentUN(un);
    insertMetaRealUnitNodes(un);
    linkDoubles(un);
}

void TopologyServiceImpl::inclusiveY4_T4K_M(QSharedPointer<UnitNode> un) {
    QSharedPointer<UnitNode> tmpParentUN;
    // find reciver in meta set
    for(auto& parentUN : as_const(listMetaRealUnitNodes)) {
        if(parentUN->getType() == TypeUnitNodeEnum::BOD_T4K_M &&
           parentUN->getUdpAdress() == un->getUdpAdress() &&
           parentUN->getUdpPort() == un->getUdpPort() &&
           parentUN->getNum1() == un->getNum1()) {
            tmpParentUN = parentUN;
            break;
        }
    }
    // create reciver
    if(tmpParentUN.isNull()){
        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BOD_T4K_M);
        tmpParentUN->setType(TypeUnitNodeEnum::BOD_T4K_M);
        tmpParentUN->setUdpAdress(un->getUdpAdress());
        tmpParentUN->setUdpPort(un->getUdpPort());
        tmpParentUN->setName("MetaBOD_T4K_M_" + QString::number(un->getNum1()));
        tmpParentUN->setNum1(un->getNum1());
        tmpParentUN->setControl(false);
        tmpParentUN->setMetaEntity(1);

        tmpParentUN->setPublishedState(10);

        inclusiveBOD_T4K_M(tmpParentUN);
    }

    tmpParentUN->addChild(un);
    un->setParentUN(tmpParentUN);
    insertMetaRealUnitNodes(un);
    linkDoubles(un);
}

void TopologyServiceImpl::inclusiveDD_T4K_M(QSharedPointer<UnitNode> un) {
    QSharedPointer<UnitNode> tmpParentUN;
    // find reciver in meta set
    for(auto& parentUN : as_const(listMetaRealUnitNodes)) {
        if(parentUN->getType() == TypeUnitNodeEnum::Y4_T4K_M &&
           parentUN->getUdpAdress() == un->getUdpAdress() &&
           parentUN->getUdpPort() == un->getUdpPort() &&
           parentUN->getNum1() == un->getNum1() &&
           (parentUN->getNum2() / 100) == (un->getNum2() / 100)) {
            tmpParentUN = parentUN;
            break;
        }
    }
    // create reciver
    if(tmpParentUN.isNull()) {
        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::Y4_T4K_M);
        tmpParentUN->setType(TypeUnitNodeEnum::Y4_T4K_M);
        tmpParentUN->setUdpAdress(un->getUdpAdress());
        tmpParentUN->setUdpPort(un->getUdpPort());
        tmpParentUN->setName("MetaY4_T4K_M_" + QString::number(un->getNum1()) + "_" + QString::number(un->getNum2()));
        tmpParentUN->setNum1(un->getNum1());
        tmpParentUN->setNum2((un->getNum2() / 100) * 100);
        tmpParentUN->setControl(false);
        tmpParentUN->setMetaEntity(1);

        tmpParentUN->setPublishedState(10);

        inclusiveY4_T4K_M(tmpParentUN);
    }

    tmpParentUN->addChild(un);
    un->setParentUN(tmpParentUN);
    insertMetaRealUnitNodes(un);
}

void TopologyServiceImpl::inclusiveBOD_SOTA(QSharedPointer<UnitNode> un) {
    un->setParentUN(un);
    insertMetaRealUnitNodes(un);
    linkDoubles(un);
}

void TopologyServiceImpl::inclusiveY4_SOTA(QSharedPointer<UnitNode> un) {
    QSharedPointer<UnitNode> tmpParentUN;
    // find reciver in meta set
    for(auto& parentUN : as_const(listMetaRealUnitNodes)) {
        if(parentUN->getType() == TypeUnitNodeEnum::BOD_SOTA &&
           parentUN->getUdpAdress() == un->getUdpAdress() &&
           parentUN->getUdpPort() == un->getUdpPort() &&
           parentUN->getNum1() == un->getNum1()) {
            tmpParentUN = parentUN;
            break;
        }
    }
    // create reciver
    if(tmpParentUN.isNull()){
        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BOD_SOTA);
        tmpParentUN->setType(TypeUnitNodeEnum::BOD_SOTA);
        tmpParentUN->setUdpAdress(un->getUdpAdress());
        tmpParentUN->setUdpPort(un->getUdpPort());
        tmpParentUN->setName("MetaBOD_SOTA_" + QString::number(un->getNum1()));
        tmpParentUN->setNum1(un->getNum1());
        tmpParentUN->setControl(false);
        tmpParentUN->setMetaEntity(1);

        tmpParentUN->setPublishedState(10);

        inclusiveBOD_SOTA(tmpParentUN);
    }

    tmpParentUN->addChild(un);
    un->setParentUN(tmpParentUN);
    insertMetaRealUnitNodes(un);
    linkDoubles(un);
}

void TopologyServiceImpl::inclusiveDD_SOTA(QSharedPointer<UnitNode> un) {
    QSharedPointer<UnitNode> tmpParentUN;
    // find reciver in meta set
    for(auto& parentUN : as_const(listMetaRealUnitNodes)) {
        if(parentUN->getType() == TypeUnitNodeEnum::Y4_SOTA &&
           parentUN->getUdpAdress() == un->getUdpAdress() &&
           parentUN->getUdpPort() == un->getUdpPort() &&
           parentUN->getNum1() == un->getNum1() &&
           (parentUN->getNum2() / 100) == (un->getNum2() / 100)) {
            tmpParentUN = parentUN;
            break;
        }
    }
    // create reciver
    if(tmpParentUN.isNull()) {
        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNodeEnum::Y4_SOTA);
        tmpParentUN->setType(TypeUnitNodeEnum::Y4_SOTA);
        tmpParentUN->setUdpAdress(un->getUdpAdress());
        tmpParentUN->setUdpPort(un->getUdpPort());
        tmpParentUN->setName("MetaY4_SOTA_" + QString::number(un->getNum1()) + "_" + QString::number(un->getNum2()));
        tmpParentUN->setNum1(un->getNum1());
        tmpParentUN->setNum2((un->getNum2() / 100) * 100);
        tmpParentUN->setControl(false);
        tmpParentUN->setMetaEntity(1);

        tmpParentUN->setPublishedState(10);

        inclusiveY4_SOTA(tmpParentUN);
    }

    tmpParentUN->addChild(un);
    un->setParentUN(tmpParentUN);
    insertMetaRealUnitNodes(un);
}

bool TopologyServiceImpl::inclusiveMetaBLIP() {

    //возможное добавление

    QSharedPointer<UnitNode> possibleParent = nullptr;
    for(const auto& un : as_const(listMetaRealUnitNodes)) {
        if(un->getParentUN().isNull()
        && (TypeUnitNodeEnum::SD_BL_IP == un->getType()
         || TypeUnitNodeEnum::IU_BL_IP == un->getType())) {
            possibleParent = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BL_IP);
            possibleParent->setType(TypeUnitNodeEnum::BL_IP);
            possibleParent->setUdpAdress(un->getUdpAdress());
            possibleParent->setUdpPort(un->getUdpPort());
            possibleParent->setName("MetaBLIP");
            possibleParent->setNum1(static_cast<uint8_t>(0xFF));
            possibleParent->setControl(false);
            possibleParent->setMetaEntity(1);
        }
    }

    if(!possibleParent.isNull()) {
        for(const auto& un : as_const(listMetaRealUnitNodes)) {
            if(un->getParentUN().isNull()
            && (TypeUnitNodeEnum::SD_BL_IP == un->getType()
             || TypeUnitNodeEnum::IU_BL_IP == un->getType())
            && possibleParent->getUdpAdress() == un->getUdpAdress()
            && possibleParent->getUdpPort() == un->getUdpPort()) {
                possibleParent->addChild(un);
                un->setParentUN(possibleParent);
            }
        }

        possibleParent->setPublishedState(10);
        insertMetaRealUnitNodes(possibleParent);
        linkDoubles(possibleParent);

        return true;
    }

    return false;
}

bool TopologyServiceImpl::inclusiveMetaBLIPSD() {

    //возможное добавление
    bool result = false;
    QSharedPointer<UnitNode> parent = nullptr;
    for(const auto& un : as_const(listMetaRealUnitNodes)) {
        if(un->getParentUN().isNull()
        && TypeUnitNodeEnum::BL_IP == un->getType()) {
            parent = un;
            result = result || inclusiveMetaBLIPSD(parent);
        }
    }

    return result;
}

bool TopologyServiceImpl::inclusiveMetaBLIPSD(QSharedPointer<UnitNode> parent)
{

    //возможное добавление
    if(parent.isNull())
        return false;

    bool result = false;
    for(const auto& num2 : {1,2,3,4,5,6,7,8}) {
        bool needAddSD = true;
        for(int i = 0, n = parent->childCount(); i < n; i++) {
            auto unChild = parent->child(i);
            if(!unChild.isNull() &&
               TypeUnitNodeEnum::SD_BL_IP == unChild->getType() &&
               unChild->getNum2() == num2 &&
               parent->getUdpPort() == unChild->getUdpPort() &&
               parent->getUdpAdress() == unChild->getUdpAdress()) {
                needAddSD = false;
                break;
            }
        }

        if(needAddSD) {
            auto newMetaUnSdBlIp = UnitNodeFactory::makeShare(TypeUnitNodeEnum::SD_BL_IP, parent);
            newMetaUnSdBlIp->setNum2(num2);
            newMetaUnSdBlIp->setUdpPort(parent->getUdpPort());
            newMetaUnSdBlIp->setUdpAdress(parent->getUdpAdress());
            newMetaUnSdBlIp->setUdpTimeout(parent->getUdpTimeout());
            newMetaUnSdBlIp->setNum1(parent->getNum1());
            newMetaUnSdBlIp->setStateWord(0x41u, parent->getStateWord(0x41u));

            newMetaUnSdBlIp->setName("MetaSD_" + QString::number(newMetaUnSdBlIp->getNum2()));
            newMetaUnSdBlIp->setControl(false);
            newMetaUnSdBlIp->setMetaEntity(1);
            newMetaUnSdBlIp->setPublishedState(10);

            parent->addChild(newMetaUnSdBlIp);
            newMetaUnSdBlIp->setParentUN(parent);

            insertMetaRealUnitNodes(newMetaUnSdBlIp);
            linkDoubles(newMetaUnSdBlIp);

            result = true;
        }
    }
    return result;

}

bool TopologyServiceImpl::inclusiveMetaBLIPIU() {
    //возможное добавление
    bool result = false;
    QSharedPointer<UnitNode> parent = nullptr;
    for(const auto& un : as_const(listMetaRealUnitNodes)) {
        if(un->getParentUN().isNull()
        && TypeUnitNodeEnum::BL_IP == un->getType()) {
            parent = un;
            result = result || inclusiveMetaBLIPIU(parent);
        }
    }
    return result;
}

bool TopologyServiceImpl::inclusiveMetaBLIPIU(QSharedPointer<UnitNode> parent)
{
    //возможное добавление

    if(parent.isNull())
        return false;

    bool result = false;
    for(const auto& num2 : {1,2,3,4}) {
        bool needAddSD = true;
        for(int i = 0, n = parent->childCount(); i < n; i++) {
            auto unChild = parent->child(i);
            if(!unChild.isNull() &&
               TypeUnitNodeEnum::IU_BL_IP == unChild->getType() &&
               unChild->getNum2() == num2 &&
               parent->getUdpPort() == unChild->getUdpPort() &&
               parent->getUdpAdress() == unChild->getUdpAdress()) {
                needAddSD = false;
                break;
            }
        }

        if(needAddSD) {
            auto newMetaUnIuBlIp = UnitNodeFactory::makeShare(TypeUnitNodeEnum::IU_BL_IP, parent);
            newMetaUnIuBlIp->setNum2(num2);
            newMetaUnIuBlIp->setUdpPort(parent->getUdpPort());
            newMetaUnIuBlIp->setUdpAdress(parent->getUdpAdress());
            newMetaUnIuBlIp->setUdpTimeout(parent->getUdpTimeout());
            newMetaUnIuBlIp->setNum1(parent->getNum1());
            newMetaUnIuBlIp->setStateWord(0x41u, parent->getStateWord(0x41u));

            newMetaUnIuBlIp->setName("MetaIU_" + QString::number(newMetaUnIuBlIp->getNum2()));
            newMetaUnIuBlIp->setControl(false);
            newMetaUnIuBlIp->setMetaEntity(1);
            newMetaUnIuBlIp->setPublishedState(10);

            parent->addChild(newMetaUnIuBlIp);
            newMetaUnIuBlIp->setParentUN(parent);

            insertMetaRealUnitNodes(newMetaUnIuBlIp);
            linkDoubles(newMetaUnIuBlIp);

            result = true;
        }
    }
    return result;
}

bool TopologyServiceImpl::inclusiveMetaRLM()
{
    auto result = false;
    for(const auto& un : as_const(listMetaRealUnitNodes)) {
        if(un->getParentUN().isNull()
        && (TypeUnitNodeEnum::RLM_C == un->getType()
         || TypeUnitNodeEnum::RLM_KRL == un->getType())) {
            un->setParentUN(un);
            result = true;
        }
    }
    return result;
}

bool TopologyServiceImpl::inclusiveMetaBaseTG() {

    //возможное добавление

    QSharedPointer<UnitNode> possibleParent = nullptr;
    for(const auto& un : as_const(listMetaRealUnitNodes)) {
        if(un->getParentUN().isNull()
        && (TypeUnitNodeEnum::TG == un->getType())) {
            possibleParent = UnitNodeFactory::makeShare(TypeUnitNodeEnum::TG_Base);
            possibleParent->setType(TypeUnitNodeEnum::TG_Base);

            possibleParent->setUdpAdress(un->getUdpAdress());
            possibleParent->setUdpPort(un->getUdpPort());
            possibleParent->setNum1(un->getNum1());
            possibleParent->setNum2(0);
            possibleParent->setNum3(0);
            possibleParent->setName("MetaBaseTG_" + QString::number(un->getNum1()));
            possibleParent->setControl(false);
            possibleParent->setMetaEntity(1);
        }
    }

    if(!possibleParent.isNull()) {
        for(const auto& un : as_const(listMetaRealUnitNodes)) {
            if(un->getParentUN().isNull()
            && TypeUnitNodeEnum::TG == un->getType()
            && possibleParent->getUdpAdress() == un->getUdpAdress()
            && possibleParent->getUdpPort() == un->getUdpPort()) {
                possibleParent->addChild(un);
                un->setParentUN(possibleParent);
            }
        }

        possibleParent->setPublishedState(10);
        insertMetaRealUnitNodes(possibleParent);
        linkDoubles(possibleParent);

        return true;
    }

    return false;
}

bool TopologyServiceImpl::inclusiveMetaTG()
{
    //возможное добавление
    bool result = false;
    QSharedPointer<UnitNode> parent = nullptr;
    for(const auto& un : as_const(listMetaRealUnitNodes)) {
        if(un->getParentUN().isNull()
        && TypeUnitNodeEnum::TG_Base == un->getType()) {
            parent = un;
            result = result || inclusiveMetaTG(parent);
        }
    }
    return result;

}

bool TopologyServiceImpl::inclusiveMetaTG(QSharedPointer<UnitNode> parent)
{

    if(parent.isNull())
        return false;

    bool result = false;
    for(const auto& num2 : {1,2,3,4}) {
        bool needAddTG = true;
        for(int i = 0, n = parent->childCount(); i < n; i++) {
            auto unChild = parent->child(i);
            if(!unChild.isNull() &&
               TypeUnitNodeEnum::TG == unChild->getType() &&
               unChild->getNum1() == parent->getNum1() &&
               unChild->getNum2() == num2 &&
               parent->getUdpPort() == unChild->getUdpPort() &&
               parent->getUdpAdress() == unChild->getUdpAdress()) {
                needAddTG = false;
                break;
            }
        }

        if(needAddTG) {
            auto newMetaUnTg = UnitNodeFactory::makeShare(TypeUnitNodeEnum::TG, parent);
            newMetaUnTg->setNum2(num2);
            newMetaUnTg->setUdpPort(parent->getUdpPort());
            newMetaUnTg->setUdpAdress(parent->getUdpAdress());
            newMetaUnTg->setUdpTimeout(parent->getUdpTimeout());
            newMetaUnTg->setNum1(parent->getNum1());
            newMetaUnTg->setStateWord(0x41u, parent->getStateWord(0x41u));

            newMetaUnTg->setName("MetaTG_" + QString::number(newMetaUnTg->getNum1()) + "_" + QString::number(newMetaUnTg->getNum2()));
            newMetaUnTg->setControl(false);
            newMetaUnTg->setMetaEntity(1);
            newMetaUnTg->setPublishedState(10);

            parent->addChild(newMetaUnTg);
            newMetaUnTg->setParentUN(parent);

            insertMetaRealUnitNodes(newMetaUnTg);
            linkDoubles(newMetaUnTg);

            result = true;
        }
    }
    return result;

}

//bool TopologyServiceImpl::inclusiveMetaBOD_T4K_M(QSharedPointer<UnitNode> un) {

//    //возможное добавление

//    QSharedPointer<UnitNode> possibleParent = nullptr;
//    for(const auto& un : as_const(listMetaRealUnitNodes)) {
//        if(un->getParentUN().isNull()
//        && TypeUnitNodeEnum::Y4_T4K_M == un->getType()) {
//            possibleParent = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BOD_T4K_M);
//            possibleParent->setType(TypeUnitNodeEnum::BOD_T4K_M);
//            possibleParent->setUdpAdress(un->getUdpAdress());
//            possibleParent->setUdpPort(un->getUdpPort());
//            possibleParent->setName("MetaBOD_T4K_M_" + QString::number(un->getNum1()));
//            possibleParent->setNum1(un->getNum1());
//            possibleParent->setControl(false);
//            possibleParent->setMetaEntity(1);
//            break;
//        } else if(un->getParentUN().isNull()
//               && TypeUnitNodeEnum::DD_T4K_M == un->getType()) {
//            possibleParent = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BOD_T4K_M);
//            possibleParent->setType(TypeUnitNodeEnum::BOD_T4K_M);
//            possibleParent->setUdpAdress(un->getUdpAdress());
//            possibleParent->setUdpPort(un->getUdpPort());
//            possibleParent->setName("MetaBOD_T4K_M");
//            possibleParent->setNum1(un->getNum1());
//            possibleParent->setControl(false);
//            possibleParent->setMetaEntity(1);
//            break;
//        }
//    }

//    if(!possibleParent.isNull()) {
//        for(const auto& un : as_const(listMetaRealUnitNodes)) {
//            if(un->getParentUN().isNull()
//            && TypeUnitNodeEnum::Y4_T4K_M == un->getType()
//            && possibleParent->getNum1() == un->getNum1()
//            && possibleParent->getUdpAdress() == un->getUdpAdress()
//            && possibleParent->getUdpPort() == un->getUdpPort()) {
//                possibleParent->addChild(un);
//                un->setParentUN(possibleParent);
//            }
//        }

//        possibleParent->setPublishedState(10);
//        insertMetaRealUnitNodes(possibleParent);
//        linkDoubles(possibleParent);

//        return true;
//    }

//    return false;
//}

//bool TopologyServiceImpl::inclusiveMetaY4_T4K_M(QSharedPointer<UnitNode> un) {

//    //возможное добавление

//    QSharedPointer<UnitNode> possibleParent = nullptr;
//    for(const auto& un : as_const(listMetaRealUnitNodes)) {
//        if(un->getParentUN().isNull()
//        && TypeUnitNodeEnum::Y4_T4K_M == un->getType()) {
//            possibleParent = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BOD_T4K_M);
//            possibleParent->setType(TypeUnitNodeEnum::BOD_T4K_M);
//            possibleParent->setUdpAdress(un->getUdpAdress());
//            possibleParent->setUdpPort(un->getUdpPort());
//            possibleParent->setName("MetaBOD_T4K_M");
//            possibleParent->setNum1(un->getNum1());
//            possibleParent->setControl(false);
//            possibleParent->setMetaEntity(1);
//            break;
//        } else if(un->getParentUN().isNull()
//               && TypeUnitNodeEnum::DD_T4K_M == un->getType()) {
//            possibleParent = UnitNodeFactory::makeShare(TypeUnitNodeEnum::BOD_T4K_M);
//            possibleParent->setType(TypeUnitNodeEnum::BOD_T4K_M);
//            possibleParent->setUdpAdress(un->getUdpAdress());
//            possibleParent->setUdpPort(un->getUdpPort());
//            possibleParent->setName("MetaBOD_T4K_M");
//            possibleParent->setNum1(un->getNum1());
//            possibleParent->setControl(false);
//            possibleParent->setMetaEntity(1);
//            break;
//        }
//    }

//    if(!possibleParent.isNull()) {
//        for(const auto& un : as_const(listMetaRealUnitNodes)) {
//            if(un->getParentUN().isNull()
//            && TypeUnitNodeEnum::Y4_T4K_M == un->getType()
//            && possibleParent->getNum1() == un->getNum1()
//            && possibleParent->getUdpAdress() == un->getUdpAdress()
//            && possibleParent->getUdpPort() == un->getUdpPort()) {
//                possibleParent->addChild(un);
//                un->setParentUN(possibleParent);
//            }
//        }

//        possibleParent->setPublishedState(10);
//        insertMetaRealUnitNodes(possibleParent);
//        linkDoubles(possibleParent);

//        return true;
//    }

//    return false;}

//bool TopologyServiceImpl::inclusiveMetaDD_T4K_M() {

//    QSet<QPair<QString, int>> pairsAdressPort;
//    for(const auto& un : as_const(listMetaRealUnitNodes)) {
//        pairsAdressPort.insert(QPair<QString, int>(un->getUdpAdress(), un->getUdpPort()));
//    }

//    for(const auto& pairAdressPort : as_const(pairsAdressPort)) {
//        for(int addrBOD = 1, maxAddrBOD = 100; addrBOD <= maxAddrBOD; addrBOD++) {
//            decltype (listMetaRealUnitNodes) exists;
//            for(const auto& un : as_const(listMetaRealUnitNodes)) {
//                if(TypeUnitNodeEnum::DD_T4K_M == un->getType()
//                && addrBOD == un->getNum1()
//                && pairAdressPort.first == un->getUdpAdress()
//                && pairAdressPort.second == un->getUdpPort()) {
//                    exists.insert(un);
//                }
//            }

//            for(int y4t4km = 1, maxy4t4km = 4; y4t4km <= maxy4t4km; y4t4km++) {



//            }
//        }
//    }
//}

//bool TopologyServiceImpl::inclusiveMetaDD_T4K_M(QSharedPointer<UnitNode> un) {

//}


int TopologyServiceImpl::linkDoubles(QSharedPointer<UnitNode> &un) const
{
    int result = 0;
    const QSet<QSharedPointer<UnitNode>> tmp = QSet<QSharedPointer<UnitNode>>::fromList(listTreeUnitNodes)
                                                                             .unite(listMetaRealUnitNodes);

    for(const QSharedPointer<UnitNode> &dblUN : tmp) {
        if(dblUN->getType() == un->getType() &&
                dblUN->getUdpAdress() == un->getUdpAdress() &&
                dblUN->getUdpPort() == un->getUdpPort() &&
//                dblUN->getNum3() == un->getNum3() &&
                dblUN->getNum2() == un->getNum2() &&
                dblUN->getNum1() == un->getNum1() &&
                dblUN != un) {
            un->setDoubles(dblUN->getDoubles());
            un->setDoubles(dblUN);
            dblUN->setDoubles(un->getDoubles());
            dblUN->setDoubles(un);
            result++;
        }
    }
    return result;
}

QSet<QSharedPointer<UnitNode>>::iterator TopologyServiceImpl::insertMetaRealUnitNodes(const QSharedPointer<UnitNode> &value) {
//    qDebug() << "TopologyServiceImpl::insertMetaRealUnitNodes";
    auto it = listMetaRealUnitNodes.insert(value);
    sortedMetaRealUnitNodes = listMetaRealUnitNodes.values();
    std::sort(sortedMetaRealUnitNodes.begin(), sortedMetaRealUnitNodes.end());
    return it;
}

QList<QSharedPointer<UnitNode> > TopologyServiceImpl::getLinkedUI(QSharedPointer<UnitNode> un) const
{
    QList<QSharedPointer<UnitNode> > result;

    auto setMasterUN = un->getDoubles();
    setMasterUN.insert(un);

    QSet<QSharedPointer<UnitNode> > setSlaveUN;
    for(const auto& m : as_const(setMasterUN)) {
        for(const auto& c : as_const(m->listTreeChilds())) {
            auto cun = c.dynamicCast<UnitNode>();
            if(TypeUnitNodeEnum::IU_BL_IP == cun->getType()
            || TypeUnitNodeEnum::SSOI_IU_BL_IP == cun->getType()) {
                setSlaveUN.insert(cun);
                setSlaveUN.unite(cun->getDoubles());
            }
        }
    }

    setSlaveUN = setSlaveUN.intersect(listMetaRealUnitNodes);

    result = setSlaveUN.values();

    return result;
}

QSharedPointer<UnitNode> TopologyServiceImpl::getMetaRealUnitNodes(const QSharedPointer<UnitNode> &target) const
{
    for(const auto& un : as_const(listMetaRealUnitNodes)) {
        if(target->equale(*un.data())) {
            return un;
        }
    }
    return QSharedPointer<UnitNode>();
}

QSharedPointer<UnitNode> TopologyServiceImpl::getMetaRealUnitNodes(UnitNode* target) const
{
    for(auto it = listMetaRealUnitNodes.begin(); it != listMetaRealUnitNodes.end(); it++) {
        const auto& un = *it;
        if(target == un.data()) {
            return un;
        }
    }
    return QSharedPointer<UnitNode>();
}

void TopologyServiceImpl::systemUnitNodesSetDkInvolvedFalse()
{
    for(const auto& un : as_const(sortedMetaRealUnitNodes)) {
        if(un->getDkInvolved())
            return;
    }
    if(!systemUnitNodes.isNull())
        systemUnitNodes->setDkInvolved(false);
}

QSharedPointer<UnitNode> TopologyServiceImpl::getTreeUnitNodes(UnitNode* target) const
{
    for(QSharedPointer<UnitNode> un : as_const(listTreeUnitNodes)) {
        if(target == un.data()) {
            return un;
        }
    }
    return QSharedPointer<UnitNode>();
}

void TopologyServiceImpl::addTreeChildrenToParent(QSharedPointer<UnitNode> child, QSharedPointer<UnitNode> parent)
{
    child->setTreePparent(parent);
    parent->addTreeChildren(child);
}

QSharedPointer<UnitNode> TopologyServiceImpl::findReciver(QSharedPointer<UnitNode> reciver) const {
    if(!reciver.isNull() && !reciver->getParentUN().isNull())
        reciver = reciver->getParentUN();
    while(!reciver.isNull()) {
        if(TypeUnitNodeEnum::BL_IP == reciver->getType()
        || TypeUnitNodeEnum::SSOI_BL_IP == reciver->getType()
        || TypeUnitNodeEnum::RLM_KRL == reciver->getType()
        || TypeUnitNodeEnum::RLM_C == reciver->getType()
        || TypeUnitNodeEnum::TG_Base == reciver->getType()
        || TypeUnitNodeEnum::BOD_T4K_M == reciver->getType()
        || TypeUnitNodeEnum::BOD_SOTA == reciver->getType()) {
            return reciver;
        }
        reciver = reciver->getParentUN();
    }
    return reciver;
}

QSet<QSharedPointer<UnitNode>> TopologyServiceImpl::findChild(QSharedPointer<UnitNode> parent) const {
    auto getChildsLikeSet = [](QSharedPointer<UnitNode> someParebt) {
        return someParebt->getListChilde().toSet();
    };

    auto childs = getChildsLikeSet(parent);

    auto oldSizeChilds = childs.size();
    auto newSizeChilds = oldSizeChilds;
    do {
        oldSizeChilds = childs.size();
        decltype (childs) appendChilds;
        for(const auto& child : as_const(childs)) {
            appendChilds.unite(getChildsLikeSet(child));
        }
        childs.unite(appendChilds);
        newSizeChilds = oldSizeChilds;
    } while(oldSizeChilds < newSizeChilds);

    return childs;
}

QSet<QSharedPointer<UnitNode>> TopologyServiceImpl::findChildByType(int type, QSharedPointer<UnitNode> parent) const {
    auto childs = findChild(parent);

    for(auto it = childs.begin(); it != childs.end();) {
        const auto& un = *it;
        if(type != un->getType()) {
            it = childs.erase(it);
        } else {
            ++it;
        }
    }

    return childs;
}

QSharedPointer<UnitNode> TopologyServiceImpl::findParentByType(int type, QSharedPointer<UnitNode> parent) const {
    if(!parent.isNull() && !parent->getParentUN().isNull())
        parent = parent->getParentUN();
    while(!parent.isNull()) {
        if(type == parent->getType()) {
            return parent;
        }
        parent = parent->getParentUN();
    }
    return parent;
}

QSet<QSharedPointer<UnitNode> > TopologyServiceImpl::findeSetAutoOnOffUN(const QSharedPointer<UnitNode> &un)
{
    QSet<QSharedPointer<UnitNode> > unSetTmp;
    if(TypeUnitNodeEnum::IU_BL_IP != un->getType()
    && TypeUnitNodeEnum::SSOI_IU_BL_IP != un->getType()) {
        return unSetTmp;
    }
    unSetTmp.insert(un);
    unSetTmp = unSetTmp + un->getDoubles();
    for(auto it = unSetTmp.begin(); it != unSetTmp.end();) {
        const auto& unDouble = *it;
        //qDebug() << "itr :" << unSetTmp;
        //qDebug() << "fnd :" << unDouble << unDouble->getMetaNames() << unDouble->getName();
        if(!unDouble->treeParent().isNull()) {
            if(TypeUnitNodeEnum::SD_BL_IP == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()
            || TypeUnitNodeEnum::SSOI_SD_BL_IP == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()
            || TypeUnitNodeEnum::RLM_KRL == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()
            || TypeUnitNodeEnum::RLM_C == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()
            || TypeUnitNodeEnum::TG == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()
            || TypeUnitNodeEnum::DD_SOTA == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()
            || TypeUnitNodeEnum::DD_T4K_M == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()) {
                //qDebug() << "trg :"<< unDouble->getMetaNames() << unDouble->toString();
                it++;
                continue;
            } else {
                it = unSetTmp.erase(it);
                continue;
            }
        } else {
            it = unSetTmp.erase(it);
            continue;
        }
        it++;
    }
//    //qDebug() << "res :" << unSetTmp;
    return unSetTmp;
}


