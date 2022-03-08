#include "HandlerStateWord0x42.h"
#include "./blip/ProcessingStateWord0x42BLIPDK.h"
#include "./blip/ProcessingStateWord0x42BLIPIU.h"
#include "./blip/ProcessingStateWord0x42BLIPSD.h"
#include "./blip/ProcessingStateWord0x42BLIPUzo.h"
#include "./ssoiblip/ProcessingStateWord0x42SSOIBLIPDK.h"
#include "./ssoiblip/ProcessingStateWord0x42SSOIBLIPIU.h"
#include "./ssoiblip/ProcessingStateWord0x42SSOIBLIPSD.h"
#include "./ssoiblip/ProcessingStateWord0x42SSOIBLIPUzo.h"

HandlerStateWord0x42::HandlerStateWord0x42(const DataQueueItem &dataItem) :
    HandlerStateWordAbstract(dataItem)
{

}

HandlerStateWord0x42::~HandlerStateWord0x42()
{

}

void HandlerStateWord0x42::onHandler(const StateWord &data, const QSharedPointer<UnitNode> &un) const
{
    if( ProcessingStateWord0x42BLIPDK(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x42SSOIBLIPDK(data, un).ProcessingStateWordAbstract::processing() ) {

//    } else if( ProcessingStateWord0x42BLIPUzo(data, un).ProcessingStateWordAbstract::processing() ) {

//    } else if( ProcessingStateWord0x42SSOIBLIPUzo(data, un).ProcessingStateWordAbstract::processing() ) {

//    } else if( ProcessingStateWord0x42BLIPIU(data, un).ProcessingStateWordAbstract::processing() ) {

//    } else if( ProcessingStateWord0x42SSOIBLIPIU(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x42BLIPSD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else if( ProcessingStateWord0x42SSOIBLIPSD(data, un).ProcessingStateWordAbstract::processing() ) {

    } else {

    }
}
