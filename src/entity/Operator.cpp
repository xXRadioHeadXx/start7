#include "Operator.h"

Operator Operator::approvedOperator = Operator();

Operator::Operator()
{

}

bool Operator::isNull() const {
    return getFN().isEmpty() && getN1().isEmpty() && getN2().isEmpty() && getPW().isEmpty();
};

Operator & Operator::operator=(const Operator& o) {
    this->setFN(o.getFN());
    this->setN1(o.getN1());
    this->setN2(o.getN2());
    this->setPW(o.getPW());
    return *this;
}

QString Operator::getOperatorLable() const
{
    QString str = "";
    if(this->isNull())
        return  str;
    if(!this->getFN().isEmpty()) {
        str.append(this->getFN());
    }
    if(!this->getN1().isEmpty()) {
        str.append(" " + this->getN1());
    }
    if(!this->getN2().isEmpty()) {
        str.append(" " + this->getN2());
    }
    return str;
};

QString Operator::getFN() const
{
    return FN;
}

void Operator::setFN(const QString &value)
{
    FN = value;
}

QString Operator::getN1() const
{
    return N1;
}

void Operator::setN1(const QString &value)
{
    N1 = value;
}

QString Operator::getN2() const
{
    return N2;
}

void Operator::setN2(const QString &value)
{
    N2 = value;
}

QString Operator::getPW() const
{
    return PW;
}

void Operator::setPW(const QString &value)
{
    PW = value;
}

QByteArray Operator::XOR_Crypt(const QByteArray in, const QByteArray key)
{
   QByteArray out;
   for (int x = 0; x < in.size(); x++) {
      out.append(((quint8)in.at(x) ^ (quint8)key.at((x + 1) % key.size()) * 2));
   }
   return out;
}

QString Operator::XOR_Crypt(const QString in, const QString key)
{
    return QString::fromLocal8Bit(Operator::XOR_Crypt(in.toLocal8Bit(),  key.toLocal8Bit()));
}

Operator Operator::getApprovedOperator()
{
    return approvedOperator;
}

void Operator::setApprovedOperator(const Operator &value)
{
    approvedOperator = value;
}
