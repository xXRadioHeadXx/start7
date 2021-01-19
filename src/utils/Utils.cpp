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

void Utils::setCellText(QTableWidget * const table, const int row, const int column, const QString text)
{
    if(row >= table->rowCount() || column >= table->colorCount())
        return;
    QTableWidgetItem * item = table->item(row, column);
    if(nullptr == item) {
        item = new QTableWidgetItem();
        table->setItem(row, column, item);
    }
    item->setText(text);
}

void Utils::setCellColor(QTableWidget * const table, const int row, const int column, const QColor color)
{
    if(row >= table->rowCount() || column >= table->colorCount())
        return;
    QTableWidgetItem * item = table->item(row, column);
    if(nullptr == item) {
        item = new QTableWidgetItem();
        table->setItem(row, column, item);
    }
    item->setBackground(QBrush(color));

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


void Utils::fillDiagnosticTable(QTableWidget * const table, const UnitNode * selUN)
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

void Utils::fillDiagnosticTableBLIP(QTableWidget * const table, const UnitNode *selUN) {
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

    setCellText( table, 0,0, (QObject::tr("Параметр"))); // ("Параметр"));
    setCellText( table, 0,1, (QObject::tr("Вход"))); // ("Вход"));
    setCellText( table, 0,2, (QObject::tr("Статус"))); // ("Статус"));

    setCellText( table, 1,0, (QObject::tr("СД1"))); // ("СД1"));
    setCellText( table, 2,0, (QObject::tr("СД2"))); // ("СД2"));
    setCellText( table, 3,0, (QObject::tr("СД3"))); // ("СД3"));
    setCellText( table, 4,0, (QObject::tr("СД4"))); // ("СД4"));
    setCellText( table, 5,0, (QObject::tr("СД5"))); // ("СД5"));
    setCellText( table, 6,0, (QObject::tr("СД6"))); // ("СД6"));
    setCellText( table, 7,0, (QObject::tr("СД7"))); // ("СД7"));
    setCellText( table, 8,0, (QObject::tr("СД8"))); // ("СД8"));

    setCellText( table, 9,0, (""));
    setCellText( table, 9,1, (QObject::tr("Выход"))); // ("Выход"));
    setCellText( table, 9,2, (QObject::tr("Статус"))); // ("Статус"));

    setCellText( table, 10,0, (QObject::tr("ДК"))); // ("ДК"));
    setCellText( table, 11,0, (QObject::tr("ИУ1"))); // ("ИУ1"));
    setCellText( table, 12,0, (QObject::tr("ИУ2"))); // ("ИУ2"));
    setCellText( table, 13,0, (QObject::tr("ИУ3"))); // ("ИУ3"));
    setCellText( table, 14,0, (QObject::tr("ИУ4"))); // ("ИУ4"));

    setCellText( table, 1,1, ("?"));
    setCellText( table, 1,2, ("?"));
    setCellText( table, 2,1, ("?"));
    setCellText( table, 2,2, ("?"));
    setCellText( table, 3,1, ("?"));
    setCellText( table, 3,2, ("?"));
    setCellText( table, 4,1, ("?"));
    setCellText( table, 4,2, ("?"));
    setCellText( table, 5,1, ("?"));
    setCellText( table, 5,2, ("?"));
    setCellText( table, 6,1, ("?"));
    setCellText( table, 6,2, ("?"));
    setCellText( table, 7,1, ("?"));
    setCellText( table, 7,2, ("?"));
    setCellText( table, 8,1, ("?"));
    setCellText( table, 8,2, ("?"));

    setCellText( table, 10,1, ("?"));
    setCellText( table, 10,2, ("?"));

    setCellText( table, 11,1, ("?"));
    setCellText( table, 11,2, (""));
    setCellText( table, 12,1, ("?"));
    setCellText( table, 12,2, (""));
    setCellText( table, 13,1, ("?"));
    setCellText( table, 13,2, (""));
    setCellText( table, 14,1, ("?"));
    setCellText( table, 14,2, (""));

    for(int i = 0, n = 3; i < n; i++)
        for(int j = 0, m = 15; j < m; j++)
            setCellColor( table, j, i, cellGray);

    if(TypeUnitNode::BL_IP == parent->getType()) {
        int row = 10;

        if(1 == parent->isWasDK()) {
            setCellText( table, row, 2, (QObject::tr("Было"))); // "Тревога"
            setCellColor( table, row, 2, cellRed);
        } else {//if(status2 & Status::Not) {
            setCellText( table, row, 2, (QObject::tr("Нет"))); // "Норма"
            setCellColor( table, row, 2, cellGreen);
        }

        if(1 == parent->isExistDK()) {
            setCellText( table, row, 1, (QObject::tr("Есть"))); // "Было"
            setCellColor( table, row, 1, cellRed);
        } else if(0 == parent->isExistDK()) {
            setCellText( table, row, 1, (QObject::tr("Нет"))); // "Нет"
            setCellColor( table, row, 1, cellGreen);
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
            setCellText( table, row, 1, (QObject::tr("Нет связи"))); // "Норма"
            setCellColor( table, row, 1, cellYellow);
        } else if(TypeUnitNode::SD_BL_IP == un->getType()) {
            row = un->getNum2();
            if(1 == un->isAlarm()) {
                setCellText( table, row, 1, (QObject::tr("Тревога"))); // "Тревога"
                setCellColor( table, row, 1, cellRed);
            }
            else if(1 == un->isNorm()) {
                setCellText( table, row, 1, (QObject::tr("Норма"))); // "Норма"
                setCellColor( table, row, 1, cellGreen);
            }

            if(1 == un->isWasAlarm()) {
                setCellText( table, row, 2, (QObject::tr("Было"))); // "Было"
                setCellColor( table, row, 2, cellRed);
            } else if(0 == un->isWasAlarm()) {
                setCellText( table, row, 2, (QObject::tr("Нет"))); // "Нет"
                setCellColor( table, row, 2, cellGreen);
            }

            if(1 == un->isOff())
            {
                 setCellText( table, row, 1, ("-"));
                 setCellColor( table, row, 1, cellGray);
                 setCellText( table, row, 2, (QObject::tr("Выкл"))); // "Выкл"
                 setCellColor( table, row, 2, cellGray);
            }

        } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
            row = 10 + un->getNum2();
            if(1 == un->isOn()) {
                setCellText( table, row, 1, (QObject::tr("Вкл"))); // "Вкл"
                setCellColor( table, row, 1, cellRed);
                setCellText( table, row, 2, (""));
                setCellColor( table, row, 2, cellGray);
            } else if(1 == un->isOff()) {
                setCellText( table, row, 1, (QObject::tr("Выкл"))); // "Выкл"
                setCellColor( table, row, 1, cellGreen);
                setCellText( table, row, 2, (""));
                setCellColor( table, row, 2, cellGray);
            }

        }
    }
}

