#include "ProcessingStateWord0x32TGDK.h"

#include "UnitNode.h"
#include "UnitNodeFactory.h"
#include "swptg/SWPTGType0x32.h"
#include "swptg/SWPTGSubType0x32.h"
#include "ContainerRequesters.h"
#include "global.h"
#include "ProcessDKWaiter.h"
#include "TopologyService.h"
#include "SignalSlotCommutator.h"
#include "GraphTerminal.h"
#include "SoundAdjuster.h"

ProcessingStateWord0x32TGDK::ProcessingStateWord0x32TGDK(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x32TGDK::~ProcessingStateWord0x32TGDK()
{

}

bool ProcessingStateWord0x32TGDK::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
    if(!currentUN->getDkInvolved()) {
        return false;
    }

    const auto& isAutoDK = currentUN->getIsAutoDkInvolved();

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x32u, data);

//    const auto& swpCurrent = currentUN->swpTGType0x32().C(currentUN->getNum2());

    if((TypeUnitNodeEnum::TG == currentUN->getType()
     && 1 == currentUN->swpTGType0x32().C(currentUN->getNum2()).isFault())) { // ДК уже никогда не выполнить
        for(const auto& ar : as_const(ContainerRequesters::getLsWaiter())) {
             if(RequesterType::DKWaiter == ar->getRequesterType()) {
                 auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                 if(dwWaiter->getLsTrackedUN().contains(currentUN)) {
                     finishDKWaiter(dwWaiter);
                     qDebug() << "PortManager::procDkStatusWord0x32 remove dwWaiter";
                     return true;
                 }
             }
        }
    }


    if(DKCiclStatus::DKDone != currentUN->getDkStatus()) {
        procDK(currentUN, previousUN);
        if(DKCiclStatus::DKDone == currentUN->getDkStatus()) {
            for(const auto& ar : as_const(ContainerRequesters::getLsWaiter())) {
                 if(RequesterType::DKWaiter == ar->getRequesterType()) {
                     auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                     if(dwWaiter->removeLsTrackedUN(currentUN)) {
                         if(0 == dwWaiter->getLsTrackedUN().size()) {
                             ContainerRequesters::removeLsWaiter(dwWaiter);
                             SignalSlotCommutator::emitStopDKWait();
                         }
                         qDebug() << "PortManager::removeLsTrackedUN(" << currentUN->toString() << ")";
                         break;
                     }
                 }
            }
            JourEntity msg;
            msg.setObject(currentUN->getName());
            msg.setObjecttype(currentUN->getType());
            msg.setD1(currentUN->getNum1());
            msg.setD2(currentUN->getNum2());
            msg.setD3(currentUN->getNum3());
            msg.setD4(currentUN->getOutType());
            msg.setDirection(currentUN->getDirection());
            msg.setComment(tr("Ком. ДК выполнена"));
            msg.setType(3);
            msg.setParams(currentUN->makeJson());
            if(!isAutoDK) {
                SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
            }

            GraphTerminal::sendAbonentEventsAndStates(currentUN);
        }
    }
    if((TypeUnitNodeEnum::TG == currentUN->getType()
     && (1 == currentUN->swpTGType0x32().C(currentUN->getNum2()).isInAlarm()
      || 1 == currentUN->swpTGType0x32().C(currentUN->getNum2()).isSideAlarm()
      || 1 == currentUN->swpTGType0x32().C(currentUN->getNum2()).isWasOpened()))) {
        //нужен сброс
        auto reciver = TopologyService::findReciver(currentUN);
        if(reciver.isNull()) {
            auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                                  DataQueueItem::makeResetFlags0x24);
            reciver->pushBackUniqManagerSingleMsg(msMsg);
//            qDebug() << "PortManager::procDkStatusWord0x32 -- DataQueueItem::fillResetFlags0x24(" << resetFlags0x24.data().toHex() << ", " << currentUN->toString() << ");";
        }
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    return true;
}

