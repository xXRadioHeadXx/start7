//#include <QDebug>

#include "UnitNode.h"
#include "ServerSettingUtils.h"
#include "Icons.h"
#include "Icons_cfg.h"
#include "SignalSlotCommutator.h"
#include "global.h"
#include "swpblip/SWPBLIPType0x41.h"
#include "swpblip/SWPBLIPType0x42.h"
#include "swprlm/SWPRLMType0x31.h"
#include "swprlmc/SWPRLMCType0x31.h"
#include "swpblip/SWPSDBLIPType0x42.h"
#include "swpblip/SWPSDBLIPType0x41.h"
#include "swpblip/SWPIUBLIPType0x41.h"
#include "swpt4k/SWPT4KBODType0x32.h"
#include "swpt4k/SWPT4KBODType0x33.h"
#include "swpt4k/SWPT4KDDType0x34.h"
#include "swpsota/SWPSOTABODType0x32.h"
#include "swpsota/SWPSOTABODType0x33.h"
#include "swpsota/SWPSOTABODType0x34.h"
#include "swptg/SWPTGType0x31.h"
#include "swptg/SWPTGType0x34.h"
#include "swptg/SWPTGType0x33.h"
#include "swptg/SWPTGType0x32.h"
#include "swptg/SWPTGSubType0x32.h"
#include "swptg/SWPTGSubType0x33.h"
#include "swpt4k/SWPT4KBODType0x32.h"
#include "swpt4k/SWPT4KY4Type0x32.h"
#include "swpt4k/SWPT4KDDType0x32.h"
#include "swpt4k/SWPT4KDDCType0x32.h"
#include "swpt4k/SWPT4KBODType0x33.h"
#include "swpt4k/SWPT4KY4Type0x33.h"
#include "swpt4k/SWPT4KDDType0x33.h"
#include "swpt4k/SWPT4KDDCType0x33.h"
#include "swpt4k/SWPT4KDDCFType0x33.h"
#include "swpt4k/SWPT4KBODType0x33.h"
#include "swpt4k/SWPT4KBODType0x34.h"
#include "swpsota/SWPSOTABODType0x32.h"
#include "swpsota/SWPSOTAY4Type0x32.h"
#include "swpsota/SWPSOTADDType0x32.h"
#include "swpsota/SWPSOTADDCType0x32.h"
#include "swpsota/SWPSOTABODType0x33.h"
#include "swpsota/SWPSOTAY4Type0x33.h"
#include "swpsota/SWPSOTADDType0x33.h"
#include "swpsota/SWPSOTADDFType0x33.h"
#include "swpsota/SWPSOTABODType0x33.h"
#include "swpsota/SWPSOTABODType0x34.h"

#include "DataQueueItem.h"

#include "swpssoiblip/SWPSSOIBLIPType0x41.h"
#include "swpssoiblip/SWPSSOIBLIPType0x42.h"

#include <swpt4k/SWPT4KDDType0x34.h>

QSet<QString> UnitNode::getMetaNames() const
{
    return metaNames;
}

void UnitNode::resetMetaNames(const QString &value)
{
    metaNames.clear();
    setMetaNames(value);
}

void UnitNode::setMetaNames(const QString &value)
{
    metaNames.insert(value);
}

void UnitNode::setMetaNames(const QSet<QString> &value)
{
    metaNames += value;
}

void UnitNode::setType(int value)
{
    UnitNodeCFG::setType(value);
    matchEditableControl();
    matchEditableOnOff();
    matchNeedsPreamble();
}

void UnitNode::setBazalt(int value)
{
    UnitNodeCFG::setBazalt(value);
    matchEditableControl();
    matchEditableOnOff();
}

void UnitNode::setUdpTimeout(int value)
{
    int udpTimeout = qMax(50, value);

    UnitNodeCFG::setUdpTimeout(udpTimeout);

//    int maxBeatCount = 400;
//    if(50 != udpTimeout) {
//        maxBeatCount = (delayDisconnectStatus / udpTimeout) + 1;
//    }
//    setMaxCountStatusConnectRequesterWaitAnswer(maxBeatCount);
}

QSharedPointer<UnitNode> UnitNode::getParentUN() const
{
    return parentUN;
}

void UnitNode::setParentUN(QSharedPointer<UnitNode> value)
{
    parentUN = value;
}

//QSharedPointer<UnitNode> UnitNode::getTreeParentUN() const
//{
//    return treeParentUN;
//}

//void UnitNode::setTreeParentUN(QSharedPointer<UnitNode> value)
//{
//    treeParentUN = value;
//}

//QList<QSharedPointer<UnitNode> > UnitNode::getListTreeChilde() const
//{
//    return listTreeChilde;
//}

QList<QSharedPointer<UnitNode> > UnitNode::getListChilde() const
{
    return listChilde;
}

