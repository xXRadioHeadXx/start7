#include "OnOffIUWaiter.h"
#include "SignalSlotCommutator.h"

#include "PortManager.h"
#include "Utils.h"
#include "global.h"
#include "swpblip/SWPIUBLIPType0x41.h"
#include "swpssoiblip/SWPSSOIIUBLIPType0x41.h"

#include <MessageBoxServer.h>
#include "TopologyService.h"

OnOffIUWaiter::OnOffIUWaiter(const bool isAuto, const bool fromAbonent, QSharedPointer<UnitNode>  target, RequesterType requesterType) :
    AbstractRequester(target, requesterType),
    isAuto(isAuto),
    fromAbonent(fromAbonent)
{
//    qDebug() << "OnOffIUWaiter::OnOffIUWaiter(" << this << ") -->";
}

OnOffIUWaiter::~OnOffIUWaiter()
{
//    qDebug() << "OnOffIUWaiter::~OnOffIUWaiter(" << this << ") <--";
}

void OnOffIUWaiter::init()
{
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

    int interval = UnitNodeCFG::adamOffToMs(getUnTarget()->getAdamOff());

    setTimeIntervalWaiteFirst(interval);
    setTimeIntervalRequest(500);

    auto f_jour = [] (const QSharedPointer<UnitNode> &target) {
        JourEntity msg;
        msg.setObject(target->getName());
        msg.setObjecttype(target->getType());
        msg.setD1(target->getNum1());
        msg.setD2(target->getNum2());
        msg.setD3(target->getNum3());
        msg.setType(130);
        msg.setDirection(target->getDirection());
        QString comment;
        comment = tr("Послана ком. Выкл (Авто)");
        msg.setComment(comment);
        msg.setParams(target->makeJson());
        if(!target->getName().isEmpty() && 1 != target->getMetaEntity()) {
            SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
            GraphTerminal::sendAbonentEventsAndStates(target, msg);
        }

        target->setWaitAutoCommand(true);
        target->updDoubl();
    };

    if(TypeUnitNodeEnum::IU_BL_IP == getUnTarget()->getType()) {
        updateStateConditionReactor = [un = getUnTarget(), isAuto = isAuto, fromAbonent = fromAbonent](){
                                                const auto& swpIU = un->swpIUBLIPType0x41();
                                                if(1 == swpIU.isOff()) // выкл
                                                {
                                                    return;
                                                }
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
                                                if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
                                                    MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
                                                }
    //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                            };

    } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == getUnTarget()->getType()) {
        updateStateConditionReactor = [un = getUnTarget(), isAuto = isAuto, fromAbonent = fromAbonent](){
                                                const auto& swpIU = un->swpSSOIIUBLIPType0x41();
                                                if(1 == swpIU.isOff()) // выкл
                                                {
                                                    return;
                                                }
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
                                                if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
                                                    MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
                                                }
    //                                            MessageBoxServer::infoErrorExecutingTheLockOpeningCommand();
                                            };

    }

    setManagerFirstMsg(QSharedPointer<ManagerSingleMsg>::create(getUnTarget(),
                                                                DataQueueItem::makeOn0x23));
    getManagerFirstMsg()->setReject([un = getUnTarget(), isAuto = isAuto, fromAbonent = fromAbonent](){
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
                                            if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
                                                MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
                                            }
//                                            MessageBoxServer::infoErrorExecutingTheOnAutoCommand();
                                        });
    setManagerSecondMsg(QSharedPointer<ManagerSingleMsg>::create(getUnTarget(),
                                                                 DataQueueItem::makeOff0x23,
                                                                 f_jour));
    getManagerSecondMsg()->setReject([un = getUnTarget(), isAuto = isAuto, fromAbonent = fromAbonent](){
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
                                            if((un->getAlarmMsgOn() || (!isAuto && !fromAbonent)) && !(isAuto || fromAbonent)) {
                                                MessageBoxServer::infoTheOperationCannotBePerformedThereIsNoConnectionWithTheSensor(un->getName());
                                            }
//                                            MessageBoxServer::infoErrorExecutingTheOffAutoCommand();
                                         });

}

DataQueueItem OnOffIUWaiter::makeFirstMsg()
{
//    DataQueueItem result;
//    if(nullptr == getPtrPort() || getUnReciver().isNull())
//        return result;

//    result.setData(DataQueueItem::makeOn0x23(getUnTarget()));
//    result.setPort(getUnReciver()->getUdpPort());
//    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
//    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

//    if(!getUnTarget().isNull() && TypeUnitNode::RLM_C == getUnTarget()->getType())
//        result.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));

//    if(result.isValid())
//        return result;

    return DataQueueItem();
}

DataQueueItem OnOffIUWaiter::makeSecondMsg() {
//    DataQueueItem result;
//    if(nullptr == getPtrPort() || getUnReciver().isNull())
//        return result;

//    result.setData(DataQueueItem::makeOff0x23(getUnTarget()));
//    result.setPort(getUnReciver()->getUdpPort());
//    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
//    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

//    if(!getUnTarget().isNull() && TypeUnitNode::RLM_C == getUnTarget()->getType())
//        result.setPreamble(QByteArray().fill(static_cast<uint8_t>(0xFF), 3));

//    if(result.isValid()) {

//        JourEntity msg;
//        msg.setObject(getUnTarget()->getName());
//        msg.setObjecttype(getUnTarget()->getType());
//        msg.setD1(getUnTarget()->getNum1());
//        msg.setD2(getUnTarget()->getNum2());
//        msg.setD3(getUnTarget()->getNum3());
//        msg.setD4(getUnTarget()->getOutType());
//        msg.setType(130);
//        msg.setDirection(getUnTarget()->getDirection());
//        QString comment;
//        comment = tr("Послана ком. Выкл (Авто)");
//        msg.setComment(comment);

//        if(!getUnTarget()->getName().isEmpty() && 1 != getUnTarget()->getMetaEntity()) {
//            SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
//            GraphTerminal::sendAbonentEventsAndStates(getUnTarget(), msg);
//        }

//        getUnTarget()->setWaitAutoCommand(true);
//        getUnTarget()->updDoubl();
//        return result;
//    }

    return DataQueueItem();
}

DataQueueItem OnOffIUWaiter::makeEndMsg()
{
    return DataQueueItem();
}
