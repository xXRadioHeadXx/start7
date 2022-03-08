#ifndef SWPFAULT_H
#define SWPFAULT_H

class SWPFault {
public:
    virtual ~SWPFault() {}
    virtual int isFault() const = 0;
};

#endif // SWPFAULT_H
