#ifndef SOUNDADJUSTER_H
#define SOUNDADJUSTER_H

#include <QObject>
#include "template/SingletonTemplate.h"
#include "QSound"

class SoundAdjuster : public QObject, public SingletonTemplate<SoundAdjuster>
{
    Q_OBJECT
    static QSound sound;
protected:
//    explicit SoundAdjuster() {}
public:
    virtual ~SoundAdjuster() {}

    void init();

public slots:
    void playAlarm(int loops = QSound::Infinite);
    void playAlarmOneTime();
    void playAlarm2(int loops = QSound::Infinite);
    void playAlarm2OneTime();
    void playRingin(int loops = QSound::Infinite);
    void playRinginOneTime();
    void playRingout(int loops = QSound::Infinite);
    void playRingoutOneTime();
    void stop();
signals:

};

#endif // SOUNDADJUSTER_H
