//#include <QDebug>

#include "UnitNodeCFG.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

int UnitNodeCFG::getType() const
{
    return Type;
}

void UnitNodeCFG::setType(int value)
{
    Type = value;
}

int UnitNodeCFG::getNum1() const
{
    return Num1;
}

void UnitNodeCFG::setNum1(int value)
{
    Num1 = value;
}

int UnitNodeCFG::getNum2() const
{
    return Num2;
}

void UnitNodeCFG::setNum2(int value)
{
    Num2 = value;
}

int UnitNodeCFG::getNum3() const
{
    return Num3;
}

void UnitNodeCFG::setNum3(int value)
{
    Num3 = value;
}

int UnitNodeCFG::getLevel() const
{
    return Level;
}

void UnitNodeCFG::setLevel(int value)
{
    Level = value;
}

QString UnitNodeCFG::getName() const
{
    return Name;
}

void UnitNodeCFG::setName(const QString &value)
{
    Name = value;
}

int UnitNodeCFG::getIconVisible() const
{
    return IconVisible;
}

void UnitNodeCFG::setIconVisible(int value)
{
    IconVisible = value;
}

int UnitNodeCFG::getX() const
{
    return X;
}

void UnitNodeCFG::setX(int value)
{
    X = value;
//    updDoubl();
}

int UnitNodeCFG::getY() const
{
    return Y;
}

void UnitNodeCFG::setY(int value)
{
    Y = value;
}

int UnitNodeCFG::getDK() const
{
    return DK;
}

void UnitNodeCFG::setDK(int value)
{
    DK = value;
}

int UnitNodeCFG::getBazalt() const
{
    return Bazalt;
}

void UnitNodeCFG::setBazalt(int value)
{
    Bazalt = value;
}

int UnitNodeCFG::getMetka() const
{
    return Metka;
}

void UnitNodeCFG::setMetka(int value)
{
    Metka = value;
}

int UnitNodeCFG::getRazriv() const
{
    return Razriv;
}

void UnitNodeCFG::setRazriv(int value)
{
    Razriv = value;
}

int UnitNodeCFG::getAdamOff() const
{
    return AdamOff;
}

void UnitNodeCFG::setAdamOff(int value)
{
    AdamOff = value;
}

int UnitNodeCFG::getAlarmMsgOn() const
{
    return AlarmMsgOn;
}

void UnitNodeCFG::setAlarmMsgOn(int value)
{
    AlarmMsgOn = value;
}

int UnitNodeCFG::getConnectBlock() const
{
    return ConnectBlock;
}

void UnitNodeCFG::setConnectBlock(int value)
{
    ConnectBlock = value;
}

int UnitNodeCFG::getOutType() const
{
    return OutType;
}

void UnitNodeCFG::setOutType(int value)
{
    OutType = value;
}

int UnitNodeCFG::getAsoosd_kk() const
{
    return asoosd_kk;
}

void UnitNodeCFG::setAsoosd_kk(int value)
{
    asoosd_kk = value;
}

int UnitNodeCFG::getAsoosd_nn() const
{
    return asoosd_nn;
}

void UnitNodeCFG::setAsoosd_nn(int value)
{
    asoosd_nn = value;
}

QString UnitNodeCFG::getDescription() const
{
    return Description;
}

void UnitNodeCFG::setDescription(const QString &value)
{
    Description = value;
}

int UnitNodeCFG::getLan() const
{
    return lan;
}

void UnitNodeCFG::setLan(int value)
{
    lan = value;
}

int UnitNodeCFG::getLon() const
{
    return lon;
}

void UnitNodeCFG::setLon(int value)
{
    lon = value;
}

int UnitNodeCFG::getUdpUse() const
{
    return UdpUse;
}

void UnitNodeCFG::setUdpUse(int value)
{
    UdpUse = value;
}

QString UnitNodeCFG::getUdpAdress() const
{
    return UdpAdress;
}

void UnitNodeCFG::setUdpAdress(const QString &value)
{
    UdpAdress = value;
}

QString UnitNodeCFG::getDirection() const
{
    return getUdpAdress() + ":" + QString::number(getUdpPort());
}

int UnitNodeCFG::getUdpPort() const
{
    return UdpPort;
}

void UnitNodeCFG::setUdpPort(int value)
{
    UdpPort = value;
}

int UnitNodeCFG::getUdpTimeout() const
{
    return UdpTimeout;
}

