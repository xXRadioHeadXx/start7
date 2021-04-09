#include <ServerSettingUtils.h>

#include <QSettings>
#include <QDebug>
#include <UnitNodeFactory.h>
#include <Utils.h>
#include <global.h>
#include <QTextCodec>
#include <TreeItem.h>
#include <SimpleIni.h>

ServerSettingUtils::ServerSettingUtils()
{

}

QList<QSharedPointer<UnitNode> > ServerSettingUtils::listTreeUnitNodes;
QSet<QSharedPointer<UnitNode> > ServerSettingUtils::listMetaRealUnitNodes;

QList<QSharedPointer<UnitNode> > ServerSettingUtils::loadTreeUnitNodes(QSharedPointer<UnitNode> root, QString fileName) {
    if(!getListTreeUnitNodes().isEmpty()) {
        getListTreeUnitNodes().clear();
    }

    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

    CSimpleIniA ini;
    QString filePath = QCoreApplication::applicationDirPath() + "/rifx.ini";
    ini.LoadFile(filePath.toStdString().c_str());

    int cntTrItm = codec->toUnicode(ini.GetValue("TREE", "Count")).toInt();

    if(0 >= cntTrItm)
        return getListTreeUnitNodes();

    {
        QSharedPointer<UnitNode> tmpUN = UnitNodeFactory::makeShare(TypeUnitNode::SYSTEM, root);

        tmpUN->setType(TypeUnitNode::SYSTEM);
        tmpUN->setNum1(0);
        tmpUN->setNum2(0);
        tmpUN->setNum3(0);
        tmpUN->setLevel(0);
        tmpUN->setName(QObject::tr("Система"));
        tmpUN->setMetaNames("Obj_0");

        ServerUnitNodeTreeItem::addTreeChildrenToParent(tmpUN, root);
        root = tmpUN;
        getListTreeUnitNodes().append(QSharedPointer<UnitNode>(tmpUN));
    }

    for(int index = 0; index < cntTrItm; index++)
    {
        QString strGroup("Obj_%1");
        strGroup = strGroup.arg(index + 1);
        if(0 != ini.GetSection(strGroup.toStdString().c_str())) {
            QSharedPointer<UnitNode> tmpUN = UnitNodeFactory::makeShare((TypeUnitNode)codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Type")).toInt(), root);
            tmpUN->setMetaNames(strGroup);

            tmpUN->setType(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Type")).toInt());
            tmpUN->setNum1(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Num1")).toInt());
            tmpUN->setNum2(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Num2")).toInt());
            tmpUN->setNum3(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Num3")).toInt());
            tmpUN->setLevel(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Level")).toInt());
            tmpUN->setName(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Name")));
            tmpUN->setIconVisible(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "IconVisible")).toInt());
            tmpUN->setX(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "X")).toInt());
            tmpUN->setY(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Y")).toInt());
            tmpUN->setDK(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "DK")).toInt());
            tmpUN->setBazalt(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Bazalt")).toInt());
            tmpUN->setMetka(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Metka")).toInt());
            tmpUN->setRazriv(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Razriv")).toInt());
            tmpUN->setAdamOff(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "AdamOff")).toInt());
            tmpUN->setAlarmMsgOn(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "AlarmMsgOn")).toInt());
            tmpUN->setConnectBlock(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "ConnectBlock")).toInt());
            tmpUN->setOutType(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "OutType")).toInt());
            tmpUN->setAsoosd_kk(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "asoosd_kk")).toInt());
            tmpUN->setAsoosd_nn(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "asoosd_nn")).toInt());
            tmpUN->setDescription(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Description")));
            tmpUN->setLan(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "lan")).toInt());
            tmpUN->setLon(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "lon")).toInt());
            tmpUN->setUdpUse(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "UdpUse")).toInt());
            tmpUN->setUdpAdress(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "UdpAdress")));
            tmpUN->setUdpPort(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "UpdPort")).toInt());
            tmpUN->setMetka1Time_0(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Metka1Time_0")).toInt());
            tmpUN->setMetka1Time_1(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Metka1Time_1")).toInt());
            tmpUN->setMetka2Time_0(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Metka2Time_0")).toInt());
            tmpUN->setMetka2Time_1(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Metka2Time_1")).toInt());
            tmpUN->setMetka3Time_0(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Metka3Time_0")).toInt());
            tmpUN->setMetka3Time_1(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Metka3Time_1")).toInt());
            tmpUN->setMetka4Time_0(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Metka4Time_0")).toInt());
            tmpUN->setMetka4Time_1(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Metka4Time_1")).toInt());
            tmpUN->setMetkaDopuskTime_0(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "MetkaDopuskTime_0")).toInt());
            tmpUN->setMetkaDopuskTime_1(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "MetkaDopuskTime_1")).toInt());
            tmpUN->setUdpTimeout(qMax(50, codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "UdpTimeout")).toInt()));

            tmpUN->setIcon1Path(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Icon1Path")));
            tmpUN->setIcon2Path(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Icon2Path")));
            tmpUN->setIcon3Path(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Icon3Path")));
            tmpUN->setIcon4Path(codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Icon4Path")));


            if(!tmpUN->getName().isEmpty())
            {
//                qDebug() << tmpUN->metaName << tmpUN->toString();
                getListTreeUnitNodes().append(QSharedPointer<UnitNode>(tmpUN));
                bool key = true;
                for (auto rit = getListTreeUnitNodes().rbegin(); rit != getListTreeUnitNodes().rend(); ++rit) {
                    if((*rit)->getLevel() < tmpUN->getLevel())
                    {
                        ServerUnitNodeTreeItem::addTreeChildrenToParent(tmpUN, (*rit));
                        key = false;
                        break;
                    }
                }

                if(key) {
                    ServerUnitNodeTreeItem::addTreeChildrenToParent(tmpUN, root);
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

    for(auto un : getListTreeUnitNodes())
        qDebug() << un->toString();

    return getListTreeUnitNodes();
}

QList<QSharedPointer<UnitNode> > ServerSettingUtils::loadEmptyTree(QSharedPointer<UnitNode> root)
{
    if(!getListTreeUnitNodes().isEmpty()) {
   //     for(UnitNode*un : getListTreeUnitNodes())
   //         delete un;
        getListTreeUnitNodes().clear();
        root->removeAllTreeChildren();
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

        ServerUnitNodeTreeItem::addTreeChildrenToParent(tmpUN, root);
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