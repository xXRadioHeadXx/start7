#include "ProcessDKWaiter.h"
#include "SignalSlotCommutator.h"

#include <PortManager.h>
#include <Utils.h>

ProcessDKWaiter::ProcessDKWaiter(UnitNode * target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
    qDebug() << "ProcessDKWaiter::ProcessDKWaiter";
}

ProcessDKWaiter::~ProcessDKWaiter()
{
//    qDebug() << "ProcessDKWaiter::~ProcessDKWaiter()";
    Utils::typeDefPort(getPtrPort())->setProcDK(false);
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

    result.setData(Utils::makeDK0x21(getUnReciver()));
    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Utils::typeDefPort(getPtrPort())->getPortIndex());

    if(result.isValid())
        return result;

    return DataQueueItem();
}

DataQueueItem ProcessDKWaiter::makeSecondMsg() {
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == getUnReciver())
        return result;

    result.setData(Utils::makeAlarmReset0x24(getUnReciver()));
    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Utils::typeDefPort(getPtrPort())->getPortIndex());

    if(result.isValid())
        return result;

    return DataQueueItem();
}

void ProcessDKWaiter::init() {
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
        if(Utils::typeDefPort(pt)->getStIpPort().contains(getIpPort())) {
            setPtrPort(pt);
            setPortIndex(Utils::typeDefPort(getPtrPort())->getPortIndex());
            break;
        }
    }

    for(UnitNode * uncld : getUnReciver()->getListChilde()) {
        if(0 != uncld->getDK() && (TypeUnitNode::SD_BL_IP == uncld->getType() /* или датчик */)) {
            uncld->setDkInvolved(true);
            uncld->setDkStatus(DKCiclStatus::DKReady);
            uncld->updDoubl();
            this->lsTrackedUN.append(uncld);
        }
    }

    setTimeIntervalWaite(11000);
    setTimeIntervalRequest(500);

    connect(this, SIGNAL(unsuccessful()), SignalSlotCommutator::getInstance(), SLOT(emitEndDKWait()));
}
