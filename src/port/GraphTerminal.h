#ifndef GRAPHTERMINAL_H
#define GRAPHTERMINAL_H

#include <DataQueueItem.h>
#include <QObject>
#include <TcpServer.h>
#include <QTcpSocket>
#include <qdom.h>
#include <JourEntity.h>

class GraphTerminal : public QObject
{
    Q_OBJECT
private:
    static TcpServer * m_tcpServer;
    QList<DataQueueItem> overallReadQueue;
    QList<DataQueueItem> overallWriteQueue;

    static QHash<QTcpSocket*, QByteArray*> abonents;

    void procCommands(DataQueueItem itm);
    void procKeepAlive(QDomElement root);
    void procEventBook(QDomElement root);
    void procEventsAndStates(DataQueueItem itm);
    void procAlarmsReset(QDomElement root);
    void procDbStart(QDomElement root);

    QDomDocument makeInitialStatus(QString docType = "InitialStatus");
    QDomDocument makeEventsAndStates(QString docType = "EventsAndStates");
    QByteArray makeProtocolVersionInfo();
    static QDomDocument makeEventBook(JourEntity jour);
    static QDomDocument makeEventBook(UnitNode *un);
    static QDomDocument makeEventBook(UnitNode *un, JourEntity jour);

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

    static void sendAbonentEventBook(JourEntity jour);
    static void sendAbonentEventBook(UnitNode *un);
    static void sendAbonentEventBook(UnitNode *un, JourEntity jour);
    static void sendAbonent(QByteArray ba);

signals:

};

#endif // GRAPHTERMINAL_H
