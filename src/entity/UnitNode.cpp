#include <QDebug>

#include <UnitNode.h>
#include <ServerSettingUtils.h>
#include <Icons.h>
#include <Icons_cfg.h>
#include <SignalSlotCommutator.h>
#include <global.h>
#include <SWPBLIP.h>
#include <SWPRLM.h>
#include <SWPRLMC.h>
#include <SWPSDBLIP.h>
#include <SWPIUBLIP.h>
#include <SWPTGType0x31.h>
#include <SWPTGType0x34.h>
#include <SWPTGType0x33.h>
#include <SWPTGType0x32.h>
#include <DataQueueItem.h>

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
    UnitNodeCFG::setUdpTimeout(value);

    int udpTimeout = 50;

    udpTimeout = qMax(udpTimeout, getUdpTimeout());

    int maxBeatCount = 400;
    if(50 != udpTimeout) {
        maxBeatCount = (delayDisconnectStatus / udpTimeout) + 1;
    }
    setMaxCountSCRWA(maxBeatCount);
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

QPixmap UnitNode::getPxm(SubTypeApp type)
{
    if(SubTypeApp::server == type) {
        if(TypeUnitNode::SYSTEM == getType()) {
            return Icons::fldr();
        } else if(TypeUnitNode::GROUP == getType()) {
            if(childCount())
                return Icons::fldr();
            else
                return Icons::fldr_empt();
        } else if(TypeUnitNode::SD_BL_IP == getType()) {
            const SWPSDBLIP swp = swpSDBLIP();
            if(0 == getBazalt()) {
                if(getControl() && swp.isNull()) {
                    return Icons::sqr_ylw();
                } else if(!getControl() && swp.isNull()) {
                    return Icons::sqr_blk_crs_ylw();
                } else if(1 == swp.isWasAlarm() && getControl()) {
                    return Icons::sqr_rd();
                } else if(1 == swp.isWasAlarm() && !getControl()) {
                    return Icons::sqr_blk_crs_rd();
                } else if(1 == swp.isAlarm() && getControl()) {
                    return Icons::sqr_rd();
                } else if(1 == swp.isAlarm() && !getControl()) {
                    return Icons::sqr_blk_crs_rd();
                } else if(1 == swp.isOff() && getControl()) {
                    return Icons::sqr_blk();
                } else if(1 == swp.isOff() && !getControl()) {
                    return Icons::sqr_blk_crs_gry();
                } else if(1 == swp.isNorm() && getControl()) {
                    return Icons::sqr_grn();
                } else if(1 == swp.isNorm() && !getControl()) {
                    return Icons::sqr_blk_crs_grn();
                } else if(getControl()) {
                    return Icons::sqr_ylw();
                } else if(!getControl()) {
                    return Icons::sqr_blk_crs_ylw();
                }
            } else {
                if(getControl() && swp.isNull()) {
                    return Icons::sqr_ylw();
                } else if(!getControl() && swp.isNull()) {
                    return Icons::sqr_blk_crs_ylw();
                } else if(1 == swp.isAlarm()) {
                    return Icons::sqr_rd_opn();
                } else if(1 == swp.isNorm()) {
                    return Icons::sqr_grn_cls();
                } else {
                    return Icons::sqr_ylw();
                }
            }

        } else if(TypeUnitNode::IU_BL_IP == getType()) {
            const SWPIUBLIP swp = swpIUBLIP();
            if(getControl() && swp.isNull()) {
                return Icons::sqr_ylw();
            } else if(!getControl() && swp.isNull()) {
                return Icons::sqr_blk_crs_ylw();
            } else if(1 == swp.isOn()) {
                return Icons::sqr_grn_crs2_rd();
            } else if(1 == swp.isOff()) {
                return Icons::sqr_grn_mns_gry();
            } else
                return Icons::sqr_ylw();
        } else if(TypeUnitNode::RLM_C == getType()) {
            const SWPRLMC swp = swpRLMC();
            if(getControl() && swp.isNull()) {
                return Icons::sqr_ylw();
            } else if(!getControl() && swp.isNull()) {
                return Icons::sqr_blk_crs_ylw();
            } else if(1 == swp.lowLevl() && getControl()) {
                return Icons::sqr_blu();
            } else if(1 == swp.lowLevl() && !getControl()) {
                return Icons::sqr_blk_crs_blu();
            } else if(1 == swp.isWasAlarm() && getControl()) {
                return Icons::sqr_rd();
            } else if(1 == swp.isWasAlarm() && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isAlarm() && getControl()) {
                return Icons::sqr_rd();
            } else if(1 == swp.isAlarm() && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isOff() && getControl()) {
                return Icons::sqr_blk();
            } else if(1 == swp.isOff() && !getControl()) {
                return Icons::sqr_blk_crs_gry();
            } else if(1 == swp.isNorm() && getControl()) {
                return Icons::sqr_grn();
            } else if(1 == swp.isNorm() && !getControl()) {
                return Icons::sqr_blk_crs_grn();
            } else if(getControl()) {
                return Icons::sqr_ylw();
            } else if(!getControl()) {
                return Icons::sqr_blk_crs_ylw();
            }
        } else if(TypeUnitNode::RLM_KRL == getType()) {
            const SWPRLM swp = swpRLM();
            if(getControl() && swp.isNull()) {
                return Icons::sqr_ylw();
            } else if(!getControl() && swp.isNull()) {
                return Icons::sqr_blk_crs_ylw();
            } else if(0 == swp.isOutAlarm() &&
                      1 == swp.isInAlarm() &&
                      1 == swp.isWasAlarm() &&
                      0 == swp.isWasDK() &&
                      0 == swp.isWasOpened() && getControl()) {
                return Icons::sqr_blu();
            } else if(0 == swp.isOutAlarm() &&
                      1 == swp.isInAlarm() &&
                      1 == swp.isWasAlarm() &&
                      0 == swp.isWasDK() &&
                      0 == swp.isWasOpened() && !getControl()) {
                return Icons::sqr_blk_crs_blu();
            } else if(1 == swp.isWasAlarm() && getControl()) {
                return Icons::sqr_rd();
            } else if(1 == swp.isWasAlarm() && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isAlarm() && getControl()) {
                return Icons::sqr_rd();
            } else if(1 == swp.isAlarm() && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isOff() && getControl()) {
                return Icons::sqr_blk();
            } else if(1 == swp.isOff() && !getControl()) {
                return Icons::sqr_blk_crs_gry();
            } else if(1 == swp.isNorm() && getControl()) {
                return Icons::sqr_grn();
            } else if(1 == swp.isNorm() && !getControl()) {
                return Icons::sqr_blk_crs_grn();
            } else if(getControl()) {
                return Icons::sqr_ylw();
            } else if(!getControl()) {
                return Icons::sqr_blk_crs_ylw();
            }
        } else if(TypeUnitNode::TG == getType() || TypeUnitNode::TG_Base == getType()) {
            const SWPTGType0x31 swp = swpTGType0x31();
            if(getControl() && swp.isNull()) {
                return Icons::sqr_ylw();
            } else if(!getControl() && swp.isNull()) {
                return Icons::sqr_blk_crs_ylw();
            } else if(1 == swp.isWasAlarm() && getControl()) {
                return Icons::sqr_rd();
            } else if(1 == swp.isWasAlarm() && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isAlarm() && getControl()) {
                return Icons::sqr_rd();
            } else if(1 == swp.isAlarm() && !getControl()) {
                return Icons::sqr_blk_crs_rd();
            } else if(1 == swp.isOff() && getControl()) {
                return Icons::sqr_blk();
            } else if(1 == swp.isOff() && !getControl()) {
                return Icons::sqr_blk_crs_gry();
            } else if(1 == swp.isNorm() && getControl()) {
                return Icons::sqr_grn();
            } else if(1 == swp.isNorm() && !getControl()) {
                return Icons::sqr_blk_crs_grn();
            } else if(getControl()) {
                return Icons::sqr_ylw();
            } else if(!getControl()) {
                return Icons::sqr_blk_crs_ylw();
            }
        }
    } else if(SubTypeApp::configurator == type) {


         if(TypeUnitNode::GROUP == getType()||TypeUnitNode::SYSTEM == getType())
         {
         if(childCount())
         return Icons::fldr();
         else
         return Icons::fldr_empt();
         }
         else
             if(TypeUnitNode::SD_BL_IP    == getType())
             {
                 if(this->getBazalt()==1)
                     return Icons_cfg::sd_basalt();
                 return Icons_cfg::sd();
             }
         else if(TypeUnitNode::IU_BL_IP    == getType()) {return Icons_cfg::iu();        }
         else if(TypeUnitNode::BOD_T4K_M   == getType()) {return Icons_cfg::BOD_T4K_M(); }
         else if(TypeUnitNode::BOD_SOTA    == getType()) {return Icons_cfg::BOD_T4K_M(); }
         else if(TypeUnitNode::Y4_T4K_M    == getType()) {return Icons_cfg::Y4_T4K_M();  }
         else if(TypeUnitNode::DD_T4K_M    == getType()) {return Icons_cfg::Y4_T4K_M();  }
         else if(TypeUnitNode::TG          == getType()) {return Icons_cfg::TG();        }
         else if(TypeUnitNode::RLM_KRL     == getType()) {return Icons_cfg::RLM_KRL();   }
         else if(TypeUnitNode::RLM_C       == getType()) {return Icons_cfg::RLM_KRL();   }
         else if(TypeUnitNode::Y4_SOTA     == getType()) {return Icons_cfg::Y4_SOTA();   }
         else if(TypeUnitNode::DD_SOTA     == getType()) {return Icons_cfg::Y4_SOTA();   }
         else if(TypeUnitNode::KL          == getType()) {return Icons_cfg::KL();        }
         else if(TypeUnitNode::NET_DEV     == getType()) {return Icons_cfg::NET_DEV();   }
         else if(TypeUnitNode::ONVIF       == getType()) {return Icons_cfg::ONVIF();     }
         else if(TypeUnitNode::STRAZH_IP   == getType()) {return Icons_cfg::ONVIF();     }

         else if(TypeUnitNode::SSOI_SD   == getType()) {return Icons_cfg::default_square_gray();     }
         else if(TypeUnitNode::SSOI_IU   == getType()) {return Icons_cfg::default_square_gray();     }
         else if(TypeUnitNode::ADAM   == getType()) {return Icons_cfg::default_square_gray();     }
         else if(TypeUnitNode::TOROS   == getType()) {return Icons_cfg::default_square_gray();     }
         else if(TypeUnitNode::DEVLINE   == getType()) {return Icons_cfg::ONVIF();       }
         else if(TypeUnitNode::RASTRMTV   == getType()) {return Icons_cfg::ONVIF();       }
         else if(TypeUnitNode::INFO_TABLO   == getType()) {return Icons_cfg::default_square_gray();     }



//         Y4_SOTA = 30,//Участок Сота
//         DD_SOTA = 28,//ДД Сота

      }

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
        c->setStateWord(this->getStateWord());
        c->setStateWordType0x31(this->getStateWordType0x31());
        c->setStateWordType0x34(this->getStateWordType0x34());
        c->setStateWordType0x33(this->getStateWordType0x33());
        c->setStateWordType0x32(this->getStateWordType0x32());
        c->setDkStatus(this->getDkStatus());
        c->setDkInvolved(this->getDkInvolved());
        c->setParentUN(this->getParentUN());
        c->setTimeIntervalStatusRequest(this->getTimeIntervalStatusRequest());
        c->setControl(this->getControl());
        c->setX(this->getX());
        c->setY(this->getY());
    }
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

