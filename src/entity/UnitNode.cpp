#include <QDebug>

#include <UnitNode.h>
#include <SettingUtils.h>
#include <Icons.h>
#include <Icons_cfg.h>
#include <SignalSlotCommutator.h>
#include <global.hpp>

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


int UnitNode::getType() const
{
    return Type;
}

void UnitNode::setType(int value)
{
    Type = value;
}

int UnitNode::getNum1() const
{
    return Num1;
}

void UnitNode::setNum1(int value)
{
    Num1 = value;
}

int UnitNode::getNum2() const
{
    return Num2;
}

void UnitNode::setNum2(int value)
{
    Num2 = value;
}

int UnitNode::getNum3() const
{
    return Num3;
}

void UnitNode::setNum3(int value)
{
    Num3 = value;
}

int UnitNode::getLevel() const
{
    return Level;
}

void UnitNode::setLevel(int value)
{
    Level = value;
}

QString UnitNode::getName() const
{
    return Name;
}

void UnitNode::setName(const QString &value)
{
    Name = value;
}

int UnitNode::getIconVisible() const
{
    return IconVisible;
}

void UnitNode::setIconVisible(int value)
{
    IconVisible = value;
}

int UnitNode::getX() const
{
    return X;
}

void UnitNode::setX(int value)
{
    X = value;
//    updDoubl();
}

int UnitNode::getY() const
{
    return Y;
}

void UnitNode::setY(int value)
{
    Y = value;
//    updDoubl();
}

int UnitNode::getDK() const
{
    return DK;
}

void UnitNode::setDK(int value)
{
    DK = value;
}

int UnitNode::getBazalt() const
{
    return Bazalt;
}

void UnitNode::setBazalt(int value)
{
    Bazalt = value;
}

int UnitNode::getMetka() const
{
    return Metka;
}

void UnitNode::setMetka(int value)
{
    Metka = value;
}

int UnitNode::getRazriv() const
{
    return Razriv;
}

void UnitNode::setRazriv(int value)
{
    Razriv = value;
}

int UnitNode::getAdamOff() const
{
    return AdamOff;
}

void UnitNode::setAdamOff(int value)
{
    AdamOff = value;
}

int UnitNode::getAlarmMsgOn() const
{
    return AlarmMsgOn;
}

void UnitNode::setAlarmMsgOn(int value)
{
    AlarmMsgOn = value;
}

int UnitNode::getConnectBlock() const
{
    return ConnectBlock;
}

void UnitNode::setConnectBlock(int value)
{
    ConnectBlock = value;
}

int UnitNode::getOutType() const
{
    return OutType;
}

void UnitNode::setOutType(int value)
{
    OutType = value;
}

int UnitNode::getAsoosd_kk() const
{
    return asoosd_kk;
}

void UnitNode::setAsoosd_kk(int value)
{
    asoosd_kk = value;
}

int UnitNode::getAsoosd_nn() const
{
    return asoosd_nn;
}

void UnitNode::setAsoosd_nn(int value)
{
    asoosd_nn = value;
}

QString UnitNode::getDescription() const
{
    return Description;
}

void UnitNode::setDescription(const QString &value)
{
    Description = value;
}

int UnitNode::getLan() const
{
    return lan;
}

void UnitNode::setLan(int value)
{
    lan = value;
}

int UnitNode::getLon() const
{
    return lon;
}

void UnitNode::setLon(int value)
{
    lon = value;
}

int UnitNode::getUdpUse() const
{
    return UdpUse;
}

void UnitNode::setUdpUse(int value)
{
    UdpUse = value;
}

QString UnitNode::getUdpAdress() const
{
    return UdpAdress;
}

void UnitNode::setUdpAdress(const QString &value)
{
    UdpAdress = value;
}

int UnitNode::getUdpPort() const
{
    return UdpPort;
}

void UnitNode::setUdpPort(int value)
{
    UdpPort = value;
}

int UnitNode::getUdpTimeout() const
{
    return UdpTimeout;
}

void UnitNode::setUdpTimeout(int value)
{
    UdpTimeout = value;
}

