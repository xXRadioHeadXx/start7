#include "ProcessingStateWord0x33T4KDD.h"

#include "UnitNode.h"
#include "UnitNodeFactory.h"
#include "swpt4k/SWPT4KBODType0x33.h"
#include "swpt4k/SWPT4KY4Type0x33.h"
#include "swpt4k/SWPT4KDDType0x33.h"
#include "swpt4k/SWPT4KDDCType0x33.h"
#include "swpt4k/SWPT4KDDCFType0x33.h"
#include "global.h"
#include "DataBaseManager.h"
#include "TopologyService.h"
#include "SignalSlotCommutator.h"
#include "GraphTerminal.h"
#include "SoundAdjuster.h"
#include "MessageBoxServer.h"

ProcessingStateWord0x33T4KDD::ProcessingStateWord0x33T4KDD(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x33T4KDD::~ProcessingStateWord0x33T4KDD()
{

}

bool ProcessingStateWord0x33T4KDD::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procT4KMDDStatusWord0x33() -->";
    if(TypeUnitNodeEnum::DD_T4K_M != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procT4KMDDStatusWord0x33(1) <--";
        return false;
    }

    const auto& reciverBOD = TopologyService::findReciver(currentUN);
    if(reciverBOD.isNull()) {
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procT4KMDDStatusWord0x33(3) <--";

        return false;
    }

    const auto& reciverY4 = TopologyService::findParentByType(TypeUnitNodeEnum::Y4_T4K_M, currentUN);
    if(reciverY4.isNull()) {
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procT4KMDDStatusWord0x33(31) <--";

        return false;
    }
    if(TypeUnitNodeEnum::Y4_T4K_M != reciverY4->getType()) {
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procT4KMDDStatusWord0x33(32) <--";

        return false;
    }
    auto y4 = currentUN->getNum2() / 100;
    if(y4 > 2 && SWPT4KBODType0x33(data).getY4() < 1) {
//        qDebug() << "PortManager::procT4KMDDStatusWord0x33(32) <--";
        return false;
    }

    auto ddNum = currentUN->getNum2() % 100;
    if(ddNum != SWPT4KBODType0x33(data).getDd()) {
//        qDebug() << "PortManager::procT4KMDDStatusWord0x33(32) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x33u, data);
    reciverBOD->setStateWord(0x33u, data);

    const auto& swpCurrent = currentUN->swpT4KBODType0x33(),
               &swpPrevious = previousUN->swpT4KBODType0x33();

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciverBOD->pushBackUniqManagerSingleMsg(msMsg);

        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procT4KMDDStatusWord0x33(4) <--";
        return true;
    }

    auto isChangedStatus = false;
    if(swpCurrent.dd().isInOpened() != swpPrevious.dd().isInOpened()
    || swpCurrent.dd().isWasOpened() != swpPrevious.dd().isWasOpened()
    || swpCurrent.dd().isInCommunicationBreak() != swpPrevious.dd().isInCommunicationBreak()
    || swpCurrent.dd().isWasCommunicationBreak() != swpPrevious.dd().isWasCommunicationBreak()
    || swpCurrent.dd().isInterrogation() != swpPrevious.dd().isInterrogation()
    || swpCurrent.dd().isFault() != swpPrevious.dd().isFault()

    || swpCurrent.dd().c(1).isWasAlarm() != swpPrevious.dd().c(1).isWasAlarm()
    || swpCurrent.dd().c(1).isCliff() != swpPrevious.dd().c(1).isCliff()
    || swpCurrent.dd().c(1).isClosure() != swpPrevious.dd().c(1).isClosure()

    || swpCurrent.dd().c(1).f(1).isWasAlarm() != swpPrevious.dd().c(1).f(1).isWasAlarm()
    || swpCurrent.dd().c(1).f(2).isWasAlarm() != swpPrevious.dd().c(1).f(2).isWasAlarm()

    || swpCurrent.dd().c(2).isWasAlarm() != swpPrevious.dd().c(2).isWasAlarm()
    || swpCurrent.dd().c(2).isCliff() != swpPrevious.dd().c(2).isCliff()
    || swpCurrent.dd().c(2).isClosure() != swpPrevious.dd().c(2).isClosure()

    || swpCurrent.dd().c(2).f(1).isWasAlarm() != swpPrevious.dd().c(2).f(1).isWasAlarm()
    || swpCurrent.dd().c(2).f(2).isWasAlarm() != swpPrevious.dd().c(2).f(2).isWasAlarm()
      ) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procT4KMDDStatusWord0x33() -- isChangedStatus " << isChangedStatus;

    auto isChangedStatusC1 = false;
    if(swpCurrent.dd().c(1).isWasAlarm() != swpPrevious.dd().c(1).isWasAlarm()
    || swpCurrent.dd().c(1).isCliff() != swpPrevious.dd().c(1).isCliff()
    || swpCurrent.dd().c(1).isClosure() != swpPrevious.dd().c(1).isClosure()

    || swpCurrent.dd().c(1).f(1).isWasAlarm() != swpPrevious.dd().c(1).f(1).isWasAlarm()
    || swpCurrent.dd().c(1).f(2).isWasAlarm() != swpPrevious.dd().c(1).f(2).isWasAlarm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatusC1 = true;
    }
//    qDebug() << "PortManager::procT4KMDDStatusWord0x33() -- isChangedStatus " << isChangedStatus;

    auto isChangedStatusC2 = false;
    if(swpCurrent.dd().c(2).isWasAlarm() != swpPrevious.dd().c(2).isWasAlarm()
    || swpCurrent.dd().c(2).isCliff() != swpPrevious.dd().c(2).isCliff()
    || swpCurrent.dd().c(2).isClosure() != swpPrevious.dd().c(2).isClosure()

    || swpCurrent.dd().c(2).f(1).isWasAlarm() != swpPrevious.dd().c(2).f(1).isWasAlarm()
    || swpCurrent.dd().c(2).f(2).isWasAlarm() != swpPrevious.dd().c(2).f(2).isWasAlarm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatusC2 = true;
    }
//    qDebug() << "PortManager::procT4KMDDStatusWord0x33() -- isChangedStatus " << isChangedStatus;


    auto isSwitchReady = false;
    if(1 == swpCurrent.isReady()
    && swpCurrent.isReady() != swpPrevious.isReady()) {
        // состояние не зменилось - что-то пропускаем
        isSwitchReady = true;
    }
//    qDebug() << "PortManager::procT4KMDDStatusWord0x33() -- isSwitchReady " << isSwitchReady;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState() || -1 == reciverBOD->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procT4KMDDStatusWord0x33() -- isFirstWakeUp " << isFirstWakeUp;


    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciverBOD->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procT4KMDDStatusWord0x33() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needResetFlags0x24 = false;
    auto makedResetFlags0x24 = false;
    Q_UNUSED(makedResetFlags0x24)
    if(1 == swpCurrent.isReady()
    && (1 == swpCurrent.dd().isWasOpened()
     || 1 == swpCurrent.dd().isWasCommunicationBreak()
     || 1 == swpCurrent.dd().isFault()

     || 1 == swpCurrent.dd().c(1).isWasAlarm()
     || 1 == swpCurrent.dd().c(1).isCliff()
     || 1 == swpCurrent.dd().c(1).isClosure()

     || 1 == swpCurrent.dd().c(1).f(1).isWasAlarm()
     || 1 == swpCurrent.dd().c(1).f(2).isWasAlarm()

     || 1 == swpCurrent.dd().c(2).isWasAlarm()
     || 1 == swpCurrent.dd().c(2).isCliff()
     || 1 == swpCurrent.dd().c(2).isClosure()

     || 1 == swpCurrent.dd().c(2).f(1).isWasAlarm()
     || 1 == swpCurrent.dd().c(2).f(2).isWasAlarm())) { // сброс тревоги
        needResetFlags0x24 = true;
    }
//    qDebug() << "PortManager::procT4KMDDStatusWord0x33() -- needResetFlags0x24" << needResetFlags0x24;
    if(needResetFlags0x24) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciverBOD->pushBackUniqManagerSingleMsg(msMsg);
    }
