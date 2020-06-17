#include "StatusRequester.h"

StatusRequester::StatusRequester(QObject * parent) : QObject(parent)
{
    msg = DataQueueItem::makeStatusRequest0x22();

}

StatusRequester::~StatusRequester()
{
    timerStatusRequest.stop();
}

void StatusRequester::startStatusRequest(){
    timerStatusRequest.stop();

    timerStatusRequest.singleShot(timeIntervalStatusRequest, this, SLOT(beatStatusRequest()));
}

void StatusRequester::beatStatusRequest() {
    DataQueueItem itm(msg, QHostAddress(ipPort.first), QVariant(ipPort.second).toInt(), portIndex);

    Port::typeDefPort(ptrPort)->write(itm, false);
    beatCount++;

    timerStatusRequest.singleShot(timeIntervalStatusRequest, this, SLOT(beatStatusRequest()));
}
