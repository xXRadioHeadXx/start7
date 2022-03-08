#ifndef SWPINTERROGATION_H
#define SWPINTERROGATION_H

class SWPInterrogation {
public:
    virtual ~SWPInterrogation() {}
    virtual int isInterrogation() const = 0;
};

#endif // SWPINTERROGATION_H
