#include "GraphTerminal.h"

#include "SWPSDBLIPType0x41.h"
#include "SWPIUBLIPType0x41.h"
#include "SWPRLMType0x31.h"
#include "SWPRLMCType0x31.h"
#include "SWPTGType0x31.h"
#include "SWPTGType0x32.h"
#include "SWPTGType0x33.h"
#include "SWPTGType0x34.h"
#include "SWPTGSubType0x32.h"
#include "SWPTGSubType0x33.h"
#include "SWPTGSubType0x34.h"
#include "TcpServer.h"
#include <QTcpSocket>
#include <qdom.h>
#include "UnitNode.h"
#include "DataBaseManager.h"
#include "JourEntity.h"
#include <QDomDocument>
#include "ServerSettingUtils.h"
#include "SignalSlotCommutator.h"
#include "global.h"

QSharedPointer<TcpServer> GraphTerminal::m_tcpServer = QSharedPointer<TcpServer>();
QMultiHash<QSharedPointer<QTcpSocket>, QSharedPointer<QByteArray> > GraphTerminal::abonents = QMultiHash<QSharedPointer<QTcpSocket>, QSharedPointer<QByteArray> >();


GraphTerminal::GraphTerminal(int nPort, QObject *parent) : QObject(parent)
{
    Q_UNUSED(nPort)
    try {

        QString sPort = ServerSettingUtils::getValueSettings("Port", "INTEGRATION").toString();

        m_tcpServer = QSharedPointer<TcpServer>::create(sPort.toInt(), this);
        connect(m_tcpServer.data(), SIGNAL(dataReceived(DataQueueItem)), this, SLOT(pushOverallReadQueue(DataQueueItem)));
        connect(m_tcpServer.data(), SIGNAL(dataReceived(DataQueueItem)), this, SLOT(manageOverallReadQueue()));


        QString nHost = ServerSettingUtils::getValueSettings("Host", "INTEGRATION").toString();
        Q_UNUSED(nHost)
        QString nPort2 = ServerSettingUtils::getValueSettings("Port2", "INTEGRATION").toString();
        Q_UNUSED(nPort2)

//        m_tcpServer->writeData(nHost, "Hello!");

        const auto buffers = m_tcpServer->getAbonents();
        abonents.unite(buffers);
        for(auto socket : as_const(abonents.keys())) {
            connect(socket.data(), SIGNAL(disconnected()), SLOT(disconnected()));
        }
        SignalSlotCommutator::getInstance()->emitChangeCountIntegrationAbonent(abonents.size());


    }  catch (...) {
      //qDebug() << "GraphTerminal::GraphTerminal -- some exception";
    }

}

QList<DataQueueItem> GraphTerminal::getOverallReadQueue() const
{
    return overallReadQueue;
}

void GraphTerminal::setOverallReadQueue(const QList<DataQueueItem> &value)
{
    overallReadQueue = value;
}

QList<DataQueueItem> GraphTerminal::popOverallReadQueue() {
    QList<DataQueueItem> result(getOverallReadQueue());
    for(const auto& itm : as_const(result)) {
        overallReadQueue.removeOne(itm);
    }
    return result;
}

DataQueueItem GraphTerminal::popReadQueue()
{
    QList<DataQueueItem> ls(getOverallReadQueue());
    if(ls.isEmpty())
        return DataQueueItem();

    DataQueueItem result = ls.first();
    overallReadQueue.removeOne(result);

    return result;
}

void GraphTerminal::pushOverallReadQueue(const QList<DataQueueItem> &value) {
    overallReadQueue.append(value);
    //    //qDebug() << "pushOverallReadQueue size(" << overallReadQueue.size() << ")";
}

void GraphTerminal::pushReadQueue(const DataQueueItem &value)
{
    overallReadQueue.append(value);
}

void GraphTerminal::pushOverallReadQueue(const DataQueueItem &value){
    overallReadQueue.append(value);
//    //qDebug() << "pushOverallReadQueue size(" << overallReadQueue.size() << ")";
}

QList<DataQueueItem> GraphTerminal::getOverallWriteQueue() const
{
    return overallWriteQueue;
}

void GraphTerminal::setOverallWriteQueue(const QList<DataQueueItem> &value)
{
    overallWriteQueue = value;
}

QList<DataQueueItem> GraphTerminal::popOverallWriteQueue() {
    QList<DataQueueItem> result(getOverallWriteQueue());
    for(const auto& itm : as_const(result)) {
        overallWriteQueue.removeOne(itm);
    }
    return result;
}

DataQueueItem GraphTerminal::popWriteQueue()
{
    QList<DataQueueItem> ls(getOverallWriteQueue());
    if(ls.isEmpty())
        return DataQueueItem();

    DataQueueItem result = ls.first();
    overallWriteQueue.removeOne(result);

    return result;
}

void GraphTerminal::pushOverallWriteQueue(const QList<DataQueueItem> &value) {
    overallWriteQueue.append(value);
}


void GraphTerminal::pushOverallWriteQueue(const DataQueueItem &value){
    overallWriteQueue.append(value);
}

void GraphTerminal::manageOverallReadQueue()
{
//    //qDebug() << "GraphTerminal::manageOverallReadQueue() -->";
    while(!getOverallReadQueue().isEmpty()) {
        DataQueueItem itm = popReadQueue();

        QDomDocument doc;
        if(!doc.setContent(itm.data()))
            continue;

        QDomElement root = doc.documentElement();
        if (root.tagName().toUpper() != QString("RIFPlusPacket").toUpper()) {
            qWarning() << "The file is not a RIFPlusPacket file, it is " + root.tagName();
            continue;
        }

        if(!root.attributes().contains("type"))
            continue;

        QString type = root.attribute("type");

//        //qDebug() << "root.attribute(\"type\") " << type;
        if("Commands" == type) {
            procCommands(itm);
            continue;
        } else if("KeepAlive" == type) {
            continue;
        } else if("InitialStatus" == type) {
            continue;
        } else if("EventBook" == type) {
            continue;
        } else if("EventsAndStates" == type) {
            procEventsAndStates(itm);
            continue;
        } else if("AlarmsReset" == type) {
//            requestAlarmReset();
//            {
//                JourEntity msgOn;
//                msgOn.setObject(tr("Оператор"));
//                msgOn.setType(1903);
//                msgOn.setComment(tr("Удал. ком. Сброс тревог"));
//                msgOn.setDirection(Utils::hostAddressToString(itm.address()));
//                DataBaseManager::insertJourMsg_wS(msgOn);
//                GraphTerminal::sendAbonentEventsAndStates(msgOn);
//                DataBaseManager::resetAllFlags_wS();
//            }
            SignalSlotCommutator::getInstance()->emitAlarmsReset(nullptr);
            {
                JourEntity msgOn;
                msgOn.setObject(tr("Оператор"));
                msgOn.setType(903);
                msgOn.setComment(tr("Выполнен сброс тревог"));
                DataBaseManager::insertJourMsg_wS(msgOn);
                GraphTerminal::sendAbonentEventsAndStates(msgOn);
            }
            continue;
        } else if("DbStart" == type) {
            procDbStart(itm);
            continue;
        } else {

        }

    }
//    //qDebug() << "GraphTerminal::manageOverallReadQueue() <--";

}

