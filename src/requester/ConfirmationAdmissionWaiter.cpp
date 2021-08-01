#include "ConfirmationAdmissionWaiter.h"

#include "PortManager.h"
#include "Utils.h"
#include "global.h"

ConfirmationAdmissionWaiter::ConfirmationAdmissionWaiter(QSharedPointer<UnitNode>  target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
//    qDebug() << "ConfirmationAdmissionWaiter::ConfirmationAdmissionWaiter(" << this << ") -->";
}

ConfirmationAdmissionWaiter::~ConfirmationAdmissionWaiter()
{
//    qDebug() << "ConfirmationAdmissionWaiter::~ConfirmationAdmissionWaiter(" << this << ") <--";
}

void ConfirmationAdmissionWaiter::init()
{
    if(!getUnTarget().isNull()) {
        setUnReciver(UnitNode::findReciver(getUnTarget()));
    }

    if(getUnTarget().isNull() || getUnReciver().isNull())
        return;

    setIpPort(QPair<QString, QString>(getUnReciver()->getUdpAdress(), QVariant(getUnReciver()->getUdpPort()).toString()));

    for(AbstractPort * pt : as_const(PortManager::getUdpPortsVector())) {
        if(Port::typeDefPort(pt)->getStIpPort().end() != Port::typeDefPort(pt)->getStIpPort().find(getIpPort())) {
            setPtrPort(pt);
            setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
            break;
        }
    }

    setTimeIntervalWaiteFirst(0);
    setTimeIntervalRequest(500);

    DataQueueItem result;

    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    setFirstMsg(result);
}

DataQueueItem ConfirmationAdmissionWaiter::makeFirstMsg()
{
    return getFirstMsg();
}

DataQueueItem ConfirmationAdmissionWaiter::makeSecondMsg() {
    return getSecondMsg();
}

DataQueueItem ConfirmationAdmissionWaiter::makeEndMsg()
{
    return getEndMsg();
}
