#include "ManagerSingleMsgAlarmReset.h"

ManagerSingleMsgAlarmReset::ManagerSingleMsgAlarmReset(const QSharedPointer<UnitNode> &target, QByteArray(*maker)(const QSharedPointer<UnitNode>)) :
    ManagerSingleMsg(target, maker)
{

}

DataQueueItem ManagerSingleMsgAlarmReset::makeDatagram() const
{
    DataQueueItem result;

    auto reciver = UnitNode::findReciver(target);
    if(reciver.isNull()) {
        return result;
    }

    result.setPort(reciver->getUdpPort());
    result.setAddress(Utils::hostAddress(reciver->getUdpAdress()));
    result.setData(maker(target));

    return result;
}
