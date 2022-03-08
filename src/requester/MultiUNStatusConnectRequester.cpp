#include "MultiUNStatusConnectRequester.h"

#include "SignalSlotCommutator.h"

#include "PortManager.h"
#include "Utils.h"
#include "global.h"

#include "TopologyService.h"

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
    for(const auto& un : as_const(lsTrackedUN)) {
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
    for(const auto& uncld : as_const(getLsTrackedUN())) {
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
            return as_const(getLsTrackedUN()).last();
        }

        return getLsTrackedUN().at(index - 1);

    } else if(1 == getLsTrackedUN().size()) {
        return as_const(getLsTrackedUN()).first();
    }

    return QSharedPointer<UnitNode>::create();
}

QSharedPointer<UnitNode> MultiUNStatusConnectRequester::currentTrackedUN() const
{
    return getUnReciver();
}

QSharedPointer<UnitNode> MultiUNStatusConnectRequester::nextTrackedUN() const
{
//    qDebug() << "MultiUNStatusConnectRequester::nextTrackedUN() -->";
    if(1 < getLsTrackedUN().size())
    {
        auto index = getLsTrackedUN().indexOf(currentTrackedUN());

        if(getLsTrackedUN().size() <= index + 1) {
//            qDebug() << "MultiUNStatusConnectRequester::nextTrackedUN() first <--" << QString((getLsTrackedUN().first()->getDkInvolved() ? "DK! " : "")) << getLsTrackedUN().first()->toString();
            return as_const(getLsTrackedUN()).first();
        }
//        qDebug() << "MultiUNStatusConnectRequester::nextTrackedUN() at(" << (index + 1) << ") <--" << QString((getLsTrackedUN().at(index + 1)->getDkInvolved() ? "DK! " : "")) << getLsTrackedUN().at(index + 1)->toString();
        return getLsTrackedUN().at(index + 1);

    } else if(1 == getLsTrackedUN().size()) {
//        qDebug() << "MultiUNStatusConnectRequester::nextTrackedUN() first <--" << QString((getLsTrackedUN().first()->getDkInvolved() ? "DK! " : "")) << getLsTrackedUN().first()->toString();
        return as_const(getLsTrackedUN()).first();
    }
//    qDebug() << "MultiUNStatusConnectRequester::nextTrackedUN() null <--";
    return QSharedPointer<UnitNode>::create();
}

int MultiUNStatusConnectRequester::optimalTimeIntervalRequest(QSharedPointer<UnitNode> un) const
{
    int udpTimeout = 50;
    if(TypeUnitNodeEnum::SSOI_BL_IP == un->getType()) {
        for(const auto& cun : as_const(TopologyService::findChild(un))) {
            if(TypeUnitNodeEnum::SSOI_SD_BL_IP == cun->getType()
            || TypeUnitNodeEnum::SSOI_IU_BL_IP == cun->getType()) {
                udpTimeout = qMax(udpTimeout, cun->getUdpTimeout());
            }
        }
    } else if(TypeUnitNodeEnum::BL_IP == un->getType()) {
        for(const auto& cun : as_const(TopologyService::findChild(un))) {
            if(TypeUnitNodeEnum::SD_BL_IP == cun->getType()
            || TypeUnitNodeEnum::IU_BL_IP == cun->getType()) {
                udpTimeout = qMax(udpTimeout, cun->getUdpTimeout());
            }
        }
    } else if(TypeUnitNodeEnum::TG_Base == un->getType()) {
        for(const auto& cun : as_const(TopologyService::findChild(un))) {
            if(TypeUnitNodeEnum::TG == cun->getType()) {
                udpTimeout = qMax(udpTimeout, cun->getUdpTimeout());
            }
        }
    } else if(TypeUnitNodeEnum::BOD_T4K_M == un->getType()) {
        for(const auto& cun : as_const(TopologyService::findChild(un))) {
            udpTimeout = qMax(udpTimeout, cun->getUdpTimeout());
        }
    } else {
        udpTimeout = qMax(udpTimeout, un->getUdpTimeout());
    }

    return udpTimeout;
}

