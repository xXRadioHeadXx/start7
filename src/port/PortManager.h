#ifndef PORTMANAGER_H
#define PORTMANAGER_H

#include <QObject>
#include <QSettings>
#include <QQueue>
#include <ProcessDKWaiter.h>

#include <StatusRequester.h>
#include <DataBaseManager.h>
#include <UnitNode.h>
#include <Port.h>
#include <DataQueueItem.h>
#include <ConfirmationAdmissionWaiter.h>
#include <OnOffIUWaiter.h>

class PortManager : public QObject
{
    Q_OBJECT

private:

    const int MAX_COUNT_PORTS = 256;

    DataBaseManager *m_dbm = nullptr;

    static QList<AbstractPort *> m_udpPortsVector;

    QList<DataQueueItem> overallReadQueue;
    QList<DataQueueItem> overallWriteQueue;

    QList<StatusRequester *> lsStatusRequester;
    QList<AbstractRequester *> lsWaiter;

    void setupPort(const int index = 0);
    void setupPort(AbstractPort *port);
    ProcessDKWaiter * addProcessDKWaiter(QHostAddress address, int port, int index);
    static QList<AbstractPort *> loadPorts(QString fileName = "rifx.ini");
    static DataQueueItem parcingStatusWord0x41(DataQueueItem &item, DataQueueItem & resultRequest);


public:
    explicit PortManager(QObject *parent, DataBaseManager *dbm);
    virtual ~PortManager();
    Port* createPort(QObject *parent, const int index);
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

    QList<AbstractRequester *> getLsWaiter() const;
    void setLsWaiter(const QList<AbstractRequester *> &value);
    void appLsWaiter(AbstractRequester *value);
    void preppLsWaiter(AbstractRequester *value);
    void removeLsWaiter(AbstractRequester *value);


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
    void requestDK(UnitNode *selUN = nullptr);
    void requestOnOffCommand(UnitNode *selUN, bool value);
    void requestAutoOnOffIUCommand(UnitNode *selUN);


    void manageOverallReadQueue();

};

#endif // PORTMANAGER_H
