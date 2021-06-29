#include "SWP.h"

const StateWord &SWP::getStateWord() const
{
    return stateWord;
}

const QByteArray &SWP::byteWord() const
{
    return getStateWord().getByteWord();
}

const QDateTime &SWP::cdate() const
{
    return getStateWord().getCdate();
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
    return getStateWord().getByteWord().isEmpty();
}

SWP::SWP(const QByteArray &byteWord) :
    stateWord(StateWord(byteWord))
{
}

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

const QByteArray &StateWord::getByteWord() const
{
    return byteWord;
}

const QDateTime &StateWord::getCdate() const
{
    return cdate;
}
