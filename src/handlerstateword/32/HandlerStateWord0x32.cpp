#include "HandlerStateWord0x32.h"
#include "ProcessingStateWord0x32T4KBOD.h"
#include "ProcessingStateWord0x32T4KDD.h"
#include "ProcessingStateWord0x32T4KDK.h"
#include "ProcessingStateWord0x32TG.h"
#include "ProcessingStateWord0x32TGDK.h"
#include "ProcessingStateWord0x32T4KY4.h"

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

    } else if( ProcessingStateWord0x32TGDK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32T4KBOD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32T4KY4(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32T4KDD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x32TG(data, un).ProcessingStateWordAbstract::processing() ) {

    } else {

    }
}
