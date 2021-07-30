#ifndef PORT_H
#define PORT_H

#include <QByteArray>
#include <QUdpSocket>

#include "AbstractPort.h"
#include "DataBaseManager.h"

#include "DataQueueItem.h"

class Port :
        public AbstractPort
{
    Q_OBJECT
private:
    struct QHostAddressComparator {
        bool operator()(const QHostAddress &lhs, const QHostAddress &rhs) const
        {
            return lhs.toIPv4Address() < rhs.toIPv4Address();
        }
    };

    QSharedPointer<QAbstractSocket> m_ptrSocket;
    QString strPort;
    QString strIp;
    QByteArray readArray;
    const int portIndex;
    QSharedPointer<DataBaseManager> m_dbm;
    std::set<QPair<QString, QString> > stIpPort;

    std::set<QHostAddress, QHostAddressComparator> stHostAddress;

    std::list<DataQueueItem> localReadQueue;
    std::list<DataQueueItem> localWriteQueue;

    int timeIntervalProcDK = 11'000;
    QTimer timerBeatProcDK;
    bool procDK = false;

public:
#ifdef QT_DEBUG
    static bool readPass;
#endif


    explicit Port(const AbstractPort::Protocol &protocol = AbstractPort::UDP, QObject *parent = nullptr, const int index = 0, DataBaseManager *dbm = nullptr);
    virtual ~Port();

    // interface -->
    bool open();
    void close();
    void write(const std::list<DataQueueItem> &data);
    void write(const DataQueueItem &data, bool dbIns = true);
    bool isOpen();
    // interface <--

    void prepareUdpScoket(QString strIp, QString strPort);

    static Port * typeDefPort(const AbstractPort * port);

    // getter setter -->
    QString getStrPort() const;
    void setStrPort(const QString &value);

    QString getStrIp() const;
    void setStrIp(const QString &value);

    //AbstractPort::Protocol AbstractPort::getProtocol() const;
    void setProtocol(const AbstractPort::Protocol &value);

    QByteArray getReadArray() const;
    void setReadArray(const QByteArray &value);
    void appendToReadArray(const QByteArray &value);

    int getPortIndex() const;

    std::set<QPair<QString, QString> > getStIpPort() const;
    void setSetIpPort(const std::set<QPair<QString, QString> > &value);
    void addToSetIpPort(const QPair<QString, QString> &value);

    std::set<QHostAddress, QHostAddressComparator> getStHostAddress() const;
    void setStHostAddress(const std::set<QHostAddress, QHostAddressComparator> &value);

    std::list<DataQueueItem> getLocalReadQueue() const;
    std::list<DataQueueItem> popLocalReadQueue();
    void setLocalReadQueue(const std::list<DataQueueItem> &value);
    void pushLocalReadQueue(const std::list<DataQueueItem> &value);
    void pushLocalReadQueue(const DataQueueItem &value);

    std::list<DataQueueItem> getLocalWriteQueue() const;
    std::list<DataQueueItem> popLocalWriteQueue();
    void setLocalWriteQueue(const std::list<DataQueueItem> &value);
    void pushLocalWriteQueue(const std::list<DataQueueItem> &value);
    void pushLocalWriteQueue(const DataQueueItem &value);
    // getter setter <--


    void setDbm(QSharedPointer<DataBaseManager> dbm);

    bool getProcDK() const;
    void setProcDK(bool value);
    void setProcDK_wTW();

private:

    bool openUdpScoket(QString strPort);
    bool openTcpScoket(QString host, QString strPort);
    void readUdpDatagrams();
    void readTcpDatagrams();
    QHostAddress hostAddress();
    QString localHost();

public slots:
    // interface -->
    std::list<DataQueueItem> readAll();
    void write();
    // interface <--

private slots:

    void readMessage();
    void beatProcDK_wTW();

signals:

};

#endif // PORT_H
