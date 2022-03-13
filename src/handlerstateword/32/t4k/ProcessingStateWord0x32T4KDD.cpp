#include "ProcessingStateWord0x32T4KDD.h"

#include "UnitNode.h"
#include "UnitNodeFactory.h"
#include "swpt4k/SWPT4KBODType0x32.h"
#include "swpt4k/SWPT4KY4Type0x32.h"
#include "swpt4k/SWPT4KDDType0x32.h"
#include "swpt4k/SWPT4KDDCType0x32.h"
#include "global.h"
#include "DataBaseManager.h"
#include "TopologyService.h"
#include "SignalSlotCommutator.h"
#include "GraphTerminal.h"
#include "SoundAdjuster.h"
#include "MessageBoxServer.h"

ProcessingStateWord0x32T4KDD::ProcessingStateWord0x32T4KDD(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x32T4KDD::~ProcessingStateWord0x32T4KDD()
{

}

bool ProcessingStateWord0x32T4KDD::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
    if(TypeUnitNodeEnum::DD_T4K_M != currentUN->getType()
    || currentUN->getDkInvolved()) {
        return false;
    }

//    qDebug() << "ProcessingStateWord0x32T4KDD::processing() -->";

    const auto& reciverBOD = TopologyService::findReciver(currentUN);
    if(reciverBOD.isNull()) {

//        qDebug() << "ProcessingStateWord0x32T4KDD::processing(3) <--";

        return false;
    }

    const auto& reciverY4 = TopologyService::findParentByType(TypeUnitNodeEnum::Y4_T4K_M, currentUN);
    if(reciverY4.isNull()) {

//        qDebug() << "ProcessingStateWord0x32T4KDD::processing(31) <--";

        return false;
    }
    if(TypeUnitNodeEnum::Y4_T4K_M != reciverY4->getType()) {

//        qDebug() << "ProcessingStateWord0x32T4KDD::processing(32) <--";

        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x32u, data);
    reciverBOD->setStateWord(0x32u, data);

    const auto& swpCurrent = currentUN->swpT4KBODType0x32(),
               &swpPrevious = previousUN->swpT4KBODType0x32();

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciverBOD->pushBackUniqManagerSingleMsg(msMsg);

        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "ProcessingStateWord0x32T4KDD::processing(4) <--";
        return true;
    }

    auto y4 = currentUN->getNum2() / 100;

    auto ddNum = currentUN->getNum2() % 100;

    auto isChangedStatus = false;
    if(swpCurrent.y(y4).dd(ddNum).isInOpened() != swpPrevious.y(y4).dd(ddNum).isInOpened()
    || swpCurrent.y(y4).dd(ddNum).isWasOpened() != swpPrevious.y(y4).dd(ddNum).isWasOpened()
    || swpCurrent.y(y4).dd(ddNum).isInCommunicationBreak() != swpPrevious.y(y4).dd(ddNum).isInCommunicationBreak()
    || swpCurrent.y(y4).dd(ddNum).isWasCommunicationBreak() != swpPrevious.y(y4).dd(ddNum).isWasCommunicationBreak()
    || swpCurrent.y(y4).dd(ddNum).c(1).isFault() != swpPrevious.y(y4).dd(ddNum).c(1).isFault()
    || swpCurrent.y(y4).dd(ddNum).c(1).isWasAlarm() != swpPrevious.y(y4).dd(ddNum).c(1).isWasAlarm()
    || swpCurrent.y(y4).dd(ddNum).c(2).isFault() != swpPrevious.y(y4).dd(ddNum).c(2).isFault()
    || swpCurrent.y(y4).dd(ddNum).c(2).isWasAlarm() != swpPrevious.y(y4).dd(ddNum).c(2).isWasAlarm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "ProcessingStateWord0x32T4KDD::processing() -- isChangedStatus " << isChangedStatus;

    auto isChangedStatusC1 = false;
    if(swpCurrent.y(y4).dd(ddNum).c(1).isFault() != swpPrevious.y(y4).dd(ddNum).c(1).isFault()
    || swpCurrent.y(y4).dd(ddNum).c(1).isWasAlarm() != swpPrevious.y(y4).dd(ddNum).c(1).isWasAlarm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatusC1 = true;
    }
//    qDebug() << "ProcessingStateWord0x32T4KDD::processing() -- isChangedStatus " << isChangedStatus;

    auto isChangedStatusC2 = false;
    if(swpCurrent.y(y4).dd(ddNum).c(2).isFault() != swpPrevious.y(y4).dd(ddNum).c(2).isFault()
    || swpCurrent.y(y4).dd(ddNum).c(2).isWasAlarm() != swpPrevious.y(y4).dd(ddNum).c(2).isWasAlarm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatusC2 = true;
    }
//    qDebug() << "ProcessingStateWord0x32T4KDD::processing() -- isChangedStatus " << isChangedStatus;


    auto isSwitchReady = false;
    if(1 == swpCurrent.isReady()
    && swpCurrent.isReady() != swpPrevious.isReady()) {
        // состояние не зменилось - что-то пропускаем
        isSwitchReady = true;
    }
//    qDebug() << "ProcessingStateWord0x32T4KDD::processing() -- isSwitchReady " << isSwitchReady;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState() || -1 == reciverBOD->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "ProcessingStateWord0x32T4KDD::processing() -- isFirstWakeUp " << isFirstWakeUp;


    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciverBOD->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "ProcessingStateWord0x32T4KDD::processing() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needResetFlags0x24 = false;
    auto makedResetFlags0x24 = false;
    Q_UNUSED(makedResetFlags0x24)
    if(1 == swpCurrent.isReady()
    && (1 == swpCurrent.y(y4).dd(ddNum).isWasOpened()
     || 1 == swpCurrent.y(y4).dd(ddNum).isWasCommunicationBreak()
     || 1 == swpCurrent.y(y4).dd(ddNum).c(1).isFault()
     || 1 == swpCurrent.y(y4).dd(ddNum).c(1).isWasAlarm()
     || 1 == swpCurrent.y(y4).dd(ddNum).c(2).isFault()
     || 1 == swpCurrent.y(y4).dd(ddNum).c(2).isWasAlarm())) { // сброс тревоги
        needResetFlags0x24 = true;
    }
//    qDebug() << "ProcessingStateWord0x32T4KDD::processing() -- needResetFlags0x24" << needResetFlags0x24;
    if(needResetFlags0x24) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciverBOD->pushBackUniqManagerSingleMsg(msMsg);
    }