int UnitNode::getMetka1Time_0() const
{
    return Metka1Time_0;
}

void UnitNode::setMetka1Time_0(int value)
{
    Metka1Time_0 = value;
}

int UnitNode::getMetka1Time_1() const
{
    return Metka1Time_1;
}

void UnitNode::setMetka1Time_1(int value)
{
    Metka1Time_1 = value;
}

int UnitNode::getMetka2Time_0() const
{
    return Metka2Time_0;
}

void UnitNode::setMetka2Time_0(int value)
{
    Metka2Time_0 = value;
}

int UnitNode::getMetka2Time_1() const
{
    return Metka2Time_1;
}

void UnitNode::setMetka2Time_1(int value)
{
    Metka2Time_1 = value;
}

int UnitNode::getMetka3Time_0() const
{
    return Metka3Time_0;
}

void UnitNode::setMetka3Time_0(int value)
{
    Metka3Time_0 = value;
}

int UnitNode::getMetka3Time_1() const
{
    return Metka3Time_1;
}

void UnitNode::setMetka3Time_1(int value)
{
    Metka3Time_1 = value;
}

int UnitNode::getMetka4Time_0() const
{
    return Metka4Time_0;
}

void UnitNode::setMetka4Time_0(int value)
{
    Metka4Time_0 = value;
}

int UnitNode::getMetka4Time_1() const
{
    return Metka4Time_1;
}

void UnitNode::setMetka4Time_1(int value)
{
    Metka4Time_1 = value;
}

int UnitNode::getMetkaDopuskTime_0() const
{
    return MetkaDopuskTime_0;
}

void UnitNode::setMetkaDopuskTime_0(int value)
{
    MetkaDopuskTime_0 = value;
}

int UnitNode::getMetkaDopuskTime_1() const
{
    return MetkaDopuskTime_1;
}

void UnitNode::setMetkaDopuskTime_1(int value)
{
    MetkaDopuskTime_1 = value;
}

UnitNode *UnitNode::getParentUN() const
{
    return parentUN;
}

void UnitNode::setParentUN(UnitNode *value)
{
    parentUN = value;
//    updDoubl();
}

UnitNode *UnitNode::getTreeParentUN() const
{
    return treeParentUN;
}

void UnitNode::setTreeParentUN(UnitNode *value)
{
    treeParentUN = value;
}

int UnitNode::getTimeIntervalStatusRequest() const
{
    return timeIntervalStatusRequest;
}

void UnitNode::setTimeIntervalStatusRequest(int value)
{
    timeIntervalStatusRequest = value;
//    updDoubl();
}

QList<UnitNode *> UnitNode::getListTreeChilde() const
{
    return listTreeChilde;
}

QList<UnitNode *> UnitNode::getListChilde() const
{
    return listChilde;
}

quint8 UnitNode::getStatus1() const
{
    return status1;
}

void UnitNode::setStatus1(const quint8 &value)
{
    status1 = value;
//    updDoubl();
}

quint8 UnitNode::getStatus2() const
{
    return status2;
}