void GraphTerminal::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    for(const auto &key : abonents.keys()) {
        if(key.data() == socket) {
            abonents.remove(key);
            SignalSlotCommutator::getInstance()->emitChangeCountIntegrationAbonent(abonents.size());

            qDebug() << "GraphTerminal::disconnected()" << abonents;
            return;
        }
    }
}

void GraphTerminal::procCommands(DataQueueItem itm) {
    //qDebug() << "GraphTerminal::procCommands() -->";
    QDomDocument doc;
    if(!doc.setContent(itm.data()))
        return;

    QDomElement root = doc.documentElement();
//    QDomNodeList nodeList = root.childNodes();

    QDomNode nodeCommands = root.namedItem("Commands");
    if(nodeCommands.isNull())
        return;

    QDomNodeList nodeListCommands = nodeCommands.childNodes();
    for(int i = 0, n = nodeListCommands.count(); i < n; i++) {
        QDomNode nodeCommand = nodeListCommands.at(i);
        if("Command" == nodeCommand.nodeName()) {
            //qDebug() << nodeCommand.nodeName();
            if(!nodeCommand.attributes().contains("id"))
                continue;

            QDomNode idCommand = nodeCommand.attributes().namedItem("id");
//            QDomDocument docAnswer;
            QByteArray dataAnswer;
            //qDebug() << "GraphTerminal::procCommands() idCommand.nodeValue(" << idCommand.nodeValue() << ")";
//            //qDebug() << "GraphTerminal::procCommands() " << doc.toString();
            if("0" == idCommand.nodeValue()) {
                dataAnswer = makeInitialStatus("InitialStatus answer command 0").toByteArray();
                //
            } else if("10000" == idCommand.nodeValue()) {
//                dataAnswer = makeEventsAndStates("EventsAndStates answer command 10000").toByteArray();

                const auto buffers = m_tcpServer->getAbonents();
                for(const auto &socket : as_const(buffers.keys())) {
                    if(socket->peerAddress() == itm.address()) {
                        abonents.insert(socket, buffers.value(socket));
                        connect(socket.data(), SIGNAL(disconnected()), SLOT(disconnected()));
                        SignalSlotCommutator::getInstance()->emitChangeCountIntegrationAbonent(abonents.size());

//                        qDebug() << "GraphTerminal::procCommands(10000)" << abonents;
                    }
                }
                //
            } else if("10001" == idCommand.nodeValue()) {

                for(const auto& socket : as_const(abonents.keys())) {
                    if(socket->peerAddress() == itm.address()) {
                        abonents.remove(socket);
                        SignalSlotCommutator::getInstance()->emitChangeCountIntegrationAbonent(abonents.size());

//                        qDebug() << "GraphTerminal::procCommands(10001)" << abonents;
                        break;
                    }
                }
                //
            } else if(("100" == idCommand.nodeValue()) || ("101" == idCommand.nodeValue())) {
//                        <RIFPlusPacket type="Commands"><Commands><Command id="100" name=" Выключение ИУ"/><device id="1" level="1" type="4"
//                        num1="1" num2="1" num3="1"></Commands></RIFPlusPacket>

                if(2 != nodeCommands.childNodes().count())
                    continue;

                QDomNode nodeDevice = nodeCommands.namedItem("device");
                if(nodeDevice.isNull())
                    continue;
                QDomNode deviceId, deviceLevel, deviceType, deviceNum1, deviceNum2, deviceNum3;

                if(!nodeDevice.attributes().contains("id")) continue;
                else deviceId = nodeDevice.attributes().namedItem("id");

                if(!nodeDevice.attributes().contains("level")) continue;
                else deviceLevel = nodeDevice.attributes().namedItem("level");

                if(!nodeDevice.attributes().contains("type")) continue;
                else deviceType = nodeDevice.attributes().namedItem("type");

                if(!nodeDevice.attributes().contains("num1")) continue;
                else deviceNum1 = nodeDevice.attributes().namedItem("num1");

                if(!nodeDevice.attributes().contains("num2")) continue;
                else deviceNum2 = nodeDevice.attributes().namedItem("num2");

                if(!nodeDevice.attributes().contains("num3")) continue;
                else deviceNum3 = nodeDevice.attributes().namedItem("num3");

                QSharedPointer<UnitNode> unTarget = QSharedPointer<UnitNode>(nullptr);
                for(auto un : as_const(ServerSettingUtils::getSetMetaRealUnitNodes())) {
                    if(un->getMetaNames().contains("Obj_" + deviceId.nodeValue()) &&
                       un->getLevel() == deviceLevel.nodeValue().toInt() &&
                       un->getType() == deviceType.nodeValue().toInt() &&
                       un->getNum1() == deviceNum1.nodeValue().toInt() &&
                       un->getNum2() == deviceNum2.nodeValue().toInt() &&
                       un->getNum3() == deviceNum3.nodeValue().toInt()) {
                        unTarget = un;
                        break;
                    }
                }

                if(nullptr == unTarget)
                    continue;
                if(TypeUnitNode::IU_BL_IP == unTarget->getType())
                    if(unTarget->swpIUBLIPType0x41().isNull())
                        continue;

                if(TypeUnitNode::SD_BL_IP == unTarget->getType())
                    if(unTarget->swpSDBLIPType0x41().isNull())
                        continue;


                bool value = ("100" == idCommand.nodeValue()) ? false : ("101" == idCommand.nodeValue()) ? true : false;

                if(0 != unTarget->getBazalt() && 1 == unTarget->swpSDBLIPType0x41().isAlarm() && "100" == idCommand.nodeValue()) {
                    SignalSlotCommutator::getInstance()->emitLockOpenCloseCommand(true, unTarget, false);
                } else if(0 != unTarget->getBazalt() && 1 == unTarget->swpSDBLIPType0x41().isNorm() && "101" == idCommand.nodeValue()) {
                    SignalSlotCommutator::getInstance()->emitLockOpenCloseCommand(true, unTarget, true);
                } else if(0 != unTarget->getBazalt()) {
                    SignalSlotCommutator::getInstance()->emitLockOpenCloseCommand(true, unTarget, value);
                } else if(unTarget->isEditableOnOff() && 1 == unTarget->swpIUBLIPType0x41().isOff() && "101" == idCommand.nodeValue()) {
                    const auto& setUn = Utils::findeSetAutoOnOffUN(unTarget);
                    if(setUn.isEmpty()) {
                        SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(false, true, unTarget, true);
                    } else {
                        SignalSlotCommutator::getInstance()->emitAutoOnOffIU(false, true, unTarget);
                    }
                } else if(unTarget->isEditableOnOff() && "101" == idCommand.nodeValue()) {
                    const auto& setUn = Utils::findeSetAutoOnOffUN(unTarget);
                    if(setUn.isEmpty()) {
                        SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(false, true, unTarget, true);
                    } else {
                        SignalSlotCommutator::getInstance()->emitAutoOnOffIU(false, true, unTarget);
                    }
                } else if(unTarget->isEditableOnOff() && (1 == unTarget->swpIUBLIPType0x41().isOff()) && "101" == idCommand.nodeValue()) {
                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(false, true, unTarget, true);
                } else if(unTarget->isEditableOnOff() && 1 == unTarget->swpIUBLIPType0x41().isOn() && "100" == idCommand.nodeValue()) {
                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(false, true, unTarget, false);
                } else  {
                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(false, true, unTarget, value);
                }
                //
            } else/* if("101" == idCommand.nodeValue()) {
                //
            } else*/ if(("133" == idCommand.nodeValue()) || ("1133" == idCommand.nodeValue())) {
                //qDebug() << "-->";
                if(2 != nodeCommands.childNodes().count())
                    continue;

                QDomNode nodeDevice = nodeCommands.namedItem("device");

                if(nodeDevice.isNull())
                    continue;

                QDomNode deviceId, deviceLevel, deviceType, deviceNum1, deviceNum2, deviceNum3;

                if(nodeDevice.attributes().contains("id")) deviceId = nodeDevice.attributes().namedItem("id");

                if(nodeDevice.attributes().contains("level")) deviceLevel = nodeDevice.attributes().namedItem("level");

                if(nodeDevice.attributes().contains("type")) deviceType = nodeDevice.attributes().namedItem("type");

                if(nodeDevice.attributes().contains("num1")) deviceNum1 = nodeDevice.attributes().namedItem("num1");

                if(nodeDevice.attributes().contains("num2")) deviceNum2 = nodeDevice.attributes().namedItem("num2");

                if(nodeDevice.attributes().contains("num3")) deviceNum3 = nodeDevice.attributes().namedItem("num3");

                QSharedPointer<UnitNode>  unTarget = nullptr;
                QSet<QSharedPointer<UnitNode> > unTargetSet;

                //qDebug() << "id[" << deviceId.nodeValue() << "] level[" << deviceLevel.nodeValue() << "] type[" << deviceType.nodeValue() << "] num1[" << deviceNum1.nodeValue() << "] num2[" << deviceNum2.nodeValue() << "] num3[" << deviceNum3.nodeValue() << "]";

                for(QSharedPointer<UnitNode>  un : as_const(ServerSettingUtils::getListTreeUnitNodes())) {
                    if(!deviceId.isNull()) {
                        QString unMetaName("Obj_" + deviceId.nodeValue());
                        if(un->getMetaNames().contains(unMetaName)) {
                            unTargetSet.insert(un);
                        }
                    }

                    if(!deviceId.isNull() && !deviceLevel.isNull() && !deviceType.isNull() && !deviceNum1.isNull() && !deviceNum2.isNull() && !deviceNum3.isNull()) {
                        QString unMetaName("Obj_" + deviceId.nodeValue());
                        if(un->getMetaNames().contains(unMetaName) &&
                           un->getLevel() == deviceLevel.nodeValue().toInt() &&
                           un->getNum1() == deviceNum1.nodeValue().toInt() &&
                           un->getNum2() == deviceNum2.nodeValue().toInt() &&
                           un->getNum3() == deviceNum3.nodeValue().toInt()) {
                            unTargetSet.insert(un);
                        }
                    }

                    if(deviceId.isNull() && deviceLevel.isNull() && !deviceType.isNull() && !deviceNum1.isNull() && !deviceNum2.isNull() && !deviceNum3.isNull()) {
                        if(un->getLevel() == deviceLevel.nodeValue().toInt() &&
                           un->getNum1() == deviceNum1.nodeValue().toInt() &&
                           un->getNum2() == deviceNum2.nodeValue().toInt() &&
                           un->getNum3() == deviceNum3.nodeValue().toInt()) {
                            unTargetSet.insert(un);
                        }
                    }
                }

                for(const auto& un : as_const(unTargetSet.values())) {
                    if(TypeUnitNode::SD_BL_IP == un->getType() ||
                       TypeUnitNode::IU_BL_IP == un->getType() ||
                       TypeUnitNode::RLM_C == un->getType() ||
                       TypeUnitNode::RLM_KRL == un->getType() ||
                       TypeUnitNode::TG == un->getType()) {
                        unTarget = un;
                        //qDebug() << unTarget->toString();
                        break;
                    }
                }

                SignalSlotCommutator::getInstance()->emitRequestDK(false, true, unTarget);

                //qDebug() << "<--";
                //
//            } else if("1133" == idCommand.nodeValue()) {
//                //
            } else if("1" == idCommand.nodeValue()) {
                if(2 != nodeCommands.childNodes().count())
                    continue;
                QDomNode nodeDevice = nodeCommands.namedItem("device");
                if(nodeDevice.isNull())
                    continue;
                if(!nodeDevice.attributes().contains("id"))
                    continue;
                QString unMetaName("Obj_" + nodeDevice.attributes().namedItem("id").nodeValue());

                for(auto un : as_const(ServerSettingUtils::getListTreeUnitNodes())) {
                    if(un->getMetaNames().contains(unMetaName)) {
                        SignalSlotCommutator::getInstance()->emitChangeSelectUN(un);
                    }
                }
                //
            } else if(("137" == idCommand.nodeValue()) || ("136" == idCommand.nodeValue())) {

                if(2 != nodeCommands.childNodes().count())
                    continue;

                QDomNode nodeDevice = nodeCommands.namedItem("device");

                if(nodeDevice.isNull())
                    continue;

                QDomNode deviceId, deviceLevel, deviceType, deviceNum1, deviceNum2, deviceNum3;

                if(nodeDevice.attributes().contains("id")) deviceId = nodeDevice.attributes().namedItem("id");

                if(nodeDevice.attributes().contains("level")) deviceLevel = nodeDevice.attributes().namedItem("level");

                if(nodeDevice.attributes().contains("type")) deviceType = nodeDevice.attributes().namedItem("type");

                if(nodeDevice.attributes().contains("num1")) deviceNum1 = nodeDevice.attributes().namedItem("num1");

                if(nodeDevice.attributes().contains("num2")) deviceNum2 = nodeDevice.attributes().namedItem("num2");

                if(nodeDevice.attributes().contains("num3")) deviceNum3 = nodeDevice.attributes().namedItem("num3");

                QSharedPointer<UnitNode>  unTarget = nullptr;
                QSet<QSharedPointer<UnitNode> > unTargetSet;

                //qDebug() << "id[" << deviceId.nodeValue() << "] level[" << deviceLevel.nodeValue() << "] type[" << deviceType.nodeValue() << "] num1[" << deviceNum1.nodeValue() << "] num2[" << deviceNum2.nodeValue() << "] num3[" << deviceNum3.nodeValue() << "]";

                for(auto un : as_const(ServerSettingUtils::getListTreeUnitNodes())) {
                    if(!deviceId.isNull()) {
                        QString unMetaName("Obj_" + deviceId.nodeValue());
                        if(un->getMetaNames().contains(unMetaName)) {
                            unTargetSet.insert(un);
                        }
                    }

                    if(!deviceId.isNull() && !deviceLevel.isNull() && !deviceType.isNull() && !deviceNum1.isNull() && !deviceNum2.isNull() && !deviceNum3.isNull()) {
                        QString unMetaName("Obj_" + deviceId.nodeValue());
                        if(un->getMetaNames().contains(unMetaName) &&
                           un->getLevel() == deviceLevel.nodeValue().toInt() &&
                           un->getNum1() == deviceNum1.nodeValue().toInt() &&
                           un->getNum2() == deviceNum2.nodeValue().toInt() &&
                           un->getNum3() == deviceNum3.nodeValue().toInt()) {
                            unTargetSet.insert(un);
                        }
                    }

                    if(deviceId.isNull() && deviceLevel.isNull() && !deviceType.isNull() && !deviceNum1.isNull() && !deviceNum2.isNull() && !deviceNum3.isNull()) {
                        if(un->getLevel() == deviceLevel.nodeValue().toInt() &&
                           un->getNum1() == deviceNum1.nodeValue().toInt() &&
                           un->getNum2() == deviceNum2.nodeValue().toInt() &&
                           un->getNum3() == deviceNum3.nodeValue().toInt()) {
                            unTargetSet.insert(un);
                        }
                    }
                }

                for(const auto& un : as_const(unTargetSet.values())) {
                    if(un->isEditableControl()) {
                        unTarget = un;
                        //qDebug() << unTarget->toString();
                        break;
                    }
                }

                bool val = true;
                if("137" == idCommand.nodeValue()) {
                    val = true;
                } else if("136" == idCommand.nodeValue()) {
                    val = false;
                }

                if(nullptr != unTarget) {

                    JourEntity msgOn;
                    msgOn.setObject(unTarget->getName());
                    msgOn.setObjecttype(unTarget->getType());
                    msgOn.setD1(unTarget->getNum1());
                    msgOn.setD2(unTarget->getNum2());
                    msgOn.setD3(unTarget->getNum3());
                    msgOn.setDirection(Utils::hostAddressToString(itm.address()));
                    msgOn.setType((val ? 1137 : 1136));
                    msgOn.setComment(tr("Удал. ком. Контроль ") + (val ? tr("Вкл") : tr("Выкл")));
                    if(!unTarget->getName().isEmpty() && 1 != unTarget->getMetaEntity()) {
                        DataBaseManager::insertJourMsg_wS(msgOn);
                    }

                    unTarget->setControl(val);
                    if(unTarget->getControl())
                        unTarget->setPublishedState(-1);
                    unTarget->updDoubl();

                    dataAnswer = makeEventsAndStates(unTarget, msgOn).toByteArray();

//                    if(unTarget->getControl()) {
//                        unTarget->setStatus1(Status::Uncnown);
//                        unTarget->setStatus2(Status::Uncnown);
//                    }
                }
                //qDebug() << "<--";

                //
//            } else if("136" == idCommand.nodeValue()) {
//                //
            } else if("1301" == idCommand.nodeValue()) {
                if(2 != nodeCommands.childNodes().count())
                    continue;

                QDomNode nodeDevice = nodeCommands.namedItem("device");

                if(nodeDevice.isNull())
                    continue;

                QDomNode deviceId, deviceLevel, deviceType, deviceNum1, deviceNum2, deviceNum3;

                if(nodeDevice.attributes().contains("id")) deviceId = nodeDevice.attributes().namedItem("id");

                if(nodeDevice.attributes().contains("level")) deviceLevel = nodeDevice.attributes().namedItem("level");

                if(nodeDevice.attributes().contains("type")) deviceType = nodeDevice.attributes().namedItem("type");

                if(nodeDevice.attributes().contains("num1")) deviceNum1 = nodeDevice.attributes().namedItem("num1");

                if(nodeDevice.attributes().contains("num2")) deviceNum2 = nodeDevice.attributes().namedItem("num2");

                if(nodeDevice.attributes().contains("num3")) deviceNum3 = nodeDevice.attributes().namedItem("num3");

                QSharedPointer<UnitNode>  unTarget = nullptr;
                QSet<QSharedPointer<UnitNode> > unTargetSet;

                //qDebug() << "id[" << deviceId.nodeValue() << "] level[" << deviceLevel.nodeValue() << "] type[" << deviceType.nodeValue() << "] num1[" << deviceNum1.nodeValue() << "] num2[" << deviceNum2.nodeValue() << "] num3[" << deviceNum3.nodeValue() << "]";

                for(auto un : as_const(ServerSettingUtils::getListTreeUnitNodes())) {
                    if(!deviceId.isNull()) {
                        QString unMetaName("Obj_" + deviceId.nodeValue());
                        if(un->getMetaNames().contains(unMetaName)) {
                            unTargetSet.insert(un);
                        }
                    }

                    if(!deviceId.isNull() && !deviceLevel.isNull() && !deviceType.isNull() && !deviceNum1.isNull() && !deviceNum2.isNull() && !deviceNum3.isNull()) {
                        QString unMetaName("Obj_" + deviceId.nodeValue());
                        if(un->getMetaNames().contains(unMetaName) &&
                           un->getLevel() == deviceLevel.nodeValue().toInt() &&
                           un->getNum1() == deviceNum1.nodeValue().toInt() &&
                           un->getNum2() == deviceNum2.nodeValue().toInt() &&
                           un->getNum3() == deviceNum3.nodeValue().toInt()) {
                            unTargetSet.insert(un);
                        }
                    }

                    if(deviceId.isNull() && deviceLevel.isNull() && !deviceType.isNull() && !deviceNum1.isNull() && !deviceNum2.isNull() && !deviceNum3.isNull()) {
                        if(un->getLevel() == deviceLevel.nodeValue().toInt() &&
                           un->getNum1() == deviceNum1.nodeValue().toInt() &&
                           un->getNum2() == deviceNum2.nodeValue().toInt() &&
                           un->getNum3() == deviceNum3.nodeValue().toInt()) {
                            unTargetSet.insert(un);
                        }
                    }
                }

                for(const auto& un : as_const(unTargetSet.values())) {
                    if(TypeUnitNode::SD_BL_IP == un->getType() ||
                       TypeUnitNode::IU_BL_IP == un->getType() ||
                       TypeUnitNode::RLM_C == un->getType() ||
                       TypeUnitNode::RLM_KRL == un->getType() ||
                       TypeUnitNode::TG == un->getType()) {
                        unTarget = un;
                        //qDebug() << unTarget->toString();
                        break;
                    }
                }

                dataAnswer = makeEventsAndStates(unTarget).toByteArray();
                //
            } else if("2" == idCommand.nodeValue()) {
                dataAnswer = makeProtocolVersionInfo();
                //
            } else if("33" == idCommand.nodeValue()) {
                //
            } else if("143" == idCommand.nodeValue()) {
                //
            } else if("146" == idCommand.nodeValue()) {
                //
            } else if("10010" == idCommand.nodeValue()) {
//                4.16 Получение архива событий
//                Формат <RIFPlusPacket type="Commands"><Commands><Command id="10010" name="Получить архив событий" start=”1000”
//                length=”100”/></Commands></RIFPlusPacket>
//                или <RIFPlusPacket type="Commands"><Commands><Command id="10010" name="Получить архив событий" from=”2021-05-14 16:20:00”
//                length=”100”/></Commands></RIFPlusPacket>
//                В ответ сервер пришлёт список не более length событий из БД, начиная с ID >= start или с временем >= from
                QDomNode start = nodeCommand.attributes().namedItem("start");
                QDomNode from = nodeCommand.attributes().namedItem("from");
                QDomNode length = nodeCommand.attributes().namedItem("length");

                if((start.nodeValue().isEmpty() && from.nodeValue().isEmpty()) || length.nodeValue().isEmpty())
                    continue;

                QList<JourEntity> jours;

                if(!start.nodeValue().isEmpty() && from.nodeValue().isEmpty())
                    jours = DataBaseManager::getJourRecordAfter(start.nodeValue().toInt(), length.nodeValue().toInt());
                else if(start.nodeValue().isEmpty() && !from.nodeValue().isEmpty())
                    jours = DataBaseManager::getJourRecordAfter(QDateTime::fromString(from.nodeValue(), "yyyy-MM-dd hh:mm:ss"), length.nodeValue().toInt());

                dataAnswer = makeListJourRecord(jours.mid(0, length.nodeValue().toInt())).toByteArray();
                //

            } else {
                //
            }

            if(!dataAnswer.isEmpty()) {
                DataQueueItem itmAnswer = itm;
                itmAnswer.setData(dataAnswer);

                const auto &hostSender = QHostAddress(itm.address());
                const quint16 &portSender = itm.port();

                const auto buffers = m_tcpServer->getAbonents();
                for(const auto& socket : as_const(buffers.keys())) {
                    if((socket->peerAddress().isEqual(hostSender) && socket->peerPort() == portSender)
                    || socket->peerAddress().isEqual(QHostAddress(QHostAddress::Any))) {
                        QByteArray buf;
                        QTextStream ts(&buf);
                        auto cw51 = QTextCodec::codecForName("windows-1251");

                        ts.setCodec(cw51);
                        ts << dataAnswer;
                        ts.flush();

                        this->m_tcpServer->writeData(socket, buf);
                    }
                }

            }


        }
    }
    //qDebug() << "GraphTerminal::procCommands() <--";
}

