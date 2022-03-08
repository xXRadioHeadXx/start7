#ifndef SWPINCOMMUNICATIONBREAK_H
#define SWPINCOMMUNICATIONBREAK_H

class SWPInCommunicationBreak {
public:
    virtual ~SWPInCommunicationBreak() {}
    virtual int isInCommunicationBreak() const = 0;
};

#endif // SWPINCOMMUNICATIONBREAK_H
