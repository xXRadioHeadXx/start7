#include "ManagerSingleMsgAlarmReset.h"

ManagerSingleMsgAlarmReset::ManagerSingleMsgAlarmReset(const QSharedPointer<UnitNode> &target, QByteArray(*maker)(const QSharedPointer<UnitNode>)) :
    ManagerSingleMsg(target, maker)
{

}
