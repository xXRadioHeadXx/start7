#include "ManagerOneMsg.h"

ManagerOneMsg::ManagerOneMsg(const QSharedPointer<UnitNode> &target, QByteArray(*maker)(const QSharedPointer<UnitNode>)) :
    QObject(nullptr),
    target(target),
    maker(maker)
{

}

DataQueueItem ManagerOneMsg::makeDatagram() const
{
    DataQueueItem result;
    return result;
}