void GraphTerminal::procKeepAlive(QDomElement /*root*/) {

}

void GraphTerminal::procEventBook(QDomElement /*root*/) {

}

void GraphTerminal::procEventsAndStates(DataQueueItem itm) {
    //qDebug() << "GraphTerminal::procEventsAndStates() -->";
    QDomDocument doc;
    if(!doc.setContent(itm.data()))
        return;

    QDomElement root = doc.documentElement();
//    QDomNodeList nodeList = root.childNodes();

    QDomNode nodeDevices = root.namedItem("devices");
    if(nodeDevices.isNull())
        return;

    QDomNodeList nodeListDevices = nodeDevices.childNodes();
    for(int i = 0, n = nodeListDevices.count(); i < n; i++) {
        QDomNode nodeDevice = nodeListDevices.at(i);
        if("device" == nodeDevice.nodeName()) {
//            //qDebug() << nodeDevice.nodeName();
//            if(!nodeDevice.attributes().contains("id"))
//                continue;

            QDomNode nodeStates = nodeDevice.namedItem("states");
            if(nodeStates.isNull())
                continue;

            QDomNodeList nodeListStates = nodeStates.childNodes();
            for(int i = 0, n = nodeListStates.count(); i < n; i++) {
                QDomNode nodeState = nodeListStates.at(i);
                if("state" == nodeState.nodeName()) {
                    QDomNode idState = nodeState.attributes().namedItem("id");
                    QDomDocument docAnswer;
                    //qDebug() << "GraphTerminal::procEventsAndStates() idState.nodeValue(" << idState.nodeValue() << ")";
                    //qDebug() << "GraphTerminal::procEventsAndStates() " << doc.toString();

                    if("903" == idState.nodeValue()) {
                        {
                            JourEntity msgOn;
                            msgOn.setObject(tr("Оператор"));
                            msgOn.setType(1903);
                            msgOn.setComment(tr("Удал. ком. Сброс тревог"));
                            msgOn.setDirection(Utils::hostAddressToString(itm.address()));
                            msgOn.setFlag(0);
                            DataBaseManager::insertJourMsg_wS(msgOn);
                            GraphTerminal::sendAbonentEventsAndStates(msgOn);
                            DataBaseManager::resetAllFlags_wS();
                        }

                        SignalSlotCommutator::getInstance()->emitAlarmsReset(nullptr);

                        {
                            JourEntity msgOn;
                            msgOn.setObject(tr("Оператор"));
                            msgOn.setType(903);
                            msgOn.setComment(tr("Выполнен сброс тревог"));
                            msgOn.setFlag(0);
                            DataBaseManager::insertJourMsg_wS(msgOn);
                            GraphTerminal::sendAbonentEventsAndStates(msgOn);
                        }
                    }

                    if(!docAnswer.isNull()) {
                        DataQueueItem itmAnswer = itm;
                        itmAnswer.setData(docAnswer.toByteArray());

                        const auto buffers = m_tcpServer->getAbonents();
                        for(const auto& socket : as_const(buffers.keys())) {
                            if(socket->peerAddress() == itm.address()) {
                                QByteArray buf;
                                QTextStream ts(&buf);
                                auto cw51 = QTextCodec::codecForName("windows-1251");

                                ts.setCodec(cw51);
                                ts << docAnswer.toString();
                                ts.flush();

                                this->m_tcpServer->writeData(socket, buf);
                            }
                        }
                    }

                }
            }
        }
    }

    //qDebug() << "GraphTerminal::procEventsAndStates() <--";
}

