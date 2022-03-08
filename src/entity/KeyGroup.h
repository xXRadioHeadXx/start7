#ifndef KEYGROUP_H
#define KEYGROUP_H

#include <QString>



class KeyGroup
{
private:
    static const QString objectGroup;
public:
    KeyGroup();
    static const QString &ObjectGroup() {return objectGroup;};
};

#endif // KEYGROUP_H
