#include "ProcessingStateWord0x32SOTADD.h"

#include "../src/entity/UnitNode.h"
#include "../src/entity/UnitNodeFactory.h"
#include "../src/statewordparsers/swpsota/SWPSOTABODType0x32.h"
#include "../src/statewordparsers/swpsota/SWPSOTAY4Type0x32.h"
#include "../src/statewordparsers/swpsota/SWPSOTADDType0x32.h"
#include "../src/statewordparsers/swpsota/SWPSOTADDCType0x32.h"
#include "../src/global.h"
#include "../src/database/DataBaseManager.h"
#include "../src/utils/TopologyService.h"
#include "../src/utils/SignalSlotCommutator.h"
#include "../src/port/GraphTerminal.h"
#include "../src/utils/SoundAdjuster.h"
#include "../src/utils/MessageBoxServer.h"

ProcessingStateWord0x32SOTADD::ProcessingStateWord0x32SOTADD(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x32SOTADD::~ProcessingStateWord0x32SOTADD()
{

}

bool ProcessingStateWord0x32SOTADD::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
    if(TypeUnitNodeEnum::DD_SOTA != currentUN->getType()
    || currentUN->getDkInvolved()) {
        return false;
    }

//    qDebug() << "ProcessingStateWord0x32SOTADD::processing() -->";

    const auto& reciverBOD = TopologyService::findReciver(currentUN);
    if(reciverBOD.isNull()) {

//        qDebug() << "ProcessingStateWord0x32SOTADD::processing(3) <--";

        return false;
    }

    const auto& reciverY4 = TopologyService::findParentByType(TypeUnitNodeEnum::Y4_SOTA, currentUN);
    if(reciverY4.isNull()) {

//        qDebug() << "ProcessingStateWord0x32SOTADD::processing(31) <--";

        return false;
    }
    if(TypeUnitNodeEnum::Y4_SOTA != reciverY4->getType()) {

//        qDebug() << "ProcessingStateWord0x32SOTADD::processing(32) <--";

        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x32u, data);
    reciverBOD->setStateWord(0x32u, data);

    const auto& swpCurrent = currentUN->swpSOTABODType0x32(),
               &swpPrevious = previousUN->swpSOTABODType0x32();

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciverBOD->pushBackUniqManagerSingleMsg(msMsg);

        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procSOTAMDDStatusWord0x32(4) <--";
        return true;
    }

    auto y4 = currentUN->getNum2() / 100;

    auto ddNum = currentUN->getNum2() % 100;

    auto isChangedStatus = false;
    if(swpCurrent.y(y4).dd(ddNum).isWasAlarm() != swpPrevious.y(y4).dd(ddNum).isWasAlarm()
    || swpCurrent.y(y4).dd(ddNum).isFault() != swpPrevious.y(y4).dd(ddNum).isFault()
    || swpCurrent.y(y4).dd(ddNum).isInCommunicationBreak() != swpPrevious.y(y4).dd(ddNum).isInCommunicationBreak()
    || swpCurrent.y(y4).dd(ddNum).isWasCommunicationBreak() != swpPrevious.y(y4).dd(ddNum).isWasCommunicationBreak()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procSOTAMDDStatusWord0x32() -- isChangedStatus " << isChangedStatus;

    auto isSwitchReady = false;
    if(1 == swpCurrent.isReady()
    && swpCurrent.isReady() != swpPrevious.isReady()) {
        // состояние не зменилось - что-то пропускаем
        isSwitchReady = true;
    }
//    qDebug() << "PortManager::procSOTAMDDStatusWord0x32() -- isSwitchReady " << isSwitchReady;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState() || -1 == reciverBOD->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procSOTAMDDStatusWord0x32() -- isFirstWakeUp " << isFirstWakeUp;


    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciverBOD->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procSOTAMDDStatusWord0x32() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needResetFlags0x24 = false;
    auto makedResetFlags0x24 = false;
    Q_UNUSED(makedResetFlags0x24)
    if(1 == swpCurrent.isReady()
    && (1 == swpCurrent.y(y4).dd(ddNum).isWasAlarm()
     || 1 == swpCurrent.y(y4).dd(ddNum).isWasCommunicationBreak()
     || 1 == swpCurrent.y(y4).dd(ddNum).isFault())) { // сброс тревоги
        needResetFlags0x24 = true;
    }
//    qDebug() << "PortManager::procSOTAMDDStatusWord0x32() -- needResetFlags0x24" << needResetFlags0x24;
    if(needResetFlags0x24) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciverBOD->pushBackUniqManagerSingleMsg(msMsg);
    }
//    qDebug() << "PortManager::procSOTAMDDStatusWord0x32() -- makedResetFlags0x24" << makedResetFlags0x24;

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

