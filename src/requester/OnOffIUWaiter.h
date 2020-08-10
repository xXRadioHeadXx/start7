#ifndef ONOFFIUWAITER_H
#define ONOFFIUWAITER_H

#include "AbstractPort.h"
#include <AbstractRequester.h>
#include "DataQueueItem.h"

#include <QObject>
#include <QTimer>
#include <Utils.h>
#include <QDebug>

#include <UnitNode.h>

class OnOffIUWaiter final : public AbstractRequester
{
public:
    explicit OnOffIUWaiter(UnitNode * target, RequesterType requesterType = RequesterType::AutoOnOffWaiter);
    virtual ~OnOffIUWaiter();
    virtual void init() override;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
};

#endif // ONOFFIUWAITER_H
