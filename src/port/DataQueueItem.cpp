#include <DataQueueItem.h>

DataQueueItem::DataQueueItem() noexcept : m_port(0), m_data(QByteArray()), m_portIndex(0) {}

DataQueueItem::DataQueueItem(const QByteArray data, QHostAddress address, int port, const int index) noexcept : m_port(port), m_address(address), m_data(data), m_portIndex(index) {}

DataQueueItem::~DataQueueItem() {}


QByteArray DataQueueItem::data() const {return m_data;}

void DataQueueItem::setData(const QByteArray &data) {m_data = data;}


void DataQueueItem::setData() {m_data.clear();}

int DataQueueItem::portIndex() const {return m_portIndex;}

QHostAddress DataQueueItem::address() const {return m_address;}

int DataQueueItem::port() const {return m_port;}

bool DataQueueItem::isValid() {return !data().isEmpty() && !address().isNull() && 0 < port() && -1 < portIndex();}

DataQueueItem& DataQueueItem::operator=(const DataQueueItem& right) {
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

bool DataQueueItem::operator==(const DataQueueItem &right) const
    {
        if(this == &right)
            return true;
        return m_data == right.data() &&
               m_portIndex == right.portIndex() &&
               m_address == right.address() &&
               m_port == right.port();
    }

    void DataQueueItem::setPort(int port) { m_port = port; }

    void DataQueueItem::setAddress(const QHostAddress &address) { m_address = address; }

    void DataQueueItem::setPortIndex(int portIndex) { m_portIndex = portIndex; }


QByteArray DataQueueItem::data0x21 = QByteArray();

DataQueueItem DataQueueItem::makeDK0x21(DataQueueItem &item, const UnitNode * un)
{
    item.setData(DataQueueItem::makeDK0x21(un));
    return item;
}

QByteArray DataQueueItem::makeDK0x21(const UnitNode * un)
{
    if(DataQueueItem::data0x21.isEmpty()) {
        DataQueueItem::data0x21.append((quint8)0xB5);      //<SB>
        DataQueueItem::data0x21.append((quint8)0xFF);      //<ADDR>
        DataQueueItem::data0x21.append((char)0x00);        //<NBB> 0x00
        DataQueueItem::data0x21.append((quint8)0x21);      //<CMD> 0x21
        DataQueueItem::data0x21.append(Utils::getByteSumm(DataQueueItem::data0x21)); //<CHKS>
    }
    return QByteArray(DataQueueItem::data0x21);
}

QByteArray DataQueueItem::data0x22 = QByteArray();

DataQueueItem DataQueueItem::makeStatusRequest0x22(DataQueueItem &item, const UnitNode * un)
{
    item.setData(DataQueueItem::makeStatusRequest0x22(un));
    return item;
}

QByteArray DataQueueItem::makeStatusRequest0x22(const UnitNode * un)
{
    if(DataQueueItem::data0x22.isEmpty()) {
        DataQueueItem::data0x22.append((quint8)0xB5);      //<SB>
        DataQueueItem::data0x22.append((quint8)0xFF);      //<ADDR>
        DataQueueItem::data0x22.append((char)0x00);        //<NBB> 0x00
        DataQueueItem::data0x22.append((quint8)0x22);      //<CMD> 0x22
        DataQueueItem::data0x22.append(Utils::getByteSumm(DataQueueItem::data0x22)); //<CHKS>
    }

    return QByteArray(DataQueueItem::data0x22);
}

QByteArray DataQueueItem::data0x24 = QByteArray();

DataQueueItem DataQueueItem::makeAlarmReset0x24(DataQueueItem &item, const UnitNode * un)
{
    item.setData(DataQueueItem::makeAlarmReset0x24(un));
    return item;
}

QByteArray DataQueueItem::makeAlarmReset0x24(const UnitNode * un)
{
    if(DataQueueItem::data0x24.isEmpty()) {
        DataQueueItem::data0x24.append((quint8)0xB5);      //<SB>
        DataQueueItem::data0x24.append((quint8)0xFF);      //<ADDR>
        DataQueueItem::data0x24.append((char)0x00);        //<NBB> 0x00
        DataQueueItem::data0x24.append((quint8)0x24);      //<CMD> 0x24
        DataQueueItem::data0x24.append(Utils::getByteSumm(DataQueueItem::data0x24)); //<CHKS>
    }

    return QByteArray(DataQueueItem::data0x24);
}

QByteArray DataQueueItem::data0x20 = QByteArray();

DataQueueItem DataQueueItem::makeOnOff0x20(DataQueueItem &item, const UnitNode * un)
{
    item.setData(DataQueueItem::makeOnOff0x20(un));
    return item;
}

QByteArray DataQueueItem::makeOnOff0x20(const UnitNode * un)
{
    if(DataQueueItem::data0x20.isEmpty()) {
        DataQueueItem::data0x20.append((quint8)0xB5);      //<SB>
        DataQueueItem::data0x20.append((quint8)0xFF);      //<ADDR>
        DataQueueItem::data0x20.append((char)0x01);        //<NBB> 0x00
        DataQueueItem::data0x20.append((quint8)0x20);      //<CMD> 0x20
        DataQueueItem::data0x20.append((quint8)0xFF);      //<D1>
        DataQueueItem::data0x20.append(Utils::getByteSumm(DataQueueItem::data0x20)); //<CHKS>
    }

    return DataQueueItem::data0x20;
}

QByteArray DataQueueItem::data0x23 = QByteArray();


QByteArray DataQueueItem::makeOnOff0x23(UnitNode *un, bool onOff, UnitNode *pun)
{
    if(DataQueueItem::data0x23.isEmpty()) {
        DataQueueItem::data0x23.append((quint8)0xB5);      //<SB>
        DataQueueItem::data0x23.append((quint8)0xFF);      //<ADDR>
        DataQueueItem::data0x23.append((char)0x01);        //<NBB> 0x00
        DataQueueItem::data0x23.append((quint8)0x23);      //<CMD> 0x23
        DataQueueItem::data0x23.append((quint8)0xFF);      //<D1>
        DataQueueItem::data0x23.append(Utils::getByteSumm(DataQueueItem::data0x23)); //<CHKS>
    }

    if(nullptr == un)
        return QByteArray(DataQueueItem::data0x23);
    else if(TypeUnitNode::IU_BL_IP != un->getType())
        return QByteArray(DataQueueItem::data0x23);

    UnitNode * target = un;

    if(nullptr == pun) {
        pun = target;
    }
    if(TypeUnitNode::BL_IP != pun->getType()) {
        while(nullptr != pun) {
            if(TypeUnitNode::BL_IP == pun->getType()) {
                break;
            }
            pun = pun->getParentUN();
        }
    }
    UnitNode * reciver = pun;

    quint8 D1 = 0x00;
    if(TypeUnitNode::SD_BL_IP == target->getType() ||
            TypeUnitNode::IU_BL_IP == target->getType()) {
        while(nullptr != reciver) {
            if(TypeUnitNode::BL_IP == reciver->getType()) {
                break;
            }
            reciver = reciver->getParentUN();
        }
    }
    int type = target->getType();

    for(UnitNode * un : reciver->getListChilde()) {
        if(type != un->getType())
            continue;
        quint8 mask = 0;
        switch (un->getNum2()) {
        case 1:
            mask = 0x01;
            break;
        case 2:
            mask = 0x02;
            break;
        case 3:
            mask = 0x04;
            break;
        case 4:
            mask = 0x08;
            break;
        case 5:
            mask = 0x10;
            break;
        case 6:
            mask = 0x20;
            break;
        case 7:
            mask = 0x40;
            break;
        case 8:
            mask = 0x80;
            break;
        default:
            mask = 0x00;
            break;
        }

        if(TypeUnitNode::SD_BL_IP == un->getType() &&
                Status::Off == un->getStatus2() &&
                Status::Uncnown == un->getStatus1())
            D1 = D1 & ~mask;
        else if(TypeUnitNode::IU_BL_IP == un->getType() &&
                Status::Off == un->getStatus1())
            D1 = D1 & ~mask;
        else
            D1 = D1 | mask;

        if(un == target && onOff)
            D1 = D1 | mask;
        else if(un == target && !onOff)
            D1 = D1 & ~mask;
    }

    QByteArray data = DataQueueItem::data0x23;
    data[4] = D1;
    data.chop(1);
    data.append(Utils::getByteSumm(data)); //<CHKS>

    return data;
}

DataQueueItem DataQueueItem::makeOnOff0x23(DataQueueItem &item, UnitNode *un)
{
    item.setData(DataQueueItem::makeOnOff0x23(un, true));
    return item;
}

bool DataQueueItem::isValideDirectionI(DataQueueItem &item)
{
    if(item.data().isEmpty() || item.address().isNull() || 0 > item.port() || -1 > item.portIndex())
        return false;

    try {
        quint8 SB = item.data().at(0),
                ADDR_r = item.data().at(1),
                ADDR_s = item.data().at(2),
                NBB = item.data().at(3),
                CMD = item.data().at(4);
        quint8 CHKS = item.data().at(5 + NBB);

        if((quint8)0xB5 != SB ||
                (quint8)0xFE != ADDR_r ||
                (quint8)0xFF != ADDR_s)
            return false;

        QByteArray tmpData = item.data();
        quint8 crc = Utils::getByteSumm(tmpData, 1, 5 + NBB - 1);
        if(crc != CHKS)
            return false;

        switch (CMD) {
        case (quint8)0x41: {
            if((quint8)0x04 != NBB)
                return false;
            return true;
        }
        case (quint8)0x30: {
            if((quint8)0x00 != NBB)
                return false;
            return true;
        }
        default:
            return false;
        }

        return true;

    } catch (...) {
        qDebug() << "fillDiagnosticTable catch exception ...";
    }


    return false;
}

