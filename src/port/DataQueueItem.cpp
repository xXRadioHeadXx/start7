#include "DataQueueItem.h"
#include "global.h"
#include "UnitNode.h"
#include "SWPBLIPType0x41.h"

QByteArray DataQueueItem::preamble() const
{
    return m_preamble;
}

void DataQueueItem::setPreamble(const QByteArray &preamble)
{
    m_preamble = preamble;
}

int DataQueueItem::getSpecialSkipTimeInterval() const
{
    return specialSkipTimeInterval;
}

void DataQueueItem::setSpecialSkipTimeInterval(int value)
{
    specialSkipTimeInterval = value;
}

int DataQueueItem::getSpecialSkipTimeCount() const
{
    return specialSkipTimeCount;
}

void DataQueueItem::setSpecialSkipTimeCount(int value)
{
    specialSkipTimeCount = value;
}

DataQueueItem::DataQueueItem() noexcept : m_port(0), m_data(QByteArray()), m_portIndex(0) {}

DataQueueItem::DataQueueItem(const QByteArray data, QHostAddress address, int port, const int index) noexcept : m_port(port), m_address(address), m_data(data), m_portIndex(index) {}

DataQueueItem::DataQueueItem(const DataQueueItem & parent)
{
    m_data = parent.data();
    m_portIndex = parent.portIndex();
    m_address = parent.address();
    m_port = parent.port();
}

DataQueueItem::DataQueueItem(DataQueueItem && parent)
{
    m_data = parent.data();
    m_portIndex = parent.portIndex();
    m_address = parent.address();
    m_port = parent.port();
}

DataQueueItem::~DataQueueItem() {}


QByteArray DataQueueItem::data() const {return m_data;}

QByteArray DataQueueItem::dataToWrite() const { return preamble() + data(); }

void DataQueueItem::setData(const QByteArray &data) {m_data = data;}


void DataQueueItem::setData() {m_data.clear();}

int DataQueueItem::portIndex() const {return m_portIndex;}

QHostAddress DataQueueItem::address() const {return m_address;}

int DataQueueItem::port() const {return m_port;}

bool DataQueueItem::isValid() {return !data().isEmpty() && !address().isNull() && 0 < port() && -1 < portIndex();}

DataQueueItem& DataQueueItem::operator=(const DataQueueItem& right) {
    m_data = right.data();
    m_portIndex = right.portIndex();
    m_address = right.address();
    m_port = right.port();

    return *this;
}

