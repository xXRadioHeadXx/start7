#include "TcpServer.h"

#include <QDataStream>
#include <QTcpSocket>
#include <QTime>
#include <QDomDocument>
#include "Utils.h"
#include "global.h"

TcpServer::TcpServer(int nPort, QObject *parent) : QObject(parent), nPort(nPort)
 {
     m_ptrTcpServer = QSharedPointer<QTcpServer>::create(this);
     if (!m_ptrTcpServer->listen(QHostAddress::Any, nPort)) {
//         QMessageBox::critical(0,
//                               "Server Error",
//                               "Unable to start the server:"
//                               + m_ptrTcpServer->errorString()
//                              );
         //qDebug() << "TcpServer Error: Unable to start the server:" + m_ptrTcpServer->errorString();
         m_ptrTcpServer->close();
         m_ptrTcpServer.clear();
         return;
     }
     connect(m_ptrTcpServer.data(), SIGNAL(newConnection()), SLOT(newConnection()));
}

TcpServer::~TcpServer() {
    if(!m_ptrTcpServer.isNull()) {
        m_ptrTcpServer->close();
    }
}

bool TcpServer::writeData(QString host, QByteArray data)
{
    for(const auto &socket : as_const(abonents.keys())) {
        if(host == Utils::hostAddressToString(socket->peerAddress())) {
            return writeData(socket, data);
        }
    }

    return writeData(connectToHost(host), data);
}

const QHash<QSharedPointer<QTcpSocket>, QSharedPointer<QByteArray> > TcpServer::getAbonents() const
{
    return abonents;
}

QSharedPointer<QTcpSocket> TcpServer::connectToHost(QString host)
{
    qDebug() << "TcpServer::connectToHost(" << "host" << ")";
    for(const auto &socket : abonents.keys()) {
        if(host == Utils::hostAddressToString(socket->peerAddress())) {
            return socket;
        }
    }

    auto ptrSocket = new QTcpSocket();
    auto socket = QSharedPointer<QTcpSocket>(ptrSocket, &QTcpSocket::deleteLater);
    socket->connectToHost(host, nPort);
    abonents.insert(socket, QSharedPointer<QByteArray>::create());
    connect(socket.data(), SIGNAL(readyRead()), SLOT(readyRead()));
    connect(socket.data(), SIGNAL(disconnected()), SLOT(disconnected()));
    connect(socket.data(), SIGNAL(()), SLOT(disconnected()));
    qDebug() << "GraphTerminal::connectToHost()" << abonents;
    if(socket->waitForConnected())
        return socket;

    return QSharedPointer<QTcpSocket>();
}

bool TcpServer::writeData(QSharedPointer<QTcpSocket> socket, QByteArray data)
{
    if(socket.isNull())
        return false;

    if(socket->state() == QAbstractSocket::ConnectedState)
    {
//        //qDebug() << "TcpServer::writeData(" << QString::fromLocal8Bit(data) << ")";
        if(-1 == socket->write(data))
            return false; //write the data itself
        return socket->waitForBytesWritten(500);
    }
    else
        return false;
}

void TcpServer::newConnection()
{
    auto server = static_cast<QTcpServer*>(sender());

    auto ptrSocket = server->nextPendingConnection();
    auto socket = QSharedPointer<QTcpSocket>(ptrSocket, &QTcpSocket::deleteLater);

    abonents.insert(socket,  QSharedPointer<QByteArray>::create());

    connect(socket.data(), SIGNAL(readyRead()), SLOT(readyRead()));
    connect(socket.data(), SIGNAL(disconnected()), SLOT(disconnected()));

//    qDebug() << "TcpServer::newConnection()" << abonents;
}

void TcpServer::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    for(const auto &key : abonents.keys()) {
        if(key.data() == socket) {
            abonents.remove(key);
            qDebug() << "TcpServer::disconnected()" << abonents;
            return;
        }
    }
}

