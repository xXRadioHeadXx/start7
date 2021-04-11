#ifndef SHEDULERNEWDUTY_H
#define SHEDULERNEWDUTY_H

#include "Sheduler.h"

class ShedulerNewDuty : public Sheduler
{
    Q_OBJECT
public:
    ShedulerNewDuty(QTime runTime);

private:
    virtual void regularRun() const override;
};

#endif // SHEDULERNEWDUTY_H
