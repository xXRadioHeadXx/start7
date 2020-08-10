#ifndef STATUSCONNECTREQUESTER_H
#define STATUSCONNECTREQUESTER_H

#include "AbstractPort.h"
#include <AbstractRequester.h>
#include "DataQueueItem.h"

#include <AbstractRequester.h>
#include <Utils.h>
#include <QDebug>

#include <UnitNode.h>

class StatusConnectRequester final : public AbstractRequester
{
private:
    QList<UnitNode *> lsTrackedUN;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;

public:
    explicit StatusConnectRequester(UnitNode * target, RequesterType requesterType = RequesterType::ConnectRequester);
    virtual ~StatusConnectRequester();

    virtual void init() override;

    QList<UnitNode *> getLsTrackedUN() const;
    void setLsTrackedUN(const QList<UnitNode *> &value);
    void addLsTrackedUN(UnitNode *value);


};

#endif // STATUSCONNECTREQUESTER_H
