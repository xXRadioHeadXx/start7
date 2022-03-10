#ifndef SWPCOUNTIMPACT_H
#define SWPCOUNTIMPACT_H

template <typename T>
class SWPCountImpact {
public:
    virtual ~SWPCountImpact() {}
    virtual T countImpact() const = 0;
};

#endif // SWPCOUNTIMPACT_H