void UnitNodeCFG::setUdpTimeout(int value)
{
    UdpTimeout = value;
}

int UnitNodeCFG::getMetka1Time_0() const
{
    return Metka1Time_0;
}

void UnitNodeCFG::setMetka1Time_0(int value)
{
    Metka1Time_0 = value;
}

int UnitNodeCFG::getMetka1Time_1() const
{
    return Metka1Time_1;
}

void UnitNodeCFG::setMetka1Time_1(int value)
{
    Metka1Time_1 = value;
}

int UnitNodeCFG::getMetka2Time_0() const
{
    return Metka2Time_0;
}

void UnitNodeCFG::setMetka2Time_0(int value)
{
    Metka2Time_0 = value;
}

int UnitNodeCFG::getMetka2Time_1() const
{
    return Metka2Time_1;
}

void UnitNodeCFG::setMetka2Time_1(int value)
{
    Metka2Time_1 = value;
}

int UnitNodeCFG::getMetka3Time_0() const
{
    return Metka3Time_0;
}

void UnitNodeCFG::setMetka3Time_0(int value)
{
    Metka3Time_0 = value;
}

int UnitNodeCFG::getMetka3Time_1() const
{
    return Metka3Time_1;
}

void UnitNodeCFG::setMetka3Time_1(int value)
{
    Metka3Time_1 = value;
}

int UnitNodeCFG::getMetka4Time_0() const
{
    return Metka4Time_0;
}

void UnitNodeCFG::setMetka4Time_0(int value)
{
    Metka4Time_0 = value;
}

int UnitNodeCFG::getMetka4Time_1() const
{
    return Metka4Time_1;
}

void UnitNodeCFG::setMetka4Time_1(int value)
{
    Metka4Time_1 = value;
}

int UnitNodeCFG::getMetkaDopuskTime_0() const
{
    return MetkaDopuskTime_0;
}

void UnitNodeCFG::setMetkaDopuskTime_0(int value)
{
    MetkaDopuskTime_0 = value;
}

int UnitNodeCFG::getMetkaDopuskTime_1() const
{
    return MetkaDopuskTime_1;
}

void UnitNodeCFG::setMetkaDopuskTime_1(int value)
{
    MetkaDopuskTime_1 = value;
}

int UnitNodeCFG::getTimeIntervalStatusRequest() const
{
    return timeIntervalStatusRequest;
}

void UnitNodeCFG::setTimeIntervalStatusRequest(int value)
{
    timeIntervalStatusRequest = value;
//    updDoubl();
}

bool UnitNodeCFG::getControl() const
{
    return control;
}

void UnitNodeCFG::setControl(bool value)
{
    control = value;
    //    updDoubl();
}

int UnitNodeCFG::adamOffToMs(int adamOff)
{
    int interval;
    switch (adamOff) {
        case 0:
            interval = 0;
            break;
        case 1:
            interval = 5'000;
            break;
        case 2:
            interval = 10'000;
            break;
        case 3:
            interval = 30'000;
            break;
        case 4:
            interval = 60'000;
            break;
        case 5:
            interval = 300'000;
            break;
        case 6:
            interval = 600'000;
            break;
        case 7:
            interval = 1'200'000;
            break;
        case 8:
            interval = 2'400'000;
            break;
        case 9:
            interval = 3'600'000;
            break;
        default:
            interval = 0;
            break;
    }
    return interval;
}

