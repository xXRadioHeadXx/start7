#include <QDebug>

#include <UnitNode.h>
#include <SettingUtils.h>
#include <Icons.h>
#include <Icons_cfg.h>
#include <SignalSlotCommutator.h>
#include <global.h>
#include <QtMath>

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
    matchEditableControl();
    matchEditableOnOff();
    matchNeedsPreamble();
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
    matchEditableControl();
    matchEditableOnOff();
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

    int udpTimeout = 50;

    udpTimeout = qMax(udpTimeout, getUdpTimeout());

    int maxBeatCount = 400;
    if(50 != udpTimeout) {
        maxBeatCount = (delayDisconnectStatus / udpTimeout) + 1;
    }
    setMaxCountSCRWA(maxBeatCount);
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
            const SWPSDBLIP swp = swpSDBLIP();
            if(0 == getBazalt()) {
                if(getControl() && swp.isNull()) {
                    qDebug() << "swp.isNull("<<swp.getStateWord().isEmpty()<<") "<<toString();
                    qDebug() << "swp.isNull("<<swp.isNull()<<")";
                    qDebug() << "swp.isNull("<<getStateWord().isEmpty()<<")";
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
            } else if(!getControl() && swpSDBLIP().isNull()) {
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
        } else if(TypeUnitNode::TG == getType()) {
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

         else if(TypeUnitNode::SSOI_SD   == getType())

             {
                 if(this->getBazalt()==1)
                     return Icons_cfg::sd_basalt();


                 if(this->getConnectBlock()==1)
                     return Icons_cfg::sd_connect_block();

                 return Icons_cfg::sd();
             }


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

QPixmap UnitNode::getPxm(SubTypeApp type, int column)
{
    if(SubTypeApp::configurator == type) {

             if(column==0)
             {
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

             else if(TypeUnitNode::SSOI_SD   == getType())

                 {
                     if(this->getBazalt()==1)
                         return Icons_cfg::sd_basalt();


                     if(this->getConnectBlock()==1)
                         return Icons_cfg::sd_connect_block();

                     return Icons_cfg::sd();
                 }


             else if(TypeUnitNode::SSOI_IU   == getType()) {return Icons_cfg::default_square_gray();     }


             else if(TypeUnitNode::ADAM   == getType()) {return Icons_cfg::default_square_gray();     }
             else if(TypeUnitNode::TOROS   == getType()) {return Icons_cfg::default_square_gray();     }
             else if(TypeUnitNode::DEVLINE   == getType()) {return Icons_cfg::ONVIF();       }
             else if(TypeUnitNode::RASTRMTV   == getType()) {return Icons_cfg::ONVIF();       }
             else if(TypeUnitNode::INFO_TABLO   == getType()) {return Icons_cfg::default_square_gray();     }



    //         Y4_SOTA = 30,//Участок Сота
    //         DD_SOTA = 28,//ДД Сота

          }
             else
             if(column==1)
             {
                 if(DK==1)
                 {
                     if(this->getType()==TypeUnitNode::SD_BL_IP)
                     return Icons_cfg::DK();

                     if(this->getType()==TypeUnitNode::SSOI_SD)
                     return Icons_cfg::DK();

                     if(this->getType()==TypeUnitNode::KL)
                     return Icons_cfg::DK();
                 }






                 return Icons_cfg::empty();

             }
             else
             if(column==2)
             {
                 if(AlarmMsgOn==1)
                 return Icons_cfg::Alarm();
                 else
                 return Icons_cfg::empty();
             }
    }

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
        c->stateWordType0x31 = this->stateWordType0x31;
        c->stateWordType0x32 = this->stateWordType0x32;
        c->stateWordType0x33 = this->stateWordType0x33;
        c->stateWordType0x34 = this->stateWordType0x34;
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

int UnitNode::isConnected() const
{
    if(getStateWord().isEmpty())
        return 0;
    else
        return 1;
}

//quint8 UnitNode_SD_BL_IP::mask() const
//{
//    quint8 mask = 0;
//    switch (this->getNum2()) {
//    case 1:
//        mask = 0x01;
//        break;
//    case 2:
//        mask = 0x02;
//        break;
//    case 3:
//        mask = 0x04;
//        break;
//    case 4:
//        mask = 0x08;
//        break;
//    case 5:
//        mask = 0x10;
//        break;
//    case 6:
//        mask = 0x20;
//        break;
//    case 7:
//        mask = 0x40;
//        break;
//    case 8:
//        mask = 0x80;
//        break;
//    default:
//        mask = 0x00;
//        break;
//    }
//    return mask;
//}

//int UnitNode_SD_BL_IP::isAlarm() const
//{
//    return isInAlarm();
//}

//int UnitNode_SD_BL_IP::isInAlarm() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(0)) & mask())
//        return 1; //Status::Alarm);
//    else
//        return 0; //Status::Norm);
//}


//int UnitNode_SD_BL_IP::isNorm() const
//{
//    int isalarm = isAlarm();
//    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
//}

//int UnitNode_SD_BL_IP::isWasAlarm() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(2)) & mask())
//        return 1; //Status::Was);
//    else
//        return 0; //Status::Not);
//}

//int UnitNode_SD_BL_IP::isOn() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(0) == (static_cast<quint8>(getStateWord().at(3)) & mask()))
//        return 0; //Status::Off;
//    else
//        return 1; //
//}

//int UnitNode_SD_BL_IP::isOff() const
//{
//    int ison = isOn();
//    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
//}


//quint8 UnitNode_IU_BL_IP::mask() const
//{
//    quint8 mask = 0;
//    switch (this->getNum2()) {
//    case 1:
//        mask = 0x01;
//        break;
//    case 2:
//        mask = 0x02;
//        break;
//    case 3:
//        mask = 0x04;
//        break;
//    case 4:
//        mask = 0x08;
//        break;
//    case 5:
//        mask = 0x10;
//        break;
//    case 6:
//        mask = 0x20;
//        break;
//    case 7:
//        mask = 0x40;
//        break;
//    case 8:
//        mask = 0x80;
//        break;
//    default:
//        mask = 0x00;
//        break;
//    }
//    return mask;
//}

//int UnitNode_IU_BL_IP::isOutAlarm() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(1)) & mask())
//        return 1; //Status::On);
//    else
//        return 0; //Status::Off;
//}

//int UnitNode_IU_BL_IP::isOn() const
//{
//    return isOutAlarm();
//}

//int UnitNode_IU_BL_IP::isOff() const
//{
//    int ison = isOn();
//    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
//}

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
        TypeUnitNode::TG == getType()))
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
        TypeUnitNode::TG == getType()))
        needsPreamble = true;
}

