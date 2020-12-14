#include "StatusConnectRequester.h"

#include "SignalSlotCommutator.h"

#include <PortManager.h>
#include <Utils.h>
#include <global.hpp>

StatusConnectRequester::StatusConnectRequester(UnitNode * target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
//    qDebug() << "StatusConnectRequester::StatusConnectRequester";
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

void StatusConnectRequester::specialReserveSlot() const
{
    qDebug () << "StatusConnectRequester::specialReserveSlot()";

    SignalSlotCommutator::getInstance()->emitLostedConnect(getUnReciver());
}


DataQueueItem StatusConnectRequester::makeFirstMsg() {
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == getUnReciver())
        return result;

    if(TypeUnitNode::BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::SD_BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::IU_BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::RLM_C == getUnReciver()->getType()) {
    result.setData(DataQueueItem::makeStatusRequest0x22(getUnReciver()));
    }
    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(result.isValid())
        return result;

    return DataQueueItem();
}

DataQueueItem StatusConnectRequester::makeSecondMsg() {
    return DataQueueItem();
}

DataQueueItem StatusConnectRequester::makeEndMsg()
{
    return DataQueueItem();
}

void StatusConnectRequester::init() {
    if(nullptr != getUnTarget()) {
        UnitNode * un = getUnTarget();
        while(nullptr != un) {

            if(TypeUnitNode::BL_IP == un->getType() /* или датчик */ ||
               TypeUnitNode::RLM_C == un->getType()) {
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

    for(UnitNode * uncld : as_const(getUnReciver()->getListChilde())) {
        if(TypeUnitNode::IU_BL_IP == uncld->getType() || TypeUnitNode::SD_BL_IP == uncld->getType() /* или датчик */) {
            this->lsTrackedUN.append(uncld);
        }
    }

    setMaxBeatCount(200);
    setTimeIntervalRequest(100);
    setTimeIntervalWaiteFirst(0);

    connect(this, SIGNAL(unsuccessful()), this, SLOT(specialReserveSlot()));
}
