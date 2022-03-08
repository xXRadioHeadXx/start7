#include "ProcessingStateWord0x33T4KBOD.h"

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

ProcessingStateWord0x33T4KBOD::ProcessingStateWord0x33T4KBOD(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x33T4KBOD::~ProcessingStateWord0x33T4KBOD()
{

}

bool ProcessingStateWord0x33T4KBOD::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -->";
    if(TypeUnitNodeEnum::BOD_T4K_M != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procT4KMBODStatusWord0x33(1) <--";
        return false;
    }

    const auto& reciverBOD = TopologyService::findReciver(currentUN);
    if(reciverBOD.isNull()) {

        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procT4KMBODStatusWord0x33(2) <--";

        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x33u, data);

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

//        qDebug() << "PortManager::procT4KMBODStatusWord0x33(5) <--";
        return true;
    }

    auto swpCurrentYIsInAlarm =
            1 == swpCurrent.y1().isInAlarm()
         || 1 == swpCurrent.y2().isInAlarm()
         || 1 == swpCurrent.y3().isInAlarm()
         || 1 == swpCurrent.y4().isInAlarm();

    auto swpPreviousYIsInAlarm =
            1 == swpPrevious.y1().isInAlarm()
         || 1 == swpPrevious.y2().isInAlarm()
         || 1 == swpPrevious.y3().isInAlarm()
         || 1 == swpPrevious.y4().isInAlarm();

    auto swpCurrentYIsWasAlarm =
            1 == swpCurrent.y1().isWasAlarm()
         || 1 == swpCurrent.y2().isWasAlarm()
         || 1 == swpCurrent.y3().isWasAlarm()
         || 1 == swpCurrent.y4().isWasAlarm();

    auto swpPreviousYIsWasAlarm =
            1 == swpPrevious.y1().isWasAlarm()
         || 1 == swpPrevious.y2().isWasAlarm()
         || 1 == swpPrevious.y3().isWasAlarm()
         || 1 == swpPrevious.y4().isWasAlarm();

//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -- swpCurrentYIsInAlarm " << swpCurrentYIsInAlarm;
//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -- swpPreviousYIsInAlarm " << swpPreviousYIsInAlarm;
//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -- swpCurrentYIsWasAlarm " << swpCurrentYIsWasAlarm;
//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -- swpPreviousYIsWasAlarm " << swpPreviousYIsWasAlarm;

    auto isChangedStatus = false;
    if(swpCurrent.isReady() != swpPrevious.isReady()
    || swpCurrent.isInOpened() != swpPrevious.isInOpened()
    || swpCurrent.isWasOpened() != swpPrevious.isWasOpened()
    || swpCurrentYIsInAlarm != swpPreviousYIsInAlarm
    || swpCurrentYIsWasAlarm != swpPreviousYIsWasAlarm
      ) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -- isChangedStatus " << isChangedStatus;

    auto isSwitchReady = false;
    if(1 == swpCurrent.isReady()
    && swpCurrent.isReady() != swpPrevious.isReady()) {
        // состояние не зменилось - что-то пропускаем
        isSwitchReady = true;
    }
//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -- isSwitchReady " << isSwitchReady;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState() || -1 == reciverBOD->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -- isFirstWakeUp " << isFirstWakeUp;


    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciverBOD->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needResetFlags0x24 = false;
    auto makedResetFlags0x24 = false;
    if(1 == swpCurrent.isReady()
    && (1 == swpCurrent.isWasOpened()
     || 1 == swpCurrentYIsWasAlarm)) { // сброс тревоги
        needResetFlags0x24 = true;
    }
//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -- needResetFlags0x24" << needResetFlags0x24;
    if(needResetFlags0x24) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciverBOD->pushBackUniqManagerSingleMsg(msMsg);
        makedResetFlags0x24 = true;
    }
//    qDebug() << "PortManager::procT4KMBODStatusWord0x33() -- makedResetFlags0x24" << makedResetFlags0x24;

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

//    qDebug() << "состояние T4KM_BOD -->" << commentMsg;
//    qDebug() << "pT4KM_BOD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cT4KM_BOD: " << currentUN->toString() << swpCurrent.byteWord().toHex();

//    bool iniState = false;
    // запись тревога/норма/неисправность ЧЭ1 -->
    if(1 == swpCurrent.isReady()
    && 1 == swpCurrent.isWasOpened()
    && (swpCurrent.isWasOpened() != swpPrevious.isWasOpened()
     || isSwitchReady)) {
        commentMsg = QObject::tr("Тревога - Вскрытие");
        typeMsg = 21;
        currentUN->setPublishedState(21);

        reciverBOD->setClearedAlarm(21);
    } else if(1 == swpCurrent.isReady()
           && swpCurrentYIsWasAlarm
           && (swpCurrentYIsWasAlarm != swpPreviousYIsWasAlarm
            || isSwitchReady)) {
        commentMsg = QObject::tr("Тревога - Сработка");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        reciverBOD->setClearedAlarm(20);
    } else if(1 == swpCurrent.isReady()
           && !swpCurrentYIsWasAlarm
           && (swpCurrentYIsWasAlarm != swpPreviousYIsWasAlarm
            || isSwitchReady)) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
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
     || 20 == currentUN->getPublishedState()
     || 21 == currentUN->getPublishedState()
     || currentUN->getPublishedState() != previousUN->getPublishedState())
    && isChangedStatus
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

        if(20 == typeMsg || 21 == typeMsg) {
            SoundAdjuster::playAlarm();
        }

        if(1 == currentUN->getAlarmMsgOn() && (12 == msg.getType() || 20 == typeMsg || 21 == typeMsg)) {
            MessageBoxServer::showAttentionJourMsg(msg);
        }

    }
    // запись тревога/норма/неисправность ЧЭ1 <--

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "typeMsg:" << typeMsg << "commentMsg:" << commentMsg;
//    qDebug() << "pT4KM_BOD: " << previousUN->toString() << previousUN->getPublishedState();
//    qDebug() << "cT4KM_BOD: " << currentUN->toString() << currentUN->getPublishedState();
//    qDebug() << "состояние T4KM_BOD <--";


//    qDebug() << "PortManager::procT4KMBODStatusWord0x33(X) <--";
    return true;
}
