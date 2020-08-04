#ifndef UTILS_H
#define UTILS_H

#include <QHostAddress>
#include <QTableWidget>

#include <UnitNode.h>

//enum BeatStatus {
//    Start = 0,
//    Request = 1,
//    Waite = 2,
//    Unsuccessful = 3,
//    RequestStep1 = 4,
//    RequestStep2 = 5
//};

class Utils
{
public:
    static QColor cellRed;
    static QColor cellGreen;
    static QColor cellGray;

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
    static QByteArray XOR_Crypt(const QByteArray in, const QByteArray key);
    static QString XOR_Crypt(const QString in, const QString key);

};

#endif // UTILS_H
