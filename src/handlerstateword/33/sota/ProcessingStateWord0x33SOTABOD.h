#ifndef PROCESSINGSTATEWORD0X33SOTABOD_H
#define PROCESSINGSTATEWORD0X33SOTABOD_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x33SOTABOD : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x33SOTABOD(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x33SOTABOD();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X33SOTABOD_H