//    qDebug() << "PortManager::procT4KMDDStatusWord0x33() -- makedResetFlags0x24" << makedResetFlags0x24;

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
    && 1 == swpCurrent.dd().isFault()
    && (swpCurrent.dd().isFault() != swpPrevious.dd().isFault()
     || isSwitchReady)) {
        commentMsg = QObject::tr("Неисправность");
        typeMsg = 12;
        currentUN->setPublishedState(12);
        reciverBOD->setClearedAlarm(12);
        reciverY4->setClearedAlarm(12);
    } else if(1 == swpCurrent.isReady()
    && 1 == swpCurrent.dd().isWasOpened()
    && (swpCurrent.dd().isWasOpened() == swpPrevious.dd().isWasOpened()
     || isSwitchReady)) {
        commentMsg = QObject::tr("Тревога - Вскрытие");
        typeMsg = 21;
        currentUN->setPublishedState(21);
        reciverBOD->setClearedAlarm(21);
        reciverY4->setClearedAlarm(21);
    } else if(1 == swpCurrent.isReady()
           && 1 == swpCurrent.dd().isWasCommunicationBreak()
           && (swpCurrent.dd().isWasCommunicationBreak() == swpPrevious.dd().isWasCommunicationBreak()
            || isSwitchReady)) {
        commentMsg = QObject::tr("Обрыв связи");
        typeMsg = 12;
        currentUN->setPublishedState(12);
    } else if(1 == swpCurrent.isReady()
           || isSwitchReady) {
        //    bool iniState = false;
            // запись тревога/норма/неисправность ЧЭ1 -->
            if(1 == swpCurrent.isReady()
                   && 1 == swpCurrent.dd().c(1).isWasAlarm()
                   && (swpCurrent.dd().c(1).isWasAlarm() != swpPrevious.dd().c(1).isWasAlarm()
                    || isSwitchReady)) {
                commentMsg = QObject::tr("Тревога - Сработка по ЧЭ1");
                typeMsg = 22;
                currentUN->setPublishedState(22);

                reciverBOD->setClearedAlarm(22);
                reciverY4->setClearedAlarm(22);
            } else if(1 == swpCurrent.isReady()
                   && 0 == swpCurrent.dd().c(1).isWasAlarm()
                   && (swpCurrent.dd().c(1).isWasAlarm() != swpPrevious.dd().c(1).isWasAlarm()
                    || isSwitchReady)) {
                commentMsg = QObject::tr("Норма по ЧЭ1");
                typeMsg = 5;
                currentUN->setPublishedState(5);
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
            && (isChangedStatusC1
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

            typeMsg = -1;
            commentMsg = "";
            // запись тревога/норма/неисправность ЧЭ1 <--

            // запись тревога/норма/неисправность ЧЭ2 -->
            if(1 == swpCurrent.isReady()
                   && 1 == swpCurrent.dd().c(2).isWasAlarm()
                   && (swpCurrent.dd().c(2).isWasAlarm() != swpPrevious.dd().c(2).isWasAlarm()
                    || isSwitchReady)) {
                commentMsg = QObject::tr("Тревога - Сработка по ЧЭ2");
                typeMsg = 23;
                currentUN->setPublishedState(23);

                reciverBOD->setClearedAlarm(23);
                reciverY4->setClearedAlarm(23);
            } else if(1 == swpCurrent.isReady()
                   && 0 == swpCurrent.dd().c(2).isWasAlarm()
                   && (swpCurrent.dd().c(2).isWasAlarm() != swpPrevious.dd().c(2).isWasAlarm()
                    || isSwitchReady)) {
                commentMsg = QObject::tr("Норма по ЧЭ2");
                typeMsg = 6;
                currentUN->setPublishedState(6);
            }
            if(isWakeUp || isFirstWakeUp) {
                commentMsg += " (начальное состояние)";
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

                if(23 == typeMsg) {
                    SoundAdjuster::playAlarm();
                }

                if(1 == currentUN->getAlarmMsgOn() && (13 == msg.getType() || 23 == msg.getType())) {
                    MessageBoxServer::showAttentionJourMsg(msg);
                }
            }

            typeMsg = -1;
            commentMsg = "";
            // запись тревога/норма/неисправность ЧЭ2 <--
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

//    qDebug() << "PortManager::procT4KMDDStatusWord0x33(X) <--";
    return true;
}
