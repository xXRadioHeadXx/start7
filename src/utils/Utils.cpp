#include "Utils.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QHostAddress>
#include "ServerSettingUtils.h"
#include "SignalSlotCommutator.h"
#include "global.h"
#include "UnitNode.h"
#include "SWPBLIP.h"
#include "SWPRLM.h"
#include "SWPRLMC.h"
#include "SWPSDBLIP.h"
#include "SWPIUBLIP.h"
#include "SWPTGType0x32.h"
#include "SWPTGSubType0x32.h"
#include "SWPTGType0x34.h"
#include "SWPTGSubType0x34.h"


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

QTableWidgetItem * Utils::setCellText(QTableWidget * const table, const int row, const int column, const QString &text)
{
    if(row >= table->rowCount() || column >= table->columnCount())
        return nullptr;
    QTableWidgetItem * item = table->item(row, column);
    if(nullptr == item) {
        table->setItem(row, column, new QTableWidgetItem(text));
    } else {
        item->setText(text);
    }

    return table->item(row, column);;
}

QTableWidgetItem *Utils::setCellTextWithForeground(QTableWidget * const table, const int row, const int column, const QString &text, const QBrush &foreground)
{
    auto item = setCellText(table, row, column, text);
    if(nullptr != item) {
        if(item->backgroundColor() != cellGray && foreground.color() != QColor(0x00, 0x00, 0x00)) {
            item->setForeground(foreground);
        } else {
            item->setForeground(QBrush(QColor(0x00, 0x00, 0x00)));
        }
        QFont font = item->font();
        if(foreground.color() != QColor(0x00, 0x00, 0x00)) {
            font.setBold(true);
        } else {
            font.setBold(false);
        }
        item->setFont(font);
    }
    return item;
}

