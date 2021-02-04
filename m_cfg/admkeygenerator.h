#ifndef ADMKEYGENERATOR_H
#define ADMKEYGENERATOR_H

#include <QObject>
#include <QDateTime>
#include <QErrorMessage>
#include <qdevicewatcher.h>
#include <QDebug>

class AdmKeyGenerator : public QObject
{
    Q_OBJECT
private:
    double version;
    QDateTime datetime;
    QErrorMessage dialog;
    QDeviceWatcher *watcher;


public:
    explicit AdmKeyGenerator(QObject *parent = nullptr);
    void create_key(QString filepath);
    bool check_key(QString filepath);

    double getVersion() const;
    QDateTime getDatetime() const;

public slots:
    void slotDeviceAdded(const QString &dev)
    {
        qDebug()<<"Added";
    }
    void slotDeviceRemoved(const QString &dev)
    {
        qDebug()<<"Removed";
    }
    void slotDeviceChanged(const QString &dev)
    {
        qDebug()<<"Changed";
    }
};

#endif // ADMKEYGENERATOR_H
