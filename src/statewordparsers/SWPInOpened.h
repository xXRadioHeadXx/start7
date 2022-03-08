#ifndef SWPINOPENED_H
#define SWPINOPENED_H

class SWPInOpened {
public:
    virtual ~SWPInOpened() {}
    virtual int isInOpened() const = 0;
};

#endif // SWPINOPENED_H