void Utils::setCellColor(QTableWidget * const table, const int row, const int column, const QColor color)
{
    if(row >= table->rowCount() || column >= table->columnCount())
        return;
    QTableWidgetItem * item = table->item(row, column);
    if(nullptr == item) {
        table->setItem(row, column, new QTableWidgetItem());
        item = table->item(row, column);
    }
    if(nullptr != item) {
        item->setBackground(QBrush(color));
    }

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
QColor Utils::cellBlue = QColor(0x80, 0x9F, 0xFF);


void Utils::fillDiagnosticTable(QTableWidget * const table, const QSharedPointer<UnitNode> selUN)
{
    try {
        if(selUN.isNull() || nullptr == table)
            return;

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
        //qDebug() << "fillDiagnosticTable catch exception ...";
    }
}

void Utils::fillDiagnosticTableBLIP(QTableWidget * const table, const QSharedPointer<UnitNode> selUN) {
    QSharedPointer<UnitNode>  parent = selUN->getParentUN();
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

    // prepare -->
    table->setRowCount(15);
    table->setColumnCount(3);

//    table->setColumnWidth(0, 60);
//    table->setColumnWidth(1, 150);
//    table->setColumnWidth(3, 150);

    setCellTextWithForeground( table, 0,0, (QObject::tr("Параметр"))); // ("Параметр"));
    setCellTextWithForeground( table, 0,1, (QObject::tr("Вход"))); // ("Вход"));
    setCellTextWithForeground( table, 0,2, (QObject::tr("Статус"))); // ("Статус"));

    setCellTextWithForeground( table, 1,0, (QObject::tr("СД1"))); // ("СД1"));
    setCellTextWithForeground( table, 2,0, (QObject::tr("СД2"))); // ("СД2"));
    setCellTextWithForeground( table, 3,0, (QObject::tr("СД3"))); // ("СД3"));
    setCellTextWithForeground( table, 4,0, (QObject::tr("СД4"))); // ("СД4"));
    setCellTextWithForeground( table, 5,0, (QObject::tr("СД5"))); // ("СД5"));
    setCellTextWithForeground( table, 6,0, (QObject::tr("СД6"))); // ("СД6"));
    setCellTextWithForeground( table, 7,0, (QObject::tr("СД7"))); // ("СД7"));
    setCellTextWithForeground( table, 8,0, (QObject::tr("СД8"))); // ("СД8"));

    setCellTextWithForeground( table, 9,0, (""));
    setCellTextWithForeground( table, 9,1, (QObject::tr("Выход"))); // ("Выход"));
    setCellTextWithForeground( table, 9,2, (QObject::tr("Статус"))); // ("Статус"));

    setCellTextWithForeground( table, 10,0, (QObject::tr("ДК"))); // ("ДК"));
    setCellTextWithForeground( table, 11,0, (QObject::tr("ИУ1"))); // ("ИУ1"));
    setCellTextWithForeground( table, 12,0, (QObject::tr("ИУ2"))); // ("ИУ2"));
    setCellTextWithForeground( table, 13,0, (QObject::tr("ИУ3"))); // ("ИУ3"));
    setCellTextWithForeground( table, 14,0, (QObject::tr("ИУ4"))); // ("ИУ4"));


    for(int i = 0, n = table->columnCount(); i < n; i++)
        for(int j = 0, m = table->rowCount(); j < m; j++)
            setCellColor( table, j, i, cellGray);

    for(int i = 1, n = 3; i < n; i++) {
        for(int j = 1, m = 15; j < m; j++) {
            if(9 == j)
                continue;
            else if(2 == i && 10 < j)
                continue;
            setCellTextWithForeground( table, j, i, "?", QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }
    }

    // prepare <--

    // fill -->

//    if(10 == parent->getPublishedState()) {
//        for(int i = 1, n = 3; i < n; i++) {
//            for(int j = 1, m = 15; j < m; j++) {
//                if(9 == j)
//                    continue;
//                else if(2 == i && 10 < j)
//                    continue;
//                setCellColor( table, j, i, cellYellow);
//                setCellTextWithForeground( table, j, i, "?");
//            }
//        }
//        return;
//    }

    if(TypeUnitNode::BL_IP == parent->getType()) {
        int row = 10;

        if(1 == parent->swpBLIP().isWasDK()) {
            setCellColor( table, row, 2, cellRed);
            setCellTextWithForeground( table, row, 2, (QObject::tr("Было")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Тревога"
        } else {//if(status2 & Status::Not) {
            setCellColor( table, row, 2, cellGreen);
            setCellTextWithForeground( table, row, 2, (QObject::tr("Нет")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Норма"
        }

        if(1 == parent->swpBLIP().isExistDK()) {
            setCellColor( table, row, 1, cellRed);
            setCellTextWithForeground( table, row, 1, (QObject::tr("Есть")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Было"
        } else if(0 == parent->swpBLIP().isExistDK()) {
            setCellColor( table, row, 1, cellGreen);
            setCellTextWithForeground( table, row, 1, (QObject::tr("Нет")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Нет"
        }
    }


    QList<QSharedPointer<UnitNode> > tmpLs = parent->getListChilde();
    for(QSharedPointer<UnitNode>  un : tmpLs) {
        if(TypeUnitNode::SD_BL_IP != un->getType() && TypeUnitNode::IU_BL_IP != un->getType()) {
            continue;
        }

        if (10 == un->getPublishedState()) {
            for(int i = 1, n = 3; i < n; i++) {
                for(int j = 1, m = 15; j < m; j++) {
                    if(9 == j) {
                        continue;
                    } else if(2 == i && 10 < j) {
                        continue;
                    }
                    setCellColor( table, j, i, cellYellow);
                    setCellTextWithForeground( table, j, i, QObject::tr("Нет связи!"), QBrush(QColor(0xFF, 0xFF, 0xFF)));
                }
            }
            return;
        }

        int row = -1;

        if(un->getStateWord().getByteWord().isEmpty()) {
            if(TypeUnitNode::SD_BL_IP == un->getType()) {
                row = un->getNum2();
            } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
                row = 10 + un->getNum2();
            }
            setCellColor( table, row, 1, cellYellow);
            setCellTextWithForeground( table, row, 1, (QObject::tr("Нет связи")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Норма"
        } else if(TypeUnitNode::SD_BL_IP == un->getType()) {
            row = un->getNum2();
            if(1 == un->swpSDBLIP().isAlarm()) {
                setCellColor( table, row, 1, cellRed);
                setCellTextWithForeground( table, row, 1, (QObject::tr("Тревога")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Тревога"
            }
            else if(1 == un->swpSDBLIP().isNorm()) {
                setCellColor( table, row, 1, cellGreen);
                setCellTextWithForeground( table, row, 1, (QObject::tr("Норма")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Норма"
            }

            if(1 == un->swpSDBLIP().isWasAlarm()) {
                setCellColor( table, row, 2, cellRed);
                setCellTextWithForeground( table, row, 2, (QObject::tr("Было")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Было"
            } else if(0 == un->swpSDBLIP().isWasAlarm()) {
                setCellColor( table, row, 2, cellGreen);
                setCellTextWithForeground( table, row, 2, (QObject::tr("Нет")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Нет"
            }

            if(1 == un->swpSDBLIP().isOff())
            {
                setCellColor( table, row, 1, cellGray);
                setCellTextWithForeground( table, row, 1, ("-"), QBrush(QColor(0xFF, 0xFF, 0xFF)));
                setCellColor( table, row, 2, cellGray);
                setCellTextWithForeground( table, row, 2, (QObject::tr("Выкл")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Выкл"
            }

        } else if(TypeUnitNode::IU_BL_IP == un->getType()) {
            row = 10 + un->getNum2();
            if(1 == un->swpIUBLIP().isOn()) {
                setCellColor( table, row, 1, cellRed);
                setCellTextWithForeground( table, row, 1, (QObject::tr("Вкл")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Вкл"
                setCellColor( table, row, 2, cellGray);
                setCellTextWithForeground( table, row, 2, (""));
            } else if(1 == un->swpIUBLIP().isOff()) {
                setCellColor( table, row, 1, cellGreen);
                setCellTextWithForeground( table, row, 1, (QObject::tr("Выкл")), QBrush(QColor(0xFF, 0xFF, 0xFF))); // "Выкл"
                setCellColor( table, row, 2, cellGray);
                setCellTextWithForeground( table, row, 2, (""));
            }

        }
    }
    // fill <--
}

void Utils::fillDiagnosticTableRLMKRL(QTableWidget * const table, const QSharedPointer<UnitNode> un)
{
    // prepare -->
    table->setRowCount(9);
    table->setColumnCount(3);

//    table->setColumnWidth(0, 150);
//    table->setColumnWidth(1, 150);
//    table->setColumnWidth(2, 150);

    for(int i = 0, n = table->rowCount(); i < n; i++) {
        for(int j = 0, m = table->columnCount(); j < m; j++) {
            setCellTextWithForeground( table, i, j, "");
            setCellColor( table, i, j, cellGray);
        }
    }

    setCellTextWithForeground( table, 0,0, (QObject::tr("Параметр")));
//    setCellTextWithForeground( table, 0,1, (QObject::tr("Вход")));
    setCellTextWithForeground( table, 0,2, (QObject::tr("Статус")));

    setCellTextWithForeground( table, 1,0, (QObject::tr("Датчик")));
    setCellTextWithForeground( table, 2,0, (QObject::tr("Срабатывание")));

//    setCellTextWithForeground( table, 3,0, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 3,1, (QObject::tr("Выход")));
    setCellTextWithForeground( table, 3,2, (QObject::tr("Статус")));

    setCellTextWithForeground( table, 4,0, (QObject::tr("Тревога")));

//    setCellTextWithForeground( table, 0,0, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 5,1, (QObject::tr("Вход")));
    setCellTextWithForeground( table, 5,2, (QObject::tr("Статус")));

    setCellTextWithForeground( table, 6,0, (QObject::tr("ДК")));
    setCellTextWithForeground( table, 7,0, (QObject::tr("Вскрытие")));
    setCellTextWithForeground( table, 8,0, (QObject::tr("Уровень")));
    // prepare <--

    // fill -->

    if(10 == un->getPublishedState()) {
        for(int i = 1, n = 3; i < n; i++) {
            for(int j = 1, m = 9; j < m; j++) {
                if(1 == j && 1 == i) {
                    continue;
                } else if(2 == j && 2 == i) {
                    continue;
                } else if(3 == j) {
                    continue;
                } else if(5 == j) {
                    continue;
                } else if(8 == j && 2 == i) {
                    continue;
                }
                setCellColor( table, j, i, cellYellow);
                setCellTextWithForeground( table, j, i, QObject::tr("Нет связи!"), QBrush(QColor(0xFF, 0xFF, 0xFF)));
            }
        }
        return;
    }

    //"Датчик"
    if(1 == un->swpRLM().isOn()) {
        setCellColor( table, 1,2, cellGreen);
        setCellTextWithForeground( table, 1,2, (QObject::tr("Вкл[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(1 == un->swpRLM().isOff()) {
        setCellColor( table, 1,2, cellRed);
        setCellTextWithForeground( table, 1,2, (QObject::tr("Выкл[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Срабатывание"
    if(1 == un->swpRLM().isOutAlarm()) {
        setCellColor( table, 2,1, cellRed);
        setCellTextWithForeground( table, 2,1, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLM().isOutAlarm()) {
        setCellColor( table, 2,1, cellGreen);
        setCellTextWithForeground( table, 2,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Выход \"Тревога\""
    if(1 == un->swpRLM().isInAlarm()) {
        setCellColor( table, 4,1, cellRed);
        setCellTextWithForeground( table, 4,1, (QObject::tr("Да[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLM().isInAlarm()) {
        setCellColor( table, 4,1, cellGreen);
        setCellTextWithForeground( table, 4,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Статус \"Тревога\""
    if(1 == un->swpRLM().isWasAlarm()) {
        setCellColor( table, 4,2, cellRed);
        setCellTextWithForeground( table, 4,2, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLM().isWasAlarm()) {
        setCellColor( table, 4,2, cellGreen);
        setCellTextWithForeground( table, 4,2, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Вход \"ДК\""
    if(1 == un->swpRLM().isExistDK()) {
        setCellColor( table, 6,1, cellYellow);
        setCellTextWithForeground( table, 6,1, (QObject::tr("Есть[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLM().isExistDK()) {
        setCellColor( table, 6,1, cellGreen);
        setCellTextWithForeground( table, 6,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Статус \"ДК\""
    if(1 == un->swpRLM().isWasDK()) {
        setCellColor( table, 6,2, cellYellow);
        setCellTextWithForeground( table, 6,2, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLM().isWasDK()) {
        setCellColor( table, 6,2, cellGreen);
        setCellTextWithForeground( table, 6,2, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Вход \"Вскрытие\""
    if(1 == un->swpRLM().isInOpened()) {
        setCellColor( table, 7,1, cellRed);
        setCellTextWithForeground( table, 7,1, (QObject::tr("Есть[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLM().isInOpened()) {
        setCellColor( table, 7,1, cellGreen);
        setCellTextWithForeground( table, 7,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Статус \"Вскрытие\""
    if(1 == un->swpRLM().isWasOpened()) {
        setCellColor( table, 7,2, cellRed);
        setCellTextWithForeground( table, 7,2, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLM().isWasOpened()) {
        setCellColor( table, 7,2, cellGreen);
        setCellTextWithForeground( table, 7,2, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Уровень"
    if(-1.0 != un->swpRLM().voltage()) {
        setCellColor( table, 8,1, cellGray);
        setCellTextWithForeground( table, 8,1, (QString::number(un->swpRLM().voltage(), 'f', 2)), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    // fill <--
}

void Utils::fillDiagnosticTableRLM_C(QTableWidget *table, const QSharedPointer<UnitNode> un)
{
    // prepare -->
    table->setRowCount(13);
    table->setColumnCount(3);

//    table->setColumnWidth(0, 150);
//    table->setColumnWidth(1, 150);
//    table->setColumnWidth(2, 150);

    for(int i = 0, n = table->rowCount(); i < n; i++) {
        for(int j = 0, m = table->columnCount(); j < m; j++) {
            setCellColor( table, i, j, cellGray);
            setCellTextWithForeground( table, i, j, "");
        }
    }

    setCellTextWithForeground( table, 0,0, (QObject::tr("Параметр")));
//    setCellTextWithForeground( table, 0,1, (QObject::tr("Вход")));
    setCellTextWithForeground( table, 0,2, (QObject::tr("Статус")));

    setCellTextWithForeground( table, 1,0, (QObject::tr("Датчик")));
    setCellTextWithForeground( table, 2,0, (QObject::tr("Срабатывание")));

//    setCellTextWithForeground( table, 3,0, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 3,1, (QObject::tr("Выход")));
    setCellTextWithForeground( table, 3,2, (QObject::tr("Статус")));

    setCellTextWithForeground( table, 4,0, (QObject::tr("Тревога")));

//    setCellTextWithForeground( table, 0,0, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 5,1, (QObject::tr("Вход")));
    setCellTextWithForeground( table, 5,2, (QObject::tr("Статус")));

    setCellTextWithForeground( table, 6,0, (QObject::tr("ДК")));
    setCellTextWithForeground( table, 7,0, (QObject::tr("Синхронизация")));
    setCellTextWithForeground( table, 8,0, (QObject::tr("Низкий ровень")));
    setCellTextWithForeground( table, 9,0, (QObject::tr("Уровень")));
    setCellTextWithForeground( table, 10,0, (QObject::tr("Пороги")));
    setCellTextWithForeground( table, 11,0, (QObject::tr("Период тактирования")));
    setCellTextWithForeground( table, 12,0, (QObject::tr("Режим обработки")));
    // prepare <--

    // fill -->
    if(10 == un->getPublishedState()) {
        for(int i = 1, n = 3; i < n; i++) {
            for(int j = 1, m = 13; j < m; j++) {
                if(1 == j && 1 == i) {
                    continue;
                } else if(2 == j && 2 == i) {
                    continue;
                } else if(3 == j) {
                    continue;
                } else if(5 == j) {
                    continue;
                } else if(7 == j) {
                    continue;
                } else if(7 < j && 2 == i) {
                    continue;
                }
                setCellColor( table, j, i, cellYellow);
                setCellTextWithForeground( table, j, i, QObject::tr("Нет связи!"), QBrush(QColor(0xFF, 0xFF, 0xFF)));
            }
        }
        return;
    }

    //"Датчик"
    if(1 == un->swpRLMC().isOn()) {
        setCellColor( table, 1,2, cellGreen);
        setCellTextWithForeground( table, 1,2, (QObject::tr("Вкл[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(1 == un->swpRLMC().isOff()) {
        setCellColor( table, 1,2, cellGray);
        setCellTextWithForeground( table, 1,2, (QObject::tr("Выкл[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Срабатывание"
    if(1 == un->swpRLMC().isOutAlarm()) {
        setCellColor( table, 2,1, cellRed);
        setCellTextWithForeground( table, 2,1, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLMC().isOutAlarm()) {
        setCellColor( table, 2,1, cellGreen);
        setCellTextWithForeground( table, 2,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Выход \"Тревога\""
    if(1 == un->swpRLMC().isInAlarm()) {
        setCellColor( table, 4,1, cellRed);
        setCellTextWithForeground( table, 4,1, (QObject::tr("Да[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLMC().isInAlarm()) {
        setCellColor( table, 4,1, cellGreen);
        setCellTextWithForeground( table, 4,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Статус \"Тревога\""
    if(1 == un->swpRLMC().isWasAlarm()) {
        setCellColor( table, 4,2, cellRed);
        setCellTextWithForeground( table, 4,2, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLMC().isWasAlarm()) {
        setCellColor( table, 4,2, cellGreen);
        setCellTextWithForeground( table, 4,2, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Вход \"ДК\""
    if(1 == un->swpRLMC().isExistDK()) {
        setCellColor( table, 6,1, cellYellow);
        setCellTextWithForeground( table, 6,1, (QObject::tr("Есть[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLMC().isExistDK()) {
        setCellColor( table, 6,1, cellGreen);
        setCellTextWithForeground( table, 6,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Статус \"ДК\""
    if(1 == un->swpRLMC().isWasDK()) {
        setCellColor( table, 6,2, cellYellow);
        setCellTextWithForeground( table, 6,2, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLMC().isWasDK()) {
        setCellColor( table, 6,2, cellGreen);
        setCellTextWithForeground( table, 6,2, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Синхронизация"
    if(1 == un->swpRLMC().isExternalSynchronization()) {
        setCellColor( table, 7,1, cellGray);
        setCellTextWithForeground( table, 7,1, (QObject::tr("Внешняя")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLMC().isExternalSynchronization()) {
        setCellColor( table, 7,1, cellGray);
        setCellTextWithForeground( table, 7,1, (QObject::tr("Внутренняя")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Низкий ровень"
    if(1 == un->swpRLMC().isFault()) {
        setCellColor( table, 8,1, cellRed);
        setCellTextWithForeground( table, 8,1, (QObject::tr("Да<1>")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == un->swpRLMC().isFault()) {
        setCellColor( table, 8,1, cellGreen);
        setCellTextWithForeground( table, 8,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Уровень"
    if(-1.0 != un->swpRLMC().voltage()) {
        setCellColor( table, 9,1, cellGray);
        setCellTextWithForeground( table, 9,1, (QString::number(un->swpRLMC().voltage(), 'f', 2)), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Пороги"
    if(-1.0 != un->swpRLMC().threshold()) {
        setCellColor( table, 10,1, cellGray);
        if(1.0 > un->swpRLMC().threshold())
            setCellTextWithForeground( table, 10,1, (QString::number(un->swpRLMC().threshold(), 'f', 1)), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        else
            setCellTextWithForeground( table, 10,1, (QString::number(un->swpRLMC().threshold(), 'f', 0)), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Период тактирования"
    if(-1 != un->swpRLMC().clockPeriod()) {
        setCellColor( table, 11,1, cellGray);
        setCellTextWithForeground( table, 11,1, (QObject::tr("Такт ") + QString::number(un->swpRLMC().clockPeriod() + 1)), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Режим обработки"
    if(-1 != un->swpRLMC().modeProcessing()) {
        setCellColor( table, 12,1, cellGray);
        QString str;
        switch (un->swpRLMC().modeProcessing()) {
        case 0: str = QObject::tr("Основной"); break;
        case 1: str = QObject::tr("Дополнительный"); break;
        case 2: str = QObject::tr("Ползущий (Плз)"); break;
        case 3: str = QObject::tr("2-й ярус (2Яр)"); break;
        }
        setCellTextWithForeground( table, 12,1, (str), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    // fill <--
}

void Utils::fillDiagnosticTableTG(QTableWidget * const table, const QSharedPointer<UnitNode> selUN)
{
    // prepare -->
    table->setRowCount(23);
    table->setColumnCount(6);

//    table->setColumnWidth(0, 100);
//    table->setColumnWidth(1, 150);
//    table->setColumnWidth(2, 150);
//    table->setColumnWidth(3, 150);
//    table->setColumnWidth(4, 150);
//    table->setColumnWidth(5, 150);

    for(int i = 0, n = table->rowCount(); i < n; i++) {
        for(int j = 0, m = table->columnCount(); j < m; j++) {
            if(0 != i && 0 != j && 2 != j && 4 != j) {
                setCellTextWithForeground( table, i,j, "");
            }
            setCellColor( table, i,j, cellGray);
        }
    }

    setCellTextWithForeground( table, 0,0, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 0,1, (QObject::tr("Значение")));
    setCellTextWithForeground( table, 0,2, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 0,3, (QObject::tr("Значение")));
    setCellTextWithForeground( table, 0,4, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 0,5, (QObject::tr("Значение")));

    for(int i = 1, n = 5; i < n; i++) {
        setCellTextWithForeground( table, i,0, (QObject::tr("Сработка ЧЭ%1").arg(i)));
        setCellTextWithForeground( table, i,2, (QObject::tr("Выход \"Тревога ЧЭ%1\"").arg(i)));
        setCellTextWithForeground( table, i,4, (QObject::tr("Сработка со стороны ЧЭ%1").arg(i)));
    }

    setCellTextWithForeground( table, 5,0, (QObject::tr("ДК")));
    setCellTextWithForeground( table, 5,2, (QObject::tr("Выход \"ДК\"")));
    setCellTextWithForeground( table, 6,0, (QObject::tr("Вскрытие")));
    setCellTextWithForeground( table, 6,2, (QObject::tr("Вход \"Вскрытие\"")));

    setCellTextWithForeground( table, 7,0, (QObject::tr("ЧЭ1")));

    for(int i = 0, n = 3; i < n; i++) {
        setCellTextWithForeground( table, i + 8,0, (QObject::tr("Фильтр%1: Сработка").arg(1 + i)));
        setCellTextWithForeground( table, i + 8,2, (QObject::tr("Уровень")));
        setCellTextWithForeground( table, i + 8,4, (QObject::tr("Порог")));
    }

    setCellTextWithForeground( table, 11,0, (QObject::tr("ЧЭ2")));

    for(int i = 0, n = 3; i < n; i++) {
        setCellTextWithForeground( table, i + 12,0, (QObject::tr("Фильтр%1: Сработка").arg(1 + i)));
        setCellTextWithForeground( table, i + 12,2, (QObject::tr("Уровень")));
        setCellTextWithForeground( table, i + 12,4, (QObject::tr("Порог")));
    }

    setCellTextWithForeground( table, 15,0, (QObject::tr("ЧЭ3")));

    for(int i = 0, n = 3; i < n; i++) {
        setCellTextWithForeground( table, i + 16,0, (QObject::tr("Фильтр%1: Сработка").arg(1 + i)));
        setCellTextWithForeground( table, i + 16,2, (QObject::tr("Уровень")));
        setCellTextWithForeground( table, i + 16,4, (QObject::tr("Порог")));
    }

    setCellTextWithForeground( table, 19,0, (QObject::tr("ЧЭ4")));

    for(int i = 0, n = 3; i < n; i++) {
        setCellTextWithForeground( table, i + 20,0, (QObject::tr("Фильтр%1: Сработка").arg(1 + i)));
        setCellTextWithForeground( table, i + 20,2, (QObject::tr("Уровень")));
        setCellTextWithForeground( table, i + 20,4, (QObject::tr("Порог")));
    }



    setCellTextWithForeground( table, 7,2, (""));
    setCellTextWithForeground( table, 11,2, (""));
    setCellTextWithForeground( table, 15,2, (""));
    setCellTextWithForeground( table, 19,2, (""));
    setCellTextWithForeground( table, 5,4, (""));
    setCellTextWithForeground( table, 6,4, (""));
    setCellTextWithForeground( table, 7,4, (""));
    setCellTextWithForeground( table, 11,4, (""));
    setCellTextWithForeground( table, 15,4, (""));
    setCellTextWithForeground( table, 19,4, (""));



    // prepare <--

    // fill -->
    if(10 == selUN->getPublishedState()) {
        for(int i = 1, n = table->columnCount(); i < n; i+=2) {
            for(int j = 1, m = table->rowCount(); j < m; j++) {
                if((5 == j || 6 == j) && 5 == i) {
                    continue;
                } else if((7 == j || 11 == j || 15 == j || 19 == j) && 1 != i) {
                    continue;
                }
                setCellColor( table, j, i, cellYellow);
                setCellTextWithForeground( table, j, i, QObject::tr("Нет связи!"), QBrush(QColor(0xFF, 0xFF, 0xFF)));
            }
        }
        return;
    }

    auto swp32 = selUN->swpTGType0x32();

    for(int i = 1, n = 5; i < n; i++) {
//        setCellTextWithForeground( table, i,0, (QObject::tr("Сработка ЧЭ%1").arg(i)));
        //"Cработка ЧЭ%1"
        if(1 == swp32.C(i).isInAlarm()) {
            setCellColor( table, i,1, cellRed);
            setCellTextWithForeground( table, i,1, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        } else if(0 == swp32.C(i).isInAlarm()) {
            setCellColor( table, i,1, cellGreen);
            setCellTextWithForeground( table, i,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }
//        setCellTextWithForeground( table, i,2, (QObject::tr("Выход \"Тревога ЧЭ%1\"").arg(i)));
        //Выход "Тревога ЧЭ%1"
        if(1 == swp32.C(i).isOutAlarm()) {
            setCellColor( table, i,3, cellRed);
            setCellTextWithForeground( table, i,3, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        } else if(0 == swp32.C(i).isOutAlarm()) {
            setCellColor( table, i,3, cellGreen);
            setCellTextWithForeground( table, i,3, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }
//        setCellTextWithForeground( table, i,4, (QObject::tr("Сработка со стороны ЧЭ%1").arg(i)));
        //"Сработка со стороны ЧЭ%1"
        if(1 == swp32.C(i).isSideAlarm()) {
            setCellColor( table, i,5, cellRed);
            setCellTextWithForeground( table, i,5, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        } else if(0 == swp32.C(i).isSideAlarm()) {
            setCellColor( table, i,5, cellGreen);
            setCellTextWithForeground( table, i,5, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }
    }

//    "ДК"
    if(1 == swp32.isWasDK()) {
        setCellColor( table, 5,1, cellYellow);
        setCellTextWithForeground( table, 5,1, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == swp32.isWasDK()) {
        setCellColor( table, 5,1, cellGreen);
        setCellTextWithForeground( table, 5,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
//    "Выход \"ДК\""
    if(1 == swp32.isExistDK()) {
        setCellColor( table, 5,3, cellYellow);
        setCellTextWithForeground( table, 5,3, (QObject::tr("Есть[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == swp32.isExistDK()) {
        setCellColor( table, 5,3, cellGreen);
        setCellTextWithForeground( table, 5,3, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
//    "Вскрытие"
    if(1 == swp32.isWasOpened()) {
        setCellColor( table, 6,1, cellRed);
        setCellTextWithForeground( table, 6,1, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == swp32.isWasOpened()) {
        setCellColor( table, 6,1, cellGreen);
        setCellTextWithForeground( table, 6,1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
//    "Выход \"Вскрытие\""
    if(1 == swp32.isInOpened()) {
        setCellColor( table, 6,3, cellRed);
        setCellTextWithForeground( table, 6,3, (QObject::tr("Есть[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(0 == swp32.isInOpened()) {
        setCellColor( table, 6,3, cellGreen);
        setCellTextWithForeground( table, 6,3, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }

    auto swp34 = selUN->swpTGType0x34();

    for(int ci = 0, n = 4; ci < n; ci++) {

        if(1 == swp34.C(ci + 1).isOffFlt1() && 1 == swp34.C(ci + 1).isOffFlt2() && 1 == swp34.C(ci + 1).isOffFlt3()) {
            setCellColor( table, (7 + 4 * ci),1, cellGray);
            setCellTextWithForeground( table, (7 + 4 * ci),1, (QObject::tr("Выкл")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        } else if(50001 == swp32.C(ci + 1).voltage()) {
            setCellColor( table, (7 + 4 * ci),1, cellBlue);
            setCellTextWithForeground( table, (7 + 4 * ci),1, (QObject::tr("Обрыв кабеля")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        } else if(50000 == swp32.C(ci + 1).voltage()) {
            setCellColor( table, (7 + 4 * ci),1, cellBlue);
            setCellTextWithForeground( table, (7 + 4 * ci),1, (QObject::tr("Замыкание кабеля")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        } else if(1 == swp32.C(ci + 1).isFault()) {
            setCellColor( table, (7 + 4 * ci),1, cellBlue);
            setCellTextWithForeground( table, (7 + 4 * ci),1, (QObject::tr("Неисправность")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        } else {
            setCellColor( table, (7 + 4 * ci),1, cellGreen);
            setCellTextWithForeground( table, (7 + 4 * ci),1, (QObject::tr("Норма")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }

//        "Фильтр%1: Сработка"
        if(1 == swp32.C(ci + 1).isInAlarmFlt1()) {
            setCellColor( table, (8 + 4 * ci),1, cellRed);
            setCellTextWithForeground( table, (8 + 4 * ci),1, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        } else if(0 == swp32.C(ci + 1).isInAlarmFlt1()) {
            setCellColor( table, (8 + 4 * ci),1, cellGreen);
            setCellTextWithForeground( table, (8 + 4 * ci),1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }

//        "Фильтр%2: Сработка"
        if(1 == swp32.C(ci + 1).isInAlarmFlt2()) {
            setCellColor( table, (9 + 4 * ci),1, cellRed);
            setCellTextWithForeground( table, (9 + 4 * ci),1, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        } else if(0 == swp32.C(ci + 1).isInAlarmFlt2()) {
            setCellColor( table, (9 + 4 * ci),1, cellGreen);
            setCellTextWithForeground( table, (9 + 4 * ci),1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }

//        "Фильтр%3: Сработка"
        if(1 == swp32.C(ci + 1).isInAlarmFlt3()) {
            setCellColor( table, (10 + 4 * ci),1, cellRed);
            setCellTextWithForeground( table, (10 + 4 * ci),1, (QObject::tr("Было[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        } else if(0 == swp32.C(ci + 1).isInAlarmFlt3()) {
            setCellColor( table, (10 + 4 * ci),1, cellGreen);
            setCellTextWithForeground( table, (10 + 4 * ci),1, (QObject::tr("Нет[0]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }

//        "Фильтр%3: Уровень"
        if(-1.0 != swp32.C(ci + 1).voltage()) {
            setCellColor( table, (8 + 4 * ci),3, cellGray);
            setCellTextWithForeground( table, (8 + 4 * ci),3, (QString::number(swp32.C(ci + 1).voltage())), QBrush(QColor(0xFF, 0xFF, 0xFF)));

            setCellColor( table, (9 + 4 * ci),3, cellGray);
            setCellTextWithForeground( table, (9 + 4 * ci),3, (QString::number(swp32.C(ci + 1).voltage())), QBrush(QColor(0xFF, 0xFF, 0xFF)));

            setCellColor( table, (10 + 4 * ci),3, cellGray);
            setCellTextWithForeground( table, (10 + 4 * ci),3, (QString::number(swp32.C(ci + 1).voltage())), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }


        //"Фильтр%1: Пороги"
        if(-1.0 != swp34.C(ci + 1).thresholdFlt1()) {
            setCellColor( table, (8 + 4 * ci),5, cellGray);
            setCellTextWithForeground( table, (8 + 4 * ci),5, (QString::number(swp34.C(ci + 1).thresholdFlt1())), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }

        //"Фильтр%2: Пороги"
        if(-1.0 != swp34.C(ci + 1).thresholdFlt2()) {
            setCellColor( table, (9 + 4 * ci),5, cellGray);
            setCellTextWithForeground( table, (9 + 4 * ci),5, (QString::number(swp34.C(ci + 1).thresholdFlt2())), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }

        //"Фильтр%3: Пороги"
        if(-1.0 != swp34.C(ci + 1).thresholdFlt3()) {
            setCellColor( table, (10 + 4 * ci),5, cellGray);
            setCellTextWithForeground( table, (10 + 4 * ci),5, (QString::number(swp34.C(ci + 1).thresholdFlt3())), QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }
    }

    // fill <--
}

void Utils::fillDiagnosticTableDD_T4K_M(QTableWidget * const table, const QSharedPointer<UnitNode> /*selUN*/)
{
    // prepare -->
    table->setRowCount(14);
    table->setColumnCount(4);

    for(int i = 0, n = 14; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            setCellColor( table, i, j, cellGray);
            if(0 != i && 0 != j && 2 != j)
                setCellTextWithForeground( table, i, j, "?", QBrush(QColor(0xFF, 0xFF, 0xFF)));

        }
    }

    setCellTextWithForeground( table, 0,0, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 0,1, (QObject::tr("Значение")));
    setCellTextWithForeground( table, 0,2, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 0,3, (QObject::tr("Значение")));

    setCellTextWithForeground( table, 1,0, (QObject::tr("Готовность БОД")));


    for(int i = 0, n = 5; i < n; i++) {
        setCellTextWithForeground( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        setCellTextWithForeground( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    setCellTextWithForeground( table, 10,0, (QObject::tr("Выход \"ДК\"")));
    setCellTextWithForeground( table, 11,0, (QObject::tr("Состояние \"ДК\" было")));
    setCellTextWithForeground( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")));
    setCellTextWithForeground( table, 13,0, (QObject::tr("Вскрытие БО было")));

    setCellTextWithForeground( table, 1,2, (QObject::tr("Сработка по ЧЭ1 было")));
    setCellTextWithForeground( table, 2,2, (QObject::tr("Сработка по ЧЭ2 было")));
    setCellTextWithForeground( table, 3,2, (QObject::tr("Обрыв по ЧЭ1 есть")));
    setCellTextWithForeground( table, 4,2, (QObject::tr("Замыкание по ЧЭ1 есть")));
    setCellTextWithForeground( table, 5,2, (QObject::tr("Обрыв по ЧЭ2 есть")));
    setCellTextWithForeground( table, 6,2, (QObject::tr("Замыкание по ЧЭ2 есть")));
    setCellTextWithForeground( table, 7,2, (QObject::tr("Неисправность ДД")));
    setCellTextWithForeground( table, 8,2, (QObject::tr("Обрыв связи с ДД есть")));
    setCellTextWithForeground( table, 9,2, (QObject::tr("Обрыв связи с ДД был")));
    setCellTextWithForeground( table, 10,2, (QObject::tr("Вскрытие ДД есть")));
    setCellTextWithForeground( table, 11,2, (QObject::tr("Вскрытие ДД был")));
    setCellTextWithForeground( table, 12,2, (QObject::tr("Уровень Сигнала ЧЭ1")));
    setCellTextWithForeground( table, 13,2, (QObject::tr("Уровень Сигнала ЧЭ2")));


    // prepare <--
    // fill -->
    // fill <--
}

void Utils::fillDiagnosticTableDD_SOTA(QTableWidget * const table, const QSharedPointer<UnitNode> /*selUN*/)
{
    // prepare -->
    table->setRowCount(14);
    table->setColumnCount(4);

    for(int i = 0, n = 14; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            setCellColor( table, i, j, cellGray);
            if(0 != i && 0 != j && 2 != j)
                setCellTextWithForeground( table, i, j, "?", QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }
    }

    setCellTextWithForeground( table, 0,0, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 0,1, (QObject::tr("Значение")));
    setCellTextWithForeground( table, 0,2, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 0,3, (QObject::tr("Значение")));

    setCellTextWithForeground( table, 1,0, (QObject::tr("Готовность БОД")));


    for(int i = 0, n = 5; i < n; i++) {
        setCellTextWithForeground( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        setCellTextWithForeground( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    setCellTextWithForeground( table, 10,0, (QObject::tr("Выход \"ДК\"")));
    setCellTextWithForeground( table, 11,0, (QObject::tr("Состояние \"ДК\" было")));
    setCellTextWithForeground( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")));
    setCellTextWithForeground( table, 13,0, (QObject::tr("Вскрытие БО было")));

    setCellTextWithForeground( table, 1,2, (QObject::tr("Сработка было")));
    setCellTextWithForeground( table, 2,2, (QObject::tr("Обрыв связи с ДД есть")));
    setCellTextWithForeground( table, 3,2, (QObject::tr("Обрыв связи с ДД был")));
    setCellTextWithForeground( table, 4,2, (QObject::tr("Вскрытие ДД есть")));
    setCellTextWithForeground( table, 5,2, (QObject::tr("Неисправность ДД есть")));
    setCellTextWithForeground( table, 6,2, (QObject::tr("Тревога по Ф1 есть")));
    setCellTextWithForeground( table, 7,2, (QObject::tr("Тревога поФ2 есть")));
    setCellTextWithForeground( table, 8,2, (QObject::tr("Опрос ДД")));
    setCellTextWithForeground( table, 9,2, (QObject::tr("Уровень Сигнала")));
    for(int i = 0, n = 5; i < n; i++) {
        setCellTextWithForeground( table, 10 + i,2, (QObject::tr("")));
    }


    // prepare <--
    // fill -->
    // fill <--
}

void Utils::fillDiagnosticTableY4_SOTA(QTableWidget * const table, const QSharedPointer<UnitNode> /*selUN*/)
{
    // prepare -->
    table->setRowCount(20);
    table->setColumnCount(53);

    for(int i = 0, n = 20; i < n; i++) {
        for(int j = 0, m = 53; j < m; j++) {
            setCellColor( table, i, j, cellGray);
            if(nullptr == table->item(i, j)) {
                setCellTextWithForeground( table, i, j, "");
            }

        }
    }

    setCellTextWithForeground( table, 0,0, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 0,1, (QObject::tr("Значение")));
    setCellTextWithForeground( table, 0,2, (QObject::tr("Параметр")));

    setCellTextWithForeground( table, 1,0, (QObject::tr("Готовность БОД")));


    for(int i = 0, n = 4; i < n; i++) {
        setCellTextWithForeground( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        setCellTextWithForeground( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    setCellTextWithForeground( table, 10,0, (QObject::tr("Выход \"ДК\"")));
    setCellTextWithForeground( table, 11,0, (QObject::tr("Состояние \"ДК\" было")));
    setCellTextWithForeground( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")));
    setCellTextWithForeground( table, 13,0, (QObject::tr("Вскрытие БО было")));

    setCellTextWithForeground( table, 1,2, (QObject::tr("Участки 1-2")));
    setCellTextWithForeground( table, 11,2, (QObject::tr("Участки 3-4")));

    int dec[] = {2,6,12,16};
    for(int i = 0, n = 4; i < n; i++) {
        setCellTextWithForeground( table, dec[i] + 0,2, (QObject::tr("ДД")));
        setCellTextWithForeground( table, dec[i] + 1,2, (QObject::tr("Сработка ДД было")));
        setCellTextWithForeground( table, dec[i] + 2,2, (QObject::tr("Обрыв связи с ДД есть")));
        setCellTextWithForeground( table, dec[i] + 3,2, (QObject::tr("Обрыв связи с ДД был")));
    }

    for(int i = 0, n = 50; i < n; i++) {
        setCellTextWithForeground( table, dec[0],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
        setCellTextWithForeground( table, dec[1],3 + i, (QString("%1").arg(i + 1 + 50, 2, 10, QLatin1Char('0'))));
        setCellTextWithForeground( table, dec[2],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
        setCellTextWithForeground( table, dec[3],3 + i, (QString("%1").arg(i + 1 + 50, 2, 10, QLatin1Char('0'))));
    }


    // prepare <--

    // fill -->
    // fill <--
}

void Utils::fillDiagnosticTableY4_T4K_M(QTableWidget * const table, const QSharedPointer<UnitNode> /*selUN*/)
{
    // prepare -->
    table->setRowCount(22);
    table->setColumnCount(29);

    for(int i = 0, n = 22; i < n; i++) {
        for(int j = 0, m = 29; j < m; j++) {
            QTableWidgetItem * item = table->item(i, j);
            if(nullptr == item) {
                setCellTextWithForeground( table, i, j, "");
            }

            setCellColor(table, i, j, cellGray);
        }
    }

    setCellTextWithForeground( table, 0,0, (QObject::tr("Параметр")));
    setCellTextWithForeground( table, 0,1, (QObject::tr("Значение")));
    setCellTextWithForeground( table, 0,2, (QObject::tr("Параметр")));

    setCellTextWithForeground( table, 1,0, (QObject::tr("Готовность БОД")));


    for(int i = 0, n = 4; i < n; i++) {
        setCellTextWithForeground( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)));
        setCellTextWithForeground( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)));
    }

    setCellTextWithForeground( table, 10,0, (QObject::tr("Выход \"ДК\"")));
    setCellTextWithForeground( table, 11,0, (QObject::tr("Состояние \"ДК\" было")));
    setCellTextWithForeground( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")));
    setCellTextWithForeground( table, 13,0, (QObject::tr("Вскрытие БО было")));

    setCellTextWithForeground( table, 1,2, (QObject::tr("Участки 1-2")));
    setCellTextWithForeground( table, 12,2, (QObject::tr("Участки 3-4")));

    int dec[] = {2,13};
    for(int i = 0, n = 2; i < n; i++) {
        setCellTextWithForeground( table, dec[i] + 0,2, (QObject::tr("ДДискретный")));
        setCellTextWithForeground( table, dec[i] + 1,2, (QObject::tr("Сработка по ЧЭ1 было")));
        setCellTextWithForeground( table, dec[i] + 2,2, (QObject::tr("Сработка по ЧЭ2 было")));
        setCellTextWithForeground( table, dec[i] + 3,2, (QObject::tr("Неисправность по ЧЭ1 есть")));
        setCellTextWithForeground( table, dec[i] + 4,2, (QObject::tr("Неисправность по ЧЭ2 есть")));
        setCellTextWithForeground( table, dec[i] + 5,2, (QObject::tr("Обрыв связи с ДД есть")));
        setCellTextWithForeground( table, dec[i] + 6,2, (QObject::tr("Обрыв связи с ДД был")));
        setCellTextWithForeground( table, dec[i] + 7,2, (QObject::tr("Вскрытие ДД есть")));
        setCellTextWithForeground( table, dec[i] + 8,2, (QObject::tr("Вскрытие ДД было")));
    }

    for(int i = 0, n = 26; i < n; i++) {
        setCellTextWithForeground( table, dec[0],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
        setCellTextWithForeground( table, dec[1],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))));
    }


    // prepare <--

    // fill -->
    // fill <--
}

QSet<QSharedPointer<UnitNode> > Utils::findeSetAutoOnOffUN(QSharedPointer<UnitNode> un)
{
    QSet<QSharedPointer<UnitNode> > unSetTmp;
    if(TypeUnitNode::IU_BL_IP != un->getType()) {
        return unSetTmp;
    }
    unSetTmp.insert(un);
    unSetTmp = unSetTmp + un->getDoubles();
    for(const auto& unDouble : unSetTmp.values()) {
//        //qDebug() << "itr :" << unSetTmp;
//        //qDebug() << "fnd :" << unDouble << unDouble->getMetaNames() << unDouble->getName();
        if(!unDouble->treeParent().isNull()) {
            if(TypeUnitNode::SD_BL_IP == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()) {
//                //qDebug() << "trg :"<< unDouble->getMetaNames() << unDouble->toString();
            } else {
                unSetTmp.remove(unDouble);
            }
        } else {
            unSetTmp.remove(unDouble);
        }
    }
//    //qDebug() << "res :" << unSetTmp;
    return unSetTmp;
}

QSize Utils::getQTableWidgetContentSize(QTableWidget * const table)
{
    int w = table->verticalHeader()->width() + 4; // +4 seems to be needed
    for (int i = 0; i < table->columnCount(); i++)
       w += table->columnWidth(i); // seems to include gridline (on my machine)
    int h = table->horizontalHeader()->height() + 4;
    for (int i = 0; i < table->rowCount(); i++)
       h += table->rowHeight(i);
    return QSize(w, h);
}


char Utils::reverseBits( char number )
{
   int G_bitsInByte = 8;
   int bytes = sizeof( char );
   int bits = bytes * G_bitsInByte;
   char result = 0;
   while( bits > 0 )
   {
      result |= ( number & 1 ) << ( bits - 1 );
      number >>= 1;
      --bits;
   }

   return result;
}

QByteArray Utils::xorCrypt(const QByteArray in, const QByteArray key)
{
   QByteArray out;
   for (int x = 0; x < in.size(); x++) {
      out.append((static_cast<quint8>(in.at(x)) ^ static_cast<quint8>(key.at((x + 1) % key.size())) * static_cast<quint8>(2)));
   }
   return out;
}

QString Utils::xorCrypt(const QString in, const QString key)
{
    return QString::fromLatin1(Utils::xorCrypt(in.toLatin1(),  key.toLatin1()));
}

QString Utils::XOR_Crypt(QString src)
{
    QByteArray ar=src.toLocal8Bit();
    QString key="start7";
    QByteArray pw=key.toLocal8Bit();

    QByteArray res;
    res.clear();
    for (int x=1; x < ar.size() + 1; x++) {
        int val1=  pw[(x)%pw.size()] * 2;
        int inx=ar[x-1];
        int val2= inx ^ val1;
        char chr = (char)val2;
        res.append(chr);
    }
    QString str_res = QString::fromLocal8Bit(res);
    return str_res;
}
