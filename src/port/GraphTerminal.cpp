#include "GraphTerminal.h"

#include <QDomDocument>

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
            procCommands(root);
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

void GraphTerminal::procCommands(QDomElement root) {
    QDomNodeList nodeList = root.childNodes();

    for(int i = 0, n = nodeList.count(); i < n; i++) {
        QDomNode node = nodeList.at(i);
        if("Commands" == node.nodeName()) {
            QDomNodeList nodeListCommands = node.childNodes();
            for(int i = 0, n = nodeListCommands.count(); i < n; i++) {
                QDomNode nodeCommand = nodeListCommands.at(i);
                if("Command" == nodeCommand.nodeName()) {
                    qDebug() << nodeCommand.nodeName();
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
