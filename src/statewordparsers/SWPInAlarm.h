#ifndef SWPINALARM_H
#define SWPINALARM_H

class SWPInAlarm {
public:
    virtual ~SWPInAlarm() {}
    virtual int isInAlarm() const = 0;
};

#endif // SWPINALARM_H
