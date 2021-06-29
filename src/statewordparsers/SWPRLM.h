#ifndef SWPRLM_H
#define SWPRLM_H

#include "SWP.h"

class SWPRLM : public SWP
{
public:
    SWPRLM(const StateWord &byteWord);
//    SWPRLM(const QByteArray &byteWord);
    SWPRLM(const SWPRLM & parent);
    virtual ~SWPRLM();

    float threshold() const;
    int modeProcessing() const;
    int clockPeriod() const;
    double voltage() const;
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
    int isFault() const;
};

#endif // SWPRLM_H
