#include <QHostInfo>
#include <QDebug>
#include <QNetworkDatagram>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTcpSocket>

#include "DataQueueItem.h"
#include "Port.h"
#include "Utils.h"
#include "global.h"

void Port::setDbm(QSharedPointer<DataBaseManager> dbm)
{
    m_dbm = dbm;
}

bool Port::getProcDK() const
{
    return procDK;
}

void Port::setProcDK(bool value)
{
    procDK = value;
}

void Port::setProcDK_wTW()
{
    setProcDK(true);
    timerBeatProcDK.singleShot(timeIntervalProcDK, this, SLOT(beatProcDK_wTW));
    timerBeatProcDK.start();
}

void Port::beatProcDK_wTW()
{
    setProcDK(false);
    timerBeatProcDK.stop();
}

Port::Port(const AbstractPort::Protocol &protocol, QObject *parent, const int index, DataBaseManager *dbm) : AbstractPort(protocol, parent), portIndex(index), m_dbm(dbm) {}

Port::~Port() {

}

// interface -->
bool Port::open() {
    bool status = false;

    switch (protocol) {
    case AbstractPort::UDP:
        status = openUdpScoket(getStrPort());
        break;
    case AbstractPort::TCP:
        status = openTcpScoket(getStrIp(), getStrPort());
        break;
    default:
        break;
    }
    return status;
}

void Port::close() {
    switch (protocol) {
    case AbstractPort::UDP:
        if (m_ptrSocket) {
            m_ptrSocket->deleteLater();
            m_ptrSocket = nullptr;
        }
        break;
    case AbstractPort::TCP:
        if (m_ptrSocket) {
            m_ptrSocket->deleteLater();
            m_ptrSocket = nullptr;
        }
        break;
    default:
        break;
    }
}

QList<DataQueueItem> Port::readAll() {
    return popLocalReadQueue();
}

void Port::write(const QList<DataQueueItem> &data) {
    for(const auto& itm : data) {
        write(itm);
    }
}

void Port::write(const DataQueueItem &data, bool /*dbIns*/) {
    switch (getProtocol()) {
    case AbstractPort::UDP:
        if (m_ptrSocket) {
//            //qDebug() << "write i(" << data.portIndex() << ") s(" << data.data().size() << ") " << data.data().toHex();
            static_cast<QUdpSocket *>(m_ptrSocket.data())->writeDatagram(data.dataToWrite(), data.address(), data.port());

        }
        break;
    case AbstractPort::TCP:
        if (m_ptrSocket) {
//            //qDebug() << "write i(" << data.portIndex() << ") s(" << data.data().size() << ") " << data.data().toHex();
            static_cast<QTcpSocket *>(m_ptrSocket.data())->write(data.dataToWrite());
        }
        break;
    default:
        break;
    }
}

void Port::write() {
     write(popLocalWriteQueue());
}

bool Port::isOpen() {
    switch (getProtocol()) {
    case AbstractPort::UDP:
//        if(udpSocket != NULL)
//            return udpSocket->isOpen();
        return m_ptrSocket != NULL;
    case AbstractPort::TCP:
        return (m_ptrSocket->state() == QAbstractSocket::ConnectedState);
    default:
        return false;
    }
    return false;
}
// interface <--

void Port::prepareUdpScoket(QString ip, QString port) {
    setStrIp(ip);
    setStrPort(port);
}

Port * Port::typeDefPort(const AbstractPort * port) {
    if(AbstractPort::UDP == port->getProtocol())
        return (Port *)port;
    else if(AbstractPort::TCP == port->getProtocol())
        return (Port *)port;
    else
        return nullptr;
}


bool Port::openUdpScoket(QString port)
{
    if (port.isEmpty()) {
        //qDebug() << "Returns false when the IP address or port number is wrong.";
        return false; // Returns false when the IP address or port number is wrong.
    }

//    for(const auto& tmp : as_const(getStIpPort()))
//        //qDebug() << QHostAddress(tmp.first)<< "port " << tmp.second;

    if(nullptr == m_ptrSocket)
        m_ptrSocket = QSharedPointer<QUdpSocket>::create();

    if (m_ptrSocket->bind(QHostAddress::Any, (quint16)port.toInt(), QUdpSocket::ShareAddress) == false) {
        //qDebug() << "Return false when the port is occupied.";
        return false; // Return false when the port is occupied.
    }

//    ip edit false teperb .?!
    qDebug() << "connect(" <<
    connect(m_ptrSocket.data(), SIGNAL(readyRead()), this, SLOT(readMessage()), Qt::QueuedConnection)
             << ")";

    return true; // return, because the UDP protocol does not need to connect.
}

bool Port::openTcpScoket(QString host, QString port)
{
    if (port.isEmpty()) {
        //qDebug() << "Returns false when the IP address or port number is wrong.";
        return false; // Returns false when the IP address or port number is wrong.
    }

    if(nullptr == m_ptrSocket)
        m_ptrSocket = QSharedPointer<QTcpSocket>::create();
    m_ptrSocket->connectToHost(QHostAddress(host), (quint16)port.toInt());

    QObject::connect(m_ptrSocket.data(),&QAbstractSocket::disconnected,[]()->void{qDebug("Disconnected");});

    if (m_ptrSocket->state() != QAbstractSocket::ConnectedState) { //->bind(QHostAddress::Any, (quint16)port.toInt(), QUdpSocket::ShareAddress) == false) {
        //qDebug() << "Return false when the port is occupied.";
        return false; // Return false when the port is occupied.
    }

//    ip edit false teperb .?!
    qDebug() << "connect(" <<
    connect(m_ptrSocket.data(), SIGNAL(readyRead()), this, SLOT(readMessage()), Qt::QueuedConnection)
             << ")";

    return true; // return, because the UDP protocol does not need to connect.
}

