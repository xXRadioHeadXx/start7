#ifndef SWPTHRESHOLD_H
#define SWPTHRESHOLD_H

class SWPThreshold {
    virtual ~SWPThreshold() {}
    virtual float threshold() const  = 0;
};

#endif // SWPTHRESHOLD_H
