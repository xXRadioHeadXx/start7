#include "MultiUNStatusConnectRequester.h"

#include "SignalSlotCommutator.h"

#include <PortManager.h>
#include <Utils.h>
#include <global.h>

MultiUNStatusConnectRequester::MultiUNStatusConnectRequester(QSharedPointer<UnitNode>  target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
//    qDebug() << "MultiUNStatusConnectRequester::MultiUNStatusConnectRequester(" << this << ") -->";
}

MultiUNStatusConnectRequester::~MultiUNStatusConnectRequester()
{
//    qDebug() << "MultiUNStatusConnectRequester::~MultiUNStatusConnectRequester(" << this << ") <--";
    Port::typeDefPort(getPtrPort())->setProcDK(false);
}

QList<QSharedPointer<UnitNode> > MultiUNStatusConnectRequester::getLsTrackedUN() const
{
    return lsTrackedUN;
}

void MultiUNStatusConnectRequester::setLsTrackedUN(const QList<QSharedPointer<UnitNode>> &value)
{
    lsTrackedUN = value;
}

void MultiUNStatusConnectRequester::addLsTrackedUN(QSharedPointer<UnitNode>  value)
{
    qDebug() << "MultiUNStatusConnectRequester::addLsTrackedUN -->";
    for(auto un : lsTrackedUN) {
        if(un->getType() == value->getType() &&
           un->getNum1() == value->getNum1() &&
           un->getUdpPort() == value->getUdpPort() &&
           un->getUdpAdress() == value->getUdpAdress()) {

            qDebug() << "MultiUNStatusConnectRequester::addLsTrackedUN REJECT " << value->toString();


            qDebug() << "MultiUNStatusConnectRequester::addLsTrackedUN <--";
            return;
        }
    }

    lsTrackedUN.append(value);

    for(auto un : lsTrackedUN) {
        qDebug() << "MultiUNStatusConnectRequester::addLsTrackedUN APRUVE " << un->toString();
    }
    qDebug() << "MultiUNStatusConnectRequester::addLsTrackedUN <--";



    int sumUdpTimeout = 0;
    for(auto uncld : as_const(getLsTrackedUN())) {
        sumUdpTimeout += uncld->getUdpTimeout();
    }

    int maxBeatCount = 400;
    if(0 < sumUdpTimeout) {
        maxBeatCount = (delayDisconnectStatus / sumUdpTimeout) + 1;
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
//        qDebug() << "MultiUNStatusConnectRequester::makeFirstMsg() -- max:" << getUnReciver()->getMaxCountSCRWA() << "<= curr:" << getUnReciver()->getCountSCRWA() << " " << getUnReciver()->toString();
        getUnReciver()->setCountSCRWA(0);
        SignalSlotCommutator::getInstance()->emitLostedConnect(getUnReciver());
    }

    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(TypeUnitNode::BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::SD_BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::IU_BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::RLM_C == getUnReciver()->getType() ||
       TypeUnitNode::RLM_KRL == getUnReciver()->getType() ||
       TypeUnitNode::TG == getUnReciver()->getType()) {

        if(!getUnReciver()->queueMsg.isEmpty()) {
            result = getUnReciver()->queueMsg.dequeue();
        } else {
            switch (getUnReciver()->getNeededStateWordType()) {
                case 0: {
                    DataQueueItem::makeStatusRequest0x22(result, getUnReciver());
                    break;
                }
                case 1: {
                    DataQueueItem::makeStatusRequest0x2A(result, getUnReciver());
                    break;
                }
                case 2: {
                    DataQueueItem::makeStatusRequest0x2C(result, getUnReciver());
                    break;
                }
                case 3: {
                    DataQueueItem::makeStatusRequest0x2E(result, getUnReciver());
                    break;
                }
                default: {
                    DataQueueItem::makeStatusRequest0x22(result, getUnReciver());
                    break;
                }
            }
        }
    }

    if(1 < getLsTrackedUN().size())
    {
        int udpTimeout = 50;
        udpTimeout = qMax(udpTimeout, getUnReciver()->getUdpTimeout());
        setTimeIntervalRequest(udpTimeout);

        int index = getLsTrackedUN().indexOf(getUnReciver());
        QSharedPointer<UnitNode>  un = nullptr;
        if( -1 == index || index >= getLsTrackedUN().size() ) {
            un = getLsTrackedUN().value(0, nullptr);
        } else {
            un = getLsTrackedUN().value(index + 1, getLsTrackedUN().value(0, nullptr));
        }
        setUnReciver(un);
        setUnTarget(un);



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
        QSharedPointer<UnitNode>  un = getUnTarget();
        while(nullptr != un) {

            if(TypeUnitNode::BL_IP == un->getType() /* или датчик */ ||
               TypeUnitNode::RLM_C == un->getType() ||
               TypeUnitNode::RLM_KRL == un->getType() ||
               TypeUnitNode::TG == un->getType()) {
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

//    for(QSharedPointer<UnitNode>  uncld : as_const(getUnReciver()->getListChilde())) {
//        if(TypeUnitNode::IU_BL_IP == uncld->getType() || TypeUnitNode::SD_BL_IP == uncld->getType() /* или датчик */) {
//            this->lsTrackedUN.append(uncld);
//        }
//    }

    setTimeIntervalWaiteFirst(0);

    int udpTimeout = 50;

    if(TypeUnitNode::BL_IP == getUnReciver()->getType()) {
        for(QSharedPointer<UnitNode>  uncld : as_const(getUnReciver()->getListChilde())) {
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

    setMaxBeatCount(0);

    connect(this, SIGNAL(importantBeatStatus()), this, SLOT(specialReserveSlot()));
}
