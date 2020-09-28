#include "GraphTerminal.h"

GraphTerminal::GraphTerminal(int nPort, QObject *parent) : QObject(parent)
{
    m_tcpServer = new TcpServer(nPort, this);
    connect(m_tcpServer, SIGNAL(dataReceived(QByteArray)), this, SLOT(prt(QByteArray)));
}

void GraphTerminal::prt(QByteArray ba)
{
    qDebug() << "GraphTerminal::prt(" << ba << ")";
}
