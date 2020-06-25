#ifndef JOURENTITY_H
#define JOURENTITY_H

#include <QObject>
#include <QDateTime>
#include <QVariant>

class JourEntity : public QObject
{
    Q_OBJECT
private:

    int id = 0;
    QDateTime cdate = QDateTime::currentDateTime();
    QDateTime mdate = QDateTime::currentDateTime();
    QString comment;
    QString object;
    int objectid = 0;
    QString reason;
    QString measures;
//    QString operator;
    QString operatorid;
    QString status;
    QString direction;

    int d1 = 0;
    int d2 = 0;
    int d3 = 0;
    int d4 = 0;
    int type = 0;
    int objecttype = 0;
    int flag = 0;

    static QMap<int, QString> mapTypeObject;
    static QMap<int, QString> mapTypeEvent;
    static QMap<int, QString> mapTypeConnectObject;

public:

    enum TypeObject {
        oAllObject = 0,//"Все",
        oSD = 1,//"СД",
        oIU = 2,//"ИУ",
        oRIFRLM = 3,//"РИФ-РЛМ(КРЛ), Трасса",
        oSDCollector = 4,//"СД концентратора",
        oToros = 5,//"Торос",
        oNast = 6,//"Наст",
        oRadar = 7,//"Радар",
        oRazrivBO = 8,//"Разрыв БО",
        oTochkaGard = 9,//"Точка/Гарда",
        oAdam = 10,//"Адам-406x/4168",
        oSDBLIP = 11,//"СД БЛ-IP",
        oIUBLIP = 12,//"ИУ БЛ-IP",
        oRIFRLMS = 13,//"РИФ-РЛМ-С",
        oBODTochkaM = 14,//"БОД Точка-М/Гарда-М",
        oDDTochkaM = 15,//"ДД Точка-М/Гарда-М",
        oBODSota = 16,//"БОД Сота/Сота-М",
        oDDSota = 17//"ДД Сота/Сота-М"
    };

    enum TypeEvent {
        eAllEvent = 0,//"Все"
        eAlarm = 1,//"Тревоги"
        eAlarmWorked = 2,//"Тревога - СРАБОТКА"
        eAlarmOpening = 3,//"Тревога - ВСКРЫТИЕ"
        eFault = 4,//"Неисправности"
        eFaultNoConnect = 5,//"Нет связи"
        eFaultDK = 6,//"Ком. ДК не выполнена"
        eFaultCommand = 7,//"Ком. упр. не выполнена"
        eCommand = 8,//"Команды"
        eCommandDK = 9,//"ДК"
        eCommandUZMonolit = 10,//"УЗ Монолит"
        eCommandOperator = 11//"Оператор"
    };

    enum TypeConnectObject {
        coAllConnectObject = 0,//"не указан"
        coRIFRLM = 1,//"РИФ-РЛМ"
        coRIFKRL = 2,//"РИФ-КРЛ"
        coRIFKRLM = 3,//"РИФ-КРЛМ"
        coRIFRLMS = 4,//"РИФ-РЛМ-С"
        coTrassa = 5,//"Трасса"
        coTochkaGard = 6,//"Точка/Гарда"
        coRazryad = 7//"Разряд"
    };

    explicit JourEntity(QObject *parent = nullptr);
    JourEntity(const JourEntity & parent);
    JourEntity(JourEntity *parent);
    QVariant data(int column) const noexcept;
    JourEntity & operator=(const JourEntity& );

    int getId() const;
    void setId(int value);

    QDateTime getCdate() const;
    void setCdate(const QDateTime &value = QDateTime::currentDateTime());

    QDateTime getMdate() const;
    void setMdate(const QDateTime &value = QDateTime::currentDateTime());

    QString getComment() const;
    void setComment(const QString &value);

    QString getObject() const;
    void setObject(const QString &value);

    QString getReason() const;
    void setReason(const QString &value);

    QString getMeasures() const;
    void setMeasures(const QString &value);

    QString getOperatorid() const;
    void setOperatorid(const QString &value);

    QString getStatus() const;
    void setStatus(const QString &value);

    QString getDirection() const;
    void setDirection(const QString &value);

    int getObjectid() const;
    void setObjectid(int value);

    int getD1() const;
    void setD1(int value);

    int getD2() const;
    void setD2(int value);

    int getD3() const;
    void setD3(int value);

    int getD4() const;
    void setD4(int value);

    int getType() const;
    void setType(int value);

    int getObjecttype() const;
    void setObjecttype(int value);

    int getFlag() const;
    void setFlag(int value);

    static QMap<int, QString> getMapTypeEvent();

    static QMap<int, QString> getMapTypeObject();

    static QMap<int, QString> getMapTypeConnectObject();

private:

signals:
};

#endif // JOURENTITY_H
