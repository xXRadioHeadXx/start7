#include "../src/requester/StatusConnectRequester.h"

#include "../src/requester/AbstractRequester.h"
#include "../src/utils/SignalSlotCommutator.h"
#include "../src/template/SingletonTemplate.h"
#include "../src/entity/TypeUnitNode.h"

#include "../src/port/PortManager.h"
#include "../src/utils/Utils.h"
#include "../src/global.h"

StatusConnectRequester::StatusConnectRequester(UnitNode * target, RequesterType requesterType) : AbstractRequester(QSharedPointer<UnitNode>(target), requesterType)
{
//    //qDebug() << "StatusConnectRequester::StatusConnectRequester(" << this << ") -->";
}

StatusConnectRequester::~StatusConnectRequester()
{
//    //qDebug() << "StatusConnectRequester::~StatusConnectRequester(" << this << ") <--";
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
//    qDebug () << "StatusConnectRequester::specialReserveSlot(" << getUnReciver()->toString() << ")";

    SignalSlotCommutator::instance().emitLostedConnect(getUnReciver());
}


DataQueueItem StatusConnectRequester::makeFirstMsg() {
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == getUnReciver())
        return result;

    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(TypeUnitNode::BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::SD_BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::IU_BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::RLM_C == getUnReciver()->getType() ||
       TypeUnitNode::RLM_KRL == getUnReciver()->getType()) {
        DataQueueItem::makeStatusRequest0x22(result, getUnReciver());
    }

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
               TypeUnitNode::RLM_C == un->getType() ||
               TypeUnitNode::RLM_KRL == un->getType()) {
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

    setTimeIntervalWaiteFirst(0);

    int udpTimeout = 50;

    if(TypeUnitNode::BL_IP == getUnReciver()->getType()) {
        for(UnitNode * uncld : as_const(getUnReciver()->getListChilde())) {
            if(TypeUnitNode::IU_BL_IP == uncld->getType() || TypeUnitNode::SD_BL_IP == uncld->getType() /* или датчик */) {
                udpTimeout = qMax(udpTimeout, uncld->getUdpTimeout());
            }
        }
    } else {
        udpTimeout = qMax(udpTimeout, getUnReciver()->getUdpTimeout());
    }
    setTimeIntervalRequest(udpTimeout);

    int maxBeatCount = 400;
    if(50 != udpTimeout) {
        maxBeatCount = (delayDisconnectStatus / udpTimeout) + 1;
    }

    setMaxBeatCount(maxBeatCount);

    connect(this, SIGNAL(importantBeatStatus()), this, SLOT(specialReserveSlot()));
}
