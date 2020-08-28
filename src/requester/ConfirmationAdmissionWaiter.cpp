#include "ConfirmationAdmissionWaiter.h"

#include <PortManager.h>
#include <Utils.h>

ConfirmationAdmissionWaiter::ConfirmationAdmissionWaiter(UnitNode * target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
//    qDebug() << "ConfirmationAdmissionWaiter::ConfirmationAdmissionWaiter";
}

ConfirmationAdmissionWaiter::~ConfirmationAdmissionWaiter()
{
//    qDebug() << "ConfirmationAdmissionWaiter::~ConfirmationAdmissionWaiter()";
}

void ConfirmationAdmissionWaiter::init()
{
    if(nullptr != getUnTarget()) {
        UnitNode * un = getUnTarget();
        while(nullptr != un) {
            if(TypeUnitNode::BL_IP == un->getType()) {
                setUnReciver(un);
                break;
            }
            un = un->getParentUN();
        }
    }

    if(nullptr == getUnTarget() || nullptr == getUnReciver())
        return;

    setIpPort(QPair<QString, QString>(getUnReciver()->getUdpAdress(), QVariant(getUnReciver()->getUdpPort()).toString()));

    for(AbstractPort * pt : PortManager::getUdpPortsVector()) {
        if(Port::typeDefPort(pt)->getStIpPort().contains(getIpPort())) {
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
