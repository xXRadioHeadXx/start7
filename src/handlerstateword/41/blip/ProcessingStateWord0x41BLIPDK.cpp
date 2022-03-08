#include "ProcessingStateWord0x41BLIPDK.h"

#include <QDebug>
#include "UnitNode.h"
#include "swpblip/SWPSDBLIPType0x41.h"
#include "UnitNodeFactory.h"
#include "SignalSlotCommutator.h"



ProcessingStateWord0x41BLIPDK::ProcessingStateWord0x41BLIPDK(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x41BLIPDK::~ProcessingStateWord0x41BLIPDK()
{

}

bool ProcessingStateWord0x41BLIPDK::processing(const StateWord &data, const QSharedPointer<UnitNode> &currentUN) const
{
//    qDebug() << "PortManager::procDkBLIPStatusWord0x41() -->";
    if(0 == currentUN->getDK()
    || TypeUnitNodeEnum::SD_BL_IP != currentUN->getType()
    || DKCiclStatus::DKIgnore == currentUN->getDkStatus()
    || DKCiclStatus::DKWrong == currentUN->getDkStatus()
    || DKCiclStatus::DKDone == currentUN->getDkStatus()
    || !currentUN->getDkInvolved()) {
//        qDebug() << "PortManager::procDkBLIPStatusWord0x41(1) <--";
        return false;
    }

    QSharedPointer<UnitNode> previousUN = UnitNodeFactory::makeShare(*currentUN);
    currentUN->setStateWord(0x41u, data);

    auto swpCurrent = currentUN->swpSDBLIPType0x41();
    if(1 == swpCurrent.isOff()) {
        currentUN->setDkStatus(DKCiclStatus::DKWrong);

        currentUN->updDoubl();
        SignalSlotCommutator::emitUpdUN();

        return true;
    }

    QMap<int, QString> mapDKCiclStatus = {
        {0,"DKIgnore"},
        {1,"DKReady"},
        {2,"DKNorm"},
        {3,"DKWasAlarn"},
        {4,"DKWas"},
        {5,"DKDone"},
        {-1,"DKWrong"}
    };

    qDebug() << "DkStatus --> " << currentUN->toString();
    auto unCalcDkStatus = currentUN->calcDKStatus();
    qDebug() << "DkStatus -- unCalcDkStatus " << mapDKCiclStatus.value(unCalcDkStatus);
    qDebug() << "DkStatus -- unDkStatus " << mapDKCiclStatus.value(currentUN->getDkStatus());
    qDebug() << "DkStatus -- unDkStatus " << mapDKCiclStatus.value(previousUN->getDkStatus());
    if(DKCiclStatus::DKReady == previousUN->getDkStatus() &&
            DKCiclStatus::DKNorm == unCalcDkStatus)
        currentUN->setDkStatus(DKCiclStatus::DKNorm);
    else if((DKCiclStatus::DKNorm == previousUN->getDkStatus() || DKCiclStatus::DKReady == previousUN->getDkStatus())&&
            DKCiclStatus::DKWasAlarm == unCalcDkStatus)
        currentUN->setDkStatus(DKCiclStatus::DKWasAlarm);
    else if(DKCiclStatus::DKWasAlarm == previousUN->getDkStatus() &&
            DKCiclStatus::DKNorm == unCalcDkStatus)
        currentUN->setDkStatus(DKCiclStatus::DKDone);
    else if(DKCiclStatus::DKWasAlarm == previousUN->getDkStatus() &&
            DKCiclStatus::DKWas == unCalcDkStatus)
        currentUN->setDkStatus(DKCiclStatus::DKDone);
    else if((DKCiclStatus::DKNorm == previousUN->getDkStatus() &&
             DKCiclStatus::DKNorm == unCalcDkStatus) ||
            (DKCiclStatus::DKWasAlarm == previousUN->getDkStatus() &&
             DKCiclStatus::DKWasAlarm == unCalcDkStatus))
        currentUN->setDkStatus(previousUN->getDkStatus());
    else
        currentUN->setDkStatus(DKCiclStatus::DKWrong);
    qDebug() << "DkStatus -- unNewDkStatus " << mapDKCiclStatus.value(currentUN->getDkStatus());

    currentUN->updDoubl();
    SignalSlotCommutator::emitUpdUN();

    qDebug() << "DkStatus <--";
    qDebug() << "PortManager::procDkBLIPStatusWord0x41(2) <--";
    return true;
}
