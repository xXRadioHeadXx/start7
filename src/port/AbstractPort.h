#ifndef ABSTRACTPORT_H
#define ABSTRACTPORT_H

#include <QObject>

class QSettings;

enum Protocol {
    UDP = 0
};

class AbstractPort : public QObject
{
    Q_OBJECT
public:
    enum Protocol {
        UDP = 0,
        TCP = 1,
        SERIAL = 2
    };
    AbstractPort::Protocol protocol = UDP;
    AbstractPort::Protocol getProtocol() const {return protocol;}

    explicit AbstractPort(QObject *parent = nullptr) : QObject(parent) {}

    virtual void retranslate() {}
    virtual void loadConfig(QSettings *config) = 0;
    virtual void saveConfig(QSettings *config) = 0;
    virtual bool open() = 0;
    virtual void close() = 0;
//    virtual QByteArray readAll() = 0;
//    virtual void write(const QByteArray &data) = 0;
    virtual bool portStatus(QString *string) = 0;
    virtual bool isOpen() = 0;

signals:
    void readyRead();
    void portError();
    void portChanged();

    void readyRead(int index);
    void portError(int index);
    void portChanged(int index);
};

#endif // ABSTRACTPORT_H