bool UnitNode::isEditableOnOff() const
{
    return editableOnOff;
}

UnitNode::UnitNode(UnitNode *parent) : QObject(parent)
{
    this->parentUN = parent;
}

UnitNode::UnitNode(const UnitNode & parent) :
    QObject(nullptr),
    stateWord(parent.stateWord),
    stateWordType0x31(parent.stateWordType0x31),
    stateWordType0x32(parent.stateWordType0x32),
    stateWordType0x33(parent.stateWordType0x33),
    stateWordType0x34(parent.stateWordType0x34),
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
    setStateWord(parent.getStateWord());
    setStateWordType0x31(parent.getStateWordType0x31());
    setStateWordType0x34(parent.getStateWordType0x34());
    setStateWordType0x33(parent.getStateWordType0x33());
    setStateWordType0x32(parent.getStateWordType0x32());
    setMetaNames(parent.getMetaNames());
    setType(parent.getType());
    setNum1(parent.getNum1());
    setNum2(parent.getNum2());
    setNum3(parent.getNum3());
    setLevel(parent.getLevel());
    setName(parent.getName());
    setIconVisible(parent.getIconVisible());
    setX(parent.getX());
    setY(parent.getY());
    setDK(parent.getDK());
    setBazalt(parent.getBazalt());
    setMetka(parent.getMetka());
    setRazriv(parent.getRazriv());
    setAdamOff(parent.getAdamOff());
    setAlarmMsgOn(parent.getAlarmMsgOn());
    setConnectBlock(parent.getConnectBlock());
    setOutType(parent.getOutType());
    setAsoosd_kk(parent.getAsoosd_kk());
    setAsoosd_nn(parent.getAsoosd_nn());
    setDescription(parent.getDescription());
    setLan(parent.getLan());
    setLon(parent.getLon());
    setUdpUse(parent.getUdpUse());
    setUdpAdress(parent.getUdpAdress());
    setUdpPort(parent.getUdpPort());
    setMetka1Time_0(parent.getMetka1Time_0());
    setMetka1Time_1(parent.getMetka1Time_1());
    setMetka2Time_0(parent.getMetka2Time_0());
    setMetka2Time_1(parent.getMetka2Time_1());
    setMetka3Time_0(parent.getMetka3Time_0());
    setMetka3Time_1(parent.getMetka3Time_1());
    setMetka4Time_0(parent.getMetka4Time_0());
    setMetka4Time_1(parent.getMetka4Time_1());
    setMetkaDopuskTime_0(parent.getMetkaDopuskTime_0());
    setMetkaDopuskTime_1(parent.getMetkaDopuskTime_1());
    setDkStatus(parent.getDkStatus());
    setDkInvolved(parent.getDkInvolved());

    matchEditableControl();
    matchEditableOnOff();
    matchNeedsPreamble();
}

