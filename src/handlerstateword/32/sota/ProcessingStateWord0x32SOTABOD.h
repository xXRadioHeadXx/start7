#ifndef PROCESSINGSTATEWORD0X32SOTABOD_H
#define PROCESSINGSTATEWORD0X32SOTABOD_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x32SOTABOD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x32SOTABOD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x32SOTABOD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X32SOTABOD_H
