#include "MultiUNStatusConnectRequester.h"

#include "SignalSlotCommutator.h"

#include "PortManager.h"
#include "Utils.h"
#include "global.h"

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
//    qDebug() << "MultiUNStatusConnectRequester::addLsTrackedUN -->";
    for(auto un : lsTrackedUN) {
        if(un->getType() == value->getType() &&
           un->getNum1() == value->getNum1() &&
           un->getUdpPort() == value->getUdpPort() &&
           un->getUdpAdress() == value->getUdpAdress()) {

//            qDebug() << "MultiUNStatusConnectRequester::addLsTrackedUN REJECT " << value->toString();


//            qDebug() << "MultiUNStatusConnectRequester::addLsTrackedUN <--";
            return;
        }
    }

    lsTrackedUN.append(value);

//    for(auto un : lsTrackedUN) {
//        qDebug() << "MultiUNStatusConnectRequester::addLsTrackedUN APRUVE " << un->toString();
//    }



    int sumUdpTimeout = 0;
    for(auto uncld : as_const(getLsTrackedUN())) {
        sumUdpTimeout += uncld->getUdpTimeout();
    }

    int maxBeatCount = 400;
    if(0 < sumUdpTimeout) {
        maxBeatCount = (delayDisconnectStatus / sumUdpTimeout) + 1;
    }

    for(auto uncld : as_const(getLsTrackedUN())) {
        uncld->setMaxCountStatusConnectRequesterWaitAnswer(maxBeatCount);
    }
//    qDebug() << "MultiUNStatusConnectRequester::addLsTrackedUN <--";
}

QSharedPointer<UnitNode> MultiUNStatusConnectRequester::previousTrackedUN() const
{
    if(1 < getLsTrackedUN().size())
    {
        auto index = getLsTrackedUN().indexOf(currentTrackedUN());

        if(0 > index - 1) {
            return getLsTrackedUN().last();
        }

        return getLsTrackedUN().at(index - 1);

    } else if(1 == getLsTrackedUN().size()) {
        return getLsTrackedUN().first();
    }

    return QSharedPointer<UnitNode>::create();
}

QSharedPointer<UnitNode> MultiUNStatusConnectRequester::currentTrackedUN() const
{
    return getUnReciver();
}

QSharedPointer<UnitNode> MultiUNStatusConnectRequester::nextTrackedUN() const
{
//    for(auto un : getLsTrackedUN()) {
//        if(!un->queueMsg.isEmpty() && un != currentTrackedUN()) {
//            return un;
//        }
//    }

    if(1 < getLsTrackedUN().size())
    {
        auto index = getLsTrackedUN().indexOf(currentTrackedUN());

        if(getLsTrackedUN().size() <= index + 1) {
            return getLsTrackedUN().first();
        }

        return getLsTrackedUN().at(index + 1);

    } else if(1 == getLsTrackedUN().size()) {
        return getLsTrackedUN().first();
    }

    return QSharedPointer<UnitNode>::create();
}

int MultiUNStatusConnectRequester::optimalTimeIntervalRequest(QSharedPointer<UnitNode> un) const
{
    int udpTimeout = 50;
    if(TypeUnitNode::BL_IP == un->getType()) {
        for(auto i = 0, n = un->childCount(); i < n; i++) {
            auto cun = un->child(i);
            if(TypeUnitNode::SD_BL_IP == cun->getType() || TypeUnitNode::IU_BL_IP == cun->getType()) {
                udpTimeout = qMax(udpTimeout, cun->getUdpTimeout());
            }
        }
    } else if(TypeUnitNode::TG_Base == un->getType()) {
        for(auto i = 0, n = un->childCount(); i < n; i++) {
            auto cun = un->child(i);
            if(TypeUnitNode::TG == cun->getType()) {
                udpTimeout = qMax(udpTimeout, cun->getUdpTimeout());
            }
        }
    } else {
        udpTimeout = qMax(udpTimeout, un->getUdpTimeout());
    }

    return udpTimeout;
}

void MultiUNStatusConnectRequester::specialReserveSlot() const
{
//    qDebug () << "MultiUNStatusConnectRequester::specialReserveSlot(" << getUnReciver()->toString() << ")";

//    SignalSlotCommutator::getInstance()->emitLostedConnect(getUnReciver());
}


