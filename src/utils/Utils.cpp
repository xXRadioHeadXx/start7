#include <Utils.h>
#include <SettingUtils.h>
#include <SignalSlotCommutator.h>
#include <PortManager.h>

Utils::Utils()
{

}

QHostAddress Utils::hostAddress(const QString ip) {
    QString address = strHostAddress(ip);
    return QHostAddress(address);
}

QString Utils::strHostAddress(const QString ip) {
    QString address = (ip == "localhost" ? "127.0.0.1" : ip);
    return address;
}

QString Utils::hostAddressToString(const QHostAddress host)
{
    bool conversionOK = false;
    QHostAddress ip4Address(host.toIPv4Address(&conversionOK));
    QString ip4String;
    if (conversionOK)
    {
        ip4String = ip4Address.toString();
    }
    return ip4String;
}

quint8 Utils::getByteSumm(QByteArray &ba, int bi, int ei) {
    if(-1 == ei) {
        ei = ba.size() - 1;
    }

    quint8 sum = 0;
    for(; bi <= ei; bi++) {
        sum += (quint8)ba.at(bi);
    }

    return sum;
}

QString Utils::typeUNToStr(const int type)
{
    switch (type) {
    case 0:
        return QObject::trUtf8("Группа"); //"Группа";
    case 11:
        return QObject::trUtf8("СД"); //"СД БЛ-IP";
    case 12:
        return QObject::trUtf8("ИУ"); //"ИУ БЛ-IP";
    case 10:
        return QObject::trUtf8("Точка-Гарда"); //"Точка-Гарда";
    case 1:
        return QObject::trUtf8("РИФ-РЛМ(КРЛ), Трасса"); //"РИФ-РЛМ(КРЛ), Трасса";
    case 111:
        return QObject::trUtf8("РИФ-С"); //"РИФ-С";
    case 26:
        return QObject::trUtf8("БОД Точка-М"); //"БОД Точка-М";
    case 27:
        return QObject::trUtf8("Участок Точка-М"); //"Участок Точка-М";
    case 28:
        return QObject::trUtf8("ДД Точка-М"); //"ДД Точка-М";
    case 29:
        return QObject::trUtf8("БОД Сота-М"); //"БОД Сота-М";
    case 30:
        return QObject::trUtf8("Участок Сота-М"); //"Участок Сота-М";
//    case 28:
//        return QObject::trUtf8("ДД Сота-М"); //"ДД Сота-М";
    default:
        return QObject::trUtf8("БЛ-IP");
    }
}

QString Utils::baMsgToStr(const QByteArray ba)
{
    if(5 <= ba.size()) {
        if((quint8)0xFF != (quint8)ba.at(1) &&
           (quint8)0x00 == (quint8)ba.at(3) &&
           (quint8)0x30 == (quint8)ba.at(4))
            return  QObject::trUtf8("Подтверждение приема концентратором"); //"Подтверждение приема концентратором";
        else if((quint8)0xFF != (quint8)ba.at(1) &&
                (quint8)0x04 == (quint8)ba.at(3) &&
                (quint8)0x41 == (quint8)ba.at(4))
            return  QObject::trUtf8("Передача слов состояния концентратора"); //"Передача слов состояния концентратора";
    } else if(4 <= ba.size()) {
        if((quint8)0xFF == (quint8)ba.at(1) &&
           (quint8)0x00 == (quint8)ba.at(2) &&
           (quint8)0x22 == (quint8)ba.at(3))
            return QObject::trUtf8("Запрос состояния концентратора"); //"Запрос состояния концентратора";
        else if((quint8)0xFF == (quint8)ba.at(1) &&
                (quint8)0x00 == (quint8)ba.at(2) &&
                (quint8)0x24 == (quint8)ba.at(3))
            return QObject::trUtf8("Сброс флагов тревоги, ДК"); //"Сброс флагов тревоги, ДК";
        else if((quint8)0xFF == (quint8)ba.at(1) &&
                (quint8)0x01 == (quint8)ba.at(2) &&
                (quint8)0x23 == (quint8)ba.at(3))
            return  QObject::trUtf8("Управление ИУ"); //"Управление ИУ";
    } else if(1 == ba.size()) {
        if((quint8)0xFF == (quint8)ba.at(0))
            return  QObject::trUtf8("Включение"); //"Включение";
        else if((quint8)0x00 == (quint8)ba.at(0))
            return  QObject::trUtf8("Выключение"); //"Выключение";
    }

    return ba.toHex();
}

