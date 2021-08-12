#include "SoundAdjuster.h"
#include <QCoreApplication>
#include <QDebug>

void SoundAdjuster::init()
{
    SoundAdjuster::instance().soundAlarm = QSharedPointer<QSound>::create(":sound/alarm.wav");
    SoundAdjuster::instance().soundAlarm2 = QSharedPointer<QSound>::create(":sound/alarm2.wav");
    SoundAdjuster::instance().soundRingin = QSharedPointer<QSound>::create(":sound/ringin.wav");
    SoundAdjuster::instance().soundRingout = QSharedPointer<QSound>::create(":sound/ringout.wav");
}

void SoundAdjuster::playAlarm(const int loops)
{
    if(SoundAdjuster::instance().soundAlarm.isNull())
        return;
    if(!SoundAdjuster::instance().soundAlarm->isFinished())
        return;
    SoundAdjuster::instance().soundAlarm->setLoops(loops);
//    qDebug() << "SoundAdjuster::playAlarm(" << loops << ")" << soundAlarm.loopsRemaining() << soundAlarm.loops();
    SoundAdjuster::instance().soundAlarm->play();
}

void SoundAdjuster::playAlarmOneTime()
{
    playAlarm(1);
}

void SoundAdjuster::playAlarm2(const int loops)
{
    if(SoundAdjuster::instance().soundAlarm2.isNull())
        return;
    if(!SoundAdjuster::instance().soundAlarm2->isFinished())
        return;
    SoundAdjuster::instance().soundAlarm2->setLoops(loops);
    SoundAdjuster::instance().soundAlarm2->play();
}

void SoundAdjuster::playAlarm2OneTime()
{
    playAlarm2(1);
}

void SoundAdjuster::playRingin(const int loops)
{
    if(SoundAdjuster::instance().soundRingin.isNull())
        return;
    if(!SoundAdjuster::instance().soundRingin->isFinished())
        return;
    SoundAdjuster::instance().soundRingin->setLoops(loops);
    SoundAdjuster::instance().soundRingin->play();
}

void SoundAdjuster::playRinginOneTime()
{
    playRingin(1);
}

void SoundAdjuster::playRingout(const int loops)
{
    if(SoundAdjuster::instance().soundRingout.isNull())
        return;
    if(!SoundAdjuster::instance().soundRingout->isFinished())
        return;
    SoundAdjuster::instance().soundRingout->setLoops(loops);
    SoundAdjuster::instance().soundRingout->play();
}

void SoundAdjuster::playRingoutOneTime()
{
    playRingout(1);
}

void SoundAdjuster::stop()
{
    if(!SoundAdjuster::instance().soundAlarm.isNull())
        SoundAdjuster::instance().soundAlarm->stop();
    if(!SoundAdjuster::instance().soundAlarm2.isNull())
        SoundAdjuster::instance().soundAlarm2->stop();
    if(!SoundAdjuster::instance().soundRingin.isNull())
        SoundAdjuster::instance().soundRingin->stop();
    if(!SoundAdjuster::instance().soundRingout.isNull())
        SoundAdjuster::instance().soundRingout->stop();
}
