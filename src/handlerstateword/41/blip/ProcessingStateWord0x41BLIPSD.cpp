#include "ProcessingStateWord0x41BLIPSD.h"

#include <QDebug>
#include "JourEntity.h"
#include "UnitNode.h"
#include "TopologyService.h"
#include "global.h"
#include "swpblip/SWPSDBLIPType0x41.h"
#include "swpblip/SWPBLIPType0x41.h"
#include "UnitNodeFactory.h"
#include "SignalSlotCommutator.h"
#include "DataQueueItem.h"
#include "DataBaseManager.h"
#include "GraphTerminal.h"
#include "SoundAdjuster.h"
#include "MessageBoxServer.h"

ProcessingStateWord0x41BLIPSD::ProcessingStateWord0x41BLIPSD(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x41BLIPSD::~ProcessingStateWord0x41BLIPSD()
{

}

bool ProcessingStateWord0x41BLIPSD::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41() -->";
    if(TypeUnitNodeEnum::SD_BL_IP != currentUN->getType()
    || 1 == currentUN->getBazalt()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procSDBLIPStatusWord0x41(1) <--";
        return false;
    }

    const auto& reciver = TopologyService::findReciver(currentUN).dynamicCast<UnitNode_BL_IP>();
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procSDBLIPStatusWord0x41(2) <--";
        return false;
    }

    const auto& previousUN = UnitNodeFactory::makeShare(*currentUN).dynamicCast<UnitNode_SD_BL_IP>();
    currentUN->setStateWord(0x41u, data);
    reciver->setStateWord(0x41u, data);
    if(reciver->getDkInvolved()) {
//        qDebug() << "PortManager::procSDBLIPStatusWord0x41(2.1) <--";
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();
        return false;
    }

    const auto& swpCurrentBLIP = currentUN->swpBLIPType0x41();
    const auto& swpPreviousBLIP = previousUN->swpBLIPType0x41();
    if(1 == swpCurrentBLIP.isExistDK()
    || 1 == swpCurrentBLIP.isWasDK()
    || 1 == swpPreviousBLIP.isExistDK()
    || 1 == swpPreviousBLIP.isWasDK()) {
        {
            auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                                  DataQueueItem::makeResetFlags0x24);
            reciver->pushBackUniqManagerSingleMsg(msMsg);
        }
//        qDebug() << "PortManager::procSDBLIPStatusWord0x41(5) <--";
        return true;
    }

    const auto& swpCurrent = currentUN->swpSDBLIPType0x41(),
               &swpPrevious = previousUN->swpSDBLIPType0x41();

    auto isChangedStatus = false;
    if(swpCurrent.isAlarm() != swpPrevious.isAlarm()
    || swpCurrent.isWasAlarm() != swpPrevious.isWasAlarm()
    || swpCurrent.isNorm() != swpPrevious.isNorm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41() -- isChangedStatus " << isChangedStatus;

    auto isSwitchOnOff = false;
    if(!swpPrevious.isNull()
    && (swpCurrent.isOff() != swpPrevious.isOff()
     || swpCurrent.isOn() != swpPrevious.isOn())) {
        // состояние не зменилось - что-то пропускаем
        isSwitchOnOff = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41() -- isSwitchOnOff " << isSwitchOnOff;


    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState()
    || 10 == reciver->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needResetFlags0x24 = false;
//    auto makedResetFlags0x24 = false;
    if(1 == swpCurrent.isOn()
//    && 1 == swpCurrent.isAlarm()
    && 1 == swpCurrent.isWasAlarm()) { // сброс тревоги
        needResetFlags0x24 = true;
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41 -- needResetFlags0x24" << needResetFlags0x24;
    if(needResetFlags0x24) {
        {
            auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                                  DataQueueItem::makeResetFlags0x24);
            reciver->pushBackUniqManagerSingleMsg(msMsg);
        }
    }
//    qDebug() << "PortManager::procSDBLIPStatusWord0x41 -- makedResetFlags0x24" << makedResetFlags0x24;

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

    // запись вкл/выкл СД -->
    int typeMsg = -1;
    QString commentMsg;
    bool needRepeatActualState = false;

    if(1 == swpCurrent.isOff()) {
        commentMsg = QObject::tr("Выкл");
        typeMsg = 100;
        reciver->setPublishedState(100);
    } else if(1 == swpCurrent.isOn()) {
        commentMsg = QObject::tr("Вкл");
        typeMsg = 101;
        reciver->setPublishedState(101);
        needRepeatActualState = true;
    }

//    qDebug() << "состояние СД -->" << commentMsg;
//    qDebug() << "pSD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cSD: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние СД <--";

    if(isSwitchOnOff
    && 1 != currentUN->getMetaEntity()
    && -1 != typeMsg) {
        // следует записать сообщение
        JourEntity msg = prepareMsg;
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
    } else {
        needRepeatActualState = false;
    }
    typeMsg = -1;

    bool iniState = false;
    // запись тревог и нормы СД
    if(1 == swpCurrent.isOn()
    && 1 == swpCurrent.isAlarm()
    && 1 == swpCurrent.isWasAlarm()
    && (swpPrevious.isAlarm() != swpCurrent.isAlarm()
     || swpPrevious.isWasAlarm() != swpCurrent.isWasAlarm()
     || needRepeatActualState)) {
        //сохранение Тревога или Норма
        commentMsg = QObject::tr("Тревога-СРАБОТКА");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        reciver->setPublishedState(20);
    } else if(1 == swpCurrent.isOn()
           && 1 == swpCurrent.isNorm()
           && ((swpPrevious.isNorm() != swpCurrent.isNorm()
             && 1 != currentUN->getPublishedState())
            || needRepeatActualState)) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
        reciver->setPublishedState(1);
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


//    qDebug() << "состояние СД -->" << commentMsg;
//    qDebug() << "pSD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cSD: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние СД <--";

    bool wasSendAbonentEventsAndStates = false || isWakeUp || isFirstWakeUp;
    JourEntity msg = prepareMsg;
    if((isWakeUp ||
        isFirstWakeUp ||
        20 == currentUN->getPublishedState() ||
        currentUN->getPublishedState() != previousUN->getPublishedState() ||
        isChangedStatus ||
        needRepeatActualState) &&
       1 != currentUN->getMetaEntity() &&
       -1 != typeMsg &&
       currentUN->getControl()) {
        // следует записать сообщение
        // заполняем поля сообщения
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        wasSendAbonentEventsAndStates = false;

        if(20 == typeMsg && !iniState) {
            SoundAdjuster::playAlarm();
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

            SignalSlotCommutator::emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
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
            reciver->setPublishedState(1);
            msg.setComment(commentMsg);
            msg.setType(typeMsg);
            GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        }
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    if(20 == typeMsg && !iniState && currentUN->getControl()) {
        // тригер на ИУ
        for(const auto& iuun : as_const(TopologyService::getLinkedUI(currentUN))) {
            SignalSlotCommutator::emitAutoOnOffIU(true, false, qSharedPointerCast<UnitNode>(iuun));
        }
        //нужен сброс
    }

//    qDebug() << "PortManager::procSDBLIPStatusWord0x41(3) <--";
    return true;
}
