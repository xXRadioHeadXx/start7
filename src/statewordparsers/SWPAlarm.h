#ifndef SWPALARM_H
#define SWPALARM_H

class SWPAlarm {
public:
    virtual ~SWPAlarm() {}
    virtual int isAlarm() const = 0;
};

#endif // SWPALARM_H
