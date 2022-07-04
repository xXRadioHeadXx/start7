#include "HandlerStateWord0x34.h"
#include "../src/handlerstateword/34/sota/ProcessingStateWord0x34SOTADD.h"
#include "../src/handlerstateword/34/t4k/ProcessingStateWord0x34T4KDD.h"
#include "../src/handlerstateword/34/tg/ProcessingStateWord0x34TG.h"
#include "../src/handlerstateword/34/tg/ProcessingStateWord0x34TGDK.h"

HandlerStateWord0x34::HandlerStateWord0x34(const DataQueueItem &dataItem) :
    HandlerStateWordAbstract(dataItem)
{

}

HandlerStateWord0x34::~HandlerStateWord0x34()
{

}

void HandlerStateWord0x34::onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const
{
    if( ProcessingStateWord0x34TGDK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x34TG(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x34T4KDD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x34SOTADD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else {

    }

}
