#include "IntervalSheduler.h"

IntervalSheduler::IntervalSheduler(const QTime time) :
    QObject(nullptr),
    runInterval(time.hour() * 60 * 60)
{

}

void IntervalSheduler::start() const
{
    timer.singleShot(runInterval * 1'000, this, SLOT(regularRunSlot()));
}

void IntervalSheduler::stop()
{
    timer.stop();
}

void IntervalSheduler::regularRunSlot() const
{
    regularRun();

    timer.singleShot(runInterval * 1'000, this, SLOT(regularRunSlot()));
}
