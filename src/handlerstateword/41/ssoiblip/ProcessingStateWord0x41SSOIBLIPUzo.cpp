#include "ProcessingStateWord0x41SSOIBLIPUzo.h"

#include <QDebug>
#include "JourEntity.h"
#include "UnitNode.h"
#include "TopologyService.h"
#include "global.h"
#include "swpssoiblip/SWPSSOIBLIPType0x41.h"
#include "swpssoiblip/SWPSSOISDBLIPType0x41.h"
#include "swpssoiblip/SWPSSOIIUBLIPType0x41.h"
#include "UnitNodeFactory.h"
#include "SignalSlotCommutator.h"
#include "DataQueueItem.h"
#include "DataBaseManager.h"
#include "GraphTerminal.h"
#include "SoundAdjuster.h"
#include "MessageBoxServer.h"
#include "AbstractRequester.h"
#include "ContainerRequesters.h"

ProcessingStateWord0x41SSOIBLIPUzo::ProcessingStateWord0x41SSOIBLIPUzo(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x41SSOIBLIPUzo::~ProcessingStateWord0x41SSOIBLIPUzo()
{

}

bool ProcessingStateWord0x41SSOIBLIPUzo::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -->";
    if((TypeUnitNodeEnum::SSOI_SD_BL_IP != currentUN->getType()
     && TypeUnitNodeEnum::SSOI_IU_BL_IP != currentUN->getType())
     || 1 > currentUN->getNum2()
     || 4 < currentUN->getNum2()
     || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(1) <--";
    return false;
    }

    auto reciver = TopologyService::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(2) <--";
        return false;
    }
    reciver->setStateWord(0x41u, data);


    QSharedPointer<UnitNode> previousCopyUNLockSdBlIp, previousCopyUNLockIuBlIp;
    QSharedPointer<UnitNode>  unLockSdBlIp, unLockIuBlIp;
    for(const auto& tmpUN : as_const(reciver->getListChilde())) {
        if(TypeUnitNodeEnum::SSOI_IU_BL_IP == tmpUN->getType()
        && tmpUN->getNum2() == currentUN->getNum2()) {
            previousCopyUNLockIuBlIp = UnitNodeFactory::makeShare(*tmpUN);
            unLockIuBlIp = tmpUN;
            break;
        }
    }

    for(const auto& tmpUN : as_const(reciver->getListChilde())) {
        if(TypeUnitNodeEnum::SSOI_SD_BL_IP == tmpUN->getType()
        && tmpUN->getNum2() == currentUN->getNum2()
        && 0 != tmpUN->getBazalt()) {
            previousCopyUNLockSdBlIp = UnitNodeFactory::makeShare(*tmpUN);
            unLockSdBlIp = tmpUN;
            break;
        }
    }

    if(unLockSdBlIp.isNull()
    || unLockIuBlIp.isNull()) {
//        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(3) <--";
        return false;
    } else if(0 == unLockSdBlIp->getBazalt()) {
//        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(4) <--";
        return false;
    }

    unLockSdBlIp->setStateWord(0x41u, data);
    unLockIuBlIp->setStateWord(0x41u, data);
    if(reciver->getDkInvolved()) {
//        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(2.1) <--";
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();
        return false;
    }

    const auto& swpCurrentBLIP = unLockSdBlIp->swpSSOIBLIPType0x41();
    const auto& swpPreviousBLIP = previousCopyUNLockSdBlIp->swpSSOIBLIPType0x41();
    if(1 == swpCurrentBLIP.isWasDK()
    || 1 == swpPreviousBLIP.isWasDK()) {
        {
            auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                                  DataQueueItem::makeResetFlags0x24);
            reciver->pushBackUniqManagerSingleMsg(msMsg);
        }
//        qDebug() << "PortManager::procUzoBLIPStatusWord0x41(5) <--";
        return true;
    }

    const auto& swpCurrentSD = unLockSdBlIp->swpSSOISDBLIPType0x41(),
               &swpPreviousSD = previousCopyUNLockSdBlIp->swpSSOISDBLIPType0x41();
    const auto& swpCurrentIU = unLockIuBlIp->swpSSOIIUBLIPType0x41(),
               &swpPreviousIU = previousCopyUNLockIuBlIp->swpSSOIIUBLIPType0x41();

    auto isChangedStatus = false;
    if(swpCurrentSD.isInAlarm() != swpPreviousSD.isInAlarm()
    || swpCurrentIU.isOff() != swpPreviousIU.isOff()
    || swpCurrentSD.isInNorm() != swpPreviousSD.isInNorm()
    || swpCurrentIU.isOn() != swpPreviousIU.isOn()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }

//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -- isChangedStatus " << isChangedStatus;

    // проверка на запрещённые переходы состояний -->
    auto isForbiddenTransferStatusForReaction = false;
    if(
            (1 == swpPreviousSD.isInAlarm()
          && 1 == swpPreviousIU.isOn()  //Открыто
          && 1 == swpCurrentSD.isInAlarm()
          && 1 == swpCurrentIU.isOff())  //Открыто ключом

         || (1 == swpPreviousSD.isInNorm()
          && 1 == swpPreviousIU.isOff()  //Закрыто
          && 1 == swpCurrentSD.isInNorm()
          && 1 == swpCurrentIU.isOn())) //Закрыто ключом
    { // запрещённая обработка перехода
      // (Открыто -> Открыто ключом, Закрыто -> Закрыто ключом)
        isForbiddenTransferStatusForReaction = true;
    }
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -- isForbiddenTransferStatusForReaction " << isForbiddenTransferStatusForReaction;

    // переводим на другой шаг обработчик открытия и закрытия этого УЗ или определяем под управлением ли оно -->
    bool isGovernedBy = false;
    QPair<QString, QString> tmpPair(reciver->getUdpAdress(), QString::number(reciver->getUdpPort()));
    for(auto ar : as_const(ContainerRequesters::getLsWaiter())) {
        if(ar->getIpPort() == tmpPair
        && RequesterType::LockRequester == ar->getRequesterType()
        && ar->getUnTarget() == unLockSdBlIp) {

            isGovernedBy = true;

            if(isForbiddenTransferStatusForReaction
            || !isChangedStatus) {
                break;
            }
//            SignalSlotCommutator::emitEndLockWait();
            if(BeatStatus::RequestStep1 == ar->getBeatStatus()) {
//                ar->startSecondRequest();
                continue;
            } else if(BeatStatus::Waite == ar->getBeatStatus()) {
                ar->startSecondRequest();//(3'000);
            } else if(BeatStatus::RequestStep2 == ar->getBeatStatus()) {
//                ar->startEnd();
                continue;
            } else if(BeatStatus::WaiteEnd == ar->getBeatStatus()) {
                  ar->startEnd();
            }
        }
    }
    // переводим на другой шаг обработчик открытия и закрытия этого УЗ или определяем под управлением ли оно <--

    auto isForbiddenTransferStatusForJour = false;
    if(
            isForbiddenTransferStatusForReaction

         || (1 == swpPreviousSD.isInAlarm()
          && 1 == swpCurrentSD.isInAlarm()) //Открыто

         || (1 == swpPreviousSD.isInNorm()
          && 1 == swpCurrentSD.isInNorm())  //Закрыто

         || (1 == swpPreviousSD.isInAlarm()
          && 1 == swpPreviousIU.isOff()   //Открыто ключом
          && 1 == swpCurrentSD.isInAlarm()
          && 1 == swpCurrentIU.isOn()) //Открыто

         || (1 == swpPreviousSD.isInNorm()
          && 1 == swpPreviousIU.isOn()  //Закрыто ключом
          && 1 == swpCurrentSD.isInNorm()
          && 1 == swpCurrentIU.isOff())  //Закрыто

         || (1 == swpPreviousSD.isInAlarm()
          && 1 == swpPreviousIU.isOn()  //Открыто
          && 1 == swpCurrentSD.isInAlarm()
          && 1 == swpCurrentIU.isOff())  //Открыто ключом

         || (1 == swpPreviousSD.isInNorm()
          && 1 == swpPreviousIU.isOff()  //Закрыто
          && 1 == swpCurrentSD.isInNorm()
          && 1 == swpCurrentIU.isOn()) //Закрыто ключом
      )
    { // запрещённая запись перехода (Открыто <-> Открыто ключом, Закрыто <-> Закрыто ключом)
        isForbiddenTransferStatusForJour = true;
    }
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -- isForbiddenTransferStatusForJour " << isForbiddenTransferStatusForJour;
    // проверка на запрещённые переходы состояний <--

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState()
    || -1 == reciver->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState()
    || 10 == reciver->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41() -- isWakeUp " << isWakeUp;

    int typeMsg = -1;
    QString commentMsg;

    auto tmpPublishedStateSd = unLockSdBlIp->getPublishedState();
    auto tmpPublishedStateIu = unLockIuBlIp->getPublishedState();
    if(!isGovernedBy
    && 1 == swpCurrentSD.isInAlarm()
    && swpCurrentIU.isOn() == swpPreviousIU.isOn()
    && swpCurrentSD.isInAlarm() != swpPreviousSD.isInAlarm()) {
        //Открыто
        commentMsg = QObject::tr("Открыто ключом");
        typeMsg = 113;
        tmpPublishedStateSd = 113;
        if(1 == swpCurrentIU.isOn()) {
            tmpPublishedStateIu = 101;
        } else if(1 == swpCurrentIU.isOff()) {
            tmpPublishedStateIu = 100;
        }
    } else if(!isGovernedBy
           && 1 == swpCurrentSD.isInNorm()
           && swpCurrentIU.isOn() == swpPreviousIU.isOn()
           && swpCurrentSD.isInAlarm() != swpPreviousSD.isInAlarm()) {
        //Закрыто
        commentMsg = QObject::tr("Закрыто ключом");
        typeMsg = 112;
        tmpPublishedStateSd = 112;
        if(1 == swpCurrentIU.isOn()) {
            tmpPublishedStateIu = 101;
        } else if(1 == swpCurrentIU.isOff()) {
            tmpPublishedStateIu = 100;
        }
    } else if(1 == swpCurrentSD.isInAlarm()
           && 1 == swpCurrentIU.isOn()
           && (swpCurrentSD.isInAlarm() != swpPreviousSD.isInAlarm()
            || swpCurrentIU.isOn() != swpPreviousIU.isOn())) {
        //Открыто
        commentMsg = QObject::tr("Открыто");
        typeMsg = 111;
        tmpPublishedStateSd = 111;
        tmpPublishedStateIu = 101;
    } else if(1 == swpCurrentSD.isInNorm()
           && 1 == swpCurrentIU.isOff()
           && (swpCurrentSD.isInNorm() != swpPreviousSD.isInNorm()
            || swpCurrentIU.isOff() != swpPreviousIU.isOff())) {
        //Закрыто
        commentMsg = QObject::tr("Закрыто");
        typeMsg = 110;
        tmpPublishedStateSd = 110;
        tmpPublishedStateIu = 100;
    }
    unLockSdBlIp->setPublishedState(tmpPublishedStateSd);
    unLockIuBlIp->setPublishedState(tmpPublishedStateIu);