QPixmap UnitNode::getPxm() const
{
//    if(TypeUnitNodeEnum::SYSTEM == getType()) {
//        return Icons::fldr();
//    } else if(TypeUnitNodeEnum::GROUP == getType()) {
//        if(childCount())
//            return Icons::fldr();
//        else
//            return Icons::fldr_empt();
//    } else if(13 == getPublishedState() && !(TypeUnitNodeEnum::SD_BL_IP == getType() && 1 == getBazalt())) {
//        if(getControl()) {
//            return Icons::sqr_blu();
//        } else if(!getControl()) {
//            return Icons::sqr_blk_crs_blu();
//        }
//    } else if(TypeUnitNodeEnum::SD_BL_IP == getType()) {
//        const SWPSDBLIPType0x41 swp = swpSDBLIPType0x41();
//        if(0 == getBazalt()) {
//            if(getControl()
//            && swp.isNull()) {
//                return Icons::sqr_ylw();
//            } else if(!getControl()
//                   && swp.isNull()) {
//                return Icons::sqr_blk_crs_ylw();
//            } else if(1 == swp.isWasAlarm()
//                   && getControl()) {
//                return Icons::sqr_rd();
//            } else if(1 == swp.isWasAlarm()
//                   && !getControl()) {
//                return Icons::sqr_blk_crs_rd();
//            } else if(1 == swp.isAlarm()
//                   && getControl()) {
//                return Icons::sqr_rd();
//            } else if(1 == swp.isAlarm()
//                   && !getControl()) {
//                return Icons::sqr_blk_crs_rd();
//            } else if(1 == swp.isOff()
//                   && getControl()) {
//                return Icons::sqr_blk();
//            } else if(1 == swp.isOff()
//                   && !getControl()) {
//                return Icons::sqr_blk_crs_gry();
//            } else if(1 == swp.isNorm()
//                   && getControl()) {
//                return Icons::sqr_grn();
//            } else if(1 == swp.isNorm()
//                   && !getControl()) {
//                return Icons::sqr_blk_crs_grn();
//            } else if(getControl()) {
//                return Icons::sqr_ylw();
//            } else if(!getControl()) {
//                return Icons::sqr_blk_crs_ylw();
//            }
//        } else { // это узо
//            if(getControl()
//            && swp.isNull()) {
//                return Icons::sqr_ylw();
//            } else if(!getControl()
//                   && swp.isNull()) {
//                return Icons::sqr_blk_crs_ylw();
//            } else if(1 == swp.isOff()) {
//                return Icons::sqr_blk();
//            } else if(13 == getPublishedState()
//                   && 1 == swp.isAlarm()) {
//                return Icons::sqr_blu_opn();
//            } else if(13 == getPublishedState()
//                   && 1 == swp.isNorm()) {
//                return Icons::sqr_blu_cls();
//            } else if(1 == swp.isAlarm()) {
//                return Icons::sqr_rd_opn();
//            } else if(1 == swp.isNorm()) {
//                return Icons::sqr_grn_cls();
//            } else {
//                return Icons::sqr_ylw();
//            }
//        }

//    } else if(TypeUnitNodeEnum::IU_BL_IP == getType()) {
//        const SWPIUBLIPType0x41 swp = swpIUBLIPType0x41();
//        if(swp.isNull()) {
//            return Icons::sqr_ylw();
//        } else if(1 == swp.isOn()) {
//            return Icons::sqr_grn_crs2_rd();
//        } else if(1 == swp.isOff()) {
//            return Icons::sqr_grn_mns_gry();
//        } else
//            return Icons::sqr_ylw();
//    } else if(TypeUnitNodeEnum::RLM_C == getType()) {
//        const SWPRLMCType0x31 swp = swpRLMCType0x31();
//        if(getControl()
//        && swp.isNull()) {
//            return Icons::sqr_ylw();
//        } else if(!getControl()
//               && swp.isNull()) {
//            return Icons::sqr_blk_crs_ylw();
//        } else if(1 == swp.isOff()
//               && getControl()) {
//            return Icons::sqr_blk();
//        } else if(1 == swp.isOff()
//               && !getControl()) {
//            return Icons::sqr_blk_crs_gry();
//        } else if(1 == swp.isFault()
//               && getControl()) {
//            return Icons::sqr_blu();
//        } else if(1 == swp.isFault()
//               && !getControl()) {
//            return Icons::sqr_blk_crs_blu();
//        } else if(((1 == swp.isAlarm()
//                 || 1 == swp.isWasAlarm())
//                && !(getIsAutoDkInvolved()
//                  && getDkInvolved()))
//               && 1 == swp.isOn()
//               && getControl()) {
//            return Icons::sqr_rd();
//        } else if(((1 == swp.isAlarm()
//                 || 1 == swp.isWasAlarm())
//                && !(getIsAutoDkInvolved()
//                  && getDkInvolved()))
//               && 1 == swp.isOn()
//               && !getControl()) {
//            return Icons::sqr_blk_crs_rd();
//        } else if(1 == swp.isNorm()
//               && getControl()) {
//            return Icons::sqr_grn();
//        } else if(1 == swp.isNorm()
//               && !getControl()) {
//            return Icons::sqr_blk_crs_grn();
//        } else if(getControl()) {
//            return Icons::sqr_grn();
//        } else if(!getControl()) {
//            return Icons::sqr_blk_crs_grn();
//        }
//    } else if(TypeUnitNodeEnum::RLM_KRL == getType()) {
//        const SWPRLMType0x31 swp = swpRLMType0x31();
//        if(getControl()
//        && swp.isNull()) {
//            return Icons::sqr_ylw();
//        } else if(!getControl()
//               && swp.isNull()) {
//            return Icons::sqr_blk_crs_ylw();
//        } else if(1 == swp.isOff()
//               && getControl()) {
//            return Icons::sqr_blk();
//        } else if(1 == swp.isOff()
//               && !getControl()) {
//            return Icons::sqr_blk_crs_gry();
//        } else if(1 == swp.isFault()
//               && getControl()) {
//            return Icons::sqr_blu();
//        } else if(1 == swp.isFault()
//               && !getControl()) {
//            return Icons::sqr_blk_crs_blu();
//        } else if(((1 == swp.isAlarm()
//                 || 1 == swp.isWasAlarm())
//                && !(getIsAutoDkInvolved()
//                  && getDkInvolved()))
//               && 1 == swp.isOn()
//               && getControl()) {
//            return Icons::sqr_rd();
//        } else if(((1 == swp.isAlarm()
//                 || 1 == swp.isWasAlarm())
//                && !(getIsAutoDkInvolved()
//                  && getDkInvolved()))
//               && 1 == swp.isOn()
//               && !getControl()) {
//            return Icons::sqr_blk_crs_rd();
//        } else if(1 == swp.isNorm()
//               && getControl()) {
//            return Icons::sqr_grn();
//        } else if(1 == swp.isNorm()
//               && !getControl()) {
//            return Icons::sqr_blk_crs_grn();
//        } else if(getControl()) {
//            return Icons::sqr_grn();
//        } else if(!getControl()) {
//            return Icons::sqr_blk_crs_grn();
//        }
//    } else if(TypeUnitNodeEnum::TG == getType() || TypeUnitNodeEnum::TG_Base == getType()) {
//        const SWPTGType0x31 swp31 = swpTGType0x31();
//        const SWPTGType0x32 swp32 = swpTGType0x32();
//        const SWPTGType0x33 swp33 = swpTGType0x33();
//        const SWPTGType0x34 swp34 = swpTGType0x34();
//        if(getControl() && swp31.isNull() && swp32.isNull() && swp33.isNull() && swp34.isNull()) {
//            return Icons::sqr_ylw();
//        } else if(!getControl() && swp31.isNull() && swp32.isNull() && swp33.isNull() && swp34.isNull()) {
//            return Icons::sqr_blk_crs_ylw();
//        } else if(!swp31.isNull() && (swp32.cdate() < swp31.cdate() && swp33.cdate() < swp31.cdate())) {
//            if(1 == swp31.isOff() && getControl()) {
//                return Icons::sqr_blk();
//            } else if(1 == swp31.isOff() && !getControl()) {
//                return Icons::sqr_blk_crs_gry();
//            } else if((((1 == swp31.isAlarm()
//                      || 1 == swp31.isInAlarm()
//                      || 1 == swp31.isOutAlarm())
//                     && !(getIsAutoDkInvolved()
//                       && getDkInvolved()))
//                     || 1 == swp31.isOpened()
//                     || 1 == swp31.isWasOpened()
//                     || 1 == swp31.isInOpened())
//                    && getControl()) {
//                return Icons::sqr_rd();
//            } else if((((1 == swp31.isAlarm()
//                      || 1 == swp31.isInAlarm()
//                      || 1 == swp31.isOutAlarm())
//                     && !(getIsAutoDkInvolved()
//                       && getDkInvolved()))
//                     || 1 == swp31.isOpened()
//                     || 1 == swp31.isWasOpened()
//                     || 1 == swp31.isInOpened())
//                    && !getControl()) {
//                return Icons::sqr_blk_crs_rd();
//            } else if(1 == swp31.isNorm() && getControl()) {
//                return Icons::sqr_grn();
//            } else if(1 == swp31.isNorm() && !getControl()) {
//                return Icons::sqr_blk_crs_grn();
//            } else if(getControl()) {
//                return Icons::sqr_grn();
//            } else if(!getControl()) {
//                return Icons::sqr_blk_crs_grn();
//            }
//        } else if(!swp32.isNull() && (swp31.cdate() < swp32.cdate() && swp33.cdate() < swp32.cdate())) {
//            if(1 == swp32.C(getNum2()).isFault() && getControl()) {
//                return Icons::sqr_blu();
//            } else if(1 == swp32.C(getNum2()).isFault() && !getControl()) {
//                return Icons::sqr_blk_crs_blu();
//            } else if((((1 == swp32.C(getNum2()).isAlarm()
//                      || 1 == swp32.C(getNum2()).isOutAlarm()
//                      || 1 == swp32.C(getNum2()).isInAlarm())
//                     && !(getIsAutoDkInvolved()
//                       && getDkInvolved()))
//                     || 1 == swp32.C(getNum2()).isOpened()
//                     || 1 == swp32.C(getNum2()).isWasOpened()
//                     || 1 == swp32.C(getNum2()).isInOpened())
//                    && getControl()) {
//                return Icons::sqr_rd();
//            } else if((((1 == swp32.C(getNum2()).isAlarm()
//                      || 1 == swp32.C(getNum2()).isOutAlarm()
//                      || 1 == swp32.C(getNum2()).isInAlarm())
//                     && !(getIsAutoDkInvolved()
//                       && getDkInvolved()))
//                     || 1 == swp32.C(getNum2()).isOpened()
//                     || 1 == swp32.C(getNum2()).isWasOpened()
//                     || 1 == swp32.C(getNum2()).isInOpened())
//                    && !getControl()) {
//                return Icons::sqr_blk_crs_rd();
//            } else if(1 == swp32.C(getNum2()).isNorm() && getControl()) {
//                return Icons::sqr_grn();
//            } else if(1 == swp32.C(getNum2()).isNorm() && !getControl()) {
//                return Icons::sqr_blk_crs_grn();
//            } else if(getControl()) {
//                return Icons::sqr_grn();
//            } else if(!getControl()) {
//                return Icons::sqr_blk_crs_grn();
//            }
//        } else if(!swp33.isNull() && (swp31.cdate() < swp33.cdate() && swp32.cdate() < swp33.cdate())) {
//            if(1 == swp33.C(getNum2()).isFault() && getControl()) {
//                return Icons::sqr_blu();
//            } else if(1 == swp33.C(getNum2()).isFault() && !getControl()) {
//                return Icons::sqr_blk_crs_blu();
//            } else if((((1 == swp33.C(getNum2()).isAlarm()
//                      || 1 == swp33.C(getNum2()).isInAlarm()
//                      || 1 == swp33.C(getNum2()).isOutAlarm())
//                     && !(getIsAutoDkInvolved()
//                       && getDkInvolved()))
//                     || 1 == swp33.C(getNum2()).isOpened()
//                     || 1 == swp33.C(getNum2()).isWasOpened()
//                     || 1 == swp33.C(getNum2()).isInOpened())
//                    && getControl()) {
//                return Icons::sqr_rd();
//            } else if((((1 == swp33.C(getNum2()).isAlarm()
//                      || 1 == swp33.C(getNum2()).isInAlarm()
//                      || 1 == swp33.C(getNum2()).isOutAlarm())
//                     && !(getIsAutoDkInvolved()
//                       && getDkInvolved()))
//                     || 1 == swp33.C(getNum2()).isOpened()
//                     || 1 == swp33.C(getNum2()).isWasOpened()
//                     || 1 == swp33.C(getNum2()).isInOpened())
//                    && !getControl()) {
//                return Icons::sqr_blk_crs_rd();
//            } else if(1 == swp33.C(getNum2()).isNorm() && getControl()) {
//                return Icons::sqr_grn();
//            } else if(1 == swp33.C(getNum2()).isNorm() && !getControl()) {
//                return Icons::sqr_blk_crs_grn();
//            } else if(getControl()) {
//                return Icons::sqr_grn();
//            } else if(!getControl()) {
//                return Icons::sqr_blk_crs_grn();
//            }
//        } /*else if(!swp34.isNull()) {

//        } */else if(getControl()) {
//            return Icons::sqr_ylw();
//        } else if(!getControl()) {
//            return Icons::sqr_blk_crs_ylw();
//        }
//    }

    return QPixmap();
}

int UnitNode::getDkStatus() const
{
    return dkStatus;
}

void UnitNode::setDkStatus(int value)
{
    dkStatus = value;
//    updDoubl();
}

bool UnitNode::getDkInvolved() const
{
    return dkInvolved;
}

void UnitNode::setDkInvolved(bool value)
{
    dkInvolved = value;
    isAutoDkInvolved = isAutoDkInvolved && dkInvolved;
//    updDoubl();
}

QSet<QSharedPointer<UnitNode> > UnitNode::getDoubles() const
{
    return doubles;
}

void UnitNode::setDoubles(const QSet<QSharedPointer<UnitNode> > &value)
{
    doubles = value;
    QMutableSetIterator<QSharedPointer<UnitNode> > i(doubles);
    while (i.hasNext()) {
        if (this == i.next().data())
            i.remove();
    }
}

void UnitNode::setDoubles(QSharedPointer<UnitNode> value)
{
    doubles.insert(value);
    QMutableSetIterator<QSharedPointer<UnitNode> > i(doubles);
    while (i.hasNext()) {
        if (this == i.next().data())
            i.remove();
    }}

void UnitNode::updDoubl()
{
    for(auto c : as_const(this->doubles)) {
        c->setStateWords(this->getStateWords());
        c->setDkStatus(this->getDkStatus());
        c->setDkInvolved(this->getDkInvolved());
        c->setParentUN(this->getParentUN());
        c->setTimeIntervalStatusRequest(this->getTimeIntervalStatusRequest());
        c->setControl(this->getControl());
        c->setX(this->getX());
        c->setY(this->getY());
        c->setDkInvolved(this->getDkInvolved());
        c->setIsAutoDkInvolved(this->getIsAutoDkInvolved());
        c->setWaitAutoCommand(this->getWaitAutoCommand());
        c->setPublishedState(this->getPublishedState());
    }
}

StateWord UnitNode::getStateWord(const uint8_t key) const
{
    if(0 != stateWords.count(key)) {
        try {
            return stateWords.at(key);
        }  catch (const std::out_of_range &e) {
            return StateWord();
        }
    }
    return StateWord();
}

void UnitNode::setStateWord(const uint8_t key, const StateWord &value)
{
    stateWords[key] = value;
}

//void UnitNode::deleteChild(int row)
//{
//    this->listChilde.removeAt(row);
//    this->listTreeChilde.removeAt(row);
//}

//void UnitNode::deleteAll()
//{
//    this->listChilde.clear();
//    this->listTreeChilde.clear();
//}

int UnitNode::isConnected() const
{
    if(getStateWord(0x41u).getByteWord().isEmpty() &&
       getStateWord(0x31u).getByteWord().isEmpty() &&
       getStateWord(0x32u).getByteWord().isEmpty() &&
       getStateWord(0x33u).getByteWord().isEmpty() &&
       getStateWord(0x34u).getByteWord().isEmpty())
        return 0;
    else
        return 1;
}

bool UnitNode::isEditableControl() const
{
    return editableControl;
}

void UnitNode::resetCountStatusConnectRequesterWaitAnswer()
{
    countStatusConnectRequesterWaitAnswer = 0;
}

void UnitNode::incrementCountStatusConnectRequesterWaitAnswer()
{
    countStatusConnectRequesterWaitAnswer++;
}

void UnitNode::decrementCountStatusConnectRequesterWaitAnswer()
{
    countStatusConnectRequesterWaitAnswer--;
}

int UnitNode::getCountStatusConnectRequesterWaitAnswer() const
{
    return countStatusConnectRequesterWaitAnswer;
}

void UnitNode::setCountStatusConnectRequesterWaitAnswer(int value)
{
//    if(countStatusConnectRequesterWaitAnswer == value)
//        return;
    countStatusConnectRequesterWaitAnswer = value;
//    qDebug() << this->toString() << "::setCountStatusConnectRequesterWaitAnswer(" << countStatusConnectRequesterWaitAnswer << ")";
}

