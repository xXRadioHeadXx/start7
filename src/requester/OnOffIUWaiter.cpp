#include "OnOffIUWaiter.h"
#include "SignalSlotCommutator.h"

#include <PortManager.h>
#include <Utils.h>

OnOffIUWaiter::OnOffIUWaiter(UnitNode * target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
    qDebug() << "ProcessDKWaiter::ProcessDKWaiter";
}

OnOffIUWaiter::~OnOffIUWaiter()
{
//    qDebug() << "ProcessDKWaiter::~ProcessDKWaiter()";
}

void OnOffIUWaiter::init()
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

    int interval;
    switch (getUnTarget()->getAdamOff()) {
        case 0:
            interval = 0;
            break;
        case 1:
            interval = 5000;
            break;
        case 2:
            interval = 10000;
            break;
        case 3:
            interval = 30000;
            break;
        case 4:
            interval = 60000;
            break;
        case 5:
            interval = 300000;
            break;
        case 6:
            interval = 600000;
            break;
        case 7:
            interval = 1200000;
            break;
        case 8:
            interval = 2400000;
            break;
        case 9:
            interval = 3600000;
            break;
        default:
            interval = 0;
            break;
    }

    setTimeIntervalWaite(interval);
    setTimeIntervalRequest(500);
}

DataQueueItem OnOffIUWaiter::makeFirstMsg()
{
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == getUnReciver())
        return result;

    result.setData(DataQueueItem::makeOnOff0x23(getUnTarget(), true, getUnReciver()));
    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(result.isValid())
        return result;

    return DataQueueItem();
}

DataQueueItem OnOffIUWaiter::makeSecondMsg() {
    DataQueueItem result;
    if(nullptr == getPtrPort() || nullptr == getUnReciver())
        return result;

    result.setData(DataQueueItem::makeOnOff0x23(getUnTarget(), false, getUnReciver()));
    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    if(result.isValid())
        return result;

    return DataQueueItem();
}
