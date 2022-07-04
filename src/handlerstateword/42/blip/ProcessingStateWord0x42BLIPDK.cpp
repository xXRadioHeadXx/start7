#include "ProcessingStateWord0x42BLIPDK.h"

#include "../src/entity/UnitNode.h"
#include "../src/entity/UnitNodeFactory.h"
#include "../src/utils/SignalSlotCommutator.h"
#include "../src/utils/TopologyService.h"

ProcessingStateWord0x42BLIPDK::ProcessingStateWord0x42BLIPDK(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un) {

}

ProcessingStateWord0x42BLIPDK::~ProcessingStateWord0x42BLIPDK() {

}

bool ProcessingStateWord0x42BLIPDK::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procDkBLIPStatusWord0x42() -->";
    if(0 == currentUN->getDK()
    || DKCiclStatus::DKIgnore == currentUN->getDkStatus()
    || DKCiclStatus::DKWrong == currentUN->getDkStatus()
    || DKCiclStatus::DKDone == currentUN->getDkStatus()
    || !currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procDkBLIPStatusWord0x42(1) <--";
        return false;
    }

    auto reciver = TopologyService::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procSDBLIPStatusWord0x42(2) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x42u, data);
    reciver->setStateWord(0x42u, data);

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procDkBLIPStatusWord0x42(2) <--";
    return true;
}

