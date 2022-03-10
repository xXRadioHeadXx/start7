#ifndef SWPCLOCKPERIOD_H
#define SWPCLOCKPERIOD_H

template <typename T>
class SWPClockPeriod {
public:
    virtual ~SWPClockPeriod() {}
    virtual T clockPeriod() const = 0;
};

#endif // SWPCLOCKPERIOD_H
