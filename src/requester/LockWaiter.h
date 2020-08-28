#ifndef LOCKWAITER_H
#define LOCKWAITER_H

#include "AbstractPort.h"
#include <AbstractRequester.h>
#include "DataQueueItem.h"

#include <QObject>
#include <QTimer>
#include <Utils.h>
#include <QDebug>

#include <UnitNode.h>

class LockWaiter final : public AbstractRequester
{
private:
    UnitNode * unReciverIuBlIp = nullptr;
    UnitNode * unReciverSdBlIp = nullptr;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

public:
    explicit LockWaiter(UnitNode * target, RequesterType requesterType = RequesterType::DKWaiter);
    virtual ~LockWaiter();

    virtual void init() override;

};

#endif // LOCKWAITER_H
