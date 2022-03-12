#include "ProcessingStateWord0x34SOTADD.h"

#include "UnitNode.h"
#include "UnitNodeFactory.h"
#include "swpsota/SWPSOTABODType0x34.h"
#include "swpsota/SWPSOTADDType0x34.h"
#include "swpsota/SWPSOTADDFType0x34.h"
#include "global.h"
#include "DataBaseManager.h"
#include "TopologyService.h"
#include "SignalSlotCommutator.h"
#include "GraphTerminal.h"
#include "SoundAdjuster.h"
#include "MessageBoxServer.h"

ProcessingStateWord0x34SOTADD::ProcessingStateWord0x34SOTADD(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x34SOTADD::~ProcessingStateWord0x34SOTADD()
{

}

bool ProcessingStateWord0x34SOTADD::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procSOTAMDDStatusWord0x34() -->";
    if(TypeUnitNodeEnum::DD_SOTA != currentUN->getType()
    || currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procSOTAMDDStatusWord0x34(1) <--";
        return false;
    }

    const auto& reciverBOD = TopologyService::findReciver(currentUN);
    if(reciverBOD.isNull()) {
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procSOTAMDDStatusWord0x34(3) <--";

        return false;
    }

    const auto& reciverY4 = TopologyService::findParentByType(TypeUnitNodeEnum::Y4_SOTA, currentUN);
    if(reciverY4.isNull()) {
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procSOTAMDDStatusWord0x34(31) <--";

        return false;
    }
    if(TypeUnitNodeEnum::Y4_SOTA != reciverY4->getType()) {
        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

//        qDebug() << "PortManager::procSOTAMDDStatusWord0x34(32) <--";

        return false;
    }
    auto y4 = currentUN->getNum2() / 100;
    if(y4 > 2 && SWPSOTABODType0x34(data).getY4() < 1) {
//        qDebug() << "PortManager::procSOTAMDDStatusWord0x34(32) <--";
        return false;
    }

    auto ddNum = currentUN->getNum2() % 100;
    if(ddNum != SWPSOTABODType0x34(data).getDd()) {
//        qDebug() << "PortManager::procSOTAMDDStatusWord0x34(32) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x34u, data);
    reciverBOD->setStateWord(0x34u, data);

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();


//    qDebug() << "PortManager::procSOTAMDDStatusWord0x34(X) <--";
    return true;
}