void GraphTerminal::procAlarmsReset(QDomElement /*root*/) {

}

void GraphTerminal::procDbStart(DataQueueItem /*itm*/) {
    SignalSlotCommutator::getInstance()->emitForcedNewDuty(false);
}

QDomDocument GraphTerminal::makeInitialStatus(QString docType)
{
    Q_UNUSED(docType)
    QDomDocument doc;//(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "InitialStatus");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  devicesElement  =  doc.createElement("devices");
    RIFPlusPacketElement.appendChild(devicesElement);

    for(const auto &un : as_const(ServerSettingUtils::getListTreeUnitNodes())) {
        // <device id="1" level="1" type="33" num1="1" num2="1" num3="1" name="Устройство 1" lat=”55.761248” lon: “37.608074” description=”Текстовое
        //
        // описание длиной не более 50 символов” dk=”1” option=”0”>

        if(1 == un->getMetaEntity() || un->getMetaNames().isEmpty())
            continue;

        QDomElement  deviceElement  =  doc.createElement("device");
        QString id = un->getMetaNames().values().first();
        id.remove("Obj_");
        deviceElement.setAttribute("id", id);
        deviceElement.setAttribute("level", un->getLevel());
        deviceElement.setAttribute("type", (0 > un->getType() ? 0 : un->getType()));
        deviceElement.setAttribute("num1", un->getNum1());
        deviceElement.setAttribute("num2", un->getNum2());
        deviceElement.setAttribute("num3", un->getNum3());
        deviceElement.setAttribute("name", un->getName());
//        //qDebug() << "deviceElement.setAttribute(\"name\", un->getName(" << un->getName() << "))";
        deviceElement.setAttribute("lat", (0 == un->getLan() ? "0.00000000" : QString::number(un->getLan())));
        deviceElement.setAttribute("lon", (0 == un->getLon() ? "0.00000000" : QString::number(un->getLon())));
        deviceElement.setAttribute("description", (un->getDescription().isEmpty() ? "(null)" : un->getDescription()));
        deviceElement.setAttribute("dk", (0 != un->getDK() ? 1 : 0));
        deviceElement.setAttribute("option", ((TypeUnitNode::SD_BL_IP == un->getType() && 1 == un->getBazalt()) ? 1 : 0));

        if(TypeUnitNode::ONVIF == un->getType()) {
            deviceElement.setAttribute("ip", un->getIcon1Path());
            deviceElement.setAttribute("login", un->getIcon2Path());
            deviceElement.setAttribute("password", un->getIcon3Path());
        } else if(TypeUnitNode::STRAZH_IP == un->getType()) {
            deviceElement.setAttribute("ip", un->getIcon1Path());
            deviceElement.setAttribute("ip2", un->getIcon4Path());
            deviceElement.setAttribute("login", un->getIcon2Path());
            deviceElement.setAttribute("password", un->getIcon3Path());
        } else if(!un->getUdpAdress().isEmpty() && -1 < un->getUdpPort()) {
            deviceElement.setAttribute("ip", QString("%1:%2").arg(un->getUdpAdress()).arg(un->getUdpPort()));
        }

        devicesElement.appendChild(deviceElement);

        QDomElement  statesElement  =  doc.createElement("states");
        deviceElement.appendChild(statesElement);

        if(!un->getControl() && 1 != un->getMetaEntity()) {
            QDomElement  stateElement  =  doc.createElement("state");
            stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            stateElement.setAttribute("id", 136);
            stateElement.setAttribute("name", "Контроль выкл");
            statesElement.appendChild(stateElement);
        }

        if(1 != un->getMetaEntity()) {
            QDomElement  stateElement  =  doc.createElement("state");
            makeActualStateElement(un, stateElement);
            statesElement.appendChild(stateElement);
        }
    }

//    //qDebug() << "GraphTerminal::makeInitialStatus()" << doc.toString();

    return doc;
}

