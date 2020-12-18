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

        if(1 == parent->isWasDK()) {
            table->setItem(row, 2, new QTableWidgetItem(QObject::trUtf8("Было"))); // "Тревога"
            table->item(row, 2)->setBackground(cellRed);
        } else {//if(status2 & Status::Not) {
            table->setItem(row, 2, new QTableWidgetItem(QObject::trUtf8("Нет"))); // "Норма"
            table->item(row, 2)->setBackground(cellGreen);
        }

        if(1 == parent->isExistDK()) {
            table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Есть"))); // "Было"
            table->item(row, 1)->setBackground(cellRed);
        } else if(0 == parent->isExistDK()) {
            table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Нет"))); // "Нет"
            table->item(row, 1)->setBackground(cellGreen);
        }
    }

    QList<UnitNode *> tmpLs = parent->getListChilde();
    for(UnitNode * un : tmpLs) {
        int row = -1;

        if(un->getStateWord().isEmpty()) {
            if(TypeUnitNode::SD_BL_IP == un->getType()) {
                row = un->getNum2();
            } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
                row = 10 + un->getNum2();
            }
            table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Нет связи"))); // "Норма"
            table->item(row, 1)->setBackground(cellYellow);
        } else if(TypeUnitNode::SD_BL_IP == un->getType()) {
            row = un->getNum2();
            if(1 == un->isAlarm()) {
                table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Тревога"))); // "Тревога"
                table->item(row, 1)->setBackground(cellRed);
            }
            else if(1 == un->isNorm()) {
                table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Норма"))); // "Норма"
                table->item(row, 1)->setBackground(cellGreen);
            }

            if(1 == un->isWasAlarm()) {
                table->setItem(row, 2, new QTableWidgetItem(QObject::trUtf8("Было"))); // "Было"
                table->item(row, 2)->setBackground(cellRed);
            } else if(0 == un->isWasAlarm()) {
                table->setItem(row, 2, new QTableWidgetItem(QObject::trUtf8("Нет"))); // "Нет"
                table->item(row, 2)->setBackground(cellGreen);
            }

            if(1 == un->isOff())
            {
                 table->setItem(row, 1, new QTableWidgetItem("-"));
                 table->item(row, 1)->setBackground(cellGray);
                 table->setItem(row, 2, new QTableWidgetItem(QObject::trUtf8("Выкл"))); // "Выкл"
                 table->item(row, 2)->setBackground(cellGray);
            }

        } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
            row = 10 + un->getNum2();
            if(1 == un->isOn()) {
                table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Вкл"))); // "Вкл"
                table->item(row, 1)->setBackground(cellRed);
                table->setItem(row, 2, new QTableWidgetItem(""));
                table->item(row, 2)->setBackground(cellGray);
            } else if(1 == un->isOff()) {
                table->setItem(row, 1, new QTableWidgetItem(QObject::trUtf8("Выкл"))); // "Выкл"
                table->item(row, 1)->setBackground(cellGreen);
                table->setItem(row, 2, new QTableWidgetItem(""));
                table->item(row, 2)->setBackground(cellGray);
            }

        }
    }
}

