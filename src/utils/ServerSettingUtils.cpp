#include <ServerSettingUtils.h>

#include <QSettings>
#include <QDebug>
#include <UnitNodeFactory.h>
#include <Utils.h>
#include <global.h>
#include <QTextCodec>

ServerSettingUtils::ServerSettingUtils()
{

}

QList<QSharedPointer<UnitNode> > ServerSettingUtils::listTreeUnitNodes;
QSet<QSharedPointer<UnitNode> > ServerSettingUtils::listMetaRealUnitNodes;

QList<QSharedPointer<UnitNode> > ServerSettingUtils::loadTreeUnitNodes(QSharedPointer<UnitNode> root, QString fileName) {
    if(!getListTreeUnitNodes().isEmpty()) {
        getListTreeUnitNodes().clear();
    }
    QSettings settings(fileName, QSettings::IniFormat);

    settings.beginGroup("TREE");
    int cntTrItm = settings.value( "Count", -1 ).toInt();
    settings.endGroup();



    //qDebug() << "cntTrItm" << cntTrItm;
    if(0 >= cntTrItm)
        return getListTreeUnitNodes();

/*
#if (defined (_WIN32) || defined (_WIN64))
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);
#else
    settings.setIniCodec( "UTF-8" );
#endif
*/
    //Для совместимости. со старым. конфигуратором.
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);

    {
        QSharedPointer<UnitNode> tmpUN = UnitNodeFactory::makeShare(TypeUnitNode::SYSTEM, root);

        tmpUN->setType(TypeUnitNode::SYSTEM);
        tmpUN->setNum1(0);
        tmpUN->setNum2(0);
        tmpUN->setNum3(0);
        tmpUN->setLevel(0);
        tmpUN->setName(QObject::tr("Система"));
        tmpUN->setMetaNames("Obj_0");

        root->addTreeChild(tmpUN);
        tmpUN->setTreeParentUN(root);
        root = tmpUN;
        getListTreeUnitNodes().append(QSharedPointer<UnitNode>(tmpUN));
    }

    for(int index = 0; index < cntTrItm; index++)
    {
        QString strGroup("Obj_%1");
        strGroup = strGroup.arg(index + 1);
        if(settings.childGroups().contains(strGroup))
        {
            settings.beginGroup(strGroup);
            QSharedPointer<UnitNode> tmpUN = UnitNodeFactory::makeShare((TypeUnitNode)settings.value( "Type" , -1 ).toInt(), root);
            tmpUN->setMetaNames(strGroup);

            tmpUN->setType(settings.value( "Type" , -1 ).toInt());
            tmpUN->setNum1(settings.value( "Num1" , -1 ).toInt());
            tmpUN->setNum2(settings.value( "Num2" , -1 ).toInt());
            tmpUN->setNum3(settings.value( "Num3" , -1 ).toInt());
            tmpUN->setLevel(settings.value( "Level" , -1 ).toInt());
            tmpUN->setName(settings.value( "Name" , -1 ).toByteArray());
            tmpUN->setIconVisible(settings.value( "IconVisible" , -1 ).toInt());
            tmpUN->setX(settings.value( "X" , -1 ).toInt());
            tmpUN->setY(settings.value( "Y" , -1 ).toInt());
            tmpUN->setDK(settings.value( "DK" , -1 ).toInt());
            tmpUN->setBazalt(settings.value( "Bazalt" , -1 ).toInt());
            tmpUN->setMetka(settings.value( "Metka" , -1 ).toInt());
            tmpUN->setRazriv(settings.value( "Razriv" , -1 ).toInt());
            tmpUN->setAdamOff(settings.value( "AdamOff" , -1 ).toInt());
            tmpUN->setAlarmMsgOn(settings.value( "AlarmMsgOn" , -1 ).toInt());
            tmpUN->setConnectBlock(settings.value( "ConnectBlock" , -1 ).toInt());
            tmpUN->setOutType(settings.value( "OutType" , -1 ).toInt());
            tmpUN->setAsoosd_kk(settings.value( "asoosd_kk" , -1 ).toInt());
            tmpUN->setAsoosd_nn(settings.value( "asoosd_nn" , -1 ).toInt());
            tmpUN->setDescription(settings.value( "Description" , -1 ).toString());
            tmpUN->setLan(settings.value( "lan" , -1 ).toInt());
            tmpUN->setLon(settings.value( "lon" , -1 ).toInt());
            tmpUN->setUdpUse(settings.value( "UdpUse" , -1 ).toInt());
            tmpUN->setUdpAdress(settings.value( "UdpAdress" , -1 ).toString());
            tmpUN->setUdpPort(settings.value( "UpdPort" , -1 ).toInt());
            tmpUN->setMetka1Time_0(settings.value( "Metka1Time_0" , -1 ).toInt());
            tmpUN->setMetka1Time_1(settings.value( "Metka1Time_1" , -1 ).toInt());
            tmpUN->setMetka2Time_0(settings.value( "Metka2Time_0" , -1 ).toInt());
            tmpUN->setMetka2Time_1(settings.value( "Metka2Time_1" , -1 ).toInt());
            tmpUN->setMetka3Time_0(settings.value( "Metka3Time_0" , -1 ).toInt());
            tmpUN->setMetka3Time_1(settings.value( "Metka3Time_1" , -1 ).toInt());
            tmpUN->setMetka4Time_0(settings.value( "Metka4Time_0" , -1 ).toInt());
            tmpUN->setMetka4Time_1(settings.value( "Metka4Time_1" , -1 ).toInt());
            tmpUN->setMetkaDopuskTime_0(settings.value( "MetkaDopuskTime_0" , -1 ).toInt());
            tmpUN->setMetkaDopuskTime_1(settings.value( "MetkaDopuskTime_1" , -1 ).toInt());
            tmpUN->setUdpTimeout(settings.value( "UdpTimeout" , 50 ).toInt());

            if(settings.value("Icon1Path").isValid())
             tmpUN->setIcon1Path(settings.value( "Icon1Path" , -1 ).toString());

            if(settings.value("Icon2Path").isValid())
             tmpUN->setIcon2Path(settings.value( "Icon2Path" , -1 ).toString());

            if(settings.value("Icon3Path").isValid())
             tmpUN->setIcon3Path(settings.value( "Icon3Path" , -1 ).toString());

            if(settings.value("Icon4Path").isValid())
             tmpUN->setIcon4Path(settings.value( "Icon4Path" , -1 ).toString());

            settings.endGroup();

            if(!tmpUN->getName().isEmpty())
            {
//                qDebug() << tmpUN->metaName << tmpUN->toString();
                getListTreeUnitNodes().append(QSharedPointer<UnitNode>(tmpUN));
                bool key = true;
                for (auto rit = getListTreeUnitNodes().rbegin(); rit != getListTreeUnitNodes().rend(); ++rit) {
                    if((*rit)->getLevel() < tmpUN->getLevel())
                    {
                        (*rit)->addTreeChild(tmpUN);
                        tmpUN->setTreeParentUN((*rit));
                        key = false;
                        break;
                    }
                }

                if(key) {
                    root->addTreeChild(tmpUN);
                    tmpUN->setTreeParentUN(root);
                }

                //Double
                for(QSharedPointer<UnitNode> un : as_const(getListTreeUnitNodes())) {
                    if(un->getType() == tmpUN->getType() &&
                            un->getUdpAdress() == tmpUN->getUdpAdress() &&
                            un->getUdpPort() == tmpUN->getUdpPort() &&
                            un->getNum3() == tmpUN->getNum3() &&
                            un->getNum2() == tmpUN->getNum2() &&
                            un->getNum1() == tmpUN->getNum1() &&
                            un != tmpUN) {
//                        tmpUN->setMetaNames(un->getMetaNames());
//                        un->setMetaNames(tmpUN->getMetaNames());

                        tmpUN->setDoubles(un->getDoubles());
                        tmpUN->setDoubles(un);
                        un->setDoubles(tmpUN->getDoubles());
                        un->setDoubles(tmpUN);
                    }
                }



                if(!tmpUN->getDoubles().isEmpty()) {
                    tmpUN->setParentUN(tmpUN->getDoubles().values().first()->getParentUN());
                } else if(tmpUN->getDoubles().isEmpty() &&
                        (TypeUnitNode::SD_BL_IP == tmpUN->getType() ||
                        TypeUnitNode::IU_BL_IP == tmpUN->getType() ||
                        TypeUnitNode::RLM_C == tmpUN->getType() ||
                        TypeUnitNode::RLM_KRL == tmpUN->getType() ||
                        TypeUnitNode::TG == tmpUN->getType())) {
                    key = true;

                    QSharedPointer<UnitNode> tmpParentUN;// = UnitNodeFactory::make(TypeUnitNode::BL_IP);
                    for(QSharedPointer<UnitNode> parentUN : as_const(getSetMetaRealUnitNodes().toList())) {
                        if(parentUN->getType() == TypeUnitNode::BL_IP &&
                           parentUN->getUdpAdress() == tmpUN->getUdpAdress() &&
                           parentUN->getUdpPort() == tmpUN->getUdpPort()) {
                            tmpParentUN = parentUN;
                            break;
                        }
                    }
                    if(tmpParentUN.isNull()){
                        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNode::BL_IP);
                        tmpParentUN->setType(TypeUnitNode::BL_IP);
                        tmpParentUN->setUdpAdress(tmpUN->getUdpAdress());
                        tmpParentUN->setUdpPort(tmpUN->getUdpPort());
                        \
                        getSetMetaRealUnitNodes().insert(tmpParentUN);
                    }

                    auto li = getSetMetaRealUnitNodes().values();
                    for (auto rit = li.rbegin(); rit != li.rend(); ++rit) {
                        auto it = static_cast<QSharedPointer<UnitNode> >(*rit);
                        if(it->getUdpAdress() == tmpParentUN->getUdpAdress() &&
                                it->getUdpPort() == tmpParentUN->getUdpPort())
                        {
                            if(TypeUnitNode::BL_IP == it->getType()) {
                                it->addChild(tmpUN);
                                tmpUN->setParentUN(it);
                                key = false;
                                break;
                            } else if(nullptr != it->getParentUN()) {
                                if(TypeUnitNode::BL_IP == it->getParentUN()->getType()) {
                                    it->getParentUN()->addChild(tmpUN);
                                    tmpUN->setParentUN(it);
                                    key = false;
                                    break;
                                }
                            }
                        }
                    }

                    if(key) {
                        getSetMetaRealUnitNodes().insert(tmpParentUN);
                        tmpParentUN->addChild(tmpUN);
                        tmpUN->setParentUN(tmpParentUN);
                    }

                    getSetMetaRealUnitNodes().insert(tmpUN);
                }

            }
        }
    }

    for(QSharedPointer<UnitNode> un : as_const(ServerSettingUtils::getSetMetaRealUnitNodes().toList())) {
        if(TypeUnitNode::SD_BL_IP == un->getType() && nullptr != un->getParentUN() && 1 <= un->getNum1() && 4 >= un->getNum1()) {
            QSharedPointer<UnitNode> parent = un->getParentUN();
            bool needAddUI = true;
            for(int i = 0, n = parent->childCount(); i < n; i++) {
                auto unChild = parent->child(i);
                if(nullptr != unChild &&
                   TypeUnitNode::IU_BL_IP == unChild->getType() &&
                   un->getNum2() == unChild->getNum2() &&
                   un->getUdpPort() == unChild->getUdpPort() &&
                   un->getUdpAdress() == unChild->getUdpAdress()) {
                    needAddUI = false;
                    break;
                }
            }

            if(needAddUI) {
                QSharedPointer<UnitNode> newMetaUnIuBlIp = UnitNodeFactory::makeShare(TypeUnitNode::IU_BL_IP, parent);
                newMetaUnIuBlIp->setNum2(un->getNum2());
                newMetaUnIuBlIp->setUdpPort(un->getUdpPort());
                newMetaUnIuBlIp->setUdpAdress(un->getUdpAdress());
                newMetaUnIuBlIp->setUdpTimeout(un->getUdpTimeout());
                newMetaUnIuBlIp->setNum1(un->getNum1());
                newMetaUnIuBlIp->setStateWord(un->getStateWord());

                newMetaUnIuBlIp->setName("MetaIU_" + QString::number(newMetaUnIuBlIp->getNum2()));
                newMetaUnIuBlIp->setControl(false);

                ServerSettingUtils::getSetMetaRealUnitNodes().insert(newMetaUnIuBlIp);
                parent->addChild(newMetaUnIuBlIp);
                newMetaUnIuBlIp->setParentUN(parent);
            }
        }
    }

    return getListTreeUnitNodes();
}

