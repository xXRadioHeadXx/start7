#include "tadmaudit.h"
#include <QFile>
#include <QDebug>
#include <QDataStream>

TAdmAudit::TAdmAudit(QObject *parent) : QObject(parent)
{

}

void TAdmAudit::setVersion(double value)
{
    Version = value;
}

QDateTime TAdmAudit::getCreateDt() const
{
    return CreateDt;
}

void TAdmAudit::setCreateDt(const QDateTime &value)
{
    CreateDt = value;
}

double TAdmAudit::getCRC() const
{
    return CRC;
}

void TAdmAudit::setCRC(double value)
{
    CRC = value;
}

double TAdmAudit::getVersion() const
{
    return Version;
}

bool TAdmAudit::Load(QString filePath)
{

    QFile file(filePath);


    if(file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"PROFIT";
        QDataStream stream(&file);
        stream << this;
        file.close();

        return true;

    }

    else
    {
        qDebug()<<"FALSE";
        return false;
    }
}

bool TAdmAudit::Save(QString fn)
{
return true;
}
