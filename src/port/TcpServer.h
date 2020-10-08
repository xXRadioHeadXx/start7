#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <DataQueueItem.h>
#include <QObject>
#include <QTcpServer>

class TcpServer : public QObject
{
    Q_OBJECT
private:
    int nPort = -1;
    QTcpServer * m_ptrTcpServer;
    QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received

    QTcpSocket *connectToHost(QString host);

public:
    explicit TcpServer(int nPort, QObject *parent = nullptr);
    virtual ~TcpServer();


public slots:
    bool writeData(QString host, QByteArray data);
    bool writeData(QTcpSocket * socket, QByteArray data);


private slots:
    void newConnection();
    void disconnected();
    void readyRead();

signals:
//    void dataReceived(QByteArray);
    void dataReceived(DataQueueItem);


};

#endif // TCPSERVER_H