QByteArray UnitNode::getStateWord() const
{
    return stateWord;
}

void UnitNode::setStateWord(const QByteArray &value)
{
    stateWord = value;
}

int UnitNode::isConnected() const
{
    if(getStateWord().isEmpty())
        return 0;
    else
        return 1;
}

bool UnitNode::isEditableControl() const
{
    return editableControl;
}

int UnitNode::getCountSCRWA() const
{
    return countSCRWA;
}

void UnitNode::setCountSCRWA(int value)
{
    countSCRWA = value;
}

int UnitNode::getMaxCountSCRWA() const
{
    return maxCountSCRWA;
}

void UnitNode::setMaxCountSCRWA(int value)
{
    maxCountSCRWA = value;
}

QByteArray UnitNode::getStateWordType0x31() const
{
    return stateWordType0x31;
}

void UnitNode::setStateWordType0x31(const QByteArray &value)
{
    stateWordType0x31 = value;
}

QByteArray UnitNode::getStateWordType0x34() const
{
    return stateWordType0x34;
}

void UnitNode::setStateWordType0x34(const QByteArray &value)
{
    stateWordType0x34 = value;
}

QByteArray UnitNode::getStateWordType0x33() const
{
    return stateWordType0x33;
}

void UnitNode::setStateWordType0x33(const QByteArray &value)
{
    stateWordType0x33 = value;
}