int UnitNode::getMaxCountStatusConnectRequesterWaitAnswer() const
{
    return maxCountStatusConnectRequesterWaitAnswer;
}

void UnitNode::setMaxCountStatusConnectRequesterWaitAnswer(int value)
{
//    if(maxCountStatusConnectRequesterWaitAnswer == value)
//        return;
    maxCountStatusConnectRequesterWaitAnswer = value;
//    qDebug() << this->toString() << "::setMaxCountStatusConnectRequesterWaitAnswer(" << maxCountStatusConnectRequesterWaitAnswer << ") ~ " << maxCountStatusConnectRequesterWaitAnswer * getUdpTimeout() << "ms";
}

int UnitNode::getNeededStateWordType() const
{
    return neededStateWordType;
}

void UnitNode::setNeededStateWordType(int value)
{
    neededStateWordType = value;
}
int UnitNode::getDefaultNeededStateWordType() const
{
    return defaultNeededStateWordType;
}

void UnitNode::setDefaultNeededStateWordType(int value)
{
    defaultNeededStateWordType = value;
}

int UnitNode::getPublishedState() const
{
    return publishedState;
}

void UnitNode::setPublishedState(int newPublishedState)
{
    publishedState = newPublishedState;
}

int UnitNode::getMetaEntity() const
{
    return metaEntity;
}

void UnitNode::setMetaEntity(int newMetaEntity)
{
    metaEntity = newMetaEntity;
}

std::map<const uint8_t, StateWord> UnitNode::getStateWords() const
{
    return stateWords;
}

void UnitNode::setStateWords(const std::map<const uint8_t, StateWord> &value)
{
    stateWords = value;
}

bool UnitNode::getIsAutoDkInvolved() const
{
    return isAutoDkInvolved;
}

void UnitNode::setIsAutoDkInvolved(bool newIsAutoDkInvolved)
{
    isAutoDkInvolved = newIsAutoDkInvolved;
}

bool UnitNode::getWaitAutoCommand() const
{
    return waitAutoCommand;
}

void UnitNode::setWaitAutoCommand(bool newWaitAutoCommand)
{
    waitAutoCommand = newWaitAutoCommand;
}

bool UnitNode::takeResetWaitAutoCommand()
{
    auto res = waitAutoCommand;
    waitAutoCommand = false;
    return res;
}

void UnitNode::calkStateUN(QString &comment, int &code) const
{
    if(TypeUnitNodeEnum::SD_BL_IP == getType() && !swpSDBLIPType0x41().isNull()) {
        const auto& swpCurrent = swpSDBLIPType0x41();

        if(1 == swpCurrent.isOff()) {
            comment = QObject::tr("Выкл");
            code = 100;
        } else if(1 == swpCurrent.isOn() &&
                  1 == swpCurrent.isAlarm() &&
                  1 == swpCurrent.isWasAlarm()) {
            //сохранение Тревога или Норма
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        } else if(1 == swpCurrent.isOn() &&
                  1 == swpCurrent.isNorm()) {
            comment = QObject::tr("Норма");
            code = 1;
        } else if(1 == swpCurrent.isOn() &&
                  1 != swpCurrent.isNorm()) {
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        }
    } else if(TypeUnitNodeEnum::IU_BL_IP == getType() && !swpIUBLIPType0x41().isNull()) {
        const auto& swpCurrent = swpIUBLIPType0x41();

        if(1 == swpCurrent.isOff()) {
            comment = QObject::tr("Выкл");
            code = 100;
        } else if(1 == swpCurrent.isOn()) {
            comment = QObject::tr("Вкл");
            code = 101;
        }
    } else if(TypeUnitNodeEnum::RLM_KRL == getType() && !swpRLMType0x31().isNull()) {
        const auto& swpCurrent = swpRLMType0x31();

        if(1 == swpCurrent.isOff()) {
            comment = QObject::tr("Выкл");
            code = 100;
        } else if(1 == swpCurrent.isFault()) {
            //сохранение неисправность или Норма
            comment = QObject::tr("Неисправность");
            code = 12;
        } else if(1 == swpCurrent.isOn()
               && 1 == swpCurrent.isOpened()
               && 1 == swpCurrent.isWasOpened()) {
            //сохранение Тревога или Норма
            comment = QObject::tr("Тревога-ВСКРЫТИЕ");
            code = 21;
        } else if(1 == swpCurrent.isOn()
               && 1 == swpCurrent.isAlarm()
               && 1 == swpCurrent.isWasAlarm()) {
            //сохранение Тревога или Норма
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        } else if(1 == swpCurrent.isOn()
               && 1 == swpCurrent.isNorm()) {
            comment = QObject::tr("Норма");
            code = 1;
        } else if(1 == swpCurrent.isOn() &&
                  1 != swpCurrent.isNorm()) {
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        }
    } else if(TypeUnitNodeEnum::RLM_C == getType() && !swpRLMCType0x31().isNull()) {
        const auto& swpCurrent = swpRLMCType0x31();

        if(1 == swpCurrent.isOff()) {
            comment= QObject::tr("Выкл");
            code = 100;
        } else if(1 == swpCurrent.isFault()) {
            //сохранение неисправность или Норма
            comment = QObject::tr("Неисправность");
            code = 12;
        } else if(1 == swpCurrent.isOn()
               && 1 == swpCurrent.isAlarm()
               && 1 == swpCurrent.isWasAlarm()) {
            //сохранение Тревога или Норма
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        } else if(1 == swpCurrent.isOn()
               && 1 == swpCurrent.isNorm()) {
            comment = QObject::tr("Норма");
            code = 1;
        } else if(1 == swpCurrent.isOn() &&
                  1 != swpCurrent.isNorm()) {
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        }
    } else if(TypeUnitNodeEnum::TG == getType() && !swpTGType0x33().isNull()) {
        const auto& swpCurrent = swpTGType0x33();
        const auto& swpCurrentCi = swpCurrent.C(getNum2());

        if(1 == swpCurrentCi.isFault()) {
            //сохранение неисправность или Норма
            comment = QObject::tr("Неисправность");
            code = 12;
        } else if(1 == swpCurrentCi.isOpened()) {
            //сохранение Тревога или Норма
            comment = QObject::tr("Тревога-ВСКРЫТИЕ");
            code = 21;
        } else if(1 == swpCurrentCi.isAlarm()) {
            //сохранение Тревога или Норма
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        } else if(1 == swpCurrentCi.isNorm()) {
            comment = QObject::tr("Норма");
            code = 1;
        } else if(1 != swpCurrentCi.isNorm()) {
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        }
    } else if(TypeUnitNodeEnum::TG == getType() && !swpTGType0x32().isNull()) {
        const auto& swpCurrent = swpTGType0x32();
        const auto& swpCurrentCi = swpCurrent.C(getNum2());

        if(1 == swpCurrentCi.isFault()) {
            //сохранение неисправность или Норма
            comment = QObject::tr("Неисправность");
            code = 12;
        } else if(1 == swpCurrentCi.isOpened()) {
            //сохранение Тревога или Норма
            comment = QObject::tr("Тревога-ВСКРЫТИЕ");
            code = 21;
        } else if(1 == swpCurrentCi.isAlarm()) {
            //сохранение Тревога или Норма
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        } else if(1 == swpCurrentCi.isNorm()) {
            comment = QObject::tr("Норма");
            code = 1;
        } else if(1 != swpCurrentCi.isNorm()) {
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        }
    } else if(TypeUnitNodeEnum::TG == getType() && !swpTGType0x31().isNull()) {
        const auto& swpCurrent = swpTGType0x31();

        if(1 == swpCurrent.isOff()) {
            comment = QObject::tr("Выкл");
            code = 100;
        } else if(1 == swpCurrent.isOn()
                  && 1 == swpCurrent.isOpened()
                  && 1 == swpCurrent.isWasOpened()) {
            //сохранение Тревога или Норма
            comment = QObject::tr("Тревога-ВСКРЫТИЕ");
            code = 21;
        } else if(1 == swpCurrent.isOn()
               && 1 == swpCurrent.isAlarm()
               && 1 == swpCurrent.isWasAlarm()) {
            //сохранение Тревога или Норма
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        } else if(1 == swpCurrent.isOn()
               && 1 == swpCurrent.isNorm()) {
            comment = QObject::tr("Норма");
            code = 1;
        } else if(1 == swpCurrent.isOn() &&
                  1 != swpCurrent.isNorm()) {
            comment = QObject::tr("Тревога-СРАБОТКА");
            code = 20;
        }
    }

    if((-1 == getPublishedState() || 10 == getPublishedState()) && !comment.isEmpty()) {
        comment += " (начальное состояние)";
    }
}

bool UnitNode::getNeedPostponeQueueMsg() const
{
    return needPostponeQueueMsg;
}

void UnitNode::setNeedPostponeQueueMsg(bool newNeedPostponeQueueMsg)
{
    needPostponeQueueMsg = newNeedPostponeQueueMsg;
}

int UnitNode::getTimeStatusConnectRequesterWaitAnswer() const
{
    return timeStatusConnectRequesterWaitAnswer;
}

void UnitNode::setTimeStatusConnectRequesterWaitAnswer(int newTimeStatusConnectRequesterWaitAnswer)
{
    timeStatusConnectRequesterWaitAnswer = newTimeStatusConnectRequesterWaitAnswer;
}

void UnitNode::resetTimeStatusConnectRequesterWaitAnswer()
{
    setTimeStatusConnectRequesterWaitAnswer(0);
}

void UnitNode::incrementTimeStatusConnectRequesterWaitAnswer(int incrementDelay)
{
    setTimeStatusConnectRequesterWaitAnswer(getTimeStatusConnectRequesterWaitAnswer() + incrementDelay);
}

void UnitNode::decrementTimeStatusConnectRequesterWaitAnswer(int decrementDelay)
{
    setTimeStatusConnectRequesterWaitAnswer(getTimeStatusConnectRequesterWaitAnswer() < decrementDelay ? 0 : getTimeStatusConnectRequesterWaitAnswer() - decrementDelay);
}

QSharedPointer<UnitNode> UnitNode::getInterrogationUN() const
{
    return interrogationUN;
}

void UnitNode::setInterrogationUN(QSharedPointer<UnitNode> newInterrogationUN)
{
    interrogationUN = newInterrogationUN;
}

bool UnitNode::isClearedAlarm() const
{
    return -1 == getClearedAlarm();
}

int UnitNode::getClearedAlarm() const
{
    return clearedAlarm;
}

void UnitNode::setClearedAlarm(int newClearedAlarm)
{
    clearedAlarm = newClearedAlarm;
}

void UnitNode::resetClearedAlarm()
{
    setClearedAlarm(-1);
}

