#ifndef PROCESSDKWAITER_H
#define PROCESSDKWAITER_H

#include "AbstractPort.h"
#include <AbstractRequester.h>
#include "DataQueueItem.h"

#include <QObject>
#include <QTimer>
#include <Utils.h>
#include <QDebug>

#include <UnitNode.h>

class ProcessDKWaiter final : public AbstractRequester
{
private:
    QList<UnitNode *> lsTrackedUN;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;

public:
    explicit ProcessDKWaiter(UnitNode * target, RequesterType requesterType = RequesterType::DKWaiter);
    virtual ~ProcessDKWaiter();

    virtual void init() override;

    QList<UnitNode *> getLsTrackedUN() const;
    void setLsTrackedUN(const QList<UnitNode *> &value);
    void addLsTrackedUN(UnitNode *value);
};

#endif // PROCESSDKWAITER_H
