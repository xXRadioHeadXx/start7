#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>

class TcpServer : public QObject
{
    Q_OBJECT
private:
    QTcpServer * m_ptrTcpServer;
    quint16     m_nNextBlockSize;

public:
    explicit TcpServer(int nPort, QObject *parent = nullptr);
    virtual ~TcpServer();

    void sendToClient(QTcpSocket* pSocket, const QString& str);

public slots:
    virtual void slotNewConnection();
    void slotReadClient();

signals:

};

#endif // TCPSERVER_H
