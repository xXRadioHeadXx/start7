#ifndef SWPWASALARM_H
#define SWPWASALARM_H

class SWPWasAlarm {
public:
    virtual ~SWPWasAlarm() {}
    virtual int isWasAlarm() const = 0;
};

#endif // SWPWASALARM_H