UnitNode & UnitNode::operator=(const UnitNode& c) {
    setStateWord(c.getStateWord());
    setStateWordType0x31(c.getStateWordType0x31());
    setStateWordType0x34(c.getStateWordType0x34());
    setStateWordType0x33(c.getStateWordType0x33());
    setStateWordType0x32(c.getStateWordType0x32());
    setMetaNames(c.getMetaNames());
    setType(c.getType());
    setNum1(c.getNum1());
    setNum2(c.getNum2());
    setNum3(c.getNum3());
    setLevel(c.getLevel());
    setName(c.getName());
    setIconVisible(c.getIconVisible());
    setX(c.getX());
    setY(c.getY());
    setDK(c.getDK());
    setBazalt(c.getBazalt());
    setMetka(c.getMetka());
    setRazriv(c.getRazriv());
    setAdamOff(c.getAdamOff());
    setAlarmMsgOn(c.getAlarmMsgOn());
    setConnectBlock(c.getConnectBlock());
    setOutType(c.getOutType());
    setAsoosd_kk(c.getAsoosd_kk());
    setAsoosd_nn(c.getAsoosd_nn());
    setDescription(c.getDescription());
    setLan(c.getLan());
    setLon(c.getLon());
    setUdpUse(c.getUdpUse());
    setUdpAdress(c.getUdpAdress());
    setUdpPort(c.getUdpPort());
    setMetka1Time_0(c.getMetka1Time_0());
    setMetka1Time_1(c.getMetka1Time_1());
    setMetka2Time_0(c.getMetka2Time_0());
    setMetka2Time_1(c.getMetka2Time_1());
    setMetka3Time_0(c.getMetka3Time_0());
    setMetka3Time_1(c.getMetka3Time_1());
    setMetka4Time_0(c.getMetka4Time_0());
    setMetka4Time_1(c.getMetka4Time_1());
    setMetkaDopuskTime_0(c.getMetkaDopuskTime_0());
    setMetkaDopuskTime_1(c.getMetkaDopuskTime_1());
    setDkStatus(c.getDkStatus());
    setDkInvolved(c.getDkInvolved());

    matchEditableControl();
    matchEditableOnOff();
    matchNeedsPreamble();

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
        case 1:
        {
            return QVariant(QObject::tr("ДК"));
        }
        case 2:
        {
            return QVariant(QObject::tr("Тревоги"));
        }
        case 3:
        {
            return QVariant(QObject::tr("Автовыкл"));
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
            case 3:
            {
            if((this->getType()==TypeUnitNode::IU_BL_IP)||
               (this->getType()==TypeUnitNode::SSOI_IU))
                switch(this->getAdamOff())
                {
                case 0:

                break;

                case 1:
                return "5 сек";
                break;

                case 2:
                return "10 сек";
                break;

                case 3:
                return "30 сек";
                break;

                case 4:
                return "1 мин";
                break;

                case 5:
                return "5 мин";
                break;

                case 6:
                return "10 мин";
                break;

                case 7:
                return "20 мин";
                break;

                case 8:
                return "30 мин";
                break;

                case 9:
                return "1 час";
                break;
                }
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
//        this->listTreeChilde.swap(index - 1, index);
        qSwap(listTreeChilde[index - 1], listTreeChilde[index]);
    }
}

void UnitNode::moveTreeChildUNDown(UnitNode *childUN)
{
    if(!getListTreeChilde().contains(childUN))
        return;
    auto index = getListTreeChilde().indexOf(childUN);
    if(getListTreeChilde().count() > (index + 1)) {
//        this->listTreeChilde.swap(index, index + 1);
        qSwap(listTreeChilde[index], listTreeChilde[index + 1]);
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
    return 4;//itemData.count();
}



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

//int UnitNode_RLM_C::isAlarm() const
//{
//    return isInAlarm();
//}

//int UnitNode_RLM_C::isInAlarm() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x04))
//        return 1; //Status::Alarm);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_C::isOutAlarm() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x02))
//        return 1; //Status::Was);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_C::isNorm() const
//{
//    int isalarm = isAlarm();
//    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
//}

//int UnitNode_RLM_C::isWasDK() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x20))
//        return 1; //Status::Was);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_C::isExistDK() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x10))
//        return 1; //Status::Exist);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_C::isWasAlarm() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x08))
//        return 1; //Status::Was);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_C::isOn() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x01))
//        return 1; //Status::On);
//    else
//        return 0; //Status::Off;
//}
////b5fe6304312c011600d9
//int UnitNode_RLM_C::isOff() const
//{
//    int ison = isOn();
//    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
//}

//double UnitNode_RLM_C::voltage() const
//{
//    if(getStateWord().isEmpty())
//        return -1.0;
//    return qFabs(static_cast<float>(5.0 - qFabs(5.0 * (static_cast<double>(getStateWord().at(0)) / 255.0))));
//}

//int UnitNode_RLM_C::synchronization() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x40))
//        return 1; //External);
//    else
//        return 0; //Internal;
//}

//int UnitNode_RLM_C::isExternalSynchronization() const
//{
//    return synchronization();
//}

//int UnitNode_RLM_C::isInternalSynchronization() const
//{
//    int ises = isExternalSynchronization();
//    return ((0 == ises) ? 1 : ((1 == ises) ? 0 : ises));
//}

//float UnitNode_RLM_C::threshold() const
//{
//    if(getStateWord().isEmpty())
//        return -1.0;
//    switch (static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x0F)) {
//    case static_cast<quint8>(0):  return 10.0;
//    case static_cast<quint8>(1):  return 09.0;
//    case static_cast<quint8>(2):  return 08.0;
//    case static_cast<quint8>(3):  return 07.0;
//    case static_cast<quint8>(4):  return 06.0;
//    case static_cast<quint8>(5):  return 05.0;
//    case static_cast<quint8>(6):  return 04.0;
//    case static_cast<quint8>(7):  return 03.0;
//    case static_cast<quint8>(8):  return 02.0;
//    case static_cast<quint8>(9):  return 01.0;
//    case static_cast<quint8>(10): return 00.6;
//    case static_cast<quint8>(11): return 00.5;
//    case static_cast<quint8>(12): return 00.4;
//    case static_cast<quint8>(13): return 00.3;
//    case static_cast<quint8>(14): return 00.2;
//    case static_cast<quint8>(15): return 00.1;
//    default: return -1.0;
//    }
//}

//int UnitNode_RLM_C::clockPeriod() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    return (static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x70)) >> 4;
//}

//int UnitNode_RLM_C::modeProcessing() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    return static_cast<quint8>(getStateWord().at(3)) & static_cast<quint8>(0x03);
//}

//int UnitNode_RLM_C::lowLevl() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(1)) & static_cast<quint8>(0x80))
//        return 1; //Status::Error);
//    else
//        return 0; //Status::Not;
//}

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

QString UnitNode::toString() const
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
    case BL_IP: result.append("БЛ-IP").append(getUdpAdress()).append(":").append(QString::number(getUdpPort())); break; // 0xFF,БЛ IP
    default: result.append("UNKNOWEN"); break; //
    }
    result = result.append(" [" + getName() + "]").append(")");
    return result;
}

