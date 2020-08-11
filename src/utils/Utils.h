#ifndef UTILS_H
#define UTILS_H

#include <QHostAddress>
#include <QTableWidget>

#include <UnitNode.h>

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
    static int calcDkStatus(int type, int status1, int status2);
    static void fillDiagnosticTable(QTableWidget * table, UnitNode *selUN);
};

#endif // UTILS_H
