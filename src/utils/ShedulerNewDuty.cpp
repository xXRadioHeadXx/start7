#include "ShedulerNewDuty.h"

#include "../src/database/DataBaseManager.h"
#include "../src/port/GraphTerminal.h"
#include "../src/entity/JourEntity.h"
#include "../src/utils/SignalSlotCommutator.h"

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
