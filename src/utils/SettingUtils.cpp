#include <SettingUtils.h>

#include <QSettings>
#include <QDebug>

#include <Utils.h>
#include <global.h>
#include<QTextCodec>
#include<control_unit_manager.h>

SettingUtils::SettingUtils()
{

}

QList<UnitNode *> SettingUtils::listTreeUnitNodes;
QSet<UnitNode *> SettingUtils::listMetaRealUnitNodes;

QList<UnitNode *> SettingUtils::loadTreeUnitNodes(TreeModelUnitNode *model,UnitNode * root, QString fileName)
{
    Control_Unit_Manager* m_ctrl=new Control_Unit_Manager();
    if(!getListTreeUnitNodes().isEmpty()) {
        getListTreeUnitNodes().clear();
    }
    QSettings settings(fileName, QSettings::IniFormat);


    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
     QTextCodec::setCodecForLocale(codec);
   settings.setIniCodec(codec);

    settings.beginGroup("TREE");


    int cntTrItm = settings.value( "Count", -1 ).toInt();
    settings.endGroup();


    root->setDK(0);
    root->setAlarmMsgOn(0);

    //qDebug() << "cntTrItm" << cntTrItm;
    if(0 >= cntTrItm)
        return getListTreeUnitNodes();

/*
#if (defined (_WIN32) || defined (_WIN64))
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);

 settings.setIniCodec(codec);
//    settings.setIniCodec( "Windows-1251" );
#else
    settings.setIniCodec( "UTF-8" );
#endif
*/



    {
        UnitNode * tmpUN = UnitNodeFactory::make(TypeUnitNode::SYSTEM, root);

        tmpUN->setType(TypeUnitNode::SYSTEM);
        tmpUN->setNum1(0);
        tmpUN->setNum2(0);
        tmpUN->setNum3(0);
        tmpUN->setLevel(0);
        tmpUN->setName(QObject::tr("Система"));
        tmpUN->setMetaNames("Obj_0");

        root->addTreeChild(tmpUN);
        root = tmpUN;
        listTreeUnitNodes.append(tmpUN);
    }

    for(int index = 0; index < cntTrItm; index++)
    {
        QString strGroup("Obj_%1");
        strGroup = strGroup.arg(index + 1);
        if(settings.childGroups().contains(strGroup))
        {
            settings.beginGroup(strGroup);
            UnitNode * tmpUN = UnitNodeFactory::make((TypeUnitNode)settings.value( "Type" , -1 ).toInt(), root);
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
                UnitNode* old;
                //Вот здесь даем юниту папу но не говорим папе у него есть юнит
                bool key = true;
                for (auto rit = listTreeUnitNodes.rbegin(); rit != getListTreeUnitNodes().rend(); ++rit) {
                    if((*rit)->getLevel() < tmpUN->getLevel())
                    {

                        old=(*rit);
                        key = false;
                        break;
                    }
                }

                if(key)
                    old=root;

                 tmpUN->setTreeParentUN(old);


                bool res=m_ctrl->pass_to_add(tmpUN,old,model);//вот для этой проверки
                if(res)//если юнит прошел проверку
                {

                    old->addTreeChild(tmpUN);



                    listTreeUnitNodes.append(tmpUN);
                }

                else
                {
                    listTreeUnitNodes.clear();
                    model->rootItemUN->deleteAll();

                    return listTreeUnitNodes;
                }

                //Double
                /*for(UnitNode * un : as_const(getListTreeUnitNodes())) {
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
                }*/

               /* if(!tmpUN->getDoubles().isEmpty()) {
                    tmpUN->setParentUN(tmpUN->getDoubles().values().first()->getParentUN());
                } else if(tmpUN->getDoubles().isEmpty() &&
                        (TypeUnitNode::SD_BL_IP == tmpUN->getType() ||
                        TypeUnitNode::IU_BL_IP == tmpUN->getType() ||
                        TypeUnitNode::RLM_C == tmpUN->getType() ||
                        TypeUnitNode::RLM_KRL == tmpUN->getType() ||
                        TypeUnitNode::TG == tmpUN->getType())) {
                    key = true;
                    UnitNode * tmpParentUN = UnitNodeFactory::make(TypeUnitNode::BL_IP);
                    tmpParentUN->setType(TypeUnitNode::BL_IP);
                    tmpParentUN->setUdpAdress(tmpUN->getUdpAdress());
                    tmpParentUN->setUdpPort(tmpUN->getUdpPort());

                    auto li = getSetMetaRealUnitNodes().values();
                    for (auto rit = li.rbegin(); rit != li.rend(); ++rit) {
                        auto it = static_cast<UnitNode *>(*rit);
                        if(it->getUdpAdress() == tmpParentUN->getUdpAdress() &&
                                it->getUdpPort() == tmpParentUN->getUdpPort())
                        {
                            if(TypeUnitNode::BL_IP == it->getType()) {
                                it->addChild(tmpUN);
                                key = false;
                                break;
                            } else if(nullptr != it->getParentUN()) {
                                if(TypeUnitNode::BL_IP == it->getParentUN()->getType()) {
                                    it->getParentUN()->addChild(tmpUN);
                                    key = false;
                                    break;
                                }
                            }
                        }
                    }

                    if(key) {
                        getSetMetaRealUnitNodes().insert(tmpParentUN);
                        tmpParentUN->addChild(tmpUN);
                    }



                    getSetMetaRealUnitNodes().insert(tmpUN);
                }*/

            }
        }
    }

    /*for(UnitNode * un : as_const(SettingUtils::getSetMetaRealUnitNodes().toList())) {
        if(TypeUnitNode::SD_BL_IP == un->getType() && nullptr != un->getParentUN() && 1 <= un->getNum1() && 4 >= un->getNum1()) {
            auto parent = un->getParentUN();
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
                auto newMetaUnIuBlIp = UnitNodeFactory::make(TypeUnitNode::IU_BL_IP, parent);
                newMetaUnIuBlIp->setNum2(un->getNum2());
                newMetaUnIuBlIp->setUdpPort(un->getUdpPort());
                newMetaUnIuBlIp->setUdpAdress(un->getUdpAdress());
                newMetaUnIuBlIp->setUdpTimeout(un->getUdpTimeout());
                newMetaUnIuBlIp->setNum1(un->getNum1());
                newMetaUnIuBlIp->setStateWord(un->getStateWord());

                newMetaUnIuBlIp->setName("MetaIU_" + QString::number(newMetaUnIuBlIp->getNum2()));
                newMetaUnIuBlIp->setControl(false);

                SettingUtils::getSetMetaRealUnitNodes().insert(newMetaUnIuBlIp);
                parent->addChild(newMetaUnIuBlIp);
            }
        }
    }*/

    return getListTreeUnitNodes();
}

