#ifndef SWPOUTNORM_H
#define SWPOUTNORM_H

class SWPOutNorm {
public:
    virtual ~SWPOutNorm() {}
    virtual int isOutNorm() const = 0;
};

#endif // SWPOUTNORM_H
