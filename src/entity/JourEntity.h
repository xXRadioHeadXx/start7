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

public:

    enum TypeObject {
        AllObject = 0,//"Все",
        SD = 1,//"СД",
        IU = 2,//"ИУ",
        RIFRLM = 3,//"РИФ-РЛМ(КРЛ), Трасса",
        SDCollector = 4,//"СД концентратора",
        Toros = 5,//"Торос",
        Nast = 6,//"Наст",
        Radar = 7,//"Радар",
        RazrivBO = 8,//"Разрыв БО",
        TochkaGard = 9,//"Точка/Гарда",
        Adam = 10,//"Адам-406x/4168",
        SDBLIP = 11,//"СД БЛ-IP",
        IUBLIP = 12,//"ИУ БЛ-IP",
        RIFRLMS = 13,//"РИФ-РЛМ-С",
        BODTochkaM = 14,//"БОД Точка-М/Гарда-М",
        DDTochkaM = 15,//"ДД Точка-М/Гарда-М",
        BODSota = 16,//"БОД Сота/Сота-М",
        DDSota = 17//"ДД Сота/Сота-М"
    };

    enum TypeEvent {
        AllEvent = 0,//"Все"
        Alarm = 1,//"Тревоги"
        AlarmWorked = 2,//"Тревога - СРАБОТКА"
        AlarmOpening = 3,//"Тревога - ВСКРЫТИЕ"
        Fault = 4,//"Неисправности"
        FaultNoConnect = 5,//"Нет связи"
        FaultDK = 6,//"Ком. ДК не выполнена"
        FaultCommand = 7,//"Ком. упр. не выполнена"
        Command = 8,//"Команды"
        CommandDK = 9,//"ДК"
        CommandUZMonolit = 10,//"УЗ Монолит"
        CommandOperator = 11//"Оператор"
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

private:

signals:
};

#endif // JOURENTITY_H
