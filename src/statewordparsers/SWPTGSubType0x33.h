#ifndef SWPTGSUBTYPE0X33_H
#define SWPTGSUBTYPE0X33_H

#include "SWP.h"

class SWPTGSubType0x33 : public SWP
{
private:
    const int flang;
public:
    SWPTGSubType0x33(const QByteArray stateWord, const int flang);
    SWPTGSubType0x33(const SWPTGSubType0x33 & parent);
    virtual ~SWPTGSubType0x33();
    int getFlang() const;

    int isInAlarm() const;
    int isOutAlarm() const;
    int isFault() const;
    int isSideAlarm() const;

    int isInOpened() const;
    int isWasOpened() const;

    int isOpened() const;
    int isAlarm() const;
    int isNorm() const;


};

#endif // SWPTGSUBTYPE0X33_H
