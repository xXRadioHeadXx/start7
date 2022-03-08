#include "HandlerStateWord0x31.h"

#include "./rlm/ProcessingStateWord0x31RLM.h"
#include "./rlmc/ProcessingStateWord0x31RLMC.h"
#include "./tg/ProcessingStateWord0x31TG.h"
#include "ProcessingStateWord0x31DK.h"

HandlerStateWord0x31::HandlerStateWord0x31(const DataQueueItem &dataItem) :
    HandlerStateWordAbstract(dataItem)
{

}

HandlerStateWord0x31::~HandlerStateWord0x31()
{

}

void HandlerStateWord0x31::onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const
{
    if( ProcessingStateWord0x31DK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x31RLM(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x31RLMC(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x31TG(data, un).ProcessingStateWordAbstract::processing() ) {

    } else {

    }
}
