#ifndef SWPCLOCKPERIOD_H
#define SWPCLOCKPERIOD_H

class SWPClockPeriod {
    virtual ~SWPClockPeriod() {}
    virtual int clockPeriod() const = 0;
};

#endif // SWPCLOCKPERIOD_H
