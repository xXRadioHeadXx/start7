#ifndef GRAPHTERMINAL_H
#define GRAPHTERMINAL_H

#include <QObject>
#include <TcpServer.h>

class GraphTerminal : public QObject
{
    Q_OBJECT

    TcpServer * m_tcpServer = nullptr;
public:
    explicit GraphTerminal(int nPort, QObject *parent = nullptr);

private slots:
    void prt(QByteArray ba);
signals:

};

#endif // GRAPHTERMINAL_H
