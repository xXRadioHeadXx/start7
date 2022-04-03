#include "DataQueueItem.h"
#include "global.h"
#include "UnitNode.h"
#include "swpblip/SWPBLIPType0x41.h"
#include "swptg/SWPTGType0x34.h"
#include "swpssoiblip/SWPSSOIBLIPType0x41.h"

#include "TopologyService.h"

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

DataQueueItem::DataQueueItem() :
    m_port(0)
  , m_data(QByteArray())
  , m_portIndex(0) {

}

DataQueueItem::DataQueueItem(const QByteArray data
                           , QHostAddress address
                           , int port
                           , const int index) :
    m_port(port)
  , m_address(address)
  , m_data(data)
  , m_portIndex(index) {

}

DataQueueItem::DataQueueItem(const DataQueueItem &parent)
{
    m_data = parent.data();
    m_preamble = parent.preamble();
    m_portIndex = parent.portIndex();
    m_address = parent.address();
    m_port = parent.port();
}

DataQueueItem::DataQueueItem(DataQueueItem &&parent)
{
    m_data = parent.data();
    m_preamble = parent.preamble();
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

DataQueueItem& DataQueueItem::operator=(const DataQueueItem &right) {
    m_data = right.data();
    m_preamble = right.preamble();
    m_portIndex = right.portIndex();
    m_address = right.address();
    m_port = right.port();

    return *this;
}

DataQueueItem& DataQueueItem::operator=(DataQueueItem&& right) {
    m_data = right.data();
    m_preamble = right.preamble();
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
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOnOff0x20(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x20.isEmpty()) {
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0xB5));      //<SB>
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0x01));      //<NBB> 0x00
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0x20));      //<CMD> 0x20
//        DataQueueItem::data0x20.append(static_cast<uint8_t>(0xFF));      //<D1>
//        DataQueueItem::data0x20.append(Utils::getByteSumm(DataQueueItem::data0x20)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x20;
    if(nullptr != un) {
        if(TypeUnitNodeEnum::BL_IP == un->getType() ||
           TypeUnitNodeEnum::SD_BL_IP == un->getType() ||
           TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
            out[1] = static_cast<uint8_t>(0xFF);
            out[2] = static_cast<uint8_t>(0x01);        //<NBB> 0x00
            out.append(static_cast<uint8_t>(0xFF));
        } else if(TypeUnitNodeEnum::SSOI_BL_IP == un->getType() ||
                  TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType() ||
                  TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()) {
            out[1] = static_cast<uint8_t>(un->getNum1());
            out[2] = static_cast<uint8_t>(0x01);        //<NBB> 0x00
            out.append(static_cast<uint8_t>(0xFF));
        } else if(TypeUnitNodeEnum::RLM_C == un->getType()) {
                    out[1] = static_cast<uint8_t>(un->getNum1());
            out[2] = static_cast<uint8_t>(0x02);        //<NBB> 0x02
            out.append(un->getStateWord(0x31u).getByteWord().isEmpty() ? QByteArray() : un->getStateWord(0x31u).getByteWord().right(2));
        } else if(TypeUnitNodeEnum::RLM_KRL == un->getType()) {
            out[1] = static_cast<uint8_t>(un->getNum1());
            out[2] = static_cast<uint8_t>(0x01);        //<NBB> 0x01
            out.append(un->getStateWord(0x31u).getByteWord().isEmpty() ? QByteArray() : un->getStateWord(0x31u).getByteWord().left(1));
        } else if(TypeUnitNodeEnum::TG_Base == un->getType() ||
                  TypeUnitNodeEnum::TG == un->getType()) {
            out[1] = static_cast<uint8_t>(un->getNum1());
            out[2] = static_cast<uint8_t>(0x07);        //<NBB> 0x07
            out.append(QByteArray().fill(0x00, 7));
        }
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    return out;
}

QByteArray DataQueueItem::makeOn0x20(const QSharedPointer<UnitNode> target)
{
    if(DataQueueItem::data0x20.isEmpty()) {
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0xB5));      //<SB>
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0x01));      //<NBB> 0x00
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0x20));      //<CMD> 0x20
//        DataQueueItem::data0x20.append(static_cast<uint8_t>(0xFF));      //<D1>
//        DataQueueItem::data0x20.append(Utils::getByteSumm(DataQueueItem::data0x20)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x20;
    if(target.isNull()) {
        out.append(Utils::getByteSumm(out)); //<CHKS>
        return out;
    }

    if(TypeUnitNodeEnum::SD_BL_IP != target->getType()
    && TypeUnitNodeEnum::SSOI_SD_BL_IP != target->getType()) {
        out.append(Utils::getByteSumm(out)); //<CHKS>
        return out;
    }

//    out[1] = static_cast<uint8_t>(0xFF);
    out[1] = static_cast<uint8_t>(target->getNum1());
    out[2] = static_cast<uint8_t>(0x01);        //<NBB> 0x00
    out.append(static_cast<uint8_t>(0xFF));

    uint8_t D1 = (target->getStateWord(0x41u).getByteWord().isEmpty() ? 0x00 : target->getStateWord(0x41u).getByteWord().at(3)); // байт для БЛ
    uint8_t mask = target->swpSDBLIPType0x41().mask();

    D1 = D1 | mask;
    out[4] = D1;

    out.append(Utils::getByteSumm(out)); //<CHKS>

    qDebug() << "DataQueueItem::makeOn0x20(" << target->toString() << ")" << out.toHex();

    return out;
}

QByteArray DataQueueItem::makeOff0x20(const QSharedPointer<UnitNode> target)
{
    if(DataQueueItem::data0x20.isEmpty()) {
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0xB5));      //<SB>
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0x01));      //<NBB> 0x00
        DataQueueItem::data0x20.append(static_cast<uint8_t>(0x20));      //<CMD> 0x20