DataQueueItem& DataQueueItem::operator=(DataQueueItem&& right) {
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



QByteArray DataQueueItem::data0x20 = QByteArray();

DataQueueItem DataQueueItem::fillOnOff0x20(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeOnOff0x20(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOnOff0x20(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x20.isEmpty()) {
        DataQueueItem::data0x20.append(static_cast<quint8>(0xB5));      //<SB>
        DataQueueItem::data0x20.append(static_cast<quint8>(0xFF));      //<ADDR>
        DataQueueItem::data0x20.append(static_cast<quint8>(0x01));      //<NBB> 0x00
        DataQueueItem::data0x20.append(static_cast<quint8>(0x20));      //<CMD> 0x20
//        DataQueueItem::data0x20.append(static_cast<quint8>(0xFF));      //<D1>
//        DataQueueItem::data0x20.append(Utils::getByteSumm(DataQueueItem::data0x20)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x20;
    if(nullptr != un) {
        if(TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::SD_BL_IP == un->getType() ||
           TypeUnitNode::IU_BL_IP == un->getType()) {
            out[1] = static_cast<quint8>(0xFF);
            out[2] = static_cast<quint8>(0x01);        //<NBB> 0x00
            out.append(static_cast<quint8>(0xFF));
        } else if(TypeUnitNode::RLM_C == un->getType()) {
            out[1] = static_cast<quint8>(un->getNum1());
            out[2] = static_cast<quint8>(0x02);        //<NBB> 0x02
            out.append(un->getStateWord(0x31u).getByteWord().right(2));
        } else if(TypeUnitNode::RLM_KRL == un->getType()) {
            out[1] = static_cast<quint8>(un->getNum1());
            out[2] = static_cast<quint8>(0x01);        //<NBB> 0x01
            out.append(un->getStateWord(0x31u).getByteWord().left(1));
        } else if(TypeUnitNode::TG_Base == un->getType() ||
                  TypeUnitNode::TG == un->getType()) {
            out[1] = static_cast<quint8>(un->getNum1());
            out[2] = static_cast<quint8>(0x07);        //<NBB> 0x07
            out.append(QByteArray().fill(0x00, 7));
        }
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    return out;
}

QByteArray DataQueueItem::data0x21 = QByteArray();

DataQueueItem DataQueueItem::fillDK0x21(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeDK0x21(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeDK0x21(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x21.isEmpty()) {
        DataQueueItem::data0x21.append(static_cast<quint8>(0xB5));      //<SB>
        DataQueueItem::data0x21.append(static_cast<quint8>(0xFF));      //<ADDR>
        DataQueueItem::data0x21.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x21.append(static_cast<quint8>(0x21));      //<CMD> 0x21
//        DataQueueItem::data0x21.append(Utils::getByteSumm(DataQueueItem::data0x21)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x21;
    if(nullptr != un) {
        if(TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::SD_BL_IP == un->getType() ||
           TypeUnitNode::IU_BL_IP == un->getType()) {
            out[1] = static_cast<quint8>(0xFF);
        } else if(TypeUnitNode::RLM_C == un->getType() ||
                  TypeUnitNode::RLM_KRL == un->getType() ||
                  TypeUnitNode::TG == un->getType() ||
                  TypeUnitNode::TG_Base == un->getType()) {
            out[1] = static_cast<quint8>(un->getNum1());
        }
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    return out;
}

QByteArray DataQueueItem::data0x22 = QByteArray();

DataQueueItem DataQueueItem::fillStatusRequest0x22(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeStatusRequest0x22(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeStatusRequest0x22(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x22.isEmpty()) {
        DataQueueItem::data0x22.append(static_cast<quint8>(0xB5));      //<SB>
        DataQueueItem::data0x22.append(static_cast<quint8>(0xFF));      //<ADDR>
        DataQueueItem::data0x22.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x22.append(static_cast<quint8>(0x22));      //<CMD> 0x22
//        DataQueueItem::data0x22.append(Utils::getByteSumm(DataQueueItem::data0x22)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x22;
    if(nullptr != un) {
        if(TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::SD_BL_IP == un->getType() ||
           TypeUnitNode::IU_BL_IP == un->getType()) {
            out[1] = static_cast<quint8>(0xFF);
        } else if(TypeUnitNode::RLM_C == un->getType() ||
                  TypeUnitNode::RLM_KRL == un->getType() ||
                  TypeUnitNode::TG == un->getType() ||
                  TypeUnitNode::TG_Base == un->getType()) {
            out[1] = static_cast<quint8>(un->getNum1());
        }
    } else {
        out[1] = static_cast<quint8>(0xFF);
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    return out;
}

QByteArray DataQueueItem::data0x23 = QByteArray();

DataQueueItem DataQueueItem::fillOnOff0x23(DataQueueItem &item, QSharedPointer<UnitNode>un)
{
    item.setData(DataQueueItem::makeOnOff0x23(un, true));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOnOff0x23(QSharedPointer<UnitNode> un, bool onOff)
{
    if(DataQueueItem::data0x23.isEmpty()) {
        DataQueueItem::data0x23.append(static_cast<quint8>(0xB5));      //<SB>
        DataQueueItem::data0x23.append(static_cast<quint8>(0xFF));      //<ADDR>
        DataQueueItem::data0x23.append(static_cast<quint8>(0x01));        //<NBB> 0x00
        DataQueueItem::data0x23.append(static_cast<quint8>(0x23));      //<CMD> 0x23
        DataQueueItem::data0x23.append(static_cast<quint8>(0xFF));      //<D1>
        DataQueueItem::data0x23.append(Utils::getByteSumm(DataQueueItem::data0x23)); //<CHKS>
    }

    if(un.isNull())
        return QByteArray(DataQueueItem::data0x23);
    else if(TypeUnitNode::IU_BL_IP != un->getType())
        return QByteArray(DataQueueItem::data0x23);

    QSharedPointer<UnitNode> target = un;

//    if(pun.isNull()) {
//        pun = target;
//    }
//    if(TypeUnitNode::BL_IP != pun->getType()) {
//        while(nullptr != pun) {
//            if(TypeUnitNode::BL_IP == pun->getType()) {
//                break;
//            }
//            pun = pun->getParentUN();
//        }
//    }
    auto reciver = UnitNode::findReciver(un);

    quint8 D1 = 0x00;
    int type = target->getType();

    const auto &swpReciver = reciver->swpBLIPType0x41();
    if(!reciver.isNull() && !swpReciver.isNull()) {
        D1 = swpReciver.byteWord().at(1) & 0b00001111;
        quint8 mask = 0x00;
        if(TypeUnitNode::SD_BL_IP == un->getType() && !un->swpSDBLIPType0x41().isNull())
            mask = un->swpSDBLIPType0x41().mask();
        else if(TypeUnitNode::IU_BL_IP == un->getType() && !un->swpIUBLIPType0x41().isNull())
            mask = un->swpIUBLIPType0x41().mask();
        if(onOff)
            D1 = D1 | mask;
        else if(!onOff)
            D1 = D1 & ~mask;
    } else {
        for(auto un : as_const(reciver->getListChilde())) {
            if(type != un->getType())
                continue;
            quint8 mask = 0x00;
            if(TypeUnitNode::SD_BL_IP == un->getType() && !un->swpSDBLIPType0x41().isNull())
                mask = un->swpSDBLIPType0x41().mask();
            else if(TypeUnitNode::IU_BL_IP == un->getType() && !un->swpIUBLIPType0x41().isNull())
                mask = un->swpIUBLIPType0x41().mask();

            if(TypeUnitNode::SD_BL_IP == un->getType() &&
                    !un->swpSDBLIPType0x41().isNull() &&
                    1 == un->swpSDBLIPType0x41().isOff())
                D1 = D1 & ~mask;
            else if(TypeUnitNode::IU_BL_IP == un->getType() &&
                    !un->swpIUBLIPType0x41().isNull() &&
                    1 == un->swpIUBLIPType0x41().isOff())
                D1 = D1 & ~mask;
            else
                D1 = D1 | mask;

            if(un == target && onOff)
                D1 = D1 | mask;
            else if(un == target && !onOff)
                D1 = D1 & ~mask;
        }
    }

    QByteArray data = DataQueueItem::data0x23;
    data[4] = D1;
    data.chop(1);
    data.append(Utils::getByteSumm(data)); //<CHKS>

    return data;
}

DataQueueItem DataQueueItem::fillOn0x23(DataQueueItem &item, QSharedPointer<UnitNode>un)
{
    item.setData(DataQueueItem::makeOn0x23(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOn0x23(QSharedPointer<UnitNode> un)
{
return DataQueueItem::makeOnOff0x23(un, true);
}

DataQueueItem DataQueueItem::fillOff0x23(DataQueueItem &item, QSharedPointer<UnitNode>un)
{
    item.setData(DataQueueItem::makeOff0x23(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOff0x23(QSharedPointer<UnitNode> un)
{
    return DataQueueItem::makeOnOff0x23(un, false);
}

QByteArray DataQueueItem::data0x24 = QByteArray();

DataQueueItem DataQueueItem::fillAlarmReset0x24(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeAlarmReset0x24(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeAlarmReset0x24(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x24.isEmpty()) {
        DataQueueItem::data0x24.append(static_cast<quint8>(0xB5));      //<SB>
        DataQueueItem::data0x24.append(static_cast<quint8>(0xFF));      //<ADDR>
        DataQueueItem::data0x24.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x24.append(static_cast<quint8>(0x24));      //<CMD> 0x24
//        DataQueueItem::data0x24.append(Utils::getByteSumm(DataQueueItem::data0x24)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x24;
    if(nullptr != un) {
        if(TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::SD_BL_IP == un->getType() ||
           TypeUnitNode::IU_BL_IP == un->getType()) {
            out[1] = static_cast<quint8>(0xFF);
        } else if(TypeUnitNode::RLM_C == un->getType() || TypeUnitNode::RLM_KRL == un->getType() || TypeUnitNode::TG == un->getType() ) {
            out[1] = static_cast<quint8>(un->getNum1());
        }
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    return out;
}

QByteArray DataQueueItem::data0x25 = QByteArray();

DataQueueItem DataQueueItem::fillOff0x25(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeOff0x25(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOff0x25(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x25.isEmpty()) {
        DataQueueItem::data0x25.append(static_cast<quint8>(0xB5));      //<SB>
        DataQueueItem::data0x25.append(static_cast<quint8>(0xFF));      //<ADDR>
        DataQueueItem::data0x25.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x25.append(static_cast<quint8>(0x25));      //<CMD> 0x25
//        DataQueueItem::data0x25.append(Utils::getByteSumm(DataQueueItem::data0x25)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x25;
    if(nullptr != un) {
        if(TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::SD_BL_IP == un->getType() ||
           TypeUnitNode::IU_BL_IP == un->getType()) {
            out[1] = static_cast<quint8>(0xFF);
        } else if(TypeUnitNode::RLM_C == un->getType() || TypeUnitNode::RLM_KRL == un->getType()) {
            out[1] = static_cast<quint8>(un->getNum1());
        }
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    return out;
}

QByteArray DataQueueItem::data0x26 = QByteArray();

DataQueueItem DataQueueItem::fillOn0x26(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeOn0x26(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOn0x26(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x26.isEmpty()) {
        DataQueueItem::data0x26.append(static_cast<quint8>(0xB5));      //<SB>
        DataQueueItem::data0x26.append(static_cast<quint8>(0xFF));      //<ADDR>
        DataQueueItem::data0x26.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x26.append(static_cast<quint8>(0x26));      //<CMD> 0x26
//        DataQueueItem::data0x26.append(Utils::getByteSumm(DataQueueItem::data0x26)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x26;
    if(nullptr != un) {
        if(TypeUnitNode::BL_IP == un->getType() ||
           TypeUnitNode::SD_BL_IP == un->getType() ||
           TypeUnitNode::IU_BL_IP == un->getType()) {
            out[1] = static_cast<quint8>(0xFF);
        } else if(TypeUnitNode::RLM_C == un->getType() || TypeUnitNode::RLM_KRL == un->getType()) {
            out[1] = static_cast<quint8>(un->getNum1());
        }
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>
    return out;
}

QByteArray DataQueueItem::data0x2A = QByteArray();

DataQueueItem DataQueueItem::fillStatusRequest0x2A(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeStatusRequest0x2A(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    item.setSpecialSkipTimeInterval(300);
    item.setSpecialSkipTimeCount(2);
    return item;
}

QByteArray DataQueueItem::makeStatusRequest0x2A(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x2A.isEmpty()) {
        DataQueueItem::data0x2A.append(static_cast<quint8>(0xB5));      //<SB>
        DataQueueItem::data0x2A.append(static_cast<quint8>(0xFF));      //<ADDR>
        DataQueueItem::data0x2A.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x2A.append(static_cast<quint8>(0x2A));      //<CMD> 0x2A
//        DataQueueItem::data0x2A.append(Utils::getByteSumm(DataQueueItem::data0x2A)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x2A;
    if(nullptr != un) {
        out[1] = static_cast<quint8>(un->getNum1());
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    return out;
}


QByteArray DataQueueItem::data0x2C = QByteArray();

DataQueueItem DataQueueItem::fillStatusRequest0x2C(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeStatusRequest0x2C(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    item.setSpecialSkipTimeInterval(300);
    item.setSpecialSkipTimeCount(2);
    return item;
}

QByteArray DataQueueItem::makeStatusRequest0x2C(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x2C.isEmpty()) {
        DataQueueItem::data0x2C.append(static_cast<quint8>(0xB5));      //<SB>
        DataQueueItem::data0x2C.append(static_cast<quint8>(0xFF));      //<ADDR>
        DataQueueItem::data0x2C.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x2C.append(static_cast<quint8>(0x2C));      //<CMD> 0x2C
//        DataQueueItem::data0x2C.append(Utils::getByteSumm(DataQueueItem::data0x2C)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x2C;
    if(nullptr != un) {
        out[1] = static_cast<quint8>(un->getNum1());
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    return out;
}


QByteArray DataQueueItem::data0x2E = QByteArray();

DataQueueItem DataQueueItem::fillStatusRequest0x2E(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeStatusRequest0x2E(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));
    item.setSpecialSkipTimeInterval(300);
    item.setSpecialSkipTimeCount(2);
    return item;
}

QByteArray DataQueueItem::makeStatusRequest0x2E(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x2E.isEmpty()) {
        DataQueueItem::data0x2E.append(static_cast<quint8>(0xB5));      //<SB>
        DataQueueItem::data0x2E.append(static_cast<quint8>(0xFF));      //<ADDR>
        DataQueueItem::data0x2E.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x2E.append(static_cast<quint8>(0x2E));      //<CMD> 0x2E
//        DataQueueItem::data0x2E.append(Utils::getByteSumm(DataQueueItem::data0x2E)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x2E;
    if(nullptr != un) {
        out[1] = static_cast<quint8>(un->getNum1());
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    return out;
}

bool DataQueueItem::isValideDirectionI(DataQueueItem &item)
{
    if(item.data().isEmpty() ||
       item.address().isNull() ||
       0 > item.port() ||
       -1 > item.portIndex())
        return false;
    auto itemData = item.data();
    while(0 == itemData.indexOf(static_cast<quint8>(0xFF))) {
        itemData.remove(0, 1);
    }
    try {
        if(6 > itemData.size())
            return false;
        quint8 SB = itemData.at(0),
                ADDR_r = itemData.at(1),
//                ADDR_s = itemData.at(2),
                NBB = itemData.at(3),
                CMD = itemData.at(4);
        if((6 + NBB) > itemData.size())
            return false;
        quint8 CHKS = itemData.at(5 + NBB);

        if(static_cast<quint8>(0xB5) != SB ||
                static_cast<quint8>(0xFE) != ADDR_r /*||
                static_cast<quint8>(0xFF != ADDR_s*/)
            return false;

        QByteArray tmpData = itemData;
        quint8 crc = Utils::getByteSumm(tmpData, 1, 5 + NBB - 1);
        if(crc != CHKS)
            return false;

        switch (CMD) {
        case static_cast<quint8>(0x30): {
            if(static_cast<quint8>(0x00) != NBB)
                return false;
            return true;
        }
        case static_cast<quint8>(0x31): {
            if(static_cast<quint8>(0x04) != NBB && static_cast<quint8>(0x03) != NBB)
                return false;
            return true;
        }
        case static_cast<quint8>(0x32): {
            if(static_cast<quint8>(0x0D) != NBB)
                return false;
            return true;
        }
        case static_cast<quint8>(0x33): {
            if(static_cast<quint8>(0x03) != NBB)
                return false;
            return true;
        }
        case static_cast<quint8>(0x34): {
            if(static_cast<quint8>(0x1C) != NBB)
                return false;
            return true;
        }
        case static_cast<quint8>(0x41): {
            if(static_cast<quint8>(0x04) != NBB)
                return false;
            return true;
        }
        case static_cast<quint8>(0x42): {
            if(static_cast<quint8>(0x02) != NBB)
                return false;
            return true;
        }
        default:
            return false;
        }

        return true;

    } catch (...) {
        //qDebug() << "fillDiagnosticTable catch exception ...";
    }


    return false;
}

