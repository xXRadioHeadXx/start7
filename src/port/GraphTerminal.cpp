#include "GraphTerminal.h"

#include <DataBaseManager.h>
#include <JourEntity.h>
#include <QDomDocument>
#include <SettingUtils.h>
#include <SignalSlotCommutator.h>
#include <global.hpp>

TcpServer * GraphTerminal::m_tcpServer = nullptr;
QHash<QTcpSocket*, QByteArray*> GraphTerminal::abonents = QHash<QTcpSocket*, QByteArray*>();


GraphTerminal::GraphTerminal(int nPort, QObject *parent) : QObject(parent)
{
    m_tcpServer = new TcpServer(nPort, this);
    connect(m_tcpServer, SIGNAL(dataReceived(DataQueueItem)), this, SLOT(pushOverallReadQueue(DataQueueItem)));
    connect(m_tcpServer, SIGNAL(dataReceived(DataQueueItem)), this, SLOT(manageOverallReadQueue()));

    try {
        QSettings settings(QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ), QSettings::IniFormat);
    #if (defined (_WIN32) || defined (_WIN64))
        settings.setIniCodec( "Windows-1251" );
    #else
        settings.setIniCodec( "UTF-8" );
    #endif

        settings.beginGroup("INTEGRATION");
        QString nHost = settings.value( "Host", "127.0.0.1" ).toString();
        settings.endGroup();

        m_tcpServer->writeData(nHost, "Hello!");

        QHash<QTcpSocket*, QByteArray*> buffers = m_tcpServer->getBuffers();
        for(QTcpSocket * socket : as_const(buffers.keys())) {
            abonents.insert(socket, buffers.value(socket));
            connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
        }

    }  catch (...) {
      qDebug() << "GraphTerminal::GraphTerminal -- some exception";
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
    //    qDebug() << "pushOverallReadQueue size(" << overallReadQueue.size() << ")";
}

void GraphTerminal::pushReadQueue(const DataQueueItem &value)
{
    overallReadQueue.append(value);
}

void GraphTerminal::pushOverallReadQueue(const DataQueueItem &value){
    overallReadQueue.append(value);
//    qDebug() << "pushOverallReadQueue size(" << overallReadQueue.size() << ")";
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
//    qDebug() << "GraphTerminal::manageOverallReadQueue() -->";
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

//        qDebug() << "root.attribute(\"type\") " << type;
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
            {
                JourEntity msgOn;
                msgOn.setObject(tr("Оператор"));
                msgOn.setType(1903);
                msgOn.setComment(tr("Удал. ком. Сброс тревог"));
                msgOn.setDirection(Utils::hostAddressToString(itm.address()));
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
//    qDebug() << "GraphTerminal::manageOverallReadQueue() <--";

}

void GraphTerminal::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    abonents.remove(socket);
}

