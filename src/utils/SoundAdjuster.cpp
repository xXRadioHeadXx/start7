#include "SoundAdjuster.h"
#include <QCoreApplication>
#include <QDebug>

void SoundAdjuster::init()
{
    soundAlarm = QSharedPointer<QSound>::create(":sound/alarm.wav");
    soundAlarm2 = QSharedPointer<QSound>::create(":sound/alarm2.wav");
    soundRingin = QSharedPointer<QSound>::create(":sound/ringin.wav");
    soundRingout = QSharedPointer<QSound>::create(":sound/ringout.wav");
}

void SoundAdjuster::playAlarm(const int loops)
{
    if(soundAlarm.isNull())
        return;
    if(!soundAlarm->isFinished())
        return;
    soundAlarm->setLoops(loops);
//    qDebug() << "SoundAdjuster::playAlarm(" << loops << ")" << soundAlarm.loopsRemaining() << soundAlarm.loops();
    soundAlarm->play();
}

void SoundAdjuster::playAlarmOneTime()
{
    playAlarm(1);
}

void SoundAdjuster::playAlarm2(const int loops)
{
    if(soundAlarm2.isNull())
        return;
    if(!soundAlarm2->isFinished())
        return;
    soundAlarm2->setLoops(loops);
    soundAlarm2->play();
}

void SoundAdjuster::playAlarm2OneTime()
{
    playAlarm2(1);
}

void SoundAdjuster::playRingin(const int loops)
{
    if(soundRingin.isNull())
        return;
    if(!soundRingin->isFinished())
        return;
    soundRingin->setLoops(loops);
    soundRingin->play();
}

void SoundAdjuster::playRinginOneTime()
{
    playRingin(1);
}

void SoundAdjuster::playRingout(const int loops)
{
    if(soundRingout.isNull())
        return;
    if(!soundRingout->isFinished())
        return;
    soundRingout->setLoops(loops);
    soundRingout->play();
}

void SoundAdjuster::playRingoutOneTime()
{
    playRingout(1);
}

void SoundAdjuster::stop()
{
    if(!soundAlarm.isNull())
        soundAlarm->stop();
    if(!soundAlarm2.isNull())
        soundAlarm2->stop();
    if(!soundRingin.isNull())
        soundRingin->stop();
    if(!soundRingout.isNull())
        soundRingout->stop();
}
