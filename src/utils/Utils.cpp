#include "Utils.h"
#include <random>
#include <QTableWidget>
#include <QHeaderView>
#include <QHostAddress>
#include "ServerSettingUtils.h"
#include "SignalSlotCommutator.h"
#include "global.h"
#include "UnitNode.h"
#include "swpblip/SWPBLIPType0x41.h"
#include "swpssoiblip/SWPSSOIBLIPType0x41.h"
#include "swprlm/SWPRLMType0x31.h"
#include "swprlmc/SWPRLMCType0x31.h"
#include "swpblip/SWPSDBLIPType0x41.h"
#include "swpblip/SWPSDBLIPType0x42.h"
#include "swpblip/SWPIUBLIPType0x41.h"
#include "swptg/SWPTGType0x32.h"
#include "swptg/SWPTGSubType0x32.h"
#include "swptg/SWPTGType0x34.h"
#include "swptg/SWPTGSubType0x34.h"
#include "swpblip/SWPBLIPType0x42.h"
#include "swpt4k/SWPT4KBODType0x32.h"
#include "swpt4k/SWPT4KY4Type0x32.h"
#include "swpt4k/SWPT4KDDType0x32.h"
#include "swpt4k/SWPT4KDDCType0x32.h"

#include "swpt4k/SWPT4KBODType0x33.h"
#include "swpt4k/SWPT4KY4Type0x33.h"
#include "swpt4k/SWPT4KDDType0x33.h"
#include "swpt4k/SWPT4KDDCType0x33.h"
#include "swpt4k/SWPT4KDDCFType0x33.h"


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

uint8_t Utils::getByteSumm(QByteArray &ba, int bi, int ei) {
    if(-1 == ei) {
        ei = ba.size() - 1;
    }

    uint8_t sum = 0;
    for(; bi <= ei; bi++) {
        sum += static_cast<uint8_t>(ba.at(bi));
    }

    return sum;
}

QString Utils::typeUNToStr(const int type)
{
    switch (type) {
    case TypeUnitNodeEnum::GROUP:
        return QObject::tr("Группа"); //"Группа";
    case TypeUnitNodeEnum::SD_BL_IP:
        return QObject::tr("СД"); //"СД БЛ-IP";
    case TypeUnitNodeEnum::IU_BL_IP:
        return QObject::tr("ИУ"); //"ИУ БЛ-IP";
    case TypeUnitNodeEnum::TG:
        return QObject::tr("Точка/Гарда"); //"Точка-Гарда";
    case TypeUnitNodeEnum::RLM_KRL:
        return QObject::tr("РИФ-РЛМ"); //"РИФ-РЛМ(КРЛ), Трасса";
    case TypeUnitNodeEnum::RLM_C:
        return QObject::tr("РИФ-РЛМ-С"); //"РИФ-С";
    case TypeUnitNodeEnum::BOD_T4K_M:
        return QObject::tr("БОД Точка-М"); //"БОД Точка-М";
    case TypeUnitNodeEnum::Y4_T4K_M:
        return QObject::tr("Участок Точка-М"); //"Участок Точка-М";
    case TypeUnitNodeEnum::DD_T4K_M:
        return QObject::tr("ДД Точка-М"); //"ДД Точка-М";
    case TypeUnitNodeEnum::BOD_SOTA:
        return QObject::tr("БОД Сота-М"); //"БОД Сота-М";
    case TypeUnitNodeEnum::Y4_SOTA:
        return QObject::tr("Участок Сота-М"); //"Участок Сота-М";
    case TypeUnitNodeEnum::DD_SOTA:
        return QObject::tr("ДД Сота-М"); //"ДД Сота-М";
    case TypeUnitNodeEnum::BL_IP:
        return QObject::tr("БЛ-IP");
    case TypeUnitNodeEnum::SSOI_BL_IP:
        return QObject::tr("ССОИ БЛ-IP");
    case TypeUnitNodeEnum::SSOI_SD_BL_IP:
        return QObject::tr("СД");
    case TypeUnitNodeEnum::SSOI_IU_BL_IP:
        return QObject::tr("ИУ");
    default:
        return QObject::tr("БЛ-IP");
    }
}

QString Utils::baMsgToStr(const QByteArray ba)
{
    if(5 <= ba.size()) {
        if(static_cast<uint8_t>(0xFF) != static_cast<uint8_t>(ba.at(1)) &&
           static_cast<uint8_t>(0x00) == static_cast<uint8_t>(ba.at(3)) &&
           static_cast<uint8_t>(0x30) == static_cast<uint8_t>(ba.at(4)))
            return  QObject::tr("Подтверждение приема концентратором"); //"Подтверждение приема концентратором";
        else if(static_cast<uint8_t>(0xFF) != static_cast<uint8_t>(ba.at(1)) &&
                static_cast<uint8_t>(0x04) == static_cast<uint8_t>(ba.at(3)) &&
                static_cast<uint8_t>(0x41) == static_cast<uint8_t>(ba.at(4)))
            return  QObject::tr("Передача слов состояния концентратора"); //"Передача слов состояния концентратора";
    } else if(4 <= ba.size()) {
        if(static_cast<uint8_t>(0xFF) == static_cast<uint8_t>(ba.at(1)) &&
           static_cast<uint8_t>(0x00) == static_cast<uint8_t>(ba.at(2)) &&
           static_cast<uint8_t>(0x22) == static_cast<uint8_t>(ba.at(3)))
            return QObject::tr("Запрос состояния концентратора"); //"Запрос состояния концентратора";
        else if(static_cast<uint8_t>(0xFF) == static_cast<uint8_t>(ba.at(1)) &&
                static_cast<uint8_t>(0x00) == static_cast<uint8_t>(ba.at(2)) &&
                static_cast<uint8_t>(0x24) == static_cast<uint8_t>(ba.at(3)))
            return QObject::tr("Сброс флагов тревоги, ДК"); //"Сброс флагов тревоги, ДК";
        else if(static_cast<uint8_t>(0xFF) == static_cast<uint8_t>(ba.at(1)) &&
                static_cast<uint8_t>(0x01) == static_cast<uint8_t>(ba.at(2)) &&
                static_cast<uint8_t>(0x23) == static_cast<uint8_t>(ba.at(3)))
            return  QObject::tr("Управление ИУ"); //"Управление ИУ";
    } else if(1 == ba.size()) {
        if(static_cast<uint8_t>(0xFF) == static_cast<uint8_t>(ba.at(0)))
            return  QObject::tr("Включение"); //"Включение";
        else if(static_cast<uint8_t>(0x00) == static_cast<uint8_t>(ba.at(0)))
            return  QObject::tr("Выключение"); //"Выключение";
    }

    return ba.toHex();
}

