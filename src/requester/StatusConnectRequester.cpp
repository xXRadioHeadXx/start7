#include "StatusConnectRequester.h"

#include "SignalSlotCommutator.h"

#include <PortManager.h>
#include <Utils.h>

StatusConnectRequester::StatusConnectRequester(UnitNode * target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
    qDebug() << "StatusConnectRequester::StatusConnectRequester";
}

StatusConnectRequester::~StatusConnectRequester()
{
//    qDebug() << "StatusConnectRequester::~StatusConnectRequester()";
    Port::typeDefPort(getPtrPort())->setProcDK(false);
}

QList<UnitNode *> StatusConnectRequester::getLsTrackedUN() const
{
    return lsTrackedUN;
}

void StatusConnectRequester::setLsTrackedUN(const QList<UnitNode *> &value)
{
    lsTrackedUN = value;
}

void StatusConnectRequester::addLsTrackedUN(UnitNode *  value)
{
    lsTrackedUN.append(value);
}


DataQueueItem StatusConnectRequester::makeFirstMsg() {
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

DataQueueItem StatusConnectRequester::makeSecondMsg() {
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

void StatusConnectRequester::init() {
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
            this->lsTrackedUN.append(uncld);
        }
    }

    setTimeIntervalWaite(11000);
    setTimeIntervalRequest(500);

    connect(this, SIGNAL(unsuccessful()), SignalSlotCommutator::getInstance(), SLOT(emitEndDKWait()));
}
