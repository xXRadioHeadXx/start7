#include "IniFileServiceImpl.h"

#include <QTextCodec>
#include "UnitNodeFactory.h"

QSharedPointer<UnitNode> IniFileServiceImpl::makeSharedUnitNodeBySection(const QString section)
{
    if(0 == ini.GetSection(section.toStdString().c_str()))
        return QSharedPointer<UnitNode>();

    QString isEnable = codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Enable"));
    if("false" == isEnable) {
//                qDebug() << "ServerSettingUtils::loadTreeUnitNodes -- " << key << " disabled";
        return QSharedPointer<UnitNode>();
    }

    auto tmpUN = UnitNodeFactory::makeShare(static_cast<TypeUnitNodeEnum>(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Type")).toInt()));
    tmpUN->setMetaNames(section);

    tmpUN->setType(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Type")).toInt());
    tmpUN->setNum1(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Num1")).toInt());
    tmpUN->setNum2(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Num2")).toInt());
    tmpUN->setNum3(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Num3")).toInt());
    tmpUN->setLevel(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Level")).toInt());
    tmpUN->setName(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Name")));
    tmpUN->setIconVisible(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "IconVisible")).toInt());
    tmpUN->setX(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "X")).toInt());
    tmpUN->setY(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Y")).toInt());
    tmpUN->setDK(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "DK")).toInt());
    tmpUN->setBazalt(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Bazalt")).toInt());
    tmpUN->setMetka(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Metka")).toInt());
    tmpUN->setRazriv(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Razriv")).toInt());
    tmpUN->setAdamOff(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "AdamOff")).toInt());
    tmpUN->setAlarmMsgOn(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "AlarmMsgOn")).toInt());
    tmpUN->setConnectBlock(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "ConnectBlock")).toInt());
    tmpUN->setOutType(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "OutType")).toInt());
    tmpUN->setAsoosd_kk(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "asoosd_kk")).toInt());
    tmpUN->setAsoosd_nn(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "asoosd_nn")).toInt());
    tmpUN->setDescription(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Description")));
    tmpUN->setLan(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "lan")).toInt());
    tmpUN->setLon(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "lon")).toInt());
    tmpUN->setUdpUse(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "UdpUse")).toInt());
    tmpUN->setUdpAdress(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "UdpAdress")));
    tmpUN->setUdpPort(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "UpdPort")).toInt());
    tmpUN->setMetka1Time_0(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Metka1Time_0")).toInt());
    tmpUN->setMetka1Time_1(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Metka1Time_1")).toInt());
    tmpUN->setMetka2Time_0(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Metka2Time_0")).toInt());
    tmpUN->setMetka2Time_1(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Metka2Time_1")).toInt());
    tmpUN->setMetka3Time_0(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Metka3Time_0")).toInt());
    tmpUN->setMetka3Time_1(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Metka3Time_1")).toInt());
    tmpUN->setMetka4Time_0(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Metka4Time_0")).toInt());
    tmpUN->setMetka4Time_1(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Metka4Time_1")).toInt());
    tmpUN->setMetkaDopuskTime_0(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "MetkaDopuskTime_0")).toInt());
    tmpUN->setMetkaDopuskTime_1(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "MetkaDopuskTime_1")).toInt());
    tmpUN->setUdpTimeout(qMax(50, codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "UdpTimeout")).toInt()));

    tmpUN->setIcon1Path(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Icon1Path")));
    tmpUN->setIcon2Path(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Icon2Path")));
    tmpUN->setIcon3Path(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Icon3Path")));
    tmpUN->setIcon4Path(codec->toUnicode(ini.GetValue(section.toStdString().c_str(), "Icon4Path")));

    return tmpUN;
}

const QString IniFileServiceImpl::getValueBySectionKey(const QString section, const QString key, const QString defaultValue)
{
    return codec->toUnicode(ini.GetValue(section.toStdString().c_str(), key.toStdString().c_str(), defaultValue.toStdString().c_str()));
}
