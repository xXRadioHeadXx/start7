#include "OnOffIUWaiter.h"
#include "SignalSlotCommutator.h"

#include <PortManager.h>
#include <Utils.h>
#include <global.h>

OnOffIUWaiter::OnOffIUWaiter(QSharedPointer<UnitNode>  target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
    //qDebug() << "OnOffIUWaiter::OnOffIUWaiter(" << this << ") -->";
}

OnOffIUWaiter::~OnOffIUWaiter()
{
    //qDebug() << "OnOffIUWaiter::~OnOffIUWaiter(" << this << ") <--";
}

void OnOffIUWaiter::init()
{
    if(nullptr != getUnTarget()) {
        QSharedPointer<UnitNode>  un = getUnTarget();
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

    for(AbstractPort * pt : as_const(PortManager::getUdpPortsVector())) {
        if(Port::typeDefPort(pt)->getStIpPort().contains(getIpPort())) {
            setPtrPort(pt);
            setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
            break;
        }
    }

    int interval = UnitNodeCFG::adamOffToMs(getUnTarget()->getAdamOff());

    setTimeIntervalWaiteFirst(interval);
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

    if(nullptr != getUnTarget() && TypeUnitNode::RLM_C == getUnTarget()->getType())
        result.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));

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

    if(nullptr != getUnTarget() && TypeUnitNode::RLM_C == getUnTarget()->getType())
        result.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));

    if(result.isValid())
        return result;

    return DataQueueItem();
}

DataQueueItem OnOffIUWaiter::makeEndMsg()
{
    return DataQueueItem();
}
