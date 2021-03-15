#ifndef SWPRLM_H
#define SWPRLM_H

#include <SWP.h>

class SWPRLM : public SWP
{
public:
    SWPRLM(const QByteArray &stateWord);
    SWPRLM(const SWPRLM & parent);
    virtual ~SWPRLM();

    float threshold() const;
    int modeProcessing() const;
    int clockPeriod() const;
    float voltage() const;
    int isOn() const;
    int isOff() const;
    int isAlarm() const;
    int isInAlarm() const;
    int isOutAlarm() const;
    int isNorm() const;
    int isWasAlarm() const;
    int isExistDK() const;
    int synchronization() const;
    int isWasDK() const;
    int isOpened() const;
    int isInOpened() const;
    int isWasOpened() const;
};

#endif // SWPRLM_H