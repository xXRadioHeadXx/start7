#include "ProcessingStateWord0x34TGDK.h"

#include "../src/entity/UnitNode.h"
#include "../src/utils/SignalSlotCommutator.h"

#include "../src/utils/TopologyService.h"

ProcessingStateWord0x34TGDK::ProcessingStateWord0x34TGDK(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x34TGDK::~ProcessingStateWord0x34TGDK()
{

}

bool ProcessingStateWord0x34TGDK::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procDkStatusWord0x34 -->";
    if(!currentUN->getDkInvolved()
    || TypeUnitNodeEnum::TG != currentUN->getType()) {
//        qDebug() << "PortManager::procDkStatusWord0x34(1) <--";
        return false;
    }

//    const auto& isAutoDK = currentUN->getIsAutoDkInvolved();

    auto reciver = TopologyService::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procIUBLIPStatusWord0x41(2) <--";
        return false;
    }

    currentUN->setStateWord(0x34u, data);
    reciver->setStateWord(0x34u, data);

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procDkStatusWord0x34(1) <--";
    return true;
}

