#include "HandlerStateWord0x33.h"

#include "ProcessingStateWord0x33SOTABOD.h"
#include "ProcessingStateWord0x33SOTADD.h"
#include "ProcessingStateWord0x33SOTADK.h"
#include "ProcessingStateWord0x33SOTAY4.h"
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
//        qDebug() << "ProcessingStateWord0x33T4KDK()::processing() --x";
    } else if( ProcessingStateWord0x33SOTADK(data, un).ProcessingStateWordAbstract::processing() ) {
//        qDebug() << "ProcessingStateWord0x33SOTADK()::processing() --x";
    } else if( ProcessingStateWord0x33TGDK(data, un).ProcessingStateWordAbstract::processing() ) {
//        qDebug() << "ProcessingStateWord0x33TGDK()::processing() --x";
    } else if( ProcessingStateWord0x33T4KBOD(data, un).ProcessingStateWordAbstract::processing() ) {
//        qDebug() << "ProcessingStateWord0x33T4KBOD()::processing() --x";
    } else if( ProcessingStateWord0x33SOTABOD(data, un).ProcessingStateWordAbstract::processing() ) {
//        qDebug() << "ProcessingStateWord0x33SOTABOD()::processing() --x";
    } else if( ProcessingStateWord0x33T4KY4(data, un).ProcessingStateWordAbstract::processing() ) {
//        qDebug() << "ProcessingStateWord0x33T4KY4()::processing() --x";
    } else if( ProcessingStateWord0x33SOTAY4(data, un).ProcessingStateWordAbstract::processing() ) {
//        qDebug() << "ProcessingStateWord0x33SOTAY4()::processing() --x";
    } else if( ProcessingStateWord0x33T4KDD(data, un).ProcessingStateWordAbstract::processing() ) {
//        qDebug() << "ProcessingStateWord0x33T4KDD()::processing() --x";
    } else if( ProcessingStateWord0x33SOTADD(data, un).ProcessingStateWordAbstract::processing() ) {
//        qDebug() << "ProcessingStateWord0x33SOTADD()::processing() --x";
    } else if( ProcessingStateWord0x33TG(data, un).ProcessingStateWordAbstract::processing() ) {
//        qDebug() << "ProcessingStateWord0x33TG()::processing() --x";
    } else {
//        qDebug() << "HandlerStateWord0x33()::onHandler() --x";
    }
}
