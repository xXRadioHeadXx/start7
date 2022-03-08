#ifndef SWPCLOSURE_H
#define SWPCLOSURE_H
//Замыкание
class SWPClosure {
public:
    virtual ~SWPClosure() {}
    virtual int isClosure() const = 0;
};

#endif // SWPCLOSURE_H
