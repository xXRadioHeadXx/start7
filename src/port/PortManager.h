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

    static std::list<AbstractPort *> m_udpPortsVector;
    static GraphTerminal * graphTerminal;

    std::list<DataQueueItem> overallReadQueue;
    std::list<DataQueueItem> overallWriteQueue;

    static std::list<QSharedPointer<AbstractRequester> > lsSCR;
    static std::list<QSharedPointer<AbstractRequester> > lsWaiter;

    QTimer timerFirstWakeUp;

    void setupPort(const int index = 0);
    void setupPort(AbstractPort *port);
//    ProcessDKWaiter * addProcessDKWaiter(QHostAddress address, int port, int index);
    static GraphTerminal * loadPortsTcpGraphTerminal(QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));
    static std::list<AbstractPort *> loadPortsUdpObj(QString fileName = QString( QCoreApplication::applicationDirPath() + "/rifx.ini" ));

    static DataQueueItem parcingStatusWord0x41(DataQueueItem &item, DataQueueItem & resultRequest);
    static bool procDkBLIPStatusWord0x41(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);
    static bool procUzoBLIPStatusWord0x41(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);
    static bool procIUBLIPStatusWord0x41(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);
    static bool procSDBLIPStatusWord0x41(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);

    static DataQueueItem parcingStatusWord0x42(DataQueueItem &item, DataQueueItem & resultRequest);
    static bool procDkBLIPStatusWord0x42(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);
    static bool procSDBLIPStatusWord0x42(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);

    static DataQueueItem parcingStatusWord0x31(DataQueueItem &item, DataQueueItem & resultRequest);
    static bool procDkStatusWord0x31(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);
    static bool procRlmStatusWord0x31(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);
    static bool procRlmCStatusWord0x31(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);
    static bool procTgStatusWord0x31(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);

    static DataQueueItem parcingStatusWord0x32(DataQueueItem &item, DataQueueItem & resultRequest);
    static bool procDkStatusWord0x32(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);
    static bool procTgStatusWord0x32(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);


    static DataQueueItem parcingStatusWord0x33(DataQueueItem &item, DataQueueItem & resultRequest);
    static bool procDkStatusWord0x33(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);
    static bool procTgStatusWord0x33(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);

    static DataQueueItem parcingStatusWord0x34(DataQueueItem &item, DataQueueItem & resultRequest);
    static bool procDkStatusWord0x34(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);
    static bool procTgStatusWord0x34(const QSharedPointer<UnitNode> &currentUN, const StateWord &stateWord);

    static void procDK(QSharedPointer<UnitNode>  current, QSharedPointer<UnitNode>  previous);

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

    std::list<DataQueueItem> &getOverallReadQueue();
    std::list<DataQueueItem> popOverallReadQueue();
    void setOverallReadQueue(const std::list<DataQueueItem> &value);
    void pushOverallReadQueue(const std::list<DataQueueItem> &value);
    void pushOverallReadQueue(const DataQueueItem &value);

    std::list<DataQueueItem> &getOverallWriteQueue();
    std::list<DataQueueItem> popOverallWriteQueue();
    void setOverallWriteQueue(const std::list<DataQueueItem> &value);
    void pushOverallWriteQueue(const std::list<DataQueueItem> &value);
    void pushOverallWriteQueue(const DataQueueItem &value);

    static std::list<AbstractPort *> getUdpPortsVector();

    static std::list<QSharedPointer<AbstractRequester> > getLsWaiter();
    void setLsWaiter(const std::list<QSharedPointer<AbstractRequester> > &value);
    void appLsWaiter(QSharedPointer<AbstractRequester> value);
    void prependLsWaiter(QSharedPointer<AbstractRequester> value);
    static void removeLsWaiter(QSharedPointer<AbstractRequester> value);
    void clearLsWaiter();

    static std::list<QSharedPointer<AbstractRequester> > getLsSCR();
    void setLsSCR(const std::list<QSharedPointer<AbstractRequester> > &value);
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
    std::list<DataQueueItem> readAll(const int index);
    void write();
    void write(const std::list<DataQueueItem> &data);
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
    static void unLostedConnect(QSharedPointer<UnitNode> un);
};

#endif // PORTMANAGER_H
