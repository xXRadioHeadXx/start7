#include "TcpServer.h"

#include <QDataStream>
#include <QTcpSocket>
#include <QTime>
#include <QDomDocument>
#include <Utils.h>
#include <global.h>

TcpServer::TcpServer(int nPort, QObject *parent) : QObject(parent), nPort(nPort)
 {
     m_ptrTcpServer = new QTcpServer(this);
     if (!m_ptrTcpServer->listen(QHostAddress::Any, nPort)) {
//         QMessageBox::critical(0,
//                               "Server Error",
//                               "Unable to start the server:"
//                               + m_ptrTcpServer->errorString()
//                              );
         //qDebug() << "TcpServer Error: Unable to start the server:" + m_ptrTcpServer->errorString();
         m_ptrTcpServer->close();
         delete m_ptrTcpServer;
         m_ptrTcpServer = nullptr;
         return;
     }
     connect(m_ptrTcpServer, SIGNAL(newConnection()), SLOT(newConnection()));
}

TcpServer::~TcpServer() {
    if(nullptr != m_ptrTcpServer) {
        m_ptrTcpServer->close();
        delete m_ptrTcpServer;
        m_ptrTcpServer = nullptr;
    }
}

bool TcpServer::writeData(QString host, QByteArray data)
{
    for(QTcpSocket * socket : as_const(buffers.keys())) {
        if(host == Utils::hostAddressToString(socket->peerAddress())) {
            return writeData(socket, data);
        }
    }

    return writeData(connectToHost(host), data);
}

QHash<QTcpSocket *, QByteArray *> TcpServer::getBuffers() const
{
    return buffers;
}

QTcpSocket * TcpServer::connectToHost(QString host)
{
    QTcpSocket * socket = new QTcpSocket;
    socket->connectToHost(host, nPort);
    connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
    QByteArray *buffer = new QByteArray();
    buffers.insert(socket, buffer);
    if(socket->waitForConnected())
        return socket;
    return nullptr;
}

bool TcpServer::writeData(QTcpSocket *socket, QByteArray data)
{
    if(nullptr == socket)
        return false;

    if(socket->state() == QAbstractSocket::ConnectedState)
    {
//        //qDebug() << "TcpServer::writeData(" << QString::fromLocal8Bit(data) << ")";
        socket->write(data); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}

void TcpServer::newConnection()
{
    while (m_ptrTcpServer->hasPendingConnections())
    {
        QTcpSocket *socket = m_ptrTcpServer->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
        QByteArray *buffer = new QByteArray();
        buffers.insert(socket, buffer);
    }
}

void TcpServer::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    buffers.remove(socket);
    socket->deleteLater();
    delete buffer;
}

void TcpServer::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
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