//    qDebug() << "ProcessingStateWord0x32T4KDD::processing() -- makedResetFlags0x24" << makedResetFlags0x24;

    JourEntity prepareMsg;
    // заполняем поля сообщения за отправителя
    prepareMsg.setObject(currentUN->getName());
    prepareMsg.setObjecttype(currentUN->getType());
    prepareMsg.setD1(currentUN->getNum1());
    prepareMsg.setD2(currentUN->getNum2());
    prepareMsg.setD3(currentUN->getNum3());
    prepareMsg.setD4(currentUN->getOutType());
    prepareMsg.setDirection(currentUN->getDirection());
    prepareMsg.setParams(currentUN->makeJson());

    int typeMsg = -1;
    QString commentMsg;

//    qDebug() << "состояние T4KM_DD -->" << commentMsg;
//    qDebug() << "pT4KM_DD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cT4KM_DD: " << currentUN->toString() << swpCurrent.byteWord().toHex();

    if(1 == swpCurrent.isReady()
    && 1 == swpCurrent.y(y4).dd(ddNum).isWasOpened()
    && (swpCurrent.y(y4).dd(ddNum).isWasOpened() == swpPrevious.y(y4).dd(ddNum).isWasOpened()
     || isSwitchReady)) {
        commentMsg = QObject::tr("Тревога - Вскрытие");
        typeMsg = 21;
        currentUN->setPublishedState(21);

        reciverBOD->setClearedAlarm(21);
        reciverY4->setClearedAlarm(21);
//    } else if(1 == swpCurrent.isReady()
//           && 1 == swpCurrent.y(y4).dd(ddNum).isWasCommunicationBreak()
//           && (swpCurrent.y(y4).dd(ddNum).isWasCommunicationBreak() == swpPrevious.y(y4).dd(ddNum).isWasCommunicationBreak()
//            || isSwitchReady)) {
//        commentMsg = QObject::tr("Обрыв связи");
//        typeMsg = 12;
//        currentUN->setPublishedState(12);
    } else if(1 == swpCurrent.isReady()
           || isSwitchReady) {
        //    bool iniState = false;
            // запись тревога/норма/неисправность ЧЭ1 -->

        int typeMsgC1 = -1;
        QString commentMsgC1;
            if(1 == swpCurrent.isReady()
            && 1 == swpCurrent.y(y4).dd(ddNum).c(1).isFault()) {
                commentMsgC1 = QObject::tr("Неисправность по ЧЭ1");
                typeMsgC1 = 12;
                currentUN->setPublishedState(12);

                reciverBOD->setClearedAlarm(12);
                reciverY4->setClearedAlarm(12);
            } else if(1 == swpCurrent.isReady()
                   && 0 == swpCurrent.y(y4).dd(ddNum).c(1).isFault()
                   && 1 == swpCurrent.y(y4).dd(ddNum).c(1).isWasAlarm()) {
                commentMsgC1 = QObject::tr("Тревога - Сработка по ЧЭ1");
                typeMsgC1 = 22;
                currentUN->setPublishedState(22);

                reciverBOD->setClearedAlarm(22);
                reciverY4->setClearedAlarm(22);
            } else if(1 == swpCurrent.isReady()
                   && 0 == swpCurrent.y(y4).dd(ddNum).c(1).isFault()
                   && 0 == swpCurrent.y(y4).dd(ddNum).c(1).isWasAlarm()) {
                commentMsgC1 = QObject::tr("Норма по ЧЭ1");
                typeMsgC1 = 5;
                currentUN->setPublishedState(5);
            }
            if(isWakeUp || isFirstWakeUp) {
                commentMsgC1 += " (начальное состояние)";
            }

            bool wasSendAbonentEventsAndStates = false || isWakeUp || isFirstWakeUp;
            Q_UNUSED(wasSendAbonentEventsAndStates)
            if((isWakeUp
             || isFirstWakeUp
             || isSwitchReady
             || 12 == currentUN->getPublishedState()
             || 22 == currentUN->getPublishedState()
             || currentUN->getPublishedState() != previousUN->getPublishedState())
            && (isChangedStatusC1
             || isSwitchReady)
            && 1 != currentUN->getMetaEntity()
            && -1 != typeMsgC1
            && 5 != typeMsgC1
            && currentUN->getControl()) {
                JourEntity msg = prepareMsg;
                // следует записать сообщение
                // заполняем поля сообщения
                currentUN->done=true;
                msg.setComment(commentMsgC1);
                msg.setType(typeMsgC1);

                SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
                wasSendAbonentEventsAndStates = false;

                if(22 == typeMsgC1) {
                    SoundAdjuster::playAlarm();
                }

                if(1 == currentUN->getAlarmMsgOn() && (12 == msg.getType() || 22 == msg.getType())) {
                    MessageBoxServer::showAttentionJourMsg(msg);
                }

            }

            // запись тревога/норма/неисправность ЧЭ1 <--

            // запись тревога/норма/неисправность ЧЭ2 -->
            int typeMsgC2 = -1;
            QString commentMsgC2 = "";
            if(1 == swpCurrent.isReady()
            && 1 == swpCurrent.y(y4).dd(ddNum).c(2).isFault()) {
                commentMsgC2 = QObject::tr("Неисправность по ЧЭ2");
                typeMsgC2 = 13;
                currentUN->setPublishedState(13);

                reciverBOD->setClearedAlarm(13);
                reciverY4->setClearedAlarm(13);
            } else if(1 == swpCurrent.isReady()
                   && 0 == swpCurrent.y(y4).dd(ddNum).c(2).isFault()
                   && 1 == swpCurrent.y(y4).dd(ddNum).c(2).isWasAlarm()) {
                commentMsgC2 = QObject::tr("Тревога - Сработка по ЧЭ2");
                typeMsgC2 = 23;
                currentUN->setPublishedState(23);

                reciverBOD->setClearedAlarm(23);
                reciverY4->setClearedAlarm(23);
            } else if(1 == swpCurrent.isReady()
                   && 0 == swpCurrent.y(y4).dd(ddNum).c(2).isFault()
                   && 0 == swpCurrent.y(y4).dd(ddNum).c(2).isWasAlarm()) {
                commentMsgC2 = QObject::tr("Норма по ЧЭ2");
                typeMsgC2 = 6;
                currentUN->setPublishedState(6);
            }
            if(isWakeUp || isFirstWakeUp) {
                commentMsgC2 += " (начальное состояние)";
            }

            wasSendAbonentEventsAndStates = false || isWakeUp || isFirstWakeUp;
            if((isWakeUp
             || isFirstWakeUp
             || isSwitchReady
             || 13 == currentUN->getPublishedState()
             || 23 == currentUN->getPublishedState()
             || currentUN->getPublishedState() != previousUN->getPublishedState())
            && (isChangedStatusC2
             || isSwitchReady)
            && 1 != currentUN->getMetaEntity()
            && -1 != typeMsgC2
            && 6 != typeMsgC2
            && currentUN->getControl()) {
                JourEntity msg = prepareMsg;
                // следует записать сообщение
                // заполняем поля сообщения
                currentUN->done=true;
                msg.setComment(commentMsgC2);
                msg.setType(typeMsgC2);

                SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
                wasSendAbonentEventsAndStates = false;

                if(23 == typeMsgC2) {
                    SoundAdjuster::playAlarm();
                }

                if(1 == currentUN->getAlarmMsgOn() && (13 == msg.getType() || 23 == msg.getType())) {
                    MessageBoxServer::showAttentionJourMsg(msg);
                }
            }
            // запись тревога/норма/неисправность ЧЭ2 <--

            if(5 == typeMsgC1
            && 6 == typeMsgC2) {
                commentMsg = QObject::tr("Норма");
                typeMsg = 1;
            }
    } else if(0 == swpCurrent.isReady()) {
        commentMsg = QObject::tr("Неопределенное состояние");
        typeMsg = 0;
        currentUN->setPublishedState(0);
    }
    if(isWakeUp || isFirstWakeUp) {
        commentMsg += " (начальное состояние)";
    }

    bool wasSendAbonentEventsAndStates = false || isWakeUp || isFirstWakeUp;
    Q_UNUSED(wasSendAbonentEventsAndStates)
    if((isWakeUp
     || isFirstWakeUp
     || isSwitchReady
     || 12 == currentUN->getPublishedState()
     || 22 == currentUN->getPublishedState()
     || currentUN->getPublishedState() != previousUN->getPublishedState())
    && (isChangedStatus
     || isSwitchReady)
    && 1 != currentUN->getMetaEntity()
    && -1 != typeMsg
    && currentUN->getControl()) {
        JourEntity msg = prepareMsg;
        // следует записать сообщение
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        wasSendAbonentEventsAndStates = false;

        if(22 == typeMsg) {
            SoundAdjuster::playAlarm();
        }

        if(1 == currentUN->getAlarmMsgOn() && (12 == msg.getType() || 22 == msg.getType())) {
            MessageBoxServer::showAttentionJourMsg(msg);
        }

    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "typeMsg:" << typeMsg << "commentMsg:" << commentMsg;
//    qDebug() << "pT4KM_DD: " << previousUN->toString() << previousUN->getPublishedState();
//    qDebug() << "cT4KM_DD: " << currentUN->toString() << currentUN->getPublishedState();
//    qDebug() << "состояние T4KM_DD <--";

//    qDebug() << "ProcessingStateWord0x32T4KDD::processing(X) <--";
    return true;
}
