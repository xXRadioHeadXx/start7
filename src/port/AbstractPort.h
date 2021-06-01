#ifndef ABSTRACTPORT_H
#define ABSTRACTPORT_H

#include <QObject>

class AbstractPort : public QObject
{
    Q_OBJECT
public:
    enum Protocol {
        UDP = 0,
        TCP = 1,
        SERIAL = 2
    };
    AbstractPort::Protocol protocol = AbstractPort::UDP;

    AbstractPort::Protocol getProtocol() const {return protocol;}
    void setProtocol(const AbstractPort::Protocol &value) { protocol = value; }
    explicit AbstractPort(const AbstractPort::Protocol &protocol, QObject *parent = nullptr) : QObject(parent), protocol(protocol) {}
    virtual ~AbstractPort() {}

    virtual bool open() = 0;
    virtual void close() = 0;
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


