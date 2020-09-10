#ifndef OPERATOR_H
#define OPERATOR_H

#include <QString>

class Operator
{
public:
    Operator();

    bool isNull() const;

    Operator & operator=(const Operator& );

    QString getOperatorLable() const;

    QString getFN() const;
    void setFN(const QString &value);

    QString getN1() const;
    void setN1(const QString &value);

    QString getN2() const;
    void setN2(const QString &value);

    QString getPW() const;
    void setPW(const QString &value);

    static QByteArray XOR_Crypt(const QByteArray in, const QByteArray key);
    static QString XOR_Crypt(const QString in, const QString key);

    static Operator getApprovedOperator();
    static void setApprovedOperator(const Operator &value);

private:
    QString FN;
    QString N1;
    QString N2;
    QString PW;

    static Operator approvedOperator;
};

#endif // OPERATOR_H