void ProcessingStateWord0x32TGDK::finishDKWaiter(QSharedPointer<AbstractRequester> ar) const {
    if(RequesterType::DKWaiter == ar->getRequesterType()) {
        for(QSharedPointer<UnitNode>  un : ar.dynamicCast<ProcessDKWaiter>()->getLsTrackedUN()) {

            const auto& isAutoDK = un->getIsAutoDkInvolved();

            JourEntity msg;
            msg.setObject(un->getName());
            msg.setObjecttype(un->getType());
            msg.setD1(un->getNum1());
            msg.setD2(un->getNum2());
            msg.setD3(un->getNum3());
            msg.setD4(un->getOutType());
            msg.setDirection(un->getDirection());
            msg.setParams(un->makeJson());

            bool needSendEventsAndStates = false;
            if(DKCiclStatus::DKDone == un->getDkStatus()) {
                msg.setComment(tr("Ком. ДК выполнена"));
                msg.setType(3);
                if(!un->getName().isEmpty() && 1 != un->getMetaEntity() && !isAutoDK) {
                    DataBaseManager::insertJourMsg_wS(msg);
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                }
                needSendEventsAndStates = true;
            } else {
                QString comment = tr("Ком. ДК не выполнена");
                if(isAutoDK)
                    comment = tr("Ком. ДК (Авто) не выполнена");
                msg.setComment(comment);
                msg.setType(11);
                if(!un->getName().isEmpty() && 1 != un->getMetaEntity()) {
                    DataBaseManager::insertJourMsg_wS(msg);
                    GraphTerminal::sendAbonentEventsAndStates(un, msg);
                    SoundAdjuster::playAlarm2();
                }
            }
            un->setDkInvolved(false);
            un->setDkStatus(DKCiclStatus::DKIgnore);
            un->updDoubl();
            if(needSendEventsAndStates)
                GraphTerminal::sendAbonentEventsAndStates(un);
            TopologyService::systemUnitNodesSetDkInvolvedFalse();
            SignalSlotCommutator::emitUpdUN();
        }
//                                SignalSlotCommutator::getInstance()->emitStopDKWait();
//                                removeLsWaiter(ar);
    } else if(RequesterType::LockRequester == ar->getRequesterType()){

        if(RequesterType::LockRequester == ar->getRequesterType()) {
        }

        ar->startWaiteEndSecondWaite();
    }

    if(RequesterType::LockRequester != ar->getRequesterType()) {
        if(RequesterType::DKWaiter == ar->getRequesterType()) {
            SignalSlotCommutator::emitStopDKWait();
        }
        ContainerRequesters::removeLsWaiter(ar);
    }
}

void ProcessingStateWord0x32TGDK::procDK(const QSharedPointer<UnitNode> &current, const QSharedPointer<UnitNode> &previous) const {
    qDebug() << "DkStatus --> " << current->toString();
    if(current.isNull() || previous.isNull())
        return;

    QMap<int, QString> mapDKCiclStatus = {
        {0,"DKIgnore"},
        {1,"DKReady"},
        {2,"DKNorm"},
        {3,"DKWasAlarn"},
        {4,"DKWas"},
        {5,"DKDone"},
        {-1,"DKWrong"}
    };

    if(DKCiclStatus::DKIgnore != previous->getDkStatus() &&
       DKCiclStatus::DKWrong != previous->getDkStatus() &&
       DKCiclStatus::DKDone != previous->getDkStatus() &&
       current->getDkInvolved()) {
        int unCalcDkStatus = current->calcDKStatus();
        qDebug() << "DkStatus -- unCalcDkStatus " << mapDKCiclStatus.value(unCalcDkStatus);
        qDebug() << "DkStatus -- unDkStatus " << mapDKCiclStatus.value(current->getDkStatus());
        if(DKCiclStatus::DKReady == previous->getDkStatus() &&
                DKCiclStatus::DKNorm == unCalcDkStatus) {
            current->setDkStatus(DKCiclStatus::DKNorm);
        } else if((DKCiclStatus::DKNorm == previous->getDkStatus() || DKCiclStatus::DKReady == previous->getDkStatus())&&
                DKCiclStatus::DKWasAlarm == unCalcDkStatus) {
            current->setDkStatus(DKCiclStatus::DKWasAlarm);
        } else if(DKCiclStatus::DKWasAlarm == previous->getDkStatus() &&
                DKCiclStatus::DKNorm == unCalcDkStatus) {
            current->setDkStatus(DKCiclStatus::DKDone);
        } else if(DKCiclStatus::DKWasAlarm == previous->getDkStatus() &&
                DKCiclStatus::DKWas == unCalcDkStatus) {
            current->setDkStatus(DKCiclStatus::DKDone);
        } else if((DKCiclStatus::DKNorm == previous->getDkStatus() &&
                 DKCiclStatus::DKNorm == unCalcDkStatus) ||
                (DKCiclStatus::DKWasAlarm == previous->getDkStatus() &&
                 DKCiclStatus::DKWasAlarm == unCalcDkStatus)) {
            current->setDkStatus(previous->getDkStatus());
        } else {
            current->setDkStatus(DKCiclStatus::DKWrong);
        }
        current->updDoubl();
    }
    qDebug() << "DkStatus -- unNewDkStatus " << mapDKCiclStatus.value(current->getDkStatus());
    qDebug() << "DkStatus <--";
}

