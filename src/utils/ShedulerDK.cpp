#include "ShedulerDK.h"

ShedulerDK::ShedulerDK(QTime runTime, const double mean) :
    IntervalSheduler(runTime, mean)
{

}

void ShedulerDK::regularRun() const
{
    emit activated();
}