void Utils::fillDiagnosticTableRLMKRL(QTableWidget * const table, const UnitNode */*selUN*/)
{
    table->setRowCount(7);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    setCellText( table, 0,0, (QObject::tr("Параметр")));
    setCellText( table, 0,1, (QObject::tr("Значение")));
    setCellText( table, 0,2, (QObject::tr("Параметр")));
    setCellText( table, 0,3, (QObject::tr("Значение")));

    setCellText( table, 1,0, (QObject::tr("Состояние")));
    setCellText( table, 2,0, (QObject::tr("Тревога")));
    setCellText( table, 3,0, (QObject::tr("Сработка")));

    setCellText( table, 4,0, QObject::tr("Вскрытие"));
    setCellColor( table, 4,0, cellGray);

    setCellText( table, 5,0, QObject::tr("ДК"));
    setCellColor( table, 5,0, cellGray);

    setCellText( table, 6,0, QObject::tr("Уровень"));
    setCellColor( table, 6,0, cellGray);

    for(int i = 0, n = 7; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            if(2 == i && 2 == j)
                setCellText( table, i, j, QObject::tr("Вход \"Тревога\""));
            else if(4 == i && 2 == j)
                setCellText( table, i, j, QObject::tr("Вход \"Вскрытие\""));
            else if(5 == i && 2 == j)
                setCellText( table, i, j, QObject::tr("Вход \"ДК\""));
            else if(0 != i && 2 == j)
                setCellText( table, i, j, "");
            else if(0 != i && 0 != j)
                setCellText( table, i, j, "?");

            setCellColor( table, i, j, cellGray);
        }
    }

}

