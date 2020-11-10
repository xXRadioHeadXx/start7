#include <Utils.h>
#include <SettingUtils.h>
#include <SignalSlotCommutator.h>
#include <global.hpp>

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
QColor Utils::cellYellow = QColor(0xFF, 0xDD, 0x0E);


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

            if((status1 & Status::NoConnection) && (status2 & Status::NoConnection)) {
                if(TypeUnitNode::SD_BL_IP == un->getType()) {
                    row = un->getNum2();
                } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
                    row = 10 + un->getNum2();
                }
                table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Нет связи"))); // "Норма"
                table->item(row, 1)->setBackground(cellYellow);
            } else if(TypeUnitNode::SD_BL_IP == un->getType()) {
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

QSet<UnitNode *> Utils::findeSetAutoOnOffUN(UnitNode *un)
{
    QSet<UnitNode *> unSetTmp;
    if(TypeUnitNode::IU_BL_IP != un->getType()) {
        return unSetTmp;
    }
    unSetTmp.insert(un);
    unSetTmp = unSetTmp + un->getDoubles();
    for(const auto& unDouble : as_const(unSetTmp.toList())) {
        qDebug() << "itr :" << unSetTmp;
        qDebug() << "fnd :" << unDouble << unDouble->getMetaNames() << unDouble->getName();
        if(nullptr != unDouble->getTreeParentUN()) {
            if(TypeUnitNode::SD_BL_IP == unDouble->getTreeParentUN()->getType()) {
                qDebug() << "trg :"<< unDouble->getMetaNames() << unDouble->getName();
            } else {
                unSetTmp.remove(unDouble);
            }
        } else {
            unSetTmp.remove(unDouble);
        }
    }
    qDebug() << "res :" << unSetTmp;
    return unSetTmp;
}


