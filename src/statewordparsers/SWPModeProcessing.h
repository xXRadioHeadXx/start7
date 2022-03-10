#ifndef SWPMODEPROCESSING_H
#define SWPMODEPROCESSING_H

template <typename T>
class SWPModeProcessing {
public:
    virtual ~SWPModeProcessing() {}
    virtual T modeProcessing() const = 0;
};

#endif // SWPMODEPROCESSING_H
