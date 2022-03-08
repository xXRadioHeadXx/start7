#include "ProcessingStateWord0x42SSOIBLIPSD.h"

#include "UnitNode.h"
#include "UnitNodeFactory.h"
#include "SignalSlotCommutator.h"
#include "TopologyService.h"
#include "swpssoiblip/SWPSSOISDBLIPType0x42.h"


ProcessingStateWord0x42SSOIBLIPSD::ProcessingStateWord0x42SSOIBLIPSD(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x42SSOIBLIPSD::~ProcessingStateWord0x42SSOIBLIPSD()
{

}

bool ProcessingStateWord0x42SSOIBLIPSD::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
    //    qDebug() << "PortManager::procSSOISDBLIPStatusWord0x42() -->";
    if(TypeUnitNodeEnum::SSOI_SD_BL_IP != currentUN->getType()
    || 1 == currentUN->getBazalt()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procSSOISDBLIPStatusWord0x42(1) <--";
        return false;
    }

    auto reciver = TopologyService::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procSSOISDBLIPStatusWord0x42(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x42u, data);

    if(reciver->getDkInvolved()) {
//        qDebug() << "PortManager::procSSOISDBLIPStatusWord0x42(2.1) <--";
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();
        return false;
    }

    const auto& swpCurrent = currentUN->swpSSOISDBLIPType0x42(),
               &swpPrevious = previousUN->swpSSOISDBLIPType0x42();

//    auto isChangedStatus = false;
//    if(swpCurrent.isInAlarm() != swpPrevious.isInAlarm() ||
//       swpCurrent.isLineBreak() != swpPrevious.isLineBreak()) {
//        // состояние не зменилось - что-то пропускаем
//        isChangedStatus = true;
//    }
//    qDebug() << "PortManager::procSSOISDBLIPStatusWord0x42() -- isChangedStatus " << isChangedStatus;

//    auto isFirstWakeUp = false;
//    // устройство очнулось (после потери связи например)
//    if(-1 == currentUN->getPublishedState()) {
//        isFirstWakeUp = true;
//    }
//    qDebug() << "PortManager::procSSOISDBLIPStatusWord0x42() -- isFirstWakeUp " << isFirstWakeUp;

//    auto isWakeUp = false;
//    // устройство очнулось (после потери связи например)
//    if(10 == currentUN->getPublishedState() || 10 == reciver->getPublishedState()) {
//        isWakeUp = true;
//    }
//    qDebug() << "PortManager::procSSOISDBLIPStatusWord0x42() -- isWakeUp " << isWakeUp;

    // запись вкл/выкл СД -->
    QString commentMsg;

    if(1 == swpCurrent.isInAlarm()) {
        commentMsg = QObject::tr("Выкл");

//        qDebug() << "состояние СД -->" << commentMsg;
//        qDebug() << "pSD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//        qDebug() << "cSD: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//        qDebug() << "состояние СД <--";
    }

    if(1 == swpCurrent.isShortCircuit()) {
        commentMsg = QObject::tr("Замыкание");

//        qDebug() << "состояние СД -->" << commentMsg;
//        qDebug() << "pSD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//        qDebug() << "cSD: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//        qDebug() << "состояние СД <--";
    }

    if(1 == swpCurrent.isLineBreak()) {
        commentMsg = QObject::tr("Обрыв");

//        qDebug() << "состояние СД -->" << commentMsg;
//        qDebug() << "pSD: " << previousUN->toString() << swpPrevious.byteWord().toHex();
//        qDebug() << "cSD: " << currentUN->toString() << swpCurrent.byteWord().toHex();
//        qDebug() << "состояние СД <--";
    }

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procSSOISDBLIPStatusWord0x42(3) <--";
        return true;
}
