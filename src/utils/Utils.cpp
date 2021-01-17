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
        sum += static_cast<quint8>(ba.at(bi));
    }

    return sum;
}

QString Utils::typeUNToStr(const int type)
{
    switch (type) {
    case 0:
        return QObject::tr("Группа"); //"Группа";
    case 11:
        return QObject::tr("СД"); //"СД БЛ-IP";
    case 12:
        return QObject::tr("ИУ"); //"ИУ БЛ-IP";
    case 10:
        return QObject::tr("Точка-Гарда"); //"Точка-Гарда";
    case 1:
        return QObject::tr("РИФ-РЛМ(КРЛ), Трасса"); //"РИФ-РЛМ(КРЛ), Трасса";
    case 111:
        return QObject::tr("РИФ-С"); //"РИФ-С";
    case 26:
        return QObject::tr("БОД Точка-М"); //"БОД Точка-М";
    case 27:
        return QObject::tr("Участок Точка-М"); //"Участок Точка-М";
    case 28:
        return QObject::tr("ДД Точка-М"); //"ДД Точка-М";
    case 29:
        return QObject::tr("БОД Сота-М"); //"БОД Сота-М";
    case 30:
        return QObject::tr("Участок Сота-М"); //"Участок Сота-М";
//    case 28:
//        return QObject::tr("ДД Сота-М"); //"ДД Сота-М";
    default:
        return QObject::tr("БЛ-IP");
    }
}

QString Utils::baMsgToStr(const QByteArray ba)
{
    if(5 <= ba.size()) {
        if(static_cast<quint8>(0xFF) != static_cast<quint8>(ba.at(1)) &&
           static_cast<quint8>(0x00) == static_cast<quint8>(ba.at(3)) &&
           static_cast<quint8>(0x30) == static_cast<quint8>(ba.at(4)))
            return  QObject::tr("Подтверждение приема концентратором"); //"Подтверждение приема концентратором";
        else if(static_cast<quint8>(0xFF) != static_cast<quint8>(ba.at(1)) &&
                static_cast<quint8>(0x04) == static_cast<quint8>(ba.at(3)) &&
                static_cast<quint8>(0x41) == static_cast<quint8>(ba.at(4)))
            return  QObject::tr("Передача слов состояния концентратора"); //"Передача слов состояния концентратора";
    } else if(4 <= ba.size()) {
        if(static_cast<quint8>(0xFF) == static_cast<quint8>(ba.at(1)) &&
           static_cast<quint8>(0x00) == static_cast<quint8>(ba.at(2)) &&
           static_cast<quint8>(0x22) == static_cast<quint8>(ba.at(3)))
            return QObject::tr("Запрос состояния концентратора"); //"Запрос состояния концентратора";
        else if(static_cast<quint8>(0xFF) == static_cast<quint8>(ba.at(1)) &&
                static_cast<quint8>(0x00) == static_cast<quint8>(ba.at(2)) &&
                static_cast<quint8>(0x24) == static_cast<quint8>(ba.at(3)))
            return QObject::tr("Сброс флагов тревоги, ДК"); //"Сброс флагов тревоги, ДК";
        else if(static_cast<quint8>(0xFF) == static_cast<quint8>(ba.at(1)) &&
                static_cast<quint8>(0x01) == static_cast<quint8>(ba.at(2)) &&
                static_cast<quint8>(0x23) == static_cast<quint8>(ba.at(3)))
            return  QObject::tr("Управление ИУ"); //"Управление ИУ";
    } else if(1 == ba.size()) {
        if(static_cast<quint8>(0xFF) == static_cast<quint8>(ba.at(0)))
            return  QObject::tr("Включение"); //"Включение";
        else if(static_cast<quint8>(0x00) == static_cast<quint8>(ba.at(0)))
            return  QObject::tr("Выключение"); //"Выключение";
    }

    return ba.toHex();
}

