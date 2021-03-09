#include "MultiUNStatusConnectRequester.h"

#include "SignalSlotCommutator.h"

#include <PortManager.h>
#include <Utils.h>
#include <global.hpp>

MultiUNStatusConnectRequester::MultiUNStatusConnectRequester(UnitNode * target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
//    qDebug() << "MultiUNStatusConnectRequester::MultiUNStatusConnectRequester(" << this << ") -->";
}

MultiUNStatusConnectRequester::~MultiUNStatusConnectRequester()
{
//    qDebug() << "MultiUNStatusConnectRequester::~MultiUNStatusConnectRequester(" << this << ") <--";
    Port::typeDefPort(getPtrPort())->setProcDK(false);
}

QList<UnitNode *> MultiUNStatusConnectRequester::getLsTrackedUN() const
{
    return lsTrackedUN;
}

void MultiUNStatusConnectRequester::setLsTrackedUN(const QList<UnitNode *> &value)
{
    lsTrackedUN = value;
}

void MultiUNStatusConnectRequester::addLsTrackedUN(UnitNode *  value)
{
    lsTrackedUN.append(value);

    int sumUdpTimeout = 0;
    for(auto uncld : as_const(getLsTrackedUN())) {
        sumUdpTimeout += uncld->getUdpTimeout();
    }

    int maxBeatCount = 400;
    if(0 < sumUdpTimeout) {
        maxBeatCount = (20500 / sumUdpTimeout) + 1;
    }

    for(auto uncld : as_const(getLsTrackedUN())) {
        uncld->setMaxCountSCRWA(maxBeatCount);
    }

}

void MultiUNStatusConnectRequester::specialReserveSlot() const
{
//    qDebug () << "MultiUNStatusConnectRequester::specialReserveSlot(" << getUnReciver()->toString() << ")";

//    SignalSlotCommutator::getInstance()->emitLostedConnect(getUnReciver());
}


DataQueueItem MultiUNStatusConnectRequester::makeFirstMsg() {
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == getUnReciver())
        return result;

    if(getUnReciver()->getMaxCountSCRWA() <= getUnReciver()->getCountSCRWA()) {
        SignalSlotCommutator::getInstance()->emitLostedConnect(getUnReciver());
    }

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

    {
        int index = getLsTrackedUN().indexOf(getUnReciver());
        UnitNode * un = nullptr;
        if( -1 == index || index + 1 >= getLsTrackedUN().size() ) {
            un = getLsTrackedUN().value(0, nullptr);
        } else {
            un = getLsTrackedUN().at(index + 1);
        }
        setUnReciver(un);
        setUnTarget(un);

        int udpTimeout = 50;
        udpTimeout = qMax(udpTimeout, getUnReciver()->getUdpTimeout());
        setTimeIntervalRequest(udpTimeout);

        getUnReciver()->setCountSCRWA(getUnReciver()->getCountSCRWA() + 1);
    }

    if(result.isValid())
        return result;

    return DataQueueItem();
}

DataQueueItem MultiUNStatusConnectRequester::makeSecondMsg() {
    return DataQueueItem();
}

DataQueueItem MultiUNStatusConnectRequester::makeEndMsg()
{
    return DataQueueItem();
}

void MultiUNStatusConnectRequester::init() {
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

//    for(UnitNode * uncld : as_const(getUnReciver()->getListChilde())) {
//        if(TypeUnitNode::IU_BL_IP == uncld->getType() || TypeUnitNode::SD_BL_IP == uncld->getType() /* или датчик */) {
//            this->lsTrackedUN.append(uncld);
//        }
//    }

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
        maxBeatCount = (20500 / udpTimeout) + 1;
    }

    setMaxBeatCount(maxBeatCount);

    connect(this, SIGNAL(importantBeatStatus()), this, SLOT(specialReserveSlot()));
}
