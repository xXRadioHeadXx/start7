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

ServerSettingUtils::ServerSettingUtils()
{

}

QList<QSharedPointer<UnitNode> > ServerSettingUtils::listTreeUnitNodes;
QSet<QSharedPointer<UnitNode> > ServerSettingUtils::listMetaRealUnitNodes;

QList<QSharedPointer<UnitNode> > ServerSettingUtils::getLinkedUI(QSharedPointer<UnitNode> un)
{
    QList<QSharedPointer<UnitNode> > result;

    auto setMasterUN = un->getDoubles();
    setMasterUN.insert(un);

    QSet<QSharedPointer<UnitNode> > setSlaveUN;
    for(const auto &m : as_const(setMasterUN)) {
        for(const auto &c : as_const(m->listTreeChilds())) {
            auto cun = c.dynamicCast<UnitNode>();
            if(TypeUnitNode::IU_BL_IP == cun->getType()) {
                setSlaveUN.insert(cun);
            }
        }
    }

    setSlaveUN.intersect(ServerSettingUtils::getSetMetaRealUnitNodes());

    result = setSlaveUN.values();

    return result;
}

int ServerSettingUtils::linkDoubles(QSharedPointer<UnitNode> &un)
{
    int result = 0;
    for(const QSharedPointer<UnitNode> &dblUN : as_const(getListTreeUnitNodes())) {
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

QList<QSharedPointer<UnitNode> > ServerSettingUtils::loadTreeUnitNodes(QSharedPointer<UnitNode> root, QString fileName) {
    qDebug() << "ServerSettingUtils::loadTreeUnitNodes -->";
    if(!getListTreeUnitNodes().isEmpty()) {
        getListTreeUnitNodes().clear();
    }

    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

    CSimpleIniA ini;
    QString filePath = (fileName.isEmpty() ? QCoreApplication::applicationDirPath() + "/rifx.ini" : fileName);
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

        qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " parse";

        if(0 != ini.GetSection(strGroup.toStdString().c_str())) {
            QSharedPointer<UnitNode> tmpUN = UnitNodeFactory::makeShare((TypeUnitNode)codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Type")).toInt(), root);
            tmpUN->setMetaNames(strGroup);

            QString isEnable = codec->toUnicode(ini.GetValue(strGroup.toStdString().c_str(), "Enable"));
            if("false" == isEnable) {
                qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " disabled";
                continue;
            }

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
                qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " parse successfully " << tmpUN->toString();
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

                //Double паходим дубли
                ServerSettingUtils::linkDoubles(tmpUN);

                key = false;

                if(!tmpUN->getDoubles().isEmpty()) {

                    QSharedPointer<UnitNode> posybleParent;
                    for(const auto &dbl : as_const(tmpUN->getDoubles().values())) {
                        auto posybleParent = UnitNode::findReciver(dbl);
                        if(!posybleParent.isNull()) {
                            tmpUN->setParentUN(posybleParent);
                            qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " set parrent " << tmpUN->toString() << " parent " << tmpUN->getParentUN()->toString();
                            break;
                        }
                    }
                } else if(tmpUN->getDoubles().isEmpty() &&
                          (TypeUnitNode::RLM_C == tmpUN->getType() ||
                           TypeUnitNode::RLM_KRL == tmpUN->getType())) {

//                    tmpUN->addChild(tmpUN);
                    tmpUN->setParentUN(tmpUN);
                    qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " insert " << tmpUN->toString() << " parent " << tmpUN->getParentUN()->toString();
                    getSetMetaRealUnitNodes().insert(tmpUN);

                } else if(tmpUN->getDoubles().isEmpty() &&
                        (TypeUnitNode::SD_BL_IP == tmpUN->getType() ||
                        TypeUnitNode::IU_BL_IP == tmpUN->getType())) {
                    key = true;

                    QSharedPointer<UnitNode> tmpParentUN;
                    // find reciver in meta set
                    for(QSharedPointer<UnitNode> parentUN : as_const(getSetMetaRealUnitNodes().values())) {
                        if(parentUN->getType() == TypeUnitNode::BL_IP &&
                           parentUN->getUdpAdress() == tmpUN->getUdpAdress() &&
                           parentUN->getUdpPort() == tmpUN->getUdpPort()) {
                            tmpParentUN = parentUN;
                            break;
                        }
                    }
                    // create reciver
                    if(tmpParentUN.isNull()){
                        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNode::BL_IP);
                        tmpParentUN->setType(TypeUnitNode::BL_IP);
                        tmpParentUN->setUdpAdress(tmpUN->getUdpAdress());
                        tmpParentUN->setUdpPort(tmpUN->getUdpPort());
                        tmpParentUN->setName("MetaBLIP");
                        tmpParentUN->setNum1(static_cast<quint8>(0xFF));
                        tmpParentUN->setControl(false);
                        tmpParentUN->setMetaEntity(1);
                        \
                        getSetMetaRealUnitNodes().insert(tmpParentUN);
                        ServerSettingUtils::linkDoubles(tmpParentUN);
                    }

                    tmpParentUN->addChild(tmpUN);
                    tmpUN->setParentUN(tmpParentUN);

                    qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " insert " << tmpUN->toString() << " parent " << tmpUN->getParentUN()->toString();
                    getSetMetaRealUnitNodes().insert(tmpUN);

                } else if(tmpUN->getDoubles().isEmpty() &&
                          TypeUnitNode::TG == tmpUN->getType()) {
                    // find reciver in meta set
                    QSharedPointer<UnitNode> tmpParentUN;// = UnitNodeFactory::make(TypeUnitNode::BL_IP);
                    for(QSharedPointer<UnitNode> parentUN : as_const(getSetMetaRealUnitNodes().values())) {
                        if(parentUN->getType() == TypeUnitNode::TG_Base &&
                           parentUN->getUdpAdress() == tmpUN->getUdpAdress() &&
                           parentUN->getUdpPort() == tmpUN->getUdpPort() &&
                           parentUN->getNum1() == tmpUN->getNum1()) {
                            tmpParentUN = parentUN;
                            break;
                        }
                    }
                    // create reciver
                    if(tmpParentUN.isNull()){
                        tmpParentUN = UnitNodeFactory::makeShare(TypeUnitNode::TG_Base);
//                        *(tmpParentUN.data()) = *(tmpUN.data());

                        tmpParentUN->setType(TypeUnitNode::TG_Base);
                        tmpParentUN->setUdpAdress(tmpUN->getUdpAdress());
                        tmpParentUN->setUdpPort(tmpUN->getUdpPort());
                        tmpParentUN->setNum1(tmpUN->getNum1());
                        tmpParentUN->setNum2(0);
                        tmpParentUN->setNum3(0);

                        tmpParentUN->setName("MetaTG_" + QString::number(tmpParentUN->getNum1()));
                        tmpParentUN->setControl(false);
                        tmpParentUN->setMetaEntity(1);

                        getSetMetaRealUnitNodes().insert(tmpParentUN);
                        ServerSettingUtils::linkDoubles(tmpParentUN);
                    }

                    tmpParentUN->addChild(tmpUN);
                    tmpUN->setParentUN(tmpParentUN);

                    qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " insert " << tmpUN->toString() << " parent " << tmpUN->getParentUN()->toString();
                    getSetMetaRealUnitNodes().insert(tmpUN);
                } else {
                    qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << strGroup << " not insert " << tmpUN->toString();
                }

            }
        }
    }

    for(QSharedPointer<UnitNode> un : as_const(ServerSettingUtils::getSetMetaRealUnitNodes().values())) {
        if(TypeUnitNode::SD_BL_IP == un->getType() &&
           !un->getParentUN().isNull() &&
           1 <= un->getNum2() && 4 >= un->getNum2()) {
            QSharedPointer<UnitNode> parent = un->getParentUN();
            bool needAddUI = true;

            for(int i = 0, n = parent->childCount(); i < n; i++) {
                auto unChild = parent->child(i);
                if(!unChild.isNull() &&
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
                newMetaUnIuBlIp->setStateWord(0x41u, un->getStateWord(0x41u));

                newMetaUnIuBlIp->setName("MetaIU_" + QString::number(newMetaUnIuBlIp->getNum2()));
                newMetaUnIuBlIp->setControl(false);
                newMetaUnIuBlIp->setMetaEntity(1);

                parent->addChild(newMetaUnIuBlIp);
                newMetaUnIuBlIp->setParentUN(parent);
                qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- meta insert " << newMetaUnIuBlIp->toString() << " parent " << newMetaUnIuBlIp->getParentUN()->toString();
                ServerSettingUtils::getSetMetaRealUnitNodes().insert(newMetaUnIuBlIp);
                ServerSettingUtils::linkDoubles(newMetaUnIuBlIp);
            }
        }
    }

//    for(auto un : getListTreeUnitNodes())
//        qDebug() << un->toString();
//    for(auto un : getSetMetaRealUnitNodes())
//        qDebug() << un->toString();

    qDebug() << "ServerSettingUtils::loadTreeUnitNodes <--";

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
    for(QSharedPointer<UnitNode> & un : getSetMetaRealUnitNodes().values()) {
        if(target == un.data()) {
            return un;
        }
    }
    return QSharedPointer<UnitNode>();
}

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

QSet<int>  ServerSettingUtils::priorityJoutTyper = {901,902, 20,21,22,23,25,905,1007, 200,10, 904, 12,13,17,18, 110,111,112,113,11, 130,131/*,133*/,134,135,136,137,140,141,150,151,1000,1001,1002,1003,1004,1007/*,1133*/,1136,1137,1902, 11,13};

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

