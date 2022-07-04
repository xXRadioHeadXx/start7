#include "../src/requester/ProcessDKWaiter.h"
#include "../src/utils/SignalSlotCommutator.h"

#include "../src/port/PortManager.h"
#include "../src/utils/Utils.h"
#include "../src/global.h"

#include "../src/statewordparsers/swpblip/SWPBLIPType0x41.h"
#include "../src/statewordparsers/swpblip/SWPSDBLIPType0x41.h"
#include "../src/statewordparsers/swpblip/SWPIUBLIPType0x41.h"
#include "../src/statewordparsers/swprlm/SWPRLMType0x31.h"
#include "../src/statewordparsers/swprlmc/SWPRLMCType0x31.h"
#include "../src/statewordparsers/swptg/SWPTGType0x31.h"
#include "../src/statewordparsers/swptg/SWPTGType0x32.h"
#include "../src/statewordparsers/swptg/SWPTGSubType0x32.h"
#include "../src/statewordparsers/swptg/SWPTGType0x33.h"
#include "../src/statewordparsers/swptg/SWPTGSubType0x33.h"
#include "../src/statewordparsers/swpt4k/SWPT4KBODType0x32.h"
#include "../src/statewordparsers/swpt4k/SWPT4KBODType0x33.h"
#include "../src/statewordparsers/swpt4k/SWPT4KY4Type0x32.h"
#include "../src/statewordparsers/swpt4k/SWPT4KY4Type0x33.h"

#include "../src/utils/MessageBoxServer.h"
#include "../src/utils/ServerSettingUtils.h"
#include "../src/utils/TopologyService.h"

ProcessDKWaiter::ProcessDKWaiter(const bool isAuto, const bool fromAbonent, QSharedPointer<UnitNode>  target, RequesterType requesterType) :
    AbstractRequester(target, requesterType),
    isAuto(isAuto),
    fromAbonent(fromAbonent)
{
    //qDebug() << "ProcessDKWaiter::ProcessDKWaiter(" << this << ") -->";
}

ProcessDKWaiter::~ProcessDKWaiter()
{
    //qDebug() << "ProcessDKWaiter::~ProcessDKWaiter(" << this << ") <--";
    Port::typeDefPort(getPtrPort())->setProcDK(false);
//    if(TypeUnitNode::BL_IP == getUnReciver()->getType()) {
//        getUnReciver()->setDkInvolved(false);
//    }
    getUnReciver()->setDkInvolved(false);
    auto reciver = TopologyService::findReciver(getUnReciver());
    if(!reciver.isNull()) {
       reciver->setDkInvolved(false);
    }
    for(const auto& cld : as_const(getUnReciver()->getListChilde())) {
        cld->setDkInvolved(false);
    }
    TopologyService::systemUnitNodesSetDkInvolvedFalse();
}

QList<QSharedPointer<UnitNode> > ProcessDKWaiter::getLsTrackedUN() const
{
    return lsTrackedUN;
}

void ProcessDKWaiter::setLsTrackedUN(const QList<QSharedPointer<UnitNode> > &value)
{
    lsTrackedUN = value;
}

void ProcessDKWaiter::addLsTrackedUN(QSharedPointer<UnitNode> value)
{
    lsTrackedUN.append(value);
    //    qDebug() << "ProcessDKWaiter::addLsTrackedUN(" << value->toString() << ")";
}

bool ProcessDKWaiter::removeLsTrackedUN(const QSharedPointer<UnitNode> value)
{
    return 0 != lsTrackedUN.removeAll(value);
    //    qDebug() << "ProcessDKWaiter::addLsTrackedUN(" << value->toString() << ")";
}


const QList<QSharedPointer<UnitNode> > &ProcessDKWaiter::getLsTrackedUN()
{
    return lsTrackedUN;
}

DataQueueItem ProcessDKWaiter::makeFirstMsg() {
    qDebug() << "DataQueueItem ProcessDKWaiter::makeFirstMsg() -->";
    DataQueueItem result;
    qDebug() << "DataQueueItem ProcessDKWaiter::makeFirstMsg() <--";
    return result;
}

DataQueueItem ProcessDKWaiter::makeSecondMsg() {
    qDebug() << "DataQueueItem ProcessDKWaiter::makeSecondMsg() -->";
    DataQueueItem result;
    qDebug() << "DataQueueItem ProcessDKWaiter::makeSecondMsg() <--";
    return result;
}

DataQueueItem ProcessDKWaiter::makeEndMsg()
{
    return DataQueueItem();
}

