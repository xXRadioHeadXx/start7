#ifndef UTILS_H
#define UTILS_H

#include <QHostAddress>
#include <QTableWidget>

#include <UnitNode.h>

///
/// \brief Значения, меньшие по модулю этой величины, считаем нулевыми
///
/// \remarks
///     Для подстраховки при сравнении значений с плавающей точкой
///
template<typename FloatingType = float>
const FloatingType _threshold0 = 0.09;

///
/// \brief Проверка на равенство нулю с учетом возможной погрешности
///
/// \remarks
///     Для подстраховки при сравнении значений с плавающей точкой
///
template<typename FloatingType, typename FloatingType2 = FloatingType>
inline bool treatAs0(FloatingType value, FloatingType2 threshold0 = _threshold0<FloatingType2>)
{
    return abs(value) < threshold0;
};

///
/// \brief Проверка на равенство с учетом возможной погрешности
///
/// \remarks
///     Для подстраховки при сравнении значений с плавающей точкой
///
template<typename FloatingType1, typename FloatingType2, typename FloatingType3 = FloatingType1>
inline bool treatAsEqual(FloatingType1 value1, FloatingType2 value2, FloatingType3 threshold0 = _threshold0<FloatingType3>)
{
    return treatAs0(value1 - value2, threshold0);
};


class Utils
{
public:
    static QColor cellRed;
    static QColor cellGreen;
    static QColor cellGray;
    static QColor cellYellow;

public:
    Utils();

    static QHostAddress hostAddress(const QString ip);
    static QString strHostAddress(const QString ip);
    static QString hostAddressToString(const QHostAddress host);
    static quint8 getByteSumm(QByteArray &ba, int bi = 1, int ei = -1);
    static QString typeUNToStr(const int type);
    static QString baMsgToStr(const QByteArray ba = QByteArray());
    static bool isSavedMsg(const QByteArray ba);
    template <typename T>
    static QList<T> reversed( const QList<T> & in );
    static void setCellText(QTableWidget * const table, const int row, const int column, const QString text);
    static void setCellColor(QTableWidget * const table, const int row, const int column, const QColor color);
    static void fillDiagnosticTable(QTableWidget * const table, const UnitNode *selUN);
    static void fillDiagnosticTableBLIP(QTableWidget * const table, const UnitNode * selUN);
    static void fillDiagnosticTableRLMKRL(QTableWidget * const table, const UnitNode * selUN);
    static void fillDiagnosticTableRLM_C(QTableWidget *table, const UnitNode *selUN);
    static void fillDiagnosticTableTG(QTableWidget *const table, const UnitNode *selUN);
    static void fillDiagnosticTableDD_T4K_M(QTableWidget * const table, const UnitNode *selUN);
    static void fillDiagnosticTableDD_SOTA(QTableWidget * const table, const UnitNode *selUN);
    static void fillDiagnosticTableY4_SOTA(QTableWidget * const table, const UnitNode *selUN);
    static void fillDiagnosticTableY4_T4K_M(QTableWidget * const table, const UnitNode *selUN);
    static QSet<UnitNode *> findeSetAutoOnOffUN(UnitNode *un);

};

#endif // UTILS_H
