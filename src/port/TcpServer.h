#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "../src/port/DataQueueItem.h"
#include <QObject>
#include <QTcpServer>

class TcpServer : public QObject
{
    Q_OBJECT
private:
    int nPort = -1;
    QSharedPointer<QTcpServer> m_ptrTcpServer;
    QHash<QSharedPointer<QTcpSocket>, QSharedPointer<QByteArray> > abonents; //We need a buffer to store data until block has completely received

    QSharedPointer<QTcpSocket> connectToHost(QString host);

public:
    explicit TcpServer(int nPort, QObject *parent = nullptr);
    virtual ~TcpServer();


    const QHash<QSharedPointer<QTcpSocket>, QSharedPointer<QByteArray> > getBuffers() const;

    const QHash<QSharedPointer<QTcpSocket>, QSharedPointer<QByteArray> > getAbonents() const;

public slots:
    bool writeData(QString host, QByteArray data);
    bool writeData(QSharedPointer<QTcpSocket> socket, QByteArray data);


private slots:
    void newConnection();
    void disconnected();
    void readyRead();

signals:
//    void dataReceived(QByteArray);
    void dataReceived(DataQueueItem);


};

#endif // TCPSERVER_H
