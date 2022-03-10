#include "ProcessingStateWord0x32TG.h"

#include "UnitNode.h"
#include "UnitNodeFactory.h"
#include "swptg/SWPTGType0x32.h"
#include "swptg/SWPTGSubType0x32.h"
#include "global.h"
#include "DataBaseManager.h"
#include "TopologyService.h"
#include "SignalSlotCommutator.h"
#include "GraphTerminal.h"
#include "SoundAdjuster.h"
#include "MessageBoxServer.h"

ProcessingStateWord0x32TG::ProcessingStateWord0x32TG(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x32TG::~ProcessingStateWord0x32TG()
{

}

bool ProcessingStateWord0x32TG::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procTgStatusWord0x32() -->";
    if(TypeUnitNodeEnum::TG != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procTgStatusWord0x32(1) <--";
        return false;
    }

    auto reciver = TopologyService::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procTgStatusWord0x32(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x32u, data);
    reciver->setStateWord(0x32u, data);

    const auto& swpCurrent = currentUN->swpTGType0x32(),
               &swpPrevious = previousUN->swpTGType0x32();
    const auto& swpCurrentCi = swpCurrent.C(currentUN->getNum2()),
               &swpPreviousCi = swpPrevious.C(currentUN->getNum2());

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        {
            auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                                  DataQueueItem::makeResetFlags0x24);
            reciver->pushBackUniqManagerSingleMsg(msMsg);
        }
//        qDebug() << "PortManager::procTgStatusWord0x32(5) <--";
        return true;
    }

    auto isChangedStatus = false;
    if(swpCurrentCi.isInOpened() != swpPreviousCi.isInOpened()
    || swpCurrentCi.isWasOpened() != swpPreviousCi.isWasOpened()
    || swpCurrentCi.isInAlarm() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isOutAlarm() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isSideAlarm() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isFault() != swpPreviousCi.isAlarm()
    || swpCurrentCi.isNorm() != swpPreviousCi.isNorm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x32() -- isChangedStatus " << isChangedStatus;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x32() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x32() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needResetFlags0x24 = false;
//    auto makedResetFlags0x24 = false;
    if(1 == swpCurrentCi.isInAlarm()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpCurrentCi.isSideAlarm()
    || 1 == swpCurrentCi.isWasOpened()) { // сброс тревоги
        needResetFlags0x24 = true;
    }
//    qDebug() << "PortManager::procTgStatusWord0x32 -- needResetFlags0x24" << needResetFlags0x24;
    if(needResetFlags0x24) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciver->pushBackUniqManagerSingleMsg(msMsg);
    }
//    qDebug() << "PortManager::procTgStatusWord0x32 -- makedResetFlags0x24" << makedResetFlags0x24;

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

    bool iniState = false;
    // запись неисправность/вскрытие/тревога/норма TG
    if(1 == swpCurrentCi.isFault()
    && swpCurrentCi.isFault() != swpPreviousCi.isFault()) {
        //сохранение неисправность или Норма
        commentMsg = QObject::tr("Неисправность");
        typeMsg = 12;
        currentUN->setPublishedState(12);
    } else if(1 == swpCurrentCi.isOpened()
           && swpPreviousCi.isOpened() != swpCurrentCi.isOpened()) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-ВСКРЫТИЕ");
        typeMsg = 21;
        currentUN->setPublishedState(21);
    } else if(1 == swpCurrentCi.isAlarm()
           && swpPreviousCi.isAlarm() != swpCurrentCi.isAlarm()) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
    } else if(1 == swpCurrentCi.isNorm()
           && swpPreviousCi.isNorm() != swpCurrentCi.isNorm()
           && 1 != currentUN->getPublishedState()) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
    } else if(1 != swpCurrentCi.isNorm()&&
              (isFirstWakeUp || isWakeUp)) {
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        iniState = true;
    }
    if(isWakeUp || isFirstWakeUp) {
        commentMsg += " (начальное состояние)";
    }

//    qDebug() << "состояние TG -->" << commentMsg;
//    qDebug() << "pTG: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cTG: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние TG <--";

    bool wasSendAbonentEventsAndStates = false || isWakeUp || isFirstWakeUp;
    JourEntity msg = prepareMsg;
    if((isWakeUp ||
        isFirstWakeUp ||
        12 == currentUN->getPublishedState() ||
        20 == currentUN->getPublishedState() ||
        21 == currentUN->getPublishedState() ||
        currentUN->getPublishedState() != previousUN->getPublishedState()) &&
       isChangedStatus &&
       1 != currentUN->getMetaEntity() &&
       -1 != typeMsg &&
       currentUN->getControl()) {
        // следует записать сообщение
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);
                currentUN->done=true;
        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        wasSendAbonentEventsAndStates = false;

        if(20 == typeMsg) {
            SoundAdjuster::playAlarm();
        } else if(12 == typeMsg || 21 == typeMsg) {
            SoundAdjuster::playAlarm2();
        }

        if(1 == currentUN->getAlarmMsgOn() && (12 == msg.getType() || 20 == msg.getType() || 21 == msg.getType() )) {
            MessageBoxServer::showAttentionJourMsg(msg);
        }

    }

    if((21 == typeMsg || 20 == typeMsg) && !iniState && currentUN->getControl()) {
        // тригер на ИУ
        for(const auto& iuun : as_const(TopologyService::getLinkedUI(currentUN))) {
            SignalSlotCommutator::emitAutoOnOffIU(true, false, qSharedPointerCast<UnitNode>(iuun));
        }
        //нужен сброс
    }

    if(wasSendAbonentEventsAndStates) {
        if(1 == swpCurrentCi.isNorm()) {
            commentMsg = QObject::tr("Норма");
            typeMsg = 1;
            currentUN->setPublishedState(1);
            msg.setComment(commentMsg);
            msg.setType(typeMsg);
            GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        }
     }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procTgStatusWord0x32(X) <--";
    return true;
}

