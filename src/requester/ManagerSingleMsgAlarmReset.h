#ifndef MANAGERSINGLEMSGALARMRESET_H
#define MANAGERSINGLEMSGALARMRESET_H

#include "ManagerSingleMsg.h"

#include "DataQueueItem.h"

class ManagerSingleMsgAlarmReset : public ManagerSingleMsg
{
public:
    ManagerSingleMsgAlarmReset(const QSharedPointer<UnitNode> &target, QByteArray (*maker)(const QSharedPointer<UnitNode>) = DataQueueItem::makeAlarmReset0x24);

    virtual DataQueueItem makeDatagram() const final;

};

#endif // MANAGERSINGLEMSGALARMRESET_H
