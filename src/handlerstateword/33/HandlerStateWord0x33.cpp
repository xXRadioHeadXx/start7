#include "HandlerStateWord0x33.h"

#include "ProcessingStateWord0x33T4KBOD.h"
#include "ProcessingStateWord0x33T4KDD.h"
#include "ProcessingStateWord0x33T4KDK.h"
#include "ProcessingStateWord0x33TG.h"
#include "ProcessingStateWord0x33TGDK.h"
#include "ProcessingStateWord0x33T4KY4.h"

HandlerStateWord0x33::HandlerStateWord0x33(const DataQueueItem &dataItem) :
    HandlerStateWordAbstract(dataItem)
{

}

HandlerStateWord0x33::~HandlerStateWord0x33()
{

}

void HandlerStateWord0x33::onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const
{
    if( ProcessingStateWord0x33T4KDK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x33TGDK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x33T4KBOD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x33T4KY4(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x33T4KDD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x33TG(data, un).ProcessingStateWordAbstract::processing() ) {

    } else {

    }
}
