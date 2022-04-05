#include "ShedulerNewDuty.h"

#include "DataBaseManager.h"
#include "GraphTerminal.h"
#include "JourEntity.h"
#include "SignalSlotCommutator.h"

ShedulerNewDuty::ShedulerNewDuty(QTime runTime) :
    Sheduler(runTime)
{

}

void ShedulerNewDuty::regularRun() const
{
    JourEntity msg;
    msg.setObject(tr("Оператор"));
    msg.setType(902);
    msg.setComment(tr("Начата новая смена (Авто)"));
    msg.setType(902);
    msg.setFlag(0);

    QString sql = " update public.jour set flag = 0 where flag != 0 ;";
    DataBaseManager::executeQuery(sql);

    SignalSlotCommutator::emitInsNewJourMSG(msg);DataBaseManager::insertJourMsg_wS(msg);
    GraphTerminal::sendAbonentEventsAndStates(msg);

    DataBaseManager::setIdStartLastDuty();

    SignalSlotCommutator::emitUpdAllJourMSG();
    SignalSlotCommutator::emitUpdateLabelOperator();

}
