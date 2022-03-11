#ifndef PROCESSINGSTATEWORD0X32SOTAY4_H
#define PROCESSINGSTATEWORD0X32SOTAY4_H

#include <ProcessingStateWordAbstract.h>

class ProcessingStateWord0x32SOTAY4 : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x32SOTAY4(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x32SOTAY4();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X32SOTAY4_H
