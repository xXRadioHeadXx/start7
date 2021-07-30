#ifndef PROCESSDKWAITER_H
#define PROCESSDKWAITER_H

#include "AbstractRequester.h"

class ProcessDKWaiter final : public AbstractRequester
{
private:
    std::list<QSharedPointer<UnitNode> > lsTrackedUN;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

public:
    explicit ProcessDKWaiter(QSharedPointer<UnitNode>  target, RequesterType requesterType = RequesterType::DKWaiter);
    virtual ~ProcessDKWaiter();

    virtual void init() override;

    std::list<QSharedPointer<UnitNode> > getLsTrackedUN() const;
    void setLsTrackedUN(const std::list<QSharedPointer<UnitNode> > &value);
    void addLsTrackedUN(QSharedPointer<UnitNode> value);
    bool removeLsTrackedUN(const QSharedPointer<UnitNode> value);
    const std::list<QSharedPointer<UnitNode> > & getLsTrackedUN();
};

#endif // PROCESSDKWAITER_H