QDomDocument GraphTerminal::makeEventsAndStates(QString /*docType*/)
{
    QDomDocument doc;//(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "EventsAndStates");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  devicesElement  =  doc.createElement("devices");
    RIFPlusPacketElement.appendChild(devicesElement);

    for(QSharedPointer<UnitNode>  un : as_const(ServerSettingUtils::getListTreeUnitNodes())) {
        // <device id="0" level="0" type="33" num1="1" num2="1" num3="1" name="1" lat=”55.761248” lon: “37.608074” description=”Текстовое описание длиной
        // не более 50 символов”>

        if(1 == un->getMetaEntity() || un->getMetaNames().isEmpty())
            continue;

        QDomElement  deviceElement  =  doc.createElement("device");
        QString id;
        if(!un->getMetaNames().isEmpty()) {
            id = un->getMetaNames().values().value(0, "Obj_X");
            id.remove("Obj_");
        } else {
            id = "X";
        }
        deviceElement.setAttribute("id", id);
        deviceElement.setAttribute("level", un->getLevel());
        deviceElement.setAttribute("type", (0 > un->getType() ? 0 : un->getType()));
        deviceElement.setAttribute("num1", un->getNum1());
        deviceElement.setAttribute("num2", un->getNum2());
        deviceElement.setAttribute("num3", un->getNum3());
        deviceElement.setAttribute("name", un->getName());
        deviceElement.setAttribute("lat", (0 == un->getLan() ? "0.00000000" : QString::number(un->getLan())));
        deviceElement.setAttribute("lon", (0 == un->getLon() ? "0.00000000" : QString::number(un->getLon())));
        deviceElement.setAttribute("description", (un->getDescription().isEmpty() ? "(null)" : un->getDescription()));
        deviceElement.setAttribute("dk", (0 != un->getDK() ? 1 : 0));
        deviceElement.setAttribute("option", ((TypeUnitNode::SD_BL_IP == un->getType() && 1 == un->getBazalt()) ? 1 : 0));

        if(TypeUnitNode::ONVIF == un->getType()) {
            deviceElement.setAttribute("ip", un->getIcon1Path());
            deviceElement.setAttribute("login", un->getIcon2Path());
            deviceElement.setAttribute("password", un->getIcon3Path());
        } else if(TypeUnitNode::STRAZH_IP == un->getType()) {
            deviceElement.setAttribute("ip", un->getIcon1Path());
            deviceElement.setAttribute("ip2", un->getIcon4Path());
            deviceElement.setAttribute("login", un->getIcon2Path());
            deviceElement.setAttribute("password", un->getIcon3Path());
        } else if(!un->getUdpAdress().isEmpty() && -1 < un->getUdpPort()) {
            deviceElement.setAttribute("ip", QString("%1:%2").arg(un->getUdpAdress()).arg(un->getUdpPort()));
        }

        devicesElement.appendChild(deviceElement);

        QDomElement  statesElement  =  doc.createElement("states");
        deviceElement.appendChild(statesElement);
        if(!un->getControl() && 1 != un->getMetaEntity()) {
            QDomElement  stateElement  =  doc.createElement("state");
            stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            stateElement.setAttribute("id", 136);
            stateElement.setAttribute("name", "Контроль выкл");
            statesElement.appendChild(stateElement);
        }
        if(1 != un->getMetaEntity()) {
            QDomElement  stateElement  =  doc.createElement("state");
            makeActualStateElement(un, stateElement);
            statesElement.appendChild(stateElement);
        }
    }

//    //qDebug() << "GraphTerminal::makeEventsAndStates()" << doc.toString();

    return doc;
}