void UnitNode::matchEditableControl()
{
    if(!editableControl &&
            ((TypeUnitNodeEnum::SSOI_SD_BL_IP == getType() && 0 == getBazalt())
          || (TypeUnitNodeEnum::SD_BL_IP == getType() && 0 == getBazalt())
          || TypeUnitNodeEnum::RLM_C == getType()
          || TypeUnitNodeEnum::RLM_KRL == getType()
          || TypeUnitNodeEnum::TG == getType()
          || TypeUnitNodeEnum::TG_Base == getType()
          || TypeUnitNodeEnum::BOD_T4K_M == getType()
          || TypeUnitNodeEnum::Y4_T4K_M == getType()
          || TypeUnitNodeEnum::DD_T4K_M == getType()
          || TypeUnitNodeEnum::BOD_SOTA == getType()
          || TypeUnitNodeEnum::Y4_SOTA == getType()
          || TypeUnitNodeEnum::DD_SOTA == getType()))
        editableControl = true;
}

void UnitNode::matchEditableOnOff()
{
    if(!editableOnOff &&
       ((0 == getBazalt() && TypeUnitNodeEnum::SSOI_SD_BL_IP == getType())
     || (0 == getBazalt() && TypeUnitNodeEnum::SD_BL_IP == getType())
     || TypeUnitNodeEnum::IU_BL_IP == getType()
     || TypeUnitNodeEnum::SSOI_IU_BL_IP == getType()
     || TypeUnitNodeEnum::RLM_C == getType()
     ||  TypeUnitNodeEnum::RLM_KRL == getType()/* ||
        TypeUnitNode::TG == getType()*/))
        editableOnOff = true;
}

bool UnitNode::isNeedsPreamble() const
{
    return needsPreamble;
}

void UnitNode::matchNeedsPreamble()
{
    if(!needsPreamble &&
       (TypeUnitNodeEnum::SSOI_SD_BL_IP == getType()
     || TypeUnitNodeEnum::SSOI_IU_BL_IP == getType()
     || TypeUnitNodeEnum::SSOI_BL_IP == getType()

     || TypeUnitNodeEnum::RLM_C == getType()

     || TypeUnitNodeEnum::RLM_KRL == getType()

     || TypeUnitNodeEnum::TG == getType()
     || TypeUnitNodeEnum::TG_Base == getType()

     || TypeUnitNodeEnum::BOD_T4K_M == getType()
     || TypeUnitNodeEnum::Y4_T4K_M == getType()
     || TypeUnitNodeEnum::DD_T4K_M == getType()

     || TypeUnitNodeEnum::BOD_SOTA == getType()
     || TypeUnitNodeEnum::Y4_SOTA == getType()
     || TypeUnitNodeEnum::DD_SOTA == getType()))
        needsPreamble = true;
}

bool UnitNode::isEditableOnOff() const
{
    return editableOnOff;
}

UnitNode::UnitNode(const QSharedPointer<UnitNode> parent) :
    /*UnitNodeCFG(static_cast<UnitNodeCFG*>(parent.data()))
  , */UnitNodeTreeItem(parent)
{
    this->done=false;
    this->parentUN = parent;
}

const SWPBLIPType0x41 UnitNode::swpBLIPType0x41() const {return SWPBLIPType0x41(getStateWord(0x41u));}
const SWPSDBLIPType0x41 UnitNode::swpSDBLIPType0x41() const {return SWPSDBLIPType0x41(getStateWord(0x41u), getNum2());}
const SWPIUBLIPType0x41 UnitNode::swpIUBLIPType0x41() const {return SWPIUBLIPType0x41(getStateWord(0x41u), getNum2());}
const SWPSSOIBLIPType0x41 UnitNode::swpSSOIBLIPType0x41() const {return SWPSSOIBLIPType0x41(getStateWord(0x41u));}
const SWPSSOISDBLIPType0x41 UnitNode::swpSSOISDBLIPType0x41() const {return SWPSSOISDBLIPType0x41(getStateWord(0x41u), getNum2());}
const SWPSSOIIUBLIPType0x41 UnitNode::swpSSOIIUBLIPType0x41() const {return SWPSSOIIUBLIPType0x41(getStateWord(0x41u), getNum2());}
const SWPSSOIBLIPType0x42 UnitNode::swpSSOIBLIPType0x42() const {return SWPSSOIBLIPType0x42(getStateWord(0x42u));}
const SWPSSOISDBLIPType0x42 UnitNode::swpSSOISDBLIPType0x42() const {return SWPSSOISDBLIPType0x42(getStateWord(0x42u), getNum2());}
const SWPBLIPType0x42 UnitNode::swpBLIPType0x42() const {return SWPBLIPType0x42(getStateWord(0x42u));}
const SWPSDBLIPType0x42 UnitNode::swpSDBLIPType0x42() const {return SWPSDBLIPType0x42(getStateWord(0x42u), getNum2());}
const SWPRLMType0x31 UnitNode::swpRLMType0x31() const {return SWPRLMType0x31(getStateWord(0x31u));}
const SWPRLMCType0x31 UnitNode::swpRLMCType0x31() const {return SWPRLMCType0x31(getStateWord(0x31u));}
const SWPTGType0x31 UnitNode::swpTGType0x31() const {return SWPTGType0x31(getStateWord(0x31u));}
const SWPTGType0x34 UnitNode::swpTGType0x34() const {return SWPTGType0x34(getStateWord(0x34u));}
const SWPTGType0x33 UnitNode::swpTGType0x33() const {return SWPTGType0x33(getStateWord(0x33u));}
const SWPTGType0x32 UnitNode::swpTGType0x32() const {return SWPTGType0x32(getStateWord(0x32u));}
const SWPT4KBODType0x32 UnitNode::swpT4KBODType0x32() const {return SWPT4KBODType0x32(getStateWord(0x32u));}
const SWPSOTABODType0x32 UnitNode::swpSOTABODType0x32() const {return SWPSOTABODType0x32(getStateWord(0x32u));}
const SWPT4KBODType0x33 UnitNode::swpT4KBODType0x33() const {return SWPT4KBODType0x33(getStateWord(0x33u));}
const SWPSOTABODType0x33 UnitNode::swpSOTABODType0x33() const {return SWPSOTABODType0x33(getStateWord(0x33u));}
const SWPT4KBODType0x34 UnitNode::swpT4KBODType0x34() const {return SWPT4KBODType0x34(getStateWord(0x34u));}
const SWPSOTABODType0x34 UnitNode::swpSOTABODType0x34() const {return SWPSOTABODType0x34(getStateWord(0x34u));}

const QList<QSharedPointer<ManagerSingleMsg>> &UnitNode::getListManagersSingleMsg()
{
    return queueManagersSingleMsg;
}

bool UnitNode::pushBackUniqManagerSingleMsg(const QSharedPointer<ManagerSingleMsg> &mngr){
    for(const auto& content : as_const(queueManagersSingleMsg)) {
        if(content.data() == mngr.data())
            return false;
        if(content->equale(*mngr.data()))
            return false;
    }
    queueManagersSingleMsg.push_back(mngr);
    return true;
};

QSharedPointer<ManagerSingleMsg> UnitNode::takeFirstManagerSingleMsg() {
    if(!queueManagersSingleMsg.isEmpty())
        return queueManagersSingleMsg.takeFirst();
    return QSharedPointer<ManagerSingleMsg>();
}

QSharedPointer<ManagerSingleMsg> UnitNode::getFirstManagerSingleMsg()
{
    if(!queueManagersSingleMsg.isEmpty())
        return queueManagersSingleMsg.first();
    return QSharedPointer<ManagerSingleMsg>();
};

const QQueue<DataQueueItem> &UnitNode::getQueueMsg()
{
    return queueMsg;
}

void UnitNode::pushUniqQueueMsg(const DataQueueItem &msg){
    for(const auto& content : as_const(queueMsg)) {
        if(content.data() == msg.data())
            return;
    }
    queueMsg.enqueue(msg);
};

DataQueueItem UnitNode::pullQueueMsg() {
    if(!queueMsg.isEmpty())
        return queueMsg.dequeue();
    return DataQueueItem();
};

UnitNode::UnitNode(const UnitNode & parent) :
//    UnitNodeCFG(static_cast<UnitNodeCFG>(parent)),
    UnitNodeTreeItem(),
    stateWords(parent.stateWords),
    metaNames(parent.metaNames),
    parentUN(parent.parentUN),
    dkStatus(parent.dkStatus),
    dkInvolved(parent.dkInvolved),
    isAutoDkInvolved(parent.isAutoDkInvolved),
    waitAutoCommand(parent.waitAutoCommand),
    publishedState(parent.publishedState)
{
    this->done=false;
    UnitNodeCFG::operator=(parent);
    TreeItem::operator=(parent);
    setStateWords(parent.getStateWords());
    setMetaNames(parent.getMetaNames());

    setDkStatus(parent.getDkStatus());
    setDkInvolved(parent.getDkInvolved());
    setPublishedState(parent.getPublishedState());

    setIsAutoDkInvolved(parent.getIsAutoDkInvolved());
    setWaitAutoCommand(parent.getWaitAutoCommand());

    matchEditableControl();
    matchEditableOnOff();
    matchNeedsPreamble();
}

UnitNode::~UnitNode()
{
//    qDebug() << "UnitNode::~UnitNode("<<this->toString()<<")";
}

UnitNode & UnitNode::operator=(const UnitNode& c) {
    UnitNodeCFG::operator=(c);
    TreeItem::operator=(c);
    setStateWords(c.getStateWords());
    setMetaNames(c.getMetaNames());

    setDkStatus(c.getDkStatus());
    setDkInvolved(c.getDkInvolved());
    setPublishedState(c.getPublishedState());

    setIsAutoDkInvolved(c.getIsAutoDkInvolved());
    setWaitAutoCommand(c.getWaitAutoCommand());

    matchEditableControl();
    matchEditableOnOff();
    matchNeedsPreamble();

    return *this;
}

bool UnitNode::operator>(const UnitNode & un) const
{
    if(0 >this->getUdpAdress().compare(un.getUdpAdress(), Qt::CaseInsensitive)) {
        return false;
    }

    if(this->getUdpPort() < un.getUdpPort()) {
        return false;
    }

    if(this->getType() < un.getType()) {
        return false;
    }

    if(this->getNum1() < un.getNum1()) {
        return false;
    }

    if(this->getNum2() < un.getNum2()) {
        return false;
    }

    if(this->getNum2() < un.getNum2()) {
        return false;
    }

    return true;
}

