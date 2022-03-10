#ifndef SWPTHRESHOLD_H
#define SWPTHRESHOLD_H

template <typename T>
class SWPThreshold {
public:
    virtual ~SWPThreshold() {}
    virtual T threshold() const  = 0;
};

#endif // SWPTHRESHOLD_H