bool Utils::isSavedMsg(const QByteArray ba) {

    if(5 <= ba.size()) {
        if(static_cast<quint8>(0xFF) != static_cast<quint8>(ba.at(1)) &&
           static_cast<quint8>(0x00) == static_cast<quint8>(ba.at(3)) &&
           static_cast<quint8>(0x30) == static_cast<quint8>(ba.at(4)))
            return true; //"Подтверждение приема концентратором";
        else if(static_cast<quint8>(0xFF) != static_cast<quint8>(ba.at(1)) &&
                static_cast<quint8>(0x04) == static_cast<quint8>(ba.at(3)) &&
                static_cast<quint8>(0x41) == static_cast<quint8>(ba.at(4)))
            return false; //"Передача слов состояния концентратора";
    } else if(4 <= ba.size()) {
        if(static_cast<quint8>(0xFF) == static_cast<quint8>(ba.at(1)) &&
           static_cast<quint8>(0x00) == static_cast<quint8>(ba.at(2)) &&
           static_cast<quint8>(0x22) == static_cast<quint8>(ba.at(3)))
            return false; //"Запрос состояния концентратора";
        else if(static_cast<quint8>(0xFF) == static_cast<quint8>(ba.at(1)) &&
                static_cast<quint8>(0x00) == static_cast<quint8>(ba.at(2)) &&
                static_cast<quint8>(0x24) == static_cast<quint8>(ba.at(3)))
            return true; //"Сброс флагов тревоги, ДК";
        else if(static_cast<quint8>(0xFF) == static_cast<quint8>(ba.at(1)) &&
                static_cast<quint8>(0x01) == static_cast<quint8>(ba.at(2)) &&
                static_cast<quint8>(0x23) == static_cast<quint8>(ba.at(3)))
            return true; //"Управление ИУ";
    } else if(1 == ba.size()) {
        if(static_cast<quint8>(0xFF) == static_cast<quint8>(ba.at(0)))
            return true; //"Включение";
        else if(static_cast<quint8>(0x00) == static_cast<quint8>(ba.at(0)))
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

QColor Utils::cellRed = QColor(0xE3, 0x06, 0x13);
QColor Utils::cellGreen = QColor(0x00, 0x96, 0x40);
QColor Utils::cellGray = QColor(0xCF, 0xCF, 0xCF);
QColor Utils::cellYellow = QColor(0xFF, 0xDD, 0x0E);


void Utils::fillDiagnosticTable(QTableWidget *table, UnitNode * selUN)
{
    try {
        if(nullptr == selUN || nullptr == table)
            return;

        table->clear();
        if(TypeUnitNode::RLM_KRL == selUN->getType())
            Utils::fillDiagnosticTableRLMKRL(table, selUN);
        else if(TypeUnitNode::RLM_C == selUN->getType())
            Utils::fillDiagnosticTableRLM_C(table, selUN);
        else if(TypeUnitNode::TG == selUN->getType())
            Utils::fillDiagnosticTableTG(table, selUN);
        else if(TypeUnitNode::DD_T4K_M == selUN->getType())
            Utils::fillDiagnosticTableDD_T4K_M(table, selUN);
        else if(TypeUnitNode::DD_SOTA == selUN->getType())
            Utils::fillDiagnosticTableDD_SOTA(table, selUN);
        else if(TypeUnitNode::Y4_SOTA == selUN->getType() || TypeUnitNode::BOD_SOTA == selUN->getType())
            Utils::fillDiagnosticTableY4_SOTA(table, selUN);
        else if(TypeUnitNode::BOD_T4K_M == selUN->getType() || TypeUnitNode::Y4_T4K_M == selUN->getType())
            Utils::fillDiagnosticTableY4_T4K_M(table, selUN);
        else if(TypeUnitNode::SD_BL_IP == selUN->getType() || TypeUnitNode::IU_BL_IP == selUN->getType())
            Utils::fillDiagnosticTableBLIP(table, selUN);

        table->resizeColumnsToContents();
        table->resizeRowsToContents();
    } catch (...) {
        qDebug() << "fillDiagnosticTable catch exception ...";
    }
}

void Utils::fillDiagnosticTableBLIP(QTableWidget *table, UnitNode * selUN) {
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

    table->setRowCount(15);
    table->setColumnCount(3);

    table->setColumnWidth(0, 60);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::tr("Параметр"))); // ("Параметр"));
    table->setItem(0,1, new QTableWidgetItem(QObject::tr("Вход"))); // ("Вход"));
    table->setItem(0,2, new QTableWidgetItem(QObject::tr("Статус"))); // ("Статус"));

    table->setItem(1,0, new QTableWidgetItem(QObject::tr("СД1"))); // ("СД1"));
    table->setItem(2,0, new QTableWidgetItem(QObject::tr("СД2"))); // ("СД2"));
    table->setItem(3,0, new QTableWidgetItem(QObject::tr("СД3"))); // ("СД3"));
    table->setItem(4,0, new QTableWidgetItem(QObject::tr("СД4"))); // ("СД4"));
    table->setItem(5,0, new QTableWidgetItem(QObject::tr("СД5"))); // ("СД5"));
    table->setItem(6,0, new QTableWidgetItem(QObject::tr("СД6"))); // ("СД6"));
    table->setItem(7,0, new QTableWidgetItem(QObject::tr("СД7"))); // ("СД7"));
    table->setItem(8,0, new QTableWidgetItem(QObject::tr("СД8"))); // ("СД8"));

    table->setItem(9,0, new QTableWidgetItem(""));
    table->setItem(9,1, new QTableWidgetItem(QObject::tr("Выход"))); // ("Выход"));
    table->setItem(9,2, new QTableWidgetItem(QObject::tr("Статус"))); // ("Статус"));

    table->setItem(10,0, new QTableWidgetItem(QObject::tr("ДК"))); // ("ДК"));
    table->setItem(11,0, new QTableWidgetItem(QObject::tr("ИУ1"))); // ("ИУ1"));
    table->setItem(12,0, new QTableWidgetItem(QObject::tr("ИУ2"))); // ("ИУ2"));
    table->setItem(13,0, new QTableWidgetItem(QObject::tr("ИУ3"))); // ("ИУ3"));
    table->setItem(14,0, new QTableWidgetItem(QObject::tr("ИУ4"))); // ("ИУ4"));

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

        if(1 == parent->isWasDK()) {
            table->setItem(row, 2, new QTableWidgetItem(QObject::tr("Было"))); // "Тревога"
            table->item(row, 2)->setBackground(cellRed);
        } else {//if(status2 & Status::Not) {
            table->setItem(row, 2, new QTableWidgetItem(QObject::tr("Нет"))); // "Норма"
            table->item(row, 2)->setBackground(cellGreen);
        }

        if(1 == parent->isExistDK()) {
            table->setItem(row, 1, new QTableWidgetItem(QObject::tr("Есть"))); // "Было"
            table->item(row, 1)->setBackground(cellRed);
        } else if(0 == parent->isExistDK()) {
            table->setItem(row, 1, new QTableWidgetItem(QObject::tr("Нет"))); // "Нет"
            table->item(row, 1)->setBackground(cellGreen);
        }
    }

    QList<UnitNode *> tmpLs = parent->getListChilde();
    for(UnitNode * un : tmpLs) {
        if(TypeUnitNode::SD_BL_IP != un->getType() && TypeUnitNode::IU_BL_IP != un->getType()) {
            continue;
        }

        int row = -1;

        if(un->getStateWord().isEmpty()) {
            if(TypeUnitNode::SD_BL_IP == un->getType()) {
                row = un->getNum2();
            } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
                row = 10 + un->getNum2();
            }
            table->setItem(row, 1, new QTableWidgetItem(QObject::tr("Нет связи"))); // "Норма"
            table->item(row, 1)->setBackground(cellYellow);
        } else if(TypeUnitNode::SD_BL_IP == un->getType()) {
            row = un->getNum2();
            if(1 == un->isAlarm()) {
                table->setItem(row, 1, new QTableWidgetItem(QObject::tr("Тревога"))); // "Тревога"
                table->item(row, 1)->setBackground(cellRed);
            }
            else if(1 == un->isNorm()) {
                table->setItem(row, 1, new QTableWidgetItem(QObject::tr("Норма"))); // "Норма"
                table->item(row, 1)->setBackground(cellGreen);
            }

            if(1 == un->isWasAlarm()) {
                table->setItem(row, 2, new QTableWidgetItem(QObject::tr("Было"))); // "Было"
                table->item(row, 2)->setBackground(cellRed);
            } else if(0 == un->isWasAlarm()) {
                table->setItem(row, 2, new QTableWidgetItem(QObject::tr("Нет"))); // "Нет"
                table->item(row, 2)->setBackground(cellGreen);
            }

            if(1 == un->isOff())
            {
                 table->setItem(row, 1, new QTableWidgetItem("-"));
                 table->item(row, 1)->setBackground(cellGray);
                 table->setItem(row, 2, new QTableWidgetItem(QObject::tr("Выкл"))); // "Выкл"
                 table->item(row, 2)->setBackground(cellGray);
            }

        } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
            row = 10 + un->getNum2();
            if(1 == un->isOn()) {
                table->setItem(row, 1, new QTableWidgetItem(QObject::tr("Вкл"))); // "Вкл"
                table->item(row, 1)->setBackground(cellRed);
                table->setItem(row, 2, new QTableWidgetItem(""));
                table->item(row, 2)->setBackground(cellGray);
            } else if(1 == un->isOff()) {
                table->setItem(row, 1, new QTableWidgetItem(QObject::tr("Выкл"))); // "Выкл"
                table->item(row, 1)->setBackground(cellGreen);
                table->setItem(row, 2, new QTableWidgetItem(""));
                table->item(row, 2)->setBackground(cellGray);
            }

        }
    }
}