QVariant UnitNode::dataTreeColumn(int column) const
{
    switch(column)
    {
        case 0:
        {
            return this->getDkInvolved() ? tr("ДК") : "";
        }
        case 1:
        {
#ifdef QT_DEBUG
            QString str = "{%7 ps:%1, n1:%2, n2:%3, n3:%4, dbl:%5} %6";
            QString dbl;
//            for(const auto& d : getDoubles()) {
//                dbl.append(d->getName());
//                dbl.append(",");
//            }
//            dbl.append("}");
//            dbl.prepend("{");

//            QMap<int, QString> mapDKCiclStatus = {
//                {0,"DKIgnore"},
//                {1,"DKReady"},
//                {2,"DKNorm"},
//                {3,"DKWasAlarn"},
//                {4,"DKWas"},
//                {5,"DKDone"},
//                {-1,"DKWrong"}
//            };
            QString dk;
            const auto& swp31 = swpTGType0x31();
            const auto& swp32 = swpTGType0x32().C(getNum2());
            const auto& swp33 = swpTGType0x33();
            if(!swp31.isNull() && (swp32.cdate() < swp31.cdate() && swp33.cdate() < swp31.cdate())) {
                dk.append(swp31.isExistDK() ? "1" : "0").append(swp31.isWasDK() ? "1" : "0");
            } else if(!swp32.isNull() && (swp31.cdate() < swp32.cdate() && swp33.cdate() < swp32.cdate())) {
                dk.append(swp32.isExistDK()).append(swp32.isWasDK());
            } else if(!swp33.isNull() && (swp31.cdate() < swp33.cdate() && swp32.cdate() < swp33.cdate())) {
                dk.append(swp33.isExistDK()).append(swp33.isWasDK());
            }
            str = str.arg(QString::number(getPublishedState()),
                          QString::number(getNum1()),
                          QString::number(getNum2()),
                          QString::number(getNum3()),
                          dbl,
                          getName(),
//                          mapDKCiclStatus.value(getDkStatus())
                          dk
                          );
            return str;
#else
        return this->getName();
#endif
        }
        default:
            return QVariant();
    }

    return QVariant();
}

//void UnitNode::addTreeChild(QSharedPointer<UnitNode> tc) noexcept
//{
//    if(!tc) {
//        return;
//    }
//    tc->setTreeParentUN(QSharedPointer<UnitNode>());

//    for(QSharedPointer<UnitNode> un : as_const(TopologyService::getListTreeUnitNodes())) {
//        QMutableListIterator<QSharedPointer<UnitNode> > i(un->listTreeChilde);
//        while (i.hasNext()) {
//            if (tc.data() == i.next().data())
//                i.remove();
//        }
//    }
//    if(!this->listTreeChilde.contains(tc)) {
//        this->listTreeChilde.append(tc);
//    }
//}

//void UnitNode::moveTreeChildUNUp(QSharedPointer<UnitNode>  childUN)
//{
//    if(!getListTreeChilde().contains(childUN))
//        return;
//    auto index = getListTreeChilde().indexOf(childUN);
//    if(0 < index) {
////        this->listTreeChilde.swap(index - 1, index);
//        qSwap(listTreeChilde[index - 1], listTreeChilde[index]);
//    }
//}

//void UnitNode::moveTreeChildUNDown(QSharedPointer<UnitNode> childUN)
//{
//    if(!getListTreeChilde().contains(childUN))
//        return;
//    auto index = getListTreeChilde().indexOf(childUN);
//    if(getListTreeChilde().count() > (index + 1)) {
////        this->listTreeChilde.swap(index, index + 1);
//        qSwap(listTreeChilde[index], listTreeChilde[index + 1]);
//    }
//}

void UnitNode::addChild(QSharedPointer<UnitNode> tc) noexcept
{
    if(!tc)
    {
        return;
    }
    if(!this->listChilde.contains(tc))
    {
        this->listChilde.append(tc);
        std::sort(listChilde.begin(), listChilde.end());
    }
}

//QSharedPointer<UnitNode>  UnitNode::treeChild(int num) noexcept
//{
//    return listTreeChilde.value(num, 0);
//}

//QList<QSharedPointer<UnitNode> > UnitNode::treeChild() noexcept
//{
//    return listTreeChilde;
//}

QSharedPointer<UnitNode>  UnitNode::child(int num) noexcept
{
    return listChilde.value(num, 0);
}

//int UnitNode::treeChildCount() const noexcept
//{
//    return this->listTreeChilde.size();////!!!!!
//}

int UnitNode::childCount() const noexcept
{
    return this->listChilde.size();////!!!!!
}

//int UnitNode::treeRow() const noexcept
//{
//    if (treeParentUN) {
//        for(int i = 0, n = treeParentUN->listTreeChilde.size(); i < n; i++) {
//            if(treeParentUN->listTreeChilde.at(i).data() == this)
//                return i;
//        }
//    }
//    return 0;
//}

//int UnitNode::columnCount() const noexcept
//{
//    return 2;//itemData.count();
//}



int UnitNode_BL_IP::isExistDK() const
{
    if(getStateWord(0x41u).getByteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(getStateWord(0x41u).getByteWord().at(1)) & 0x80)
        return 1; // Status::Exists);
    else
        return 0; // Status::Not);
}

//int UnitNode_BL_IP::isWasAlarm() const
//{
//    if(getStateWord(0x41u).getByteWord().isEmpty())
//        return -1;
//    if(static_cast<uint8_t>(getStateWord(0x41u).getByteWord().at(1)) & 0x40)
//        return 1; //Status::Was);
//    else
//        return 0; //Status::Not);
//}

int UnitNode_SSOI_BL_IP::isExistDK() const
{
    if(getStateWord(0x41u).getByteWord().isEmpty())
        return -1;
    if(static_cast<uint8_t>(getStateWord(0x41u).getByteWord().at(1)) & 0x80)
        return 1; // Status::Exists);
    else
        return 0; // Status::Not);
}

//int UnitNode_SSOI_BL_IP::isWasAlarm() const
//{
//    if(getStateWord(0x41u).getByteWord().isEmpty())
//        return -1;
//    if(static_cast<uint8_t>(getStateWord(0x41u).getByteWord().at(1)) & 0x40)
//        return 1; //Status::Was);
//    else
//        return 0; //Status::Not);
//}

int UnitNode_SD_BL_IP::calcDKStatus() const {

    if(1 == swpSDBLIPType0x41().isWasAlarm() && 1 == swpSDBLIPType0x41().isAlarm()) {
        return DKCiclStatus::DKWasAlarm;
    } else if(1 == swpSDBLIPType0x41().isNorm() && 1 == swpSDBLIPType0x41().isWasAlarm()) {
        return DKCiclStatus::DKWas;
//            return DKCiclStatus::DKWrong;
//    } else if(1 == swpSDBLIPType0x41().isAlarm()) {
//        return DKCiclStatus::DKWrong;
////            return DKCiclStatus::DKWasAlarn;
    } else if(1 == swpSDBLIPType0x41().isOff()) {
        return DKCiclStatus::DKWrong;
    } else if(1 == swpSDBLIPType0x41().isNorm()) {
        return DKCiclStatus::DKNorm;
    }
    return getDkStatus();
//    return DKCiclStatus::DKWrong;
}

int UnitNode_SSOI_SD_BL_IP::calcDKStatus() const {

    if(1 == swpSSOISDBLIPType0x41().isWasAlarm()
    && 1 == swpSSOISDBLIPType0x41().isAlarm()) {
        return DKCiclStatus::DKWasAlarm;
    } else if(1 != swpSSOISDBLIPType0x41().isInAlarm()
           && 1 == swpSSOISDBLIPType0x41().isWasAlarm()) {
        return DKCiclStatus::DKWas;
    } else if(1 == swpSSOISDBLIPType0x41().isOff()) {
        return DKCiclStatus::DKWrong;
    } else if(1 == swpSSOISDBLIPType0x41().isNorm()) {
        return DKCiclStatus::DKNorm;
    }
    return getDkStatus();
}

int UnitNode_TG::calcDKStatus() const {
//    const auto swp31 = swpTGType0x31();
    const auto swp32 = swpTGType0x32();
    const auto swp33 = swpTGType0x33();

    /*if(!swp31.isNull() && !swp32.isNull() && !swp33.isNull() && (swp31.cdate() >= swp33.cdate()) && (swp31.cdate() >= swp33.cdate())) {
        //
        if(1 == swp31.isWasAlarm() || 1 == swp31.isOutAlarm()) {
            return DKCiclStatus::DKWasAlarn;
        } else if(0 == swp31.isInAlarm() && 0 == swp31.isOutAlarm() && 1 == swp31.isWasAlarm()) {
            return DKCiclStatus::DKNorm;
        }
       //
    } else*/ if(!swp32.isNull() && !swp33.isNull() && (swp32.cdate() >= swp33.cdate())) {
        //
        if(1 == swp32.C(getNum2()).isInAlarm() || 1 == swp32.C(getNum2()).isSideAlarm()) {
            return DKCiclStatus::DKWasAlarm;
        } else if(0 == swp32.C(getNum2()).isInAlarm() && 0 == swp32.C(getNum2()).isOutAlarm()) {
            return DKCiclStatus::DKNorm;
        }
       //
    } else if(!swp33.isNull()) {
        //
        if(1 == swp33.C(getNum2()).isInAlarm() || 1 == swp33.C(getNum2()).isSideAlarm()) {
            return DKCiclStatus::DKWasAlarm;
        } else if(0 == swp33.C(getNum2()).isInAlarm() && 0 == swp33.C(getNum2()).isOutAlarm()) {
            return DKCiclStatus::DKNorm;
        }
       //
    } else if(!swp32.isNull()) {
        //
        if(1 == swp32.C(getNum2()).isInAlarm() || 1 == swp32.C(getNum2()).isSideAlarm()) {
            return DKCiclStatus::DKWasAlarm;
        } else if(0 == swp32.C(getNum2()).isInAlarm() && 0 == swp32.C(getNum2()).isOutAlarm()) {
            return DKCiclStatus::DKNorm;
        }
       //
    } /*else if(!swp31.isNull()) {
        //
        if(1 == swp31.isWasAlarm() || 1 == swp31.isOutAlarm()) {
            return DKCiclStatus::DKWasAlarn;
        } else if(0 == swp31.isInAlarm() && 0 == swp31.isOutAlarm() && 1 == swp31.isWasAlarm()) {
            return DKCiclStatus::DKNorm;
        }
       //
    }*/
    return DKCiclStatus::DKWas;
}

int UnitNode_RLM_KRL::calcDKStatus() const {
    const auto swp = swpRLMType0x31();

    if(!swp.isNull()) {
        if(1 == swp.isAlarm() && 1 == swp.isWasAlarm()) {
            return DKCiclStatus::DKWasAlarm;
        } else if(1 == swp.isOn() && 1 == swp.isNorm()) {
            return DKCiclStatus::DKNorm;
        }
    }
    return DKCiclStatus::DKWas;
}

int UnitNode_RLM_C::calcDKStatus() const {
    const auto swp = swpRLMCType0x31();

    if(!swp.isNull()) {
        if(1 == swp.isAlarm() && 1 == swp.isWasAlarm()) {
            return DKCiclStatus::DKWasAlarm;
        } else if(1 == swp.isOn() && 1 == swp.isNorm()) {
            return DKCiclStatus::DKNorm;
        }
    }
    return DKCiclStatus::DKWas;
}

std::function<void ()> UnitNode::getUpdateStateConditionReactor() const
{
    return updateStateConditionReactor;
}

void UnitNode::setUpdateStateConditionReactor(const std::function<void ()> &value)
{
    updateStateConditionReactor = value;
}

void UnitNode::callUpdateStateConditionReactor()
{
    if(updateStateConditionReactor) {
        const auto tmp = getUpdateStateConditionReactor();

        std::function<void()> empty;
        setUpdateStateConditionReactor(empty);

        tmp();
    }
}

