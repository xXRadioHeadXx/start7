#ifndef SWPRLMCTYPE0X31_H
#define SWPRLMCTYPE0X31_H

#include "../src/statewordparsers/SWP.h"

class SWPRLMCType0x31 : public SWP
{
public:
    SWPRLMCType0x31(const StateWord &stateWord);

    SWPRLMCType0x31(const SWPRLMCType0x31&) = default;
    SWPRLMCType0x31(SWPRLMCType0x31&&) = default;
    SWPRLMCType0x31 & operator=(const SWPRLMCType0x31&) = default;
    SWPRLMCType0x31& operator=(SWPRLMCType0x31&&) = default;

    virtual ~SWPRLMCType0x31();

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

#endif // SWPRLMCTYPE0X31_H
