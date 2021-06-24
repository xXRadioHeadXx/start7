#include "unit_parametr.h"

Unit_Parametr::Unit_Parametr(QString Name)
{
name=Name;
value="";
needed=false;
}

QString Unit_Parametr::getName() const
{
    return name;
}



QString Unit_Parametr::getValue() const
{
    return value;
}

void Unit_Parametr::setValue(const QString &val)
{
    value = val;
}

bool Unit_Parametr::getNeeded() const
{
    return needed;
}

void Unit_Parametr::setNeeded(bool value)
{
    needed = value;
}