QPixmap UnitNode_SYSTEM::getPxm() const
{
    return Icons::fldr();
}

QPixmap UnitNode_GROUP::getPxm() const
{
    if(childCount())
        return Icons::fldr();
    else
        return Icons::fldr_empt();
    return QPixmap();
}

QPixmap UnitNode_SD_BL_IP::getPxm() const
{
    if(13 == getPublishedState() && !(TypeUnitNodeEnum::SD_BL_IP == getType() && 1 == getBazalt())) {
        if(getControl()) {
            return Icons::sqr_blu();
        } else if(!getControl()) {
            return Icons::sqr_blk_crs_blu();
        }
    } else if(TypeUnitNodeEnum::SD_BL_IP == getType()) {
        const SWPSDBLIPType0x41 swp = swpSDBLIPType0x41();
        if(0 == getBazalt()) {
            if(getControl()
            && swp.isNull()) {
                return Icons::sqr_ylw();
            } else if(!getControl()
                   && swp.isNull()) {
                return Icons::sqr_blk_crs_ylw();
            } else if(1 == swp.isWasAlarm()
                   && getControl()) {
                return Icons::sqr_rd();
            } else if(1 == swp.isWasAlarm()
                   && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isAlarm()
                   && getControl()) {
                return Icons::sqr_rd();
            } else if(1 == swp.isAlarm()
                   && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isOff()
                   && getControl()) {
                return Icons::sqr_blk();
            } else if(1 == swp.isOff()
                   && !getControl()) {
                return Icons::sqr_blk_crs_gry();
            } else if(1 == swp.isNorm()
                   && getControl()) {
                return Icons::sqr_grn();
            } else if(1 == swp.isNorm()
                   && !getControl()) {
                return Icons::sqr_blk_crs_grn();
            } else if(getControl()) {
                return Icons::sqr_ylw();
            } else if(!getControl()) {
                return Icons::sqr_blk_crs_ylw();
            }
        } else { // это узо
            if(getControl()
            && swp.isNull()) {
                return Icons::sqr_ylw();
            } else if(!getControl()
                   && swp.isNull()) {
                return Icons::sqr_blk_crs_ylw();
            } else if(1 == swp.isOff()) {
                return Icons::sqr_blk();
            } else if(13 == getPublishedState()
                   && 1 == swp.isAlarm()) {
                return Icons::sqr_blu_opn();
            } else if(13 == getPublishedState()
                   && 1 == swp.isNorm()) {
                return Icons::sqr_blu_cls();
            } else if(1 == swp.isAlarm()) {
                return Icons::sqr_rd_opn();
            } else if(1 == swp.isNorm()) {
                return Icons::sqr_grn_cls();
            } else {
                return Icons::sqr_ylw();
            }
        }
    }

    return QPixmap();
}

QPixmap UnitNode_IU_BL_IP::getPxm() const
{
    const SWPIUBLIPType0x41 swp = swpIUBLIPType0x41();
    if(swp.isNull()) {
        return Icons::sqr_ylw();
    } else if(1 == swp.isOn()) {
        return Icons::sqr_grn_crs2_rd();
    } else if(1 == swp.isOff()) {
        return Icons::sqr_grn_mns_gry();
    } else
        return Icons::sqr_ylw();
    return QPixmap();
}

QPixmap UnitNode_RLM_C::getPxm() const {
    const SWPRLMCType0x31 swp = swpRLMCType0x31();
    if(getControl()
    && swp.isNull()) {
        return Icons::sqr_ylw();
    } else if(!getControl()
           && swp.isNull()) {
        return Icons::sqr_blk_crs_ylw();
    } else if(1 == swp.isOff()
           && getControl()) {
        return Icons::sqr_blk();
    } else if(1 == swp.isOff()
           && !getControl()) {
        return Icons::sqr_blk_crs_gry();
    } else if(1 == swp.isFault()
           && getControl()) {
        return Icons::sqr_blu();
    } else if(1 == swp.isFault()
           && !getControl()) {
        return Icons::sqr_blk_crs_blu();
    } else if(((1 == swp.isAlarm()
             || 1 == swp.isWasAlarm())
            && !(getIsAutoDkInvolved()
              && getDkInvolved()))
           && 1 == swp.isOn()
           && getControl()) {
        return Icons::sqr_rd();
    } else if(((1 == swp.isAlarm()
             || 1 == swp.isWasAlarm())
            && !(getIsAutoDkInvolved()
              && getDkInvolved()))
           && 1 == swp.isOn()
           && !getControl()) {
        return Icons::sqr_blk_crs_rd();
    } else if(1 == swp.isNorm()
           && getControl()) {
        return Icons::sqr_grn();
    } else if(1 == swp.isNorm()
           && !getControl()) {
        return Icons::sqr_blk_crs_grn();
    } else if(getControl()) {
        return Icons::sqr_grn();
    } else if(!getControl()) {
        return Icons::sqr_blk_crs_grn();
    }
    return QPixmap();
}

QPixmap UnitNode_RLM_KRL::getPxm() const {
    const SWPRLMType0x31 swp = swpRLMType0x31();
    if(getControl()
    && swp.isNull()) {
        return Icons::sqr_ylw();
    } else if(!getControl()
           && swp.isNull()) {
        return Icons::sqr_blk_crs_ylw();
    } else if(1 == swp.isOff()
           && getControl()) {
        return Icons::sqr_blk();
    } else if(1 == swp.isOff()
           && !getControl()) {
        return Icons::sqr_blk_crs_gry();
    } else if(1 == swp.isFault()
           && getControl()) {
        return Icons::sqr_blu();
    } else if(1 == swp.isFault()
           && !getControl()) {
        return Icons::sqr_blk_crs_blu();
    } else if(((1 == swp.isAlarm()
             || 1 == swp.isWasAlarm())
            && !(getIsAutoDkInvolved()
              && getDkInvolved()))
           && 1 == swp.isOn()
           && getControl()) {
        return Icons::sqr_rd();
    } else if(((1 == swp.isAlarm()
             || 1 == swp.isWasAlarm())
            && !(getIsAutoDkInvolved()
              && getDkInvolved()))
           && 1 == swp.isOn()
           && !getControl()) {
        return Icons::sqr_blk_crs_rd();
    } else if(1 == swp.isNorm()
           && getControl()) {
        return Icons::sqr_grn();
    } else if(1 == swp.isNorm()
           && !getControl()) {
        return Icons::sqr_blk_crs_grn();
    } else if(getControl()) {
        return Icons::sqr_grn();
    } else if(!getControl()) {
        return Icons::sqr_blk_crs_grn();
    }
    return QPixmap();
}

