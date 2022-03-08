#ifndef SWPRLMTYPE0X31_H
#define SWPRLMTYPE0X31_H

#include "SWP.h"

class SWPRLMType0x31 : public SWP
{
public:
    SWPRLMType0x31(const StateWord &byteWord);

    SWPRLMType0x31(const SWPRLMType0x31&) = default;
    SWPRLMType0x31(SWPRLMType0x31&&) = default;
    SWPRLMType0x31 & operator=(const SWPRLMType0x31&) = default;
    SWPRLMType0x31& operator=(SWPRLMType0x31&&) = default;

    virtual ~SWPRLMType0x31();

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

#endif // SWPRLMTYPE0X31_H
