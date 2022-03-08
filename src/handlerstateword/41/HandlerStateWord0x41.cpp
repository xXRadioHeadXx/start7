#include "HandlerStateWord0x41.h"
#include "./blip/ProcessingStateWord0x41BLIPDK.h"
#include "./blip/ProcessingStateWord0x41BLIPIU.h"
#include "./blip/ProcessingStateWord0x41BLIPSD.h"
#include "./blip/ProcessingStateWord0x41BLIPUzo.h"
#include "./ssoiblip/ProcessingStateWord0x41SSOIBLIPDK.h"
#include "./ssoiblip/ProcessingStateWord0x41SSOIBLIPIU.h"
#include "./ssoiblip/ProcessingStateWord0x41SSOIBLIPSD.h"
#include "./ssoiblip/ProcessingStateWord0x41SSOIBLIPUzo.h"

 HandlerStateWord0x41::HandlerStateWord0x41(const DataQueueItem & dataItem) :
    HandlerStateWordAbstract(dataItem)
{

}

HandlerStateWord0x41::~HandlerStateWord0x41()
{

}

void HandlerStateWord0x41::onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const
{
    if( ProcessingStateWord0x41BLIPDK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x41SSOIBLIPDK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x41BLIPUzo(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x41SSOIBLIPUzo(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x41BLIPIU(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x41SSOIBLIPIU(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x41BLIPSD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x41SSOIBLIPSD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else {

    }
}
