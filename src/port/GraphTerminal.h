#ifndef GRAPHTERMINAL_H
#define GRAPHTERMINAL_H

#include <QObject>
#include "JourEntity.h"
#include "DataQueueItem.h"

class TcpServer;
class QTcpSocket;
class UnitNode;
class QDomElement;
class QDomDocument;
class GraphTerminal : public QObject
{
    Q_OBJECT
private:
    static QSharedPointer<TcpServer> m_tcpServer;
    QList<DataQueueItem> overallReadQueue;
    QList<DataQueueItem> overallWriteQueue;

    static QHash<QTcpSocket*, QByteArray*> abonents;

    void procCommands(DataQueueItem itm);
    void procKeepAlive(QDomElement root);
    void procEventBook(QDomElement root);
    void procEventsAndStates(DataQueueItem itm);
    void procAlarmsReset(QDomElement root);
    void procDbStart(DataQueueItem itm);

    QDomDocument makeInitialStatus(QString docType = "InitialStatus");
    QDomDocument makeEventsAndStates(QString docType = "EventsAndStates");
    QByteArray makeProtocolVersionInfo();
    static QDomDocument makeEventsAndStates(JourEntity jour);
    static QDomDocument makeEventsAndStates(QSharedPointer<UnitNode> un);
    static QDomDocument makeEventsAndStates(QSharedPointer<UnitNode> un, JourEntity jour);
    static QDomElement makeActualStateElement(QSharedPointer<UnitNode>  un, QDomElement &stateElement);
    static QDomDocument makeEventBook(JourEntity jour);

    static QDomElement makeJourRecord(const JourEntity &jour, QDomElement &joursDom);
    static QDomDocument makeListJourRecord(const QList<JourEntity> &jourList);

public:
    explicit GraphTerminal(int nPort, QObject *parent = nullptr);

    QList<DataQueueItem> getOverallReadQueue() const;
    QList<DataQueueItem> popOverallReadQueue();
    DataQueueItem popReadQueue();
    void setOverallReadQueue(const QList<DataQueueItem> &value);
    void pushOverallReadQueue(const QList<DataQueueItem> &value);

    QList<DataQueueItem> getOverallWriteQueue() const;
    QList<DataQueueItem> popOverallWriteQueue();
    DataQueueItem popWriteQueue();
    void setOverallWriteQueue(const QList<DataQueueItem> &value);
    void pushOverallWriteQueue(const QList<DataQueueItem> &value);

private slots:
    void manageOverallReadQueue();
    void disconnected();

public slots:
    void pushOverallReadQueue(const DataQueueItem &value);
    void pushReadQueue(const DataQueueItem &value);
    void pushOverallWriteQueue(const DataQueueItem &value);

public:
    static void sendAbonentEventBook(JourEntity jour);
    static void sendAbonentEventsAndStates(JourEntity jour);
    static void sendAbonentEventsAndStates(QSharedPointer<UnitNode> un);
    static void sendAbonentEventsAndStates(QSharedPointer<UnitNode> un, JourEntity jour);
    static void sendAbonent(QByteArray ba);

signals:

};

#endif // GRAPHTERMINAL_H
