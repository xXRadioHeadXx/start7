#include "SignalSlotCommutator.h"
#include <QSharedPointer>
//#include <QDebug>

void SignalSlotCommutator::emitInsNewCommandMSG(const uint32_t id) {
    emit SignalSlotCommutator::instance().insNewCommandMSG(id);
}

void SignalSlotCommutator::emitInsNewCommandMSG() {
    emit SignalSlotCommutator::instance().insNewCommandMSG();
}

void SignalSlotCommutator::emitInsNewJourMSG(const uint32_t id) {
    emit SignalSlotCommutator::instance().insNewJourMSG(id);
}

void SignalSlotCommutator::emitInsNewJourMSG() {
    emit SignalSlotCommutator::instance().insNewJourMSG();
}

void SignalSlotCommutator::emitUpdAllJourMSG() {
    emit SignalSlotCommutator::instance().updAllJourMSG();
}

void SignalSlotCommutator::emitUpdJourMSG(const uint32_t id) {
    emit SignalSlotCommutator::instance().updJourMSG(id);
}

void SignalSlotCommutator::emitUpdJourMSG() {
    emit SignalSlotCommutator::instance().updJourMSG();
}

void SignalSlotCommutator::emitUpdUN() {
    emit SignalSlotCommutator::instance().updUN();
}

void SignalSlotCommutator::emitUpdDataTreeUN() {
    emit SignalSlotCommutator::instance().updDataTreeUN();
}

void SignalSlotCommutator::emitStartDKWait(int interval) {
    emit SignalSlotCommutator::instance().startDKWait(interval);
}

void SignalSlotCommutator::emitStopDKWait() {
    emit SignalSlotCommutator::instance().stopDKWait();
}

void SignalSlotCommutator::emitEndDKWait() {
    emit SignalSlotCommutator::instance().endDKWait();
}

void SignalSlotCommutator::emitStartLockWait(int interval) {
    emit SignalSlotCommutator::instance().startLockWait(interval);
}

void SignalSlotCommutator::emitStartLockWait(int interval, int startInterval) {
    emit SignalSlotCommutator::instance().startLockWait(interval, startInterval);
}

void SignalSlotCommutator::emitStopLockWait() {
    emit SignalSlotCommutator::instance().stopLockWait();
}

void SignalSlotCommutator::emitEndLockWait() {
    emit SignalSlotCommutator::instance().endLockWait();
}

void SignalSlotCommutator::emitAutoOnOffIU(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget) {
    emit SignalSlotCommutator::instance().autoOnOffIU(isAuto, fromAbonent, unTarget);
}

void SignalSlotCommutator::emitLostedConnect(QSharedPointer<UnitNode>  un) {
    emit SignalSlotCommutator::instance().lostConnect(un);
}

void SignalSlotCommutator::emitRequestOnOffCommand(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget, const bool onOffValue) {
    emit SignalSlotCommutator::instance().requestOnOffCommand(isAuto, fromAbonent, unTarget, onOffValue);
}

void SignalSlotCommutator::emitLockOpenCloseCommand(bool out, QSharedPointer<UnitNode>  un, bool value) {
    emit SignalSlotCommutator::instance().lockOpenCloseCommand(out, un, value);
}

void SignalSlotCommutator::emitLockOpenCloseCommand(QSharedPointer<UnitNode>  un, bool value) {
    emit SignalSlotCommutator::instance().lockOpenCloseCommand(false, un, value);
}

void SignalSlotCommutator::emitChangeSelectUN(QSharedPointer<UnitNode>  un) {
    emit SignalSlotCommutator::instance().changeSelectUN(un);
}

void SignalSlotCommutator::emitRequestDK(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget) {
    emit SignalSlotCommutator::instance().requestDK(isAuto, fromAbonent, unTarget);
}

void SignalSlotCommutator::emitForcedNewDuty(bool out) {
    emit SignalSlotCommutator::instance().forcedNewDuty(out);
}

void SignalSlotCommutator::emitResetFlags(QSharedPointer<UnitNode> un) {
    emit SignalSlotCommutator::instance().resetFlags(un);
}

void SignalSlotCommutator::emitUpdateLabelOperator() {
    emit SignalSlotCommutator::instance().updateLabelOperator();
}

void SignalSlotCommutator::emitChangeCountIntegrationAbonent(int value) {
    emit SignalSlotCommutator::instance().changeCountIntegrationAbonent(value);
}
