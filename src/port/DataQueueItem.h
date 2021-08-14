#ifndef DATAQUEUEITEM_H
#define DATAQUEUEITEM_H

#include <QByteArray>
#include <QHostAddress>
#include "Utils.h"

class UnitNode;
class DataQueueItem
{
private:
    int m_port = -1;
    QHostAddress m_address;
    QByteArray m_data;
    QByteArray m_preamble;
    int m_portIndex = -1;
    int specialSkipTimeInterval = 0;
    int specialSkipTimeCount = 1;


    static QByteArray data0x20;
    static QByteArray data0x21;
    static QByteArray data0x22;
    static QByteArray data0x23;
    static QByteArray data0x24;
    static QByteArray data0x25;
    static QByteArray data0x26;
    static QByteArray data0x2A;
    static QByteArray data0x2C;
    static QByteArray data0x2E;

public:
    DataQueueItem() noexcept;
    DataQueueItem(const QByteArray data, QHostAddress address, int port, const int index) noexcept;

    DataQueueItem(const DataQueueItem&);
    DataQueueItem(DataQueueItem&&);

    virtual ~DataQueueItem();

    QByteArray data() const;
    QByteArray dataToWrite() const;
    void setData(const QByteArray &data);
    void setData();
    int portIndex() const;
    QHostAddress address() const;
    int port() const;
    bool isValid();
    DataQueueItem & operator=(const DataQueueItem&);
    DataQueueItem& operator=(DataQueueItem&&);

    bool operator==(const DataQueueItem &right) const;
    void setPort(int port);
    void setAddress(const QHostAddress &address);
    void setPortIndex(int portIndex);

    static DataQueueItem fillOnOff0x20(DataQueueItem &item, const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));
    static QByteArray makeOnOff0x20(const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));

    static DataQueueItem fillDK0x21(DataQueueItem &item, const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));
    static QByteArray makeDK0x21(const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));

    static DataQueueItem fillStatusRequest0x22(DataQueueItem &item, const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));
    static QByteArray makeStatusRequest0x22(const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));

    static QByteArray makeOnOff0x23(QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr), bool onOff = true);
    static DataQueueItem makeOnOff0x23(DataQueueItem &item, QSharedPointer<UnitNode>un = QSharedPointer<UnitNode>(nullptr));

    static QByteArray makeOn0x23(QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));
    static DataQueueItem fillOn0x23(DataQueueItem &item, QSharedPointer<UnitNode>un = QSharedPointer<UnitNode>(nullptr));

    static QByteArray makeOff0x23(QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));
    static DataQueueItem fillOff0x23(DataQueueItem &item, QSharedPointer<UnitNode>un = QSharedPointer<UnitNode>(nullptr));

    static DataQueueItem fillAlarmReset0x24(DataQueueItem &item, const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));
    static QByteArray makeAlarmReset0x24(const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));

    static DataQueueItem fillOff0x25(DataQueueItem &item, const QSharedPointer<UnitNode> un);
    static QByteArray makeOff0x25(const QSharedPointer<UnitNode> un);

    static DataQueueItem fillOn0x26(DataQueueItem &item, const QSharedPointer<UnitNode> un);
    static QByteArray makeOn0x26(const QSharedPointer<UnitNode> un);

    static DataQueueItem fillStatusRequest0x2A(DataQueueItem &item, const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));
    static QByteArray makeStatusRequest0x2A(const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));

    static DataQueueItem fillStatusRequest0x2C(DataQueueItem &item, const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));
    static QByteArray makeStatusRequest0x2C(const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));

    static DataQueueItem fillStatusRequest0x2E(DataQueueItem &item, const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));
    static QByteArray makeStatusRequest0x2E(const QSharedPointer<UnitNode> un = QSharedPointer<UnitNode>(nullptr));


    static bool isValideDirectionI(DataQueueItem &item);
    QByteArray preamble() const;
    void setPreamble(const QByteArray &preamble = QByteArray().fill(static_cast<quint8>(0xFF),3));
    int getSpecialSkipTimeInterval() const;
    void setSpecialSkipTimeInterval(int value);
    int getSpecialSkipTimeCount() const;
    void setSpecialSkipTimeCount(int value);
};

#endif // DATAQUEUEITEM_H