void Utils::fillDiagnosticTableRLMKRL(QTableWidget *table, UnitNode *selUN)
{
    table->setRowCount(7);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::trUtf8("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,3, new QTableWidgetItem(QObject::trUtf8("Значение")));

    table->setItem(1,0, new QTableWidgetItem(QObject::trUtf8("Состояние")));
    table->setItem(2,0, new QTableWidgetItem(QObject::trUtf8("Тревога")));
    table->setItem(3,0, new QTableWidgetItem(QObject::trUtf8("Сработка")));
    auto itm = new QTableWidgetItem(QObject::trUtf8("Вскрытие"));
    itm->setBackground(cellGray);
    table->setItem(4,0, itm);
//    table->setItem(4,0, new QTableWidgetItem(QObject::trUtf8("Вскрытие")));
    itm = new QTableWidgetItem(QObject::trUtf8("ДК"));
    itm->setBackground(cellGray);
    table->setItem(5,0, itm);
//    table->setItem(5,0, new QTableWidgetItem(QObject::trUtf8("ДК")));
    itm = new QTableWidgetItem(QObject::trUtf8("Уровень"));
    itm->setBackground(cellGray);
    table->setItem(6,0, itm);
//    table->setItem(6,0, new QTableWidgetItem(QObject::trUtf8("Уровень")));

    for(int i = 0, n = 7; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            QTableWidgetItem * item = nullptr;
            if(2 == i && 2 == j)
                item = new QTableWidgetItem(QObject::trUtf8("Вход \"Тревога\""));
            else if(4 == i && 2 == j)
                item = new QTableWidgetItem(QObject::trUtf8("Вход \"Вскрытие\""));
            else if(5 == i && 2 == j)
                item = new QTableWidgetItem(QObject::trUtf8("Вход \"ДК\""));
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

void Utils::fillDiagnosticTableRLM_C(QTableWidget *table, UnitNode *selUN)
{
    table->setRowCount(11);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::trUtf8("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,3, new QTableWidgetItem(QObject::trUtf8("Значение")));

    table->setItem(1,0, new QTableWidgetItem(QObject::trUtf8("Состояние")));
    table->setItem(2,0, new QTableWidgetItem(QObject::trUtf8("Тревога")));
    table->setItem(3,0, new QTableWidgetItem(QObject::trUtf8("Сработка")));
    table->setItem(4,0, new QTableWidgetItem(QObject::trUtf8("ДК")));
    table->setItem(5,0, new QTableWidgetItem(QObject::trUtf8("Синхронизация")));
    table->setItem(6,0, new QTableWidgetItem(QObject::trUtf8("Низкий ровень")));
    table->setItem(7,0, new QTableWidgetItem(QObject::trUtf8("Уровень")));
    table->setItem(8,0, new QTableWidgetItem(QObject::trUtf8("Пороги")));
    table->setItem(9,0, new QTableWidgetItem(QObject::trUtf8("Период тактирования")));
    table->setItem(10,0, new QTableWidgetItem(QObject::trUtf8("Режим обработки")));

    for(int i = 0, n = 11; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            QTableWidgetItem * item = nullptr;
            if(2 == i && 2 == j)
                item = new QTableWidgetItem(QObject::trUtf8("Вход \"Тревога\""));
            else if(4 == i && 2 == j)
                item = new QTableWidgetItem(QObject::trUtf8("Вход \"ДК\""));
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

void Utils::fillDiagnosticTableTG(QTableWidget *table, UnitNode *selUN)
{
    table->setRowCount(15);
    table->setColumnCount(6);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);
    table->setColumnWidth(4, 150);
    table->setColumnWidth(5, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::trUtf8("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,3, new QTableWidgetItem(QObject::trUtf8("Значение")));
    table->setItem(0,4, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,5, new QTableWidgetItem(QObject::trUtf8("Значение")));

    for(int i = 1, n = 5; i < n; i++) {
        table->setItem(i,0, new QTableWidgetItem(QObject::trUtf8("Сработка ЧЭ%1").arg(i)));
        table->setItem(i,2, new QTableWidgetItem(QObject::trUtf8("Выход \"Тревога ЧЭ%1\"").arg(i)));
        table->setItem(i,4, new QTableWidgetItem(QObject::trUtf8("Сработка со стороны ЧЭ%1").arg(i)));
    }

    table->setItem(5,0, new QTableWidgetItem(QObject::trUtf8("ДК")));
    table->setItem(5,2, new QTableWidgetItem(QObject::trUtf8("Выход \"ДК\"")));
    table->setItem(6,0, new QTableWidgetItem(QObject::trUtf8("Вскрытие")));
    table->setItem(6,2, new QTableWidgetItem(QObject::trUtf8("Выход \"Вскрытие\"")));

    table->setItem(7,0, new QTableWidgetItem(QObject::trUtf8("ЧЭ1")));

    for(int i = 0, n = 3; i < n; i++) {
        table->setItem(i + 8,0, new QTableWidgetItem(QObject::trUtf8("Фильтр%1: Сработка").arg(1 + i)));
        table->setItem(i + 8,2, new QTableWidgetItem(QObject::trUtf8("Уровень")));
        table->setItem(i + 8,4, new QTableWidgetItem(QObject::trUtf8("Порог")));
    }

    table->setItem(11,0, new QTableWidgetItem(QObject::trUtf8("ЧЭ2")));

    for(int i = 0, n = 3; i < n; i++) {
        table->setItem(i + 12,0, new QTableWidgetItem(QObject::trUtf8("Фильтр%1: Сработка").arg(1 + i)));
        table->setItem(i + 12,2, new QTableWidgetItem(QObject::trUtf8("Уровень")));
        table->setItem(i + 12,4, new QTableWidgetItem(QObject::trUtf8("Порог")));
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

void Utils::fillDiagnosticTableDD_T4K_M(QTableWidget *table, UnitNode *selUN)
{
    table->setRowCount(14);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::trUtf8("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,3, new QTableWidgetItem(QObject::trUtf8("Значение")));

    table->setItem(1,0, new QTableWidgetItem(QObject::trUtf8("Готовность БОД")));


    for(int i = 0, n = 5; i < n; i++) {
        table->setItem(2 + i,0, new QTableWidgetItem(QObject::trUtf8("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        table->setItem(6 + i,0, new QTableWidgetItem(QObject::trUtf8("Тревога Уч.%1 было").arg(1 + i)));
    }

    table->setItem(10,0, new QTableWidgetItem(QObject::trUtf8("Выход \"ДК\"")));
    table->setItem(11,0, new QTableWidgetItem(QObject::trUtf8("Состояние \"ДК\" было")));
    table->setItem(12,0, new QTableWidgetItem(QObject::trUtf8("Выход \"Вскрытие БО\"")));
    table->setItem(13,0, new QTableWidgetItem(QObject::trUtf8("Вскрытие БО было")));

    table->setItem(1,2, new QTableWidgetItem(QObject::trUtf8("Сработка по ЧЭ1 было")));
    table->setItem(2,2, new QTableWidgetItem(QObject::trUtf8("Сработка по ЧЭ2 было")));
    table->setItem(3,2, new QTableWidgetItem(QObject::trUtf8("Обрыв по ЧЭ1 есть")));
    table->setItem(4,2, new QTableWidgetItem(QObject::trUtf8("Замыкание по ЧЭ1 есть")));
    table->setItem(5,2, new QTableWidgetItem(QObject::trUtf8("Обрыв по ЧЭ2 есть")));
    table->setItem(6,2, new QTableWidgetItem(QObject::trUtf8("Замыкание по ЧЭ2 есть")));
    table->setItem(7,2, new QTableWidgetItem(QObject::trUtf8("Неисправность ДД")));
    table->setItem(8,2, new QTableWidgetItem(QObject::trUtf8("Обрыв связи с ДД есть")));
    table->setItem(9,2, new QTableWidgetItem(QObject::trUtf8("Обрыв связи с ДД был")));
    table->setItem(10,2, new QTableWidgetItem(QObject::trUtf8("Вскрытие ДД есть")));
    table->setItem(11,2, new QTableWidgetItem(QObject::trUtf8("Вскрытие ДД был")));
    table->setItem(12,2, new QTableWidgetItem(QObject::trUtf8("Уровень Сигнала ЧЭ1")));
    table->setItem(13,2, new QTableWidgetItem(QObject::trUtf8("Уровень Сигнала ЧЭ2")));

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

void Utils::fillDiagnosticTableDD_SOTA(QTableWidget *table, UnitNode *selUN)
{
    table->setRowCount(14);
    table->setColumnCount(4);

    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::trUtf8("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,3, new QTableWidgetItem(QObject::trUtf8("Значение")));

    table->setItem(1,0, new QTableWidgetItem(QObject::trUtf8("Готовность БОД")));


    for(int i = 0, n = 5; i < n; i++) {
        table->setItem(2 + i,0, new QTableWidgetItem(QObject::trUtf8("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        table->setItem(6 + i,0, new QTableWidgetItem(QObject::trUtf8("Тревога Уч.%1 было").arg(1 + i)));
    }

    table->setItem(10,0, new QTableWidgetItem(QObject::trUtf8("Выход \"ДК\"")));
    table->setItem(11,0, new QTableWidgetItem(QObject::trUtf8("Состояние \"ДК\" было")));
    table->setItem(12,0, new QTableWidgetItem(QObject::trUtf8("Выход \"Вскрытие БО\"")));
    table->setItem(13,0, new QTableWidgetItem(QObject::trUtf8("Вскрытие БО было")));

    table->setItem(1,2, new QTableWidgetItem(QObject::trUtf8("Сработка было")));
    table->setItem(2,2, new QTableWidgetItem(QObject::trUtf8("Обрыв связи с ДД есть")));
    table->setItem(3,2, new QTableWidgetItem(QObject::trUtf8("Обрыв связи с ДД был")));
    table->setItem(4,2, new QTableWidgetItem(QObject::trUtf8("Вскрытие ДД есть")));
    table->setItem(5,2, new QTableWidgetItem(QObject::trUtf8("Неисправность ДД есть")));
    table->setItem(6,2, new QTableWidgetItem(QObject::trUtf8("Тревога по Ф1 есть")));
    table->setItem(7,2, new QTableWidgetItem(QObject::trUtf8("Тревога поФ2 есть")));
    table->setItem(8,2, new QTableWidgetItem(QObject::trUtf8("Опрос ДД")));
    table->setItem(9,2, new QTableWidgetItem(QObject::trUtf8("Уровень Сигнала")));
    for(int i = 0, n = 5; i < n; i++) {
        table->setItem(10 + i,2, new QTableWidgetItem(QObject::trUtf8("")));
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

void Utils::fillDiagnosticTableY4_SOTA(QTableWidget *table, UnitNode *selUN)
{
    table->setRowCount(20);
    table->setColumnCount(53);

    table->setColumnWidth(0, 150);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::trUtf8("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::trUtf8("Параметр")));

    table->setItem(1,0, new QTableWidgetItem(QObject::trUtf8("Готовность БОД")));


    for(int i = 0, n = 4; i < n; i++) {
        table->setItem(2 + i,0, new QTableWidgetItem(QObject::trUtf8("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        table->setItem(6 + i,0, new QTableWidgetItem(QObject::trUtf8("Тревога Уч.%1 было").arg(1 + i)));
    }

    table->setItem(10,0, new QTableWidgetItem(QObject::trUtf8("Выход \"ДК\"")));
    table->setItem(11,0, new QTableWidgetItem(QObject::trUtf8("Состояние \"ДК\" было")));
    table->setItem(12,0, new QTableWidgetItem(QObject::trUtf8("Выход \"Вскрытие БО\"")));
    table->setItem(13,0, new QTableWidgetItem(QObject::trUtf8("Вскрытие БО было")));

    table->setItem(1,2, new QTableWidgetItem(QObject::trUtf8("Участки 1-2")));
    table->setItem(11,2, new QTableWidgetItem(QObject::trUtf8("Участки 3-4")));

    int dec[] = {2,6,12,16};
    for(int i = 0, n = 4; i < n; i++) {
        table->setItem(dec[i] + 0,2, new QTableWidgetItem(QObject::trUtf8("ДД")));
        table->setItem(dec[i] + 1,2, new QTableWidgetItem(QObject::trUtf8("Сработка ДД было")));
        table->setItem(dec[i] + 2,2, new QTableWidgetItem(QObject::trUtf8("Обрыв связи с ДД есть")));
        table->setItem(dec[i] + 3,2, new QTableWidgetItem(QObject::trUtf8("Обрыв связи с ДД был")));
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

void Utils::fillDiagnosticTableY4_T4K_M(QTableWidget *table, UnitNode *selUN)
{
    table->setRowCount(22);
    table->setColumnCount(29);

    table->setColumnWidth(0, 150);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 150);
    table->setColumnWidth(3, 150);

    table->setItem(0,0, new QTableWidgetItem(QObject::trUtf8("Параметр")));
    table->setItem(0,1, new QTableWidgetItem(QObject::trUtf8("Значение")));
    table->setItem(0,2, new QTableWidgetItem(QObject::trUtf8("Параметр")));

    table->setItem(1,0, new QTableWidgetItem(QObject::trUtf8("Готовность БОД")));


    for(int i = 0, n = 4; i < n; i++) {
        table->setItem(2 + i,0, new QTableWidgetItem(QObject::trUtf8("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        table->setItem(6 + i,0, new QTableWidgetItem(QObject::trUtf8("Тревога Уч.%1 было").arg(1 + i)));
    }

    table->setItem(10,0, new QTableWidgetItem(QObject::trUtf8("Выход \"ДК\"")));
    table->setItem(11,0, new QTableWidgetItem(QObject::trUtf8("Состояние \"ДК\" было")));
    table->setItem(12,0, new QTableWidgetItem(QObject::trUtf8("Выход \"Вскрытие БО\"")));
    table->setItem(13,0, new QTableWidgetItem(QObject::trUtf8("Вскрытие БО было")));

    table->setItem(1,2, new QTableWidgetItem(QObject::trUtf8("Участки 1-2")));
    table->setItem(12,2, new QTableWidgetItem(QObject::trUtf8("Участки 3-4")));

    int dec[] = {2,13};
    for(int i = 0, n = 2; i < n; i++) {
        table->setItem(dec[i] + 0,2, new QTableWidgetItem(QObject::trUtf8("ДДискретный")));
        table->setItem(dec[i] + 1,2, new QTableWidgetItem(QObject::trUtf8("Сработка по ЧЭ1 было")));
        table->setItem(dec[i] + 2,2, new QTableWidgetItem(QObject::trUtf8("Сработка по ЧЭ2 было")));
        table->setItem(dec[i] + 3,2, new QTableWidgetItem(QObject::trUtf8("Неисправность по ЧЭ1 есть")));
        table->setItem(dec[i] + 4,2, new QTableWidgetItem(QObject::trUtf8("Неисправность по ЧЭ2 есть")));
        table->setItem(dec[i] + 5,2, new QTableWidgetItem(QObject::trUtf8("Обрыв связи с ДД есть")));
        table->setItem(dec[i] + 6,2, new QTableWidgetItem(QObject::trUtf8("Обрыв связи с ДД был")));
        table->setItem(dec[i] + 7,2, new QTableWidgetItem(QObject::trUtf8("Вскрытие ДД есть")));
        table->setItem(dec[i] + 8,2, new QTableWidgetItem(QObject::trUtf8("Вскрытие ДД было")));
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
    for(const auto& unDouble : as_const(unSetTmp.toList())) {
//        qDebug() << "itr :" << unSetTmp;
//        qDebug() << "fnd :" << unDouble << unDouble->getMetaNames() << unDouble->getName();
        if(nullptr != unDouble->getTreeParentUN()) {
            if(TypeUnitNode::SD_BL_IP == unDouble->getTreeParentUN()->getType()) {
//                qDebug() << "trg :"<< unDouble->getMetaNames() << unDouble->getName();
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