void UnitNode::setStatus2(const quint8 &value)
{
    status2 = value;
//    updDoubl();
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
            if(0 == getBazalt()) {
                if(1 == isWasAlarm() && getControl()) {
                    return Icons::sqr_rd();
                } else if(1 == isWasAlarm() && !getControl()) {
                    return Icons::sqr_blk_crs_rd();
                } else if(1 == isAlarm() && getControl()) {
                    return Icons::sqr_rd();
                } else if(1 == isAlarm() && !getControl()) {
                    return Icons::sqr_blk_crs_rd();
                } else if(1 == isOff() && getControl()) {
                    return Icons::sqr_gry();
                } else if(1 == isOff() && !getControl()) {
                    return Icons::sqr_blk_crs_gry();
                } else if(1 == isNorm() && getControl()) {
                    return Icons::sqr_grn();
                } else if(1 == isNorm() && !getControl()) {
                    return Icons::sqr_blk_crs_grn();
                } else if(getControl()) {
                    return Icons::sqr_ylw();
                } else if(!getControl()) {
                    return Icons::sqr_blk_crs_ylw();
                }
            } else {
                if(1 == isAlarm()) {
                    return Icons::sqr_rd_opn();
                } else if(1 == isNorm()) {
                    return Icons::sqr_grn_cls();
                } else {
                    return Icons::sqr_ylw();
                }
            }

        } else if(TypeUnitNode::IU_BL_IP == getType()) {
            if(1 == isOn()) {
                return Icons::sqr_grn_crs2_rd();
            } else if(1 == isOff()) {
                return Icons::sqr_grn_mns_gry();
            } else
                return Icons::sqr_ylw();
        } else if(TypeUnitNode::RLM_C == getType()) {
            if(0 == getBazalt()) {
                if(1 == isWasAlarm() && getControl()) {
                    return Icons::sqr_rd();
                } else if(1 == isWasAlarm() && !getControl()) {
                    return Icons::sqr_blk_crs_rd();
                } else if(1 == isAlarm() && getControl()) {
                    return Icons::sqr_rd();
                } else if(1 == isAlarm() && !getControl()) {
                    return Icons::sqr_blk_crs_rd();
                } else if(1 == isOff() && getControl()) {
                    return Icons::sqr_gry();
                } else if(1 == isOff() && !getControl()) {
                    return Icons::sqr_blk_crs_gry();
                } else if(1 == isNorm() && getControl()) {
                    return Icons::sqr_grn();
                } else if(1 == isNorm() && !getControl()) {
                    return Icons::sqr_blk_crs_grn();
                } else if(getControl()) {
                    return Icons::sqr_ylw();
                } else if(!getControl()) {
                    return Icons::sqr_blk_crs_ylw();
                }
            } else {
                if(1 == isAlarm()) {
                    return Icons::sqr_rd_opn();
                } else if(1 == isNorm()) {
                    return Icons::sqr_grn_cls();
                } else {
                    return Icons::sqr_ylw();
                }
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

QSet<UnitNode *> UnitNode::getDoubles() const
{
    return doubles;
}

void UnitNode::setDoubles(const QSet<UnitNode *> &value)
{
    doubles = value;
    doubles.remove(this);
}

void UnitNode::setDoubles(UnitNode * value)
{
    doubles.insert(value);
    doubles.remove(this);
}

void UnitNode::updDoubl()
{
    for(auto c : as_const(this->doubles)) {
        c->stateWord = this->stateWord;
        c->status1 = this->status1;
        c->status2 = this->status2;
        c->dkStatus = this->dkStatus;
        c->dkInvolved = this->dkInvolved;
        c->visible = this->visible;
        c->parentUN = this->parentUN;
        c->timeIntervalStatusRequest = this->timeIntervalStatusRequest;
        c->control = this->control;
        c->X = this->X;
        c->Y = this->Y;
//        metaNames = c->metaNames;
//        Type = c->Type;
//        Num1 = c->Num1;
//        Num2 = c->Num2;
//        Num3 = c->Num3;
//        Level = c->Level;
//        Name = c->Name;
//        IconVisible = c->IconVisible;

//        DK = c->DK;
//        Bazalt = c->Bazalt;
//        Metka = c->Metka;
//        Razriv = c->Razriv;
//        AdamOff = c->AdamOff;
//        AlarmMsgOn = c->AlarmMsgOn;
//        ConnectBlock = c->ConnectBlock;
//        OutType = c->OutType;
//        asoosd_kk = c->asoosd_kk;
//        asoosd_nn = c->asoosd_nn;
//        Description = c->Description;
//        lan = c->lan;
//        lon = c->lon;
//        UdpUse = c->UdpUse;
//        UdpAdress = c->UdpAdress;
//        UdpPort = c->UdpPort;
//        Metka1Time_0 = c->Metka1Time_0;
//        Metka1Time_1 = c->Metka1Time_1;
//        Metka2Time_0 = c->Metka2Time_0;
//        Metka2Time_1 = c->Metka2Time_1;
//        Metka3Time_0 = c->Metka3Time_0;
//        Metka3Time_1 = c->Metka3Time_1;
//        Metka4Time_0 = c->Metka4Time_0;
//        Metka4Time_1 = c->Metka4Time_1;
//        MetkaDopuskTime_0 = c->MetkaDopuskTime_0;
//        MetkaDopuskTime_1 = c->MetkaDopuskTime_1;
    }
}

bool UnitNode::getControl() const
{
    return control;
}

void UnitNode::setControl(bool value)
{
    control = value;
    //    updDoubl();
}

void UnitNode::deleteChild(int row)
{
    this->listChilde.removeAt(row);
    this->listTreeChilde.removeAt(row);
}

void UnitNode::deleteAll()
{
    this->listChilde.clear();
    this->listTreeChilde.clear();
}

int UnitNode::adamOffToMs(int adamOff)
{
    int interval;
    switch (adamOff) {
        case 0:
            interval = 0;
            break;
        case 1:
            interval = 5000;
            break;
        case 2:
            interval = 10000;
            break;
        case 3:
            interval = 30000;
            break;
        case 4:
            interval = 60000;
            break;
        case 5:
            interval = 300000;
            break;
        case 6:
            interval = 600000;
            break;
        case 7:
            interval = 1200000;
            break;
        case 8:
            interval = 2400000;
            break;
        case 9:
            interval = 3600000;
            break;
        default:
            interval = 0;
            break;
    }
    return interval;
}


QByteArray UnitNode::getStateWord() const
{
    return stateWord;
}

void UnitNode::setStateWord(const QByteArray &value)
{
    stateWord = value;
}

int UnitNode::isConnected()
{
    if(getStateWord().isEmpty())
        return 0;
    else
        return 1;
}

quint8 UnitNode_SD_BL_IP::mask()
{
    quint8 mask = 0;
    switch (this->getNum2()) {
    case 1:
        mask = 0x01;
        break;
    case 2:
        mask = 0x02;
        break;
    case 3:
        mask = 0x04;
        break;
    case 4:
        mask = 0x08;
        break;
    case 5:
        mask = 0x10;
        break;
    case 6:
        mask = 0x20;
        break;
    case 7:
        mask = 0x40;
        break;
    case 8:
        mask = 0x80;
        break;
    default:
        mask = 0x00;
        break;
    }
    return mask;
}

int UnitNode_SD_BL_IP::isAlarm()
{
    return isInAlarm();
}

int UnitNode_SD_BL_IP::isInAlarm()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(0)) & mask())
        return 1; //Status::Alarm);
    else
        return 0; //Status::Norm);
}


