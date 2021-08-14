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

    result.setPort(target->getUdpPort());
    result.setAddress(Utils::hostAddress(target->getUdpAdress()));
    result.setData(maker(target));

    return result;
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