void Utils::fillDiagnosticTableRLM_C(QTableWidget *table, const UnitNode *un)
{
    table->setRowCount(11);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    setCellText( table, 0,0, (QObject::tr("Параметр")));
    setCellText( table, 0,1, (QObject::tr("Значение")));
    setCellText( table, 0,2, (QObject::tr("Параметр")));
    setCellText( table, 0,3, (QObject::tr("Значение")));

    setCellText( table, 1,0, (QObject::tr("Состояние")));
    setCellText( table, 2,0, (QObject::tr("Тревога")));
    setCellText( table, 3,0, (QObject::tr("Сработка")));
    setCellText( table, 4,0, (QObject::tr("ДК")));
    setCellText( table, 5,0, (QObject::tr("Синхронизация")));
    setCellText( table, 6,0, (QObject::tr("Низкий ровень")));
    setCellText( table, 7,0, (QObject::tr("Уровень")));
    setCellText( table, 8,0, (QObject::tr("Пороги")));
    setCellText( table, 9,0, (QObject::tr("Период тактирования")));
    setCellText( table, 10,0, (QObject::tr("Режим обработки")));

    for(int i = 0, n = 11; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            if(2 == i && 2 == j)
                setCellText(table, i, j, QObject::tr("Вход \"Тревога\""));
            else if(4 == i && 2 == j)
                setCellText(table, i, j, QObject::tr("Вход \"ДК\""));
            else if(0 != i && 2 == j)
                setCellText(table, i, j, "");
            else if(0 != i && 0 != j)
                setCellText(table, i, j, ""); // or "?"

            setCellColor(table, i, j, cellGray);
        }
    }

    if(1 == un->isOn()) {
        setCellText( table, 1,1, (QObject::tr("Вкл[1]")));
        setCellColor( table, 1,1, cellGray);
    } else if(1 == un->isOff()) {
        setCellText( table, 1,1, (QObject::tr("Выкл[0]")));
        setCellColor( table, 1,1, cellGray);
    }

    if(1 == un->isInAlarm()) {
        setCellText( table, 2,1, (QObject::tr("Да[1]")));
        setCellColor( table, 2,1, cellRed);
    } else if(0 == un->isInAlarm()) {
        setCellText( table, 2,1, (QObject::tr("Нет[0]")));
        setCellColor( table, 2,1, cellGreen);
    }

    if(1 == un->isOutAlarm()) {
        setCellText( table, 2,3, (QObject::tr("Да[1]")));
        setCellColor( table, 2,3, cellRed);
    } else if(0 == un->isOutAlarm()) {
        setCellText( table, 2,3, (QObject::tr("Нет[0]")));
        setCellColor( table, 2,3, cellGreen);
    }

    if(1 == un->isWasAlarm()) {
        setCellText( table, 3,1, (QObject::tr("Да[1]")));
        setCellColor( table, 3,1, cellRed);
    } else if(0 == un->isWasAlarm()) {
        setCellText( table, 3,1, (QObject::tr("Нет[0]")));
        setCellColor( table, 3,1, cellGreen);
    }

    if(1 == un->isExistDK()) {
        setCellText( table, 4,1, (QObject::tr("Есть[1]")));
        setCellColor( table, 4,1, cellYellow);
    } else if(0 == un->isExistDK()) {
        setCellText( table, 4,1, (QObject::tr("Нет[0]")));
        setCellColor( table, 4,1, cellGreen);
    }

    if(1 == un->isWasDK()) {
        setCellText( table, 4,3, (QObject::tr("Есть[1]")));
        setCellColor( table, 4,3, cellYellow);
    } else if(0 == un->isWasDK()) {
        setCellText( table, 4,3, (QObject::tr("Нет[0]")));
        setCellColor( table, 4,3, cellGreen);
    }

    if(1 == un->isExternalSynchronization()) {
        setCellText( table, 5,1, (QObject::tr("Внешняя")));
        setCellColor( table, 5,1, cellGray);
    } else if(0 == un->isExternalSynchronization()) {
        setCellText( table, 5,1, (QObject::tr("Внутренняя")));
        setCellColor( table, 5,1, cellGray);
    }

    if(1 == un->lowLevl()) {
        setCellText( table, 6,1, (QObject::tr("Да<1>")));
        setCellColor( table, 6,1, cellRed);
    } else if(0 == un->lowLevl()) {
        setCellText( table, 6,1, (QObject::tr("Нет[0]")));
        setCellColor( table, 6,1, cellGreen);
    }

    if(-1.0 != un->voltage()) {
        setCellText( table, 7,1, (QString::number(un->voltage(), 'f', 2)));
        setCellColor( table, 7,1, cellGray);
    }

    if(-1.0 != un->threshold()) {
        setCellText( table, 8,1, (QString::number(un->threshold(), 'f', 2)));
        setCellColor( table, 8,1, cellGray);
    }

    if(-1 != un->clockPeriod()) {
        setCellText( table, 9,1, (QObject::tr("Такт ") + QString::number(un->clockPeriod() + 1)));
        setCellColor( table, 9,1, cellGray);
    }

    if(-1 != un->modeProcessing()) {
        QString str;
        switch (un->modeProcessing()) {
        case 0: str = QObject::tr("Основной"); break;
        case 1: str = QObject::tr("Дополнительный"); break;
        case 2: str = QObject::tr("Ползущий (Плз)"); break;
        case 3: str = QObject::tr("2-й ярус (2Яр)"); break;
        }
        setCellText( table, 10,1, (str));
        setCellColor( table, 10,1, cellGray);
    }

}