int UnitNode_SD_BL_IP::isNorm()
{
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int UnitNode_SD_BL_IP::isWasAlarm()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(2)) & mask())
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}

int UnitNode_SD_BL_IP::isOn()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(0) == (static_cast<quint8>(getStateWord().at(3)) & mask()))
        return 0; //Status::Off;
    else
        return 1; //
}

int UnitNode_SD_BL_IP::isOff()
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}


quint8 UnitNode_IU_BL_IP::mask()
{
    quint8 mask = 0;
    switch (this->getNum2()) {
    case 1:
        mask = 0x01;
        break;
    case 2:
        mask = 0x02;
        break;
    case 3:
        mask = 0x04;
        break;
    case 4:
        mask = 0x08;
        break;
    case 5:
        mask = 0x10;
        break;
    case 6:
        mask = 0x20;
        break;
    case 7:
        mask = 0x40;
        break;
    case 8:
        mask = 0x80;
        break;
    default:
        mask = 0x00;
        break;
    }
    return mask;
}

int UnitNode_IU_BL_IP::isOutAlarm()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & mask())
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}

int UnitNode_IU_BL_IP::isOn()
{
    return isOutAlarm();
}

int UnitNode_IU_BL_IP::isOff()
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

UnitNode::UnitNode(UnitNode *parent) : QObject(parent)
{
    this->parentUN = parent;
}

