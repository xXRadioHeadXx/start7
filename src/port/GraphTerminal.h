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

signals:

};

#endif // GRAPHTERMINAL_H
