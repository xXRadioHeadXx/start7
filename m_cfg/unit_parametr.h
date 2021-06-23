#ifndef UNIT_PARAMETR_H
#define UNIT_PARAMETR_H

#include <QObject>

class Unit_Parametr
{
public:
    Unit_Parametr(QString Name);

    QString getName() const;


    QString getValue() const;
    void setValue(const QString &value);

    bool getNeeded() const;
    void setNeeded(bool value);

private:

    QString name;
    QString value;
    bool needed;
};

#endif // UNIT_PARAMETR_H