UnitNode::UnitNode(const UnitNode & parent) :
    QObject(nullptr),
    stateWord(parent.stateWord),
    metaNames(parent.metaNames),
    Type(parent.Type),
    Num1(parent.Num1),
    Num2(parent.Num2),
    Num3(parent.Num3),
    Level(parent.Level),
    Name(parent.Name),
    IconVisible(parent.IconVisible),
    X(parent.X),
    Y(parent.Y),
    DK(parent.DK),
    Bazalt(parent.Bazalt),
    Metka(parent.Metka),
    Razriv(parent.Razriv),
    AdamOff(parent.AdamOff),
    AlarmMsgOn(parent.AlarmMsgOn),
    ConnectBlock(parent.ConnectBlock),
    OutType(parent.OutType),
    asoosd_kk(parent.asoosd_kk),
    asoosd_nn(parent.asoosd_nn),
    Description(parent.Description),
    lan(parent.lan),
    lon(parent.lon),
    UdpUse(parent.UdpUse),
    UdpAdress(parent.UdpAdress),
    UdpPort(parent.UdpPort),
    Metka1Time_0(parent.Metka1Time_0),
    Metka1Time_1(parent.Metka1Time_1),
    Metka2Time_0(parent.Metka2Time_0),
    Metka2Time_1(parent.Metka2Time_1),
    Metka3Time_0(parent.Metka3Time_0),
    Metka3Time_1(parent.Metka3Time_1),
    Metka4Time_0(parent.Metka4Time_0),
    Metka4Time_1(parent.Metka4Time_1),
    MetkaDopuskTime_0(parent.MetkaDopuskTime_0),
    MetkaDopuskTime_1(parent.MetkaDopuskTime_1),
    dkStatus(parent.dkStatus),
    dkInvolved(parent.dkInvolved)
{

}

UnitNode & UnitNode::operator=(const UnitNode& c) {
    stateWord = c.stateWord;
    metaNames = c.metaNames;
    Type = c.Type;
    Num1 = c.Num1;
    Num2 = c.Num2;
    Num3 = c.Num3;
    Level = c.Level;
    Name = c.Name;
    IconVisible = c.IconVisible;
    X = c.X;
    Y = c.Y;
    DK = c.DK;
    Bazalt = c.Bazalt;
    Metka = c.Metka;
    Razriv = c.Razriv;
    AdamOff = c.AdamOff;
    AlarmMsgOn = c.AlarmMsgOn;
    ConnectBlock = c.ConnectBlock;
    OutType = c.OutType;
    asoosd_kk = c.asoosd_kk;
    asoosd_nn = c.asoosd_nn;
    Description = c.Description;
    lan = c.lan;
    lon = c.lon;
    UdpUse = c.UdpUse;
    UdpAdress = c.UdpAdress;
    UdpPort = c.UdpPort;
    Metka1Time_0 = c.Metka1Time_0;
    Metka1Time_1 = c.Metka1Time_1;
    Metka2Time_0 = c.Metka2Time_0;
    Metka2Time_1 = c.Metka2Time_1;
    Metka3Time_0 = c.Metka3Time_0;
    Metka3Time_1 = c.Metka3Time_1;
    Metka4Time_0 = c.Metka4Time_0;
    Metka4Time_1 = c.Metka4Time_1;
    MetkaDopuskTime_0 = c.MetkaDopuskTime_0;
    MetkaDopuskTime_1 = c.MetkaDopuskTime_1;

    dkStatus = c.dkStatus;
    dkInvolved = c.dkInvolved;
    return *this;
}

QVariant UnitNode::data(int column) const noexcept
{
    if(this->Name.isEmpty() &&
       this->metaNames.isEmpty())
    {
        switch(column)
        {
            case 0:
            {
                return QVariant(QObject::tr("Имя")); //"Имя"
            }
            default:
                return QVariant();
        }
    }
    else
    {
        switch(column)
        {
            case 0:
            {
                return this->Name;
            }
            default:
                return QVariant();
        }
    }

    return QVariant();
}

void UnitNode::addTreeChild(UnitNode *tc) noexcept
{
    if(!tc) {
        return;
    }
    tc->setTreeParentUN(nullptr);
    for(auto un : as_const(SettingUtils::getListTreeUnitNodes())) {
        un->listTreeChilde.removeAll(tc);
    }
    if(!this->listTreeChilde.contains(tc)) {
        this->listTreeChilde.append(tc);
        tc->setTreeParentUN(this);
    }
}

