#ifndef SWPALARM_H
#define SWPALARM_H

class SWPAlarm {
    virtual ~SWPAlarm() {}
    virtual int isAlarm() const = 0;
};

#endif // SWPALARM_H