void MultiUNStatusConnectRequester::incrementAllTrackedUNTimeStatusConnectRequesterWaitAnswer(int incrementDelay)
{
    for(const auto& un : as_const(getLsTrackedUN())) {
        un->incrementTimeStatusConnectRequesterWaitAnswer(incrementDelay);
        if(delayDisconnectStatus <= un->getTimeStatusConnectRequesterWaitAnswer()) {
            un->resetTimeStatusConnectRequesterWaitAnswer();
            SignalSlotCommutator::emitLostedConnect(un);
        }
    }
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
//        SignalSlotCommutator::emitLostedConnect(getUnReciver());
    }

    if(delayDisconnectStatus <= currentTrackedUN()->getTimeStatusConnectRequesterWaitAnswer()) {
//        qDebug() << "MultiUNStatusConnectRequester::makeFirstMsg() -- max:" << getUnReciver()->getMaxCountSCRWA() << "<= curr:" << getUnReciver()->getCountSCRWA() << " " << getUnReciver()->toString();
        currentTrackedUN()->resetTimeStatusConnectRequesterWaitAnswer();
        SignalSlotCommutator::emitLostedConnect(getUnReciver());
    }


    result.setPort(currentTrackedUN()->getUdpPort());
    result.setAddress(Utils::hostAddress(currentTrackedUN()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(TypeUnitNodeEnum::BL_IP == currentTrackedUN()->getType()
    || TypeUnitNodeEnum::SSOI_BL_IP == currentTrackedUN()->getType()
//    || TypeUnitNode::SD_BL_IP == currentTrackedUN()->getType()
//    || TypeUnitNode::IU_BL_IP == currentTrackedUN()->getType()
    || TypeUnitNodeEnum::RLM_C == currentTrackedUN()->getType()
    || TypeUnitNodeEnum::RLM_KRL == currentTrackedUN()->getType()
//    || TypeUnitNode::TG == currentTrackedUN()->getType()
    || TypeUnitNodeEnum::TG_Base == currentTrackedUN()->getType()
    || TypeUnitNodeEnum::BOD_T4K_M == currentTrackedUN()->getType()) {

        if(!currentTrackedUN()->getListManagersSingleMsg().isEmpty()) {
            auto headMSMsg = currentTrackedUN()->getFirstManagerSingleMsg();
            if(3 <= headMSMsg->getCountMaker()) {
                const auto& msm = currentTrackedUN()->takeFirstManagerSingleMsg();
                if(!msm.isNull()) {
                    msm->callReject();
                }
            }
        }

        if(!currentTrackedUN()->getListManagersSingleMsg().isEmpty()
        && !currentTrackedUN()->getNeedPostponeQueueMsg()) {
//            qDebug() << "currentTrackedUN(" << currentTrackedUN()->toString() << ")->QueueManagersSingleMsg(" << currentTrackedUN()->getQueueManagersSingleMsg().size() << ")";
            currentTrackedUN()->setNeedPostponeQueueMsg(true);
            auto headMSMsg = currentTrackedUN()->getFirstManagerSingleMsg();

            result = headMSMsg->makeDatagram();

            currentTrackedUN()->decrementCountStatusConnectRequesterWaitAnswer();

            setBeatCount(getBeatCount() - 1);
            if(0 > getBeatCount())
                resetBeatCount();
        } else if(!currentTrackedUN()->getQueueMsg().isEmpty() && !currentTrackedUN()->getNeedPostponeQueueMsg()) {
//            qDebug() << "currentTrackedUN(" << currentTrackedUN()->toString() << ")->queueMsg(" << currentTrackedUN()->queueMsg.size() << ")";
            currentTrackedUN()->setNeedPostponeQueueMsg(true);
            result = currentTrackedUN()->pullQueueMsg();

            currentTrackedUN()->decrementCountStatusConnectRequesterWaitAnswer();

            setBeatCount(getBeatCount() - 1);
            if(0 > getBeatCount())
                resetBeatCount();
        } else {
            currentTrackedUN()->setNeedPostponeQueueMsg(false);
            switch (currentTrackedUN()->getNeededStateWordType()) {
                case 0x20: { // 30
                    DataQueueItem::fillSpecifyingSettingsBOD0x20(result, currentTrackedUN());
                    break;
                }
                case 0x22: { // 41 | 31
                    DataQueueItem::fillStatusRequest0x22(result, currentTrackedUN());
                    break;
                }
                case 0x2A: { // 32
                    DataQueueItem::fillStatusRequest0x2A(result, currentTrackedUN());
                    break;
                }
                case 0x2C: { // 34
                    DataQueueItem::fillStatusRequest0x2C(result, currentTrackedUN());
                    break;
                }
                case 0x2E: { // 33
                    DataQueueItem::fillStatusRequest0x2E(result, currentTrackedUN());
                    break;
                }
                case 0x2225: { // 41 & 42
                    switch (currentTrackedUN()->leftoversCounter.mod()) {
                        case 0: {
                            DataQueueItem::fillStatusRequest0x22(result, currentTrackedUN());
                            break;
                        }
                        case 1: {
                            DataQueueItem::fillOff0x25(result, currentTrackedUN());
                            break;
                        }
                        default: {
                            DataQueueItem::fillStatusRequest0x22(result, currentTrackedUN());
                            break;
                        }
                    }
                    currentTrackedUN()->leftoversCounter.increment();
                    break;
                }
                case 0x2A2E: { // 32 & 33
                    switch (currentTrackedUN()->leftoversCounter.mod()) {
                        case 0: {
                            DataQueueItem::fillStatusRequest0x2A(result, currentTrackedUN());
                            break;
                        }
                        case 1: {
                            DataQueueItem::fillStatusRequest0x2E(result, currentTrackedUN());
                            break;
                        }
                        default: {
                            DataQueueItem::fillStatusRequest0x22(result, currentTrackedUN());
                            break;
                        }
                    }
                    currentTrackedUN()->leftoversCounter.increment();
                    break;
                }
                case 0x2E2D: {
                    switch (currentTrackedUN()->leftoversCounter.mod()) {
                        case 0: {
                            DataQueueItem::fillStatusRequest0x2E(result, currentTrackedUN());
                            break;
                        }
                        case 1: {
                            DataQueueItem::fillStatusRequest0x2D(result, currentTrackedUN());
                            break;
                        }
                        default: {
                            DataQueueItem::fillStatusRequest0x2E(result, currentTrackedUN());
                            break;
                        }
                    }
                    currentTrackedUN()->leftoversCounter.increment();
                    break;
                }
                case 0x2C2E: { // 34 & 33
                    switch (currentTrackedUN()->leftoversCounter.mod()) {
                        case 0: {
                            DataQueueItem::fillStatusRequest0x2C(result, currentTrackedUN());
                            break;
                        }
                        case 1: {
                            DataQueueItem::fillStatusRequest0x2E(result, currentTrackedUN());
                            break;
                        }
                        default: {
                            DataQueueItem::fillStatusRequest0x22(result, currentTrackedUN());
                            break;
                        }
                    }
                    currentTrackedUN()->leftoversCounter.increment();
                    break;
                }
                case 0x2A2C2E: { // 32 & 34 & 33
                    switch (currentTrackedUN()->leftoversCounter.mod()) {
                        case 0: {
                            DataQueueItem::fillStatusRequest0x2A(result, currentTrackedUN());
                            break;
                        }
                        case 1: {
                            DataQueueItem::fillStatusRequest0x2C(result, currentTrackedUN());
                            break;
                        }
                        case 2: {
                            DataQueueItem::fillStatusRequest0x2E(result, currentTrackedUN());
                            break;
                        }
                        default: {
                            DataQueueItem::fillStatusRequest0x22(result, currentTrackedUN());
                            break;
                        }
                    }
                    currentTrackedUN()->leftoversCounter.increment();
                    break;
                }
                default: {
                    DataQueueItem::fillStatusRequest0x22(result, currentTrackedUN());
                    break;
                }
            }
        }
    }

    int currentSituationUdpTimeout = qMax(optimalTimeIntervalRequest(currentTrackedUN()) * result.getSpecialSkipTimeCount(), result.getSpecialSkipTimeInterval());

    int summaryUdpTimeout = currentSituationUdpTimeout;
    for (const auto& otherUN : as_const(getLsTrackedUN())) {
        if(otherUN != currentTrackedUN())
            summaryUdpTimeout += optimalTimeIntervalRequest(otherUN);
    }
//    qDebug() << "summaryUdpTimeout(" << summaryUdpTimeout << ")";

    setTimeIntervalRequest(currentSituationUdpTimeout);
    incrementAllTrackedUNTimeStatusConnectRequesterWaitAnswer(currentSituationUdpTimeout);
    int maxBeatCount = (delayDisconnectStatus / summaryUdpTimeout) + 1;
    for(auto uncld : as_const(getLsTrackedUN())) {
        uncld->setMaxCountStatusConnectRequesterWaitAnswer(maxBeatCount);
    }
//    currentTrackedUN()->setMaxCountStatusConnectRequesterWaitAnswer(maxBeatCount);

    currentTrackedUN()->incrementCountStatusConnectRequesterWaitAnswer();

    if(result.isValid())
        return result;

    return DataQueueItem();
}

void MultiUNStatusConnectRequester::aspectAfterFirstRequest()
{
    auto un = nextTrackedUN();
    setUnReciver(un); // !!! currentTrackedUN changed !!!
//    qDebug() << "MultiUNStatusConnectRequester::aspectAfterFirstRequest (!!! currentTrackedUN changed !!!)" << getUnReciver()->toString();
    setUnTarget(un);
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
        setUnReciver(TopologyService::findReciver(getUnTarget()));
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
    incrementAllTrackedUNTimeStatusConnectRequesterWaitAnswer(udpTimeout);

    int maxBeatCount = 400;
    if(50 != udpTimeout) {
        maxBeatCount = (delayDisconnectStatus / udpTimeout) + 1;
    }
    currentTrackedUN()->setMaxCountStatusConnectRequesterWaitAnswer(maxBeatCount);

    setMaxBeatCount(0);

    connect(this, SIGNAL(importantBeatStatus()), this, SLOT(specialReserveSlot()));
}
