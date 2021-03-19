#ifndef SWPSDBLIP_H
#define SWPSDBLIP_H

#include <SWP.h>

class SWPSDBLIP : public SWP
{
    quint8 _mask;
public:
    SWPSDBLIP(const QByteArray &stateWord, int numSD);
    SWPSDBLIP(const SWPSDBLIP & parent);
    virtual ~SWPSDBLIP();

    int isAlarm() const;
    int isInAlarm() const;
    int isNorm() const;
    int isWasAlarm() const;
    int isOn() const;
    int isOff() const;
    quint8 mask() const;
};

#endif // SWPSDBLIP_H