//float UnitNode_RLM_KRL::threshold() const
//{
//    if(getStateWord().isEmpty())
//        return -1.0;
//    switch (static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x0F)) {
//    case static_cast<quint8>(0):  return 10.0;
//    case static_cast<quint8>(1):  return 09.0;
//    case static_cast<quint8>(2):  return 08.0;
//    case static_cast<quint8>(3):  return 07.0;
//    case static_cast<quint8>(4):  return 06.0;
//    case static_cast<quint8>(5):  return 05.0;
//    case static_cast<quint8>(6):  return 04.0;
//    case static_cast<quint8>(7):  return 03.0;
//    case static_cast<quint8>(8):  return 02.0;
//    case static_cast<quint8>(9):  return 01.0;
//    case static_cast<quint8>(10): return 00.6;
//    case static_cast<quint8>(11): return 00.5;
//    case static_cast<quint8>(12): return 00.4;
//    case static_cast<quint8>(13): return 00.3;
//    case static_cast<quint8>(14): return 00.2;
//    case static_cast<quint8>(15): return 00.1;
//    default: return -1.0;
//    }
//}

//int UnitNode_RLM_KRL::modeProcessing() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    return (static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x10)) >> 4;
//}

//int UnitNode_RLM_KRL::clockPeriod() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    return (static_cast<quint8>(getStateWord().at(0)) & static_cast<quint8>(0x60)) >> 5;
//}

