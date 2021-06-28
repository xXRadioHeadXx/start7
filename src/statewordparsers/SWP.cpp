#include "SWP.h"

const StateWord &SWP::getStateWord() const
{
    return stateWord;
}

void SWP::setStateWord(const StateWord &value)
{
    stateWord = value;
}

SWP &SWP::operator=(const SWP & c)
{
    setStateWord(c.getStateWord());
    return *this;
}

bool SWP::isNull() const
{
    return getStateWord().isEmpty();
}

//SWP::SWP(const QByteArray &stateWord) :
//    stateWord(StateWord(stateWord))
//{
//}

SWP::SWP(const StateWord &stateWord) :
    stateWord(stateWord)
{

}

SWP::SWP(const SWP &parent):
    stateWord(parent.stateWord)
{
}

SWP::~SWP() {

}