UnitNodeCFG::UnitNodeCFG(const UnitNodeCFG* parent) :
    QObject(nullptr)
{
    if(nullptr != parent) {
        setType(parent->getType());
        setNum1(parent->getNum1());
        setNum2(parent->getNum2());
        setNum3(parent->getNum3());
        setOutType(parent->getOutType());
        setLevel(parent->getLevel());
        setName(parent->getName());
        setIconVisible(parent->getIconVisible());
        setX(parent->getX());
        setY(parent->getY());
        setDK(parent->getDK());
        setBazalt(parent->getBazalt());
        setMetka(parent->getMetka());
        setRazriv(parent->getRazriv());
        setAdamOff(parent->getAdamOff());
        setAlarmMsgOn(parent->getAlarmMsgOn());
        setConnectBlock(parent->getConnectBlock());
        setOutType(parent->getOutType());
        setAsoosd_kk(parent->getAsoosd_kk());
        setAsoosd_nn(parent->getAsoosd_nn());
        setDescription(parent->getDescription());
        setLan(parent->getLan());
        setLon(parent->getLon());
        setUdpUse(parent->getUdpUse());
        setUdpAdress(parent->getUdpAdress());
        setUdpPort(parent->getUdpPort());
        setMetka1Time_0(parent->getMetka1Time_0());
        setMetka1Time_1(parent->getMetka1Time_1());
        setMetka2Time_0(parent->getMetka2Time_0());
        setMetka2Time_1(parent->getMetka2Time_1());
        setMetka3Time_0(parent->getMetka3Time_0());
        setMetka3Time_1(parent->getMetka3Time_1());
        setMetka4Time_0(parent->getMetka4Time_0());
        setMetka4Time_1(parent->getMetka4Time_1());
        setMetkaDopuskTime_0(parent->getMetkaDopuskTime_0());
        setMetkaDopuskTime_1(parent->getMetkaDopuskTime_1());
        setIcon1Path(parent->getIcon1Path());
        setIcon2Path(parent->getIcon2Path());
        setIcon3Path(parent->getIcon3Path());
        setIcon4Path(parent->getIcon4Path());
        setTimeIntervalStatusRequest(parent->getTimeIntervalStatusRequest());
        setControl(parent->getControl());
    }
}

UnitNodeCFG::UnitNodeCFG(const UnitNodeCFG & parent) :
    QObject(nullptr)
{
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
    setIcon1Path(parent.getIcon1Path());
    setIcon2Path(parent.getIcon2Path());
    setIcon3Path(parent.getIcon3Path());
    setIcon4Path(parent.getIcon4Path());
    setTimeIntervalStatusRequest(parent.getTimeIntervalStatusRequest());
    setControl(parent.getControl());

}

UnitNodeCFG::~UnitNodeCFG()
{

}

QJsonDocument UnitNodeCFG::makeJson()
{
    QJsonObject unitNodeCFG;

    unitNodeCFG.insert("Type", QJsonValue::fromVariant(Type));
    unitNodeCFG.insert("Num1", QJsonValue::fromVariant(Num1));
    unitNodeCFG.insert("Num2", QJsonValue::fromVariant(Num2));
    unitNodeCFG.insert("Num3", QJsonValue::fromVariant(Num3));
    unitNodeCFG.insert("Level", QJsonValue::fromVariant(Level));
    unitNodeCFG.insert("Name", QJsonValue::fromVariant(Name));
    unitNodeCFG.insert("IconVisible", QJsonValue::fromVariant(IconVisible));
    unitNodeCFG.insert("X", QJsonValue::fromVariant(X));
    unitNodeCFG.insert("Y", QJsonValue::fromVariant(Y));
    unitNodeCFG.insert("DK", QJsonValue::fromVariant(DK));
    unitNodeCFG.insert("Bazalt", QJsonValue::fromVariant(Bazalt));
    unitNodeCFG.insert("Metka", QJsonValue::fromVariant(Metka));
    unitNodeCFG.insert("Razriv", QJsonValue::fromVariant(Razriv));
    unitNodeCFG.insert("AdamOff", QJsonValue::fromVariant(AdamOff));
    unitNodeCFG.insert("AlarmMsgOn", QJsonValue::fromVariant(AlarmMsgOn));
    unitNodeCFG.insert("ConnectBlock", QJsonValue::fromVariant(ConnectBlock));
    unitNodeCFG.insert("OutType", QJsonValue::fromVariant(OutType));
    unitNodeCFG.insert("asoosd_kk", QJsonValue::fromVariant(asoosd_kk));
    unitNodeCFG.insert("asoosd_nn", QJsonValue::fromVariant(asoosd_nn));
    unitNodeCFG.insert("Description", QJsonValue::fromVariant(Description));
    unitNodeCFG.insert("lan", QJsonValue::fromVariant(lan));
    unitNodeCFG.insert("lon", QJsonValue::fromVariant(lon));
    unitNodeCFG.insert("UdpUse", QJsonValue::fromVariant(UdpUse));
    unitNodeCFG.insert("UdpAdress", QJsonValue::fromVariant(UdpAdress));
    unitNodeCFG.insert("UdpPort", QJsonValue::fromVariant(UdpPort));
    unitNodeCFG.insert("UdpTimeout", QJsonValue::fromVariant(UdpTimeout));
    unitNodeCFG.insert("Metka1Time_0", QJsonValue::fromVariant(Metka1Time_0));
    unitNodeCFG.insert("Metka1Time_1", QJsonValue::fromVariant(Metka1Time_1));
    unitNodeCFG.insert("Metka2Time_0", QJsonValue::fromVariant(Metka2Time_0));
    unitNodeCFG.insert("Metka2Time_1", QJsonValue::fromVariant(Metka2Time_1));
    unitNodeCFG.insert("Metka3Time_0", QJsonValue::fromVariant(Metka3Time_0));
    unitNodeCFG.insert("Metka3Time_1", QJsonValue::fromVariant(Metka3Time_1));
    unitNodeCFG.insert("Metka4Time_0", QJsonValue::fromVariant(Metka4Time_0));
    unitNodeCFG.insert("Metka4Time_1", QJsonValue::fromVariant(Metka4Time_1));
    unitNodeCFG.insert("MetkaDopuskTime_0", QJsonValue::fromVariant(MetkaDopuskTime_0));
    unitNodeCFG.insert("MetkaDopuskTime_1", QJsonValue::fromVariant(MetkaDopuskTime_1));
    unitNodeCFG.insert("Icon1Path", QJsonValue::fromVariant(Icon1Path));
    unitNodeCFG.insert("Icon2Path", QJsonValue::fromVariant(Icon2Path));
    unitNodeCFG.insert("Icon3Path", QJsonValue::fromVariant(Icon3Path));
    unitNodeCFG.insert("Icon4Path", QJsonValue::fromVariant(Icon4Path));

    QJsonDocument doc(unitNodeCFG);

    return doc;
}

