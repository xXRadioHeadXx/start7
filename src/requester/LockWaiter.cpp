#include "LockWaiter.h"
#include "SignalSlotCommutator.h"

#include "PortManager.h"
#include "UnitNodeFactory.h"
#include "ServerSettingUtils.h"
#include "Utils.h"
#include "global.h"
#include "SWPSDBLIP.h"
#include "SWPIUBLIP.h"

LockWaiter::LockWaiter(QSharedPointer<UnitNode>  target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
    //qDebug() << "LockWaiter::LockWaiter(" << this << ") -->";
}

LockWaiter::~LockWaiter()
{
    //qDebug() << "LockWaiter::~LockWaiter(" << this << ") <--";
}

QSharedPointer<UnitNode> LockWaiter::getUnReciverIuBlIp() const
{
    return unReciverIuBlIp;
}

void LockWaiter::setUnReciverIuBlIp(QSharedPointer<UnitNode> value)
{
    unReciverIuBlIp = value;
}

QSharedPointer<UnitNode> LockWaiter::getUnReciverSdBlIp() const
{
    return unReciverSdBlIp;
}

void LockWaiter::setUnReciverSdBlIp(QSharedPointer<UnitNode> value)
{
    unReciverSdBlIp = value;
}

int LockWaiter::getInitVarianrt() const
{
    return initVarianrt;
}

void LockWaiter::setInitVarianrt(int value)
{
    initVarianrt = value;
}

DataQueueItem LockWaiter::getOnMsg()
{
    DataQueueItem msgOn;
    msgOn.setData(DataQueueItem::makeOnOff0x23(getUnReciverIuBlIp(), true, getUnReciver()));
    msgOn.setPort(getUnReciver()->getUdpPort());
    msgOn.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    msgOn.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(nullptr != getUnReciverIuBlIp() && TypeUnitNode::RLM_C == getUnReciverIuBlIp()->getType())
        msgOn.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));

    return msgOn;
}

DataQueueItem LockWaiter::getOffMsg()
{
    DataQueueItem msgOff;
    msgOff.setData(DataQueueItem::makeOnOff0x23(getUnReciverIuBlIp(), false, getUnReciver()));
    msgOff.setPort(getUnReciver()->getUdpPort());
    msgOff.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    msgOff.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(nullptr != getUnReciverIuBlIp() && TypeUnitNode::RLM_C == getUnReciverIuBlIp()->getType())
        msgOff.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));

    return msgOff;
}

DataQueueItem LockWaiter::makeFirstMsg() {
    if(1 == getInitVarianrt())
        return getOnMsg();
    else if(2 == getInitVarianrt())
        return getOffMsg();
    else if(3 == getInitVarianrt())
        return getOffMsg();
    else if(4 == getInitVarianrt())
        return getOnMsg();
    return DataQueueItem();
}

DataQueueItem LockWaiter::makeSecondMsg() {
    if(1 == getInitVarianrt())
        return DataQueueItem();
    else if(2 == getInitVarianrt())
        return DataQueueItem();
    else if(3 == getInitVarianrt())
        return getOnMsg();
    else if(4 == getInitVarianrt())
        return getOffMsg();
    return DataQueueItem();
}

DataQueueItem LockWaiter::makeEndMsg() {
    return DataQueueItem();
}