void Utils::fillDiagnosticTableRLMKRL(QTableWidget *table, UnitNode */*selUN*/)
{
    table->setRowCount(7);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::tr("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,3, new QTableWidgetItem(QObject::tr("Значение")));

    table->setItem(1,0, new QTableWidgetItem(QObject::tr("Состояние")));
    table->setItem(2,0, new QTableWidgetItem(QObject::tr("Тревога")));
    table->setItem(3,0, new QTableWidgetItem(QObject::tr("Сработка")));
    auto itm = new QTableWidgetItem(QObject::tr("Вскрытие"));
    itm->setBackground(cellGray);
    table->setItem(4,0, itm);
//    table->setItem(4,0, new QTableWidgetItem(QObject::tr("Вскрытие")));
    itm = new QTableWidgetItem(QObject::tr("ДК"));
    itm->setBackground(cellGray);
    table->setItem(5,0, itm);
//    table->setItem(5,0, new QTableWidgetItem(QObject::tr("ДК")));
    itm = new QTableWidgetItem(QObject::tr("Уровень"));
    itm->setBackground(cellGray);
    table->setItem(6,0, itm);
//    table->setItem(6,0, new QTableWidgetItem(QObject::tr("Уровень")));

    for(int i = 0, n = 7; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            QTableWidgetItem * item = nullptr;
            if(2 == i && 2 == j)
                item = new QTableWidgetItem(QObject::tr("Вход \"Тревога\""));
            else if(4 == i && 2 == j)
                item = new QTableWidgetItem(QObject::tr("Вход \"Вскрытие\""));
            else if(5 == i && 2 == j)
                item = new QTableWidgetItem(QObject::tr("Вход \"ДК\""));
            else if(0 != i && 2 == j)
                item = new QTableWidgetItem("");
            else if(0 != i && 0 != j)
                item = new QTableWidgetItem("?");
//            else
//                item = table->item(i, j);

            if(nullptr != item) {
                table->setItem(i, j, item);
            } else {
                item = table->item(i, j);
            }
            if(nullptr != item)
                item->setBackground(cellGray);
        }
    }

}