QPixmap UnitNode_TG::getPxm() const {
    const SWPTGType0x31 swp31 = swpTGType0x31();
    const SWPTGType0x32 swp32 = swpTGType0x32();
    const SWPTGType0x33 swp33 = swpTGType0x33();
    if(getControl() && swp31.isNull() && swp32.isNull() && swp33.isNull()) {
        return Icons::sqr_ylw();
    } else if(!getControl() && swp31.isNull() && swp32.isNull() && swp33.isNull()) {
        return Icons::sqr_blk_crs_ylw();
    } else if(!swp31.isNull() && (swp32.cdate() < swp31.cdate() && swp33.cdate() < swp31.cdate())) {
        if(1 == swp31.isOff() && getControl()) {
            return Icons::sqr_blk();
        } else if(1 == swp31.isOff() && !getControl()) {
            return Icons::sqr_blk_crs_gry();
        } else if((((1 == swp31.isAlarm()
                  || 1 == swp31.isInAlarm()
                  || 1 == swp31.isOutAlarm())
                 && !(getIsAutoDkInvolved()
                   && getDkInvolved()))
                 || 1 == swp31.isOpened()
                 || 1 == swp31.isWasOpened()
                 || 1 == swp31.isInOpened())
                && getControl()) {
            return Icons::sqr_rd();
        } else if((((1 == swp31.isAlarm()
                  || 1 == swp31.isInAlarm()
                  || 1 == swp31.isOutAlarm())
                 && !(getIsAutoDkInvolved()
                   && getDkInvolved()))
                 || 1 == swp31.isOpened()
                 || 1 == swp31.isWasOpened()
                 || 1 == swp31.isInOpened())
                && !getControl()) {
            return Icons::sqr_blk_crs_rd();
        } else if(1 == swp31.isNorm() && getControl()) {
            return Icons::sqr_grn();
        } else if(1 == swp31.isNorm() && !getControl()) {
            return Icons::sqr_blk_crs_grn();
        } else if(getControl()) {
            return Icons::sqr_grn();
        } else if(!getControl()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(!swp32.isNull() && (swp31.cdate() < swp32.cdate() && swp33.cdate() < swp32.cdate())) {
        if(1 == swp32.C(getNum2()).isFault() && getControl()) {
            return Icons::sqr_blu();
        } else if(1 == swp32.C(getNum2()).isFault() && !getControl()) {
            return Icons::sqr_blk_crs_blu();
        } else if((((1 == swp32.C(getNum2()).isAlarm()
                  || 1 == swp32.C(getNum2()).isOutAlarm()
                  || 1 == swp32.C(getNum2()).isInAlarm())
                 && !(getIsAutoDkInvolved()
                   && getDkInvolved()))
                 || 1 == swp32.C(getNum2()).isOpened()
                 || 1 == swp32.C(getNum2()).isWasOpened()
                 || 1 == swp32.C(getNum2()).isInOpened())
                && getControl()) {
            return Icons::sqr_rd();
        } else if((((1 == swp32.C(getNum2()).isAlarm()
                  || 1 == swp32.C(getNum2()).isOutAlarm()
                  || 1 == swp32.C(getNum2()).isInAlarm())
                 && !(getIsAutoDkInvolved()
                   && getDkInvolved()))
                 || 1 == swp32.C(getNum2()).isOpened()
                 || 1 == swp32.C(getNum2()).isWasOpened()
                 || 1 == swp32.C(getNum2()).isInOpened())
                && !getControl()) {
            return Icons::sqr_blk_crs_rd();
        } else if(1 == swp32.C(getNum2()).isNorm() && getControl()) {
            return Icons::sqr_grn();
        } else if(1 == swp32.C(getNum2()).isNorm() && !getControl()) {
            return Icons::sqr_blk_crs_grn();
        } else if(getControl()) {
            return Icons::sqr_grn();
        } else if(!getControl()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(!swp33.isNull() && (swp31.cdate() < swp33.cdate() && swp32.cdate() < swp33.cdate())) {
        if(1 == swp33.C(getNum2()).isFault() && getControl()) {
            return Icons::sqr_blu();
        } else if(1 == swp33.C(getNum2()).isFault() && !getControl()) {
            return Icons::sqr_blk_crs_blu();
        } else if((((1 == swp33.C(getNum2()).isAlarm()
                  || 1 == swp33.C(getNum2()).isInAlarm()
                  || 1 == swp33.C(getNum2()).isOutAlarm())
                 && !(getIsAutoDkInvolved()
                   && getDkInvolved()))
                 || 1 == swp33.C(getNum2()).isOpened()
                 || 1 == swp33.C(getNum2()).isWasOpened()
                 || 1 == swp33.C(getNum2()).isInOpened())
                && getControl()) {
            return Icons::sqr_rd();
        } else if((((1 == swp33.C(getNum2()).isAlarm()
                  || 1 == swp33.C(getNum2()).isInAlarm()
                  || 1 == swp33.C(getNum2()).isOutAlarm())
                 && !(getIsAutoDkInvolved()
                   && getDkInvolved()))
                 || 1 == swp33.C(getNum2()).isOpened()
                 || 1 == swp33.C(getNum2()).isWasOpened()
                 || 1 == swp33.C(getNum2()).isInOpened())
                && !getControl()) {
            return Icons::sqr_blk_crs_rd();
        } else if(1 == swp33.C(getNum2()).isNorm() && getControl()) {
            return Icons::sqr_grn();
        } else if(1 == swp33.C(getNum2()).isNorm() && !getControl()) {
            return Icons::sqr_blk_crs_grn();
        } else if(getControl()) {
            return Icons::sqr_grn();
        } else if(!getControl()) {
            return Icons::sqr_blk_crs_grn();
        }
    } /*else if(!swp34.isNull()) {

    } */else if(getControl()) {
        return Icons::sqr_ylw();
    } else if(!getControl()) {
        return Icons::sqr_blk_crs_ylw();
    }
    return QPixmap();
}

QPixmap UnitNode_SSOI_SD_BL_IP::getPxm() const
{
    if(13 == getPublishedState() && !(TypeUnitNodeEnum::SSOI_SD_BL_IP == getType() && 1 == getBazalt())) {
        if(getControl()) {
            return Icons::sqr_blu();
        } else if(!getControl()) {
            return Icons::sqr_blk_crs_blu();
        }
    } else if(TypeUnitNodeEnum::SSOI_SD_BL_IP == getType()) {
        const SWPSSOISDBLIPType0x41 swp = swpSSOISDBLIPType0x41();
        if(0 == getBazalt()) {
            if(getControl()
            && swp.isNull()) {
                return Icons::sqr_ylw();
            } else if(!getControl()
                   && swp.isNull()) {
                return Icons::sqr_blk_crs_ylw();
            } else if(9 == getNum2()
                   && 1 == swp.isWasOpened()
                   && getControl()) {
                return Icons::sqr_rd();
            } else if(9 == getNum2()
                   && 1 == swp.isWasOpened()
                   && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(9 == getNum2()
                   && 1 == swp.isInOpened()
                   && getControl()) {
                return Icons::sqr_rd();
            } else if(9 == getNum2()
                   && 1 == swp.isInOpened()
                   && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isWasAlarm()
                   && getControl()) {
                return Icons::sqr_rd();
            } else if(1 == swp.isWasAlarm()
                   && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isInAlarm()
                   && getControl()) {
                return Icons::sqr_rd();
            } else if(1 == swp.isInAlarm()
                   && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isOff()
                   && getControl()) {
                return Icons::sqr_blk();
            } else if(1 == swp.isOff()
                   && !getControl()) {
                return Icons::sqr_blk_crs_gry();
            } else if(1 == swp.isNorm()
                   && getControl()) {
                return Icons::sqr_grn();
            } else if(1 == swp.isNorm()
                   && !getControl()) {
                return Icons::sqr_blk_crs_grn();
            } else if(getControl()) {
                return Icons::sqr_ylw();
            } else if(!getControl()) {
                return Icons::sqr_blk_crs_ylw();
            }
        } else { // это узо
            if(getControl()
            && swp.isNull()) {
                return Icons::sqr_ylw();
            } else if(!getControl()
                   && swp.isNull()) {
                return Icons::sqr_blk_crs_ylw();
            } else if(1 == swp.isOff()) {
                return Icons::sqr_blk();
            } else if(13 == getPublishedState()
                   && 1 == swp.isInAlarm()) {
                return Icons::sqr_blu_opn();
            } else if(13 == getPublishedState()
                   && 1 == swp.isInNorm()) {
                return Icons::sqr_blu_cls();
            } else if(1 == swp.isInAlarm()) {
                return Icons::sqr_rd_opn();
            } else if(1 == swp.isInNorm()) {
                return Icons::sqr_grn_cls();
            } else {
                return Icons::sqr_ylw();
            }
        }
    }

    return QPixmap();
}

QPixmap UnitNode_SSOI_IU_BL_IP::getPxm() const
{
    const SWPSSOIIUBLIPType0x41 swp = swpSSOIIUBLIPType0x41();
    if(swp.isNull()) {
        return Icons::sqr_ylw();
    } else if(1 == swp.isOn()) {
        return Icons::sqr_grn_crs2_rd();
    } else if(1 == swp.isOff()) {
        return Icons::sqr_grn_mns_gry();
    } else
        return Icons::sqr_ylw();
    return QPixmap();
}

QPixmap UnitNode_BOD_T4K_M::getPxm() const
{
    const auto& swp32 = swpT4KBODType0x32();
    const auto& swp33 = swpT4KBODType0x33();
    if(getControl() && swp32.isNull() && swp33.isNull()) {
        return Icons::sqr_ylw();
    } else if(!getControl()
           && swp32.isNull()
           && swp33.isNull()) {
        return Icons::sqr_blk_crs_ylw();
    } else if(!swp32.isNull()
           && swp33.cdate() < swp32.cdate()) {
        if(0 == swp32.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && !isClearedAlarm()){
            return Icons::sqr_rd();
        } else if(!getControl()
               && !isClearedAlarm()){
            return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
            return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(!swp33.isNull() && swp32.cdate() < swp33.cdate()) {
        if(0 == swp33.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && !isClearedAlarm()){
            return Icons::sqr_rd();
        } else if(!getControl()
               && !isClearedAlarm()){
            return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
            return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(getControl()) {
        return Icons::sqr_ylw();
    } else if(!getControl()) {
        return Icons::sqr_blk_crs_ylw();
    }
    return Icons::sqr_gry_qstn();
}

QPixmap UnitNode_BOD_SOTA::getPxm() const
{
    const auto& swp32 = swpSOTABODType0x32();
    const auto& swp33 = swpSOTABODType0x33();
    if(getControl() && swp32.isNull() && swp33.isNull()) {
        return Icons::sqr_ylw();
    } else if(!getControl()
           && swp32.isNull()
           && swp33.isNull()) {
        return Icons::sqr_blk_crs_ylw();
    } else if(!swp32.isNull()
           && swp33.cdate() < swp32.cdate()) {
        if(0 == swp32.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && !isClearedAlarm()){
            return Icons::sqr_rd();
        } else if(!getControl()
               && !isClearedAlarm()){
            return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
            return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(!swp33.isNull() && swp32.cdate() < swp33.cdate()) {
        if(0 == swp33.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && !isClearedAlarm()){
            return Icons::sqr_rd();
        } else if(!getControl()
               && !isClearedAlarm()){
            return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
            return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(getControl()) {
        return Icons::sqr_ylw();
    } else if(!getControl()) {
        return Icons::sqr_blk_crs_ylw();
    }
    return Icons::sqr_gry_qstn();
}


int UnitNode_BOD_T4K_M::calcDKStatus() const
{
//    qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus() -->";
    int result = getDkStatus();
    const auto& swp32 = swpT4KBODType0x32();
    const auto& swp33 = swpT4KBODType0x33();

    for(const auto &y4 : {1,2,3,4}) {
        if(swp32.isNull()
        && swp32.isNull()) {
            result = DKCiclStatus::DKWrong;
            break;
        } else if(!swp32.isNull()
               && (swp32.cdate() > swp33.cdate() || swp33.isNull())
               && 1 == swp32.isReady()
               && 1 == swp32.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKWasAlarm";
            result = DKCiclStatus::DKWasAlarm;
        } else if(!swp33.isNull()
               && (swp33.cdate() > swp32.cdate() || swp32.isNull())
               && 1 == swp33.isReady()
               && 1 == swp33.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKWasAlarm";
            result = DKCiclStatus::DKWasAlarm;
        } else if(!swp32.isNull()
               && (swp32.cdate() > swp33.cdate() || swp33.isNull())
               && 1 == swp32.isReady()
               && 0 == swp32.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKNorm";
            result = DKCiclStatus::DKNorm;
            break;
        } else if(!swp33.isNull()
               && (swp33.cdate() > swp32.cdate() || swp32.isNull())
               && 1 == swp33.isReady()
               && 0 == swp33.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKNorm";
            result = DKCiclStatus::DKNorm;
            break;
        } else {
//            qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus(" << getDkStatus() << ") <-- getDkStatus";
            return getDkStatus();
        }
    }
    if(DKCiclStatus::DKWasAlarm == result) {
//        qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus(" << result << ") <-- result";
        return result;
    }

    for(const auto &y4 : {1,2,3,4}) {
        if(swp32.isNull()
        && swp32.isNull()) {
            result = DKCiclStatus::DKWrong;
            break;
        } else if(!swp32.isNull()
               && (swp32.cdate() > swp33.cdate() || swp33.isNull())
               && 1 == swp32.isReady()
               && 1 == swp32.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKWasAlarm";
            result = DKCiclStatus::DKWasAlarm;
            break;
        } else if(!swp33.isNull()
               && (swp33.cdate() > swp32.cdate() || swp32.isNull())
               && 1 == swp33.isReady()
               && 1 == swp33.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKWasAlarm";
            result = DKCiclStatus::DKWasAlarm;
            break;
        } else if(!swp32.isNull()
               && (swp32.cdate() > swp33.cdate() || swp33.isNull())
               && 1 == swp32.isReady()
               && 0 == swp32.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKNorm";
            result = DKCiclStatus::DKNorm;
        } else if(!swp33.isNull()
               && (swp33.cdate() > swp32.cdate() || swp32.isNull())
               && 1 == swp33.isReady()
               && 0 == swp33.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKNorm";
            result = DKCiclStatus::DKNorm;
        } else {
//            qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus(" << getDkStatus() << ") <-- getDkStatus";
            return getDkStatus();
        }
    }
    if(DKCiclStatus::DKNorm == result) {
//        qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus(" << result << ") <-- result";
        return result;
    }

//    qDebug() << "UnitNode_BOD_T4K_M::calcDKStatus(" << getDkStatus() << ") <-- getDkStatus";
    return getDkStatus();
}

int UnitNode_BOD_SOTA::calcDKStatus() const
{
//    qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus() -->";
    int result = getDkStatus();
    const auto& swp32 = swpSOTABODType0x32();
    const auto& swp33 = swpSOTABODType0x33();

    for(const auto &y4 : {1,2,3,4}) {
        if(swp32.isNull()
        && swp32.isNull()) {
            result = DKCiclStatus::DKWrong;
            break;
        } else if(!swp32.isNull()
               && (swp32.cdate() > swp33.cdate() || swp33.isNull())
               && 1 == swp32.isReady()
               && 1 == swp32.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKWasAlarm";
            result = DKCiclStatus::DKWasAlarm;
        } else if(!swp33.isNull()
               && (swp33.cdate() > swp32.cdate() || swp32.isNull())
               && 1 == swp33.isReady()
               && 1 == swp33.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKWasAlarm";
            result = DKCiclStatus::DKWasAlarm;
        } else if(!swp32.isNull()
               && (swp32.cdate() > swp33.cdate() || swp33.isNull())
               && 1 == swp32.isReady()
               && 0 == swp32.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKNorm";
            result = DKCiclStatus::DKNorm;
            break;
        } else if(!swp33.isNull()
               && (swp33.cdate() > swp32.cdate() || swp32.isNull())
               && 1 == swp33.isReady()
               && 0 == swp33.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKNorm";
            result = DKCiclStatus::DKNorm;
            break;
        } else {
//            qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus(" << getDkStatus() << ") <-- getDkStatus";
            return getDkStatus();
        }
    }
    if(DKCiclStatus::DKWasAlarm == result) {
//        qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus(" << result << ") <-- result";
        return result;
    }

    for(const auto &y4 : {1,2,3,4}) {
        if(swp32.isNull()
        && swp32.isNull()) {
            result = DKCiclStatus::DKWrong;
            break;
        } else if(!swp32.isNull()
               && (swp32.cdate() > swp33.cdate() || swp33.isNull())
               && 1 == swp32.isReady()
               && 1 == swp32.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKWasAlarm";
            result = DKCiclStatus::DKWasAlarm;
            break;
        } else if(!swp33.isNull()
               && (swp33.cdate() > swp32.cdate() || swp32.isNull())
               && 1 == swp33.isReady()
               && 1 == swp33.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKWasAlarm";
            result = DKCiclStatus::DKWasAlarm;
            break;
        } else if(!swp32.isNull()
               && (swp32.cdate() > swp33.cdate() || swp33.isNull())
               && 1 == swp32.isReady()
               && 0 == swp32.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKNorm";
            result = DKCiclStatus::DKNorm;
        } else if(!swp33.isNull()
               && (swp33.cdate() > swp32.cdate() || swp32.isNull())
               && 1 == swp33.isReady()
               && 0 == swp33.y(y4).isWasAlarm()) {
//            qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus() -- y4(" << y4 << ") DKCiclStatus::DKNorm";
            result = DKCiclStatus::DKNorm;
        } else {
//            qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus(" << getDkStatus() << ") <-- getDkStatus";
            return getDkStatus();
        }
    }
    if(DKCiclStatus::DKNorm == result) {
//        qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus(" << result << ") <-- result";
        return result;
    }

//    qDebug() << "UnitNode_BOD_SOTA_M::calcDKStatus(" << getDkStatus() << ") <-- getDkStatus";
    return getDkStatus();
}

QPixmap UnitNode_Y4_T4K_M::getPxm() const
{
    const auto& swp32 = swpT4KBODType0x32();
    const auto& swp33 = swpT4KBODType0x33();
    if(getControl() && swp32.isNull() && swp33.isNull()) {
        return Icons::sqr_ylw();
    } else if(!getControl()
           && swp32.isNull()
           && swp33.isNull()) {
        return Icons::sqr_blk_crs_ylw();
    } else if(!swp32.isNull()
           && swp33.cdate() < swp32.cdate()) {
        if(0 == swp32.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && !isClearedAlarm()){
            return Icons::sqr_rd();
        } else if(!getControl()
               && !isClearedAlarm()){
            return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
            return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(!swp33.isNull() && swp32.cdate() < swp33.cdate()) {
        if(0 == swp33.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && !isClearedAlarm()){
            return Icons::sqr_rd();
        } else if(!getControl()
               && !isClearedAlarm()){
            return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
            return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(getControl()) {
        return Icons::sqr_ylw();
    } else if(!getControl()) {
        return Icons::sqr_blk_crs_ylw();
    }
    return Icons::sqr_gry_qstn();
}

QPixmap UnitNode_DD_T4K_M::getPxm() const
{
    auto y4 = getNum2() / 100;
    auto ddNum = getNum2() % 100;
    const auto& swp32 = swpT4KBODType0x32();
    const auto& swp33 = swpT4KBODType0x33();
    if(getControl() && swp32.isNull() && swp33.isNull()) {
        return Icons::sqr_ylw();
    } else if(!getControl()
           && swp32.isNull()
           && swp33.isNull()) {
        return Icons::sqr_blk_crs_ylw();
    } else if(!swp32.isNull()
           && swp33.cdate() < swp32.cdate()) {
        if(0 == swp32.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && (1 == swp32.y(y4).dd(ddNum).c(1).isFault()
                || 1 == swp32.y(y4).dd(ddNum).c(2).isFault())){
            return Icons::sqr_blu();
        } else if(!getControl()
               && (1 == swp32.y(y4).dd(ddNum).c(1).isFault()
                || 1 == swp32.y(y4).dd(ddNum).c(2).isFault())){
            return Icons::sqr_blk_crs_blu();
        } else if(getControl()
            && (swp32.y(y4).dd(ddNum).isWasOpened()
             || swp32.y(y4).dd(ddNum).c(1).isWasAlarm()
             || swp32.y(y4).dd(ddNum).c(2).isWasAlarm())) {
            return Icons::sqr_rd();
        } else if(!getControl()
               && (swp32.y(y4).dd(ddNum).isWasOpened()
                || swp32.y(y4).dd(ddNum).c(1).isWasAlarm()
                || swp32.y(y4).dd(ddNum).c(2).isWasAlarm())){
            return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
            return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(!swp33.isNull() && swp32.cdate() < swp33.cdate()) {
        if(0 == swp33.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && (swp33.dd().isFault()
                || swp33.dd().c(1).isCliff()
                || swp33.dd().c(1).isClosure()
                || swp33.dd().c(2).isCliff()
                || swp33.dd().c(2).isClosure())){
            return Icons::sqr_blu();
        } else if(!getControl()
               && (swp33.dd().isFault()
                || swp33.dd().c(1).isCliff()
                || swp33.dd().c(1).isClosure()
                || swp33.dd().c(2).isCliff()
                || swp33.dd().c(2).isClosure())){
               return Icons::sqr_blk_crs_blu();
        } else if(getControl()
               && (swp33.dd().isWasOpened()
                || swp33.dd().c(1).isWasAlarm()
                || swp33.dd().c(2).isWasAlarm()
                || swp33.dd().c(1).f(1).isWasAlarm()
                || swp33.dd().c(1).f(2).isWasAlarm()
                || swp33.dd().c(2).f(1).isWasAlarm()
                || swp33.dd().c(2).f(2).isWasAlarm())){
               return Icons::sqr_rd();
        } else if(!getControl()
               && (swp33.dd().isWasOpened()
                || swp33.dd().c(1).isWasAlarm()
                || swp33.dd().c(2).isWasAlarm()
                || swp33.dd().c(1).f(1).isWasAlarm()
                || swp33.dd().c(1).f(2).isWasAlarm()
                || swp33.dd().c(2).f(1).isWasAlarm()
                || swp33.dd().c(2).f(2).isWasAlarm())){
               return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
               return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
               return Icons::sqr_blk_crs_grn();
        }
    } else if(getControl()) {
        return Icons::sqr_ylw();
    } else if(!getControl()) {
        return Icons::sqr_blk_crs_ylw();
    }
    return Icons::sqr_gry_qstn();

}

QPixmap UnitNode_Y4_SOTA::getPxm() const
{
    const auto& swp32 = swpSOTABODType0x32();
    const auto& swp33 = swpSOTABODType0x33();
    if(getControl() && swp32.isNull() && swp33.isNull()) {
        return Icons::sqr_ylw();
    } else if(!getControl()
           && swp32.isNull()
           && swp33.isNull()) {
        return Icons::sqr_blk_crs_ylw();
    } else if(!swp32.isNull()
           && swp33.cdate() < swp32.cdate()) {
        if(0 == swp32.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && !isClearedAlarm()){
            return Icons::sqr_rd();
        } else if(!getControl()
               && !isClearedAlarm()){
            return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
            return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(!swp33.isNull() && swp32.cdate() < swp33.cdate()) {
        if(0 == swp33.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && !isClearedAlarm()){
            return Icons::sqr_rd();
        } else if(!getControl()
               && !isClearedAlarm()){
            return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
            return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(getControl()) {
        return Icons::sqr_ylw();
    } else if(!getControl()) {
        return Icons::sqr_blk_crs_ylw();
    }
    return Icons::sqr_gry_qstn();
}

QPixmap UnitNode_DD_SOTA::getPxm() const
{
    auto y4 = getNum2() / 100;
    auto ddNum = getNum2() % 100;
    const auto& swp32 = swpSOTABODType0x32();
    const auto& swp33 = swpSOTABODType0x33();
    if(getControl() && swp32.isNull() && swp33.isNull()) {
        return Icons::sqr_ylw();
    } else if(!getControl()
           && swp32.isNull()
           && swp33.isNull()) {
        return Icons::sqr_blk_crs_ylw();
    } else if(!swp32.isNull()
           && swp33.cdate() < swp32.cdate()) {
        if(0 == swp32.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && 1 == swp32.y(y4).dd(ddNum).isFault()){
            return Icons::sqr_blu();
        } else if(!getControl()
               && 1 == swp32.y(y4).dd(ddNum).isFault()){
            return Icons::sqr_blk_crs_blu();
        } else if(getControl()
            && swp32.y(y4).dd(ddNum).isWasAlarm()) {
            return Icons::sqr_rd();
        } else if(!getControl()
               && swp32.y(y4).dd(ddNum).isWasAlarm()){
            return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
            return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
            return Icons::sqr_blk_crs_grn();
        }
    } else if(!swp33.isNull() && swp32.cdate() < swp33.cdate()) {
        if(0 == swp33.isReady()) {
            return Icons::sqr_gry_qstn();
        } else if(getControl()
               && swp33.dd().isFault()){
            return Icons::sqr_blu();
        } else if(!getControl()
               && swp33.dd().isFault()){
               return Icons::sqr_blk_crs_blu();
        } else if(getControl()
               && (swp33.dd().isWasOpened()
                || swp33.dd().isWasAlarm()
                || swp33.dd().isWasAlarm()
                || swp33.dd().f(1).isWasAlarm()
                || swp33.dd().f(2).isWasAlarm())){
               return Icons::sqr_rd();
        } else if(!getControl()
               && (swp33.dd().isWasOpened()
                || swp33.dd().isWasAlarm()
                || swp33.dd().isWasAlarm()
                || swp33.dd().f(1).isWasAlarm()
                || swp33.dd().f(2).isWasAlarm())){
               return Icons::sqr_blk_crs_rd();
        } else if(getControl()
               && isClearedAlarm()) {
               return Icons::sqr_grn();
        } else if(!getControl()
               && isClearedAlarm()) {
               return Icons::sqr_blk_crs_grn();
        }
    } else if(getControl()) {
        return Icons::sqr_ylw();
    } else if(!getControl()) {
        return Icons::sqr_blk_crs_ylw();
    }
    return Icons::sqr_gry_qstn();

}