void Utils::fillDiagnosticTableTG(QTableWidget * const table, const UnitNode */*selUN*/)
{
    table->setRowCount(15);
    table->setColumnCount(6);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);
    table->setColumnWidth(4, 150);
    table->setColumnWidth(5, 150);

    setCellText( table, 0,0, (QObject::tr("Параметр")));
    setCellText( table, 0,1, (QObject::tr("Значение")));
    setCellText( table, 0,2, (QObject::tr("Параметр")));
    setCellText( table, 0,3, (QObject::tr("Значение")));
    setCellText( table, 0,4, (QObject::tr("Параметр")));
    setCellText( table, 0,5, (QObject::tr("Значение")));

    for(int i = 1, n = 5; i < n; i++) {
        setCellText( table, i,0, (QObject::tr("Сработка ЧЭ%1").arg(i)));
        setCellText( table, i,2, (QObject::tr("Выход \"Тревога ЧЭ%1\"").arg(i)));
        setCellText( table, i,4, (QObject::tr("Сработка со стороны ЧЭ%1").arg(i)));
    }

    setCellText( table, 5,0, (QObject::tr("ДК")));
    setCellText( table, 5,2, (QObject::tr("Выход \"ДК\"")));
    setCellText( table, 6,0, (QObject::tr("Вскрытие")));
    setCellText( table, 6,2, (QObject::tr("Выход \"Вскрытие\"")));

    setCellText( table, 7,0, (QObject::tr("ЧЭ1")));

    for(int i = 0, n = 3; i < n; i++) {
        setCellText( table, i + 8,0, (QObject::tr("Фильтр%1: Сработка").arg(1 + i)));
        setCellText( table, i + 8,2, (QObject::tr("Уровень")));
        setCellText( table, i + 8,4, (QObject::tr("Порог")));
    }

    setCellText( table, 11,0, (QObject::tr("ЧЭ2")));

    for(int i = 0, n = 3; i < n; i++) {
        setCellText( table, i + 12,0, (QObject::tr("Фильтр%1: Сработка").arg(1 + i)));
        setCellText( table, i + 12,2, (QObject::tr("Уровень")));
        setCellText( table, i + 12,4, (QObject::tr("Порог")));
    }

    setCellText( table, 7,2, (""));
    setCellText( table, 11,2, (""));
    setCellText( table, 5,4, (""));
    setCellText( table, 6,4, (""));
    setCellText( table, 7,4, (""));
    setCellText( table, 11,4, (""));


    for(int i = 0, n = 15; i < n; i++) {
        for(int j = 0, m = 6; j < m; j++) {
            if(0 != i && 0 != j && 2 != j && 4 != j) {
                setCellText( table, i,j, "?");
            }
            setCellColor( table, i,j, cellGray);
        }
    }
}

