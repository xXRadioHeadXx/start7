#ifndef PROCESSDKWAITER_H
#define PROCESSDKWAITER_H

#include <AbstractRequester.h>

class ProcessDKWaiter final : public AbstractRequester
{
private:
    QList<UnitNode *> lsTrackedUN;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

public:
    explicit ProcessDKWaiter(UnitNode * target, RequesterType requesterType = RequesterType::DKWaiter);
    virtual ~ProcessDKWaiter();

    virtual void init() override;

    QList<UnitNode *> getLsTrackedUN() const;
    void setLsTrackedUN(const QList<UnitNode *> &value);
    void addLsTrackedUN(UnitNode *value);
};

#endif // PROCESSDKWAITER_H
