#ifndef UTILS_H
#define UTILS_H

#include <QByteArray>
#include <QtMath>


class UnitNode;
class QTableWidget;
class QHostAddress;
class QColor;
class Utils
{

public:
    static QColor cellRed;
    static QColor cellGreen;
    static QColor cellGray;
    static QColor cellYellow;

public:
    Utils();

    template<typename FloatingType = float>
    constexpr static const FloatingType _threshold0 = 0.09;

    template<typename FloatingType, typename FloatingType2 = FloatingType>
    static inline bool treatAs0(FloatingType value, FloatingType2 threshold0 = _threshold0<FloatingType2>)
    {
        return qFabs(value) < threshold0;
    };

    template<typename FloatingType1, typename FloatingType2, typename FloatingType3 = FloatingType1>
    static inline bool treatAsEqual(FloatingType1 value1, FloatingType2 value2, FloatingType3 threshold0 = _threshold0<FloatingType3>)
    {
        return treatAs0(value1 - value2, threshold0);
    };

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
    static void fillDiagnosticTableRLMKRL(QTableWidget * const table, const UnitNode *un);
    static void fillDiagnosticTableRLM_C(QTableWidget *table, const UnitNode *selUN);
    static void fillDiagnosticTableTG(QTableWidget *const table, const UnitNode *selUN);
    static void fillDiagnosticTableDD_T4K_M(QTableWidget * const table, const UnitNode *selUN);
    static void fillDiagnosticTableDD_SOTA(QTableWidget * const table, const UnitNode *selUN);
    static void fillDiagnosticTableY4_SOTA(QTableWidget * const table, const UnitNode *selUN);
    static void fillDiagnosticTableY4_T4K_M(QTableWidget * const table, const UnitNode *selUN);
    static QSet<UnitNode *> findeSetAutoOnOffUN(UnitNode *un);

    static char reverseBits( char number );


};

#endif // UTILS_H
