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

//void UnitNode::emitIMUpd()
//{
//    qDebug() << "emitIMUpd " << getName() << " " << getStatus1() << getStatus2();
//    SignalSlotCommutator::getInstance()->emitUpdUN();
////    emit imUpd();
//}

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
                if(Status::Was == getStatus2() && getControl()) {
                    return Icons::sqr_rd();
                } else if(Status::Was == getStatus2() && !getControl()) {
                    return Icons::sqr_blk_crs_rd();
                } else if(Status::Alarm == getStatus1() && getControl()) {
                    return Icons::sqr_rd();
                } else if(Status::Alarm == getStatus1() && !getControl()) {
                    return Icons::sqr_blk_crs_rd();
                } else if((Status::Off == getStatus2()) && (Status::Uncnown == getStatus1()) && getControl()) {
                    return Icons::sqr_gry();
                } else if((Status::Off == getStatus2()) && (Status::Uncnown == getStatus1()) && !getControl()) {
                    return Icons::sqr_blk_crs_gry();
                } else if(Status::Norm == getStatus1() && getControl()) {
                    return Icons::sqr_grn();
                } else if(Status::Norm == getStatus1() && !getControl()) {
                    return Icons::sqr_blk_crs_grn();
                } else if(getControl()) {
                    return Icons::sqr_ylw();
                } else if(!getControl()) {
                    return Icons::sqr_blk_crs_ylw();
                }
            } else {
                if(Status::Alarm == getStatus1()) {
                    return Icons::sqr_rd_opn();
                } else if(Status::Norm == getStatus1()) {
                    return Icons::sqr_grn_cls();
                } else {
                    return Icons::sqr_ylw();
                }
            }

        } else if(TypeUnitNode::IU_BL_IP == getType()) {
            if(Status::On == getStatus1()) {
                return Icons::sqr_grn_crs2_rd();
            } else if(Status::Off == getStatus1()) {
                return Icons::sqr_grn_mns_gry();
            } else
                return Icons::sqr_ylw();
        }
    }
     if(SubTypeApp::configurator == type) {


         if(TypeUnitNode::GROUP == getType()||TypeUnitNode::SYSTEM == getType())
         {
         if(childCount())
         return Icons::fldr();
         else
         return Icons::fldr_empt();
         }
         else if(TypeUnitNode::SD_BL_IP    == getType()) {return Icons_cfg::sd();        }
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
}

void UnitNode::setDoubles(UnitNode * value)
{
    doubles.insert(value);
}

void UnitNode::updDoubl()
{
    for(auto c : as_const(this->doubles)) {
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

UnitNode::UnitNode(QObject *parent) : QObject(parent)
{
    
}

UnitNode::UnitNode(UnitNode *parent) : QObject(parent)
{
    this->parentUN = parent;
}

UnitNode::UnitNode(const UnitNode & parent) :
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
    MetkaDopuskTime_1(parent.MetkaDopuskTime_1)
{

}

UnitNode & UnitNode::operator=(const UnitNode& c) {
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
                return QVariant(QObject::trUtf8("Имя")); //"Имя"
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
    if(getListTreeChilde().count() < (index + 1)) {
        this->listTreeChilde.swap(index + 1, index);
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


