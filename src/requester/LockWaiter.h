#ifndef LOCKWAITER_H
#define LOCKWAITER_H

#include <AbstractRequester.h>

class LockWaiter final : public AbstractRequester
{
private:
    UnitNode * unReciverIuBlIp = nullptr;
    UnitNode * unReciverSdBlIp = nullptr;
    int initVarianrt = 0;

    DataQueueItem getOnMsg();
    DataQueueItem getOffMsg();

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;
    virtual DataQueueItem makeEndMsg() override;

public:
    explicit LockWaiter(UnitNode * target, RequesterType requesterType = RequesterType::LockRequester);
    virtual ~LockWaiter();

    virtual void init() override;

    UnitNode *getUnReciverIuBlIp() const;
    void setUnReciverIuBlIp(UnitNode *value);
    UnitNode *getUnReciverSdBlIp() const;
    void setUnReciverSdBlIp(UnitNode *value);
    int getInitVarianrt() const;
    void setInitVarianrt(int value);
};

#endif // LOCKWAITER_H
