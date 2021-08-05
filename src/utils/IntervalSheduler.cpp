#include "IntervalSheduler.h"
#include "Utils.h"

IntervalSheduler::IntervalSheduler(const QTime time, const double mean) :
    QObject(nullptr),
    runInterval(time.hour() * 60 * 60),
    mean(mean)
{

}

void IntervalSheduler::start() const
{
    int dif = 0;
    if(0 != mean) {
        int value = (int)Utils::randomExponentialDistribution(300'000L);
        if(300'000 < value)
            value = value % 300'000;
        int pm = Utils::randomBernoulliDistribution(0.5L) ? +1 : -1;
        dif = value * pm;
    }
    timer.singleShot(((runInterval * 1'000) + dif), this, SLOT(regularRunSlot()));
}

void IntervalSheduler::stop()
{
    timer.stop();
}

void IntervalSheduler::regularRunSlot() const
{
    regularRun();

    int dif = 0;
    if(0 != mean) {
        int value = (int)Utils::randomExponentialDistribution(300'000L);
        if(300'000 < value)
            value = value % 300'000;
        int pm = Utils::randomBernoulliDistribution(0.5L) ? +1 : -1;
        dif = value * pm;
    }
    timer.singleShot(((runInterval * 1'000) + dif), this, SLOT(regularRunSlot()));
}
