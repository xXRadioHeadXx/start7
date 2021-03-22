#ifndef SWPIUBLIP_H
#define SWPIUBLIP_H

#include <SWP.h>

class SWPIUBLIP : public SWP
{
    quint8 _mask = 0x00;
public:
    SWPIUBLIP(const QByteArray &stateWord, int numIU);
    SWPIUBLIP(const SWPIUBLIP & parent);
    virtual ~SWPIUBLIP();

    int isOutAlarm() const;
    int isOn() const;
    int isOff() const;
    quint8 mask() const;
};

#endif // SWPIUBLIP_H
