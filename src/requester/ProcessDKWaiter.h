#ifndef PROCESSDKWAITER_H
#define PROCESSDKWAITER_H

#include "AbstractRequester.h"

class ProcessDKWaiter final : public AbstractRequester
{
private:
    QList<QSharedPointer<UnitNode> > lsTrackedUN;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

public:
    explicit ProcessDKWaiter(QSharedPointer<UnitNode>  target, RequesterType requesterType = RequesterType::DKWaiter);
    virtual ~ProcessDKWaiter();

    virtual void init() override;

    QList<QSharedPointer<UnitNode> > getLsTrackedUN() const;
    void setLsTrackedUN(const QList<QSharedPointer<UnitNode> > &value);
    void addLsTrackedUN(QSharedPointer<UnitNode> value);
};

#endif // PROCESSDKWAITER_H
