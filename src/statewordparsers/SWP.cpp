#include "SWP.h"

QByteArray SWP::getStateWord() const
{
    return stateWord;
}

void SWP::setStateWord(const QByteArray &value)
{
    stateWord = value;
}

SWP &SWP::operator=(const SWP & c)
{
    setStateWord(c.getStateWord());
}

bool SWP::isNull() const
{
    getStateWord().isEmpty();
}

SWP::SWP(const QByteArray &stateWord) :
    stateWord(stateWord)
{
}

SWP::SWP(const SWP &parent):
    stateWord(parent.stateWord)
{
}

SWP::~SWP() {

}
