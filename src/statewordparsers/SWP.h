#ifndef SWP_H
#define SWP_H

#include <QDateTime>
#include <QObject>

class StateWord {
private:
    QByteArray byteWord;
    QDateTime cdate; // = QDateTime::currentDateTime();
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
    SWP(const StateWord &stateWord);
    SWP(const QByteArray &byteWord);
    SWP(const QByteArray &byteWord, const QDateTime &cdate);

    SWP(const SWP&) = default;
    SWP(SWP&&) = default;
    SWP & operator=(const SWP&) = default;
    SWP& operator=(SWP&&) = default;

    virtual ~SWP();
    const StateWord & getStateWord() const;
    void setStateWord(const StateWord &value);
    const QByteArray & byteWord() const;
    const QDateTime & cdate() const;

//    SWP & operator=(const SWP& c);

    virtual bool isNull() const;
};

#endif // SWP_H
