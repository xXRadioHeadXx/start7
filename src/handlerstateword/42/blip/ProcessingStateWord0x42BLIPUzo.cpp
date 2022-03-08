#include "ProcessingStateWord0x42BLIPUzo.h"

ProcessingStateWord0x42BLIPUzo::ProcessingStateWord0x42BLIPUzo(const StateWord &data, const QSharedPointer<UnitNode> &un) :
    ProcessingStateWordAbstract(data, un)
{

}

ProcessingStateWord0x42BLIPUzo::~ProcessingStateWord0x42BLIPUzo()
{

}

bool ProcessingStateWord0x42BLIPUzo::processing(const StateWord &data, const QSharedPointer<UnitNode> &un) const
{
    return true;
}
