#include "SoundAdjuster.h"

QSound SoundAdjuster::sound("");

void SoundAdjuster::init()
{

}

void SoundAdjuster::playAlarm(int loops)
{
    if(!sound.isFinished())
        return;
    sound.setLoops(QSound::Infinite);
    sound.play(":sound/alarm.wav");
}

void SoundAdjuster::playAlarmOneTime()
{
    playAlarm(1);
}

void SoundAdjuster::playAlarm2(int loops)
{
    if(!sound.isFinished())
        return;
    sound.setLoops(loops);
    sound.play(":sound/alarm2.wav");}

void SoundAdjuster::playAlarm2OneTime()
{
    playAlarm2(1);
}

void SoundAdjuster::playRingin(int loops)
{
    if(!sound.isFinished())
        return;
    sound.setLoops(loops);
    sound.play(":sound/ringin.wav");
}

void SoundAdjuster::playRinginOneTime()
{
    playRingin(1);
}

void SoundAdjuster::playRingout(int loops)
{
    if(!sound.isFinished())
        return;
    sound.setLoops(loops);
    sound.play(":sound/ringout.wav");
}

void SoundAdjuster::playRingoutOneTime()
{
    playRingout(1);
}

void SoundAdjuster::stop()
{
    sound.stop();
}
