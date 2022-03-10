#ifndef SWPOFF_H
#define SWPOFF_H

class SWPOff {
public:
    virtual ~SWPOff() {}
    virtual int isOff() const = 0;
};

#endif // SWPOFF_H
