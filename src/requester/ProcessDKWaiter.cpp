#include "ProcessDKWaiter.h"
#include "SignalSlotCommutator.h"

#include "PortManager.h"
#include "Utils.h"
#include "global.h"

#include "SWPBLIP.h"
#include "SWPSDBLIP.h"
#include "SWPIUBLIP.h"
#include "SWPRLM.h"
#include "SWPRLMC.h"
#include "SWPTGType0x32.h"
#include "SWPTGType0x33.h"

ProcessDKWaiter::ProcessDKWaiter(QSharedPointer<UnitNode>  target, RequesterType requesterType) : AbstractRequester(target, requesterType)
{
    //qDebug() << "ProcessDKWaiter::ProcessDKWaiter(" << this << ") -->";
}

ProcessDKWaiter::~ProcessDKWaiter()
{
    //qDebug() << "ProcessDKWaiter::~ProcessDKWaiter(" << this << ") <--";
    Port::typeDefPort(getPtrPort())->setProcDK(false);
    if(TypeUnitNode::BL_IP == getUnReciver()->getType()) {
        getUnReciver()->setDkInvolved(false);
    }
}

QList<QSharedPointer<UnitNode> > ProcessDKWaiter::getLsTrackedUN() const
{
    return lsTrackedUN;
}

void ProcessDKWaiter::setLsTrackedUN(const QList<QSharedPointer<UnitNode> > &value)
{
    lsTrackedUN = value;
}

void ProcessDKWaiter::addLsTrackedUN(QSharedPointer<UnitNode> value)
{
    lsTrackedUN.append(value);
    //    qDebug() << "ProcessDKWaiter::addLsTrackedUN(" << value->toString() << ")";
}

bool ProcessDKWaiter::removeLsTrackedUN(const QSharedPointer<UnitNode> value)
{
    return 0 != lsTrackedUN.removeAll(value);
    //    qDebug() << "ProcessDKWaiter::addLsTrackedUN(" << value->toString() << ")";
}


const QList<QSharedPointer<UnitNode> > &ProcessDKWaiter::getLsTrackedUN()
{
    return lsTrackedUN;
}

DataQueueItem ProcessDKWaiter::makeFirstMsg() {
    qDebug() << "DataQueueItem ProcessDKWaiter::makeFirstMsg() -->";
    DataQueueItem result;
    if(nullptr == getPtrPort() || getUnReciver().isNull()) {
        qDebug() << "DataQueueItem ProcessDKWaiter::makeFirstMsg() <--";
        return result;
    }

    int isWasDK = -1, isExistDK = -1;
    if(TypeUnitNode::SD_BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::IU_BL_IP == getUnReciver()->getType() ||
       TypeUnitNode::BL_IP == getUnReciver()->getType()) {
        isWasDK = getUnReciver()->swpBLIP().isWasDK();
        isExistDK = getUnReciver()->swpBLIP().isExistDK();
    } else if(TypeUnitNode::RLM_KRL == getUnReciver()->getType()) {
        isWasDK = getUnReciver()->swpRLM().isWasDK();
        isExistDK = getUnReciver()->swpRLM().isExistDK();
    } else if(TypeUnitNode::RLM_C == getUnReciver()->getType()) {
        isWasDK = getUnReciver()->swpRLMC().isWasDK();
        isExistDK = getUnReciver()->swpRLMC().isExistDK();
    } else if(TypeUnitNode::TG == getUnReciver()->getType()) {
        const auto swp32 = getUnReciver()->swpTGType0x32();
        const auto swp33 = getUnReciver()->swpTGType0x33();
        if(!swp32.isNull() && !swp32.isNull() && (swp32.cdate() >= swp33.cdate())) {
            isWasDK = swp32.isWasDK();
            isExistDK = swp32.isExistDK();
        } else if(!swp33.isNull()) {
            isWasDK = swp33.isWasDK();
            isExistDK = swp33.isExistDK();
        } else if(!swp32.isNull()) {
            isWasDK = swp32.isWasDK();
            isExistDK = swp32.isExistDK();
        }
    }
    if(1 == isExistDK) {
        qDebug() << "DataQueueItem ProcessDKWaiter::makeFirstMsg() <--";
        return DataQueueItem();
    }

    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    DataQueueItem::makeDK0x21(result, getUnReciver());

    if(result.isValid()) {
        qDebug() << "DataQueueItem ProcessDKWaiter::makeFirstMsg() <--";
        return result;
    }

    qDebug() << "DataQueueItem ProcessDKWaiter::makeFirstMsg() <--";
    return DataQueueItem();
}

