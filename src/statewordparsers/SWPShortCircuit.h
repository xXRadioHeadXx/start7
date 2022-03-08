#ifndef SWPSHORTCIRCUIT_H
#define SWPSHORTCIRCUIT_H

class SWPShortCircuit {
    virtual ~SWPShortCircuit() {}
    virtual int isShortCircuit() const = 0;
};

#endif // SWPSHORTCIRCUIT_H
