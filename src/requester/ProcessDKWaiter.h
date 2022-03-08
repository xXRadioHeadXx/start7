#ifndef PROCESSDKWAITER_H
#define PROCESSDKWAITER_H

#include "AbstractRequester.h"

class ProcessDKWaiter final : public AbstractRequester
{
private:
    QList<QSharedPointer<UnitNode> > lsTrackedUN;
    const bool isAuto;
    const bool fromAbonent;
protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

public:
    explicit ProcessDKWaiter(const bool isAuto, const bool fromAbonent, QSharedPointer<UnitNode>  target, RequesterType requesterType = RequesterType::DKWaiter);
    virtual ~ProcessDKWaiter();

    virtual void init() override;

    QList<QSharedPointer<UnitNode> > getLsTrackedUN() const;
    void setLsTrackedUN(const QList<QSharedPointer<UnitNode> > &value);
    void addLsTrackedUN(QSharedPointer<UnitNode> value);
    bool removeLsTrackedUN(const QSharedPointer<UnitNode> value);
    const QList<QSharedPointer<UnitNode> > & getLsTrackedUN();
};

#endif // PROCESSDKWAITER_H