DataQueueItem MultiUNStatusConnectRequester::makeFirstMsg() {
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == currentTrackedUN())
        return result;

    if(currentTrackedUN()->getMaxCountStatusConnectRequesterWaitAnswer() <= currentTrackedUN()->getCountStatusConnectRequesterWaitAnswer()) {
//        qDebug() << "MultiUNStatusConnectRequester::makeFirstMsg() -- max:" << getUnReciver()->getMaxCountSCRWA() << "<= curr:" << getUnReciver()->getCountSCRWA() << " " << getUnReciver()->toString();
        currentTrackedUN()->resetCountStatusConnectRequesterWaitAnswer();
        SignalSlotCommutator::getInstance()->emitLostedConnect(getUnReciver());
    }

    result.setPort(currentTrackedUN()->getUdpPort());
    result.setAddress(Utils::hostAddress(currentTrackedUN()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(TypeUnitNode::BL_IP == currentTrackedUN()->getType() ||
//       TypeUnitNode::SD_BL_IP == currentTrackedUN()->getType() ||
//       TypeUnitNode::IU_BL_IP == currentTrackedUN()->getType() ||
       TypeUnitNode::RLM_C == currentTrackedUN()->getType() ||
       TypeUnitNode::RLM_KRL == currentTrackedUN()->getType() ||
//       TypeUnitNode::TG == currentTrackedUN()->getType() ||
       TypeUnitNode::TG_Base == currentTrackedUN()->getType()) {

        if(!currentTrackedUN()->queueMsg.isEmpty()) {
            result = currentTrackedUN()->queueMsg.dequeue();

            currentTrackedUN()->decrementCountStatusConnectRequesterWaitAnswer();

            setBeatCount(getBeatCount() - 1);
            if(0 > getBeatCount())
                resetBeatCount();
        } else {
            switch (currentTrackedUN()->getNeededStateWordType()) {
                case 0x22: {
                    DataQueueItem::makeStatusRequest0x22(result, currentTrackedUN());
                    break;
                }
                case 0x2A: {
                    DataQueueItem::makeStatusRequest0x2A(result, currentTrackedUN());
                    break;
                }
                case 0x2C: {
                    DataQueueItem::makeStatusRequest0x2C(result, currentTrackedUN());
                    break;
                }
                case 0x2E: {
                    DataQueueItem::makeStatusRequest0x2E(result, currentTrackedUN());
                    break;
                }
                case 0x2A2E: {
                    switch (currentTrackedUN()->leftoversCounter.mod()) {
                        case 0: {
                            DataQueueItem::makeStatusRequest0x2A(result, currentTrackedUN());
                            break;
                        }
                        case 1: {
                            DataQueueItem::makeStatusRequest0x2E(result, currentTrackedUN());
                            break;
                        }
                        default: {
                            DataQueueItem::makeStatusRequest0x22(result, currentTrackedUN());
                            break;
                        }
                    }
                    currentTrackedUN()->leftoversCounter.increment();
                    break;
                }
                case 0x2C2E: {
                    switch (currentTrackedUN()->leftoversCounter.mod()) {
                        case 0: {
                            DataQueueItem::makeStatusRequest0x2C(result, currentTrackedUN());
                            break;
                        }
                        case 1: {
                            DataQueueItem::makeStatusRequest0x2E(result, currentTrackedUN());
                            break;
                        }
                        default: {
                            DataQueueItem::makeStatusRequest0x22(result, currentTrackedUN());
                            break;
                        }
                    }
                    currentTrackedUN()->leftoversCounter.increment();
                    break;
                }
                case 0x2A2C2E: {
                    switch (currentTrackedUN()->leftoversCounter.mod()) {
                        case 0: {
                            DataQueueItem::makeStatusRequest0x2A(result, currentTrackedUN());
                            break;
                        }
                        case 1: {
                            DataQueueItem::makeStatusRequest0x2C(result, currentTrackedUN());
                            break;
                        }
                        case 2: {
                            DataQueueItem::makeStatusRequest0x2E(result, currentTrackedUN());
                            break;
                        }
                        default: {
                            DataQueueItem::makeStatusRequest0x22(result, currentTrackedUN());
                            break;
                        }
                    }
                    currentTrackedUN()->leftoversCounter.increment();
                    break;
                }
                default: {
                    DataQueueItem::makeStatusRequest0x22(result, currentTrackedUN());
                    break;
                }
            }
        }
    }

    int currentSituationUdpTimeout = qMax(optimalTimeIntervalRequest(currentTrackedUN()) * result.getSpecialSkipTimeCount(), result.getSpecialSkipTimeInterval());

    int summaryUdpTimeout = currentSituationUdpTimeout;
    for (auto otherUN : as_const(getLsTrackedUN())) {
        if(otherUN != currentTrackedUN())
            summaryUdpTimeout += optimalTimeIntervalRequest(otherUN);
    }
//    qDebug() << "summaryUdpTimeout(" << summaryUdpTimeout << ")";

    setTimeIntervalRequest(currentSituationUdpTimeout);

    int maxBeatCount = (delayDisconnectStatus / summaryUdpTimeout) + 1;
    for(auto uncld : as_const(getLsTrackedUN())) {
        uncld->setMaxCountStatusConnectRequesterWaitAnswer(maxBeatCount);
    }
//    currentTrackedUN()->setMaxCountStatusConnectRequesterWaitAnswer(maxBeatCount);

    currentTrackedUN()->incrementCountStatusConnectRequesterWaitAnswer();

    auto un = nextTrackedUN();
    setUnReciver(un); // !!! currentTrackedUN changed !!!
    setUnTarget(un);

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
    if(!getUnTarget().isNull()) {
        setUnReciver(UnitNode::findReciver(getUnTarget()));
    }

    if(getUnTarget().isNull() || getUnReciver().isNull())
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

    int udpTimeout = optimalTimeIntervalRequest(currentTrackedUN());
    setTimeIntervalRequest(udpTimeout);

    int maxBeatCount = 400;
    if(50 != udpTimeout) {
        maxBeatCount = (delayDisconnectStatus / udpTimeout) + 1;
    }
    currentTrackedUN()->setMaxCountStatusConnectRequesterWaitAnswer(maxBeatCount);

    setMaxBeatCount(0);

    connect(this, SIGNAL(importantBeatStatus()), this, SLOT(specialReserveSlot()));
}
