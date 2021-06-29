#ifndef SWPRLMC_H
#define SWPRLMC_H

#include "SWP.h"

class SWPRLMC : public SWP
{
public:
    SWPRLMC(const StateWord &stateWord);
//    SWPRLMC(const QByteArray &bytrWord);
    SWPRLMC(const SWPRLMC & parent);
    virtual ~SWPRLMC();

    int isAlarm() const;
    int isInAlarm() const;
    int isOutAlarm() const;
    int isNorm() const;
    int isWasDK() const;
    int isExistDK() const;
    int isWasAlarm() const;
    int isOn() const;
    int isOff() const;
    double voltage() const;
    int synchronization() const;
    int isExternalSynchronization() const;
    int isInternalSynchronization() const;
    float threshold() const;
    int clockPeriod() const;
    int modeProcessing() const;
    int isFault() const;
};

#endif // SWPRLMC_H