void Utils::fillDiagnosticTableRLM_C(QTableWidget *table, UnitNode *un)
{
    table->setRowCount(11);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::tr("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,3, new QTableWidgetItem(QObject::tr("Значение")));

    table->setItem(1,0, new QTableWidgetItem(QObject::tr("Состояние")));
    table->setItem(2,0, new QTableWidgetItem(QObject::tr("Тревога")));
    table->setItem(3,0, new QTableWidgetItem(QObject::tr("Сработка")));
    table->setItem(4,0, new QTableWidgetItem(QObject::tr("ДК")));
    table->setItem(5,0, new QTableWidgetItem(QObject::tr("Синхронизация")));
    table->setItem(6,0, new QTableWidgetItem(QObject::tr("Низкий ровень")));
    table->setItem(7,0, new QTableWidgetItem(QObject::tr("Уровень")));
    table->setItem(8,0, new QTableWidgetItem(QObject::tr("Пороги")));
    table->setItem(9,0, new QTableWidgetItem(QObject::tr("Период тактирования")));
    table->setItem(10,0, new QTableWidgetItem(QObject::tr("Режим обработки")));

    for(int i = 0, n = 11; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            QTableWidgetItem * item = nullptr;
            if(2 == i && 2 == j)
                item = new QTableWidgetItem(QObject::tr("Вход \"Тревога\""));
            else if(4 == i && 2 == j)
                item = new QTableWidgetItem(QObject::tr("Вход \"ДК\""));
            else if(0 != i && 2 == j)
                item = new QTableWidgetItem("");
            else if(0 != i && 0 != j)
                item = new QTableWidgetItem("?");
//            else
//                item = table->item(i, j);

            if(nullptr != item) {
                table->setItem(i, j, item);
            } else {
                item = table->item(i, j);
            }
            if(nullptr != item)
                item->setBackground(cellGray);
        }
    }

    if(1 == un->isOn()) {
        table->setItem(1,1, new QTableWidgetItem(QObject::tr("Вкл[1]")));
        table->item(1,1)->setBackground(cellGray);
    } else if(1 == un->isOff()) {
        table->setItem(1,1, new QTableWidgetItem(QObject::tr("Выкл[0]")));
        table->item(1,1)->setBackground(cellGray);
    }

    if(1 == un->isInAlarm()) {
        table->setItem(2,1, new QTableWidgetItem(QObject::tr("Да[1]")));
        table->item(2,1)->setBackground(cellRed);
    } else if(0 == un->isInAlarm()) {
        table->setItem(2,1, new QTableWidgetItem(QObject::tr("Нет[0]")));
        table->item(2,1)->setBackground(cellGreen);
    }

    if(1 == un->isOutAlarm()) {
        table->setItem(2,3, new QTableWidgetItem(QObject::tr("Да[1]")));
        table->item(2,3)->setBackground(cellRed);
    } else if(0 == un->isOutAlarm()) {
        table->setItem(2,3, new QTableWidgetItem(QObject::tr("Нет[0]")));
        table->item(2,3)->setBackground(cellGreen);
    }

    if(1 == un->isWasAlarm()) {
        table->setItem(3,1, new QTableWidgetItem(QObject::tr("Да[1]")));
        table->item(3,1)->setBackground(cellRed);
    } else if(0 == un->isWasAlarm()) {
        table->setItem(3,1, new QTableWidgetItem(QObject::tr("Нет[0]")));
        table->item(3,1)->setBackground(cellGreen);
    }

    if(1 == un->isExistDK()) {
        table->setItem(4,1, new QTableWidgetItem(QObject::tr("Есть[1]")));
        table->item(4,1)->setBackground(cellYellow);
    } else if(0 == un->isExistDK()) {
        table->setItem(4,1, new QTableWidgetItem(QObject::tr("Нет[0]")));
        table->item(4,1)->setBackground(cellGreen);
    }

    if(1 == un->isWasDK()) {
        table->setItem(4,3, new QTableWidgetItem(QObject::tr("Есть[1]")));
        table->item(4,3)->setBackground(cellYellow);
    } else if(0 == un->isWasDK()) {
        table->setItem(4,3, new QTableWidgetItem(QObject::tr("Нет[0]")));
        table->item(4,3)->setBackground(cellGreen);
    }

    if(1 == un->isExternalSynchronization()) {
        table->setItem(5,1, new QTableWidgetItem(QObject::tr("Внешняя")));
        table->item(5,1)->setBackground(cellGray);
    } else if(0 == un->isExternalSynchronization()) {
        table->setItem(5,1, new QTableWidgetItem(QObject::tr("Внутренняя")));
        table->item(5,1)->setBackground(cellGray);
    }

    if(1 == un->lowLevl()) {
        table->setItem(6,1, new QTableWidgetItem(QObject::tr("Да<1>")));
        table->item(6,1)->setBackground(cellRed);
    } else if(0 == un->lowLevl()) {
        table->setItem(6,1, new QTableWidgetItem(QObject::tr("Нет[0]")));
        table->item(6,1)->setBackground(cellGreen);
    }

    if(-1.0 != un->voltage()) {
        table->setItem(7,1, new QTableWidgetItem(QString::number(un->voltage(), 'f', 2)));
        table->item(7,1)->setBackground(cellGray);
    }

    if(-1.0 != un->threshold()) {
        table->setItem(8,1, new QTableWidgetItem(QString::number(un->threshold(), 'f', 2)));
        table->item(8,1)->setBackground(cellGray);
    }

    if(-1 != un->clockPeriod()) {
        table->setItem(9,1, new QTableWidgetItem(QObject::tr("Такт ") + QString::number(un->clockPeriod() + 1)));
        table->item(9,1)->setBackground(cellGray);
    }

    if(-1 != un->modeProcessing()) {
        QString str;
        switch (un->modeProcessing()) {
        case 0: str = QObject::tr("Основной"); break;
        case 1: str = QObject::tr("Дополнительный"); break;
        case 2: str = QObject::tr("Ползущий (Плз)"); break;
        case 3: str = QObject::tr("2-й ярус (2Яр)"); break;
        }
        table->setItem(10,1, new QTableWidgetItem(str));
        table->item(10,1)->setBackground(cellGray);
    }

}

