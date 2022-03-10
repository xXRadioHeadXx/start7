#ifndef SWPWEAKENING_H
#define SWPWEAKENING_H

template <typename T>
class SWPWeakening
{
public:
    virtual ~SWPWeakening() {}
    virtual T weakening() const = 0;
};

#endif // SWPWEAKENING_H
