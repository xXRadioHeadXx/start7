#include "ProcessingStateWord0x31RLM.h"

#include "DataQueueItem.h"
#include "JourEntity.h"
#include "UnitNode.h"
#include "TopologyService.h"
#include "UnitNodeFactory.h"
#include "swprlm/SWPRLMType0x31.h"
#include "SignalSlotCommutator.h"
#include "DataBaseManager.h"
#include "GraphTerminal.h"
#include "SoundAdjuster.h"
#include "MessageBoxServer.h"
#include "global.h"

ProcessingStateWord0x31RLM::ProcessingStateWord0x31RLM(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x31RLM::~ProcessingStateWord0x31RLM()
{

}

bool ProcessingStateWord0x31RLM::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procRlmStatusWord0x31() -->";
    if(TypeUnitNodeEnum::RLM_KRL != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procRlmStatusWord0x31(1) <--";
        return false;
    }

    auto reciver = TopologyService::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procRlmStatusWord0x31(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x31u, data);
    reciver->setStateWord(0x31u, data);

    const auto& swpCurrent = currentUN->swpRLMType0x31(),
               &swpPrevious = previousUN->swpRLMType0x31();

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        {
            auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                                  DataQueueItem::makeResetFlags0x24);
            reciver->pushBackUniqManagerSingleMsg(msMsg);
        }