QList<QSharedPointer<UnitNode> > ServerSettingUtils::loadEmptyTree(QSharedPointer<UnitNode> root)
{
    if(!getListTreeUnitNodes().isEmpty()) {
   //     for(UnitNode*un : getListTreeUnitNodes())
   //         delete un;
        getListTreeUnitNodes().clear();
        root->deleteAll();
    }




    {
        QSharedPointer<UnitNode> tmpUN = UnitNodeFactory::makeShare(TypeUnitNode::SYSTEM, root);

        tmpUN->setType(TypeUnitNode::SYSTEM);
        tmpUN->setNum1(0);
        tmpUN->setNum2(0);
        tmpUN->setNum3(0);
        tmpUN->setLevel(0);
        tmpUN->setName(QObject::tr("Система"));
        tmpUN->setMetaNames("Obj_0");

        root->addTreeChild(tmpUN);
        tmpUN->setTreeParentUN(root);
//        root = tmpUN;
        getListTreeUnitNodes().append(tmpUN);


    }

      return getListTreeUnitNodes();
}

QList<QSharedPointer<UnitNode> > & ServerSettingUtils::getListTreeUnitNodes() {
    return ServerSettingUtils::listTreeUnitNodes;
}

QSharedPointer<UnitNode> ServerSettingUtils::getTreeUnitNodes(UnitNode* target)
{
    for(QSharedPointer<UnitNode> & un : getListTreeUnitNodes()) {
        if(target == un.data()) {
            return un;
        }
    }
    return QSharedPointer<UnitNode>();
}


