#include "ProcessingStateWord0x42SSOIBLIPDK.h"

#include "UnitNode.h"
#include "UnitNodeFactory.h"
#include "SignalSlotCommutator.h"

ProcessingStateWord0x42SSOIBLIPDK::ProcessingStateWord0x42SSOIBLIPDK(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x42SSOIBLIPDK::~ProcessingStateWord0x42SSOIBLIPDK()
{

}

bool ProcessingStateWord0x42SSOIBLIPDK::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
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

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x42u, data);

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

//    qDebug() << "PortManager::procDkBLIPStatusWord0x42(2) <--";
    return true;
}
