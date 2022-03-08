#ifndef SWPREADY_H
#define SWPREADY_H

class SWPReady {
public:
    virtual ~SWPReady() {}
    virtual int isReady() const = 0;
};

#endif // SWPREADY_H