//double UnitNode_RLM_KRL::voltage() const
//{
//    if(getStateWord().isEmpty())
//        return -1.0;
//    return qFabs(static_cast<double>(5.0 - qFabs(5.0 * (static_cast<double>(getStateWord().at(1)) / 255.0))));
//}

//int UnitNode_RLM_KRL::isOn() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x01))
//        return 1; //Status::On);
//    else
//        return 0; //Status::Off;
//}

//int UnitNode_RLM_KRL::isOff() const
//{
//    int ison = isOn();
//    return ((0 == ison) ? 1 : ((1 == ison) ? 0 : ison));
//}

//int UnitNode_RLM_KRL::isAlarm() const
//{
//    return isInAlarm();
//}

//int UnitNode_RLM_KRL::isInAlarm() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x04))
//        return 1; //Status::Alarm);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_KRL::isOutAlarm() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x02))
//        return 1; //Status::Was);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_KRL::isNorm() const
//{
//    int isalarm = isAlarm();
//    return ((0 == isalarm) ? 1 : ((1 == isalarm) ? 0 : isalarm));
//}

//int UnitNode_RLM_KRL::isWasAlarm() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x08))
//        return 1; //Status::Was);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_KRL::isExistDK() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x10))
//        return 1; //Status::Exist);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_KRL::synchronization() const
//{
//    return isExistDK();
//}

//int UnitNode_RLM_KRL::isWasDK() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x20))
//        return 1; //Status::Was);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_KRL::isOpened() const
//{
//    return isInOpened();
//}

//int UnitNode_RLM_KRL::isInOpened() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x40))
//        return 1; //Status::Exist);
//    else
//        return 0; //Status::Not;
//}

//int UnitNode_RLM_KRL::isWasOpened() const
//{
//    if(getStateWord().isEmpty())
//        return -1;
//    if(static_cast<quint8>(getStateWord().at(2)) & static_cast<quint8>(0x80))
//        return 1; //Status::Was);
//    else
//        return 0; //Status::Not;
//}
