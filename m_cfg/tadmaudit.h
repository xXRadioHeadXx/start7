#ifndef TADMAUDIT_H
#define TADMAUDIT_H

#include <QObject>
#include <QDateTime>

class TAdmAudit : public QObject
{
    Q_OBJECT
public:
    explicit TAdmAudit(QObject *parent = nullptr);



    double getVersion() const;
    void setVersion(double value);

    QDateTime getCreateDt() const;
    void setCreateDt(const QDateTime &value);

    double getCRC() const;
    void setCRC(double value);

    bool Load(QString fn );
    bool Save( QString fn );

private:

    double Version;
    QDateTime CreateDt;
    double CRC;

signals:

};

#endif // TADMAUDIT_H
