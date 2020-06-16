#include "DataQueueItem.h"

DataQueueItem::DataQueueItem()
{

}

void DataQueueItem::setData(const QByteArray &data)
{
    m_data = data;
}

void DataQueueItem::setPort(int port)
{
    m_port = port;
}

void DataQueueItem::setPortIndex(int portIndex)
{
    m_portIndex = portIndex;
}

void DataQueueItem::setAddress(const QHostAddress &address)
{
    m_address = address;
}
