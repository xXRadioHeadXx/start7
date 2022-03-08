#ifndef SWPOUTALARM_H
#define SWPOUTALARM_H

class SWPOutAlarm {
public:
    virtual ~SWPOutAlarm() {}
    virtual int isOutAlarm() const = 0;
};

#endif // SWPOUTALARM_H