bool Utils::isSavedMsg(const QByteArray ba) {

    if(5 <= ba.size()) {
        if(static_cast<uint8_t>(0xFF) != static_cast<uint8_t>(ba.at(1)) &&
           static_cast<uint8_t>(0x00) == static_cast<uint8_t>(ba.at(3)) &&
           static_cast<uint8_t>(0x30) == static_cast<uint8_t>(ba.at(4)))
            return true; //"Подтверждение приема концентратором";
        else if(static_cast<uint8_t>(0xFF) != static_cast<uint8_t>(ba.at(1)) &&
                static_cast<uint8_t>(0x04) == static_cast<uint8_t>(ba.at(3)) &&
                static_cast<uint8_t>(0x41) == static_cast<uint8_t>(ba.at(4)))
            return false; //"Передача слов состояния концентратора";
    } else if(4 <= ba.size()) {
        if(static_cast<uint8_t>(0xFF) == static_cast<uint8_t>(ba.at(1)) &&
           static_cast<uint8_t>(0x00) == static_cast<uint8_t>(ba.at(2)) &&
           static_cast<uint8_t>(0x22) == static_cast<uint8_t>(ba.at(3)))
            return false; //"Запрос состояния концентратора";
        else if(static_cast<uint8_t>(0xFF) == static_cast<uint8_t>(ba.at(1)) &&
                static_cast<uint8_t>(0x00) == static_cast<uint8_t>(ba.at(2)) &&
                static_cast<uint8_t>(0x24) == static_cast<uint8_t>(ba.at(3)))
            return true; //"Сброс флагов тревоги, ДК";
        else if(static_cast<uint8_t>(0xFF) == static_cast<uint8_t>(ba.at(1)) &&
                static_cast<uint8_t>(0x01) == static_cast<uint8_t>(ba.at(2)) &&
                static_cast<uint8_t>(0x23) == static_cast<uint8_t>(ba.at(3)))
            return true; //"Управление ИУ";
    } else if(1 == ba.size()) {
        if(static_cast<uint8_t>(0xFF) == static_cast<uint8_t>(ba.at(0)))
            return true; //"Включение";
        else if(static_cast<uint8_t>(0x00) == static_cast<uint8_t>(ba.at(0)))
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

    return table->item(row, column);
}

QTableWidgetItem *Utils::setCellTextWithForeground(QTableWidget * const table, const int row, const int column, const QString &text, const QBrush &foreground)
{
    auto item = setCellText(table, row, column, text);
    if(nullptr != item) {
        if((item->background().color() != cellGray && item->background().color() != cellLightGray) && foreground.color() != QColor(0x00, 0x00, 0x00)) {
            item->setForeground(foreground);
        } else {
            item->setForeground(QBrush(QColor(0x00, 0x00, 0x00)));
        }
//        QFont font = item->font();
//        if(foreground.color() != QColor(0x00, 0x00, 0x00)) {
//            font.setBold(true);
//        } else {
//            font.setBold(false);
//        }
//        item->setFont(font);
    }
    return item;
}

QTableWidgetItem *Utils::setCellForeground(QTableWidget * const table, const int row, const int column, const QBrush &foreground)
{
    if(row >= table->rowCount() || column >= table->columnCount())
        return nullptr;
    QTableWidgetItem * item = table->item(row, column);
    if(nullptr == item) {
        table->setItem(row, column, new QTableWidgetItem());
    }

    item = table->item(row, column);

    if(nullptr != item) {
        item->setForeground(foreground);
    }

    return item;
}

QTableWidgetItem *Utils::setCellBold(QTableWidget * const table, const int row, const int column, const bool bold)
{
    if(row >= table->rowCount() || column >= table->columnCount())
        return nullptr;
    QTableWidgetItem * item = table->item(row, column);
    if(nullptr == item) {
        table->setItem(row, column, new QTableWidgetItem());
    }

    item = table->item(row, column);
    if(nullptr != item) {
        QFont font = item->font();
        font.setBold(bold);
        item->setFont(font);
    }

    return item;
}

QTableWidgetItem *Utils::setCellTextBackgroundColorForegroundBold(QTableWidget * const table, const int row, const int column, const QString &text, const QColor &background, const QBrush &foreground, const bool bold)
{
    if(row >= table->rowCount() || column >= table->columnCount())
        return nullptr;
    QTableWidgetItem * item = table->item(row, column);
    if(nullptr == item) {
        table->setItem(row, column, new QTableWidgetItem());
    }

    item = table->item(row, column);

    if(nullptr != item) {
        item->setText(text);

        item->setBackground(QBrush(background));

        item->setForeground(foreground);

        QFont font = item->font();
        font.setBold(bold);
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
QColor Utils::cellGray = QColor(0xBF, 0xBF, 0xBF);
QColor Utils::cellLightGray = QColor(0xEF, 0xEF, 0xEF);
QColor Utils::cellYellow = QColor(0xFF, 0xDD, 0x0E);
QColor Utils::cellBlue = QColor(0x80, 0x9F, 0xFF);


void Utils::fillDiagnosticTable(QTableWidget * const table, const QSharedPointer<UnitNode> selUN)
{
    try {
        if(selUN.isNull() || nullptr == table)
            return;

        if(TypeUnitNodeEnum::RLM_KRL == selUN->getType())
            Utils::fillDiagnosticTableRLMKRL(table, selUN);
        else if(TypeUnitNodeEnum::RLM_C == selUN->getType())
            Utils::fillDiagnosticTableRLM_C(table, selUN);
        else if(TypeUnitNodeEnum::TG == selUN->getType())
            Utils::fillDiagnosticTableTG(table, selUN);
        else if(TypeUnitNodeEnum::DD_T4K_M == selUN->getType())
            Utils::fillDiagnosticTableDD_T4K_M(table, selUN);
        else if(TypeUnitNodeEnum::DD_SOTA == selUN->getType())
            Utils::fillDiagnosticTableDD_SOTA(table, selUN);
        else if(TypeUnitNodeEnum::Y4_SOTA == selUN->getType()
             || TypeUnitNodeEnum::BOD_SOTA == selUN->getType())
            Utils::fillDiagnosticTableY4_SOTA(table, selUN);
        else if(TypeUnitNodeEnum::BOD_T4K_M == selUN->getType()
             || TypeUnitNodeEnum::Y4_T4K_M == selUN->getType())
            Utils::fillDiagnosticTableY4_T4K_M(table, selUN);
        else if(TypeUnitNodeEnum::SD_BL_IP == selUN->getType()
             || TypeUnitNodeEnum::IU_BL_IP == selUN->getType())
            Utils::fillDiagnosticTableBLIP(table, selUN);
        else if(TypeUnitNodeEnum::SSOI_SD_BL_IP == selUN->getType()
             || TypeUnitNodeEnum::SSOI_IU_BL_IP == selUN->getType())
            Utils::fillDiagnosticTableSSOIBLIP(table, selUN);

    } catch (...) {
        //qDebug() << "fillDiagnosticTable catch exception ...";
    }
}

void Utils::fillDiagnosticTableSSOIBLIP(QTableWidget * const table, const QSharedPointer<UnitNode> selUN) {
    QSharedPointer<UnitNode>  parent = selUN->getParentUN();
    if((TypeUnitNodeEnum::SSOI_SD_BL_IP == selUN->getType()
     || TypeUnitNodeEnum::SSOI_IU_BL_IP == selUN->getType())
    && nullptr != parent) {
        while(TypeUnitNodeEnum::SSOI_BL_IP != parent->getType()) {
            parent = parent->getParentUN();
            if(nullptr == parent)
                return;
        }
    } else {
        return;
    }

    // prepare -->
    table->setRowCount(16);
    table->setColumnCount(3);

    for(int j = 0, m = table->columnCount(); j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        for(int i = 0, n = table->rowCount(); i < n; i++) {
            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->setColumnWidth(0, 90);
    table->setColumnWidth(1, 90);
    table->setColumnWidth(2, 90);

//    table->setColumnWidth(0, 60);
//    table->setColumnWidth(1, 150);
//    table->setColumnWidth(3, 150);
    for(int i = 0, n = table->columnCount(); i < n; i++)
        for(int j = 0, m = table->rowCount(); j < m; j++) {
            if(2 == i && 11 < j) {
                setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            } else {
                setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            }
        }

    for(int i = 1, n = table->columnCount(); i < n; i++) {
        for(int j = 1, m = table->rowCount(); j < m; j++) {
            if(9 == j)
                continue;
            else if(2 == i && 11 < j)
                continue;
            setCellTextWithForeground( table, j, i, "?", QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }
    }

    setCellTextBackgroundColorForegroundBold( table, 0,0, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("Параметр"));
    setCellTextBackgroundColorForegroundBold( table, 0,1, (QObject::tr("Вход")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("Вход"));
    setCellTextBackgroundColorForegroundBold( table, 0,2, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("Статус"));

    setCellTextBackgroundColorForegroundBold( table, 1,0, (QObject::tr("СД1")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД1"));
    setCellTextBackgroundColorForegroundBold( table, 2,0, (QObject::tr("СД2")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД2"));
    setCellTextBackgroundColorForegroundBold( table, 3,0, (QObject::tr("СД3")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД3"));
    setCellTextBackgroundColorForegroundBold( table, 4,0, (QObject::tr("СД4")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД4"));
    setCellTextBackgroundColorForegroundBold( table, 5,0, (QObject::tr("СД5")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД5"));
    setCellTextBackgroundColorForegroundBold( table, 6,0, (QObject::tr("СД6")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД6"));
    setCellTextBackgroundColorForegroundBold( table, 7,0, (QObject::tr("СД7")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД7"));
    setCellTextBackgroundColorForegroundBold( table, 8,0, (QObject::tr("СД8")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД8"));

    setCellTextBackgroundColorForegroundBold( table, 9,0, (""), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 9,1, (QObject::tr("Выход")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("Выход"));
    setCellTextBackgroundColorForegroundBold( table, 9,2, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("Статус"));

    setCellTextBackgroundColorForegroundBold( table, 10,0, (QObject::tr("ДК")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ДК"));
    setCellTextBackgroundColorForegroundBold( table, 11,0, (QObject::tr("Вскрытие")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ДК"));
    setCellTextBackgroundColorForegroundBold( table, 12,0, (QObject::tr("ИУ1")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ИУ1"));
    setCellTextBackgroundColorForegroundBold( table, 13,0, (QObject::tr("ИУ2")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ИУ2"));
    setCellTextBackgroundColorForegroundBold( table, 14,0, (QObject::tr("ИУ3")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ИУ3"));
    setCellTextBackgroundColorForegroundBold( table, 15,0, (QObject::tr("ИУ4")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ИУ4"));




    // prepare <--

    // fill -->

    const auto& swpBLIP = parent->swpSSOIBLIPType0x41();
    if(TypeUnitNodeEnum::SSOI_BL_IP == parent->getType()) {
        int row = 10;

        if(1 == swpBLIP.isWasDK()) {
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Было")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else {//if(status2 & Status::Not) {
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Нет")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }

        if(1 == swpBLIP.isExistDK()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Есть")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == parent->swpBLIPType0x41().isExistDK()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Нет")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }
    }

    if(TypeUnitNodeEnum::SSOI_BL_IP == parent->getType()) {
        int row = 11;

        if(1 == swpBLIP.isWasOpened()) {
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Было")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else {//if(status2 & Status::Not) {
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Нет")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }

        if(1 == swpBLIP.isInOpened()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Есть")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == parent->swpSSOIBLIPType0x41().isInOpened()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Нет")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }
    }

    for(int indexSD = 0, countSD = 8; indexSD < countSD; indexSD++) {
        const auto& swpSD = swpBLIP.sd(indexSD + 1);
        int row = indexSD + 1;

        if(1 == swpSD.isAlarm()) {
            const auto swpSD42 = parent->swpBLIPType0x42().sd(indexSD + 1);
            if(swpSD42.isNull()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Тревога")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
            } else if(1 == swpSD42.isLineBreak() && 1 == swpSD42.isInAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Обрыв")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
            } else if(1 == swpSD42.isShortCircuit() && 1 == swpSD42.isInAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Замыкание")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
            } else {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Тревога")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
            }
        }
        else if(1 == swpSD.isNorm()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Норма")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Норма"
        }

        if(1 == swpSD.isWasAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Было")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Было"
        } else if(0 == swpSD.isWasAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Нет")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Нет"
        }

        if(1 == swpSD.isOff())
        {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("-")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Выкл")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    for(int indexIU = 0, countIU = 8; indexIU < countIU; indexIU++) {
        const auto& swpIU = swpBLIP.sd(indexIU + 1);
        int row = indexIU + 1 + 11;

        if(1 == swpIU.isOn()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Вкл")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        } else if(1 == swpIU.isOff()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Выкл")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    const auto& tmpLs = parent->getListChilde();
    for(const auto& un : tmpLs) {
        if(TypeUnitNodeEnum::SSOI_SD_BL_IP != un->getType()
        && TypeUnitNodeEnum::SSOI_IU_BL_IP != un->getType()) {
            continue;
        }

        if (10 == un->getPublishedState()) {
            for(int i = 1, n = table->columnCount(); i < n; i++) {
                for(int j = 1, m = table->rowCount(); j < m; j++) {
                    if(9 == j) {
                        continue;
                    } else if(2 == i && 11 < j) {
                        continue;
                    }
                    setCellTextBackgroundColorForegroundBold( table, j, i, (QObject::tr("Нет связи!")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
                }
            }
            return;
        }

        int row = -1;

        if(un->getStateWord(0x41u).getByteWord().isEmpty()) {
            if(TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()) {
                row = un->getNum2();
            } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()) {
                row = 11 + un->getNum2();
            }
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Нет связи!")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Норма"
        } else if(TypeUnitNodeEnum::SSOI_SD_BL_IP == un->getType()) {
            row = un->getNum2();
            if(1 == un->swpSDBLIPType0x41().isAlarm()) {
                auto swp = un->swpSDBLIPType0x42();
                if(swp.isNull()) {
                    setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Тревога")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
                } else if(1 == swp.isLineBreak() && 1 == swp.isInAlarm()) {
                    setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Обрыв")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
                } else if(1 == swp.isShortCircuit() && 1 == swp.isInAlarm()) {
                    setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Замыкание")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
                } else {
                    setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Тревога")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
                }
            }
            else if(1 == un->swpSDBLIPType0x41().isNorm()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Норма")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Норма"
            }

            if(1 == un->swpSDBLIPType0x41().isWasAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Было")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Было"
            } else if(0 == un->swpSDBLIPType0x41().isWasAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Нет")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Нет"
            }

            if(1 == un->swpSDBLIPType0x41().isOff())
            {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("-")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
                setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Выкл")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            }

        } else if(TypeUnitNodeEnum::SSOI_IU_BL_IP == un->getType()) {
            row = 11 + un->getNum2();
            if(1 == un->swpIUBLIPType0x41().isOn()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Вкл")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
                setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            } else if(1 == un->swpIUBLIPType0x41().isOff()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Выкл")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
                setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            }

        }
    }
    // fill <--
}


void Utils::fillDiagnosticTableBLIP(QTableWidget * const table, const QSharedPointer<UnitNode> selUN) {
    QSharedPointer<UnitNode>  parent = selUN->getParentUN();
    if((TypeUnitNodeEnum::SD_BL_IP == selUN->getType() ||
            TypeUnitNodeEnum::IU_BL_IP == selUN->getType()) &&
            nullptr != parent) {
        while(TypeUnitNodeEnum::BL_IP != parent->getType()) {
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

    for(int j = 0, m = table->columnCount(); j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        for(int i = 0, n = table->rowCount(); i < n; i++) {
            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->setColumnWidth(0, 90);
    table->setColumnWidth(1, 90);
    table->setColumnWidth(2, 90);

//    table->setColumnWidth(0, 60);
//    table->setColumnWidth(1, 150);
//    table->setColumnWidth(3, 150);
    for(int i = 0, n = table->columnCount(); i < n; i++)
        for(int j = 0, m = table->rowCount(); j < m; j++) {
            if(2 == i && 10 < j) {
                setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            } else {
                setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            }
        }

    for(int i = 1, n = 3; i < n; i++) {
        for(int j = 1, m = 15; j < m; j++) {
            if(9 == j)
                continue;
            else if(2 == i && 10 < j)
                continue;
            setCellTextWithForeground( table, j, i, "?", QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }
    }

    setCellTextBackgroundColorForegroundBold( table, 0,0, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("Параметр"));
    setCellTextBackgroundColorForegroundBold( table, 0,1, (QObject::tr("Вход")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("Вход"));
    setCellTextBackgroundColorForegroundBold( table, 0,2, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("Статус"));

    setCellTextBackgroundColorForegroundBold( table, 1,0, (QObject::tr("СД1")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД1"));
    setCellTextBackgroundColorForegroundBold( table, 2,0, (QObject::tr("СД2")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД2"));
    setCellTextBackgroundColorForegroundBold( table, 3,0, (QObject::tr("СД3")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД3"));
    setCellTextBackgroundColorForegroundBold( table, 4,0, (QObject::tr("СД4")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД4"));
    setCellTextBackgroundColorForegroundBold( table, 5,0, (QObject::tr("СД5")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД5"));
    setCellTextBackgroundColorForegroundBold( table, 6,0, (QObject::tr("СД6")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД6"));
    setCellTextBackgroundColorForegroundBold( table, 7,0, (QObject::tr("СД7")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД7"));
    setCellTextBackgroundColorForegroundBold( table, 8,0, (QObject::tr("СД8")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("СД8"));

    setCellTextBackgroundColorForegroundBold( table, 9,0, (""), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 9,1, (QObject::tr("Выход")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("Выход"));
    setCellTextBackgroundColorForegroundBold( table, 9,2, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("Статус"));

    setCellTextBackgroundColorForegroundBold( table, 10,0, (QObject::tr("ДК")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ДК"));
    setCellTextBackgroundColorForegroundBold( table, 11,0, (QObject::tr("ИУ1")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ИУ1"));
    setCellTextBackgroundColorForegroundBold( table, 12,0, (QObject::tr("ИУ2")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ИУ2"));
    setCellTextBackgroundColorForegroundBold( table, 13,0, (QObject::tr("ИУ3")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ИУ3"));
    setCellTextBackgroundColorForegroundBold( table, 14,0, (QObject::tr("ИУ4")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true); // ("ИУ4"));




    // prepare <--

    // fill -->

    const auto& swpBLIP = parent->swpBLIPType0x41();
    if(TypeUnitNodeEnum::BL_IP == parent->getType()) {
        int row = 10;

        if(1 == swpBLIP.isWasDK()) {
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Было")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else {//if(status2 & Status::Not) {
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Нет")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }

        if(1 == swpBLIP.isExistDK()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Есть")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == parent->swpBLIPType0x41().isExistDK()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Нет")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }
    }

    for(int indexSD = 0, countSD = 8; indexSD < countSD; indexSD++) {
        const auto& swpSD = swpBLIP.sd(indexSD + 1);
        int row = indexSD + 1;

        if(1 == swpSD.isAlarm()) {
            const auto swpSD42 = parent->swpBLIPType0x42().sd(indexSD + 1);
            if(swpSD42.isNull()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Тревога")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
            } else if(1 == swpSD42.isLineBreak() && 1 == swpSD42.isInAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Обрыв")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
            } else if(1 == swpSD42.isShortCircuit() && 1 == swpSD42.isInAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Замыкание")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
            } else {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Тревога")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
            }
        }
        else if(1 == swpSD.isNorm()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Норма")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Норма"
        }

        if(1 == swpSD.isWasAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Было")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Было"
        } else if(0 == swpSD.isWasAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Нет")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Нет"
        }

        if(1 == swpSD.isOff())
        {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("-")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Выкл")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    for(int indexIU = 0, countIU = 8; indexIU < countIU; indexIU++) {
        const auto& swpIU = swpBLIP.sd(indexIU + 1);
        int row = indexIU + 1 + 10;

        if(1 == swpIU.isOn()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Вкл")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        } else if(1 == swpIU.isOff()) {
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Выкл")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    const auto& tmpLs = parent->getListChilde();
    for(const auto& un : tmpLs) {
        if(TypeUnitNodeEnum::SD_BL_IP != un->getType() && TypeUnitNodeEnum::IU_BL_IP != un->getType()) {
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
                    setCellTextBackgroundColorForegroundBold( table, j, i, (QObject::tr("Нет связи!")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
                }
            }
            return;
        }

        int row = -1;

        if(un->getStateWord(0x41u).getByteWord().isEmpty()) {
            if(TypeUnitNodeEnum::SD_BL_IP == un->getType()) {
                row = un->getNum2();
            } else if(TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
                row = 10 + un->getNum2();
            }
            setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Нет связи!")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Норма"
        } else if(TypeUnitNodeEnum::SD_BL_IP == un->getType()) {
            row = un->getNum2();
            if(1 == un->swpSDBLIPType0x41().isAlarm()) {
                auto swp = un->swpSDBLIPType0x42();
                if(swp.isNull()) {
                    setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Тревога")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
                } else if(1 == swp.isLineBreak() && 1 == swp.isInAlarm()) {
                    setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Обрыв")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
                } else if(1 == swp.isShortCircuit() && 1 == swp.isInAlarm()) {
                    setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Замыкание")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
                } else {
                    setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Тревога")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Тревога"
                }
            }
            else if(1 == un->swpSDBLIPType0x41().isNorm()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Норма")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Норма"
            }

            if(1 == un->swpSDBLIPType0x41().isWasAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Было")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Было"
            } else if(0 == un->swpSDBLIPType0x41().isWasAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Нет")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false); // "Нет"
            }

            if(1 == un->swpSDBLIPType0x41().isOff())
            {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("-")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
                setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("Выкл")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            }

        } else if(TypeUnitNodeEnum::IU_BL_IP == un->getType()) {
            row = 10 + un->getNum2();
            if(1 == un->swpIUBLIPType0x41().isOn()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Вкл")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
                setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            } else if(1 == un->swpIUBLIPType0x41().isOff()) {
                setCellTextBackgroundColorForegroundBold( table, row, 1, (QObject::tr("Выкл")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
                setCellTextBackgroundColorForegroundBold( table, row, 2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
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

    for(int j = 0, m = table->columnCount(); j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        for(int i = 0, n = table->rowCount(); i < n; i++) {
            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->setColumnWidth(0, 120);
    table->setColumnWidth(1, 100);
    table->setColumnWidth(2, 100);

    setCellTextBackgroundColorForegroundBold( table, 0,0, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,1, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,2, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 1,0, (QObject::tr("Датчик")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 2,0, (QObject::tr("Срабатывание")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 3,0, (QObject::tr("Уровень")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 4,0, (QObject::tr("")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 4,1, (QObject::tr("Выход")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 4,2, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 5,0, (QObject::tr("Тревога")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 6,0, (QObject::tr("")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 6,1, (QObject::tr("Вход")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 6,2, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 7,0, (QObject::tr("ДК")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 8,0, (QObject::tr("Вскрытие")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    // prepare <--

    // fill -->

    if(10 == un->getPublishedState()) {
        for(int i = 1, n = table->columnCount(); i < n; i++) {
            for(int j = 1, m = table->rowCount(); j < m; j++) {
                if(1 == j && 2 == i) {
                    continue;
                } else if(2 == j && 1 == i) {
                    continue;
                } else if(4 == j) {
                    continue;
                } else if(6 == j) {
                    continue;
                } else if(3 == j && 2 == i) {
                    continue;
                }
                setCellTextBackgroundColorForegroundBold( table, j, i, (QObject::tr("Нет связи!")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }
        }
        return;
    }

    //"Датчик"
    if(1 == un->swpRLMType0x31().isOn()) {
        setCellTextBackgroundColorForegroundBold( table, 1, 1, (QObject::tr("Вкл[1]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(1 == un->swpRLMType0x31().isOff()) {
        setCellTextBackgroundColorForegroundBold( table, 1, 1, (QObject::tr("Выкл[0]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Срабатывание"
    if(1 == un->swpRLMType0x31().isOutAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 2, 2, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMType0x31().isOutAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 2, 2, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Уровень"
    if(-1.0 != un->swpRLMType0x31().voltage()) {
        setCellTextBackgroundColorForegroundBold( table, 3, 1, (QString::number(un->swpRLMType0x31().voltage(), 'f', 2)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
    }
    //"Выход \"Тревога\""
    if(1 == un->swpRLMType0x31().isInAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 1, (QObject::tr("Да[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMType0x31().isInAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Статус \"Тревога\""
    if(1 == un->swpRLMType0x31().isWasAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 2, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMType0x31().isWasAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 2, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Вход \"ДК\""
    if(1 == un->swpRLMType0x31().isExistDK()) {
        setCellTextBackgroundColorForegroundBold( table, 7, 1, (QObject::tr("Есть[1]")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMType0x31().isExistDK()) {
        setCellTextBackgroundColorForegroundBold( table, 7, 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Статус \"ДК\""
    if(1 == un->swpRLMType0x31().isWasDK()) {
        setCellTextBackgroundColorForegroundBold( table, 7, 2, (QObject::tr("Было[1]")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMType0x31().isWasDK()) {
        setCellTextBackgroundColorForegroundBold( table, 7, 2, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Вход \"Вскрытие\""
    if(1 == un->swpRLMType0x31().isInOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 8, 1, (QObject::tr("Есть[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMType0x31().isInOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 8, 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Статус \"Вскрытие\""
    if(1 == un->swpRLMType0x31().isWasOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 8, 2, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMType0x31().isWasOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 8, 2, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    // fill <--
}

void Utils::fillDiagnosticTableRLM_C(QTableWidget *table, const QSharedPointer<UnitNode> un)
{
    // prepare -->
    table->setRowCount(13);
    table->setColumnCount(3);

    for(int j = 0, m = table->columnCount(); j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        for(int i = 0, n = table->rowCount(); i < n; i++) {
            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->setColumnWidth(0, 180);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 100);

    setCellTextBackgroundColorForegroundBold( table,  0,0, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  0,1, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  0,2, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table,  1,0, (QObject::tr("Датчик")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  2,0, (QObject::tr("Срабатывание")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table,  3,0, (QObject::tr("Синхронизация")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  4,0, (QObject::tr("Низкий ровень")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  5,0, (QObject::tr("Уровень")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  6,0, (QObject::tr("Пороги")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  7,0, (QObject::tr("Период тактирования")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  8,0, (QObject::tr("Режим обработки")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table,  9,0, (QObject::tr("")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  9,1, (QObject::tr("Выход")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  9,2, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 10,0, (QObject::tr("Тревога")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 11,0, (QObject::tr("")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 11,1, (QObject::tr("Вход")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 11,2, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 12,0, (QObject::tr("ДК")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    // prepare <--

    // fill -->
    if(10 == un->getPublishedState()) {
        for(int i = 1, n = table->columnCount(); i < n; i++) {
            for(int j = 1, m = table->rowCount(); j < m; j++) {
                if(2 == j && 1 == i) {
                    continue;
                } else if(1 == j && 2 == i) {
                    continue;
                } else if(9 == j) {
                    continue;
                } else if(11 == j) {
                    continue;
                } else if(3 <= j && 9 > j && 2 == i) {
                    continue;
                }
                setCellTextBackgroundColorForegroundBold( table, j, i, (QObject::tr("Нет связи!")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }
        }
        return;
    }

    //"Датчик"
    if(1 == un->swpRLMCType0x31().isOn()) {
        setCellTextBackgroundColorForegroundBold( table, 1, 1, (QObject::tr("Вкл[1]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);

        setCellColor( table, 1,1, cellGreen);
        setCellTextWithForeground( table, 1,1, (QObject::tr("Вкл[1]")), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    } else if(1 == un->swpRLMCType0x31().isOff()) {
        setCellTextBackgroundColorForegroundBold( table, 1, 1, (QObject::tr("Выкл[0]")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
    }
    //"Срабатывание"
    if(1 == un->swpRLMCType0x31().isOutAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 2, 2, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMCType0x31().isOutAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 2, 2, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Синхронизация"
    if(1 == un->swpRLMCType0x31().isExternalSynchronization()) {
        setCellTextBackgroundColorForegroundBold( table, 3, 1, (QObject::tr("Внешняя")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
    } else if(0 == un->swpRLMCType0x31().isExternalSynchronization()) {
        setCellTextBackgroundColorForegroundBold( table, 3, 1, (QObject::tr("Внутренняя")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
    }
    //"Низкий ровень"
    if(1 == un->swpRLMCType0x31().isFault()) {
        setCellTextBackgroundColorForegroundBold( table, 4, 1, (QObject::tr("Да<1>")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMCType0x31().isFault()) {
        setCellTextBackgroundColorForegroundBold( table, 4, 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Уровень"
    if(-1.0 != un->swpRLMCType0x31().voltage()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 1, (QString::number(un->swpRLMCType0x31().voltage(), 'f', 2)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        setCellColor( table, 5,1, cellGray);
        setCellTextWithForeground( table, 5,1, (QString::number(un->swpRLMCType0x31().voltage(), 'f', 2)), QBrush(QColor(0xFF, 0xFF, 0xFF)));
    }
    //"Пороги"
    if(-1.0 != un->swpRLMCType0x31().threshold()) {
        if(1.0 > un->swpRLMCType0x31().threshold())
            setCellTextBackgroundColorForegroundBold( table, 6, 1, (QString::number(un->swpRLMCType0x31().threshold(), 'f', 1)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        else
            setCellTextBackgroundColorForegroundBold( table, 6, 1, (QString::number(un->swpRLMCType0x31().threshold(), 'f', 0)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
    }
    //"Период тактирования"
    if(-1 != un->swpRLMCType0x31().clockPeriod()) {
        setCellTextBackgroundColorForegroundBold( table, 7, 1, (QObject::tr("Такт ") + QString::number(un->swpRLMCType0x31().clockPeriod() + 1)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
    }
    //"Режим обработки"
    if(-1 != un->swpRLMCType0x31().modeProcessing()) {
        QString str;
        switch (un->swpRLMCType0x31().modeProcessing()) {
        case 0: str = QObject::tr("Основной"); break;
        case 1: str = QObject::tr("Дополнительный"); break;
        case 2: str = QObject::tr("Ползущий (Плз)"); break;
        case 3: str = QObject::tr("2-й ярус (2Яр)"); break;
        }
        setCellTextBackgroundColorForegroundBold( table, 8, 1, (str), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
    }
    //"Выход \"Тревога\""
    if(1 == un->swpRLMCType0x31().isInAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 10, 1, (QObject::tr("Да[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMCType0x31().isInAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 10, 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Статус \"Тревога\""
    if(1 == un->swpRLMCType0x31().isWasAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 10, 2, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMCType0x31().isWasAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 10, 2, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Вход \"ДК\""
    if(1 == un->swpRLMCType0x31().isExistDK()) {
        setCellTextBackgroundColorForegroundBold( table, 12, 1, (QObject::tr("Есть[1]")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMCType0x31().isExistDK()) {
        setCellTextBackgroundColorForegroundBold( table, 12, 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    //"Статус \"ДК\""
    if(1 == un->swpRLMCType0x31().isWasDK()) {
        setCellTextBackgroundColorForegroundBold( table, 14, 2, (QObject::tr("Было[1]")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == un->swpRLMCType0x31().isWasDK()) {
        setCellTextBackgroundColorForegroundBold( table, 14, 2, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
    // fill <--
}

void Utils::fillDiagnosticTableTG(QTableWidget * const table, const QSharedPointer<UnitNode> selUN)
{
    // prepare -->
    table->setRowCount(24);
    table->setColumnCount(6);

    for(int j = 0, m = table->columnCount(); j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        for(int i = 0, n = table->rowCount(); i < n; i++) {
            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    table->setColumnWidth(0, 160);
    table->setColumnWidth(1, 110);
    table->setColumnWidth(2, 175);
    table->setColumnWidth(3, 110);
    table->setColumnWidth(4, 205);
    table->setColumnWidth(5, 110);

//    table->setColumnWidth(0, 100);
//    table->setColumnWidth(1, 150);
//    table->setColumnWidth(2, 150);
//    table->setColumnWidth(3, 150);
//    table->setColumnWidth(4, 150);
//    table->setColumnWidth(5, 150);

//    for(int i = 0, n = table->rowCount(); i < n; i++) {
//        for(int j = 0, m = table->columnCount(); j < m; j++) {
//            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
//        }
//    }

    setCellTextBackgroundColorForegroundBold( table, 0,0, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,1, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,2, (QObject::tr("Вход/Выход")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,3, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,4, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,5, (QObject::tr("Статус")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    for(int i = 1, n = 5; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, i,0, (QObject::tr("Сработка ЧЭ%1").arg(i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, i,2, (QObject::tr("Выход \"Тревога ЧЭ%1\"").arg(i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, i,4, (QObject::tr("Сработка со стороны ЧЭ%1").arg(i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    setCellTextBackgroundColorForegroundBold( table, 5,0, (QObject::tr("ДК")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 5,2, (QObject::tr("Выход \"ДК\"")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 6,0, (QObject::tr("Вскрытие")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 6,2, (QObject::tr("Вход \"Вскрытие\"")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 7,0, (QObject::tr("")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 7,1, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 7,2, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 7,3, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 7,4, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 7,5, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 8,0, (QObject::tr("ЧЭ1")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 8,2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 8,3, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 8,4, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 8,5, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    for(int i = 0, n = 3; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, i + 9,0, (QObject::tr("Фильтр%1: Сработка").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, i + 9,2, (QObject::tr("Уровень")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, i + 9,4, (QObject::tr("Порог")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    setCellTextBackgroundColorForegroundBold( table, 12,0, (QObject::tr("ЧЭ2")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,3, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,4, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,5, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    for(int i = 0, n = 3; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, i + 13,0, (QObject::tr("Фильтр%1: Сработка").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, i + 13,2, (QObject::tr("Уровень")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, i + 13,4, (QObject::tr("Порог")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    setCellTextBackgroundColorForegroundBold( table, 16,0, (QObject::tr("ЧЭ3")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 16,2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 16,3, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 16,4, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 16,5, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    for(int i = 0, n = 3; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, i + 17,0, (QObject::tr("Фильтр%1: Сработка").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, i + 17,2, (QObject::tr("Уровень")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, i + 17,4, (QObject::tr("Порог")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    setCellTextBackgroundColorForegroundBold( table, 20,0, (QObject::tr("ЧЭ4")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 20,2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 20,3, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 20,4, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 20,5, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    for(int i = 0, n = 3; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, i + 21,0, (QObject::tr("Фильтр%1: Сработка").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, i + 21,2, (QObject::tr("Уровень")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, i + 21,4, (QObject::tr("Порог")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }



    setCellTextBackgroundColorForegroundBold( table,  8,2, (""), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,2, (""), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 16,2, (""), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 20,2, (""), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  5,4, (""), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  6,4, (""), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  8,4, (""), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,4, (""), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 16,4, (""), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 20,4, (""), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);



    // prepare <--

    // fill -->
    if(10 == selUN->getPublishedState()) {
        for(int i = 1, n = table->columnCount(); i < n; i+=2) {
            for(int j = 1, m = table->rowCount(); j < m; j++) {
                if((5 == j || 6 == j) && 5 == i) {
                    continue;
                } else if((8 == j || 12 == j || 16 == j || 20 == j) && 1 != i) {
                    continue;
                } else if(7 == j) {
                    continue;
                }
                setCellTextBackgroundColorForegroundBold( table, j, i, (QObject::tr("Нет связи!")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }
        }
        return;
    }

    auto swp32 = selUN->swpTGType0x32();

    for(int i = 1, n = 5; i < n; i++) {
//        setCellTextWithForeground( table, i,0, (QObject::tr("Сработка ЧЭ%1").arg(i)));
        //"Cработка ЧЭ%1"
        if(1 == swp32.C(i).isInAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, i, 1, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == swp32.C(i).isInAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, i, 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }
//        setCellTextWithForeground( table, i,2, (QObject::tr("Выход \"Тревога ЧЭ%1\"").arg(i)));
        //Выход "Тревога ЧЭ%1"
        if(1 == swp32.C(i).isOutAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, i, 3, (QObject::tr("Да[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == swp32.C(i).isOutAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, i, 3, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }
//        setCellTextWithForeground( table, i,4, (QObject::tr("Сработка со стороны ЧЭ%1").arg(i)));
        //"Сработка со стороны ЧЭ%1"
        if(1 == swp32.C(i).isSideAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, i, 5, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == swp32.C(i).isSideAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, i, 5, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }
    }

//    "ДК"
    if(1 == swp32.isWasDK()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 1, (QObject::tr("Было[1]")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp32.isWasDK()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
//    "Выход \"ДК\""
    if(1 == swp32.isExistDK()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 3, (QObject::tr("Есть[1]")), cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp32.isExistDK()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 3, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
//    "Вскрытие"
    if(1 == swp32.isWasOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 6, 1, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp32.isWasOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 6, 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }
//    "Выход \"Вскрытие\""
    if(1 == swp32.isInOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 6, 3, (QObject::tr("Есть[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp32.isInOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 6, 3, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    auto swp34 = selUN->swpTGType0x34();

    for(int ci = 0, n = 4; ci < n; ci++) {

        if(1 == swp34.C(ci + 1).isOffFlt1() && 1 == swp34.C(ci + 1).isOffFlt2() && 1 == swp34.C(ci + 1).isOffFlt3()) {
            setCellTextBackgroundColorForegroundBold( table, (8 + 4 * ci),1, (QObject::tr("Выкл")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        } else if(50'001 == swp32.C(ci + 1).voltage()) {
            setCellTextBackgroundColorForegroundBold( table, (8 + 4 * ci),1, (QObject::tr("Обрыв кабеля")), cellBlue, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(50'000 == swp32.C(ci + 1).voltage()) {
            setCellTextBackgroundColorForegroundBold( table, (8 + 4 * ci),1, (QObject::tr("Замыкание кабеля")), cellBlue, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(1 == swp32.C(ci + 1).isFault()) {
            setCellTextBackgroundColorForegroundBold( table, (8 + 4 * ci),1, (QObject::tr("Неисправность")), cellBlue, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else {
            setCellTextBackgroundColorForegroundBold( table, (8 + 4 * ci),1, (QObject::tr("Норма")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }

//        "Фильтр%1: Сработка"
        if(1 == swp32.C(ci + 1).isInAlarmFlt1()) {
            setCellTextBackgroundColorForegroundBold( table, (9 + 4 * ci), 1, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == swp32.C(ci + 1).isInAlarmFlt1()) {
            setCellTextBackgroundColorForegroundBold( table, (9 + 4 * ci), 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }

//        "Фильтр%2: Сработка"
        if(1 == swp32.C(ci + 1).isInAlarmFlt2()) {
            setCellTextBackgroundColorForegroundBold( table, (10 + 4 * ci), 1, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == swp32.C(ci + 1).isInAlarmFlt2()) {
            setCellTextBackgroundColorForegroundBold( table, (10 + 4 * ci), 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }

//        "Фильтр%3: Сработка"
        if(1 == swp32.C(ci + 1).isInAlarmFlt3()) {
            setCellTextBackgroundColorForegroundBold( table, (11 + 4 * ci), 1, (QObject::tr("Было[1]")), cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == swp32.C(ci + 1).isInAlarmFlt3()) {
            setCellTextBackgroundColorForegroundBold( table, (11 + 4 * ci), 1, (QObject::tr("Нет[0]")), cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }

//        "Фильтр%3: Уровень"
        if(-1.0 != swp32.C(ci + 1).voltage()) {
            setCellTextBackgroundColorForegroundBold( table, (9 + 4 * ci), 3, (QString::number(swp32.C(ci + 1).voltage())), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            setCellTextBackgroundColorForegroundBold( table, (10 + 4 * ci), 3, (QString::number(swp32.C(ci + 1).voltage())), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
            setCellTextBackgroundColorForegroundBold( table, (11 + 4 * ci), 3, (QString::number(swp32.C(ci + 1).voltage())), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }


        //"Фильтр%1: Пороги"
        if(-1.0 != swp34.C(ci + 1).thresholdFlt1()) {
            setCellTextBackgroundColorForegroundBold( table, (9 + 4 * ci), 5, (QString::number(swp34.C(ci + 1).thresholdFlt1())), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }

        //"Фильтр%2: Пороги"
        if(-1.0 != swp34.C(ci + 1).thresholdFlt2()) {
            setCellTextBackgroundColorForegroundBold( table, (10 + 4 * ci), 5, (QString::number(swp34.C(ci + 1).thresholdFlt2())), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }

        //"Фильтр%3: Пороги"
        if(-1.0 != swp34.C(ci + 1).thresholdFlt3()) {
            setCellTextBackgroundColorForegroundBold( table, (11 + 4 * ci), 5, (QString::number(swp34.C(ci + 1).thresholdFlt3())), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    // fill <--
}

void Utils::fillDiagnosticTableDD_T4K_M(QTableWidget * const table, const QSharedPointer<UnitNode> selUN)
{
    // prepare -->
    table->setRowCount(14);
    table->setColumnCount(4);

    for(int j = 0, m = table->columnCount(); j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        for(int i = 0, n = table->rowCount(); i < n; i++) {
            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    table->setColumnWidth(0, 180);
    table->setColumnWidth(1, 100);
    table->setColumnWidth(2, 190);
    table->setColumnWidth(3, 100);

    for(int i = 0, n = 14; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            setCellColor( table, i, j, cellGray);
            if(0 != i && 0 != j && 2 != j)
                setCellTextWithForeground( table, i, j, "?", QBrush(QColor(0xFF, 0xFF, 0xFF)));

        }
    }

    setCellTextBackgroundColorForegroundBold( table, 0,0, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,1, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,2, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,3, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 1,0, (QObject::tr("Готовность БОД")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);


    for(int i = 0, n = 4; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    setCellTextBackgroundColorForegroundBold( table, 10,0, (QObject::tr("Выход \"ДК\"")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 11,0, (QObject::tr("Состояние \"ДК\" было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 13,0, (QObject::tr("Вскрытие БО было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 1,2, (QObject::tr("Сработка по ЧЭ1 было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 2,2, (QObject::tr("Сработка по ЧЭ2 было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 3,2, (QObject::tr("Обрыв по ЧЭ1 есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 4,2, (QObject::tr("Замыкание по ЧЭ1 есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 5,2, (QObject::tr("Обрыв по ЧЭ2 есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 6,2, (QObject::tr("Замыкание по ЧЭ2 есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 7,2, (QObject::tr("Неисправность ДД")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 8,2, (QObject::tr("Обрыв связи с ДД есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 9,2, (QObject::tr("Обрыв связи с ДД был")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 10,2, (QObject::tr("Вскрытие ДД есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 11,2, (QObject::tr("Вскрытие ДД был")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,2, (QObject::tr("Уровень Сигнала ЧЭ1")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 13,2, (QObject::tr("Уровень Сигнала ЧЭ2")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    // prepare <--
    // fill -->
    const auto& swp = selUN->swpT4KBODType0x33();

    //"Готовность БОД"
    if(1 == swp.isReady()) {
        setCellTextBackgroundColorForegroundBold( table, 1, 1, "Да <1>", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.isReady()) {
        setCellTextBackgroundColorForegroundBold( table, 1, 1, "Нет [0]", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    for(int i = 0, n = 4; i < n; i++) {
        //"Вход \"Тревога Уч.%1\""
        if(1 == swp.y(i).isInAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, 2 + i, 1, "Да <1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == swp.y(i).isInAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, 2 + i, 1, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }
        //"Тревога Уч.%1 было"
        if(1 == swp.y(i).isWasAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, 6 + i, 1, "Да <1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == swp.y(i).isWasAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, 6 + i, 1, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }
    }

    //"Выход \"ДК\""
    if(1 == swp.isExistDK()) {
        setCellTextBackgroundColorForegroundBold( table, 10,1, "Да <1>", cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.isExistDK()) {
        setCellTextBackgroundColorForegroundBold( table, 10,1, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Состояние \"ДК\" было"
    if(1 == swp.isWasDK()) {
        setCellTextBackgroundColorForegroundBold( table, 11,1, "Да <1>", cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.isWasDK()) {
        setCellTextBackgroundColorForegroundBold( table, 11,1, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Выход \"Вскрытие БО\""
    if(1 == swp.isInOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 12,1, "Да <1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.isInOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 12,1, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Вскрытие БО было"
    if(1 == swp.isWasOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 13,1, "Да <1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.isWasOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 13,1, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Сработка по ЧЭ1 было"
    if(1 == swp.dd().c(1).isWasAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 1, 3, "Да <1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().c(1).isWasAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 1, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Сработка по ЧЭ2 было"
    if(1 == swp.dd().c(2).isWasAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 2, 3, "Да <1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().c(2).isWasAlarm()) {
        setCellTextBackgroundColorForegroundBold( table, 2, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Обрыв по ЧЭ1 есть"
    if(1 == swp.dd().c(1).isCliff()) {
        setCellTextBackgroundColorForegroundBold( table, 3, 3, "Да {1}", cellBlue, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().c(1).isCliff()) {
        setCellTextBackgroundColorForegroundBold( table, 3, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Замыкание по ЧЭ1 есть"
    if(1 == swp.dd().c(1).isClosure()) {
        setCellTextBackgroundColorForegroundBold( table, 4, 3, "Да <1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().c(1).isClosure()) {
        setCellTextBackgroundColorForegroundBold( table, 4, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Обрыв по ЧЭ2 есть"
    if(1 == swp.dd().c(2).isCliff()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 3, "Да {1}", cellBlue, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().c(2).isCliff()) {
        setCellTextBackgroundColorForegroundBold( table, 5, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Замыкание по ЧЭ2 есть"
    if(1 == swp.dd().c(2).isClosure()) {
        setCellTextBackgroundColorForegroundBold( table, 6, 3, "Да <1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().c(2).isClosure()) {
        setCellTextBackgroundColorForegroundBold( table, 6, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Неисправность ДД"
    if(1 == swp.dd().isFault()) {
        setCellTextBackgroundColorForegroundBold( table, 7, 3, "Да <1>", cellBlue, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().isFault()) {
        setCellTextBackgroundColorForegroundBold( table, 7, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Обрыв связи с ДД есть"
    if(1 == swp.dd().isInCommunicationBreak()) {
        setCellTextBackgroundColorForegroundBold( table, 8, 3, "Да <1>", cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().isInCommunicationBreak()) {
        setCellTextBackgroundColorForegroundBold( table, 8, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Обрыв связи с ДД был"
    if(1 == swp.dd().isWasCommunicationBreak()) {
        setCellTextBackgroundColorForegroundBold( table, 9, 3, "Да <1>", cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().isWasCommunicationBreak()) {
        setCellTextBackgroundColorForegroundBold( table, 9, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Вскрытие ДД есть"
    if(1 == swp.dd().isInOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 10, 3, "Да <1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().isInOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 10, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Вскрытие ДД было"
    if(1 == swp.dd().isWasOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 11, 3, "Да <1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.dd().isWasOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 11, 3, "Нет [0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Уровень Сигнала ЧЭ1"
    if(-1 != swp.dd().c(1).level()) {
        setCellTextBackgroundColorForegroundBold( table, 12, 3, (QString::number(swp.dd().c(1).level())), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
    }

    //"Уровень Сигнала ЧЭ2"
    if(-1.0 != swp.dd().c(2).level()) {
        setCellTextBackgroundColorForegroundBold( table, 13, 3, (QString::number(swp.dd().c(2).level())), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
    }

    // fill <--
}

void Utils::fillDiagnosticTableDD_SOTA(QTableWidget * const table, const QSharedPointer<UnitNode> /*selUN*/)
{
    // prepare -->
    table->setRowCount(14);
    table->setColumnCount(4);

    for(int j = 0, m = table->columnCount(); j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        for(int i = 0, n = table->rowCount(); i < n; i++) {
            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    table->setColumnWidth(0, 180);
    table->setColumnWidth(1, 100);
    table->setColumnWidth(2, 190);
    table->setColumnWidth(3, 100);

    for(int j = 0, m = table->columnCount(); j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        for(int i = 0, n = table->rowCount(); i < n; i++) {
            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    for(int i = 0, n = 14; i < n; i++) {
        for(int j = 0, m = 4; j < m; j++) {
            setCellColor( table, i, j, cellGray);
            if(0 != i && 0 != j && 2 != j)
                setCellTextWithForeground( table, i, j, "?", QBrush(QColor(0xFF, 0xFF, 0xFF)));
        }
    }

    setCellTextBackgroundColorForegroundBold( table, 0,0, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,1, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,2, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,3, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    for(int j = 4, m = table->columnCount(); j < m; j++) {
        setCellTextBackgroundColorForegroundBold( table, 0,j, (QObject::tr("")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    setCellTextBackgroundColorForegroundBold( table, 1,0, (QObject::tr("Готовность БОД")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);


    for(int i = 0, n = 5; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    setCellTextBackgroundColorForegroundBold( table, 10,0, (QObject::tr("Выход \"ДК\"")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 11,0, (QObject::tr("Состояние \"ДК\" было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 13,0, (QObject::tr("Вскрытие БО было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table,  1,2, (QObject::tr("Сработка было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  2,2, (QObject::tr("Обрыв связи с ДД есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  3,2, (QObject::tr("Обрыв связи с ДД был")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  4,2, (QObject::tr("Вскрытие ДД есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  5,2, (QObject::tr("Неисправность ДД есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  6,2, (QObject::tr("Тревога по Ф1 есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  7,2, (QObject::tr("Тревога поФ2 есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  8,2, (QObject::tr("Опрос ДД")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table,  9,2, (QObject::tr("Уровень Сигнала")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 10,2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 11,2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 13,2, (QObject::tr("")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);


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

    for(int j = 0, m = table->columnCount(); j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        for(int i = 0, n = table->rowCount(); i < n; i++) {
            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);

    table->setColumnWidth(0, 185);
    table->setColumnWidth(1, 90);
    table->setColumnWidth(2, 190);
    table->setColumnWidth(3, 90);


    for(int j = 4, m = 53; j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        table->setColumnWidth(j, 50);
    }

    for(int j = 0, m = 53; j < m; j++) {
        for(int i = 0, n = 20; i < n; i++) {
            setCellColor( table, i, j, cellGray);
            setCellTextWithForeground( table, i, j, "");
        }
    }

    setCellTextBackgroundColorForegroundBold( table, 0,0, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,1, (QObject::tr("Значение")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,2, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    for(int j = 3, m = table->columnCount(); j < m; j++) {
        setCellTextBackgroundColorForegroundBold( table, 0,j, (QObject::tr("")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    setCellTextBackgroundColorForegroundBold( table, 1,0, (QObject::tr("Готовность БОД")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);


    for(int i = 0, n = 4; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    setCellTextBackgroundColorForegroundBold( table, 10,0, (QObject::tr("Выход \"ДК\"")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 11,0, (QObject::tr("Состояние \"ДК\" было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 13,0, (QObject::tr("Вскрытие БО было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 1,2, (QObject::tr("Участки 1-2")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 11,2, (QObject::tr("Участки 3-4")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    int dec[] = {2,6,12,16};
    for(int i = 0, n = 4; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 0,2, (QObject::tr("ДД")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 1,2, (QObject::tr("Сработка ДД было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 2,2, (QObject::tr("Обрыв связи с ДД есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 3,2, (QObject::tr("Обрыв связи с ДД был")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    for(int i = 0, n = 50; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, dec[0],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[1],3 + i, (QString("%1").arg(i + 1 + 50, 2, 10, QLatin1Char('0'))), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[2],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[3],3 + i, (QString("%1").arg(i + 1 + 50, 2, 10, QLatin1Char('0'))), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }


    // prepare <--

    // fill -->
    // fill <--
}

void Utils::fillDiagnosticTableY4_T4K_M(QTableWidget * const table, const QSharedPointer<UnitNode> selUN)
{
    // prepare -->
    table->setRowCount(22);
    table->setColumnCount(29);

    for(int j = 0, m = table->columnCount(); j < m; j++) {
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        for(int i = 0, n = table->rowCount(); i < n; i++) {
            setCellTextBackgroundColorForegroundBold( table, i, j, "", cellGray, QBrush(QColor(0x00, 0x00, 0x00)), false);
        }
    }

    for(int i = 0, n = 22; i < n; i++) {
        for(int j = 0, m = 29; j < m; j++) {
            QTableWidgetItem * item = table->item(i, j);
            if(nullptr == item) {
                setCellTextWithForeground( table, i, j, "");
            }

            setCellColor(table, i, j, cellGray);
        }
    }

    setCellTextBackgroundColorForegroundBold( table, 0,0, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,1, (QObject::tr("Зн-е")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 0,2, (QObject::tr("Параметр")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    table->setColumnWidth(0, 180);
    table->setColumnWidth(1, 10);
    table->setColumnWidth(2, 220);
    for(int j = 3, m = table->columnCount(); j < m; j++) {
        setCellTextBackgroundColorForegroundBold( table, 0,j, (QObject::tr("")), cellLightGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        table->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Fixed);
        table->setColumnWidth(j, 10);
    }

    setCellTextBackgroundColorForegroundBold( table, 1,0, (QObject::tr("Готовность БОД")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);


    for(int i = 0, n = 4; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, 2 + i,0, (QObject::tr("Вход \"Тревога Уч.%1\"").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, 6 + i,0, (QObject::tr("Тревога Уч.%1 было").arg(1 + i)), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    setCellTextBackgroundColorForegroundBold( table, 10,0, (QObject::tr("Выход \"ДК\"")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 11,0, (QObject::tr("Состояние \"ДК\" было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,0, (QObject::tr("Выход \"Вскрытие БО\"")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 13,0, (QObject::tr("Вскрытие БО было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    setCellTextBackgroundColorForegroundBold( table, 1,2, (QObject::tr("Участки 1-2")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    setCellTextBackgroundColorForegroundBold( table, 12,2, (QObject::tr("Участки 3-4")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);

    int dec[] = {2,13};
    for(int i = 0, n = 2; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 0,2, (QObject::tr("ДДискретный")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 1,2, (QObject::tr("Сработка по ЧЭ1 было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 2,2, (QObject::tr("Сработка по ЧЭ2 было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 3,2, (QObject::tr("Неисправность по ЧЭ1 есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 4,2, (QObject::tr("Неисправность по ЧЭ2 есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 5,2, (QObject::tr("Обрыв связи с ДД есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 6,2, (QObject::tr("Обрыв связи с ДД был")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 7,2, (QObject::tr("Вскрытие ДД есть")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[i] + 8,2, (QObject::tr("Вскрытие ДД было")), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }

    for(int i = 0, n = 26; i < n; i++) {
        setCellTextBackgroundColorForegroundBold( table, dec[0],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
        setCellTextBackgroundColorForegroundBold( table, dec[1],3 + i, (QString("%1").arg(i + 1, 2, 10, QLatin1Char('0'))), cellGray, QBrush(QColor(0x00, 0x00, 0x00)), true);
    }


    // prepare <--

    // fill -->
    const auto& swp = selUN->swpT4KBODType0x32();

    //"Готовность БОД"
    if(1 == swp.isReady()) {
        setCellTextBackgroundColorForegroundBold( table, 1, 1, "<1>", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.isReady()) {
        setCellTextBackgroundColorForegroundBold( table, 1, 1, "[0]", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    for(int i = 1, n = 4; i <= n; i++) {
        //"Вход \"Тревога Уч.%1\""
        if(1 == swp.y(i).isInAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, 1 + i, 1, "<1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == swp.y(i).isInAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, 1 + i, 1, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }
        //"Тревога Уч.%1 было"
        if(1 == swp.y(i).isWasAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, 5 + i, 1, "<1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        } else if(0 == swp.y(i).isWasAlarm()) {
            setCellTextBackgroundColorForegroundBold( table, 5 + i, 1, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
        }
    }

    //"Выход \"ДК\""
    if(1 == swp.isExistDK()) {
        setCellTextBackgroundColorForegroundBold( table, 10,1, "<1>", cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.isExistDK()) {
        setCellTextBackgroundColorForegroundBold( table, 10,1, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Состояние \"ДК\" было"
    if(1 == swp.isWasDK()) {
        setCellTextBackgroundColorForegroundBold( table, 11,1, "<1>", cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.isWasDK()) {
        setCellTextBackgroundColorForegroundBold( table, 11,1, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Выход \"Вскрытие БО\""
    if(1 == swp.isInOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 12,1, "<1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.isInOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 12,1, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    //"Вскрытие БО было"
    if(1 == swp.isWasOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 13,1, "<1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    } else if(0 == swp.isWasOpened()) {
        setCellTextBackgroundColorForegroundBold( table, 13,1, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
    }

    for(int dd = 1, nDd = 26; dd <= nDd; dd++) {
        int dec[] = {0,2,2,13,13};
        for(int y4 = 1, nY4 = 4; y4 <= nY4; y4++) {
            //"Сработка по ЧЭ1 было"
            if(1 == swp.y(y4).dd(dd).c(1).isWasAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 1, dd + 2, "<1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            } else if(0 == swp.y(y4).dd(dd).c(1).isWasAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 1, dd + 2, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }

            //"Сработка по ЧЭ2 было"
            if(1 == swp.y(y4).dd(dd).c(2).isWasAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 2, dd + 2, "<1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            } else if(0 == swp.y(y4).dd(dd).c(2).isWasAlarm()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 2, dd + 2, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }

            //"Неисправность по ЧЭ1 есть"
            if(1 == swp.y(y4).dd(dd).c(1).isFault()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 3, dd + 2, "<1>", cellBlue, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            } else if(0 == swp.y(y4).dd(dd).c(1).isFault()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 3, dd + 2, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }

            //"Неисправность по ЧЭ2 есть"
            if(1 == swp.y(y4).dd(dd).c(2).isFault()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 4, dd + 2, "<1>", cellBlue, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            } else if(0 == swp.y(y4).dd(dd).c(2).isFault()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 4, dd + 2, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }

            //"Обрыв связи с ДД есть"
            if(1 == swp.y(y4).dd(dd).isInCommunicationBreak()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 5, dd + 2, "<1>", cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            } else if(0 == swp.y(y4).dd(dd).isInCommunicationBreak()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 5, dd + 2, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }

            //"Обрыв связи с ДД был"
            if(1 == swp.y(y4).dd(dd).isWasCommunicationBreak()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 6, dd + 2, "<1>", cellYellow, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            } else if(0 == swp.y(y4).dd(dd).isWasCommunicationBreak()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 6, dd + 2, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }

            //"Вскрытие ДД есть"
            if(1 == swp.y(y4).dd(dd).isInOpened()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 7, dd + 2, "<1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            } else if(0 == swp.y(y4).dd(dd).isInOpened()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 7, dd + 2, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }

            //"Вскрытие ДД было"
            if(1 == swp.y(y4).dd(dd).isWasOpened()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 8, dd + 2, "<1>", cellRed, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            } else if(0 == swp.y(y4).dd(dd).isWasOpened()) {
                setCellTextBackgroundColorForegroundBold( table, dec[y4] + 8, dd + 2, "[0]", cellGreen, QBrush(QColor(0xFF, 0xFF, 0xFF)), false);
            }
        }
    }
    // fill <--
}

QSet<QSharedPointer<UnitNode> > Utils::findeSetAutoOnOffUN(const QSharedPointer<UnitNode> &un)
{
    QSet<QSharedPointer<UnitNode> > unSetTmp;
    if(TypeUnitNodeEnum::IU_BL_IP != un->getType()
    && TypeUnitNodeEnum::SSOI_IU_BL_IP != un->getType()) {
        return unSetTmp;
    }
    unSetTmp.insert(un);
    unSetTmp = unSetTmp + un->getDoubles();
    for(auto it = unSetTmp.begin(); it != unSetTmp.end();) {
        const auto& unDouble = *it;
        //qDebug() << "itr :" << unSetTmp;
        //qDebug() << "fnd :" << unDouble << unDouble->getMetaNames() << unDouble->getName();
        if(!unDouble->treeParent().isNull()) {
            if(TypeUnitNodeEnum::SD_BL_IP == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()
            || TypeUnitNodeEnum::SSOI_SD_BL_IP == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()
            || TypeUnitNodeEnum::RLM_KRL == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()
            || TypeUnitNodeEnum::RLM_C == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()
            || TypeUnitNodeEnum::TG == qSharedPointerCast<UnitNode>(unDouble->treeParent())->getType()) {
                //qDebug() << "trg :"<< unDouble->getMetaNames() << unDouble->toString();
                it++;
                continue;
            } else {
                it = unSetTmp.erase(it);
                continue;
            }
        } else {
            it = unSetTmp.erase(it);
            continue;
        }
        it++;
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

QString Utils::outTypeToString(const int &outType)
{
    switch( outType )
    {
       case 1: return "РИФ-РЛМ";
       case 2: return "РИФ-КРЛ";
       case 3: return "РИФ-КРЛМ";
       case 4: return "РИФ-РЛМ-С";
       case 5: return "Трасса";
       case 6: return "Точка/Гарда";
       case 7: return "Разряд";
       case 8: return "УЗ Монолит";
       case 9: return "Блок связи";
       default: return "";
    }
    return "";
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
      out.append((static_cast<uint8_t>(in.at(x)) ^ static_cast<uint8_t>(key.at((x + 1) % key.size())) * static_cast<uint8_t>(2)));
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

 double Utils::randomNormalDistribution(const double mean, const double stddev) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d{mean, stddev};
    return std::round(d(gen));
}

 double Utils::randomExponentialDistribution(const double mean) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<> d(1.0 / mean);
    return d(gen);
}

 bool Utils::randomBernoulliDistribution(const double meanTrue) {
    // set meanTrue = 0.25
    // give "true" 1/4 of the time
    // give "false" 3/4 of the time
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution d(meanTrue);
    return d(gen);
}
