#ifndef PORTMANAGER_H
#define PORTMANAGER_H

#include <QObject>
#include <QSettings>
#include <QQueue>
#include <ProcessDKWaiter.h>

#include <DataBaseManager.h>
#include <UnitNode.h>
#include <Port.h>
#include <DataQueueItem.h>
#include <ConfirmationAdmissionWaiter.h>
#include <OnOffIUWaiter.h>
#include <StatusConnectRequester.h>
#include <GraphTerminal.h>
#include <MultiUNStatusConnectRequester.h>

class PortManager : public QObject
{
    Q_OBJECT

private:

    const int MAX_COUNT_PORTS = 256;

    DataBaseManager *m_dbm = nullptr;

    static QList<AbstractPort *> m_udpPortsVector;
    static GraphTerminal * graphTerminal;

    QList<DataQueueItem> overallReadQueue;
    QList<DataQueueItem> overallWriteQueue;

    static QList<AbstractRequester *> lsSCR;
    static QList<AbstractRequester *> lsWaiter;

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
    static void procDK(UnitNode * current, UnitNode * previous);


public:
    explicit PortManager(QObject *parent, DataBaseManager *dbm);
    virtual ~PortManager();
//    Port* createPort(AbstractPort::Protocol protocol, QObject *parent, const int index);
    void retranslate();
    void loadConfig(QSettings *config, const int index);
    void saveConfig(QSettings *config, const int index);
    void loadSettings(QSettings *config, const int index);
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

    static QList<AbstractRequester *> getLsWaiter();
    void setLsWaiter(const QList<AbstractRequester *> &value);
    void appLsWaiter(AbstractRequester *value);
    void prependLsWaiter(AbstractRequester *value);
    void removeLsWaiter(AbstractRequester *value);
    void clearLsWaiter();

    static QList<AbstractRequester *> getLsSCR();
    void setLsSCR(const QList<AbstractRequester *> &value);
    void appLsSCR(AbstractRequester *value);
    void prependLsSCR(AbstractRequester *value);
    void removeLsSCR(AbstractRequester *value);
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
    void requestAlarmReset(UnitNode *selUN = nullptr);
    void requestDK(bool out, UnitNode *selUN = nullptr);
    void requestDK(UnitNode *selUN = nullptr);
    void requestOnOffCommand(UnitNode *selUN, bool value);
    void requestOnOffCommand(bool out, UnitNode *selUN, bool value);
    void requestAutoOnOffIUCommand(bool out, UnitNode *selUN);
    void requestAutoOnOffIUCommand(UnitNode *selUN);
    void lockOpenCloseCommand(bool out, UnitNode *selUN, bool value);
    void lockOpenCloseCommand(UnitNode *selUN, bool value);
    void requestModeSensor(UnitNode *selUN, QByteArray stateWord);


    void manageOverallReadQueue();
    void unLostedConnect(UnitNode *un) const;
};

#endif // PORTMANAGER_H