void Utils::fillDiagnosticTableDD_T4K_M(QTableWidget * const table, const UnitNode */*selUN*/)
{
    table->setRowCount(14);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    setCellText( table, 0,0, (QObject::tr("Параметр")));
    setCellText( table, 0,1, (QObject::tr("Значение")));
    setCellText( table, 0,2, (QObject::tr("Параметр")));
    setCellText( table, 0,3, (QObject::tr("Значение")));

    setCellText( table, 1,0, (QObject::tr("Готовность БОД")));


    for(int i = 0, n = 5; i < n; i++) {
        setCellText( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        setCellText( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    setCellText( table, 10,0, (QObject::tr("Выход \"ДК\"")));
    setCellText( table, 11,0, (QObject::tr("Состояние \"ДК\" было")));
    setCellText( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")));
    setCellText( table, 13,0, (QObject::tr("Вскрытие БО было")));

    setCellText( table, 1,2, (QObject::tr("Сработка по ЧЭ1 было")));
    setCellText( table, 2,2, (QObject::tr("Сработка по ЧЭ2 было")));
    setCellText( table, 3,2, (QObject::tr("Обрыв по ЧЭ1 есть")));
    setCellText( table, 4,2, (QObject::tr("Замыкание по ЧЭ1 есть")));
    setCellText( table, 5,2, (QObject::tr("Обрыв по ЧЭ2 есть")));
    setCellText( table, 6,2, (QObject::tr("Замыкание по ЧЭ2 есть")));
    setCellText( table, 7,2, (QObject::tr("Неисправность ДД")));
    setCellText( table, 8,2, (QObject::tr("Обрыв связи с ДД есть")));
    setCellText( table, 9,2, (QObject::tr("Обрыв связи с ДД был")));
    setCellText( table, 10,2, (QObject::tr("Вскрытие ДД есть")));
    setCellText( table, 11,2, (QObject::tr("Вскрытие ДД был")));
    setCellText( table, 12,2, (QObject::tr("Уровень Сигнала ЧЭ1")));
    setCellText( table, 13,2, (QObject::tr("Уровень Сигнала ЧЭ2")));

    for(int i = 0, n = 14; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            if(0 != i && 0 != j && 2 != j)
                setCellText( table, i, j, "?");

            setCellColor( table, i, j, cellGray);
        }
    }
}

void Utils::fillDiagnosticTableDD_SOTA(QTableWidget * const table, const UnitNode */*selUN*/)
{
    table->setRowCount(14);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    setCellText( table, 0,0, (QObject::tr("Параметр")));
    setCellText( table, 0,1, (QObject::tr("Значение")));
    setCellText( table, 0,2, (QObject::tr("Параметр")));
    setCellText( table, 0,3, (QObject::tr("Значение")));

    setCellText( table, 1,0, (QObject::tr("Готовность БОД")));


    for(int i = 0, n = 5; i < n; i++) {
        setCellText( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        setCellText( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    setCellText( table, 10,0, (QObject::tr("Выход \"ДК\"")));
    setCellText( table, 11,0, (QObject::tr("Состояние \"ДК\" было")));
    setCellText( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")));
    setCellText( table, 13,0, (QObject::tr("Вскрытие БО было")));

    setCellText( table, 1,2, (QObject::tr("Сработка было")));
    setCellText( table, 2,2, (QObject::tr("Обрыв связи с ДД есть")));
    setCellText( table, 3,2, (QObject::tr("Обрыв связи с ДД был")));
    setCellText( table, 4,2, (QObject::tr("Вскрытие ДД есть")));
    setCellText( table, 5,2, (QObject::tr("Неисправность ДД есть")));
    setCellText( table, 6,2, (QObject::tr("Тревога по Ф1 есть")));
    setCellText( table, 7,2, (QObject::tr("Тревога поФ2 есть")));
    setCellText( table, 8,2, (QObject::tr("Опрос ДД")));
    setCellText( table, 9,2, (QObject::tr("Уровень Сигнала")));
    for(int i = 0, n = 5; i < n; i++) {
        setCellText( table, 10 + i,2, (QObject::tr("")));
    }

    for(int i = 0, n = 14; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            if(0 != i && 0 != j && 2 != j)
                setCellText( table, i, j, "?");
            setCellColor( table, i, j, cellGray);
        }
    }
}

void Utils::fillDiagnosticTableY4_SOTA(QTableWidget * const table, const UnitNode */*selUN*/)
{
    table->setRowCount(20);
    table->setColumnCount(53);

    table->setColumnWidth(0, 150);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    setCellText( table, 0,0, (QObject::tr("Параметр")));
    setCellText( table, 0,1, (QObject::tr("Значение")));
    setCellText( table, 0,2, (QObject::tr("Параметр")));

    setCellText( table, 1,0, (QObject::tr("Готовность БОД")));


    for(int i = 0, n = 4; i < n; i++) {
        setCellText( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        setCellText( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    setCellText( table, 10,0, (QObject::tr("Выход \"ДК\"")));
    setCellText( table, 11,0, (QObject::tr("Состояние \"ДК\" было")));
    setCellText( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")));
    setCellText( table, 13,0, (QObject::tr("Вскрытие БО было")));

    setCellText( table, 1,2, (QObject::tr("Участки 1-2")));
    setCellText( table, 11,2, (QObject::tr("Участки 3-4")));

    int dec[] = {2,6,12,16};
    for(int i = 0, n = 4; i < n; i++) {
        setCellText( table, dec[i] + 0,2, (QObject::tr("ДД")));
        setCellText( table, dec[i] + 1,2, (QObject::tr("Сработка ДД было")));
        setCellText( table, dec[i] + 2,2, (QObject::tr("Обрыв связи с ДД есть")));
        setCellText( table, dec[i] + 3,2, (QObject::tr("Обрыв связи с ДД был")));
    }

    for(int i = 0, n = 50; i < n; i++) {
        setCellText( table, dec[0],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
        setCellText( table, dec[1],3 + i, (QString("%1").arg(i + 1 + 50, 2, 10, QLatin1Char('0'))));
        setCellText( table, dec[2],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
        setCellText( table, dec[3],3 + i, (QString("%1").arg(i + 1 + 50, 2, 10, QLatin1Char('0'))));
    }

    for(int i = 0, n = 20; i < n; i++) {
        for(int j = 0, m = 53; j < m; j++) {
            if(nullptr == table->item(i, j)) {
                setCellText( table, i, j, "");
            }

            setCellColor( table, i, j, cellGray);
        }
    }
}

void Utils::fillDiagnosticTableY4_T4K_M(QTableWidget * const table, const UnitNode */*selUN*/)
{
    table->setRowCount(22);
    table->setColumnCount(29);

    table->setColumnWidth(0, 150);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    setCellText( table, 0,0, (QObject::tr("Параметр")));
    setCellText( table, 0,1, (QObject::tr("Значение")));
    setCellText( table, 0,2, (QObject::tr("Параметр")));

    setCellText( table, 1,0, (QObject::tr("Готовность БОД")));


    for(int i = 0, n = 4; i < n; i++) {
        setCellText( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        setCellText( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    setCellText( table, 10,0, (QObject::tr("Выход \"ДК\"")));
    setCellText( table, 11,0, (QObject::tr("Состояние \"ДК\" было")));
    setCellText( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")));
    setCellText( table, 13,0, (QObject::tr("Вскрытие БО было")));

    setCellText( table, 1,2, (QObject::tr("Участки 1-2")));
    setCellText( table, 12,2, (QObject::tr("Участки 3-4")));

    int dec[] = {2,13};
    for(int i = 0, n = 2; i < n; i++) {
        setCellText( table, dec[i] + 0,2, (QObject::tr("ДДискретный")));
        setCellText( table, dec[i] + 1,2, (QObject::tr("Сработка по ЧЭ1 было")));
        setCellText( table, dec[i] + 2,2, (QObject::tr("Сработка по ЧЭ2 было")));
        setCellText( table, dec[i] + 3,2, (QObject::tr("Неисправность по ЧЭ1 есть")));
        setCellText( table, dec[i] + 4,2, (QObject::tr("Неисправность по ЧЭ2 есть")));
        setCellText( table, dec[i] + 5,2, (QObject::tr("Обрыв связи с ДД есть")));
        setCellText( table, dec[i] + 6,2, (QObject::tr("Обрыв связи с ДД был")));
        setCellText( table, dec[i] + 7,2, (QObject::tr("Вскрытие ДД есть")));
        setCellText( table, dec[i] + 8,2, (QObject::tr("Вскрытие ДД было")));
    }

    for(int i = 0, n = 26; i < n; i++) {
        setCellText( table, dec[0],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
        setCellText( table, dec[1],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
    }

    for(int i = 0, n = 22; i < n; i++) {
        for(int j = 0, m = 29; j < m; j++) {
            QTableWidgetItem * item = table->item(i, j);
            if(nullptr == item) {
                setCellText( table, i, j, "");
            }

            setCellColor(table, i, j, cellGray);
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
    for(const auto& unDouble : unSetTmp.values()) {
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


