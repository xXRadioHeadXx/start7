#include "ProcessingStateWord0x34TG.h"

#include "../src/entity/UnitNode.h"
#include "../src/utils/TopologyService.h"
#include "../src/utils/SignalSlotCommutator.h"

ProcessingStateWord0x34TG::ProcessingStateWord0x34TG(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x34TG::~ProcessingStateWord0x34TG()
{

}

bool ProcessingStateWord0x34TG::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procTgStatusWord0x34() -->";
    if(TypeUnitNodeEnum::TG != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procTgStatusWord0x34(1) <--";
        return false;
    }

    auto reciver = TopologyService::findReciver(currentUN);
    if(reciver.isNull()) {
//        qDebug() << "PortManager::procTgStatusWord0x34(2) <--";
        return false;
    }

    currentUN->setStateWord(0x34u, data);
    reciver->setStateWord(0x34u, data);

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procTgStatusWord0x34(X) <--";
    return true;
}
