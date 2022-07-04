#ifndef STATUSCONNECTREQUESTER_H
#define STATUSCONNECTREQUESTER_H

#include "../src/port/AbstractPort.h"
#include "../src/requester/AbstractRequester.h"
#include "../src/port/DataQueueItem.h"

#include "../src/requester/AbstractRequester.h"
#include "../src/utils/Utils.h"
#include <QDebug>

#include "../src/entity/UnitNode.h"
#include "../src/entity/TypeUnitNode.h"

class StatusConnectRequester final : public AbstractRequester
{
private:
    QList<UnitNode *> lsTrackedUN;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

public:
    explicit StatusConnectRequester(UnitNode * target, RequesterType requesterType = RequesterType::ConnectRequester);
    virtual ~StatusConnectRequester();

    virtual void init() override;

    QList<UnitNode *> getLsTrackedUN() const;
    void setLsTrackedUN(const QList<UnitNode *> &value);
    void addLsTrackedUN(UnitNode *value);

private slots:
    virtual void specialReserveSlot() const override;

};

#endif // STATUSCONNECTREQUESTER_H
