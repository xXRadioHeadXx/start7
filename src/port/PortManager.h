#ifndef PORTMANAGER_H
#define PORTMANAGER_H

#include <QObject>
#include <QQueue>
#include "Port.h"
#include "GraphTerminal.h"

class UnitNode;
class DataBaseManager;
class GraphTerminal;
class AbstractRequester;
class DataQueueItem;
class PortManager : public QObject
{
    Q_OBJECT

private:

    const int MAX_COUNT_PORTS = 256;

    QSharedPointer<DataBaseManager> m_dbm;

    static QList<AbstractPort *> m_udpPortsVector;
    static GraphTerminal * graphTerminal;

    QList<DataQueueItem> overallReadQueue;
    QList<DataQueueItem> overallWriteQueue;

    static QList<QSharedPointer<AbstractRequester> > lsSCR;
    static QList<QSharedPointer<AbstractRequester> > lsWaiter;

    void setupPort(const int index = 0);
    void setupPort(AbstractPort *port);
//    ProcessDKWaiter * addProcessDKWaiter(QHostAddress address, int port, int index);
    static GraphTerminal * loadPortsTcpGraphTerminal(QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));
    static QList<AbstractPort *> loadPortsUdpObj(QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));
    static DataQueueItem parcingStatusWord0x41(DataQueueItem &item, DataQueueItem & resultRequest);
    static DataQueueItem parcingStatusWord0x31(DataQueueItem &item, DataQueueItem & resultRequest);
    static DataQueueItem parcingStatusWord0x32(DataQueueItem &item, DataQueueItem & resultRequest);
    static DataQueueItem parcingStatusWord0x33(DataQueueItem &item, DataQueueItem & resultRequest);
    static DataQueueItem parcingStatusWord0x34(DataQueueItem &item, DataQueueItem & resultRequest);
    static void procDK(QSharedPointer<UnitNode>  current, QSharedPointer<UnitNode>  previous);


public:
    explicit PortManager(QSharedPointer<DataBaseManager> dbm, QObject *parent = nullptr);
    explicit PortManager(DataBaseManager * dbm, QObject *parent = nullptr);
    virtual ~PortManager();
//    Port* createPort(AbstractPort::Protocol protocol, QObject *parent, const int index);
    void retranslate();
    void loadSettings();
    bool open(const int index);
    void close(const int index);
    bool portStatus(QString *string, const int index);
    bool isOpen(const int index);

    bool preparePort(QString ip, QString port, int index);

    QList<DataQueueItem> getOverallReadQueue() const;
    QList<DataQueueItem> popOverallReadQueue();
    void setOverallReadQueue(const QList<DataQueueItem> &value);
    void pushOverallReadQueue(const QList<DataQueueItem> &value);
    void pushOverallReadQueue(const DataQueueItem &value);

    QList<DataQueueItem> getOverallWriteQueue() const;
    QList<DataQueueItem> popOverallWriteQueue();
    void setOverallWriteQueue(const QList<DataQueueItem> &value);
    void pushOverallWriteQueue(const QList<DataQueueItem> &value);
    void pushOverallWriteQueue(const DataQueueItem &value);

    static QList<AbstractPort *> getUdpPortsVector();

    static QList<QSharedPointer<AbstractRequester> > getLsWaiter();
    void setLsWaiter(const QList<QSharedPointer<AbstractRequester> > &value);
    void appLsWaiter(QSharedPointer<AbstractRequester> value);
    void prependLsWaiter(QSharedPointer<AbstractRequester> value);
    static void removeLsWaiter(QSharedPointer<AbstractRequester> value);
    void clearLsWaiter();

    static QList<QSharedPointer<AbstractRequester> > getLsSCR();
    void setLsSCR(const QList<QSharedPointer<AbstractRequester> > &value);
    void appLsSCR(QSharedPointer<AbstractRequester> value);
    void prependLsSCR(QSharedPointer<AbstractRequester> value);
    void removeLsSCR(QSharedPointer<AbstractRequester> value);
    void clearLsSCR();


signals:
    void readyRead();
    void portError();
    void portChanged();

    void readyRead(int index);
    void portError(int index);
    void portChanged(int index);

public slots:
    QList<DataQueueItem> readAll(const int index);
    void write();
    void write(const QList<DataQueueItem> &data);
    void write(const DataQueueItem &data);
    void startStatusRequest();
    void requestAlarmReset(QSharedPointer<UnitNode> selUN = nullptr);
    void requestDK(bool out, QSharedPointer<UnitNode> selUN = nullptr);
    void requestDK(QSharedPointer<UnitNode> selUN = nullptr);
    void requestOnOffCommand(QSharedPointer<UnitNode> selUN, bool value);
    void requestOnOffCommand(bool out, QSharedPointer<UnitNode> selUN, bool value);
    void requestAutoOnOffIUCommand(bool out, QSharedPointer<UnitNode> selUN);
    void requestAutoOnOffIUCommand(QSharedPointer<UnitNode> selUN);
    void lockOpenCloseCommand(bool out, QSharedPointer<UnitNode> selUN, bool value);
    void lockOpenCloseCommand(QSharedPointer<UnitNode> selUN, bool value);
    void requestModeSensor(QSharedPointer<UnitNode> selUN, QByteArray stateWord);


    void manageOverallReadQueue();
    void unLostedConnect(QSharedPointer<UnitNode> un) const;
};

#endif // PORTMANAGER_H
