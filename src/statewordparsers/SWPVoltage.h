#ifndef SWPVOLTAGE_H
#define SWPVOLTAGE_H

class SWPVoltage {
public:
    virtual ~SWPVoltage() {}
    virtual double voltage() const = 0;
};

#endif // SWPVOLTAGE_H