void UnitNode::moveTreeChildUNUp(UnitNode * childUN)
{
    if(!getListTreeChilde().contains(childUN))
        return;
    auto index = getListTreeChilde().indexOf(childUN);
    if(0 < index) {
        this->listTreeChilde.swap(index - 1, index);
    }
}

void UnitNode::moveTreeChildUNDown(UnitNode *childUN)
{
    if(!getListTreeChilde().contains(childUN))
        return;
    auto index = getListTreeChilde().indexOf(childUN);
    if(getListTreeChilde().count() > (index + 1)) {
        this->listTreeChilde.swap(index, index + 1);
    }
}

void UnitNode::addChild(UnitNode *tc) noexcept
{
    if(!tc)
    {
        return;
    }
    if(!this->listChilde.contains(tc))
    {
        this->listChilde.append(tc);
        tc->setParentUN(this);
    }
}

UnitNode* UnitNode::treeChild(int num) noexcept
{
    return listTreeChilde.value(num, 0);
}

QList<UnitNode*> UnitNode::treeChild() noexcept
{
    return listTreeChilde;
}

UnitNode* UnitNode::child(int num) noexcept
{
    return listChilde.value(num, 0);
}

int UnitNode::treeChildCount() const noexcept
{
    return this->listTreeChilde.size();////!!!!!
}

int UnitNode::childCount() const noexcept
{
    return this->listChilde.size();////!!!!!
}

int UnitNode::treeRow() const noexcept
{
    if (treeParentUN)
        return treeParentUN->listTreeChilde.indexOf(const_cast<UnitNode*>(this));
    return 0;
}

int UnitNode::columnCount() const noexcept
{
    return 2;//itemData.count();
}



int UnitNode_BL_IP::isExistDK()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & 0x80)
        return 1; // Status::Exists);
    else
        return 0; // Status::Not);
}

int UnitNode_BL_IP::isWasAlarm()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & 0x40)
        return 1; //Status::Was);
    else
        return 0; //Status::Not);
}

int UnitNode_RLM_C::isAlarm()
{
    return isInAlarm();
}

int UnitNode_RLM_C::isInAlarm()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x02))
        return 1; //Status::Alarm);
    else
        return 0; //Status::Not;
}

int UnitNode_RLM_C::isOutAlarm()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x04))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int UnitNode_RLM_C::isNorm()
{
    int isalarm = isAlarm();
    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
}

int UnitNode_RLM_C::isWasDK()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x20))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int UnitNode_RLM_C::isExistDK()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x10))
        return 1; //Status::Exist);
    else
        return 0; //Status::Not;
}

int UnitNode_RLM_C::isWasAlarm()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x08))
        return 1; //Status::Was);
    else
        return 0; //Status::Not;
}

int UnitNode_RLM_C::isOn()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x01))
        return 1; //Status::On);
    else
        return 0; //Status::Off;
}
//b5fe6304312c011600d9
int UnitNode_RLM_C::isOff()
{
    int ison = isOn();
    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
}

float UnitNode_RLM_C::voltage()
{
    if(getStateWord().isEmpty())
        return -1.0;
    return static_cast<float>(5.0 - (5.0 * (static_cast<double>(getStateWord().at(0)) / 255.0)));
}

int UnitNode_RLM_C::isExternalSynchronization()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x40))
        return 1; //External);
    else
        return 0; //Internal;
}

int UnitNode_RLM_C::isInternalSynchronization()
{
    int ises = isExternalSynchronization();
    return ((0 == ises) ? 1 : ((1 == ises) ? 0 : ises));
}

