#ifndef SWPCLIFF_H
#define SWPCLIFF_H
//Обрыв
class SWPCliff {
public:
    virtual ~SWPCliff() {}
    virtual int isCliff() const = 0;
};

#endif // SWPCLIFF_H