//    qDebug() << "состояние УЗО -->" << commentMsg;
//    qDebug() << "pSD: " << previousCopyUNLockSdBlIp->toString() << swpPreviousSD.byteWord().toHex();
//    qDebug() << "cSD: " << unLockSdBlIp->toString() << swpCurrentSD.byteWord().toHex();
//    qDebug() << "pIU: " << previousCopyUNLockIuBlIp->toString() << swpPreviousIU.byteWord().toHex();
//    qDebug() << "cIU: " << unLockIuBlIp->toString() << swpCurrentIU.byteWord().toHex();
//    qDebug() << "состояние УЗО <--";

    if((isWakeUp
     || isFirstWakeUp
     || !isForbiddenTransferStatusForJour)
    && isChangedStatus
    && -1 != typeMsg) {
        // следует записать сообщение

        unLockSdBlIp->setPublishedState(tmpPublishedStateSd);
        unLockIuBlIp->setPublishedState(tmpPublishedStateIu);

        JourEntity msg;

        // заполняем поля сообщения за отправителя
        const auto& sendetMsgUN = ((1 != unLockSdBlIp->getMetaEntity()) ?
                                       unLockSdBlIp :
                                       ((1 != unLockIuBlIp->getMetaEntity()) ?
                                            unLockIuBlIp :
                                            nullptr));

        msg.setObject(sendetMsgUN->getName());
        msg.setObjecttype(sendetMsgUN->getType());
        msg.setD1(sendetMsgUN->getNum1());
        msg.setD2(sendetMsgUN->getNum2());
        msg.setD3(sendetMsgUN->getNum3());
        msg.setD4(sendetMsgUN->getOutType());
        msg.setDirection(sendetMsgUN->getDirection());
        msg.setComment(commentMsg);
        msg.setType(typeMsg);
        msg.setParams(sendetMsgUN->makeJson());
                currentUN->done=true;
        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(sendetMsgUN, msg);
        if(113 == msg.getType()) {
            SoundAdjuster::playAlarm();
        }
    }

    unLockSdBlIp->updDoubl();
    unLockIuBlIp->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    if(1 == swpCurrentSD.isWasAlarm()
    || 1 == swpCurrentSD.isWasOpened()) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciver->pushBackUniqManagerSingleMsg(msMsg);
    }

    unLockSdBlIp->callUpdateStateConditionReactor();
//    qDebug() << "PortManager::procUzoBLIPStatusWord0x41(5) <--";
    return true;
}
