#ifndef ONOFFIUWAITER_H
#define ONOFFIUWAITER_H

#include "../src/requester/AbstractRequester.h"

class OnOffIUWaiter final : public AbstractRequester
{
    const bool isAuto;
    const bool fromAbonent;
public:
    explicit OnOffIUWaiter(const bool isAuto, const bool fromAbonent, QSharedPointer<UnitNode>  target, RequesterType requesterType = RequesterType::AutoOnOffWaiter);
    virtual ~OnOffIUWaiter();
    virtual void init() override;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

};

#endif // ONOFFIUWAITER_H
