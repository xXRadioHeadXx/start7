#ifndef SHEDULERDK_H
#define SHEDULERDK_H

#include "IntervalSheduler.h"

class ShedulerDK : public IntervalSheduler
{
    Q_OBJECT
public:
    ShedulerDK(QTime runTime);

private:
    virtual void regularRun() const override;

signals:
    void activated() const;
};

#endif // SHEDULERDK_H