void Port::readUdpDatagrams()
{
    auto socket = m_ptrSocket.objectCast<QUdpSocket>();
    QByteArray datagram;

    do {
        if(socket.isNull())
            return;
        int dataSize = socket->pendingDatagramSize();
        datagram.resize(dataSize);
        QHostAddress ip6Address;
        bool conversionOK = false;
        quint16 port;
        socket->readDatagram(datagram.data(), datagram.size(), &ip6Address, &port);
//        //qDebug() << "read i(" << getPortIndex() << ") s(" << dataSize << "/" << datagram.size() << ") " << datagram.toHex() << ip6Address << port;
        QHostAddress ip4Address(ip6Address.toIPv4Address(&conversionOK));
        if (conversionOK && getStHostAddress().contains(ip4Address) && !datagram.isEmpty() && !datagram.toHex().isEmpty())
        {
            pushLocalReadQueue(DataQueueItem(datagram, ip4Address, port, getPortIndex()));
//            // временно -->
//            if(Utils::isSavedMsg(datagram)) {
//                MessageEntity msg;
//                msg.setDirection("R");
//                msg.setBytearraydata(datagram);
//                m_dbm->insertCommandMsg_wS(msg);
//            }
//            // временно <--
        }
    } while (socket->hasPendingDatagrams());

    emit readyRead(getPortIndex());
}

void Port::readTcpDatagrams()
{
//    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
//    QByteArray buffer = m_ptrSocket->readAll();
}

void Port::readMessage()
{
    switch (getProtocol()) {
    case AbstractPort::UDP:
        readUdpDatagrams();
        break;
    case AbstractPort::TCP: {
        readTcpDatagrams();
        break;
    }
    default:
        break;
    }
    emit readyRead(getPortIndex());
}

QString Port::localHost() {
    QString ip;

    QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    foreach (QHostAddress address, info.addresses()) {
         if(address.protocol() == QAbstractSocket::IPv4Protocol) {
            ip = address.toString();
         }
    }
    return ip;
}

QHostAddress Port::hostAddress() {
    QString address = ((getStrIp() == "localhost") ? localHost() : getStrIp());
    return QHostAddress(address);
}

// getter setter -->
QString Port::getStrPort() const
{
    return strPort;
}

void Port::setStrPort(const QString &value)
{
    strPort = value;
}

QString Port::getStrIp() const
{
    return strIp;
}

void Port::setStrIp(const QString &value)
{
    strIp = value;
}

//AbstractPort::Protocol Port::getProtocol() const
//{
//    return protocol;
//}

void Port::setProtocol(const AbstractPort::Protocol &value)
{
    protocol = value;
}

QByteArray Port::getReadArray() const
{
    return readArray;
}

void Port::setReadArray(const QByteArray &value)
{
    readArray = value;
}

void Port::appendToReadArray(const QByteArray &value)
{
    if(!value.isEmpty())
    {
//        MessageEntity msg;
//        msg.setComment(value.toHex());
//        m_dbm->insertJourMsg(msg);

        readArray.append(value);
    }
}

int Port::getPortIndex() const
{
    return portIndex;
}

QSet<QPair<QString, QString> > Port::getStIpPort() const
{
    return stIpPort;
}

void Port::setSetIpPort(const QSet<QPair<QString, QString> > &value)
{
    stIpPort = value;
    stHostAddress.clear();
    for(const auto& tmp : as_const(stIpPort)) {
        stHostAddress.insert(Utils::hostAddress(tmp.first));
    }
}

void Port::addToSetIpPort(const QPair<QString, QString> &value) {
    stIpPort.insert(value);
    for(const auto& tmp : as_const(stIpPort)) {
        stHostAddress.insert(Utils::hostAddress(tmp.first));
    }
}

QSet<QHostAddress> Port::getStHostAddress() const
{
    return stHostAddress;
}

void Port::setStHostAddress(const QSet<QHostAddress> &value)
{
    stHostAddress = value;
}

QList<DataQueueItem> Port::getLocalReadQueue() const
{
    return localReadQueue;
}

void Port::setLocalReadQueue(const QList<DataQueueItem> &value)
{
    localReadQueue = value;
}

QList<DataQueueItem> Port::popLocalReadQueue() {
    auto result(getLocalReadQueue()); //QList<DataQueueItem>
    for(const auto& itm : as_const(result)) {
        localReadQueue.removeOne(itm);
    }
    return result;
}

void Port::pushLocalReadQueue(const QList<DataQueueItem> &value) {
    localReadQueue.append(value);
}

void Port::pushLocalReadQueue(const DataQueueItem &value){
    localReadQueue.append(value);
}

QList<DataQueueItem> Port::getLocalWriteQueue() const
{
    return localWriteQueue;
}

void Port::setLocalWriteQueue(const QList<DataQueueItem> &value)
{
    localWriteQueue = value;
}

QList<DataQueueItem> Port::popLocalWriteQueue() {
    auto result(getLocalWriteQueue()); //QList<DataQueueItem>
    for(const auto& itm : as_const(result)) {
        localWriteQueue.removeOne(itm);
    }
    return result;
}
void Port::pushLocalWriteQueue(const QList<DataQueueItem> &value) {
    localWriteQueue.append(value);
}

void Port::pushLocalWriteQueue(const DataQueueItem &value){
    localWriteQueue.append(value);
}
// getter setter <--
