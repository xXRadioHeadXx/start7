#include "../src/utils/SignalSlotCommutator.h"
#include <QSharedPointer>
#include <QDebug>

auto & SignalSlotCommutator::self()
{
    return SignalSlotCommutator::instance();
}

bool SignalSlotCommutator::getLocalBlockUpdJourMSG() const
{
    return blockUpdJourMSG;
}

void SignalSlotCommutator::setLocalBlockUpdJourMSG(bool newBlockUpdJourMSG)
{
    blockUpdJourMSG = newBlockUpdJourMSG;
}

bool SignalSlotCommutator::getLocalBlockUpdAllJourMSG() const
{
    return blockUpdAllJourMSG;
}

void SignalSlotCommutator::setLocalBlockUpdAllJourMSG(bool newBlockUpdAllJourMSG)
{
    blockUpdAllJourMSG = newBlockUpdAllJourMSG;
}

bool SignalSlotCommutator::getLocalBlockInsNewJourMSG() const
{
    return blockInsNewJourMSG;
}

void SignalSlotCommutator::setLocalBlockInsNewJourMSG(bool newBlockInsNewJourMSG)
{
    blockInsNewJourMSG = newBlockInsNewJourMSG;
}

bool SignalSlotCommutator::getBlockUpdAllJourMSG()
{
    return self().getLocalBlockUpdAllJourMSG();
}

void SignalSlotCommutator::setBlockUpdAllJourMSG(bool newBlockUpdAllJourMSG)
{
    self().setLocalBlockUpdAllJourMSG(newBlockUpdAllJourMSG);
}

bool SignalSlotCommutator::getBlockUpdJourMSG()
{
    return self().getLocalBlockUpdJourMSG();
}

void SignalSlotCommutator::setBlockUpdJourMSG(bool newBlockUpdJourMSG)
{
    self().setLocalBlockUpdJourMSG(newBlockUpdJourMSG);
}

bool SignalSlotCommutator::getBlockInsNewJourMSG()
{
    return self().getLocalBlockInsNewJourMSG();
}

void SignalSlotCommutator::setBlockInsNewJourMSG(bool newBlockInsNewJourMSG)
{
    self().setLocalBlockInsNewJourMSG(newBlockInsNewJourMSG);
}

void SignalSlotCommutator::emitInsNewCommandMSG(const uint32_t id) {
    emit self().insNewCommandMSG(id);
}

void SignalSlotCommutator::emitInsNewCommandMSG() {
    emit self().insNewCommandMSG();
}

void SignalSlotCommutator::emitInsNewJourMSG(const uint32_t id) {
    if(self().getLocalBlockInsNewJourMSG())
        return;
    emit self().insNewJourMSG(id);
}

void SignalSlotCommutator::emitInsNewJourMSG(JourEntity msg)
{
    qDebug()<<"SignalSlotCommutator::emitInsNewJourMSG(JourEntity msg)";

    if(self().getLocalBlockInsNewJourMSG())
        return;
    emit self().insNewJourMSG(msg);
}

void SignalSlotCommutator::emitInsNewJourMSG() {
    if(self().getLocalBlockInsNewJourMSG())
        return;
    emit self().insNewJourMSG();
}

void SignalSlotCommutator::emitUpdAllJourMSG() {
    if(self().getLocalBlockUpdAllJourMSG())
        return;
    emit self().updAllJourMSG();
}

void SignalSlotCommutator::emitUpdJourMSG(const uint32_t id) {
    if(self().getLocalBlockUpdAllJourMSG())
        return;
    emit self().updJourMSG(id);
}

void SignalSlotCommutator::emitUpdJourMSG() {
    if(self().getLocalBlockUpdJourMSG())
        return;
    emit self().updJourMSG();
}

void SignalSlotCommutator::emitUpdUN() {
    if(self().getLocalBlockUpdJourMSG())
        return;
    emit self().updUN();
}

void SignalSlotCommutator::emitUpdDataTreeUN() {
    emit self().updDataTreeUN();
}

void SignalSlotCommutator::emitStartDKWait(int interval) {
    emit self().startDKWait(interval);
}

void SignalSlotCommutator::emitStopDKWait() {
    emit self().stopDKWait();
}

void SignalSlotCommutator::emitEndDKWait() {
    emit self().endDKWait();
}

void SignalSlotCommutator::emitStartLockWait(int interval) {
    emit self().startLockWait(interval);
}

void SignalSlotCommutator::emitStartLockWait(int interval, int startInterval) {
    emit self().startLockWait(interval, startInterval);
}

void SignalSlotCommutator::emitStopLockWait() {
    emit self().stopLockWait();
}

void SignalSlotCommutator::emitEndLockWait() {
    emit self().endLockWait();
}

void SignalSlotCommutator::emitAutoOnOffIU(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget) {
    emit self().autoOnOffIU(isAuto, fromAbonent, unTarget);
}

void SignalSlotCommutator::emitLostedConnect(QSharedPointer<UnitNode>  un) {
    emit self().lostConnect(un);
}

void SignalSlotCommutator::emitRequestOnOffCommand(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget, const bool onOffValue) {
    emit self().requestOnOffCommand(isAuto, fromAbonent, unTarget, onOffValue);
}

void SignalSlotCommutator::emitLockOpenCloseCommand(bool out, QSharedPointer<UnitNode>  un, bool value) {
    emit self().lockOpenCloseCommand(out, un, value);
}

void SignalSlotCommutator::emitLockOpenCloseCommand(QSharedPointer<UnitNode>  un, bool value) {
    emit self().lockOpenCloseCommand(false, un, value);
}

void SignalSlotCommutator::emitChangeSelectUN(QSharedPointer<UnitNode>  un) {
    emit self().changeSelectUN(un);
}

void SignalSlotCommutator::emitRequestDK(const bool isAuto, const bool fromAbonent, const QSharedPointer<UnitNode> unTarget) {
    emit self().requestDK(isAuto, fromAbonent, unTarget);
}

void SignalSlotCommutator::emitForcedNewDuty(bool out) {
    emit self().forcedNewDuty(out);
}

void SignalSlotCommutator::emitResetFlags(QSharedPointer<UnitNode> un) {
    emit self().resetFlags(un);
}

void SignalSlotCommutator::emitUpdateLabelOperator() {
    emit self().updateLabelOperator();
}

void SignalSlotCommutator::emitChangeCountIntegrationAbonent(int value) {
    emit self().changeCountIntegrationAbonent(value);
}

void SignalSlotCommutator::emit_enable_updateListRecords()
{
    emit self().enable_updateListRecords();
}
