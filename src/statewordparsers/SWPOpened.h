#ifndef SWPOPENED_H
#define SWPOPENED_H

class SWPOpened {
public:
    virtual ~SWPOpened() {}
    virtual int isOpened() const = 0;
};

#endif // SWPOPENED_H
