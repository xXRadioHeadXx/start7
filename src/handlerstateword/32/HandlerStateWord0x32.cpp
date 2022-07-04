#include "HandlerStateWord0x32.h"
#include "../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTABOD.h"
#include "../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTADD.h"
#include "../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTADK.h"
#include "../src/handlerstateword/32/sota/ProcessingStateWord0x32SOTAY4.h"
#include "../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KBOD.h"
#include "../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KDD.h"
#include "../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KDK.h"
#include "../src/handlerstateword/32/tg/ProcessingStateWord0x32TG.h"
#include "../src/handlerstateword/32/tg/ProcessingStateWord0x32TGDK.h"
#include "../src/handlerstateword/32/t4k/ProcessingStateWord0x32T4KY4.h"

HandlerStateWord0x32::HandlerStateWord0x32(const DataQueueItem &dataItem) :
    HandlerStateWordAbstract(dataItem)
{

}

HandlerStateWord0x32::~HandlerStateWord0x32()
{

}

void HandlerStateWord0x32::onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const
{
    if( ProcessingStateWord0x32T4KDK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else  if( ProcessingStateWord0x32SOTADK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32TGDK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32T4KBOD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32SOTABOD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32T4KY4(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32SOTAY4(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32T4KDD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32SOTADD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32TG(data, un).ProcessingStateWordAbstract::processing() ) {

    } else {

    }
}