DataQueueItem ProcessDKWaiter::makeSecondMsg() {
    qDebug() << "DataQueueItem ProcessDKWaiter::makeSecondMsg() -->";
    DataQueueItem result;
    if(nullptr == getPtrPort() || getUnReciver().isNull()) {
        qDebug() << "DataQueueItem ProcessDKWaiter::makeSecondMsg() <--";
        return result;
    }

    if(TypeUnitNode::RLM_C == getUnReciver()->getType() || TypeUnitNode::RLM_KRL == getUnReciver()->getType()) {
        qDebug() << "DataQueueItem ProcessDKWaiter::makeSecondMsg() <--";
        return result;
    }

    result.setPort(getUnReciver()->getUdpPort());
    result.setAddress(Utils::hostAddress(getUnReciver()->getUdpAdress()));
    result.setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());

    DataQueueItem::makeAlarmReset0x24(result, getUnReciver());

    if(result.isValid()) {
        qDebug() << "DataQueueItem ProcessDKWaiter::makeSecondMsg() <--";
        return result;
    }

    qDebug() << "DataQueueItem ProcessDKWaiter::makeSecondMsg() <--";
    return DataQueueItem();
}

DataQueueItem ProcessDKWaiter::makeEndMsg()
{
    return DataQueueItem();
}

void ProcessDKWaiter::init() {
    if(!getUnTarget().isNull()) {
        setUnReciver(UnitNode::findReciver(getUnTarget()));
    }

    if(getUnTarget().isNull() || getUnReciver().isNull())
        return;

    setIpPort(QPair<QString, QString>(getUnReciver()->getUdpAdress(), QVariant(getUnReciver()->getUdpPort()).toString()));

    for(AbstractPort * pt : as_const(PortManager::getUdpPortsVector())) {
        if(Port::typeDefPort(pt)->getStIpPort().contains(getIpPort())) {
            setPtrPort(pt);
            setPortIndex(Port::typeDefPort(getPtrPort())->getPortIndex());
            break;
        }
    }

    if(TypeUnitNode::BL_IP == getUnReciver()->getType()) {
        for(QSharedPointer<UnitNode>  uncld : as_const(getUnReciver()->getListChilde())) {
            if(0 != uncld->getDK() && (TypeUnitNode::SD_BL_IP == uncld->getType() /* или датчик */)) {
                uncld->setDkInvolved(true);
                uncld->setDkStatus(DKCiclStatus::DKReady);
                uncld->updDoubl();
                addLsTrackedUN(uncld);
            }
        }
        getUnReciver()->setDkInvolved(true);
    } else if(TypeUnitNode::TG_Base == getUnReciver()->getType()) {
        for(QSharedPointer<UnitNode>  uncld : as_const(getUnReciver()->getListChilde())) {
            if(TypeUnitNode::TG == uncld->getType() /* или датчик */) {
                uncld->setDkInvolved(true);
                uncld->setDkStatus(DKCiclStatus::DKReady);
                uncld->updDoubl();
                addLsTrackedUN(uncld);
            }
        }
        getUnReciver()->setDkInvolved(true);
    } else if(TypeUnitNode::RLM_C == getUnReciver()->getType() ||
              TypeUnitNode::RLM_KRL == getUnReciver()->getType()) {
        getUnReciver()->setDkInvolved(true);
        getUnReciver()->setDkStatus(DKCiclStatus::DKReady);
        getUnReciver()->updDoubl();
        addLsTrackedUN(getUnReciver());
    }

    setTimeIntervalWaiteFirst(11000);
    setTimeIntervalRequest(500);

    connect(this, SIGNAL(importantBeatStatus()), SignalSlotCommutator::getInstance(), SLOT(emitEndDKWait()));
}
