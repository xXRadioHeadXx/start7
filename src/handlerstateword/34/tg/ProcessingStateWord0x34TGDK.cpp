#include "ProcessingStateWord0x34TGDK.h"

#include "UnitNode.h"
#include "SignalSlotCommutator.h"

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

    currentUN->setStateWord(0x34u, data);

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procDkStatusWord0x34(1) <--";
    return true;
}