int UnitNode::getNeededStateWordType() const
{
    return neededStateWordType;
}

void UnitNode::setNeededStateWordType(int value)
{
    neededStateWordType = value;
}

QByteArray UnitNode::getStateWordType0x32() const
{
    return stateWordType0x32;
}

void UnitNode::setStateWordType0x32(const QByteArray &value)
{
    stateWordType0x32 = value;
}

void UnitNode::matchEditableControl()
{
    if(!editableControl &&
       ((TypeUnitNode::SD_BL_IP == getType() && 0 == getBazalt()) ||
        TypeUnitNode::RLM_C == getType() ||
        TypeUnitNode::RLM_KRL == getType() ||
        TypeUnitNode::TG == getType() ||
        TypeUnitNode::TG_Base == getType()))
        editableControl = true;
}

void UnitNode::matchEditableOnOff()
{
    if(!editableOnOff &&
       ((0 == getBazalt() && TypeUnitNode::SD_BL_IP == getType()) ||
        TypeUnitNode::IU_BL_IP == getType() ||
        TypeUnitNode::RLM_C == getType() ||
        TypeUnitNode::RLM_KRL == getType()/* ||
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
       (TypeUnitNode::RLM_C == getType() ||
        TypeUnitNode::RLM_KRL == getType() ||
        TypeUnitNode::TG == getType() ||
        TypeUnitNode::TG_Base == getType()))
        needsPreamble = true;
}

bool UnitNode::isEditableOnOff() const
{
    return editableOnOff;
}

UnitNode::UnitNode(const QSharedPointer<UnitNode> parent) :
    /*UnitNodeCFG(static_cast<UnitNodeCFG*>(parent.data()))
  , */ServerUnitNodeTreeItem(parent)
{
    this->parentUN = parent;
}

const SWPSDBLIP UnitNode::swpSDBLIP() const {return SWPSDBLIP(getStateWord(), getNum2());}
const SWPIUBLIP UnitNode::swpIUBLIP() const {return SWPIUBLIP(getStateWord(), getNum2());}
const SWPBLIP UnitNode::swpBLIP() const {return SWPBLIP(getStateWord());}
const SWPRLM UnitNode::swpRLM() const {return SWPRLM(getStateWord());}
const SWPRLMC UnitNode::swpRLMC() const {return SWPRLMC(getStateWord());}
const SWPTGType0x31 UnitNode::swpTGType0x31() const {return SWPTGType0x31(getStateWord());}
const SWPTGType0x34 UnitNode::swpTGType0x34() const {return SWPTGType0x34(getStateWordType0x34());}
const SWPTGType0x33 UnitNode::swpTGType0x33() const {return SWPTGType0x33(getStateWordType0x33());}
const SWPTGType0x32 UnitNode::swpTGType0x32() const {return SWPTGType0x32(getStateWordType0x32());}



UnitNode::UnitNode(const UnitNode & parent) :
//    UnitNodeCFG(static_cast<UnitNodeCFG>(parent)),
    ServerUnitNodeTreeItem(),
    stateWord(parent.stateWord),
    stateWordType0x31(parent.stateWordType0x31),
    stateWordType0x32(parent.stateWordType0x32),
    stateWordType0x33(parent.stateWordType0x33),
    stateWordType0x34(parent.stateWordType0x34),
    metaNames(parent.metaNames),
    dkStatus(parent.dkStatus),
    dkInvolved(parent.dkInvolved)
{
    operator=(parent);
    setStateWord(parent.getStateWord());
    setStateWordType0x31(parent.getStateWordType0x31());
    setStateWordType0x34(parent.getStateWordType0x34());
    setStateWordType0x33(parent.getStateWordType0x33());
    setStateWordType0x32(parent.getStateWordType0x32());
    setMetaNames(parent.getMetaNames());

    setDkStatus(parent.getDkStatus());
    setDkInvolved(parent.getDkInvolved());

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
    setStateWord(c.getStateWord());
    setStateWordType0x31(c.getStateWordType0x31());
    setStateWordType0x34(c.getStateWordType0x34());
    setStateWordType0x33(c.getStateWordType0x33());
    setStateWordType0x32(c.getStateWordType0x32());
    setMetaNames(c.getMetaNames());

    setDkStatus(c.getDkStatus());
    setDkInvolved(c.getDkInvolved());

    matchEditableControl();
    matchEditableOnOff();
    matchNeedsPreamble();

    return *this;
}

QVariant UnitNode::dataTreeColumn(int column) const
{
    switch(column)
    {
        case 0:
        {
            return this->getName();
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

//    for(QSharedPointer<UnitNode> un : as_const(ServerSettingUtils::getListTreeUnitNodes())) {
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
//        QSharedPointer<UnitNode> iam = QSharedPointer<UnitNode>(this);
//        tc->setParentUN(iam);
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
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & 0x80)
        return 1; // Status::Exists);
    else
        return 0; // Status::Not);
}

int UnitNode_BL_IP::isWasAlarm() const
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & 0x40)
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}

int UnitNode_SD_BL_IP::calcDKStatus() const {
    if(1 == swpSDBLIP().isWasAlarm() && 1 == swpSDBLIP().isAlarm()) {
        return DKCiclStatus::DKWasAlarn;
    } else if(1 == swpSDBLIP().isNorm() && 1 == swpSDBLIP().isWasAlarm()) {
        return DKCiclStatus::DKWas;
//            return DKCiclStatus::DKWrong;
    } else if(1 == swpSDBLIP().isAlarm()) {
        return DKCiclStatus::DKWrong;
//            return DKCiclStatus::DKWasAlarn;
    } else if(1 == swpSDBLIP().isOff()) {
        return DKCiclStatus::DKWrong;
    } else if(1 == swpSDBLIP().isNorm()) {
        return DKCiclStatus::DKNorm;
    }
    return DKCiclStatus::DKWrong;
}


int UnitNode_TG::calcDKStatus() const {
     SWPTGType0x31 swp = swpTGType0x31();
    if(1 == swp.isWasAlarm() && 1 == swp.isAlarm()) {
        return DKCiclStatus::DKWasAlarn;
    } else if(1 == swp.isNorm() && 1 == swp.isWasAlarm()) {
        return DKCiclStatus::DKWas;
//            return DKCiclStatus::DKWrong;
    } else if(1 == swp.isAlarm()) {
        return DKCiclStatus::DKWrong;
//            return DKCiclStatus::DKWasAlarn;
    } else if(1 == swp.isOff()) {
        return DKCiclStatus::DKWrong;
    } else if(1 == swp.isNorm()) {
        return DKCiclStatus::DKNorm;
    }
    return DKCiclStatus::DKWrong;
}

int UnitNode_RLM_KRL::calcDKStatus() const {
    if(1 == swpRLM().isWasAlarm() && 1 == swpRLM().isAlarm()) {
        return DKCiclStatus::DKWasAlarn;
    } else if(1 == swpRLM().isNorm() && 1 == swpRLM().isWasAlarm()) {
        return DKCiclStatus::DKWas;
//            return DKCiclStatus::DKWrong;
    } else if(1 == swpRLM().isAlarm()) {
        return DKCiclStatus::DKWrong;
//            return DKCiclStatus::DKWasAlarn;
    } else if(1 == swpRLM().isOff()) {
        return DKCiclStatus::DKWrong;
    } else if(1 == swpRLM().isNorm()) {
        return DKCiclStatus::DKNorm;
    }
    return DKCiclStatus::DKWrong;
}

int UnitNode_RLM_C::calcDKStatus() const {
    if(1 == swpRLMC().isWasAlarm() && 1 == swpRLMC().isAlarm()) {
        return DKCiclStatus::DKWasAlarn;
    } else if(1 == swpRLMC().isNorm() && 1 == swpRLMC().isWasAlarm()) {
        return DKCiclStatus::DKWas;
//            return DKCiclStatus::DKWrong;
    } else if(1 == swpRLMC().isAlarm()) {
        return DKCiclStatus::DKWrong;
//            return DKCiclStatus::DKWasAlarn;
    } else if(1 == swpRLMC().isOff()) {
        return DKCiclStatus::DKWrong;
    } else if(1 == swpRLMC().isNorm()) {
        return DKCiclStatus::DKNorm;
    }
    return DKCiclStatus::DKWrong;
}
