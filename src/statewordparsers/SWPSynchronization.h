#ifndef SWPSYNCHRONIZATION_H
#define SWPSYNCHRONIZATION_H

class SWPSynchronization {
    virtual ~SWPSynchronization() {}
    virtual int synchronization() const = 0;
};

#endif // SWPSYNCHRONIZATION_H
