#ifndef COMPORT_H
#define COMPORT_H

#include <QObject>

class ComPort : public QObject
{
    Q_OBJECT
public:
    explicit ComPort(QObject *parent = nullptr);

    int get_RifPortSpeed();
    int get_RifPortInterval();

    void set_RifPortSpeed(int val);
    void set_RifPortInterval(int val);

private:


    int RifPortSpeed;
    int RifPortInterval;
signals:

};

#endif // COMPORT_H
