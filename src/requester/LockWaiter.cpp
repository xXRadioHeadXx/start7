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

DataQueueItem LockWaiter::makeFirstMsg() {
    qDebug() << "LockWaiter::makeFirstMsg()";
    return getFirstMsg();
}

DataQueueItem LockWaiter::makeSecondMsg() {
    qDebug() << "LockWaiter::makeSecondMsg()";
    return getSecondMsg();
}

DataQueueItem LockWaiter::makeEndMsg() {
    qDebug() << "LockWaiter::makeEndMsg()";
    return getEndMsg();
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

    setTimeIntervalWaiteFirst(30000);
    setTimeIntervalWaiteSecond(30000);
    setTimeIntervalRequest(500);

    DataQueueItem msgOn;
    msgOn.setData(DataQueueItem::makeOnOff0x23(unReciverIuBlIp, true, getUnReciver()));
    msgOn.setPort(getUnReciver()->getUdpPort());
    msgOn.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    msgOn.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    DataQueueItem msgOff;
    msgOff.setData(DataQueueItem::makeOnOff0x23(unReciverIuBlIp, false, getUnReciver()));
    msgOff.setPort(getUnReciver()->getUdpPort());
    msgOff.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    msgOff.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    setFirstMsg(DataQueueItem());
    setSecondMsg(DataQueueItem());
    setEndMsg(DataQueueItem());

    if(Status::Alarm == unReciverSdBlIp->getStatus1() &&
       Status::Off == unReciverIuBlIp->getStatus1()) {
        //Открыто
        setFirstMsg(msgOn);
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(0);
        setTimeIntervalRequest(500);
    } else if(Status::Norm == unReciverSdBlIp->getStatus1() &&
              Status::On == unReciverIuBlIp->getStatus1()) {
        //Закрыто
        setFirstMsg(msgOff);
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(0);
        setTimeIntervalRequest(500);
    } else if(Status::Alarm == unReciverSdBlIp->getStatus1() &&
              Status::On == unReciverIuBlIp->getStatus1()) {
        //Открыто ключём
        setFirstMsg(msgOff);
        setSecondMsg(msgOn);
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(30000);
        setTimeIntervalRequest(500);
    } else if(Status::Norm == unReciverSdBlIp->getStatus1() &&
              Status::Off == unReciverIuBlIp->getStatus1()) {
        //Закрыто ключём
        setFirstMsg(msgOn);
        setSecondMsg(msgOff);
        setTimeIntervalWaiteFirst(30000);
        setTimeIntervalWaiteSecond(30000);
        setTimeIntervalRequest(500);
    }

    connect(this, SIGNAL(unsuccessful()), SignalSlotCommutator::getInstance(), SLOT(emitEndLockWait()));
}
