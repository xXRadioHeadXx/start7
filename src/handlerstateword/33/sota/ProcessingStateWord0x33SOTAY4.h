#ifndef PROCESSINGSTATEWORD0X33SOTAY4_H
#define PROCESSINGSTATEWORD0X33SOTAY4_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x33SOTAY4 : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x33SOTAY4(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x33SOTAY4();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X33SOTAY4_H
