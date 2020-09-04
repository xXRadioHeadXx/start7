#include "LockWaiter.h"
#include "SignalSlotCommutator.h"

#include <PortManager.h>
#include <Utils.h>

LockWaiter::LockWaiter(UnitNode * target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
    qDebug() << "LockWaiter::LockWaiter";
}

LockWaiter::~LockWaiter()
{
    qDebug() << "LockWaiter::~LockWaiter()";
}

DataQueueItem LockWaiter::getOnMsg()
{
    DataQueueItem msgOn;
    msgOn.setData(DataQueueItem::makeOnOff0x23(unReciverIuBlIp, true, getUnReciver()));
    msgOn.setPort(getUnReciver()->getUdpPort());
    msgOn.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    msgOn.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
    return msgOn;
}

DataQueueItem LockWaiter::getOffMsg()
{
    DataQueueItem msgOff;
    msgOff.setData(DataQueueItem::makeOnOff0x23(unReciverIuBlIp, false, getUnReciver()));
    msgOff.setPort(getUnReciver()->getUdpPort());
    msgOff.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    msgOff.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
    return msgOff;
}

DataQueueItem LockWaiter::makeFirstMsg() {
    if(1 == initVarianrt)
        return getOnMsg();
    else if(2 == initVarianrt)
        return getOffMsg();
    else if(3 == initVarianrt)
        return getOffMsg();
    else if(4 == initVarianrt)
        return getOnMsg();
    return DataQueueItem();
}

DataQueueItem LockWaiter::makeSecondMsg() {
    if(1 == initVarianrt)
        return DataQueueItem();
    else if(2 == initVarianrt)
        return DataQueueItem();
    else if(3 == initVarianrt)
        return getOnMsg();
    else if(4 == initVarianrt)
        return getOffMsg();
    return DataQueueItem();
}

DataQueueItem LockWaiter::makeEndMsg() {
    return DataQueueItem();
}

void LockWaiter::init() {

    if(nullptr == getUnTarget())
        return;

    unReciverSdBlIp = getUnTarget();

    UnitNode * reciver = getUnTarget();
    while(nullptr != reciver) {
        if(TypeUnitNode::BL_IP == reciver->getType()) {
            break;
        }
        reciver = reciver->getParentUN();
    }
    setUnReciver(reciver);

    unReciverIuBlIp = nullptr;
    for(UnitNode * un : reciver->getListChilde()) {
        if(TypeUnitNode::IU_BL_IP == un->getType() && unReciverSdBlIp->getNum2() == un->getNum2()) {
            unReciverIuBlIp = un;
            break;
        }
    }

    if(unReciverSdBlIp == reciver || nullptr == reciver || nullptr == unReciverIuBlIp)
        return;

    setIpPort(QPair<QString, QString>(getUnReciver()->getUdpAdress(), QVariant(getUnReciver()->getUdpPort()).toString()));

    for(AbstractPort * pt : PortManager::getUdpPortsVector()) {
        if(Port::typeDefPort(pt)->getStIpPort().contains(getIpPort())) {
            setPtrPort(pt);
            setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
            break;
        }
    }

    //
    if(nullptr != getUnTarget()) {
        UnitNode * un = getUnTarget();
        while(nullptr != un) {
            if(TypeUnitNode::BL_IP == un->getType() /* или датчик */) {
                setUnReciver(un);
                break;
            }
            un = un->getParentUN();
        }
    }

    if(nullptr == getUnTarget() || nullptr == getUnReciver())
        return;

    setIpPort(QPair<QString, QString>(getUnReciver()->getUdpAdress(), QVariant(getUnReciver()->getUdpPort()).toString()));

    for(AbstractPort * pt : PortManager::getUdpPortsVector()) {
        if(Port::typeDefPort(pt)->getStIpPort().contains(getIpPort())) {
            setPtrPort(pt);
            setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
            break;
        }
    }


    if(Status::Alarm == unReciverSdBlIp->getStatus1() &&
       Status::Off == unReciverIuBlIp->getStatus1()) {
//        qDebug() << "LockRequester::init 1";
        //Открыто
        initVarianrt = 1;
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(0);
        setTimeIntervalRequest(500);
    } else if(Status::Norm == unReciverSdBlIp->getStatus1() &&
              Status::On == unReciverIuBlIp->getStatus1()) {
//        qDebug() << "LockRequester::init 2";
        //Закрыто
        initVarianrt = 2;
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(0);
        setTimeIntervalRequest(500);
    } else if(Status::Alarm == unReciverSdBlIp->getStatus1() &&
              Status::On == unReciverIuBlIp->getStatus1()) {
//        qDebug() << "LockRequester::init 3";
        //Открыто ключём
        initVarianrt = 3;
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(30000);
        setTimeIntervalRequest(500);
    } else if(Status::Norm == unReciverSdBlIp->getStatus1() &&
              Status::Off == unReciverIuBlIp->getStatus1()) {
//        qDebug() << "LockRequester::init 4";
        //Закрыто ключём
        initVarianrt = 4;
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(30000);
        setTimeIntervalRequest(500);
    }

    setMaxBeatCount(5);

    connect(this, SIGNAL(unsuccessful()), SignalSlotCommutator::getInstance(), SLOT(emitEndLockWait()));
}
