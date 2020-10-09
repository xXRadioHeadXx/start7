#ifndef GRAPHTERMINAL_H
#define GRAPHTERMINAL_H

#include <DataQueueItem.h>
#include <QObject>
#include <TcpServer.h>
#include <qdom.h>

class GraphTerminal : public QObject
{
    Q_OBJECT
private:
    TcpServer * m_tcpServer = nullptr;
    QList<DataQueueItem> overallReadQueue;
    QList<DataQueueItem> overallWriteQueue;

    void procCommands(DataQueueItem itm);
    void procKeepAlive(QDomElement root);
    void procEventBook(QDomElement root);
    void procEventsAndStates(QDomElement root);
    void procAlarmsReset(QDomElement root);
    void procDbStart(QDomElement root);

    QDomDocument makeInitialStatus(QString docType = "InitialStatus");
    QDomDocument makeEventsAndStates(QString docType = "EventsAndStates");

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

public slots:
    void pushOverallReadQueue(const DataQueueItem &value);
    void pushReadQueue(const DataQueueItem &value);
    void pushOverallWriteQueue(const DataQueueItem &value);

signals:

};

#endif // GRAPHTERMINAL_H
