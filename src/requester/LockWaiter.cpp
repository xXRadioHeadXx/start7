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
//    qDebug() << "LockWaiter::~LockWaiter()";
    Port::typeDefPort(getPtrPort())->setProcDK(false);
}

DataQueueItem LockWaiter::makeFirstMsg() {
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == getUnReciver())
        return result;

    result.setData(DataQueueItem::makeDK0x21(getUnReciver()));
    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(result.isValid())
        return result;

    return DataQueueItem();
}

DataQueueItem LockWaiter::makeSecondMsg() {
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == getUnReciver())
        return result;

    result.setData(DataQueueItem::makeAlarmReset0x24(getUnReciver()));
    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(result.isValid())
        return result;

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

    for(UnitNode * uncld : getUnReciver()->getListChilde()) {
        if(0 != uncld->getDK() && (TypeUnitNode::SD_BL_IP == uncld->getType() /* или датчик */)) {
            uncld->setDkInvolved(true);
            uncld->setDkStatus(DKCiclStatus::DKReady);
            uncld->updDoubl();
//            this->lsTrackedUN.append(uncld);
        }
    }

    setTimeIntervalWaite(30000);
    setTimeIntervalRequest(500);

    connect(this, SIGNAL(unsuccessful()), SignalSlotCommutator::getInstance(), SLOT(emitEndLockerWait()));
}
