#include "GraphTerminal.h"

#include <DataBaseManager.h>
#include <JourEntity.h>
#include <QDomDocument>
#include <SettingUtils.h>
#include <SignalSlotCommutator.h>

GraphTerminal::GraphTerminal(int nPort, QObject *parent) : QObject(parent)
{
    m_tcpServer = new TcpServer(nPort, this);
    connect(m_tcpServer, SIGNAL(dataReceived(DataQueueItem)), this, SLOT(pushOverallReadQueue(DataQueueItem)));
    connect(m_tcpServer, SIGNAL(dataReceived(DataQueueItem)), this, SLOT(manageOverallReadQueue()));

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
    for(DataQueueItem itm : result) {
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
    for(DataQueueItem itm : result) {
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
            continue;
        } else if("AlarmsReset" == type) {
            continue;
        } else if("DbStart" == type) {
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
    QDomNodeList nodeList = root.childNodes();

    for(int i = 0, n = nodeList.count(); i < n; i++) {
        QDomNode node = nodeList.at(i);
        if("Commands" == node.nodeName()) {
            QDomNodeList nodeListCommands = node.childNodes();
            for(int i = 0, n = nodeListCommands.count(); i < n; i++) {
                QDomNode nodeCommand = nodeListCommands.at(i);
                if("Command" == nodeCommand.nodeName()) {
                    qDebug() << nodeCommand.nodeName();
                    if(!nodeCommand.attributes().contains("id"))
                        continue;

                    QDomNode idCommand = nodeCommand.attributes().namedItem("id");
                    QDomDocument docAnswer;
                    qDebug() << "GraphTerminal::procCommands() idCommand.nodeValue(" << idCommand.nodeValue() << ")";
                    qDebug() << "GraphTerminal::procCommands() " << doc.toString();
                    if("0" == idCommand.nodeValue()) {
                        docAnswer = makeInitialStatus("InitialStatus answer command 0");
                        //
                    } else if("10000" == idCommand.nodeValue()) {
                        docAnswer = makeEventsAndStates("EventsAndStates answer command 10000");

                        QHash<QTcpSocket*, QByteArray*> buffers = m_tcpServer->getBuffers();
                        for(QTcpSocket * socket : buffers.keys()) {
                            if(socket->peerAddress() == itm.address()) {
                                abonents.insert(socket, buffers.value(socket));
                                connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
                            }
                        }
                        //
                    } else if("10001" == idCommand.nodeValue()) {

                        for(QTcpSocket * socket : abonents.keys()) {
                            if(socket->peerAddress() == itm.address()) {
                                abonents.remove(socket);
                            }
                        }
                        //
                    } else if(("100" == idCommand.nodeValue()) || ("101" == idCommand.nodeValue())) {
//                        <RIFPlusPacket type="Commands"><Commands><Command id="100" name=" Выключение ИУ"/><device id="1" level="1" type="4"
//                        num1="1" num2="1" num3="1"></Commands></RIFPlusPacket>
                        QDomNodeList nodeListDevices = nodeCommand.childNodes();
                        for(int i = 0, n = nodeListDevices.count(); i < n; i++) {
                            QDomNode nodeDevice = nodeListDevices.at(i);
                            if("device" == nodeDevice.nodeName()) {

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
                                for(UnitNode * un : SettingUtils::getSetMetaRealUnitNodes()) {
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

                                if(0 != unTarget->getBazalt() && Status::Alarm == unTarget->getStatus1() && "100" == idCommand.nodeValue()) {
                                    SignalSlotCommutator::getInstance()->emitLockOpenCloseCommand(unTarget, false);
                                } else if(0 != unTarget->getBazalt() && Status::Norm == unTarget->getStatus1() && "101" == idCommand.nodeValue()) {
                                    SignalSlotCommutator::getInstance()->emitLockOpenCloseCommand(unTarget, true);
                                } else if(0 != unTarget->getBazalt()) {
                                    SignalSlotCommutator::getInstance()->emitLockOpenCloseCommand(unTarget, value);
                                } else if(0 == unTarget->getBazalt() && TypeUnitNode::SD_BL_IP == unTarget->getType() && ((Status::Off == unTarget->getStatus2()) && (Status::Uncnown == unTarget->getStatus1())) && "101" == idCommand.nodeValue()) {
                                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(unTarget, true);
                                } else if(0 == unTarget->getBazalt() && TypeUnitNode::SD_BL_IP == unTarget->getType() && !((Status::Off == unTarget->getStatus2()) && (Status::Uncnown == unTarget->getStatus1())) && "100" == idCommand.nodeValue()) {
                                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(unTarget, false);
                                } else if(TypeUnitNode::IU_BL_IP == unTarget->getType() && Status::On == unTarget->getStatus1() && "100" == idCommand.nodeValue()) {
                                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(unTarget, false);
                                } else if(TypeUnitNode::IU_BL_IP == unTarget->getType() && Status::Off == unTarget->getStatus1() && "101" == idCommand.nodeValue()) {
                                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(unTarget, true);
                                } else {
                                    SignalSlotCommutator::getInstance()->emitRequestOnOffCommand(unTarget, value);
                                }

                            } else
                                continue;
                        }
                        //
                    } else/* if("101" == idCommand.nodeValue()) {
                        //
                    } else*/ if("133" == idCommand.nodeValue()) {
                        //
                    } else if("1133" == idCommand.nodeValue()) {
                        //
                    } else if("1" == idCommand.nodeValue()) {
                        //
                    } else if("137" == idCommand.nodeValue()) {
                        //
                    } else if("136" == idCommand.nodeValue()) {
                        //
                    } else if("1301" == idCommand.nodeValue()) {
                        //
                    } else if("2" == idCommand.nodeValue()) {
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

                    if(!docAnswer.isNull()) {
                        DataQueueItem itmAnswer = itm;
                        itmAnswer.setData(docAnswer.toByteArray());

                        QHash<QTcpSocket*, QByteArray*> buffers = m_tcpServer->getBuffers();
                        for(QTcpSocket * socket : buffers.keys()) {
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
    qDebug() << "GraphTerminal::procCommands() <--";
}

void GraphTerminal::procKeepAlive(QDomElement root) {

}

void GraphTerminal::procEventBook(QDomElement root) {

}

void GraphTerminal::procEventsAndStates(QDomElement root) {

}

void GraphTerminal::procAlarmsReset(QDomElement root) {

}

void GraphTerminal::procDbStart(QDomElement root) {

}

QDomDocument GraphTerminal::makeInitialStatus(QString docType)
{
    QDomDocument doc;//(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "InitialStatus");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  devicesElement  =  doc.createElement("devices");
    RIFPlusPacketElement.appendChild(devicesElement);

    if(true) {
//        <device id="0" level="0" type="0" num1="0" num2="0" num3="0" name="???????" lat="0.00000000" lon="0.00000000" description="(null)" dk="1" option="0">
//        <states>
//        <state id="0" datetime="2020-10-15 16:05:16" name="?????. ????."/>
//        </states>
        QDomElement  deviceElement  =  doc.createElement("device");
        QString id = "0";
        deviceElement.setAttribute("id", id);
        deviceElement.setAttribute("level", "0");
        deviceElement.setAttribute("type", "0");
        deviceElement.setAttribute("num1", "0");
        deviceElement.setAttribute("num2", "0");
        deviceElement.setAttribute("num3", "0");
        deviceElement.setAttribute("name", "Система");
        deviceElement.setAttribute("lat", "0.00000000");
        deviceElement.setAttribute("lon", "0.00000000");
        deviceElement.setAttribute("description", "(null)");
        deviceElement.setAttribute("dk", "0");
        deviceElement.setAttribute("option", 0);

        devicesElement.appendChild(deviceElement);

        QDomElement  statesElement  =  doc.createElement("states");
        deviceElement.appendChild(statesElement);

        QDomElement  stateElement  =  doc.createElement("state");
        stateElement.setAttribute("id", 0);
        stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        stateElement.setAttribute("name", "Неопр. сост.");
        statesElement.appendChild(stateElement);
    }


    for(UnitNode * un : SettingUtils::getListTreeUnitNodes()) {
        // <device id="1" level="1" type="33" num1="1" num2="1" num3="1" name="Устройство 1" lat=”55.761248” lon: “37.608074” description=”Текстовое
        // описание длиной не более 50 символов” dk=”1” option=”0”>

        if(un->getMetaNames().isEmpty())
            continue;

        QDomElement  deviceElement  =  doc.createElement("device");
        QString id = un->getMetaNames().values().first();
        id.remove("Obj_");
        deviceElement.setAttribute("id", id);
        deviceElement.setAttribute("level", un->getLevel());
        deviceElement.setAttribute("type", un->getType());
        deviceElement.setAttribute("num1", un->getNum1());
        deviceElement.setAttribute("num2", un->getNum2());
        deviceElement.setAttribute("num3", un->getNum3());
        deviceElement.setAttribute("name", un->getName());
//        qDebug() << "deviceElement.setAttribute(\"name\", un->getName(" << un->getName() << "))";
        deviceElement.setAttribute("lat", (0 == un->getLan() ? "0.00000000" : QString::number(un->getLan())));
        deviceElement.setAttribute("lon", (0 == un->getLon() ? "0.00000000" : QString::number(un->getLon())));
        deviceElement.setAttribute("description", (un->getDescription().isEmpty() ? "(null)" : un->getDescription()));
        deviceElement.setAttribute("dk", un->getDK());
        deviceElement.setAttribute("option", 0);

        devicesElement.appendChild(deviceElement);

        QDomElement  statesElement  =  doc.createElement("states");
        deviceElement.appendChild(statesElement);

        QString sql = "SELECT j.* FROM jour j WHERE j.id in ( SELECT MAX(j2.id) FROM jour j2 WHERE j2.type in (0, 1, 10, 20, 21, 100, 101, 110, 111) and j2.object = '" + un->getName() + "')";
        QList<JourEntity *> tmpList = DataBaseManager::getQueryMSGRecord(sql);
        QDomElement  stateElement  =  doc.createElement("state");
        if(tmpList.isEmpty()) {
            stateElement.setAttribute("id", 0);
            stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            stateElement.setAttribute("name", "Неопр. сост.");
        } else {
            JourEntity * jour = tmpList.first();
            stateElement.setAttribute("id", jour->getType());
            stateElement.setAttribute("datetime", jour->getCdate().toString("yyyy-MM-dd hh:mm:ss"));
            stateElement.setAttribute("name", jour->getComment());
        }
        statesElement.appendChild(stateElement);
    }

//    qDebug() << "GraphTerminal::makeInitialStatus()" << doc.toString();

    return doc;
}

QDomDocument GraphTerminal::makeEventsAndStates(QString docType)
{
    QDomDocument doc;//(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "EventsAndStates");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  devicesElement  =  doc.createElement("devices");
    RIFPlusPacketElement.appendChild(devicesElement);

    if(true) {
//        <device id="0" level="0" type="0" num1="0" num2="0" num3="0" name="???????" lat="0.00000000" lon="0.00000000" description="(null)" dk="1" option="0">
//        <states>
//        <state id="0" datetime="2020-10-15 16:05:16" name="?????. ????."/>
//        </states>
        QDomElement  deviceElement  =  doc.createElement("device");
        QString id = "0";
        deviceElement.setAttribute("id", id);
        deviceElement.setAttribute("level", "0");
        deviceElement.setAttribute("type", "0");
        deviceElement.setAttribute("num1", "0");
        deviceElement.setAttribute("num2", "0");
        deviceElement.setAttribute("num3", "0");
        deviceElement.setAttribute("name", "Система");
        deviceElement.setAttribute("lat", "0.00000000");
        deviceElement.setAttribute("lon", "0.00000000");
        deviceElement.setAttribute("description", "(null)");
//        deviceElement.setAttribute("dk", "0");
//        deviceElement.setAttribute("option", 0);

        devicesElement.appendChild(deviceElement);

        QDomElement  statesElement  =  doc.createElement("states");
        deviceElement.appendChild(statesElement);

        QDomElement  stateElement  =  doc.createElement("state");
        stateElement.setAttribute("id", 0);
        stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        stateElement.setAttribute("name", "Неопр. сост.");
        statesElement.appendChild(stateElement);
    }

    for(UnitNode * un : SettingUtils::getListTreeUnitNodes()) {
        // <device id="0" level="0" type="33" num1="1" num2="1" num3="1" name="1" lat=”55.761248” lon: “37.608074” description=”Текстовое описание длиной
        // не более 50 символов”>

        if(un->getMetaNames().isEmpty())
            continue;

        QDomElement  deviceElement  =  doc.createElement("device");
        QString id = un->getMetaNames().values().first();
        id.remove("Obj_");
        deviceElement.setAttribute("id", id);
        deviceElement.setAttribute("level", un->getLevel());
        deviceElement.setAttribute("type", un->getType());
        deviceElement.setAttribute("num1", un->getNum1());
        deviceElement.setAttribute("num2", un->getNum2());
        deviceElement.setAttribute("num3", un->getNum3());
        deviceElement.setAttribute("name", un->getName());
        deviceElement.setAttribute("lat", (0 == un->getLan() ? "0.00000000" : QString::number(un->getLan())));
        deviceElement.setAttribute("lon", (0 == un->getLon() ? "0.00000000" : QString::number(un->getLon())));
        deviceElement.setAttribute("description", (un->getDescription().isEmpty() ? "(null)" : un->getDescription()));
//        deviceElement.setAttribute("dk", un->getDK());
//        deviceElement.setAttribute("option", 0);

        devicesElement.appendChild(deviceElement);

        QDomElement  statesElement  =  doc.createElement("states");
        deviceElement.appendChild(statesElement);

        QString sql = "SELECT j.* FROM jour j WHERE j.id in ( SELECT MAX(j2.id) FROM jour j2 WHERE j2.type in (0, 1, 10, 20, 21, 100, 101, 110, 111) and j2.object = '" + un->getName() + "')";
        QList<JourEntity *> tmpList = DataBaseManager::getQueryMSGRecord(sql);
        QDomElement  stateElement  =  doc.createElement("state");
        if(tmpList.isEmpty()) {
            stateElement.setAttribute("id", 0);
            stateElement.setAttribute("datetime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            stateElement.setAttribute("name", "Неопр. сост.");
        } else {
            JourEntity * jour = tmpList.first();
            stateElement.setAttribute("id", jour->getType());
            stateElement.setAttribute("datetime", jour->getCdate().toString("yyyy-MM-dd hh:mm:ss"));
            stateElement.setAttribute("name", jour->getComment());
        }
        statesElement.appendChild(stateElement);
    }

//    qDebug() << "GraphTerminal::makeEventsAndStates()" << doc.toString();

    return doc;
}
