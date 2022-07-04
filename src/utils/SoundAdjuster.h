#ifndef SOUNDADJUSTER_H
#define SOUNDADJUSTER_H

#include <QObject>
#include <QPointer>
#include <QSharedPointer>
#include "../src/template/SingletonTemplate.h"
#include <QSound>

class SoundAdjuster : public QObject,  public AfterConstructInitialization, public SingletonTemplate<SoundAdjuster>
{
    Q_OBJECT
    bool mute = false;
    QPointer<QSound> soundAlarm;
    QPointer<QSound> soundAlarm2;
    QPointer<QSound> soundRingin;
    QPointer<QSound> soundRingout;

public:
    virtual ~SoundAdjuster() {
        setMute(true);
        if(!soundAlarm.isNull())
            soundAlarm->stop();
        if(!soundAlarm2.isNull())
            soundAlarm2->stop();
        if(!soundRingin.isNull())
            soundRingin->stop();
        if(!soundRingout.isNull())
            soundRingout->stop();

        if(!soundAlarm.isNull())
            soundAlarm->deleteLater();
        if(!soundAlarm2.isNull())
            soundAlarm2->deleteLater();
        if(!soundRingin.isNull())
            soundRingin->deleteLater();
        if(!soundRingout.isNull())
            soundRingout->deleteLater();
    }

    virtual void afterConstructInitializationImpl() override;

    bool getMute() const;
    void setMute(bool value);

public slots:
    static void playAlarm(const int loops = QSound::Infinite);
    static void playAlarmOneTime();
    static void playAlarm2(const int loops = QSound::Infinite);
    static void playAlarm2OneTime();
    static void playRingin(const int loops = QSound::Infinite);
    static void playRinginOneTime();
    static void playRingout(const int loops = QSound::Infinite);
    static void playRingoutOneTime();
    static void stop();
signals:

};

#endif // SOUNDADJUSTER_H