QByteArray GraphTerminal::makeProtocolVersionInfo()
{
    return "<RIFPlusPacket type=\"ProtocolVersionInfo\"><version=\"1.19\"/></RIFPlusPacket>";
}

QDomDocument GraphTerminal::makeEventsAndStates(JourEntity jour) {
    return makeEventsAndStates(nullptr, jour);
}

QDomDocument GraphTerminal::makeEventsAndStates(QSharedPointer<UnitNode>  un) {
    return makeEventsAndStates(un, JourEntity());
}

QDomDocument GraphTerminal::makeEventsAndStates(QSharedPointer<UnitNode>  un, JourEntity jour)
{
    QDomDocument doc;//(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "EventsAndStates");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  devicesElement  =  doc.createElement("devices");
    RIFPlusPacketElement.appendChild(devicesElement);

    if(nullptr == un) {
        for(QSharedPointer<UnitNode>  unTmp : as_const(ServerSettingUtils::getListTreeUnitNodes())) {
            if(unTmp->getMetaNames().contains("Obj_0")) {
                un = unTmp;
                break;
            }
        }
    }

    QDomElement  deviceElement  =  doc.createElement("device");
    QString id;
    if(nullptr != un) {
        QString id;
        if(!un->getMetaNames().isEmpty()) {
            id = un->getMetaNames().values().value(0, "Obj_X");
            id.remove("Obj_");
        } else {
            id = "X";
        }
        deviceElement.setAttribute("id", id);
        deviceElement.setAttribute("level", un->getLevel());
        deviceElement.setAttribute("type", (0 > un->getType() ? 0 : un->getType()));
        deviceElement.setAttribute("num1", un->getNum1());
        deviceElement.setAttribute("num2", un->getNum2());
        deviceElement.setAttribute("num3", un->getNum3());
        deviceElement.setAttribute("name", un->getName());
//        //qDebug() << "deviceElement.setAttribute(\"name\", un->getName(" << un->getName() << "))";
        deviceElement.setAttribute("lat", (0 == un->getLan() ? "0.00000000" : QString::number(un->getLan())));
        deviceElement.setAttribute("lon", (0 == un->getLon() ? "0.00000000" : QString::number(un->getLon())));
        deviceElement.setAttribute("description", (un->getDescription().isEmpty() ? "(null)" : un->getDescription()));
        deviceElement.setAttribute("dk", (0 != un->getDK() ? 1 : 0));
        deviceElement.setAttribute("option", ((TypeUnitNode::SD_BL_IP == un->getType() && 1 == un->getBazalt()) ? 1 : 0));

        if(TypeUnitNode::ONVIF == un->getType()) {
            deviceElement.setAttribute("ip", un->getIcon1Path());
            deviceElement.setAttribute("login", un->getIcon2Path());
            deviceElement.setAttribute("password", un->getIcon3Path());
        } else if(TypeUnitNode::STRAZH_IP == un->getType()) {
            deviceElement.setAttribute("ip", un->getIcon1Path());
            deviceElement.setAttribute("ip2", un->getIcon4Path());
            deviceElement.setAttribute("login", un->getIcon2Path());
            deviceElement.setAttribute("password", un->getIcon3Path());
        } else if(!un->getUdpAdress().isEmpty() && -1 < un->getUdpPort()) {
            deviceElement.setAttribute("ip", QString("%1:%2").arg(un->getUdpAdress()).arg(un->getUdpPort()));
        }
    }

    devicesElement.appendChild(deviceElement);

    QDomElement  statesElement  =  doc.createElement("states");
    deviceElement.appendChild(statesElement);

    QDomElement  stateElement1  =  doc.createElement("state");
    QDomElement  stateElement  =  doc.createElement("state");
    if(0 != jour.getType() && !jour.getComment().isEmpty()) {
//        stateElement1  =  doc.createElement("state");
        stateElement1.setAttribute("id", jour.getType());
        stateElement1.setAttribute("datetime", jour.getCdate().toString("yyyy-MM-dd hh:mm:ss"));
        stateElement1.setAttribute("name", jour.getComment());
        statesElement.appendChild(stateElement1);
    }
    if(1 != un->getMetaEntity() && (0 == jour.getType() || jour.getComment().isEmpty()/* || 136 == jour.getType() || 137 == jour.getType()*/)){
        makeActualStateElement(un, stateElement);
        statesElement.appendChild(stateElement);
    }

//    //qDebug() << "GraphTerminal::makeEventsAndStates()" << doc.toString();

    return doc;

}

