#include "Sheduler.h"

Sheduler::Sheduler(const QTime time) :
    QObject(nullptr),
    runTime(time)
{

}

void Sheduler::start() const
{
    const int currSec = QTime(0, 0, 0).secsTo(QTime::currentTime());
    const int runSec = QTime(0, 0, 0).secsTo(runTime);
    const int DAY = 86400;

    const int nextSec = (currSec > runSec) ? (DAY + runSec - currSec) : (runSec - currSec);

    timer.singleShot(nextSec * 1000, this, SLOT(regularRunSlot()));
}

void Sheduler::stop()
{
    timer.stop();
}

//void Sheduler::firstRunSlot() const
//{
//    firstRun();

//    const int currSec = QTime(0, 0, 0).secsTo(QTime::currentTime());
//    const int DAY = 86400;
//    const int nextSec = currSec - (DAY + QTime(0, 0, 0).secsTo(runTime));

//    timer.singleShot(nextSec, this, SLOT(regularRunSlot()));
//}

void Sheduler::regularRunSlot() const
{
    const int currSec = QTime(0, 0, 0).secsTo(QTime::currentTime());
    const int runSec = QTime(0, 0, 0).secsTo(runTime);

    if(currSec > runSec)
        regularRun();

    const int DAY = 86400;

    const int nextSec = (currSec > runSec) ? (DAY + runSec - currSec) : (runSec - currSec);

    timer.singleShot(nextSec * 1000, this, SLOT(regularRunSlot()));
}
