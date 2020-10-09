#include "GraphTerminal.h"

#include <DataBaseManager.h>
#include <JourEntity.h>
#include <QDomDocument>
#include <SettingUtils.h>

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
    qDebug() << "GraphTerminal::manageOverallReadQueue() -->";
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

        qDebug() << "root.attribute(\"type\") " << type;
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
    qDebug() << "GraphTerminal::manageOverallReadQueue() <--";

}

void GraphTerminal::procCommands(DataQueueItem itm) {
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
                    if("0" == idCommand.nodeValue()) {
                        docAnswer = makeInitialStatus("InitialStatus answer command 0");
                        //
                    } else if("10000" == idCommand.nodeValue()) {
                        docAnswer = makeEventsAndStates("EventsAndStates answer command 10000");

                        //
                    } else if("10001" == idCommand.nodeValue()) {
                        //
                    } else if("100" == idCommand.nodeValue()) {
                        //
                    } else if("101" == idCommand.nodeValue()) {
                        //
                    } else if("133" == idCommand.nodeValue()) {
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

                }
            }
        }
    }
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
    QDomDocument doc(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "InitialStatus");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  devicesElement  =  doc.createElement("devices");
    RIFPlusPacketElement.appendChild(devicesElement);

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
        deviceElement.setAttribute("lat", un->getLan());
        deviceElement.setAttribute("lon", un->getLon());
        deviceElement.setAttribute("description", un->getDescription());
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

    qDebug() << "GraphTerminal::makeInitialStatus()" << doc.toString();

    return doc;
}

QDomDocument GraphTerminal::makeEventsAndStates(QString docType)
{
    QDomDocument doc(docType);

    QDomElement  RIFPlusPacketElement  =  doc.createElement("RIFPlusPacket");
    RIFPlusPacketElement.setAttribute("type", "EventsAndStates");
    doc.appendChild(RIFPlusPacketElement);

    QDomElement  devicesElement  =  doc.createElement("devices");
    RIFPlusPacketElement.appendChild(devicesElement);

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
        deviceElement.setAttribute("lat", un->getLan());
        deviceElement.setAttribute("lon", un->getLon());
        deviceElement.setAttribute("description", un->getDescription());
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

    qDebug() << "GraphTerminal::makeEventsAndStates()" << doc.toString();

    return doc;
}
