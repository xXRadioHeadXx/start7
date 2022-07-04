#ifndef PROCESSINGSTATEWORD0X42SSOIBLIPUZO_H
#define PROCESSINGSTATEWORD0X42SSOIBLIPUZO_H

#include "../src/handlerstateword/ProcessingStateWordAbstract.h"

class ProcessingStateWord0x42SSOIBLIPUzo : public ProcessingStateWordAbstract
{
public:
    ProcessingStateWord0x42SSOIBLIPUzo(const StateWord &data, const QSharedPointer<UnitNode> &un);
    virtual ~ProcessingStateWord0x42SSOIBLIPUzo();
    bool processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const override;
};

#endif // PROCESSINGSTATEWORD0X42SSOIBLIPUZO_H
