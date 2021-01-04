#ifndef SQLUNIT_H
#define SQLUNIT_H

#include <QObject>

class SQLunit
{
public:
    SQLunit();

    QString SQL_server;
    int SQL_port;
    QString SQL_login;
    QString SQL_password;
    QString SQL_database;
};

#endif // SQLUNIT_H
