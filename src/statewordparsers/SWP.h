#ifndef SWP_H
#define SWP_H

#include <QDateTime>
#include <QObject>

class StateWord {
private:
    /*const*/ QByteArray byteWord;
    /*const*/ QDateTime cdate; // = QDateTime::currentDateTime();
public:
    StateWord() {};
    StateWord(const QByteArray &byteWord) : byteWord(byteWord) , cdate(QDateTime::currentDateTime()) {};
    StateWord(const QByteArray &byteWord, const QDateTime &cdate) : byteWord(byteWord) , cdate(cdate) {};
    StateWord(const StateWord &stateWord) : byteWord(stateWord.byteWord) , cdate(stateWord.cdate) {};
    StateWord &operator=(const StateWord & c) {byteWord = c.byteWord; cdate = c.cdate; return *this; };
    const QDateTime &getCdate() const;
    const QByteArray &getByteWord() const;
};

class SWP
{
private:
    StateWord stateWord;
public:
    SWP(const QByteArray &byteWord);
    SWP(const StateWord &stateWord);
    SWP(const SWP & parent);
    virtual ~SWP();
    const StateWord & getStateWord() const;
    void setStateWord(const StateWord &value);
    const QByteArray & byteWord() const;
    const QDateTime & cdate() const;

    SWP & operator=(const SWP& c);

    virtual bool isNull() const;
};

#endif // SWP_H