QSet<QSharedPointer<UnitNode> > & ServerSettingUtils::getSetMetaRealUnitNodes() {
    return ServerSettingUtils::listMetaRealUnitNodes;
}

QSharedPointer<UnitNode> ServerSettingUtils::getMetaRealUnitNodes(UnitNode* target)
{
    for(QSharedPointer<UnitNode> & un : getSetMetaRealUnitNodes().toList()) {
        if(target == un.data()) {
            return un;
        }
    }
    return QSharedPointer<UnitNode>();
}

QVariant ServerSettingUtils::getValueSettings(const QString key, const QString group, const QString fileName)
{
    QVariant result;

    QSettings settings(fileName, QSettings::IniFormat);
#if (defined (_WIN32) || defined (_WIN64))
    settings.setIniCodec( "Windows-1251" );
#else
    settings.setIniCodec( "UTF-8" );
#endif

    if(!settings.childGroups().contains(group))
        return result;

    settings.beginGroup(group);
    if(!settings.childKeys().contains(key))
        return result;
    result = settings.value( key, -1 );
    settings.endGroup();

    return result;
}

bool ServerSettingUtils::loadTreeUnitNodes(UnitNode*/*root*/, UnitNode*/*unit*/)
{
//    //qDebug()<<"SettingUtils::loadTreeUnitNodes";
    return true;
}