QDomElement GraphTerminal::makeActualStateElement(QSharedPointer<UnitNode> un, QDomElement &stateElement)
{
    stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    bool isSwitchOff = false;
    if(TypeUnitNode::SD_BL_IP == un->getType() && 1 == un->swpSDBLIPType0x41().isOff()) {
        isSwitchOff = true;
    } else if(TypeUnitNode::RLM_KRL == un->getType() && 1 == un->swpRLMType0x31().isOff()) {
        isSwitchOff = true;
    } else if(TypeUnitNode::RLM_C == un->getType() && 1 == un->swpRLMCType0x31().isOff()) {
        isSwitchOff = true;
    } else if(TypeUnitNode::TG == un->getType() && 1 == un->swpTGType0x31().isOff()) {
        isSwitchOff = true;
    }

    if(isSwitchOff && 1 == un->getPublishedState()) {
        stateElement.setAttribute("id", 100);
        stateElement.setAttribute("name", "Выкл");
        return stateElement;
    }

    stateElement.setAttribute("id", un->getPublishedState());
    switch (un->getPublishedState()) {
        case 113: {
            stateElement.setAttribute("name", "Открыто ключом");
            return stateElement;
        }
        case 112: {
            stateElement.setAttribute("name", "Закрыто ключом");
            return stateElement;
        }
        case 111: {
            stateElement.setAttribute("name", "Открыто");
            return stateElement;
        }
        case 110: {
            stateElement.setAttribute("name", "Закрыто");
            return stateElement;
        }
        case 101: {
            stateElement.setAttribute("name", "Вкл");
            return stateElement;
        }
        case 100: {
            stateElement.setAttribute("name", "Выкл");
            return stateElement;
        }
        case 21: {
            stateElement.setAttribute("name", "Тревога-ВСКРЫТИЕ");
            return stateElement;
        }
        case 20: {
            stateElement.setAttribute("name", "Тревога-СРАБОТКА");
            return stateElement;
        }
        case 12: {
            stateElement.setAttribute("name", "Неисправность");
            return stateElement;
        }
        case 10: {
            stateElement.setAttribute("name", "Нет связи");
            return stateElement;
        }
        case 1: {
            stateElement.setAttribute("name", "Норма");
            return stateElement;
        }
        default: {
            stateElement.setAttribute("id", 0);
            stateElement.setAttribute("name", "Неопр. сост.");
        }
    }
    return stateElement;
}


