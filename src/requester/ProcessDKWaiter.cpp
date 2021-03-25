#include "ProcessDKWaiter.h"
#include "SignalSlotCommutator.h"

#include <PortManager.h>
#include <Utils.h>
#include <global.h>

ProcessDKWaiter::ProcessDKWaiter(UnitNode * target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
    //qDebug() << "ProcessDKWaiter::ProcessDKWaiter(" << this << ") -->";
}

ProcessDKWaiter::~ProcessDKWaiter()
{
    //qDebug() << "ProcessDKWaiter::~ProcessDKWaiter(" << this << ") <--";
    Port::typeDefPort(getPtrPort())->setProcDK(false);
    if(TypeUnitNode::BL_IP == getUnReciver()->getType()) {
        getUnReciver()->setDkInvolved(false);
    }
}

QList<UnitNode *> ProcessDKWaiter::getLsTrackedUN() const
{
    return lsTrackedUN;
}

void ProcessDKWaiter::setLsTrackedUN(const QList<UnitNode *> &value)
{
    lsTrackedUN = value;
}

void ProcessDKWaiter::addLsTrackedUN(UnitNode *  value)
{
    lsTrackedUN.append(value);
}

DataQueueItem ProcessDKWaiter::makeFirstMsg() {
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == getUnReciver())
        return result;

    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    DataQueueItem::makeDK0x21(result, getUnReciver());

    if(result.isValid())
        return result;

    return DataQueueItem();
}

DataQueueItem ProcessDKWaiter::makeSecondMsg() {
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == getUnReciver())
        return result;

    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    DataQueueItem::makeAlarmReset0x24(result, getUnReciver());

    if(result.isValid())
        return result;

    return DataQueueItem();
}

DataQueueItem ProcessDKWaiter::makeEndMsg()
{
    return DataQueueItem();
}

void ProcessDKWaiter::init() {
    if(nullptr != getUnTarget()) {
        UnitNode * un = getUnTarget();
        while(nullptr != un) {
            if(TypeUnitNode::BL_IP == un->getType() ||
               TypeUnitNode::RLM_C == un->getType() ||
               TypeUnitNode::RLM_KRL == un->getType() ||
               TypeUnitNode::TG == un->getType()
                    /* или датчик */) {
                setUnReciver(un);
                break;
            }
            un = un->getParentUN();
        }
    }

    if(nullptr == getUnTarget() || nullptr == getUnReciver())
        return;

    setIpPort(QPair<QString, QString>(getUnReciver()->getUdpAdress(), QVariant(getUnReciver()->getUdpPort()).toString()));

    for(AbstractPort * pt : as_const(PortManager::getUdpPortsVector())) {
        if(Port::typeDefPort(pt)->getStIpPort().contains(getIpPort())) {
            setPtrPort(pt);
            setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
            break;
        }
    }

    if(TypeUnitNode::BL_IP == getUnReciver()->getType()) {
        for(UnitNode * uncld : as_const(getUnReciver()->getListChilde())) {
            if(0 != uncld->getDK() && (TypeUnitNode::SD_BL_IP == uncld->getType() /* или датчик */)) {
                uncld->setDkInvolved(true);
                uncld->setDkStatus(DKCiclStatus::DKReady);
                uncld->updDoubl();
                this->lsTrackedUN.append(uncld);
            }
        }
        getUnReciver()->setDkInvolved(true);
    } else if(TypeUnitNode::RLM_C == getUnReciver()->getType() ||
              TypeUnitNode::RLM_KRL == getUnReciver()->getType() ||
              TypeUnitNode::TG == getUnReciver()->getType() ) {
        getUnReciver()->setDkInvolved(true);
        getUnReciver()->setDkStatus(DKCiclStatus::DKReady);
        getUnReciver()->updDoubl();
        this->lsTrackedUN.append(getUnReciver());
    }

    setTimeIntervalWaiteFirst(11000);
    setTimeIntervalRequest(500);

    connect(this, SIGNAL(importantBeatStatus()), SignalSlotCommutator::getInstance(), SLOT(emitEndDKWait()));
}
