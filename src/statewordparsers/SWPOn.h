#ifndef SWPON_H
#define SWPON_H

class SWPOn {
public:
    virtual ~SWPOn() {}
    virtual int isOn() const = 0;
};

#endif // SWPON_H