void GraphTerminal::sendAbonentEventsAndStates(JourEntity jour){
    sendAbonent(makeEventsAndStates(jour).toByteArray());
}

void GraphTerminal::sendAbonentEventsAndStates(QSharedPointer<UnitNode> un){
    sendAbonent(makeEventsAndStates(un).toByteArray());
}

void GraphTerminal::sendAbonentEventsAndStates(QSharedPointer<UnitNode> un, JourEntity jour){
    sendAbonent(makeEventsAndStates(un, jour).toByteArray());
}

void GraphTerminal::sendAbonent(QByteArray ba) {
//    //qDebug() << "GraphTerminal::sendAbonent()" << ba;
    if(ba.isEmpty() || abonents.keys().isEmpty())
        return;

    for(const auto& socket : as_const(abonents.keys())) {
        QByteArray buf;
        QTextStream ts(&buf);
        auto cw51 = QTextCodec::codecForName("windows-1251");

        ts.setCodec(cw51);
        ts << ba;
        ts.flush();

        m_tcpServer->writeData(socket, buf);
    }
}

void GraphTerminal::sendAbonentEventBook(JourEntity jour)
{
    sendAbonent(makeEventBook(jour).toByteArray());
}

QDomDocument GraphTerminal::makeEventBook(JourEntity jour) {
    QDomDocument doc;//(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "EventBook");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  devicesElement  =  doc.createElement("devices");
    RIFPlusPacketElement.appendChild(devicesElement);

    QSharedPointer<UnitNode>  un = nullptr;
    for(const auto &unTmp : as_const(ServerSettingUtils::getListTreeUnitNodes())) {
        if(unTmp->getName() == jour.getObject() &&
           unTmp->getNum1() == jour.getD1() &&
           unTmp->getNum2() == jour.getD2() &&
           unTmp->getNum3() == jour.getD3() &&
           unTmp->getType() == jour.getObjecttype()) {
            un = unTmp;
            break;
        }
    }
    if(nullptr == un) {
        doc.clear();
        return doc;
    }

    QDomElement  deviceElement  =  doc.createElement("device");
    if(nullptr != un) {
        QString id;
        if(!un->getMetaNames().isEmpty()) {
            id = un->getMetaNames().values().value(0, "Obj_X");
            id.remove("Obj_");
        } else {
            id = "X";
        }
        deviceElement.setAttribute("id", id);
        deviceElement.setAttribute("level", un->getLevel());
        deviceElement.setAttribute("type", (0 > un->getType() ? 0 : un->getType()));
        deviceElement.setAttribute("num1", un->getNum1());
        deviceElement.setAttribute("num2", un->getNum2());
        deviceElement.setAttribute("num3", un->getNum3());
        deviceElement.setAttribute("name", un->getName());
//        //qDebug() << "deviceElement.setAttribute(\"name\", un->getName(" << un->getName() << "))";
        deviceElement.setAttribute("lat", (0 == un->getLan() ? "0.00000000" : QString::number(un->getLan())));
        deviceElement.setAttribute("lon", (0 == un->getLon() ? "0.00000000" : QString::number(un->getLon())));
        deviceElement.setAttribute("description", (un->getDescription().isEmpty() ? "(null)" : un->getDescription()));
        deviceElement.setAttribute("dk", (0 != un->getDK() ? 1 : 0));
        deviceElement.setAttribute("option", ((TypeUnitNode::SD_BL_IP == un->getType() && 1 == un->getBazalt()) ? 1 : 0));
    }

    devicesElement.appendChild(deviceElement);

    QDomElement  statesElement  =  doc.createElement("states");
    deviceElement.appendChild(statesElement);

    QDomElement  stateElement  =  doc.createElement("state");
    stateElement.setAttribute("id", jour.getType());
    stateElement.setAttribute("datetime", jour.getCdate().toString("yyyy-MM-dd hh:mm:ss"));
    stateElement.setAttribute("name", jour.getComment());
    statesElement.appendChild(stateElement);
//    qDebug() << "GraphTerminal::makeEventBook()" << doc.toString();

    return doc;
}

QDomElement GraphTerminal::makeJourRecord(const JourEntity &jour, QDomElement &joursDom)
{
    joursDom.setAttribute("id",         jour.getId());                                    //"№/#";
    joursDom.setAttribute("datetime",   jour.getCdate().toString("yyyy-MM-dd hh:mm:ss")); //"Дата"
    joursDom.setAttribute("comment",    jour.getComment());                               //"Сообщение"
    joursDom.setAttribute("object",     jour.getObject());                                //"Объект"
    joursDom.setAttribute("reason",     jour.getReason());                                //"Причина"
    joursDom.setAttribute("measures",   jour.getMeasures());                              //"Принятые меры"
    joursDom.setAttribute("operatorid", jour.getOperatorid());                            //"Оператор"

    joursDom.setAttribute("type", jour.getType());

    joursDom.setAttribute("objecttype", jour.getObjecttype());
    joursDom.setAttribute("d1", jour.getD1());
    joursDom.setAttribute("d2", jour.getD2());
    joursDom.setAttribute("d3", jour.getD3());
    joursDom.setAttribute("d4", jour.getD4());

    joursDom.setAttribute("direction", jour.getDirection());
    return joursDom;
}

QDomDocument GraphTerminal::makeListJourRecord(const QList<JourEntity> &jourList)
{
    QDomDocument doc;//(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "ListJourRecord");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  joursElement  =  doc.createElement("jours");
    RIFPlusPacketElement.appendChild(joursElement);

    for(const auto &jour : jourList) {
        QDomElement  jourElement  =  doc.createElement("jour");
        joursElement.appendChild(jourElement);
        makeJourRecord(jour, jourElement);
    }

    return doc;
}
