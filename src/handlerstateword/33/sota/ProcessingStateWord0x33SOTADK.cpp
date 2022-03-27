#include "ProcessingStateWord0x33SOTADK.h"

#include "UnitNode.h"
#include "UnitNodeFactory.h"
#include "swpsota/SWPSOTABODType0x33.h"
#include "swpsota/SWPSOTAY4Type0x33.h"
#include "ContainerRequesters.h"
#include "global.h"
#include "ProcessDKWaiter.h"
#include "TopologyService.h"
#include "SignalSlotCommutator.h"
#include "GraphTerminal.h"
#include "SoundAdjuster.h"

ProcessingStateWord0x33SOTADK::ProcessingStateWord0x33SOTADK(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x33SOTADK::~ProcessingStateWord0x33SOTADK()
{

}

bool ProcessingStateWord0x33SOTADK::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
    if(!currentUN->getDkInvolved()
    || TypeUnitNodeEnum::BOD_SOTA == currentUN->getType()) {
        return false;
    }

    const auto& reciverBOD = TopologyService::findReciver(currentUN);
    if(reciverBOD.isNull()) {
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procSOTAY4StatusWord0x33(2) <--";

        return false;
    }

    const auto& isAutoDK = currentUN->getIsAutoDkInvolved();

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x33u, data);
    reciverBOD->setStateWord(0x33u, data);

    const auto &swpCurrent = currentUN->swpSOTABODType0x33();

    if(0 == swpCurrent.isReady()
    || 1 == swpCurrent.isInOpened()
    || 1 == swpCurrent.isWasOpened()

//    || 1 == swpCurrent.y(1).isInAlarm()
//    || 1 == swpCurrent.y(1).isWasAlarm()

//    || 1 == swpCurrent.y(2).isInAlarm()
//    || 1 == swpCurrent.y(2).isWasAlarm()

//    || 1 == swpCurrent.y(3).isInAlarm()
//    || 1 == swpCurrent.y(3).isWasAlarm()

//    || 1 == swpCurrent.y(4).isInAlarm()
//    || 1 == swpCurrent.y(4).isWasAlarm()
      ) { // ДК уже никогда не выполнить
        for(const auto& ar : as_const(ContainerRequesters::getLsWaiter())) {
            if(RequesterType::DKWaiter == ar->getRequesterType()) {
                auto dwWaiter = ar.dynamicCast<ProcessDKWaiter>();
                if(dwWaiter->getLsTrackedUN().contains(currentUN)) {
                    finishDKWaiter(dwWaiter);
//                    qDebug() << "PortManager::procDkStatusWord0x31 remove dwWaiter";
                    break;
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
//                         qDebug() << "PortManager::removeLsTrackedUN(" << currentUN->toString() << ")";
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
                currentUN->done=true;
                SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
            }

            GraphTerminal::sendAbonentEventsAndStates(currentUN);
        }
    }
    if(0 == swpCurrent.isReady()
    || 1 == swpCurrent.isInOpened()
    || 1 == swpCurrent.isWasOpened()

    || 1 == swpCurrent.y(1).isInAlarm()
    || 1 == swpCurrent.y(1).isWasAlarm()

    || 1 == swpCurrent.y(2).isInAlarm()
    || 1 == swpCurrent.y(2).isWasAlarm()

    || 1 == swpCurrent.y(3).isInAlarm()
    || 1 == swpCurrent.y(3).isWasAlarm()

    || 1 == swpCurrent.y(4).isInAlarm()
    || 1 == swpCurrent.y(4).isWasAlarm()) {
        //нужен сброс
        auto reciver = TopologyService::findReciver(currentUN);
        if(reciver.isNull()) {
            auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                                  DataQueueItem::makeResetFlags0x24);
            reciver->pushBackUniqManagerSingleMsg(msMsg);
//            qDebug() << "PortManager::procDkStatusWord0x31 -- DataQueueItem::fillResetFlags0x24(" << resetFlags0x24.data().toHex() << ", " << currentUN->toString() << ");";
        }
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    return true;}

void ProcessingStateWord0x33SOTADK::finishDKWaiter(QSharedPointer<AbstractRequester> ar) const {
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

void ProcessingStateWord0x33SOTADK::procDK(const QSharedPointer<UnitNode> &current, const QSharedPointer<UnitNode> &previous) const {
//    qDebug() << "DkStatus --> " << current->toString();
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
//        qDebug() << "DkStatus -- unCalcDkStatus " << mapDKCiclStatus.value(unCalcDkStatus);
//        qDebug() << "DkStatus -- unDkStatus " << mapDKCiclStatus.value(current->getDkStatus());
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
//    qDebug() << "DkStatus -- unNewDkStatus " << mapDKCiclStatus.value(current->getDkStatus());
//    qDebug() << "DkStatus <--";
}