//        DataQueueItem::data0x20.append(static_cast<uint8_t>(0xFF));      //<D1>
//        DataQueueItem::data0x20.append(Utils::getByteSumm(DataQueueItem::data0x20)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x20;
    if(target.isNull()) {
        out.append(Utils::getByteSumm(out)); //<CHKS>
        return out;
    }

    if(TypeUnitNodeEnum::SD_BL_IP != target->getType()
    && TypeUnitNodeEnum::SSOI_SD_BL_IP != target->getType()) {
        out.append(Utils::getByteSumm(out)); //<CHKS>
        return out;
    }

//    out[1] = static_cast<uint8_t>(0xFF);
    out[1] = static_cast<uint8_t>(target->getNum1());
    out[2] = static_cast<uint8_t>(0x01);        //<NBB> 0x00
    out.append(static_cast<uint8_t>(0xFF));

    uint8_t D1 = (target->getStateWord(0x41u).getByteWord().isEmpty() ? 0x00 : target->getStateWord(0x41u).getByteWord().at(3)); // байт для БЛ
    uint8_t mask = target->swpSDBLIPType0x41().mask();

    D1 = D1 & ~mask;
    out[4] = D1;

    out.append(Utils::getByteSumm(out)); //<CHKS>

    qDebug() << "DataQueueItem::makeOff0x20(" << target->toString() << ")" << out.toHex();

    return out;
}

QByteArray DataQueueItem::makeMode0x20(const QSharedPointer<UnitNode> target)
{

    QByteArray data0x20;
    data0x20.append(static_cast<uint8_t>(0xB5));      //<SB>
    data0x20.append(static_cast<uint8_t>(0xFF));      //<ADDR>
    data0x20.append(static_cast<uint8_t>(0x01));      //<NBB> 0x00
    data0x20.append(static_cast<uint8_t>(0x20));      //<CMD> 0x20

    QByteArray out = data0x20;
    if(target.isNull()) {
        out.append(Utils::getByteSumm(out)); //<CHKS>
        return out;
    }

    QByteArray stateWord;

    if(TypeUnitNodeEnum::RLM_C == target->getType()){
        stateWord = target->getStateWord(0x31u).getByteWord();
        out[1] = static_cast<uint8_t>(target->getNum1());
        out[2] = static_cast<uint8_t>(0x02);        //<NBB> 0x02
        out.append(stateWord.right(2));
        out[4] = stateWord.at(2);
        out[5] = stateWord.at(3);
    } else if(TypeUnitNodeEnum::RLM_KRL == target->getType()){
        stateWord = target->getStateWord(0x31u).getByteWord();
        out[1] = static_cast<uint8_t>(target->getNum1());
        out[2] = static_cast<uint8_t>(0x01);        //<NBB> 0x01
        out.append(stateWord.left(1));
        out[4] = stateWord.at(0);
    } else if(TypeUnitNodeEnum::TG_Base == target->getType()
           || TypeUnitNodeEnum::TG == target->getType()){
        stateWord = target->swpTGType0x34().C(target->getNum1()).byteWord();
        out[1] = static_cast<uint8_t>(target->getNum1());
        out[2] = static_cast<uint8_t>(0x07);        //<NBB> 0x07
        out.append(QByteArray().fill(0x00, 7));
        out = out.replace(4, 7, stateWord);
    } else if(TypeUnitNodeEnum::DD_T4K_M == target->getType()) {
        stateWord = target->getStateWord(0x34u).getByteWord();
        data0x20.clear();
        data0x20.append(static_cast<uint8_t>(0xB5));      //<SB>
        data0x20.append(static_cast<uint8_t>(target->getNum1())); //<ADDR>
        data0x20.append(static_cast<uint8_t>(0xFE));      //<ADDR>
        data0x20.append(static_cast<uint8_t>(23));      //<NBB> 0x00
        data0x20.append(static_cast<uint8_t>(0x20));      //<CMD> 0x20
        out = data0x20;
        out.append(stateWord);
    } else if(TypeUnitNodeEnum::DD_SOTA == target->getType()) {
        stateWord = target->getStateWord(0x34u).getByteWord();
        data0x20.clear();
        data0x20.append(static_cast<uint8_t>(0xB5));      //<SB>
        data0x20.append(static_cast<uint8_t>(target->getNum1())); //<ADDR>
        data0x20.append(static_cast<uint8_t>(0xFE));      //<ADDR>
        data0x20.append(static_cast<uint8_t>(12));      //<NBB> 0x00
        data0x20.append(static_cast<uint8_t>(0x20));      //<CMD> 0x20
        out = data0x20;
        out.append(stateWord);
    }

    out.append(Utils::getByteSumm(out)); //<CHKS>

    qDebug() << "DataQueueItem::makeMode0x20(" << target->toString() << ")" << out.toHex();

    return out;
}

QByteArray DataQueueItem::data0x21 = QByteArray();

