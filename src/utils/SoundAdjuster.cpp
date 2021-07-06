#include "SoundAdjuster.h"
#include <QDebug>

QSound SoundAdjuster::soundAlarm(":sound/alarm.wav");
QSound SoundAdjuster::soundAlarm2(":sound/alarm2.wav");
QSound SoundAdjuster::soundRingin(":sound/ringin.wav");
QSound SoundAdjuster::soundRingout(":sound/ringout.wav");

void SoundAdjuster::init()
{

}

void SoundAdjuster::playAlarm(const int loops)
{
    if(!soundAlarm.isFinished())
        return;
    soundAlarm.setLoops(QSound::Infinite);
    qDebug() << "SoundAdjuster::playAlarm(" << loops << ")" << soundAlarm.loopsRemaining() << soundAlarm.loops();
    soundAlarm.play(":sound/alarm.wav");
}

void SoundAdjuster::playAlarmOneTime()
{
    playAlarm(1);
}

void SoundAdjuster::playAlarm2(const int loops)
{
    if(!soundAlarm2.isFinished())
        return;
    soundAlarm2.setLoops(loops);
    soundAlarm2.play(":sound/alarm2.wav");}

void SoundAdjuster::playAlarm2OneTime()
{
    playAlarm2(1);
}

void SoundAdjuster::playRingin(const int loops)
{
    if(!soundRingin.isFinished())
        return;
    soundRingin.setLoops(loops);
    soundRingin.play(":sound/ringin.wav");
}

void SoundAdjuster::playRinginOneTime()
{
    playRingin(1);
}

void SoundAdjuster::playRingout(const int loops)
{
    if(!soundRingout.isFinished())
        return;
    soundRingout.setLoops(loops);
    soundRingout.play(":sound/ringout.wav");
}

void SoundAdjuster::playRingoutOneTime()
{
    playRingout(1);
}

void SoundAdjuster::stop()
{
    soundAlarm.stop();
}
