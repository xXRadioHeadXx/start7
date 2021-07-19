#include "ShedulerDK.h"

ShedulerDK::ShedulerDK(QTime runTime) :
    IntervalSheduler(runTime)
{

}

void ShedulerDK::regularRun() const
{
    emit activated();
}