QList<UnitNode *> SettingUtils::loadEmptyTree(UnitNode *root)
{
    if(!getListTreeUnitNodes().isEmpty()) {
   //     for(UnitNode *un : getListTreeUnitNodes())
   //         delete un;
        getListTreeUnitNodes().clear();
        root->deleteAll();
        root->setDK(0);
        root->setAlarmMsgOn(0);
    }




    {
        UnitNode * tmpUN = UnitNodeFactory::make(TypeUnitNode::SYSTEM, root);

        tmpUN->setType(TypeUnitNode::SYSTEM);
        tmpUN->setNum1(0);
        tmpUN->setNum2(0);
        tmpUN->setNum3(0);
        tmpUN->setLevel(0);
        tmpUN->setName(QObject::tr("Система"));
        tmpUN->setMetaNames("Obj_0");

        root->addTreeChild(tmpUN);
//        root = tmpUN;
        getListTreeUnitNodes().append(tmpUN);


    }

      return getListTreeUnitNodes();
}

QList<UnitNode *> & SettingUtils::getListTreeUnitNodes() {
    return SettingUtils::listTreeUnitNodes;
}

QSet<UnitNode *> & SettingUtils::getSetMetaRealUnitNodes() {
    return SettingUtils::listMetaRealUnitNodes;
}

QVariant SettingUtils::getValueSettings(const QString key, const QString group, const QString fileName)
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

bool SettingUtils::loadTreeUnitNodes(UnitNode */*root*/, UnitNode */*unit*/)
{
//    //qDebug()<<"SettingUtils::loadTreeUnitNodes";
    return true;
}
