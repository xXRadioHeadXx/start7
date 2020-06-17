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
//    static Port * typeDefPort(const AbstractPort * port);
//    static DataQueueItem makeOnOff0x20(DataQueueItem &item, const UnitNode * un = nullptr);
//    static QByteArray makeOnOff0x20(const UnitNode * un = nullptr);
//    static DataQueueItem makeDK0x21(DataQueueItem &item, const UnitNode * un = nullptr);
//    static QByteArray makeDK0x21(const UnitNode * un = nullptr);
//    static DataQueueItem makeStatusRequest0x22(DataQueueItem &item, const UnitNode * un = nullptr);
//    static QByteArray makeStatusRequest0x22(const UnitNode * un = nullptr);
//    static DataQueueItem makeOnOff0x23(DataQueueItem &item, UnitNode *un = nullptr);
//    static QByteArray makeOnOff0x23(UnitNode *un = nullptr, bool onOff = true, UnitNode *pun = nullptr);
//    static DataQueueItem makeAlarmReset0x24(DataQueueItem &item, const UnitNode * un = nullptr);
//    static QByteArray makeAlarmReset0x24(const UnitNode * un = nullptr);
//    static bool isValideDirectionI(DataQueueItem &item);
//    static DataQueueItem parcingStatusWord0x41(DataQueueItem &item, DataQueueItem & resultRequest);
    static int calcDkStatus(int type, int status1, int status2);
    static void fillDiagnosticTable(QTableWidget * table, UnitNode *selUN);
//    static AbstractPort * portOfUN(UnitNode *un);


};

#endif // UTILS_H
