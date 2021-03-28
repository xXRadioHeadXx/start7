#ifndef SIGNALSLOTCOMMUTATOR_H
#define SIGNALSLOTCOMMUTATOR_H

#include <QObject>

class UnitNode;
class SignalSlotCommutator : public QObject
{
    Q_OBJECT
public:
    static SignalSlotCommutator * getInstance();
private:
     static SignalSlotCommutator * instance;
     explicit SignalSlotCommutator(QObject *parent = nullptr);

public slots:
     void emitInsNewCommandMSG(const quint32 id) const;
     void emitInsNewCommandMSG() const;
     void emitInsNewJourMSG(const quint32 id) const;
     void emitInsNewJourMSG() const;
     void emitUpdAllJourMSG() const;
     void emitUpdJourMSG(const quint32 id) const;
     void emitUpdJourMSG() const;
     void emitUpdUN() const;
     void emitUpdDataTreeUN() const;
     void emitStartDKWait(int interval) const;
     void emitStopDKWait() const;
     void emitEndDKWait() const;
     void emitStartLockWait(int interval) const;
     void emitStopLockWait() const;
     void emitEndLockWait() const;
     void emitAutoOnOffIU(bool, UnitNode *) const;
     void emitAutoOnOffIU(UnitNode *) const;
     void emitLostedConnect(UnitNode *) const;
     void emitRequestOnOffCommand(bool, UnitNode *, bool) const;
     void emitRequestOnOffCommand(UnitNode *, bool) const;
     void emitLockOpenCloseCommand(bool, UnitNode *, bool) const;
     void emitLockOpenCloseCommand(UnitNode *, bool) const;
     void emitChangeSelectUN (UnitNode *) const;
     void emitRequestDK (UnitNode *) const;
     void emitRequestDK (bool, UnitNode * un = nullptr) const;
     void emitForcedNewDuty(bool out) const;
     void emitAlarmsReset(UnitNode * un) const;

signals:
     void insNewCommandMSG(const quint32 id) const;
     void insNewCommandMSG() const;
     void insNewJourMSG(const quint32 id) const;
     void insNewJourMSG() const;
     void updAllJourMSG() const;
     void updJourMSG(const quint32 id) const;
     void updJourMSG() const;
     void updUN() const;
     void updDataTreeUN() const;
     void startDKWait(int interval) const;
     void stopDKWait() const;
     void endDKWait() const;
     void startLockWait(int interval) const;
     void stopLockWait() const;
     void endLockWait() const;
     void autoOnOffIU(UnitNode *) const;
     void autoOnOffIU(bool, UnitNode *) const;
     void lostConnect(UnitNode *) const;
     void requestOnOffCommand(bool, UnitNode *, bool) const;
     void lockOpenCloseCommand(bool, UnitNode *, bool) const;
     void changeSelectUN (UnitNode *) const;
     void requestDK (UnitNode *) const;
     void requestDK (bool, UnitNode *) const;
     void forcedNewDuty(bool out) const;
     void alarmsReset(UnitNode * un) const;

};

#endif // SIGNALSLOTCOMMUTATOR_H
