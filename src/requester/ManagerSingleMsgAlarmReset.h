#ifndef MANAGERSINGLEMSGALARMRESET_H
#define MANAGERSINGLEMSGALARMRESET_H

#include "../src/requester/ManagerSingleMsg.h"

#include "../src/port/DataQueueItem.h"

class ManagerSingleMsgAlarmReset : public ManagerSingleMsg
{
public:
    ManagerSingleMsgAlarmReset(const QSharedPointer<UnitNode> &target, QByteArray (*maker)(const QSharedPointer<UnitNode>) = DataQueueItem::makeResetFlags0x24);

};

#endif // MANAGERSINGLEMSGALARMRESET_H
