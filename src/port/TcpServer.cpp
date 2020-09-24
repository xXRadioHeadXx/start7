#include "TcpServer.h"

#include <QDataStream>
#include <QTcpSocket>
#include <QTime>

//#include <QMessageBox>

TcpServer::TcpServer(int nPort, QObject *parent) : QObject(parent)
                                                 , m_nNextBlockSize(0)
 {
     m_ptrTcpServer = new QTcpServer(this);
     if (!m_ptrTcpServer->listen(QHostAddress::Any, nPort)) {
//         QMessageBox::critical(0,
//                               "Server Error",
//                               "Unable to start the server:"
//                               + m_ptrTcpServer->errorString()
//                              );
         qDebug() << "TcpServer Error: Unable to start the server:" + m_ptrTcpServer->errorString();
         m_ptrTcpServer->close();
         return;
     }
     connect(m_ptrTcpServer, SIGNAL(newConnection()),
             this, SLOT(slotNewConnection()));
}

TcpServer::~TcpServer() {
}


 // ----------------------------------------------------------------------
void TcpServer::slotNewConnection() {
     QTcpSocket * pClientSocket = m_ptrTcpServer->nextPendingConnection();

     connect(pClientSocket, SIGNAL(disconnected()),
             pClientSocket, SLOT(deleteLater())
            );     

     connect(pClientSocket, SIGNAL(readyRead()),
             this, SLOT(slotReadClient())
            );

     sendToClient(pClientSocket, "Server Response: Connected!");
 }

 // ----------------------------------------------------------------------
 void TcpServer::slotReadClient()
 {
     QTcpSocket * pClientSocket = (QTcpSocket *)sender();
     QDataStream in(pClientSocket);
     in.setVersion(QDataStream::Qt_5_3);
     for (;;) {
         if (!m_nNextBlockSize) {
             if (pClientSocket->bytesAvailable() < (int)sizeof(quint16)) {
                 break;
             }
             in >> m_nNextBlockSize;
         }

         if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
             break;
         }

         QTime   time;
         QString str;
         in >> time >> str;

         QString strMessage = time.toString() + " " + "Client has sent - " + str;
         qDebug() << strMessage;

         m_nNextBlockSize = 0;

         sendToClient(pClientSocket,
                      "Server Response: Received \"" + str + "\""
                     );
     }
 }

 // ----------------------------------------------------------------------
 void TcpServer::sendToClient(QTcpSocket* pSocket, const QString& str)
 {
     QByteArray  arrBlock;
     QDataStream out(&arrBlock, QIODevice::WriteOnly);
     out.setVersion(QDataStream::Qt_5_3);
     out << quint16(0) << QTime::currentTime() << str;

     out.device()->seek(0);
     out << quint16(arrBlock.size() - sizeof(quint16));

     pSocket->write(arrBlock);
 }