//        qDebug() << "PortManager::procRlmStatusWord0x31(5) <--";
        return true;
    }

    auto isChangedStatus = false;
    if(swpCurrent.isFault() != swpPrevious.isFault()
    || swpCurrent.isOpened() != swpPrevious.isOpened()
    || swpCurrent.isWasOpened() != swpPrevious.isWasOpened()
    || swpCurrent.isAlarm() != swpPrevious.isAlarm()
    || swpCurrent.isWasAlarm() != swpPrevious.isWasAlarm() ||
       swpCurrent.isNorm() != swpPrevious.isNorm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31() -- isChangedStatus " << isChangedStatus;

    auto isSwitchOnOff = false;
    if(!swpPrevious.isNull() &&
       (swpCurrent.isOff() != swpPrevious.isOff() ||
        swpCurrent.isOn() != swpPrevious.isOn())) {
        // состояние не зменилось - что-то пропускаем
        isSwitchOnOff = true;
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31() -- isSwitchOnOff " << isSwitchOnOff;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needResetFlags0x24 = false;
//    auto makedResetFlags0x24 = false;
    if(1 == swpCurrent.isOn()
    && (
        1 == currentUN->swpRLMType0x31().isOutAlarm()
     || 1 == currentUN->swpRLMType0x31().isWasDK()
     || 1 == currentUN->swpRLMType0x31().isWasAlarm()
     || 1 == currentUN->swpRLMType0x31().isWasOpened())) { // сброс тревоги
        needResetFlags0x24 = true;
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31 -- needResetFlags0x24" << needResetFlags0x24;
    if(needResetFlags0x24) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciver->pushBackUniqManagerSingleMsg(msMsg);
    }
//    qDebug() << "PortManager::procRlmStatusWord0x31 -- makedResetFlags0x24" << makedResetFlags0x24;

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
    bool needRepeatActualState = false;

    // запись вкл/выкл РЛМ
    if(1 == swpCurrent.isOff()) {
        commentMsg = QObject::tr("Выкл");
        typeMsg = 100;
    } else if(1 == swpCurrent.isOn()) {
        commentMsg = QObject::tr("Вкл");
        typeMsg = 101;
        needRepeatActualState = true;
    }

//    qDebug() << "состояние RLM -->" << commentMsg;
//    qDebug() << "pRLM: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cRLM: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние RLM <--";

    if(isSwitchOnOff && 1 != currentUN->getMetaEntity() && -1 != typeMsg) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);
                currentUN->done=true;
        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg(msg);
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
    } else {
        needRepeatActualState = false;
    }
    typeMsg = -1;

    bool iniState = false;
    // запись тревога/норма РЛМ
    if(1 == swpCurrent.isFault()
    && (swpCurrent.isFault() != swpPrevious.isFault() || needRepeatActualState)) {
        //сохранение неисправность или Норма
        commentMsg = QObject::tr("Неисправность");
        typeMsg = 12;
        currentUN->setPublishedState(12);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isOpened()
           && 1 == swpCurrent.isWasOpened()
           && (swpPrevious.isOpened() != swpCurrent.isOpened()
            || swpPrevious.isWasOpened() != swpCurrent.isWasOpened()
            || needRepeatActualState)) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-ВСКРЫТИЕ");
        typeMsg = 21;
        currentUN->setPublishedState(21);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isAlarm()
           && 1 == swpCurrent.isWasAlarm()
           && (swpPrevious.isAlarm() != swpCurrent.isAlarm()
            || swpPrevious.isWasAlarm() != swpCurrent.isWasAlarm()
            || needRepeatActualState)) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isNorm()
           && ((swpPrevious.isNorm() != swpCurrent.isNorm()
             && 1 != currentUN->getPublishedState()) || needRepeatActualState)) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
    } else if(1 == swpCurrent.isOn() &&
              1 != swpCurrent.isNorm() &&
              (isFirstWakeUp || isWakeUp)) {
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        iniState = true;
    }
    if(isWakeUp || isFirstWakeUp) {
        commentMsg += " (начальное состояние)";
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41 -- iniState" << iniState;

//    qDebug() << "состояние RLM -->" << commentMsg;
//    qDebug() << "pRLM: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cRLM: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние RLM <--";

    bool wasSendAbonentEventsAndStates = false || isWakeUp || isFirstWakeUp;
    JourEntity msg = prepareMsg;
    if((isWakeUp ||
        isFirstWakeUp ||
        12 == currentUN->getPublishedState() ||
        20 == currentUN->getPublishedState() ||
        21 == currentUN->getPublishedState() ||
        currentUN->getPublishedState() != previousUN->getPublishedState() ||
        needRepeatActualState
        ) &&
       (needRepeatActualState || isChangedStatus) &&
       1 != currentUN->getMetaEntity() &&
       -1 != typeMsg &&
       currentUN->getControl()) {
        // следует записать сообщение
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);
                currentUN->done=true;
        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg(msg);
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        wasSendAbonentEventsAndStates = false;

        if(20 == typeMsg && !iniState) {
            SoundAdjuster::playAlarm();
        } else if(12 == typeMsg || 21 == typeMsg) {
            SoundAdjuster::playAlarm2();
        }

        if(1 == currentUN->getAlarmMsgOn() && (12 == msg.getType() || 20 == msg.getType() || 21 == msg.getType() )) {
            MessageBoxServer::showAttentionJourMsg(msg);
        }
    } else if(!isSwitchOnOff && 1 == swpCurrent.isOff()) {
        currentUN->setPublishedState(1);

        if(isWakeUp || isFirstWakeUp) {
            commentMsg = QObject::tr("Выкл (начальное состояние)");
            typeMsg = 100;
            // заполняем поля сообщения
            msg.setComment(commentMsg);
            msg.setType(typeMsg);
                currentUN->done=true;
            SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg(msg);
            GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
            wasSendAbonentEventsAndStates = false;
        }
    }

    if(wasSendAbonentEventsAndStates) {
        if(1 == swpCurrent.isOn()
        && 1 == swpCurrent.isNorm()) {
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

    if((21 == typeMsg || 20 == typeMsg) && !iniState && currentUN->getControl()) {
        // тригер на ИУ
        for(const auto& iuun : as_const(TopologyService::getLinkedUI(currentUN))) {
            SignalSlotCommutator::emitAutoOnOffIU(true, false, qSharedPointerCast<UnitNode>(iuun));
        }
        //нужен сброс
    }

    return true;
}