void GraphTerminal::procCommands(DataQueueItem itm) {
    qDebug() << "GraphTerminal::procCommands() -->";
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
            qDebug() << nodeCommand.nodeName();
            if(!nodeCommand.attributes().contains("id"))
                continue;

            QDomNode idCommand = nodeCommand.attributes().namedItem("id");
//            QDomDocument docAnswer;
            QByteArray dataAnswer;
            qDebug() << "GraphTerminal::procCommands() idCommand.nodeValue(" << idCommand.nodeValue() << ")";
//            qDebug() << "GraphTerminal::procCommands() " << doc.toString();
            if("0" == idCommand.nodeValue()) {
                dataAnswer = makeInitialStatus("InitialStatus answer command 0").toByteArray();
                //
            } else if("10000" == idCommand.nodeValue()) {
//                dataAnswer = makeEventsAndStates("EventsAndStates answer command 10000").toByteArray();

                QHash<QTcpSocket*, QByteArray*> buffers = m_tcpServer->getBuffers();
                for(QTcpSocket * socket : as_const(buffers.keys())) {
                    if(socket->peerAddress() == itm.address()) {
                        abonents.insert(socket, buffers.value(socket));
                        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
                    }
                }
                //
            } else if("10001" == idCommand.nodeValue()) {

                for(const auto& socket : as_const(abonents.keys())) {
                    if(socket->peerAddress() == itm.address()) {
                        abonents.remove(socket);
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

                UnitNode * unTarget = nullptr;
                for(auto un : as_const(SettingUtils::getSetMetaRealUnitNodes())) {
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

                bool value = ("100" == idCommand.nodeValue()) ? false : ("101" == idCommand.nodeValue()) ? true : false;

                if(0 != unTarget->getBazalt() && 1 == unTarget->isAlarm() && "100" == idCommand.nodeValue()) {
                    SignalSlotCommutator::getInstance()->emitLockOpenCloseCommand(true, unTarget, false);
                } else if(0 != unTarget->getBazalt() && 1 == unTarget->isNorm() && "101" == idCommand.nodeValue()) {
                    SignalSlotCommutator::getInstance()->emitLockOpenCloseCommand(true, unTarget, true);
                } else if(0 != unTarget->getBazalt()) {
                    SignalSlotCommutator::getInstance()->emitLockOpenCloseCommand(true, unTarget, value);
                } else if(unTarget->isEditableOnOff() && 1 == unTarget->isOff() && "101" == idCommand.nodeValue()) {
                    const auto& setUn = Utils::findeSetAutoOnOffUN(unTarget);
                    if(setUn.isEmpty()) {
                        SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(true, unTarget, true);
                    } else {
                        SignalSlotCommutator::getInstance()->emitAutoOnOffIU(true, unTarget);
                    }
                } else if(unTarget->isEditableOnOff() && "101" == idCommand.nodeValue()) {
                    const auto& setUn = Utils::findeSetAutoOnOffUN(unTarget);
                    if(setUn.isEmpty()) {
                        SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(true, unTarget, true);
                    } else {
                        SignalSlotCommutator::getInstance()->emitAutoOnOffIU(true, unTarget);
                    }
                } else if(unTarget->isEditableOnOff() && (1 == unTarget->isOff()) && "101" == idCommand.nodeValue()) {
                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(true, unTarget, true);
                } else if(unTarget->isEditableOnOff() && 1 == unTarget->isOn() && "100" == idCommand.nodeValue()) {
                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(true, unTarget, false);
                } else  {
                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(true, unTarget, value);
                }
                //
            } else/* if("101" == idCommand.nodeValue()) {
                //
            } else*/ if(("133" == idCommand.nodeValue()) || ("1133" == idCommand.nodeValue())) {
                qDebug() << "-->";
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

                UnitNode * unTarget = nullptr;
                QSet<UnitNode *> unTargetSet;

                qDebug() << "id[" << deviceId.nodeValue() << "] level[" << deviceLevel.nodeValue() << "] type[" << deviceType.nodeValue() << "] num1[" << deviceNum1.nodeValue() << "] num2[" << deviceNum2.nodeValue() << "] num3[" << deviceNum3.nodeValue() << "]";

                for(UnitNode * un : as_const(SettingUtils::getListTreeUnitNodes())) {
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
                    if((TypeUnitNode::SD_BL_IP == un->getType() || TypeUnitNode::IU_BL_IP == un->getType() || TypeUnitNode::RLM_C == un->getType())) {
                        unTarget = un;
                        qDebug() << unTarget->toString();
                        break;
                    }
                }

                SignalSlotCommutator::getInstance()->emitRequestDK(true, unTarget);

                qDebug() << "<--";
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

                for(auto un : as_const(SettingUtils::getListTreeUnitNodes())) {
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

                UnitNode * unTarget = nullptr;
                QSet<UnitNode *> unTargetSet;

                qDebug() << "id[" << deviceId.nodeValue() << "] level[" << deviceLevel.nodeValue() << "] type[" << deviceType.nodeValue() << "] num1[" << deviceNum1.nodeValue() << "] num2[" << deviceNum2.nodeValue() << "] num3[" << deviceNum3.nodeValue() << "]";

                for(auto un : as_const(SettingUtils::getListTreeUnitNodes())) {
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
                        qDebug() << unTarget->toString();
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
                    unTarget->setControl(val);

                    JourEntity msgOn;
                    msgOn.setObject(unTarget->getName());
                    msgOn.setObjecttype(unTarget->getType());
                    msgOn.setD1(unTarget->getNum1());
                    msgOn.setD2(unTarget->getNum2());
                    msgOn.setD3(unTarget->getNum3());
                    msgOn.setDirection(Utils::hostAddressToString(itm.address()));
                    msgOn.setType((unTarget->getControl() ? 1137 : 1136));
                    msgOn.setComment(tr("Удал. ком. Контроль ") + (val ? tr("Вкл") : tr("Выкл")));
                    DataBaseManager::insertJourMsg_wS(msgOn);

                    dataAnswer = makeEventsAndStates(unTarget, msgOn).toByteArray();

                    if(unTarget->getControl()) {
                        unTarget->setStatus1(Status::Uncnown);
                        unTarget->setStatus2(Status::Uncnown);
                    }
                }
                qDebug() << "<--";

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

                UnitNode * unTarget = nullptr;
                QSet<UnitNode *> unTargetSet;

                qDebug() << "id[" << deviceId.nodeValue() << "] level[" << deviceLevel.nodeValue() << "] type[" << deviceType.nodeValue() << "] num1[" << deviceNum1.nodeValue() << "] num2[" << deviceNum2.nodeValue() << "] num3[" << deviceNum3.nodeValue() << "]";

                for(auto un : as_const(SettingUtils::getListTreeUnitNodes())) {
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
                    if((TypeUnitNode::SD_BL_IP == un->getType() || TypeUnitNode::IU_BL_IP == un->getType() || TypeUnitNode::RLM_C == un->getType())) {
                        unTarget = un;
                        qDebug() << unTarget->toString();
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
            } else {
                //
            }

            if(!dataAnswer.isEmpty()) {
                DataQueueItem itmAnswer = itm;
                itmAnswer.setData(dataAnswer);

                QHash<QTcpSocket*, QByteArray*> buffers = m_tcpServer->getBuffers();
                for(const auto& socket : as_const(buffers.keys())) {
                    if(socket->peerAddress() == itm.address()) {
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
    qDebug() << "GraphTerminal::procCommands() <--";
}

void GraphTerminal::procKeepAlive(QDomElement /*root*/) {

}

void GraphTerminal::procEventBook(QDomElement /*root*/) {

}

void GraphTerminal::procEventsAndStates(DataQueueItem itm) {
    qDebug() << "GraphTerminal::procEventsAndStates() -->";
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
//            qDebug() << nodeDevice.nodeName();
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
                    qDebug() << "GraphTerminal::procEventsAndStates() idState.nodeValue(" << idState.nodeValue() << ")";
                    qDebug() << "GraphTerminal::procEventsAndStates() " << doc.toString();

                    if("903" == idState.nodeValue()) {
                        {
                            JourEntity msgOn;
                            msgOn.setObject(tr("Оператор"));
                            msgOn.setType(1903);
                            msgOn.setComment(tr("Удал. ком. Сброс тревог"));
                            msgOn.setDirection(Utils::hostAddressToString(itm.address()));
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
                            DataBaseManager::insertJourMsg_wS(msgOn);
                            GraphTerminal::sendAbonentEventsAndStates(msgOn);
                        }
                    }

                    if(!docAnswer.isNull()) {
                        DataQueueItem itmAnswer = itm;
                        itmAnswer.setData(docAnswer.toByteArray());

                        QHash<QTcpSocket*, QByteArray*> buffers = m_tcpServer->getBuffers();
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

    qDebug() << "GraphTerminal::procEventsAndStates() <--";
}

void GraphTerminal::procAlarmsReset(QDomElement /*root*/) {

}

void GraphTerminal::procDbStart(DataQueueItem /*itm*/) {
    SignalSlotCommutator::getInstance()->emitForcedNewDuty(false);
}

QDomDocument GraphTerminal::makeInitialStatus(QString /*docType*/)
{
    QDomDocument doc;//(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "InitialStatus");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  devicesElement  =  doc.createElement("devices");
    RIFPlusPacketElement.appendChild(devicesElement);

    for(auto un : as_const(SettingUtils::getListTreeUnitNodes())) {
        // <device id="1" level="1" type="33" num1="1" num2="1" num3="1" name="Устройство 1" lat=”55.761248” lon: “37.608074” description=”Текстовое
        // описание длиной не более 50 символов” dk=”1” option=”0”>

        if(un->getMetaNames().isEmpty())
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
//        qDebug() << "deviceElement.setAttribute(\"name\", un->getName(" << un->getName() << "))";
        deviceElement.setAttribute("lat", (0 == un->getLan() ? "0.00000000" : QString::number(un->getLan())));
        deviceElement.setAttribute("lon", (0 == un->getLon() ? "0.00000000" : QString::number(un->getLon())));
        deviceElement.setAttribute("description", (un->getDescription().isEmpty() ? "(null)" : un->getDescription()));
        deviceElement.setAttribute("dk", (0 != un->getDK() ? 1 : 0));
        deviceElement.setAttribute("option", 0);

        devicesElement.appendChild(deviceElement);

        QDomElement  statesElement  =  doc.createElement("states");
        deviceElement.appendChild(statesElement);

        QDomElement  stateElement  =  doc.createElement("state");
        makeActualStateElement(un, stateElement);
        statesElement.appendChild(stateElement);
    }

//    qDebug() << "GraphTerminal::makeInitialStatus()" << doc.toString();

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

    for(UnitNode * un : as_const(SettingUtils::getListTreeUnitNodes())) {
        // <device id="0" level="0" type="33" num1="1" num2="1" num3="1" name="1" lat=”55.761248” lon: “37.608074” description=”Текстовое описание длиной
        // не более 50 символов”>

        if(un->getMetaNames().isEmpty())
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
        deviceElement.setAttribute("option", 0);

        devicesElement.appendChild(deviceElement);

        QDomElement  statesElement  =  doc.createElement("states");
        deviceElement.appendChild(statesElement);
        QDomElement  stateElement  =  doc.createElement("state");
        makeActualStateElement(un, stateElement);
        statesElement.appendChild(stateElement);
    }

//    qDebug() << "GraphTerminal::makeEventsAndStates()" << doc.toString();

    return doc;
}

QByteArray GraphTerminal::makeProtocolVersionInfo()
{
    return "<RIFPlusPacket type=\"ProtocolVersionInfo\"><version=\"1.19\"/></RIFPlusPacket>";
}

QDomDocument GraphTerminal::makeEventsAndStates(JourEntity jour) {
    return makeEventsAndStates(nullptr, jour);
}

QDomDocument GraphTerminal::makeEventsAndStates(UnitNode * un) {
    return makeEventsAndStates(un, JourEntity());
}

QDomDocument GraphTerminal::makeEventsAndStates(UnitNode * un, JourEntity jour)
{
    QDomDocument doc;//(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "EventsAndStates");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  devicesElement  =  doc.createElement("devices");
    RIFPlusPacketElement.appendChild(devicesElement);

    if(nullptr == un) {
        for(UnitNode * unTmp : as_const(SettingUtils::getListTreeUnitNodes())) {
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
//        qDebug() << "deviceElement.setAttribute(\"name\", un->getName(" << un->getName() << "))";
        deviceElement.setAttribute("lat", (0 == un->getLan() ? "0.00000000" : QString::number(un->getLan())));
        deviceElement.setAttribute("lon", (0 == un->getLon() ? "0.00000000" : QString::number(un->getLon())));
        deviceElement.setAttribute("description", (un->getDescription().isEmpty() ? "(null)" : un->getDescription()));
        deviceElement.setAttribute("dk", (0 != un->getDK() ? 1 : 0));
        deviceElement.setAttribute("option", 0);
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
    if(0 == jour.getType() || jour.getComment().isEmpty()/* || 136 == jour.getType() || 137 == jour.getType()*/){
        makeActualStateElement(un, stateElement);
        statesElement.appendChild(stateElement);
    }

//    qDebug() << "GraphTerminal::makeEventsAndStates()" << doc.toString();

    return doc;

}

QDomElement GraphTerminal::makeActualStateElement(UnitNode *un, QDomElement &stateElement)
{
    bool isLockPair = false;
    UnitNode * unLockSdBlIp = nullptr, * unLockIuBlIp = nullptr;
    if(1 >= un->getNum2() && 4 >= un->getNum2()) {
        UnitNode * reciver = un;
        while(nullptr != reciver) {
            if(TypeUnitNode::BL_IP == reciver->getType()) {
                break;
            }
            reciver = reciver->getParentUN();
        }
        if(nullptr != reciver) {
            for(const auto& tmpUN : as_const(reciver->getListChilde())) {
                if(TypeUnitNode::IU_BL_IP == tmpUN->getType() && tmpUN->getNum2() == un->getNum2()) {
                    unLockIuBlIp = tmpUN;
                    break;
                }
            }

            for(const auto& tmpUN : as_const(reciver->getListChilde())) {
                if(TypeUnitNode::SD_BL_IP == tmpUN->getType() && tmpUN->getNum2() == un->getNum2()) {
                    unLockSdBlIp = tmpUN;
                    break;
                }
            }
        }

        if(nullptr == unLockSdBlIp || nullptr == unLockIuBlIp)
            isLockPair = false;
        else if(0 != unLockSdBlIp->getBazalt())
            isLockPair = true;
    }
    //

    if(isLockPair && TypeUnitNode::SD_BL_IP == un->getType()) {
        if(1 == unLockSdBlIp->isAlarm() &&
           1 == unLockIuBlIp->isOff()) {
            //Открыто
            stateElement.setAttribute("id", 111);
            stateElement.setAttribute("name", "Открыто");
        } else if(1 == unLockSdBlIp->isNorm() &&
                  1 == unLockIuBlIp->isOn()) {
            //Закрыто
            stateElement.setAttribute("id", 110);
            stateElement.setAttribute("name", "Закрыто");
        } else if(1 == unLockSdBlIp->isAlarm() &&
                  1 == unLockIuBlIp->isOn()) {
            //Открыто ключом
            stateElement.setAttribute("id", 113);
            stateElement.setAttribute("name", "Открыто ключом");
        } else if(1 == unLockSdBlIp->isNorm() &&
                  1 == unLockIuBlIp->isOff()) {
            //Закрыто ключом
            stateElement.setAttribute("id", 112);
            stateElement.setAttribute("name", "Закрыто ключом");
        }
        stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    } else if((TypeUnitNode::SD_BL_IP == un->getType()) && ((1 == un->isAlarm()) || (1 == un->isWasAlarm()))) {
        //сохранение Тревога или Норма
        stateElement.setAttribute("id", 20);
        stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        stateElement.setAttribute("name", "Тревога-СРАБОТКА");
    } else if((TypeUnitNode::SD_BL_IP == un->getType()) && (1 == un->isNorm())) {
        stateElement.setAttribute("id", 1);
        stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        stateElement.setAttribute("name", "Норма");
    } else if((TypeUnitNode::SD_BL_IP == un->getType()) && (1 == un->isOff())) {
        stateElement.setAttribute("id", 100);
        stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        stateElement.setAttribute("name", "Выкл");
    } else if((TypeUnitNode::IU_BL_IP == un->getType()) && (1 == un->isOff())) {
        stateElement.setAttribute("id", 100);
        stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        stateElement.setAttribute("name", "Выкл");
    } else if((!isLockPair && TypeUnitNode::SD_BL_IP == un->getType() &&
               !un->getStateWord().isEmpty()) ||
              (!isLockPair && TypeUnitNode::IU_BL_IP == un->getType() &&
               !un->getStateWord().isEmpty())) {
         stateElement.setAttribute("id", 101);
         stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
         stateElement.setAttribute("name", "Вкл");
     } else {
        stateElement.setAttribute("id", 0);
        stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        stateElement.setAttribute("name", "Неопр. сост.");
    }
    return stateElement;
}


void GraphTerminal::sendAbonentEventsAndStates(JourEntity jour){
    sendAbonent(makeEventsAndStates(jour).toByteArray());
}

void GraphTerminal::sendAbonentEventsAndStates(UnitNode *un){
    sendAbonent(makeEventsAndStates(un).toByteArray());
}

void GraphTerminal::sendAbonentEventsAndStates(UnitNode *un, JourEntity jour){
    sendAbonent(makeEventsAndStates(un, jour).toByteArray());
}

void GraphTerminal::sendAbonent(QByteArray ba) {
//    qDebug() << "GraphTerminal::sendAbonent()" << ba;
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

    UnitNode * un = nullptr;
    for(UnitNode * unTmp : as_const(SettingUtils::getListTreeUnitNodes())) {
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
//        qDebug() << "deviceElement.setAttribute(\"name\", un->getName(" << un->getName() << "))";
        deviceElement.setAttribute("lat", (0 == un->getLan() ? "0.00000000" : QString::number(un->getLan())));
        deviceElement.setAttribute("lon", (0 == un->getLon() ? "0.00000000" : QString::number(un->getLon())));
        deviceElement.setAttribute("description", (un->getDescription().isEmpty() ? "(null)" : un->getDescription()));
        deviceElement.setAttribute("dk", (0 != un->getDK() ? 1 : 0));
        deviceElement.setAttribute("option", 0);
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