float UnitNode_RLM_C::threshold()
{
    if(getStateWord().isEmpty())
        return -1.0;
    switch (static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x0F)) {
    case static_cast<quint8>(0):  return 10.0;
    case static_cast<quint8>(1):  return 09.0;
    case static_cast<quint8>(2):  return 08.0;
    case static_cast<quint8>(3):  return 07.0;
    case static_cast<quint8>(4):  return 06.0;
    case static_cast<quint8>(5):  return 05.0;
    case static_cast<quint8>(6):  return 04.0;
    case static_cast<quint8>(7):  return 03.0;
    case static_cast<quint8>(8):  return 02.0;
    case static_cast<quint8>(9):  return 01.0;
    case static_cast<quint8>(10): return 00.6;
    case static_cast<quint8>(11): return 00.5;
    case static_cast<quint8>(12): return 00.4;
    case static_cast<quint8>(13): return 00.3;
    case static_cast<quint8>(14): return 00.2;
    case static_cast<quint8>(15): return 00.1;
    default: return -1.0;
    }
}

int UnitNode_RLM_C::clockPeriod()
{
    if(getStateWord().isEmpty())
        return -1;
    return (static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x70)) / static_cast<quint8>(0x0F);
}

int UnitNode_RLM_C::modeProcessing()
{
    if(getStateWord().isEmpty())
        return -1;
    return static_cast<quint8>(getStateWord().at(3)) & static_cast<quint8>(0x03);
}

int UnitNode_RLM_C::lowLevl()
{
    if(getStateWord().isEmpty())
        return -1;
    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x80))
        return 1; //Status::Error);
    else
        return 0; //Status::Not;
}

QString UnitNode::getIcon1Path() const
{
    return Icon1Path;
}

void UnitNode::setIcon1Path(const QString &value)
{
    Icon1Path = value;
}

QString UnitNode::getIcon2Path() const
{
    return Icon2Path;
}

void UnitNode::setIcon2Path(const QString &value)
{
    Icon2Path = value;
}

QString UnitNode::getIcon3Path() const
{
    return Icon3Path;
}

void UnitNode::setIcon3Path(const QString &value)
{
    Icon3Path = value;
}

QString UnitNode::getIcon4Path() const
{
    return Icon4Path;
}

void UnitNode::setIcon4Path(const QString &value)
{
    Icon4Path = value;
}

QString UnitNode::toString()
{
    QString result;
    result = "UnitNode(" + QString::number((qulonglong)this, 16) + "@";
    switch (getType()) {
    case SYSTEM: result.append("Система"); break; // -1,Система
    case GROUP: result.append("Группа"); break; // 0,Группа
    case KL: result.append("Концентратор"); break; // 2,Концентратор КЛ1
    case SD_BL_IP: result.append("СД БЛ-IP"); break; // 11,СД БЛ-IP
    case IU_BL_IP: result.append("ИУ БЛ-IP"); break; // 12,ИУ БЛ-IP
    case TG: result.append("Точка/Гарда"); break; // 10,      //Точка/Гарда
    case RLM_KRL: result.append("РИФ-РЛМ/КРЛ/Трасса"); break; // 1, //РИФ-РЛМ/КРЛ/Трасса
    case RLM_C: result.append("РИФ-РЛМ-С"); break; // 111, //РИФ- РЛМ-С
    case STRAZH_IP: result.append("Страж IP"); break; // 24, //Страж IP
    case ONVIF: result.append("ONVIF Камера"); break; // 25, //ONVIF камера
    case BOD_T4K_M: result.append("ОД Точка-М/Гарда"); break; // 26,БОД Точка-М/Гарда
    case Y4_T4K_M: result.append("Участок Точка-М/Гарда"); break; // 27,Участок Точка-М/Гарда
    case DD_T4K_M: result.append("ДД Точка-М/Гарда"); break; // 28,ДД Точка-М/Гарда
    case BOD_SOTA: result.append("БОД Сота"); break; // 29,БОД Сота
    case Y4_SOTA: result.append("Участок Сота"); break; // 30,Участок Сота
    case DD_SOTA: result.append("ДД Сота"); break; // 31,ДД Сота
    case NET_DEV: result.append("Сетевое устройство"); break; // 200,Сетевое устройство
    case BL_IP: result.append("БЛ-IP"); break; // 0xFF,БЛ IP
    default: result.append("UNKNOWEN"); break; //
    }
    result = result.append(" [" + getName() + "]").append(")");
    return result;
}
