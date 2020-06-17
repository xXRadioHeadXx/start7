#ifndef DATAQUEUEITEM_H
#define DATAQUEUEITEM_H

#include <QByteArray>
#include <QHostAddress>
#include <UnitNode.h>
#include <Utils.h>

class DataQueueItem
{
private:
    int m_port;
    QHostAddress m_address;
    QByteArray m_data;
    int m_portIndex;

    static QByteArray data0x21;
    static QByteArray data0x22;
    static QByteArray data0x24;
    static QByteArray data0x20;
    static QByteArray data0x23;
public:
    DataQueueItem() noexcept;
    DataQueueItem(const QByteArray data, QHostAddress address, int port, const int index) noexcept;

    virtual ~DataQueueItem();

    QByteArray data() const;
    void setData(const QByteArray &data);
    void setData();
    int portIndex() const;
    QHostAddress address() const;
    int port() const;
    bool isValid();
    DataQueueItem& operator=(const DataQueueItem& right);

    bool operator==(const DataQueueItem &right) const;
    void setPort(int port);
    void setAddress(const QHostAddress &address);
    void setPortIndex(int portIndex);

    static DataQueueItem makeOnOff0x20(DataQueueItem &item, const UnitNode * un = nullptr);
    static QByteArray makeOnOff0x20(const UnitNode * un = nullptr);

    static DataQueueItem makeDK0x21(DataQueueItem &item, const UnitNode * un = nullptr);
    static QByteArray makeDK0x21(const UnitNode * un = nullptr);


    static DataQueueItem makeStatusRequest0x22(DataQueueItem &item, const UnitNode * un = nullptr);
    static QByteArray makeStatusRequest0x22(const UnitNode * un = nullptr);


    static DataQueueItem makeAlarmReset0x24(DataQueueItem &item, const UnitNode * un = nullptr);
    static QByteArray makeAlarmReset0x24(const UnitNode * un = nullptr);

    static QByteArray makeOnOff0x23(UnitNode *un = nullptr, bool onOff = true, UnitNode *pun = nullptr);
    static DataQueueItem makeOnOff0x23(DataQueueItem &item, UnitNode *un = nullptr);

    static bool isValideDirectionI(DataQueueItem &item);
};

#endif // DATAQUEUEITEM_H
