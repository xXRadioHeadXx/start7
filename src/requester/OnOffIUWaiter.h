#ifndef ONOFFIUWAITER_H
#define ONOFFIUWAITER_H

#include <AbstractRequester.h>

class OnOffIUWaiter final : public AbstractRequester
{
public:
    explicit OnOffIUWaiter(UnitNode * target, RequesterType requesterType = RequesterType::AutoOnOffWaiter);
    virtual ~OnOffIUWaiter();
    virtual void init() override;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

};

#endif // ONOFFIUWAITER_H
