#include "ManagerSingleMsg.h"
#include "DataQueueItem.h"
#include "UnitNode.h"

ManagerSingleMsg::ManagerSingleMsg(const QSharedPointer<UnitNode> &target, QByteArray(*maker)(const QSharedPointer<UnitNode>)) :
    QObject(nullptr),
    target(target),
    maker(maker)
{

}

DataQueueItem ManagerSingleMsg::makeDatagram() const
{
    DataQueueItem result;

    auto reciver = UnitNode::findReciver(target);
    if(reciver.isNull()) {
        return result;
    }

    result.setPort(reciver->getUdpPort());
    result.setAddress(Utils::hostAddress(reciver->getUdpAdress()));
    result.setData(maker(target));

    if(nullptr != target && target->isNeedsPreamble())
        result.setPreamble(QByteArray().fill(static_cast<quint8>(0xFF), 3));

    return result;
}

bool ManagerSingleMsg::equale(const ManagerSingleMsg &rhs) const
{
    if(!target->equale(*(rhs.target.data())))
        return false;
    else if(maker != rhs.maker)
        return false;

    return true;
}

bool equale(const ManagerSingleMsg &lhs, const ManagerSingleMsg &rhs) {
    if(!lhs.target->equale(*(rhs.target.data())))
        return false;
    else if(lhs.maker != rhs.maker)
        return false;

    return true;
}

bool equale(const QSharedPointer<ManagerSingleMsg> &lhs, const QSharedPointer<ManagerSingleMsg> &rhs) {
    if(!lhs->target->equale(*(rhs->target.data())))
        return false;
    else if(lhs->maker != rhs->maker)
        return false;

    return true;
}


void ManagerSingleMsg::accident(){

}

void ManagerSingleMsg::incident() {

}

void ManagerSingleMsg::planned() {

}

void ManagerSingleMsg::accept() {

}

void ManagerSingleMsg::reject() {

}