void TcpServer::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QSharedPointer<QByteArray> buffer;
    for(const auto &key : abonents.keys()) {
        if(key.data() == socket) {
            buffer = abonents.value(key);
            break;
        }
    }
    while (socket->bytesAvailable() > 0)
    {
//        //qDebug() << "socket->bytesAvailable(" << socket->bytesAvailable() << ")";
        buffer->append(socket->readAll());
        while (0 < buffer->size()) //While can process data, process it
        {
            QByteArray data;

            data = buffer->mid(0);
            QString domStr = data;
            QDomDocument doc;
            if(doc.setContent(domStr)) {
//                //qDebug() << "TcpServer::(1)readyRead(" << domStr << ")";
                buffer->clear();

                DataQueueItem itm(data, socket->peerAddress(), socket->peerPort(), 0);

                emit dataReceived(itm);
            } else {

                int beginIndex = ((-1 != buffer->indexOf("<RIFPlusPacket>") || -1 != buffer->indexOf("<RIFPlusPacket ")) ? buffer->indexOf("<RIFPlusPacket") : -1);
                if(-1 == beginIndex)
                    break;
                else if(0 < beginIndex)
                    buffer->remove(0, beginIndex);
                beginIndex = 0;

                int endIndex = buffer->indexOf("</RIFPlusPacket>");
                if(-1 == endIndex)
                    break;

                data = buffer->mid(beginIndex, endIndex + 16);
                buffer->remove(beginIndex, endIndex + 16);

                domStr = data;
                if(doc.setContent(domStr)) {
                    //qDebug() << "TcpServer::(2)readyRead(" << domStr << ")";

                    DataQueueItem itm(domStr.toUtf8(), socket->peerAddress(), socket->peerPort(), 0);

                    emit dataReceived(itm);
                } else {
                    //qDebug() << "TcpServer::(3)readyRead[need correcting](" << domStr << ")";
                    if(domStr.contains("'"))
                        continue;

                    if(domStr.contains(QRegExp("<\\s*RIFPlusPacket\\s*type\\s*=\\s*\"Commands\"\\s*>\\s*<\\s*Commands>\\s*<Command\\s*id\\s*=\\s*\"\\d*\"\\s*\\/>\\s*<\\s*device\\s*id\\s*=\\s*\"\\d*\"\\s*>\\s*<\\/\\s*Commands\\s*>\\s*<\\/\\s*RIFPlusPacket\\s*>"))) {
                        //qDebug() << "TcpServer::(31) match";
                        domStr.insert(domStr.indexOf(QRegExp("<\/\s*Commands\s*>\s*<\/\s*RIFPlusPacket\s*>")), "</device>");
                    } else if(domStr.contains(QRegExp("<\\s*RIFPlusPacket\\s*type\\s*=\\s*\"Commands\"\\s*>\\s*<\\s*Commands>\\s*<Command\\s*id\\s*=\\s*\"\\d*\"\\s*name\\s*=\\s*\".*\"\\s*\\/>\\s*<\\s*device\\s*id\\s*=\\s*\"\\d*\"\\s*level\\s*=\\s*\"\\d*\"\\s*type\\s*=\\s*\"\\d*\"\\s*num1\\s*=\\s*\"\\d*\"\\s*num2\\s*=\\s*\"\\d*\"\\s*num3\\s*=\\s*\"\\d*\"\\s*>\\s*<\\/\\s*Commands\\s*>\\s*<\\/\\s*RIFPlusPacket\\s*>"))) {
                        //qDebug() << "TcpServer::(31) match";
                        domStr.insert(domStr.indexOf(QRegExp("<\/\s*Commands\s*>\s*<\/\s*RIFPlusPacket\s*>")), "</device>");
                    }

                    if(doc.setContent(domStr)) {
                        //qDebug() << "TcpServer::(32)readyRead(" << domStr << ")";

                        DataQueueItem itm(domStr.toUtf8(), socket->peerAddress(), socket->peerPort(), 0);

                        emit dataReceived(itm);

                        continue;
                    }
                }
            }
        }
    }
}

//qint32 ArrayToInt(QByteArray source)
//{
//    qint32 temp;
//    QDataStream data(&source, QIODevice::ReadWrite);
//    data >> temp;
//    return temp;
//}

//QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
//{
//    //Avoid use of cast, this is the Qt way to serialize objects
//    QByteArray temp;
//    QDataStream data(&temp, QIODevice::ReadWrite);
//    data << source;
//    return temp;
//}