DataQueueItem DataQueueItem::fillDK0x21(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeDK0x21(un));
    if(!un.isNull()
    && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeDK0x21(const QSharedPointer<UnitNode> un)
{
    QByteArray data0x21;

    if(!un.isNull()) {
        if(TypeUnitNodeEnum::BL_IP == un->getType()
        || TypeUnitNodeEnum::SD_BL_IP == un->getType()
        || TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
            data0x21.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x21.append(static_cast<uint8_t>(0xFF));      //<ADDR>
            data0x21.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x21.append(static_cast<uint8_t>(0x21));      //<CMD> 0x21
        } else if(TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()

               || TypeUnitNodeEnum::RLM_C == un->getType()

               || TypeUnitNodeEnum::RLM_KRL == un->getType()

               || TypeUnitNodeEnum::TG == un->getType()
               || TypeUnitNodeEnum::TG_Base == un->getType()) {
            data0x21.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x21.append(static_cast<uint8_t>(un->getNum1()));      //<ADDR>
            data0x21.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x21.append(static_cast<uint8_t>(0x21));      //<CMD> 0x21
        } else if(TypeUnitNodeEnum::BOD_T4K_M == un->getType()
               || TypeUnitNodeEnum::Y4_T4K_M == un->getType()
               || TypeUnitNodeEnum::DD_T4K_M == un->getType()

               || TypeUnitNodeEnum::BOD_SOTA == un->getType()
               || TypeUnitNodeEnum::Y4_SOTA == un->getType()
               || TypeUnitNodeEnum::DD_SOTA == un->getType()) {
            data0x21.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x21.append(static_cast<uint8_t>(un->getNum1()));      //<ADDR>
            data0x21.append(static_cast<uint8_t>(0xFE));      //<ADDR>
            data0x21.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x21.append(static_cast<uint8_t>(0x21));      //<CMD> 0x21
        }
    }
    data0x21.append(Utils::getByteSumm(data0x21)); //<CHKS>

    qDebug() << "DataQueueItem::makeDK0x21(" << un->toString() << ")" << data0x21.toHex();
    return data0x21;
}

QByteArray DataQueueItem::data0x22 = QByteArray();

DataQueueItem DataQueueItem::fillStatusRequest0x22(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeStatusRequest0x22(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeStatusRequest0x22(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x22.isEmpty()) {
        DataQueueItem::data0x22.append(static_cast<uint8_t>(0xB5));      //<SB>
        DataQueueItem::data0x22.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        DataQueueItem::data0x22.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x22.append(static_cast<uint8_t>(0x22));      //<CMD> 0x22
//        DataQueueItem::data0x22.append(Utils::getByteSumm(DataQueueItem::data0x22)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x22;
    if(nullptr != un) {
        if(TypeUnitNodeEnum::BL_IP == un->getType() ||
           TypeUnitNodeEnum::SD_BL_IP == un->getType() ||
           TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
            out[1] = static_cast<uint8_t>(0xFF);
        } else if(TypeUnitNodeEnum::SSOI_BL_IP == un->getType() ||
                  TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType() ||
                  TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType() ||
                  TypeUnitNodeEnum::RLM_C == un->getType() ||
                  TypeUnitNodeEnum::RLM_KRL == un->getType() ||
                  TypeUnitNodeEnum::TG == un->getType() ||
                  TypeUnitNodeEnum::TG_Base == un->getType()) {
            out[1] = static_cast<uint8_t>(un->getNum1());
        }
    } else {
        out[1] = static_cast<uint8_t>(0xFF);
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    return out;
}

QByteArray DataQueueItem::data0x23 = QByteArray();

DataQueueItem DataQueueItem::fillOnOff0x23(DataQueueItem &item, const QSharedPointer<UnitNode> &un)
{
    item.setData(DataQueueItem::makeOnOff0x23(un, true));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOnOff0x23(const QSharedPointer<UnitNode> &un, bool onOff)
{
    if(DataQueueItem::data0x23.isEmpty()) {
        DataQueueItem::data0x23.append(static_cast<uint8_t>(0xB5));      //<SB>
        DataQueueItem::data0x23.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        DataQueueItem::data0x23.append(static_cast<uint8_t>(0x01));        //<NBB> 0x00
        DataQueueItem::data0x23.append(static_cast<uint8_t>(0x23));      //<CMD> 0x23
        DataQueueItem::data0x23.append(static_cast<uint8_t>(0xFF));      //<D1>
        DataQueueItem::data0x23.append(Utils::getByteSumm(DataQueueItem::data0x23)); //<CHKS>
    }

    if(un.isNull()) {
        return QByteArray(DataQueueItem::data0x23);
    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP != un->getType()
           && TypeUnitNodeEnum::SSOI_SD_BL_IP != un->getType()
           && TypeUnitNodeEnum::SD_BL_IP != un->getType()
           && TypeUnitNodeEnum::IU_BL_IP != un->getType()
           && TypeUnitNodeEnum::BL_IP != un->getType()
           && TypeUnitNodeEnum::SSOI_BL_IP != un->getType()) {
        QByteArray out = DataQueueItem::data0x23;
        if(TypeUnitNodeEnum::SD_BL_IP != un->getType()
        && TypeUnitNodeEnum::IU_BL_IP != un->getType()
        && TypeUnitNodeEnum::BL_IP != un->getType()) {
            out[1] = static_cast<uint8_t>(un->getNum1());
            out.chop(1);
            out.append(Utils::getByteSumm(out)); //<CHKS>
        }
//        qDebug() << "DataQueueItem::makeOnOff0x23(" << un->toString() << ")" << onOff << out.toHex();

        return out;
    }

    QSharedPointer<UnitNode> target = un;

    auto reciver = TopologyService::findReciver(un);

    uint8_t D1 = 0x00;
    int type = target->getType();

    if(TypeUnitNodeEnum::SD_BL_IP == un->getType()
    || TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
        const auto& swpTarget = target->swpBLIPType0x41();
        if(!swpTarget.isNull()) {
            D1 = swpTarget.byteWord().at(1) & 0b00001111;
            uint8_t mask = 0x00;
            if(TypeUnitNodeEnum::SD_BL_IP == un->getType()
            && !un->swpSDBLIPType0x41().isNull())
                mask = un->swpSDBLIPType0x41().mask();
            else if(TypeUnitNodeEnum::IU_BL_IP == un->getType()
                 && !un->swpIUBLIPType0x41().isNull())
                mask = un->swpIUBLIPType0x41().mask();
            if(onOff)
                D1 = D1 | mask;
            else if(!onOff)
                D1 = D1 & ~mask;
        } else {
            for(const auto& un : as_const(reciver->getListChilde())) {
                if(type != un->getType())
                    continue;
                uint8_t mask = 0x00;
                if(TypeUnitNodeEnum::SD_BL_IP == un->getType()
                && !un->swpSDBLIPType0x41().isNull())
                    mask = un->swpSDBLIPType0x41().mask();
                else if(TypeUnitNodeEnum::IU_BL_IP == un->getType()
                     && !un->swpIUBLIPType0x41().isNull())
                    mask = un->swpIUBLIPType0x41().mask();

                if(TypeUnitNodeEnum::SD_BL_IP == un->getType()
                && !un->swpSDBLIPType0x41().isNull()
                && 1 == un->swpSDBLIPType0x41().isOff())
                    D1 = D1 & ~mask;
                else if(TypeUnitNodeEnum::IU_BL_IP == un->getType() &&
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

    } else if(TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
           || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()) {
        const auto& swpTarget = target->swpSSOIBLIPType0x41();
        if(!swpTarget.isNull()) {
            D1 = swpTarget.byteWord().at(1) & 0b00001111;
            uint8_t mask = 0x00;
            if(TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
            && !un->swpSSOISDBLIPType0x41().isNull())
                mask = un->swpSSOISDBLIPType0x41().mask();
            else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()
                 && !un->swpSSOIIUBLIPType0x41().isNull())
                mask = un->swpSSOIIUBLIPType0x41().mask();
            if(onOff)
                D1 = D1 | mask;
            else if(!onOff)
                D1 = D1 & ~mask;
        } else {
            for(const auto& un : as_const(reciver->getListChilde())) {
                if(type != un->getType())
                    continue;
                uint8_t mask = 0x00;
                if(TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
                && !un->swpSSOISDBLIPType0x41().isNull())
                    mask = un->swpSSOISDBLIPType0x41().mask();
                else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()
                     && !un->swpSSOIIUBLIPType0x41().isNull())
                    mask = un->swpSSOIIUBLIPType0x41().mask();

                if(TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
                && !un->swpSSOISDBLIPType0x41().isNull()
                && 1 == un->swpSSOISDBLIPType0x41().isOff())
                    D1 = D1 & ~mask;
                else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType() &&
                        !un->swpSSOIIUBLIPType0x41().isNull() &&
                        1 == un->swpSSOIIUBLIPType0x41().isOff())
                    D1 = D1 & ~mask;
                else
                    D1 = D1 | mask;

                if(un == target && onOff)
                    D1 = D1 | mask;
                else if(un == target && !onOff)
                    D1 = D1 & ~mask;
            }
        }

    }

    QByteArray data = DataQueueItem::data0x23;
    if(TypeUnitNodeEnum::BL_IP != un->getType()
    && TypeUnitNodeEnum::SD_BL_IP != un->getType()
    && TypeUnitNodeEnum::IU_BL_IP != un->getType()) {
        data[1] = static_cast<uint8_t>(un->getNum1());
    }
    data[4] = D1;
    data.chop(1);
    data.append(Utils::getByteSumm(data)); //<CHKS>

//    qDebug() << "DataQueueItem::makeOnOff0x23(" << un->toString() << ", " << onOff << ")" << data.toHex() << swpTarget.byteWord().toHex() << swpTarget.cdate();

//    qDebug() << "DataQueueItem::makeOnOff0x23(" << un->toString() << ")" << onOff << data.toHex();

    return data;
}

DataQueueItem DataQueueItem::fillOn0x23(DataQueueItem &item, const QSharedPointer<UnitNode> &un)
{
    item.setData(DataQueueItem::makeOn0x23(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOn0x23(const QSharedPointer<UnitNode> un)
{
return DataQueueItem::makeOnOff0x23(un, true);
}

DataQueueItem DataQueueItem::fillOff0x23(DataQueueItem &item, const QSharedPointer<UnitNode> &un)
{
    item.setData(DataQueueItem::makeOff0x23(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOff0x23(const QSharedPointer<UnitNode> un)
{
    return DataQueueItem::makeOnOff0x23(un, false);
}

QByteArray DataQueueItem::data0x24 = QByteArray();

DataQueueItem DataQueueItem::fillResetFlags0x24(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeResetFlags0x24(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeResetFlags0x24(const QSharedPointer<UnitNode> un)
{
    QByteArray data0x24;

    if(!un.isNull()) {
        if(TypeUnitNodeEnum::BL_IP == un->getType()
        || TypeUnitNodeEnum::SD_BL_IP == un->getType()
        || TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
            data0x24.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x24.append(static_cast<uint8_t>(0xFF));      //<ADDR>
            data0x24.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x24.append(static_cast<uint8_t>(0x24));
        } else if(TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()

               || TypeUnitNodeEnum::RLM_C == un->getType()

               || TypeUnitNodeEnum::RLM_KRL == un->getType()

               || TypeUnitNodeEnum::TG_Base == un->getType()
               || TypeUnitNodeEnum::TG == un->getType()) {
            data0x24.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x24.append(static_cast<uint8_t>(un->getNum1()));      //<ADDR>
            data0x24.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x24.append(static_cast<uint8_t>(0x24));
        } else if(   TypeUnitNodeEnum::BOD_T4K_M == un->getType()
                  || TypeUnitNodeEnum::Y4_T4K_M == un->getType()
                  || TypeUnitNodeEnum::DD_T4K_M == un->getType()

                  || TypeUnitNodeEnum::BOD_SOTA == un->getType()
                  || TypeUnitNodeEnum::Y4_SOTA == un->getType()
                  || TypeUnitNodeEnum::DD_SOTA == un->getType()) {
            data0x24.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x24.append(static_cast<uint8_t>(un->getNum1()));      //<ADDR>
            data0x24.append(static_cast<char>(0xFE));        //<ADDR> 0xFE
            data0x24.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x24.append(static_cast<uint8_t>(0x24));
           }
    } else {
        data0x24.append(static_cast<uint8_t>(0xB5));      //<SB>
        data0x24.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        data0x24.append(static_cast<char>(0x00));        //<NBB> 0x00
        data0x24.append(static_cast<uint8_t>(0x24));
    }
    data0x24.append(Utils::getByteSumm(data0x24)); //<CHKS>

    return data0x24;
}

QByteArray DataQueueItem::data0x25 = QByteArray();

DataQueueItem DataQueueItem::fillOff0x25(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeOff0x25(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOff0x25(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x25.isEmpty()) {
        DataQueueItem::data0x25.append(static_cast<uint8_t>(0xB5));      //<SB>
        DataQueueItem::data0x25.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        DataQueueItem::data0x25.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x25.append(static_cast<uint8_t>(0x25));      //<CMD> 0x25
//        DataQueueItem::data0x25.append(Utils::getByteSumm(DataQueueItem::data0x25)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x25;
    if(nullptr != un) {
        if(TypeUnitNodeEnum::BL_IP == un->getType() ||
           TypeUnitNodeEnum::SD_BL_IP == un->getType() ||
           TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
            out[1] = static_cast<uint8_t>(0xFF);
        } else if(TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()
               || TypeUnitNodeEnum::RLM_C == un->getType()
               || TypeUnitNodeEnum::RLM_KRL == un->getType()
               || TypeUnitNodeEnum::TG_Base == un->getType()
               || TypeUnitNodeEnum::TG == un->getType()) {
            out[1] = static_cast<uint8_t>(un->getNum1());
        }
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

//    qDebug() << "DataQueueItem::makeOff0x25(" << un->toString() << ")" << out.toHex();

    return out;
}

QByteArray DataQueueItem::data0x26 = QByteArray();

DataQueueItem DataQueueItem::fillOn0x26(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeOn0x26(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    return item;
}

QByteArray DataQueueItem::makeOn0x26(const QSharedPointer<UnitNode> un)
{
    if(DataQueueItem::data0x26.isEmpty()) {
        DataQueueItem::data0x26.append(static_cast<uint8_t>(0xB5));      //<SB>
        DataQueueItem::data0x26.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        DataQueueItem::data0x26.append(static_cast<char>(0x00));        //<NBB> 0x00
        DataQueueItem::data0x26.append(static_cast<uint8_t>(0x26));      //<CMD> 0x26
//        DataQueueItem::data0x26.append(Utils::getByteSumm(DataQueueItem::data0x26)); //<CHKS>
    }

    QByteArray out = DataQueueItem::data0x26;
    if(nullptr != un) {
        if(TypeUnitNodeEnum::BL_IP == un->getType() ||
           TypeUnitNodeEnum::SD_BL_IP == un->getType() ||
           TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
            out[1] = static_cast<uint8_t>(0xFF);
        } else if(TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()
               || TypeUnitNodeEnum::RLM_C == un->getType()
               || TypeUnitNodeEnum::RLM_KRL == un->getType()
               || TypeUnitNodeEnum::TG_Base == un->getType()
               || TypeUnitNodeEnum::TG == un->getType()) {
            out[1] = static_cast<uint8_t>(un->getNum1());
        }
    }
    out.append(Utils::getByteSumm(out)); //<CHKS>

    qDebug() << "DataQueueItem::makeOn0x26(" << un->toString() << ")" << out.toHex();

    return out;
}


DataQueueItem DataQueueItem::fillStatusRequest0x2A(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeStatusRequest0x2A(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    item.setSpecialSkipTimeInterval(300);
    item.setSpecialSkipTimeCount(2);
    return item;
}

QByteArray DataQueueItem::makeStatusRequest0x2A(const QSharedPointer<UnitNode> un)
{
    QByteArray data0x2A;
    if(un.isNull()) {
        data0x2A.append(static_cast<uint8_t>(0xB5));      //<SB>
        data0x2A.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        data0x2A.append(static_cast<char>(0x00));        //<NBB> 0x00
        data0x2A.append(static_cast<uint8_t>(0x2A));      //<CMD> 0x2A
    } else {
        if(TypeUnitNodeEnum::BL_IP == un->getType() ||
           TypeUnitNodeEnum::SD_BL_IP == un->getType() ||
           TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
            data0x2A.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x2A.append(static_cast<uint8_t>(0xFF));      //<ADDR>
            data0x2A.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x2A.append(static_cast<uint8_t>(0x2A));      //<CMD> 0x2A
        } else if(TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()

               || TypeUnitNodeEnum::RLM_C == un->getType()

               || TypeUnitNodeEnum::RLM_KRL == un->getType()

               || TypeUnitNodeEnum::TG_Base == un->getType()
               || TypeUnitNodeEnum::TG == un->getType()) {
            data0x2A.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x2A.append(static_cast<uint8_t>(un->getNum1()));      //<ADDR>
            data0x2A.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x2A.append(static_cast<uint8_t>(0x2A));      //<CMD> 0x2A
        } else if(TypeUnitNodeEnum::BOD_T4K_M == un->getType()
               || TypeUnitNodeEnum::Y4_T4K_M == un->getType()
               || TypeUnitNodeEnum::DD_T4K_M == un->getType()

               || TypeUnitNodeEnum::BOD_SOTA == un->getType()
               || TypeUnitNodeEnum::Y4_SOTA == un->getType()
               || TypeUnitNodeEnum::DD_SOTA == un->getType()) {
               data0x2A.append(static_cast<uint8_t>(0xB5));      //<SB>
               data0x2A.append(static_cast<uint8_t>(un->getNum1()));      //<ADDR>
               data0x2A.append(static_cast<char>(0x01));        //<NBB> 0x00
               data0x2A.append(static_cast<uint8_t>(0x2A));      //<CMD> 0x2A

               auto getY4 = [](QSharedPointer<UnitNode> un) {
                   auto num2 = un->getNum2();
                   return (num2 / 100);
               };

               auto getDDNum = [](QSharedPointer<UnitNode> un) {
                   auto num2 = un->getNum2();
                   return static_cast<uint8_t>(num2 % 100);
               };

               uint8_t d1 = 0x00;
               if(un->getInterrogationUN().isNull()) {
                   d1 = ((2 < getY4(un)) ? 0b10000000 : 0b00000000) | (0b01111111 & getDDNum(un));
               } else {
                   d1 = ((2 < getY4(un->getInterrogationUN())) ? 0b10000000 : 0b00000000) | (0b01111111 & getDDNum(un->getInterrogationUN()));
               }

               data0x2A.append(d1);      //<D1>
           }
    }

    data0x2A.append(Utils::getByteSumm(data0x2A)); //<CHKS>

    return data0x2A;
}


DataQueueItem DataQueueItem::fillStatusRequest0x2C(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeStatusRequest0x2C(un));
    if(nullptr != un && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    item.setSpecialSkipTimeInterval(800);
    item.setSpecialSkipTimeCount(2);
    return item;
}

QByteArray DataQueueItem::makeStatusRequest0x2C(const QSharedPointer<UnitNode> un)
{
    QByteArray data0x2C;
    if(un.isNull()) {
        data0x2C.append(static_cast<uint8_t>(0xB5));      //<SB>
        data0x2C.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        data0x2C.append(static_cast<char>(0x00));        //<NBB> 0x00
        data0x2C.append(static_cast<uint8_t>(0x2C));      //<CMD> 0x2C
    } else {
        if(TypeUnitNodeEnum::BL_IP == un->getType() ||
           TypeUnitNodeEnum::SD_BL_IP == un->getType() ||
           TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
            data0x2C.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x2C.append(static_cast<uint8_t>(0xFF));      //<ADDR>
            data0x2C.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x2C.append(static_cast<uint8_t>(0x2C));      //<CMD> 0x2C
        } else if(TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()

               || TypeUnitNodeEnum::RLM_C == un->getType()

               || TypeUnitNodeEnum::RLM_KRL == un->getType()

               || TypeUnitNodeEnum::TG_Base == un->getType()
               || TypeUnitNodeEnum::TG == un->getType()) {
            data0x2C.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x2C.append(static_cast<uint8_t>(un->getNum1()));      //<ADDR>
            data0x2C.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x2C.append(static_cast<uint8_t>(0x2C));      //<CMD> 0x2C
        } else if(TypeUnitNodeEnum::BOD_T4K_M == un->getType()
               || TypeUnitNodeEnum::Y4_T4K_M == un->getType()
               || TypeUnitNodeEnum::DD_T4K_M == un->getType()

               || TypeUnitNodeEnum::BOD_SOTA == un->getType()
               || TypeUnitNodeEnum::Y4_SOTA == un->getType()
               || TypeUnitNodeEnum::DD_SOTA == un->getType()) {
               data0x2C.append(static_cast<uint8_t>(0xB5));      //<SB>
               data0x2C.append(static_cast<uint8_t>(un->getNum1()));      //<ADDR>
               data0x2C.append(static_cast<uint8_t>(0xFE));      //<ADDR>
               data0x2C.append(static_cast<char>(0x01));        //<NBB> 0x00
               data0x2C.append(static_cast<uint8_t>(0x2C));      //<CMD> 0x2C

               auto getY4 = [](QSharedPointer<UnitNode> un) {
                   auto num2 = un->getNum2();
                   return (num2 / 100);
               };

               auto getDDNum = [](QSharedPointer<UnitNode> un) {
                   auto num2 = un->getNum2();
                   return static_cast<uint8_t>(num2 % 100);
               };

               uint8_t d1 = 0x00;
               if(un->getInterrogationUN().isNull()) {
                   d1 = ((2 < getY4(un)) ? 0b10000000 : 0b00000000) | (0b01111111 & getDDNum(un));
               } else {
                   d1 = ((2 < getY4(un->getInterrogationUN())) ? 0b10000000 : 0b00000000) | (0b01111111 & getDDNum(un->getInterrogationUN()));
               }

               data0x2C.append(d1);      //<D1>
           }
    }

    data0x2C.append(Utils::getByteSumm(data0x2C)); //<CHKS>

    return data0x2C;
}


DataQueueItem DataQueueItem::fillStatusRequest0x2D(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeStatusRequest0x2D(un));
    if(!un.isNull()
    && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    item.setSpecialSkipTimeInterval(300);
    item.setSpecialSkipTimeCount(2);
    return item;
}

QByteArray DataQueueItem::makeStatusRequest0x2D(const QSharedPointer<UnitNode> un)
{
    QByteArray data0x2D;
    if(un.isNull()) {
        data0x2D.append(static_cast<uint8_t>(0xB5));      //<SB>
        data0x2D.append(static_cast<uint8_t>(0xFF));      //<ADDR>
        data0x2D.append(static_cast<char>(0x00));        //<NBB> 0x00
        data0x2D.append(static_cast<uint8_t>(0x2D));      //<CMD> 0x2D
    } else {
        if(TypeUnitNodeEnum::BL_IP == un->getType() ||
           TypeUnitNodeEnum::SD_BL_IP == un->getType() ||
           TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
            data0x2D.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x2D.append(static_cast<uint8_t>(0xFF));      //<ADDR>
            data0x2D.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x2D.append(static_cast<uint8_t>(0x2D));      //<CMD> 0x2D
        } else if(TypeUnitNodeEnum::SSOI_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()
               || TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()

               || TypeUnitNodeEnum::RLM_C == un->getType()

               || TypeUnitNodeEnum::RLM_KRL == un->getType()

               || TypeUnitNodeEnum::TG_Base == un->getType()
               || TypeUnitNodeEnum::TG == un->getType()) {
            data0x2D.append(static_cast<uint8_t>(0xB5));      //<SB>
            data0x2D.append(static_cast<uint8_t>(un->getNum1()));      //<ADDR>
            data0x2D.append(static_cast<char>(0x00));        //<NBB> 0x00
            data0x2D.append(static_cast<uint8_t>(0x2D));      //<CMD> 0x2D
        } else if(TypeUnitNodeEnum::BOD_T4K_M == un->getType()
               || TypeUnitNodeEnum::Y4_T4K_M == un->getType()
               || TypeUnitNodeEnum::DD_T4K_M == un->getType()

               || TypeUnitNodeEnum::BOD_SOTA == un->getType()
               || TypeUnitNodeEnum::Y4_SOTA == un->getType()
               || TypeUnitNodeEnum::DD_SOTA == un->getType()) {
               data0x2D.append(static_cast<uint8_t>(0xB5));      //<SB>
               data0x2D.append(static_cast<uint8_t>(un->getNum1()));      //<ADDR>
               data0x2D.append(static_cast<uint8_t>(0xFE));      //<ADDR>
               data0x2D.append(static_cast<char>(0x01));        //<NBB> 0x00
               data0x2D.append(static_cast<uint8_t>(0x2D));      //<CMD> 0x2D

               auto getY4 = [](QSharedPointer<UnitNode> un) {
                   auto num2 = un->getNum2();
                   return (num2 / 100);
               };

               auto getDDNum = [](QSharedPointer<UnitNode> un) {
                   auto num2 = un->getNum2();
                   return static_cast<uint8_t>(num2 % 100);
               };

               uint8_t d1 = 0x00;
               if(un->getInterrogationUN().isNull()) {
                   d1 = ((2 < getY4(un)) ? 0b10000000 : 0b00000000) | (0b01111111 & getDDNum(un));
               } else {
                   d1 = ((2 < getY4(un->getInterrogationUN())) ? 0b10000000 : 0b00000000) | (0b01111111 & getDDNum(un->getInterrogationUN()));
               }

               data0x2D.append(d1);      //<D1>
           }
    }

    data0x2D.append(Utils::getByteSumm(data0x2D)); //<CHKS>

    return data0x2D;
}


QByteArray DataQueueItem::data0x2E = QByteArray();

DataQueueItem DataQueueItem::fillStatusRequest0x2E(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeStatusRequest0x2E(un));
    if(!un.isNull()
    && un->isNeedsPreamble())
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    item.setSpecialSkipTimeInterval(300);
    item.setSpecialSkipTimeCount(2);
    return item;
}

QByteArray DataQueueItem::makeStatusRequest0x2E(const QSharedPointer<UnitNode> un)
{
    auto rcvr = TopologyService::findReciver(un);
    while(rcvr != TopologyService::findReciver(rcvr)) {
        rcvr = TopologyService::findReciver(rcvr);
    }

    QByteArray data;
    data.append(static_cast<uint8_t>(0xB5));      //<SB>
    data.append(static_cast<uint8_t>(0xFF));      //<ADDR>
    if(TypeUnitNodeEnum::BOD_T4K_M == rcvr->getType()) {
        data.append(static_cast<char>(0xFE));        //<ADDR> 0xFE
    } else if(TypeUnitNodeEnum::BOD_SOTA == rcvr->getType()) {
        data.append(static_cast<uint8_t>(0xFE));        //<ADDR> 0xFE
    }
    data.append(static_cast<char>(0x00));        //<NBB> 0x00
    data.append(static_cast<uint8_t>(0x2E));      //<CMD> 0x2E

    if(!un.isNull()) {
        data[1] = static_cast<uint8_t>(un->getNum1());
    }
    data.append(Utils::getByteSumm(data)); //<CHKS>

    return data;
}

DataQueueItem DataQueueItem::fillSpecifyingSettingsBOD0x20(DataQueueItem &item, const QSharedPointer<UnitNode> un)
{
    item.setData(DataQueueItem::makeSpecifyingSettingsBOD0x20(un));
    if(!un.isNull()
    && un->isNeedsPreamble()) {
        item.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));
    }
    item.setSpecialSkipTimeInterval(400);
    item.setSpecialSkipTimeCount(2);
    return item;
}

QByteArray DataQueueItem::makeSpecifyingSettingsBOD0x20(const QSharedPointer<UnitNode> un)
{

    auto bod = TopologyService::findReciver(un);
    while(bod != TopologyService::findReciver(bod)) {
        bod = TopologyService::findReciver(bod);
    }

    QByteArray data;
    data.append(static_cast<uint8_t>(0xB5));      //<SB>
    data.append(static_cast<uint8_t>(bod->getNum1()));      //<ADDR bod>
    data.append(static_cast<uint8_t>(0xFE));      //<ADDR>

    if(TypeUnitNodeEnum::BOD_T4K_M == bod->getType()) {
        data.append(static_cast<uint8_t>(0x0B)); // 11 //<NBB> 0x00
    } else if(TypeUnitNodeEnum::BOD_SOTA == bod->getType()) {
        data.append(static_cast<uint8_t>(0x1D)); // 29 //<NBB> 0x00
    }

    data.append(static_cast<uint8_t>(0x20));      //<CMD> 0x20

    if(TypeUnitNodeEnum::BOD_T4K_M == bod->getType()) {
        data.append(static_cast<char>(0x00));        //<NBB> 0x00
    } else if(TypeUnitNodeEnum::BOD_SOTA == bod->getType()) {
        data.append(static_cast<uint8_t>(0x01));        //<NBB> 0x00
    }

    if(TypeUnitNodeEnum::BOD_T4K_M == bod->getType()) {
        data.append(8, static_cast<char>(0x00)); // 11 - 3 //<NBB> 0x00
    } else if(TypeUnitNodeEnum::BOD_SOTA == bod->getType()) {
        data.append(26, static_cast<char>(0x00)); // 29 - 3 //<NBB> 0x00
    }

//    uint8_t maxDD = 0x00;
//    if(TypeUnitNodeEnum::BOD_T4K_M == bod->getType()) {
//        maxDD = 0x1A; // 26
//    } else if(TypeUnitNodeEnum::BOD_SOTA == bod->getType()) {
//        maxDD = 0x64; // 100
//    }

    auto makeByteMask = [](QSharedPointer<UnitNode> un) {
        auto num2 = un->getNum2();
        switch ((num2 % 100) % 8) {
        case 0:
            return static_cast<uint8_t>(0x80);
        case 1:
            return static_cast<uint8_t>(0x01);
        case 2:
            return static_cast<uint8_t>(0x02);
        case 3:
            return static_cast<uint8_t>(0x04);
        case 4:
            return static_cast<uint8_t>(0x08);
        case 5:
            return static_cast<uint8_t>(0x10);
        case 6:
            return static_cast<uint8_t>(0x20);
        case 7:
            return static_cast<uint8_t>(0x40);
        case 8:
            return static_cast<uint8_t>(0x80);
        default:
            return static_cast<uint8_t>(0x00);
        }
    };

    auto makeIndex = [](QSharedPointer<UnitNode> un) {
        auto num2 = un->getNum2();
        return ((num2 % 100) / 8);
    };

    auto makeDisplacementCoefficient = [](QSharedPointer<UnitNode> un) {
        auto num2 = un->getNum2();
        return (2 < (num2 / 100) ? 1 : 0);
    };

    auto makeDisplacement = [](QSharedPointer<UnitNode> un) {
        if(TypeUnitNodeEnum::DD_T4K_M == un->getType()) {
            return 4;
        } else if(TypeUnitNodeEnum::DD_SOTA == un->getType()) {
            return 13;
        }
        return 0;
    };

    auto getY4 = [](QSharedPointer<UnitNode> un) {
        auto num2 = un->getNum2();
        return (num2 / 100);
    };

    auto getDDNum = [](QSharedPointer<UnitNode> un) {
        auto num2 = un->getNum2();
        return static_cast<uint8_t>(num2 % 100);
    };

    uint8_t ddNumY4_2 = static_cast<uint8_t>(0x00);
    uint8_t ddNumY4_4 = static_cast<uint8_t>(0x00);

    int targetTypeDD = 0;
    if(TypeUnitNodeEnum::BOD_T4K_M == bod->getType()) {
        targetTypeDD = TypeUnitNodeEnum::DD_T4K_M;
    } else if(TypeUnitNodeEnum::BOD_SOTA == bod->getType()) {
        targetTypeDD = TypeUnitNodeEnum::DD_SOTA;
    }

    for(const auto& un : as_const(TopologyService::findChildByType(targetTypeDD, bod))) {
        const auto index = makeIndex(un) + (makeDisplacement(un) * makeDisplacementCoefficient(un)) + 6;
        data[index] = static_cast<uint8_t>(data.at(index)) | makeByteMask(un);
        if(2 == getY4(un)) {
            ddNumY4_2 = (0 == ddNumY4_2) ? getDDNum(un) : std::min(ddNumY4_2, getDDNum(un));
        }
        if(4 == getY4(un)) {
            ddNumY4_4 = (0 == ddNumY4_4) ? getDDNum(un) : std::min(ddNumY4_4, getDDNum(un));
        }
    }

    data.append(ddNumY4_2);
    data.append(ddNumY4_4);

    data.append(Utils::getByteSumm(data)); //<CHKS>

    return data;
}

bool DataQueueItem::isValideDirectionI(const DataQueueItem &item)
{
    if(item.data().isEmpty()
    || item.address().isNull()
    || 0 > item.port()
    || -1 > item.portIndex())
        return false;
    auto itemData = item.data();
    while(0 == itemData.indexOf(static_cast<uint8_t>(0xFF))) {
        itemData.remove(0, 1);
    }
    try {
        if(6 > itemData.size())
            return false;
        uint8_t SB = itemData.at(0),
                ADDR_r = itemData.at(1),
//                ADDR_s = itemData.at(2),
                NBB = itemData.at(3),
                CMD = itemData.at(4);
        if((6 + NBB) > itemData.size())
            return false;
        uint8_t CHKS = itemData.at(5 + NBB);

        if(static_cast<uint8_t>(0xB5) != SB ||
                static_cast<uint8_t>(0xFE) != ADDR_r /*||
                static_cast<uint8_t>(0xFF != ADDR_s*/)
            return false;

        QByteArray tmpData = itemData;
        uint8_t crc = Utils::getByteSumm(tmpData, 1, 5 + NBB - 1);
        if(crc != CHKS)
            return false;

        switch (CMD) {
        case static_cast<uint8_t>(0x30): {
            if(static_cast<uint8_t>(0x00) != NBB)
                return false;
            return true;
        }
        case static_cast<uint8_t>(0x31): {
            if(static_cast<uint8_t>(0x04) != NBB
            && static_cast<uint8_t>(0x03) != NBB)
                return false;
            return true;
        }
        case static_cast<uint8_t>(0x32): {
            if(static_cast<uint8_t>(0x0D) != NBB
            && static_cast<uint8_t>(0x36) != NBB
            && static_cast<uint8_t>(0x66) != NBB)
                return false;
            return true;
        }
        case static_cast<uint8_t>(0x33): {
            if(static_cast<uint8_t>(0x03) != NBB
            && static_cast<uint8_t>(0x09) != NBB)
                return false;
            return true;
        }
        case static_cast<uint8_t>(0x34): {
            if(static_cast<uint8_t>(0x1C) != NBB)
                return false;
            return true;
        }
        case static_cast<uint8_t>(0x41): {
            if(static_cast<uint8_t>(0x04) != NBB)
                return false;
            return true;
        }
        case static_cast<uint8_t>(0x42): {
            if(static_cast<uint8_t>(0x02) != NBB)
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

