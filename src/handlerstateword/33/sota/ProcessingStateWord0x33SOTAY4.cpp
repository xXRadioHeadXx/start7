#include "ProcessingStateWord0x33SOTAY4.h"

#include "UnitNode.h"
#include "UnitNodeFactory.h"
#include "swpsota/SWPSOTABODType0x33.h"
#include "swpsota/SWPSOTAY4Type0x33.h"
#include "swpsota/SWPSOTADDType0x33.h"
#include "swpsota/SWPSOTADDFType0x33.h"
#include "global.h"
#include "DataBaseManager.h"
#include "TopologyService.h"
#include "SignalSlotCommutator.h"
#include "GraphTerminal.h"
#include "SoundAdjuster.h"
#include "MessageBoxServer.h"

ProcessingStateWord0x33SOTAY4::ProcessingStateWord0x33SOTAY4(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x33SOTAY4::~ProcessingStateWord0x33SOTAY4()
{

}

bool ProcessingStateWord0x33SOTAY4::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procSOTAMY4StatusWord0x33() -->";
    if(TypeUnitNodeEnum::Y4_SOTA != currentUN->getType()) {
//        qDebug() << "PortManager::procSOTAMY4StatusWord0x33(1) <--";
        return false;
    }

    if(currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procSOTAMY4StatusWord0x33(1) <--";
        return false;
    }

    const auto& reciverBOD = TopologyService::findReciver(currentUN);
    if(reciverBOD.isNull()) {
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procSOTAMY4StatusWord0x33(2) <--";

        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x33u, data);
    reciverBOD->setStateWord(0x33u, data);

    const auto& swpCurrent = currentUN->swpSOTABODType0x33(),
               &swpPrevious = previousUN->swpSOTABODType0x33();

    if(1 == swpCurrent.isExistDK()
    || 1 == swpCurrent.isWasDK()
    || 1 == swpPrevious.isExistDK()
    || 1 == swpPrevious.isWasDK()) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciverBOD->pushBackUniqManagerSingleMsg(msMsg);

        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procSOTAMY4StatusWord0x33(5) <--";
        return true;
    }

    auto y4 = currentUN->getNum2() / 100;

    auto isChangedStatus = false;
    if(swpCurrent.isReady() != swpPrevious.isReady()
    || swpCurrent.y(y4).isInAlarm() != swpPrevious.y(y4).isInAlarm()
    || swpCurrent.y(y4).isWasAlarm() != swpPrevious.y(y4).isWasAlarm()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procSOTAMY4StatusWord0x33() -- isChangedStatus " << isChangedStatus;

    auto isSwitchReady = false;
    if(1 == swpCurrent.isReady()
    && swpCurrent.isReady() != swpPrevious.isReady()) {
        // состояние не зменилось - что-то пропускаем
        isSwitchReady = true;
    }
//    qDebug() << "PortManager::procSOTAMY4StatusWord0x33() -- isSwitchReady " << isSwitchReady;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState() || -1 == reciverBOD->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procSOTAMY4StatusWord0x33() -- isFirstWakeUp " << isFirstWakeUp;


    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciverBOD->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procSOTAMY4StatusWord0x33() -- isWakeUp " << isWakeUp;

    // даём сброс тревоги если нужен
    auto needResetFlags0x24 = false;
    auto makedResetFlags0x24 = false;
    Q_UNUSED(makedResetFlags0x24)
    if(1 == swpCurrent.isReady()
    && 1 == swpCurrent.y(y4).isWasAlarm()) { // сброс тревоги
        needResetFlags0x24 = true;
    }
//    qDebug() << "PortManager::procSOTAMY4StatusWord0x33 -- needResetFlags0x24 y4("<< y4 <<")" << needResetFlags0x24;
    if(needResetFlags0x24) {
        auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                              DataQueueItem::makeResetFlags0x24);
        reciverBOD->pushBackUniqManagerSingleMsg(msMsg);
        makedResetFlags0x24 = true;
    }
//    qDebug() << "PortManager::procSOTAMY4StatusWord0x33 -- makedResetFlags0x24 y4("<< y4 <<")" << makedResetFlags0x24;

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
    Q_UNUSED(commentMsg)

//    qDebug() << "состояние SOTAM_Y4 -->" << commentMsg;
//    qDebug() << "pSOTAM_Y4: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cSOTAM_Y4: " << currentUN->toString() << swpCurrent.byteWord().toHex();

    //bool iniState = false;
    // запись тревога/норма/неисправность ЧЭ1 -->
    if(1 == swpCurrent.isReady()
    && 1 == swpCurrent.y(y4).isWasAlarm()
    && (swpCurrent.y(y4).isWasAlarm() != swpPrevious.y(y4).isWasAlarm()
     || isSwitchReady)) {
        commentMsg = QObject::tr("Тревога - Сработка");
        typeMsg = 20;
        currentUN->setPublishedState(20);
        reciverBOD->setClearedAlarm(20);
    } else if(1 == swpCurrent.isReady()
           && 0 == swpCurrent.y(y4).isWasAlarm()
           && (swpCurrent.y(y4).isWasAlarm() != swpPrevious.y(y4).isWasAlarm()
            || isSwitchReady)) {
        commentMsg = QObject::tr("Норма");
        typeMsg = 1;
        currentUN->setPublishedState(1);
    } else if(0 == swpCurrent.isReady()) {
        commentMsg = QObject::tr("Неопределенное состояние");
        typeMsg = 0;
        currentUN->setPublishedState(0);
    }
//    if(isWakeUp || isFirstWakeUp) {
//        commentMsg += " (начальное состояние)";
//    }

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
                currentUN->done=true;
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
//    qDebug() << "pSOTAM_Y4: " << previousUN->toString() << previousUN->getPublishedState();
//    qDebug() << "cSOTAM_Y4: " << currentUN->toString() << currentUN->getPublishedState();
//    qDebug() << "состояние SOTAM_Y4 <--";

//    qDebug() << "PortManager::procSOTAMY4StatusWord0x33(X) <--";
    return true;
}
