#include "ProcessingStateWord0x42SSOIBLIPUzo.h"

ProcessingStateWord0x42SSOIBLIPUzo::ProcessingStateWord0x42SSOIBLIPUzo(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x42SSOIBLIPUzo::~ProcessingStateWord0x42SSOIBLIPUzo()
{

}

bool ProcessingStateWord0x42SSOIBLIPUzo::processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const
{
    return true;
}