void ProcessDKWaiter::init() {
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

    if(TypeUnitNodeEnum::SSOI_BL_IP == getUnReciver()->getType()) {
        for(QSharedPointer<UnitNode>  uncld : as_const(getUnReciver()->getListChilde())) {
            if(0 != uncld->getDK()
            && (TypeUnitNodeEnum::SSOI_SD_BL_IP == uncld->getType() /* или датчик */)) {
                uncld->setIsAutoDkInvolved(isAuto);
                uncld->setDkInvolved(true);
                uncld->setDkStatus(DKCiclStatus::DKReady);
                uncld->updDoubl();
                addLsTrackedUN(uncld);
            }
        }
        getUnReciver()->setIsAutoDkInvolved(isAuto);
        getUnReciver()->setDkInvolved(true);
    } else if(TypeUnitNodeEnum::BL_IP == getUnReciver()->getType()) {
        for(QSharedPointer<UnitNode>  uncld : as_const(getUnReciver()->getListChilde())) {
            if(0 != uncld->getDK()
            && (TypeUnitNodeEnum::SD_BL_IP == uncld->getType() /* или датчик */)) {
                uncld->setIsAutoDkInvolved(isAuto);
                uncld->setDkInvolved(true);
                uncld->setDkStatus(DKCiclStatus::DKReady);
                uncld->updDoubl();
                addLsTrackedUN(uncld);
            }
        }
        getUnReciver()->setIsAutoDkInvolved(isAuto);
        getUnReciver()->setDkInvolved(true);
    } else if(TypeUnitNodeEnum::TG_Base == getUnReciver()->getType()) {
        for(QSharedPointer<UnitNode>  uncld : as_const(getUnReciver()->getListChilde())) {
            if(TypeUnitNodeEnum::TG == uncld->getType() /* или датчик */) {
                uncld->setIsAutoDkInvolved(isAuto);
                uncld->setDkInvolved(true);
                const auto& swp31 = uncld->swpTGType0x31();
                const auto& swp32 = uncld->swpTGType0x32().C(uncld->getNum2());
                const auto& swp33 = uncld->swpTGType0x33().C(uncld->getNum2());
                if((!swp31.isNull() && (swp32.cdate() < swp31.cdate() && swp33.cdate() < swp31.cdate())) &&
                   (1 == swp31.isOn()
                 || (1 == swp31.isOn()
                  && 1 != swp31.isNorm())
                 || (1 == swp31.isOn()
                  && 1 == swp31.isOpened()
                  && 1 == swp31.isWasOpened())
                 || (1 == swp31.isAlarm()
                  && 1 == swp31.isWasAlarm()))) {
                    uncld->setDkStatus(DKCiclStatus::DKWrong);
                    qDebug() << "DKCiclStatus::DKWrong 31 " << swp31.byteWord().toHex();
                } else if((!swp32.isNull() && (swp31.cdate() < swp32.cdate() && swp33.cdate() < swp32.cdate())) &&
                          (1 != swp32.isNorm()
                        || 1 == swp32.isFault()
                        || 1 == swp32.isOpened()
                        || 1 == swp32.isAlarm())) {
                    uncld->setDkStatus(DKCiclStatus::DKWrong);
                    qDebug() << "DKCiclStatus::DKWrong 32 " << swp31.byteWord().toHex();
                } else if((!swp33.isNull() && (swp31.cdate() < swp33.cdate() && swp32.cdate() < swp33.cdate()))
                       && (1 != swp33.isNorm()
                        || 1 == swp33.isFault()
                        || 1 == swp33.isOpened()
                        || 1 == swp33.isAlarm())) {
                    uncld->setDkStatus(DKCiclStatus::DKWrong);
                    qDebug() << "DKCiclStatus::DKWrong 33 " << swp31.byteWord().toHex();
                } else {
                    uncld->setDkStatus(DKCiclStatus::DKReady);
                }
                uncld->updDoubl();
                addLsTrackedUN(uncld);
            }
        }
        getUnReciver()->setIsAutoDkInvolved(isAuto);
        getUnReciver()->setDkInvolved(true);
    } else if(TypeUnitNodeEnum::RLM_C == getUnReciver()->getType() ||
              TypeUnitNodeEnum::RLM_KRL == getUnReciver()->getType()) {
        getUnReciver()->setIsAutoDkInvolved(isAuto);
        getUnReciver()->setDkInvolved(true);
        getUnReciver()->setDkStatus(DKCiclStatus::DKReady);
        getUnReciver()->updDoubl();
        addLsTrackedUN(getUnReciver());
    } else if(TypeUnitNodeEnum::BOD_T4K_M == getUnReciver()->getType()) {
        const auto& swp32 = getUnReciver()->swpT4KBODType0x32();
        const auto& swp33 = getUnReciver()->swpT4KBODType0x32();

        for(const auto &y4 : {1,2,3,4}) {
            if(swp32.isNull()
            && swp32.isNull()) {
                getUnReciver()->setDkStatus(DKCiclStatus::DKWrong);
                qDebug() << "DKCiclStatus::DKWrong ";
                break;
            } else if((!swp32.isNull()
                    && (swp32.cdate() > swp33.cdate()))
                   && (0 == swp32.isReady()
                     || 1 == swp32.isInOpened()
                     || 1 == swp32.isWasOpened()
                     || 1 == swp32.y(y4).isInAlarm()
                     || 1 == swp32.y(y4).isWasAlarm())) {
                getUnReciver()->setDkStatus(DKCiclStatus::DKWrong);
                qDebug() << "DKCiclStatus::DKWrong 32 " << swp32.byteWord().toHex();
                break;
            } else if((!swp33.isNull()
                    && (swp33.cdate() > swp32.cdate()))
                   && (0 == swp33.isReady()
                    || 1 == swp33.isInOpened()
                    || 1 == swp33.isWasOpened()
                    || 1 == swp33.y(y4).isInAlarm()
                    || 1 == swp33.y(y4).isWasAlarm())) {
                getUnReciver()->setDkStatus(DKCiclStatus::DKWrong);
                qDebug() << "DKCiclStatus::DKWrong 33 " << swp33.byteWord().toHex();
                break;
            } else {
                getUnReciver()->setDkStatus(DKCiclStatus::DKReady);
            }
        }

        addLsTrackedUN(getUnReciver());
        getUnReciver()->setIsAutoDkInvolved(isAuto);
        getUnReciver()->setDkInvolved(true);
    } else if(TypeUnitNodeEnum::BOD_SOTA == getUnReciver()->getType()) {
        const auto& swp32 = getUnReciver()->swpT4KBODType0x32();
        const auto& swp33 = getUnReciver()->swpT4KBODType0x32();

        for(const auto &y4 : {1,2,3,4}) {
            if(swp32.isNull()
            && swp32.isNull()) {
                getUnReciver()->setDkStatus(DKCiclStatus::DKWrong);
                qDebug() << "DKCiclStatus::DKWrong ";
                break;
            } else if((!swp32.isNull()
                    && (swp32.cdate() > swp33.cdate()))
                   && (0 == swp32.isReady()
                     || 1 == swp32.isInOpened()
                     || 1 == swp32.isWasOpened()
                     || 1 == swp32.y(y4).isInAlarm()
                     || 1 == swp32.y(y4).isWasAlarm())) {
                getUnReciver()->setDkStatus(DKCiclStatus::DKWrong);
                qDebug() << "DKCiclStatus::DKWrong 32 " << swp32.byteWord().toHex();
                break;
            } else if((!swp33.isNull()
                    && (swp33.cdate() > swp32.cdate()))
                   && (0 == swp33.isReady()
                    || 1 == swp33.isInOpened()
                    || 1 == swp33.isWasOpened()
                    || 1 == swp33.y(y4).isInAlarm()
                    || 1 == swp33.y(y4).isWasAlarm())) {
                getUnReciver()->setDkStatus(DKCiclStatus::DKWrong);
                qDebug() << "DKCiclStatus::DKWrong 33 " << swp33.byteWord().toHex();
                break;
            } else {
                getUnReciver()->setDkStatus(DKCiclStatus::DKReady);
            }
        }

        addLsTrackedUN(getUnReciver());
        getUnReciver()->setIsAutoDkInvolved(isAuto);
        getUnReciver()->setDkInvolved(true);
    }

    setTimeIntervalWaiteFirst(20'000);
    setTimeIntervalRequest(500);

    connect(this, SIGNAL(importantBeatStatus()), &SignalSlotCommutator::instance(), SLOT(emitEndDKWait()));

    auto msMsgDK = QSharedPointer<ManagerSingleMsg>::create(getUnReciver(),
                                                          DataQueueItem::makeDK0x21);
    auto reject = [un = getUnTarget()](){
        if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
            JourEntity msg;
            msg.setObject(un->getName());
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setD4(un->getOutType());
            msg.setDirection(un->getDirection());
            msg.setType(13);
            msg.setComment(tr("Ком. упр. не выполнена"));
            msg.setParams(un->makeJson());
            SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(un, msg);
        }
        if(10 != un->getPublishedState()) {
            un->setPublishedState(13);
            un->updDoubl();
        }
        /* всегда без окон сообщений*/
//        if(!isAuto)
//            MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
////                                            MessageBoxServer::infoErrorExecutingTheDKCommand();
    };
    setManagerFirstMsg(msMsgDK);
    getManagerFirstMsg()->setReject(reject);

    auto msMsgAR = QSharedPointer<ManagerSingleMsg>::create(getUnReciver(),
                                                          DataQueueItem::makeResetFlags0x24);
    setManagerSecondMsg(msMsgAR);
    getManagerSecondMsg()->setReject(reject);
}