bool Utils::isSavedMsg(const QByteArray ba) {

    if(5 <= ba.size()) {
        if((quint8)0xFF != (quint8)ba.at(1) &&
           (quint8)0x00 == (quint8)ba.at(3) &&
           (quint8)0x30 == (quint8)ba.at(4))
            return true; //"Подтверждение приема концентратором";
        else if((quint8)0xFF != (quint8)ba.at(1) &&
                (quint8)0x04 == (quint8)ba.at(3) &&
                (quint8)0x41 == (quint8)ba.at(4))
            return false; //"Передача слов состояния концентратора";
    } else if(4 <= ba.size()) {
        if((quint8)0xFF == (quint8)ba.at(1) &&
           (quint8)0x00 == (quint8)ba.at(2) &&
           (quint8)0x22 == (quint8)ba.at(3))
            return false; //"Запрос состояния концентратора";
        else if((quint8)0xFF == (quint8)ba.at(1) &&
                (quint8)0x00 == (quint8)ba.at(2) &&
                (quint8)0x24 == (quint8)ba.at(3))
            return true; //"Сброс флагов тревоги, ДК";
        else if((quint8)0xFF == (quint8)ba.at(1) &&
                (quint8)0x01 == (quint8)ba.at(2) &&
                (quint8)0x23 == (quint8)ba.at(3))
            return true; //"Управление ИУ";
    } else if(1 == ba.size()) {
        if((quint8)0xFF == (quint8)ba.at(0))
            return true; //"Включение";
        else if((quint8)0x00 == (quint8)ba.at(0))
            return true; //"Выключение";
    }

    return true;
}

template <typename T>
QList<T> Utils::reversed( const QList<T> & in ) {
    QList<T> result;
    result.reserve( in.size() );
    std::reverse_copy( in.begin(), in.end(), std::back_inserter( result ) );
    return result;
}

Port * Utils::typeDefPort(const AbstractPort * port) {
    if(AbstractPort::UDP == port->getProtocol())
        return (Port *)port;
    else
        return nullptr;
}

QByteArray Utils::data0x21 = QByteArray();

DataQueueItem Utils::makeDK0x21(DataQueueItem &item, const UnitNode *un)
{
    item.setData(makeDK0x21(un));
    return item;
}

QByteArray Utils::makeDK0x21(const UnitNode *un)
{
    if(Utils::data0x21.isEmpty()) {
        Utils::data0x21.append((quint8)0xB5);      //<SB>
        Utils::data0x21.append((quint8)0xFF);      //<ADDR>
        Utils::data0x21.append((char)0x00);        //<NBB> 0x00
        Utils::data0x21.append((quint8)0x21);      //<CMD> 0x21
        Utils::data0x21.append(getByteSumm(Utils::data0x21)); //<CHKS>
    }
    return Utils::data0x21;
}

QByteArray Utils::data0x22 = QByteArray();

DataQueueItem Utils::makeStatusRequest0x22(DataQueueItem &item, const UnitNode *un)
{
    item.setData(makeStatusRequest0x22(un));
    return item;
}

QByteArray Utils::makeStatusRequest0x22(const UnitNode *un)
{
    if(Utils::data0x22.isEmpty()) {
        Utils::data0x22.append((quint8)0xB5);      //<SB>
        Utils::data0x22.append((quint8)0xFF);      //<ADDR>
        Utils::data0x22.append((char)0x00);        //<NBB> 0x00
        Utils::data0x22.append((quint8)0x22);      //<CMD> 0x22
        Utils::data0x22.append(getByteSumm(Utils::data0x22)); //<CHKS>
    }

    return Utils::data0x22;
}

QByteArray Utils::data0x24 = QByteArray();

DataQueueItem Utils::makeAlarmReset0x24(DataQueueItem &item, const UnitNode *un)
{
    item.setData(makeAlarmReset0x24(un));
    return item;
}

QByteArray Utils::makeAlarmReset0x24(const UnitNode *un)
{
    if(Utils::data0x24.isEmpty()) {
        Utils::data0x24.append((quint8)0xB5);      //<SB>
        Utils::data0x24.append((quint8)0xFF);      //<ADDR>
        Utils::data0x24.append((char)0x00);        //<NBB> 0x00
        Utils::data0x24.append((quint8)0x24);      //<CMD> 0x24
        Utils::data0x24.append(getByteSumm(Utils::data0x24)); //<CHKS>
    }

    return Utils::data0x24;
}

