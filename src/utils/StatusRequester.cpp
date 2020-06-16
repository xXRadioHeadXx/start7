#include "StatusRequester.h"

StatusRequester::StatusRequester(QObject * parent) : QObject(parent)
{

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

    Utils::typeDefPort(ptrPort)->write(itm, false);
    beatCount++;

    timerStatusRequest.singleShot(timeIntervalStatusRequest, this, SLOT(beatStatusRequest()));
}
