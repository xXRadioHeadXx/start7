#ifndef PORTMANAGER_H
#define PORTMANAGER_H

#include <QObject>
#include <QQueue>
#include "ShedulerDK.h"
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


    QTimer timerFirstWakeUp;

    void setupPort(const int index = 0);
    void setupPort(AbstractPort *port);
//    ProcessDKWaiter * addProcessDKWaiter(QHostAddress address, int port, int index);
    static GraphTerminal * loadPortsTcpGraphTerminal(QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));
    static QList<AbstractPort *> loadPortsUdpObj(QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

    static void procDK(QSharedPointer<UnitNode> &current, const QSharedPointer<UnitNode> &previous);

    static QSharedPointer<ShedulerDK> shedulerDK;

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
    static void finishDKWaiter(QSharedPointer<AbstractRequester> ar);

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
    void requestResetFlags(QSharedPointer<UnitNode> target = QSharedPointer<UnitNode>(nullptr));
    void requestDK(const bool isAuto = true, const bool fromAbonent = false, const QSharedPointer<UnitNode> unTarget = nullptr);
    void requestOnOffCommand(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget, const bool onOffValue);
    void requestAutoOnOffIUCommand(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget);
    void lockOpenCloseCommand(bool out, QSharedPointer<UnitNode> selUN, bool value);
    void lockOpenCloseCommand(QSharedPointer<UnitNode> selUN, bool value);
    void requestModeSensor(QSharedPointer<UnitNode> selUN);
//    void requestModeSensor(QSharedPointer<UnitNode> selUN, QByteArray stateWord);


    void manageOverallReadQueue();
    static void unLostedConnect(QSharedPointer<UnitNode> un);
};

#endif // PORTMANAGER_H
