#ifndef SWPDURATIONOVERCOMING_H
#define SWPDURATIONOVERCOMING_H

template <typename T>
class SWPDurationOvercoming {
public:
    virtual ~SWPDurationOvercoming() {}
    virtual T durationOvercoming() const = 0;
};
#endif // SWPDURATIONOVERCOMING_H
