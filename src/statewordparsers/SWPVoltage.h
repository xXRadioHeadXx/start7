#ifndef SWPVOLTAGE_H
#define SWPVOLTAGE_H

template <typename T>
class SWPVoltage {
public:
    virtual ~SWPVoltage() {}
    virtual T voltage() const = 0;
};

#endif // SWPVOLTAGE_H
