#include "comport.h"

ComPort::ComPort(QObject *parent) : QObject(parent)
{
this->RifPortSpeed = 4800;
this->RifPortInterval = 50;
}

int ComPort::get_RifPortSpeed()
{
    return RifPortSpeed;
}

int ComPort::get_RifPortInterval()
{
    return RifPortInterval;
}

void ComPort::set_RifPortSpeed(int val)
{
    this->RifPortSpeed = val;
}

void ComPort::set_RifPortInterval(int val)
{
    this->RifPortInterval = val;
}
