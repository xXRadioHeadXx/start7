#ifndef SIGNALSLOTCOMMUTATOR_H
#define SIGNALSLOTCOMMUTATOR_H

#include <QObject>
#include "template/SingletonTemplate.h"

class UnitNode;
class SignalSlotCommutator : public QObject, public SingletonTemplate<SignalSlotCommutator>
{
    Q_OBJECT
public:

public slots:
     static void emitInsNewCommandMSG(const uint32_t id);
     static void emitInsNewCommandMSG();
     static void emitInsNewJourMSG(const uint32_t id);
     static void emitInsNewJourMSG();
     static void emitUpdAllJourMSG();
     static void emitUpdJourMSG(const uint32_t id);
     static void emitUpdJourMSG();
     static void emitUpdUN();
     static void emitUpdDataTreeUN();
     static void emitStartDKWait(int interval);
     static void emitStopDKWait();
     static void emitEndDKWait();
     static void emitStartLockWait(int interval);
     static void emitStartLockWait(int interval, int startInterval);
     static void emitStopLockWait();
     static void emitEndLockWait();
     static void emitAutoOnOffIU(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget);
     static void emitLostedConnect(QSharedPointer<UnitNode> );
     static void emitRequestOnOffCommand(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget, const bool onOffValue);
     static void emitLockOpenCloseCommand(bool, QSharedPointer<UnitNode> , bool);
     static void emitLockOpenCloseCommand(QSharedPointer<UnitNode> , bool);
     static void emitChangeSelectUN (QSharedPointer<UnitNode> );
     static void emitRequestDK (const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget);
     static void emitForcedNewDuty(bool out);
     static void emitResetFlags(QSharedPointer<UnitNode>  un);
     static void emitUpdateLabelOperator();
     static void emitChangeCountIntegrationAbonent(int);

signals:
     void insNewCommandMSG(const uint32_t id) const;
     void insNewCommandMSG() const;
     void insNewJourMSG(const uint32_t id) const;
     void insNewJourMSG() const;
     void updAllJourMSG() const;
     void updJourMSG(const uint32_t id) const;
     void updJourMSG() const;
     void updUN() const;
     void updDataTreeUN() const;
     void startDKWait(int interval) const;
     void stopDKWait() const;
     void endDKWait() const;
     void startLockWait(int interval) const;
     void startLockWait(int interval, int startInterval) const;
     void stopLockWait() const;
     void endLockWait() const;
     void autoOnOffIU(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget) const;
     void lostConnect(QSharedPointer<UnitNode> ) const;
     void requestOnOffCommand(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget, const bool onOffValue) const;
     void lockOpenCloseCommand(bool, QSharedPointer<UnitNode> , bool) const;
     void changeSelectUN (QSharedPointer<UnitNode> ) const;
     void requestDK (const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget) const;
     void forcedNewDuty(bool out) const;
     void resetFlags(QSharedPointer<UnitNode>  un) const;
     void updateLabelOperator() const;
     void changeCountIntegrationAbonent(int) const;

};

#endif // SIGNALSLOTCOMMUTATOR_H
