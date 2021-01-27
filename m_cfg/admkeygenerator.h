#ifndef ADMKEYGENERATOR_H
#define ADMKEYGENERATOR_H

#include <QObject>
#include <QDateTime>
#include <QErrorMessage>

class AdmKeyGenerator
{

private:
    double version;
    QDateTime datetime;
    QErrorMessage dialog;


public:
    AdmKeyGenerator();
    void create_key(QString filepath);
    bool check_key(QString filepath);

    double getVersion() const;
    QDateTime getDatetime() const;
};

#endif // ADMKEYGENERATOR_H