QByteArray Utils::data0x20 = QByteArray();

DataQueueItem Utils::makeOnOff0x20(DataQueueItem &item, const UnitNode *un)
{
    item.setData(makeOnOff0x20(un));
    return item;
}

QByteArray Utils::makeOnOff0x20(const UnitNode *un)
{
    if(Utils::data0x20.isEmpty()) {
        Utils::data0x20.append((quint8)0xB5);      //<SB>
        Utils::data0x20.append((quint8)0xFF);      //<ADDR>
        Utils::data0x20.append((char)0x01);        //<NBB> 0x00
        Utils::data0x20.append((quint8)0x20);      //<CMD> 0x20
        Utils::data0x20.append((quint8)0xFF);      //<D1>
        Utils::data0x20.append(getByteSumm(Utils::data0x20)); //<CHKS>
    }

    return Utils::data0x20;
}

QByteArray Utils::data0x23 = QByteArray();

DataQueueItem Utils::makeOnOff0x23(DataQueueItem &item, UnitNode *un)
{
    item.setData(makeOnOff0x23(un, true));
    return item;
}

QByteArray Utils::makeOnOff0x23(UnitNode *un, bool onOff , UnitNode *pun)
{
    if(Utils::data0x23.isEmpty()) {
        Utils::data0x23.append((quint8)0xB5);      //<SB>
        Utils::data0x23.append((quint8)0xFF);      //<ADDR>
        Utils::data0x23.append((char)0x01);        //<NBB> 0x00
        Utils::data0x23.append((quint8)0x23);      //<CMD> 0x23
        Utils::data0x23.append((quint8)0xFF);      //<D1>
        Utils::data0x23.append(getByteSumm(Utils::data0x23)); //<CHKS>
    }

    if(nullptr == un)
        return Utils::data0x23;
    else if(TypeUnitNode::IU_BL_IP != un->getType())
        return Utils::data0x23;

    UnitNode * target = un;

    if(nullptr == pun) {
        pun = target;
    }
    if(TypeUnitNode::BL_IP != pun->getType()) {
        while(nullptr != pun) {
            if(TypeUnitNode::BL_IP == pun->getType()) {
                break;
            }
            pun = pun->getParentUN();
        }
    }
    UnitNode * reciver = pun;

    quint8 D1 = 0x00;
    if(TypeUnitNode::SD_BL_IP == target->getType() ||
            TypeUnitNode::IU_BL_IP == target->getType()) {
        while(nullptr != reciver) {
            if(TypeUnitNode::BL_IP == reciver->getType()) {
                break;
            }
            reciver = reciver->getParentUN();
        }
    }
    int type = target->getType();

    for(UnitNode * un : reciver->getListChilde()) {
        if(type != un->getType())
            continue;
        quint8 mask = 0;
        switch (un->getNum2()) {
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

        if(TypeUnitNode::SD_BL_IP == un->getType() &&
                Status::Off == un->getStatus2() &&
                Status::Uncnown == un->getStatus1())
            D1 = D1 & ~mask;
        else if(TypeUnitNode::IU_BL_IP == un->getType() &&
                Status::Off == un->getStatus1())
            D1 = D1 & ~mask;
        else
            D1 = D1 | mask;

        if(un == target && onOff)
            D1 = D1 | mask;
        else if(un == target && !onOff)
            D1 = D1 & ~mask;
    }

    QByteArray data = Utils::data0x23;
    data[4] = D1;
    data.chop(1);
    data.append(Utils::getByteSumm(data)); //<CHKS>

    return data;
}

bool Utils::isValideDirectionI(DataQueueItem &item)
{
    if(item.data().isEmpty() || item.address().isNull() || 0 > item.port() || -1 > item.portIndex())
        return false;

    try {
        quint8 SB = item.data().at(0),
                ADDR_r = item.data().at(1),
                ADDR_s = item.data().at(2),
                NBB = item.data().at(3),
                CMD = item.data().at(4);
        quint8 CHKS = item.data().at(5 + NBB);

        if((quint8)0xB5 != SB ||
                (quint8)0xFE != ADDR_r ||
                (quint8)0xFF != ADDR_s)
            return false;

        QByteArray tmpData = item.data();
        quint8 crc = getByteSumm(tmpData, 1, 5 + NBB - 1);
        if(crc != CHKS)
            return false;

        switch (CMD) {
        case (quint8)0x41: {
            if((quint8)0x04 != NBB)
                return false;
            return true;
        }
        case (quint8)0x30: {
            if((quint8)0x00 != NBB)
                return false;
            return true;
        }
        default:
            return false;
        }

        return true;

    } catch (...) {
        qDebug() << "fillDiagnosticTable catch exception ...";
    }


    return false;
}

DataQueueItem Utils::parcingStatusWord0x41(DataQueueItem &item, DataQueueItem & resultRequest)
{
//    qDebug() << "Utils::parcingStatusWord0x41 -->";
    resultRequest = item;
    resultRequest.setData();

    QSet<UnitNode *> tmpSet = SettingUtils::getSetMetaRealUnitNodes();
    for(UnitNode * un : tmpSet) {
        if(!item.address().isEqual(QHostAddress(un->getUdpAdress())) || item.port() != un->getUdpPort())
            continue;

        quint8 mask = 0;
        switch (un->getNum2()) {
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

        quint8 newStatus1 = Status::Uncnown, newStatus2 = Status::Uncnown; // un->getStatus();
        if(TypeUnitNode::BL_IP == un->getType()) {
            if((quint8)item.data().at(6) & 0x40)
                newStatus2 = (newStatus2 | Status::Was);
            else
                newStatus2 = (newStatus2 | Status::Not);

            if((quint8)item.data().at(6) & 0x80)
                newStatus1 = (newStatus1 | Status::Exists);
            else
                newStatus1 = (newStatus1 | Status::Not);

            if(newStatus1 != un->getStatus1() || newStatus2 != un->getStatus2()) {
                un->setStatus1(newStatus1);
                un->setStatus2(newStatus2);
                un->updDoubl();
                SignalSlotCommutator::getInstance()->emitUpdUN();
            }

        } else if(TypeUnitNode::SD_BL_IP == un->getType()) {
            if((quint8)item.data().at(5) & mask)
                newStatus1 = (newStatus1 | Status::Alarm);
            else
                newStatus1 = (newStatus1 | Status::Norm);

            if((quint8)item.data().at(7) & mask)
                newStatus2 = (newStatus2 | Status::Was);
            else
                newStatus2 = (newStatus2 | Status::Not);

            if(((quint8)item.data().at(8) & mask) == 0) {
                newStatus1 = Status::Uncnown;
                newStatus2 = Status::Off;
            }
        } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
            if((quint8)item.data().at(6) & mask)
                newStatus1 = (newStatus1 | Status::On);
            else
                newStatus1 = Status::Off;
        }

        if(0 != un->getDK() && DKCiclStatus::DKIgnore != un->getDkStatus() && DKCiclStatus::DKWrong != un->getDkStatus() && DKCiclStatus::DKDone != un->getDkStatus() && un->getDkInvolved()) {
//            qDebug() << "DkStatus --> " << un->getName();
            int unCalcDkStatus = calcDkStatus(un->getType(), un->getStatus1(), un->getStatus2());
//            qDebug() << "DkStatus -- unCalcDkStatus " << unCalcDkStatus;
//            qDebug() << "DkStatus -- unDkStatus " << un->getDkStatus();
            if(DKCiclStatus::DKReady == un->getDkStatus() &&
                    DKCiclStatus::DKNorm == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKNorm);
            else if((DKCiclStatus::DKNorm == un->getDkStatus() || DKCiclStatus::DKReady == un->getDkStatus())&&
                    DKCiclStatus::DKWasAlarn == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKWasAlarn);
            else if(DKCiclStatus::DKWasAlarn == un->getDkStatus() &&
                    DKCiclStatus::DKNorm == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKDone);
            else if(DKCiclStatus::DKWasAlarn == un->getDkStatus() &&
                    DKCiclStatus::DKWas == unCalcDkStatus)
                un->setDkStatus(DKCiclStatus::DKDone);
            else if((DKCiclStatus::DKNorm == un->getDkStatus() &&
                     DKCiclStatus::DKNorm == unCalcDkStatus) ||
                    (DKCiclStatus::DKWasAlarn == un->getDkStatus() &&
                     DKCiclStatus::DKWasAlarn == unCalcDkStatus))
                un->setDkStatus(un->getDkStatus());
            else
                un->setDkStatus(DKCiclStatus::DKWrong);
            un->updDoubl();
//            qDebug() << "DkStatus -- unNewDkStatus " << un->getDkStatus();
//            qDebug() << "DkStatus <--";
        }

        if(newStatus1 != un->getStatus1() || newStatus2 != un->getStatus2()) {
            quint8 oldStatus1 = un->getStatus1(), oldStatus2 = un->getStatus2();
            un->setStatus1(newStatus1);
            un->setStatus2(newStatus2);
            un->updDoubl();
            SignalSlotCommutator::getInstance()->emitUpdUN();

            if(!un->getDkInvolved()) {

                JourEntity msg;
                msg.setObject(un->getName());

                if((TypeUnitNode::SD_BL_IP == un->getType() &&
                    Status::Uncnown == oldStatus1 &&
                    Status::Off == oldStatus2 &&
                    Status::Uncnown != newStatus1 &&
                    Status::Uncnown != newStatus2 &&
                    un->getControl()) ||
                   (TypeUnitNode::IU_BL_IP == un->getType() &&
                    Status::Off == oldStatus1 &&
                    Status::Uncnown != newStatus1 &&
                    un->getControl())) {
                    JourEntity msgOn;
                    msgOn.setObject(un->getName());
                    msgOn.setComment(QObject::trUtf8("Вкл"));
                    DataBaseManager::insertJourMsg_wS(msgOn);
                  }

                if(un->getControl() && (TypeUnitNode::SD_BL_IP == un->getType()) && (un->getStatus1() & Status::Alarm) && (un->getStatus2() & Status::Was)) {
                    //сохранение Тревога или Норма
                    msg.setComment(QObject::trUtf8("Тревога-СРАБОТКА"));

                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                    //нужен сброс
                    resultRequest.setData(makeAlarmReset0x24());
                } else if(un->getControl() && (TypeUnitNode::SD_BL_IP == un->getType()) && (un->getStatus1() & Status::Norm)) {
                    msg.setComment(QObject::trUtf8("Норма"));

                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                } else if(un->getControl() && (TypeUnitNode::SD_BL_IP == un->getType()) && (un->getStatus2() & Status::Off)) {
                    msg.setComment(QObject::trUtf8("Выкл"));

                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                } else if(un->getControl() && (TypeUnitNode::IU_BL_IP == un->getType()) && (un->getStatus1() & Status::Off)) {
                    msg.setComment(QObject::trUtf8("Выкл"));

                    SignalSlotCommutator::getInstance()->emitInsNewJourMSG(DataBaseManager::insertJourMsg(msg));
                }
            }

            if(!un->getDkInvolved() && (TypeUnitNode::SD_BL_IP == un->getType()) && (un->getStatus1() & Status::Alarm) && (un->getStatus2() & Status::Was)) {
                //сохранение Тревога или Норма
                if(0 != un->treeChildCount()) {
                    for(UnitNode * iuun : un->treeChild()) {
                        if(TypeUnitNode::IU_BL_IP == iuun->getType()) {
                            qDebug() << "Utils::parcingStatusWord0x41 emitAutoOnOffIU";
                            SignalSlotCommutator::getInstance()->emitAutoOnOffIU(iuun);
                        }
                    }
                }

                //нужен сброс
            }
        }


    }
//    qDebug() << "Utils::parcingStatusWord0x41 <--";
    return resultRequest;
}

int Utils::calcDkStatus(int type, int status1, int status2)
{
    if(TypeUnitNode::GROUP == type) {
        return DKCiclStatus::DKIgnore;
    } else if(TypeUnitNode::SD_BL_IP == type) {
        if(Status::Was == status2 && Status::Alarm == status1) {
            return DKCiclStatus::DKWasAlarn;
        } else if(Status::Norm == status1 && Status::Was == status2) {
            return DKCiclStatus::DKWas;
//            return DKCiclStatus::DKWrong;
        } else if(Status::Alarm == status1) {
            return DKCiclStatus::DKWrong;
//            return DKCiclStatus::DKWasAlarn;
        } else if((Status::Off == status2) && (Status::Uncnown == status1)) {
            return DKCiclStatus::DKWrong;
        } else if(Status::Norm == status1) {
            return DKCiclStatus::DKNorm;
        }
        return DKCiclStatus::DKWrong;
    } else if(TypeUnitNode::IU_BL_IP == type) {
        return DKCiclStatus::DKIgnore;
    }
}

QColor Utils::cellRed = QColor(0xE3, 0x06, 0x13);
QColor Utils::cellGreen = QColor(0x00, 0x96, 0x40);
QColor Utils::cellGray = QColor(0xCF, 0xCF, 0xCF);

void Utils::fillDiagnosticTable(QTableWidget *table, UnitNode * selUN)
{
    try {
        if(nullptr == selUN || nullptr == table)
            return;

        UnitNode * parent = selUN->getParentUN();
        if((TypeUnitNode::SD_BL_IP == selUN->getType() ||
                TypeUnitNode::IU_BL_IP == selUN->getType()) &&
                nullptr != parent) {
            while(TypeUnitNode::BL_IP != parent->getType()) {
                parent = parent->getParentUN();
                if(nullptr == parent)
                    return;
            }
        } else {
            return;
        }

        table->setColumnWidth(0, 60);
        table->setColumnWidth(1, 150);
        table->setColumnWidth(3, 150);

        table->setItem(0,0, new QTableWidgetItem(QObject::trUtf8("Параметр"))); // ("Параметр"));
        table->setItem(0,1, new QTableWidgetItem(QObject::trUtf8("Вход"))); // ("Вход"));
        table->setItem(0,2, new QTableWidgetItem(QObject::trUtf8("Статус"))); // ("Статус"));

        table->setItem(1,0, new QTableWidgetItem(QObject::trUtf8("СД1"))); // ("СД1"));
        table->setItem(2,0, new QTableWidgetItem(QObject::trUtf8("СД2"))); // ("СД2"));
        table->setItem(3,0, new QTableWidgetItem(QObject::trUtf8("СД3"))); // ("СД3"));
        table->setItem(4,0, new QTableWidgetItem(QObject::trUtf8("СД4"))); // ("СД4"));
        table->setItem(5,0, new QTableWidgetItem(QObject::trUtf8("СД5"))); // ("СД5"));
        table->setItem(6,0, new QTableWidgetItem(QObject::trUtf8("СД6"))); // ("СД6"));
        table->setItem(7,0, new QTableWidgetItem(QObject::trUtf8("СД7"))); // ("СД7"));
        table->setItem(8,0, new QTableWidgetItem(QObject::trUtf8("СД8"))); // ("СД8"));

        table->setItem(9,0, new QTableWidgetItem(""));
        table->setItem(9,1, new QTableWidgetItem(QObject::trUtf8("Выход"))); // ("Выход"));
        table->setItem(9,2, new QTableWidgetItem(QObject::trUtf8("Статус"))); // ("Статус"));

        table->setItem(10,0, new QTableWidgetItem(QObject::trUtf8("ДК"))); // ("ДК"));
        table->setItem(11,0, new QTableWidgetItem(QObject::trUtf8("ИУ1"))); // ("ИУ1"));
        table->setItem(12,0, new QTableWidgetItem(QObject::trUtf8("ИУ2"))); // ("ИУ2"));
        table->setItem(13,0, new QTableWidgetItem(QObject::trUtf8("ИУ3"))); // ("ИУ3"));
        table->setItem(14,0, new QTableWidgetItem(QObject::trUtf8("ИУ4"))); // ("ИУ4"));

        table->setItem(1,1, new QTableWidgetItem("?"));
        table->setItem(1,2, new QTableWidgetItem("?"));
        table->setItem(2,1, new QTableWidgetItem("?"));
        table->setItem(2,2, new QTableWidgetItem("?"));
        table->setItem(3,1, new QTableWidgetItem("?"));
        table->setItem(3,2, new QTableWidgetItem("?"));
        table->setItem(4,1, new QTableWidgetItem("?"));
        table->setItem(4,2, new QTableWidgetItem("?"));
        table->setItem(5,1, new QTableWidgetItem("?"));
        table->setItem(5,2, new QTableWidgetItem("?"));
        table->setItem(6,1, new QTableWidgetItem("?"));
        table->setItem(6,2, new QTableWidgetItem("?"));
        table->setItem(7,1, new QTableWidgetItem("?"));
        table->setItem(7,2, new QTableWidgetItem("?"));
        table->setItem(8,1, new QTableWidgetItem("?"));
        table->setItem(8,2, new QTableWidgetItem("?"));

        table->setItem(10,1, new QTableWidgetItem("?"));
        table->setItem(10,2, new QTableWidgetItem("?"));

        table->setItem(11,1, new QTableWidgetItem("?"));
        table->setItem(11,2, new QTableWidgetItem(""));
        table->setItem(12,1, new QTableWidgetItem("?"));
        table->setItem(12,2, new QTableWidgetItem(""));
        table->setItem(13,1, new QTableWidgetItem("?"));
        table->setItem(13,2, new QTableWidgetItem(""));
        table->setItem(14,1, new QTableWidgetItem("?"));
        table->setItem(14,2, new QTableWidgetItem(""));

        for(int i = 0, n = 3; i < n; i++)
            for(int j = 0, m = 15; j < m; j++)
                table->item(j, i)->setBackground(cellGray);

        if(TypeUnitNode::BL_IP == parent->getType()) {
            int row = 10;

            quint8 status2 = parent->getStatus2();
            if(status2 & Status::Was) {
                table->setItem(row, 2, new QTableWidgetItem(QObject::trUtf8("Было"))); // "Тревога"
                table->item(row, 2)->setBackground(cellRed);
            } else if(status2 & Status::Not) {
                table->setItem(row, 2, new QTableWidgetItem(QObject::trUtf8("Нет"))); // "Норма"
                table->item(row, 2)->setBackground(cellGreen);
            }

            quint8 status1 = parent->getStatus1();
            if(status1 & Status::Exists) {
                table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Есть"))); // "Было"
                table->item(row, 1)->setBackground(cellRed);
            } else if(status1 & Status::Not) {
                table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Нет"))); // "Нет"
                table->item(row, 1)->setBackground(cellGreen);
            }
        }

        QList<UnitNode *> tmpLs = parent->getListChilde();
        for(UnitNode * un : tmpLs) {
            quint8 status1 = un->getStatus1();
            quint8 status2 = un->getStatus2();
            int row = -1;

            if(TypeUnitNode::SD_BL_IP == un->getType()) {
                row = un->getNum2();
                if(status1 & Status::Alarm) {
                    table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Тревога"))); // "Тревога"
                    table->item(row, 1)->setBackground(cellRed);
                }
                else if(status1 & Status::Norm) {
                    table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Норма"))); // "Норма"
                    table->item(row, 1)->setBackground(cellGreen);
                }

                if(status2 & Status::Was) {
                    table->setItem(row, 2, new QTableWidgetItem(QObject::trUtf8("Было"))); // "Было"
                    table->item(row, 2)->setBackground(cellRed);
                } else if(status2 & Status::Not) {
                    table->setItem(row, 2, new QTableWidgetItem(QObject::trUtf8("Нет"))); // "Нет"
                    table->item(row, 2)->setBackground(cellGreen);
                }

                if((status2 & Status::Off) && (Status::Uncnown == status1))
                {
                     table->setItem(row, 1, new QTableWidgetItem("-"));
                     table->item(row, 1)->setBackground(cellGray);
                     table->setItem(row, 2, new QTableWidgetItem(QObject::trUtf8("Выкл"))); // "Выкл"
                     table->item(row, 2)->setBackground(cellGray);
                }

            } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
                row = 10 + un->getNum2();
                if(status1 & Status::On) {
                    table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Вкл"))); // "Вкл"
                    table->item(row, 1)->setBackground(cellRed);
                    table->setItem(row, 2, new QTableWidgetItem(""));
                    table->item(row, 2)->setBackground(cellGray);
                } else if(status1 & Status::Off) {
                    table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Выкл"))); // "Выкл"
                    table->item(row, 1)->setBackground(cellGreen);
                    table->setItem(row, 2, new QTableWidgetItem(""));
                    table->item(row, 2)->setBackground(cellGray);
                }

            }
        }
    } catch (...) {
        qDebug() << "fillDiagnosticTable catch exception ...";
    }    
}

AbstractPort * Utils::portOfUN(UnitNode *un) {
    QPair<QString, QString> tmpPair(un->getUdpAdress(), QVariant(un->getUdpPort()).toString());
    PortManager::getUdpPortsVector();
}