UnitNodeCFG & UnitNodeCFG::operator=(const UnitNodeCFG& c) {
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
    setIcon1Path(c.getIcon1Path());
    setIcon2Path(c.getIcon2Path());
    setIcon3Path(c.getIcon3Path());
    setIcon4Path(c.getIcon4Path());
    setTimeIntervalStatusRequest(c.getTimeIntervalStatusRequest());
    setControl(c.getControl());

    return *this;
}

QString UnitNodeCFG::getIcon1Path() const
{
    return Icon1Path;
}

void UnitNodeCFG::setIcon1Path(const QString &value)
{
    Icon1Path = value;
}

QString UnitNodeCFG::getIcon2Path() const
{
    return Icon2Path;
}

void UnitNodeCFG::setIcon2Path(const QString &value)
{
    Icon2Path = value;
}

QString UnitNodeCFG::getIcon3Path() const
{
    return Icon3Path;
}

void UnitNodeCFG::setIcon3Path(const QString &value)
{
    Icon3Path = value;
}

QString UnitNodeCFG::getIcon4Path() const
{
    return Icon4Path;
}

void UnitNodeCFG::setIcon4Path(const QString &value)
{
    Icon4Path = value;
}

QString UnitNodeCFG::toString() const
{
    QString result;
    result = "UnitNode(" + QString::number((qulonglong)this, 16) + "@";
    switch (getType()) {
    case SYSTEM: result.append("Система"); break; // -1,Система
    case GROUP: result.append("Группа"); break; // 0,Группа
    case KL: result.append("Концентратор"); break; // 2,Концентратор КЛ1
    case SD_BL_IP: result.append("СД БЛ-IP"); break; // 11,СД БЛ-IP
    case IU_BL_IP: result.append("ИУ БЛ-IP"); break; // 12,ИУ БЛ-IP
    case SSOI_SD_BL_IP: result.append("ССОИ СД БЛ-IP"); break; // 44,ССОИ СД БЛ-IP
    case SSOI_IU_BL_IP: result.append("ССОИ ИУ БЛ-IP"); break; // 45,ССОИ ИУ БЛ-IP
    case TG: result.append("Точка/Гарда"); break; // 10,      //Точка/Гарда
    case TG_Base: result.append("Meta Точка/Гарда"); break; // 110,      //Точка/Гарда
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
    case SSOI_BL_IP: result.append("ССОИ БЛ-IP").append(getUdpAdress()).append(":").append(QString::number(getUdpPort()).append(QString(" Адресс:%1").arg(getNum1()))); break; // 0xFF,БЛ IP
    default: result.append("UNKNOWEN"); break; //
    }
    result = result.append(" [" + getName() + "]").append(")").append(getDirection());
    return result;
}
