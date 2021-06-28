#ifndef SWP_H
#define SWP_H

#include <QDateTime>
#include <QObject>

struct StateWord {
    QByteArray stateWord;
    QDateTime cdate = QDateTime::currentDateTime();
    StateWord(const QByteArray &stateWord) : stateWord(stateWord) {}
};

class SWP
{
    StateWord stateWord;
public:
//    SWP(const QByteArray &stateWord);
    SWP(const StateWord &stateWord);
    SWP(const SWP & parent);
    virtual ~SWP();
    const StateWord & getStateWord() const;
    void setStateWord(const StateWord &value);

    SWP & operator=(const SWP& c);

    virtual bool isNull() const;
};

#endif // SWP_H
