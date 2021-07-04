#include "SoundAdjuster.h"

QSound SoundAdjuster::sound("");

void SoundAdjuster::init()
{

}

void SoundAdjuster::playAlarm()
{
    if(!sound.isFinished())
        return;
    sound.setLoops(QSound::Infinite);
    sound.play(":sound/alarm.wav");
}

void SoundAdjuster::playAlarmOneTime()
{
    if(!sound.isFinished())
        return;
    sound.setLoops(1);
    sound.play(":sound/alarm.wav");
}

void SoundAdjuster::stop()
{
    sound.stop();
}