void Utils::fillDiagnosticTableTG(QTableWidget *table, UnitNode */*selUN*/)
{
    table->setRowCount(15);
    table->setColumnCount(6);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);
    table->setColumnWidth(4, 150);
    table->setColumnWidth(5, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::tr("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,3, new QTableWidgetItem(QObject::tr("Значение")));
    table->setItem(0,4, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,5, new QTableWidgetItem(QObject::tr("Значение")));

    for(int i = 1, n = 5; i < n; i++) {
        table->setItem(i,0, new QTableWidgetItem(QObject::tr("Сработка ЧЭ%1").arg(i)));
        table->setItem(i,2, new QTableWidgetItem(QObject::tr("Выход \"Тревога ЧЭ%1\"").arg(i)));
        table->setItem(i,4, new QTableWidgetItem(QObject::tr("Сработка со стороны ЧЭ%1").arg(i)));
    }

    table->setItem(5,0, new QTableWidgetItem(QObject::tr("ДК")));
    table->setItem(5,2, new QTableWidgetItem(QObject::tr("Выход \"ДК\"")));
    table->setItem(6,0, new QTableWidgetItem(QObject::tr("Вскрытие")));
    table->setItem(6,2, new QTableWidgetItem(QObject::tr("Выход \"Вскрытие\"")));

    table->setItem(7,0, new QTableWidgetItem(QObject::tr("ЧЭ1")));

    for(int i = 0, n = 3; i < n; i++) {
        table->setItem(i + 8,0, new QTableWidgetItem(QObject::tr("Фильтр%1: Сработка").arg(1 + i)));
        table->setItem(i + 8,2, new QTableWidgetItem(QObject::tr("Уровень")));
        table->setItem(i + 8,4, new QTableWidgetItem(QObject::tr("Порог")));
    }

    table->setItem(11,0, new QTableWidgetItem(QObject::tr("ЧЭ2")));

    for(int i = 0, n = 3; i < n; i++) {
        table->setItem(i + 12,0, new QTableWidgetItem(QObject::tr("Фильтр%1: Сработка").arg(1 + i)));
        table->setItem(i + 12,2, new QTableWidgetItem(QObject::tr("Уровень")));
        table->setItem(i + 12,4, new QTableWidgetItem(QObject::tr("Порог")));
    }

    table->setItem(7,2, new QTableWidgetItem(""));
    table->setItem(11,2, new QTableWidgetItem(""));
    table->setItem(5,4, new QTableWidgetItem(""));
    table->setItem(6,4, new QTableWidgetItem(""));
    table->setItem(7,4, new QTableWidgetItem(""));
    table->setItem(11,4, new QTableWidgetItem(""));


    for(int i = 0, n = 15; i < n; i++) {
        for(int j = 0, m = 6; j < m; j++) {
            QTableWidgetItem * item = nullptr;
            if(0 != i && 0 != j && 2 != j && 4 != j)
                item = new QTableWidgetItem("?");
//            else
//                item = table->item(i, j);

            if(nullptr != item) {
                table->setItem(i, j, item);
            } else {
                item = table->item(i, j);
            }
            if(nullptr != item)
                item->setBackground(cellGray);
        }
    }
}

void Utils::fillDiagnosticTableDD_T4K_M(QTableWidget *table, UnitNode */*selUN*/)
{
    table->setRowCount(14);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::tr("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,3, new QTableWidgetItem(QObject::tr("Значение")));

    table->setItem(1,0, new QTableWidgetItem(QObject::tr("Готовность БОД")));


    for(int i = 0, n = 5; i < n; i++) {
        table->setItem(2 + i,0, new QTableWidgetItem(QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        table->setItem(6 + i,0, new QTableWidgetItem(QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    table->setItem(10,0, new QTableWidgetItem(QObject::tr("Выход \"ДК\"")));
    table->setItem(11,0, new QTableWidgetItem(QObject::tr("Состояние \"ДК\" было")));
    table->setItem(12,0, new QTableWidgetItem(QObject::tr("Выход \"Вскрытие БО\"")));
    table->setItem(13,0, new QTableWidgetItem(QObject::tr("Вскрытие БО было")));

    table->setItem(1,2, new QTableWidgetItem(QObject::tr("Сработка по ЧЭ1 было")));
    table->setItem(2,2, new QTableWidgetItem(QObject::tr("Сработка по ЧЭ2 было")));
    table->setItem(3,2, new QTableWidgetItem(QObject::tr("Обрыв по ЧЭ1 есть")));
    table->setItem(4,2, new QTableWidgetItem(QObject::tr("Замыкание по ЧЭ1 есть")));
    table->setItem(5,2, new QTableWidgetItem(QObject::tr("Обрыв по ЧЭ2 есть")));
    table->setItem(6,2, new QTableWidgetItem(QObject::tr("Замыкание по ЧЭ2 есть")));
    table->setItem(7,2, new QTableWidgetItem(QObject::tr("Неисправность ДД")));
    table->setItem(8,2, new QTableWidgetItem(QObject::tr("Обрыв связи с ДД есть")));
    table->setItem(9,2, new QTableWidgetItem(QObject::tr("Обрыв связи с ДД был")));
    table->setItem(10,2, new QTableWidgetItem(QObject::tr("Вскрытие ДД есть")));
    table->setItem(11,2, new QTableWidgetItem(QObject::tr("Вскрытие ДД был")));
    table->setItem(12,2, new QTableWidgetItem(QObject::tr("Уровень Сигнала ЧЭ1")));
    table->setItem(13,2, new QTableWidgetItem(QObject::tr("Уровень Сигнала ЧЭ2")));

    for(int i = 0, n = 14; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            QTableWidgetItem * item = nullptr;
            if(0 != i && 0 != j && 2 != j)
                item = new QTableWidgetItem("?");
//            else
//                item = table->item(i, j);

            if(nullptr != item) {
                table->setItem(i, j, item);
            } else {
                item = table->item(i, j);
            }
            if(nullptr != item)
                item->setBackground(cellGray);
        }
    }
}

void Utils::fillDiagnosticTableDD_SOTA(QTableWidget *table, UnitNode */*selUN*/)
{
    table->setRowCount(14);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::tr("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,3, new QTableWidgetItem(QObject::tr("Значение")));

    table->setItem(1,0, new QTableWidgetItem(QObject::tr("Готовность БОД")));


    for(int i = 0, n = 5; i < n; i++) {
        table->setItem(2 + i,0, new QTableWidgetItem(QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        table->setItem(6 + i,0, new QTableWidgetItem(QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    table->setItem(10,0, new QTableWidgetItem(QObject::tr("Выход \"ДК\"")));
    table->setItem(11,0, new QTableWidgetItem(QObject::tr("Состояние \"ДК\" было")));
    table->setItem(12,0, new QTableWidgetItem(QObject::tr("Выход \"Вскрытие БО\"")));
    table->setItem(13,0, new QTableWidgetItem(QObject::tr("Вскрытие БО было")));

    table->setItem(1,2, new QTableWidgetItem(QObject::tr("Сработка было")));
    table->setItem(2,2, new QTableWidgetItem(QObject::tr("Обрыв связи с ДД есть")));
    table->setItem(3,2, new QTableWidgetItem(QObject::tr("Обрыв связи с ДД был")));
    table->setItem(4,2, new QTableWidgetItem(QObject::tr("Вскрытие ДД есть")));
    table->setItem(5,2, new QTableWidgetItem(QObject::tr("Неисправность ДД есть")));
    table->setItem(6,2, new QTableWidgetItem(QObject::tr("Тревога по Ф1 есть")));
    table->setItem(7,2, new QTableWidgetItem(QObject::tr("Тревога поФ2 есть")));
    table->setItem(8,2, new QTableWidgetItem(QObject::tr("Опрос ДД")));
    table->setItem(9,2, new QTableWidgetItem(QObject::tr("Уровень Сигнала")));
    for(int i = 0, n = 5; i < n; i++) {
        table->setItem(10 + i,2, new QTableWidgetItem(QObject::tr("")));
    }

    for(int i = 0, n = 14; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            QTableWidgetItem * item = nullptr;
            if(0 != i && 0 != j && 2 != j)
                item = new QTableWidgetItem("?");
//            else
//                item = table->item(i, j);

            if(nullptr != item) {
                table->setItem(i, j, item);
            } else {
                item = table->item(i, j);
            }
            if(nullptr != item)
                item->setBackground(cellGray);
        }
    }
}

void Utils::fillDiagnosticTableY4_SOTA(QTableWidget *table, UnitNode */*selUN*/)
{
    table->setRowCount(20);
    table->setColumnCount(53);

    table->setColumnWidth(0, 150);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::tr("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::tr("Параметр")));

    table->setItem(1,0, new QTableWidgetItem(QObject::tr("Готовность БОД")));


    for(int i = 0, n = 4; i < n; i++) {
        table->setItem(2 + i,0, new QTableWidgetItem(QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        table->setItem(6 + i,0, new QTableWidgetItem(QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    table->setItem(10,0, new QTableWidgetItem(QObject::tr("Выход \"ДК\"")));
    table->setItem(11,0, new QTableWidgetItem(QObject::tr("Состояние \"ДК\" было")));
    table->setItem(12,0, new QTableWidgetItem(QObject::tr("Выход \"Вскрытие БО\"")));
    table->setItem(13,0, new QTableWidgetItem(QObject::tr("Вскрытие БО было")));

    table->setItem(1,2, new QTableWidgetItem(QObject::tr("Участки 1-2")));
    table->setItem(11,2, new QTableWidgetItem(QObject::tr("Участки 3-4")));

    int dec[] = {2,6,12,16};
    for(int i = 0, n = 4; i < n; i++) {
        table->setItem(dec[i] + 0,2, new QTableWidgetItem(QObject::tr("ДД")));
        table->setItem(dec[i] + 1,2, new QTableWidgetItem(QObject::tr("Сработка ДД было")));
        table->setItem(dec[i] + 2,2, new QTableWidgetItem(QObject::tr("Обрыв связи с ДД есть")));
        table->setItem(dec[i] + 3,2, new QTableWidgetItem(QObject::tr("Обрыв связи с ДД был")));
    }

    for(int i = 0, n = 50; i < n; i++) {
        table->setItem(dec[0],3 + i, new QTableWidgetItem(QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
        table->setItem(dec[1],3 + i, new QTableWidgetItem(QString("%1").arg(i + 1 + 50, 2, 10, QLatin1Char('0'))));
        table->setItem(dec[2],3 + i, new QTableWidgetItem(QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
        table->setItem(dec[3],3 + i, new QTableWidgetItem(QString("%1").arg(i + 1 + 50, 2, 10, QLatin1Char('0'))));
    }

    for(int i = 0, n = 20; i < n; i++) {
        for(int j = 0, m = 53; j < m; j++) {
            QTableWidgetItem * item = table->item(i, j);
            if(nullptr == item) {
                item = new QTableWidgetItem("");
                table->setItem(i, j, item);
            }
            if(nullptr != item)
                item->setBackground(cellGray);
        }
    }
}

void Utils::fillDiagnosticTableY4_T4K_M(QTableWidget *table, UnitNode */*selUN*/)
{
    table->setRowCount(22);
    table->setColumnCount(29);

    table->setColumnWidth(0, 150);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::tr("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::tr("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::tr("Параметр")));

    table->setItem(1,0, new QTableWidgetItem(QObject::tr("Готовность БОД")));


    for(int i = 0, n = 4; i < n; i++) {
        table->setItem(2 + i,0, new QTableWidgetItem(QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        table->setItem(6 + i,0, new QTableWidgetItem(QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    table->setItem(10,0, new QTableWidgetItem(QObject::tr("Выход \"ДК\"")));
    table->setItem(11,0, new QTableWidgetItem(QObject::tr("Состояние \"ДК\" было")));
    table->setItem(12,0, new QTableWidgetItem(QObject::tr("Выход \"Вскрытие БО\"")));
    table->setItem(13,0, new QTableWidgetItem(QObject::tr("Вскрытие БО было")));

    table->setItem(1,2, new QTableWidgetItem(QObject::tr("Участки 1-2")));
    table->setItem(12,2, new QTableWidgetItem(QObject::tr("Участки 3-4")));

    int dec[] = {2,13};
    for(int i = 0, n = 2; i < n; i++) {
        table->setItem(dec[i] + 0,2, new QTableWidgetItem(QObject::tr("ДДискретный")));
        table->setItem(dec[i] + 1,2, new QTableWidgetItem(QObject::tr("Сработка по ЧЭ1 было")));
        table->setItem(dec[i] + 2,2, new QTableWidgetItem(QObject::tr("Сработка по ЧЭ2 было")));
        table->setItem(dec[i] + 3,2, new QTableWidgetItem(QObject::tr("Неисправность по ЧЭ1 есть")));
        table->setItem(dec[i] + 4,2, new QTableWidgetItem(QObject::tr("Неисправность по ЧЭ2 есть")));
        table->setItem(dec[i] + 5,2, new QTableWidgetItem(QObject::tr("Обрыв связи с ДД есть")));
        table->setItem(dec[i] + 6,2, new QTableWidgetItem(QObject::tr("Обрыв связи с ДД был")));
        table->setItem(dec[i] + 7,2, new QTableWidgetItem(QObject::tr("Вскрытие ДД есть")));
        table->setItem(dec[i] + 8,2, new QTableWidgetItem(QObject::tr("Вскрытие ДД было")));
    }

    for(int i = 0, n = 26; i < n; i++) {
        table->setItem(dec[0],3 + i, new QTableWidgetItem(QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
        table->setItem(dec[1],3 + i, new QTableWidgetItem(QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
    }

    for(int i = 0, n = 22; i < n; i++) {
        for(int j = 0, m = 29; j < m; j++) {
            QTableWidgetItem * item = table->item(i, j);
            if(nullptr == item) {
                item = new QTableWidgetItem("");
                table->setItem(i, j, item);
            }
            if(nullptr != item)
                item->setBackground(cellGray);
        }
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
    for(const auto& unDouble : as_const(unSetTmp.values())) {
//        qDebug() << "itr :" << unSetTmp;
//        qDebug() << "fnd :" << unDouble << unDouble->getMetaNames() << unDouble->getName();
        if(nullptr != unDouble->getTreeParentUN()) {
            if(TypeUnitNode::SD_BL_IP == unDouble->getTreeParentUN()->getType()) {
//                qDebug() << "trg :"<< unDouble->getMetaNames() << unDouble->toString();
            } else {
                unSetTmp.remove(unDouble);
            }
        } else {
            unSetTmp.remove(unDouble);
        }
    }
//    qDebug() << "res :" << unSetTmp;
    return unSetTmp;
}


