#ifndef SWP_H
#define SWP_H

#include <QObject>

class SWP
{
    QByteArray stateWord;
public:
    SWP(const QByteArray &stateWord);
    SWP(const SWP & parent);
    virtual ~SWP();
    QByteArray getStateWord() const;
    void setStateWord(const QByteArray &value);

    SWP & operator=(const SWP& c);

    virtual bool isNull() const;
};

#endif // SWP_H
