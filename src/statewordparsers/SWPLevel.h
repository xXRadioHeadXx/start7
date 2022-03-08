#ifndef SWPLEVEL_H
#define SWPLEVEL_H

template <typename T>
class SWPLevel {
public:
    virtual ~SWPLevel() {}
    virtual T level() const = 0;
};

#endif // SWPLEVEL_H
