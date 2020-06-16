#ifndef DATAQUEUEITEM_H
#define DATAQUEUEITEM_H

#include <QByteArray>
#include <QHostAddress>

class /*Q_CORE_EXPORT*/ DataQueueItem
{
private:
    int m_port;
    QHostAddress m_address;
    QByteArray m_data;
    int m_portIndex;
public:
    explicit inline DataQueueItem() noexcept : m_port(0), m_data(QByteArray()), m_portIndex(0) {}
    explicit inline DataQueueItem(const QByteArray data, QHostAddress address, int port, const int index) noexcept : m_port(port), m_address(address), m_data(data), m_portIndex(index) {}
//    explicit inline DataQueueItem(const DataQueueItem & parent) noexcept : m_port(parent.port()), m_address(parent.address()), m_data(parent.data()), m_portIndex(parent.portIndex()) {}
    QByteArray data() const {return m_data;}
    void setData(const QByteArray &data) {m_data = data;};
    void setData() {m_data.clear();};
    int portIndex() const {return m_portIndex;}
    QHostAddress address() const {return m_address;}
    int port() const {return m_port;}

    bool isValid() {return !data().isEmpty() && !address().isNull() && 0 < port() && -1 < portIndex();}
    DataQueueItem& operator=(const DataQueueItem& right) {
        //проверка на самоприсваивание
        if (this == &right) {
            return *this;
        }
        m_data = right.data();
        m_portIndex = right.portIndex();
        m_address = right.address();
        m_port = right.port();
        return *this;
    }

    bool operator==(const DataQueueItem &right) const
    {
        if(this == &right)
            return true;
        return m_data == right.data() &&
               m_portIndex == right.portIndex() &&
               m_address == right.address() &&
               m_port == right.port();
    }
    void setPort(int port) { m_port = port; }
    void setAddress(const QHostAddress &address) { m_address = address; }
    void setPortIndex(int portIndex) { m_portIndex = portIndex; }
};

#endif // DATAQUEUEITEM_H
