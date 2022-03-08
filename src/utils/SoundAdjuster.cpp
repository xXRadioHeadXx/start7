#include "SoundAdjuster.h"
#include <QCoreApplication>
#include <QDebug>
#include <QWeakPointer>

bool SoundAdjuster::getMute() const
{
    return mute;
}

void SoundAdjuster::setMute(bool value)
{
    mute = value;
}

void SoundAdjuster::afterConstructInitializationImpl()
{
    SoundAdjuster::instance().soundAlarm = QPointer<QSound>(new QSound(":sound/alarm.wav"));
    SoundAdjuster::instance().soundAlarm2 = QPointer<QSound>(new QSound(":sound/alarm2.wav"));
    SoundAdjuster::instance().soundRingin = QPointer<QSound>(new QSound(":sound/ringin.wav"));
    SoundAdjuster::instance().soundRingout = QPointer<QSound>(new QSound(":sound/ringout.wav"));
}

void SoundAdjuster::playAlarm(const int loops)
{
    if(SoundAdjuster::instance().getMute())
        return;
#ifdef QT_DEBUG
        qDebug() << "SoundAdjuster::playAlarm( play )";
#else
    if(SoundAdjuster::instance().soundAlarm.isNull())
        return;
    if(!SoundAdjuster::instance().soundAlarm->isFinished())
        return;
    SoundAdjuster::instance().soundAlarm->setLoops(loops);
//    qDebug() << "SoundAdjuster::playAlarm(" << loops << ")" << soundAlarm.loopsRemaining() << soundAlarm.loops();
    SoundAdjuster::instance().soundAlarm->play();
    SoundAdjuster::instance().soundAlarm->play();
#endif
}

void SoundAdjuster::playAlarmOneTime()
{
    playAlarm(1);
}

void SoundAdjuster::playAlarm2(const int loops)
{
    if(SoundAdjuster::instance().getMute())
        return;
#ifdef QT_DEBUG
    qDebug() << "SoundAdjuster::playAlarm2( play )";
#else
    if(SoundAdjuster::instance().soundAlarm2.isNull())
        return;
    if(!SoundAdjuster::instance().soundAlarm2->isFinished())
        return;
    SoundAdjuster::instance().soundAlarm2->setLoops(loops);
    SoundAdjuster::instance().soundAlarm2->play();
#endif
}

void SoundAdjuster::playAlarm2OneTime()
{
    playAlarm2(1);
}

void SoundAdjuster::playRingin(const int loops)
{
    if(SoundAdjuster::instance().getMute())
        return;
#ifdef QT_DEBUG
    qDebug() << "SoundAdjuster::playRingin( play )";
#else
    if(SoundAdjuster::instance().soundRingin.isNull())
        return;
    if(!SoundAdjuster::instance().soundRingin->isFinished())
        return;
    SoundAdjuster::instance().soundRingin->setLoops(loops);
    SoundAdjuster::instance().soundRingin->play();
#endif
}

void SoundAdjuster::playRinginOneTime()
{
    playRingin(1);
}

void SoundAdjuster::playRingout(const int loops)
{
    if(SoundAdjuster::instance().getMute())
        return;
#ifdef QT_DEBUG
    qDebug() << "SoundAdjuster::playRingout( play )";
#else
    if(SoundAdjuster::instance().soundRingout.isNull())
        return;
    if(!SoundAdjuster::instance().soundRingout->isFinished())
        return;
    SoundAdjuster::instance().soundRingout->setLoops(loops);
    SoundAdjuster::instance().soundRingout->play();
#endif
}

void SoundAdjuster::playRingoutOneTime()
{
    playRingout(1);
}

void SoundAdjuster::stop()
{
    bool previousMuteValue =  SoundAdjuster::instance().getMute();
    SoundAdjuster::instance().setMute(true);
    if(!SoundAdjuster::instance().soundAlarm.isNull())
        SoundAdjuster::instance().soundAlarm->stop();
    if(!SoundAdjuster::instance().soundAlarm2.isNull())
        SoundAdjuster::instance().soundAlarm2->stop();
    if(!SoundAdjuster::instance().soundRingin.isNull())
        SoundAdjuster::instance().soundRingin->stop();
    if(!SoundAdjuster::instance().soundRingout.isNull())
        SoundAdjuster::instance().soundRingout->stop();
    SoundAdjuster::instance().setMute(previousMuteValue);
}
