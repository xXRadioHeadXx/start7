#include "ProcessingStateWord0x41SSOIBLIPIU.h"

#include <QDebug>
#include "JourEntity.h"
#include "UnitNode.h"
#include "TopologyService.h"
#include "swpssoiblip/SWPSSOIBLIPType0x41.h"
#include "swpssoiblip/SWPSSOIIUBLIPType0x41.h"
#include "swpssoiblip/SWPSSOISDBLIPType0x41.h"
#include "swpblip/SWPBLIPType0x41.h"
#include "UnitNodeFactory.h"
#include "SignalSlotCommutator.h"
#include "DataQueueItem.h"
#include "DataBaseManager.h"
#include "GraphTerminal.h"

ProcessingStateWord0x41SSOIBLIPIU::ProcessingStateWord0x41SSOIBLIPIU(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x41SSOIBLIPIU::~ProcessingStateWord0x41SSOIBLIPIU()
{

}

bool ProcessingStateWord0x41SSOIBLIPIU::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procIUBLIPStatusWord0x41() -->";
    if(TypeUnitNodeEnum::SSOI_IU_BL_IP != currentUN->getType()
    || 1 > currentUN->getNum2()
    || 4 < currentUN->getNum2()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procIUBLIPStatusWord0x41(1) <--";
        return false;
    }

    auto reciver = TopologyService::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procIUBLIPStatusWord0x41(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x41u, data);
    reciver->setStateWord(0x41u, data);
    if(reciver->getDkInvolved()) {
//        qDebug() << "PortManager::procIUBLIPStatusWord0x41(2.1) <--";
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();
        return false;
    }

    const auto& swpCurrentBLIP = currentUN->swpSSOIBLIPType0x41();
    const auto& swpPreviousBLIP = previousUN->swpSSOIBLIPType0x41();
    if(/*1 == swpCurrentBLIP.isExistDK()
    || */1 == swpCurrentBLIP.isWasDK()/*
    || 1 == swpPreviousBLIP.isExistDK()*/
    || 1 == swpPreviousBLIP.isWasDK()) {
        {
            auto msMsg = QSharedPointer<ManagerSingleMsg>::create(currentUN,
                                                                  DataQueueItem::makeResetFlags0x24);
            reciver->pushBackUniqManagerSingleMsg(msMsg);
        }
//        qDebug() << "PortManager::procIUBLIPStatusWord0x41(5) <--";
        return true;
    }

    const auto& swpCurrent = currentUN->swpSSOIIUBLIPType0x41();
    const auto& swpPrevious = previousUN->swpSSOIIUBLIPType0x41();

    auto isChangedStatus = false;
    if(swpCurrent.isOff() != swpPrevious.isOff() ||
       swpCurrent.isOn() != swpPrevious.isOn()) {
        // состояние не зменилось - что-то пропускаем
        isChangedStatus = true;
    }
//    qDebug() << "PortManager::procIUBLIPStatusWord0x41() -- isChangedStatus " << isChangedStatus;

    auto isFirstWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(-1 == currentUN->getPublishedState() || -1 == reciver->getPublishedState()) {
        isFirstWakeUp = true;
    }
//    qDebug() << "PortManager::procIUBLIPStatusWord0x41() -- isFirstWakeUp " << isFirstWakeUp;

    auto isWakeUp = false;
    // устройство очнулось (после потери связи например)
    if(10 == currentUN->getPublishedState() || 10 == reciver->getPublishedState()) {
        isWakeUp = true;
    }
//    qDebug() << "PortManager::procIUBLIPStatusWord0x41() -- isWakeUp " << isWakeUp;

    // запись вкл/выкл ИУ -->
    int typeMsg = -1;
    QString commentMsg;

    if(1 == swpCurrent.isOff()) {
        commentMsg = QObject::tr("Выкл");
        typeMsg = 100;
        currentUN->setPublishedState(100);
        reciver->setPublishedState(100);
    } else if(1 == swpCurrent.isOn()) {
        commentMsg = QObject::tr("Вкл");
        typeMsg = 101;
        currentUN->setPublishedState(101);
        reciver->setPublishedState(101);
    }

//    qDebug() << "состояние ИУ -->" << commentMsg;
//    qDebug() << "pIU: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//    qDebug() << "cIU: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//    qDebug() << "состояние ИУ <--";

    if((isWakeUp || isFirstWakeUp || isChangedStatus) && 1 != currentUN->getMetaEntity() && -1 != typeMsg) {
        // следует записать сообщение
        JourEntity msg;

        // заполняем поля сообщения за отправителя
        msg.setObject(currentUN->getName());
        msg.setObjecttype(currentUN->getType());
        msg.setD1(currentUN->getNum1());
        msg.setD2(currentUN->getNum2());
        msg.setD3(currentUN->getNum3());
        msg.setD4(currentUN->getOutType());
        msg.setDirection(currentUN->getDirection());
        if(currentUN->takeResetWaitAutoCommand())
            commentMsg += QObject::tr(" (Авто)");
        msg.setComment(commentMsg);
        msg.setType(typeMsg);
        msg.setParams(currentUN->makeJson());
                currentUN->done=true;
        SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg(msg);
        GraphTerminal::sendAbonentEventsAndStates(currentUN, msg);
    }
    // запись вкл/выкл ИУ <--

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    currentUN->callUpdateStateConditionReactor();
//    qDebug() << "PortManager::procIUBLIPStatusWord0x41(3) <--";
    return true;
}