//    qDebug() << "состояние SOTAM_DD -->" << commentMsg;
//    qDebug() << "pSOTAM_DD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cSOTAM_DD: " << currentUN->toString() << swpCurrent.byteWord().toHex();

    if(1 == swpCurrent.isReady()
    && 1 == swpCurrent.y(y4).dd(ddNum).isWasCommunicationBreak()
    && (swpCurrent.y(y4).dd(ddNum).isWasCommunicationBreak() == swpPrevious.y(y4).dd(ddNum).isWasCommunicationBreak()
     || isSwitchReady)) {
        commentMsg = QObject::tr("Нет связи");
        typeMsg = 10;
        currentUN->setPublishedState(10);

        reciverBOD->setClearedAlarm(12);
        reciverY4->setClearedAlarm(12);
    } else if(1 == swpCurrent.isReady()
           && 1 == swpCurrent.y(y4).dd(ddNum).isInCommunicationBreak()) {
        currentUN->setPublishedState(10);
    } else if(1 == swpCurrent.isReady()
           && 1 == swpCurrent.y(y4).dd(ddNum).isFault()
           && (swpCurrent.y(y4).dd(ddNum).isFault() == swpPrevious.y(y4).dd(ddNum).isFault()
     || isSwitchReady)) {
        commentMsg = QObject::tr("Неисправность");
        typeMsg = 12;
        currentUN->setPublishedState(12);

        reciverBOD->setClearedAlarm(12);
        reciverY4->setClearedAlarm(12);
    } else if(1 == swpCurrent.isReady()
           && 1 == swpCurrent.y(y4).dd(ddNum).isWasAlarm()
           && (swpCurrent.y(y4).dd(ddNum).isWasAlarm() == swpPrevious.y(y4).dd(ddNum).isWasAlarm()
            || isSwitchReady)) {
        commentMsg = QObject::tr("Тревога - Сработка");
        typeMsg = 20;
        currentUN->setPublishedState(20);

        reciverBOD->setClearedAlarm(20);
        reciverY4->setClearedAlarm(20);
    } else if(1 == swpCurrent.isReady()
           && 1 == swpCurrent.y(y4).dd(ddNum).isWasCommunicationBreak()
           && (swpCurrent.y(y4).dd(ddNum).isWasCommunicationBreak() == swpPrevious.y(y4).dd(ddNum).isWasCommunicationBreak()
            || isSwitchReady)) {
        commentMsg = QObject::tr("Обрыв связи");
        typeMsg = 12;
        currentUN->setPublishedState(12);
    } else if(1 == swpCurrent.isReady()
              && 0 == swpCurrent.y(y4).dd(ddNum).isFault()
              && 0 == swpCurrent.y(y4).dd(ddNum).isWasAlarm()
              && (swpCurrent.y(y4).dd(ddNum).isFault() != swpPrevious.y(y4).dd(ddNum).isFault()
               || swpCurrent.y(y4).dd(ddNum).isWasAlarm() != swpPrevious.y(y4).dd(ddNum).isWasAlarm()
               || isSwitchReady)) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
    } else if(0 == swpCurrent.isReady()) {
//        commentMsg = QObject::tr("Неопределенное состояние");
//        typeMsg = 0;
        currentUN->setPublishedState(0);
    }

    bool wasSendAbonentEventsAndStates = false || isWakeUp || isFirstWakeUp;
    Q_UNUSED(wasSendAbonentEventsAndStates)
    if((isWakeUp
     || isFirstWakeUp
     || isSwitchReady
     || 12 == currentUN->getPublishedState()
     || 20 == currentUN->getPublishedState()
     || currentUN->getPublishedState() != previousUN->getPublishedState())
    && (isChangedStatus
     || isSwitchReady)
    && 1 != currentUN->getMetaEntity()
    && -1 != typeMsg
    && currentUN->getControl()) {
        JourEntity msg = prepareMsg;
        // следует записать сообщение
        // заполняем поля сообщения
        if(isWakeUp || isFirstWakeUp || isSwitchReady) {
            commentMsg += " (начальное состояние)";
        }
        msg.setComment(commentMsg);
        msg.setType(typeMsg);

        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg(msg);
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
        wasSendAbonentEventsAndStates = false;

        if(20 == typeMsg) {
            SoundAdjuster::playAlarm();
        }

        if(1 == currentUN->getAlarmMsgOn() && (12 == msg.getType() || 20 == msg.getType())) {
            MessageBoxServer::showAttentionJourMsg(msg);
        }

    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "typeMsg:" << typeMsg << "commentMsg:" << commentMsg;
//    qDebug() << "pSOTAM_DD: " << previousUN->toString() << previousUN->getPublishedState();
//    qDebug() << "cSOTAM_DD: " << currentUN->toString() << currentUN->getPublishedState();
//    qDebug() << "состояние SOTAM_DD <--";

//    qDebug() << "PortManager::procSOTAMDDStatusWord0x32(X) <--";
    return true;
}
