#ifndef CONFIRMATIONADMISSIONWAITER_H
#define CONFIRMATIONADMISSIONWAITER_H

#include "AbstractPort.h"
#include "AbstractRequester.h"
#include "DataQueueItem.h"

#include <QObject>
#include <QTimer>
#include <Utils.h>

#include <UnitNode.h>

class ConfirmationAdmissionWaiter final : public AbstractRequester
{
public:
    explicit ConfirmationAdmissionWaiter(UnitNode * target, RequesterType requesterType = RequesterType::ConfirmWaiter);
    virtual ~ConfirmationAdmissionWaiter();
    virtual void init() override;

protected:
    virtual DataQueueItem makeFirstMsg() override;
    virtual DataQueueItem makeSecondMsg() override;

};

#endif // CONFIRMATIONADMISSIONWAITER_H