void LockWaiter::init() {

    if(getUnTarget().isNull())
        return;

    setUnReciverSdBlIp(getUnTarget());

    setUnReciver(UnitNode::findReciver(getUnTarget()));

    for(QSharedPointer<UnitNode>  un : as_const(ServerSettingUtils::getSetMetaRealUnitNodes().values())) {
        if(TypeUnitNode::IU_BL_IP == un->getType() && getUnReciverSdBlIp()->getNum2() == un->getNum2() && getUnReciverSdBlIp()->getUdpPort() == un->getUdpPort() && getUnReciverSdBlIp()->getUdpAdress() == un->getUdpAdress()) {
            setUnReciverIuBlIp(un);
            break;
        }
    }

    if(nullptr == getUnReciverIuBlIp() && !getUnReciver().isNull()) {
        auto newMetaUnIuBlIp = UnitNodeFactory::makeShare(TypeUnitNode::IU_BL_IP, getUnReciver());
        newMetaUnIuBlIp->setNum2(getUnReciverSdBlIp()->getNum2());
        newMetaUnIuBlIp->setUdpPort(getUnReciverSdBlIp()->getUdpPort());
        newMetaUnIuBlIp->setUdpAdress(getUnReciverSdBlIp()->getUdpAdress());
        newMetaUnIuBlIp->setUdpTimeout(getUnReciverSdBlIp()->getUdpTimeout());
        newMetaUnIuBlIp->setNum1(getUnReciverSdBlIp()->getNum1());
        newMetaUnIuBlIp->setStateWord(getUnReciverSdBlIp()->getStateWord());

        newMetaUnIuBlIp->setName("MetaIU_" + QString::number(newMetaUnIuBlIp->getNum2()));
        newMetaUnIuBlIp->setMetaEntity(1);

        ServerSettingUtils::getSetMetaRealUnitNodes().insert(newMetaUnIuBlIp);
        getUnReciver()->addChild(newMetaUnIuBlIp);

        setUnReciverIuBlIp(newMetaUnIuBlIp);
        ServerSettingUtils::linkDoubles(newMetaUnIuBlIp);
    }


    if(getUnReciverSdBlIp() == getUnReciver() || getUnReciver().isNull() || getUnReciverIuBlIp().isNull())
        return;

    setIpPort(QPair<QString, QString>(getUnReciver()->getUdpAdress(), QVariant(getUnReciver()->getUdpPort()).toString()));

    for(AbstractPort * pt : as_const(PortManager::getUdpPortsVector())) {
        if(Port::typeDefPort(pt)->getStIpPort().contains(getIpPort())) {
            setPtrPort(pt);
            setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
            break;
        }
    }

    //
    if(!getUnTarget().isNull()) {
        setUnReciver(UnitNode::findReciver(getUnTarget()));
    }

    if(getUnTarget().isNull() || getUnReciver().isNull())
        return;

    setIpPort(QPair<QString, QString>(getUnReciver()->getUdpAdress(), QVariant(getUnReciver()->getUdpPort()).toString()));

    for(AbstractPort * pt : as_const(PortManager::getUdpPortsVector())) {
        if(Port::typeDefPort(pt)->getStIpPort().contains(getIpPort())) {
            setPtrPort(pt);
            setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
            break;
        }
    }


    if(1 == getUnReciverSdBlIp()->swpSDBLIP().isAlarm() &&
       1 == getUnReciverIuBlIp()->swpIUBLIP().isOff()) {
//        qDebug() << "LockRequester::init 1";
        //Открыто
        setInitVarianrt(1);
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(0);
        setTimeIntervalRequest(500);
    } else if(1 == getUnReciverSdBlIp()->swpSDBLIP().isNorm() &&
              1 == getUnReciverIuBlIp()->swpIUBLIP().isOn()) {
//        qDebug() << "LockRequester::init 2";
        //Закрыто
        setInitVarianrt(2);
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(0);
        setTimeIntervalRequest(500);
    } else if(1 == getUnReciverSdBlIp()->swpSDBLIP().isAlarm() &&
              1 == getUnReciverIuBlIp()->swpIUBLIP().isOn()) {
//        qDebug() << "LockRequester::init 3";
        //Открыто ключом
        setInitVarianrt(3);
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(30000);
        setTimeIntervalRequest(500);
    } else if(1 == getUnReciverSdBlIp()->swpSDBLIP().isNorm() &&
              1 == getUnReciverIuBlIp()->swpIUBLIP().isOff()) {
//        qDebug() << "LockRequester::init 4";
        //Закрыто ключом
        setInitVarianrt(4);
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(30000);
        setTimeIntervalRequest(500);
    }

    setMaxBeatCount(5);

    connect(this, SIGNAL(importantBeatStatus()), SignalSlotCommutator::getInstance(), SLOT(emitEndLockWait()));
}
