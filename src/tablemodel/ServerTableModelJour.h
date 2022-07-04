#ifndef SERVERTABLEMODELJOUR_H
#define SERVERTABLEMODELJOUR_H

#include <QAbstractItemModel>
#include "../src/entity/JourEntity.h"
#include <QFont>

enum class SwitchOffCondition {
    AlvaysOn = 0,
    AlvaysOff = 1,
    RegularOn = 2,
    RegularOff = 3
};

class ServerTableModelJour : public QAbstractTableModel
{
    Q_OBJECT

    static QList<JourEntity> m_listJour;
    uint32_t newRecordMSG;
    uint32_t updRecordMSG;
    bool needScroll;
    QFont font;
    bool enabledReasonMeasure = true;

    SwitchOffCondition foregroundRoleFlag = SwitchOffCondition::RegularOn;
    SwitchOffCondition decorationRoleFlag = SwitchOffCondition::RegularOn;
public:
    explicit ServerTableModelJour(QObject *parent = nullptr, bool firstLoad = true);
    ~ServerTableModelJour();


    void updateListRecordsMSG();
    void updateFilter();
    // количество строк. Устанавливаем так, чтобы скроллер отображался корректно
    virtual int rowCount(const QModelIndex &index = QModelIndex()) const;
    // устанавливаем количество столбцов.
    virtual int columnCount(const QModelIndex &index = QModelIndex()) const;
    // функция для передачи данных пользователю
    virtual QVariant data(const QModelIndex &index, int role) const;
    // Функция для приёма данных от пользователя
    virtual  bool  setData(const QModelIndex &index, const QVariant &value, int role);
    // отображение   названий   столбцов
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role) const;
    // возможность редактирования элемента
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    // добавление новой строки
    virtual bool insertRows(int row, int count = 1, const QModelIndex &parent = QModelIndex());
    virtual bool insertRows(JourEntity msg,int row, int count = 1, const QModelIndex &parent = QModelIndex());

    QFont getFont() const;
    void setFont(const QFont &value);

    static QList<JourEntity> getListJour();

    SwitchOffCondition getForegroundRoleFlag() const;
    void setForegroundRoleFlag(SwitchOffCondition value);

    SwitchOffCondition getDecorationRoleFlag() const;
    void setDecorationRoleFlag(SwitchOffCondition value);

    inline QModelIndex index(int row, int column, const QModelIndex &parent) const {
        if(hasIndex(row, column, parent))
            return createIndex(row, column);
        else
            return QModelIndex();
    }
    inline QModelIndex parent(const QModelIndex &) const { return QModelIndex(); }

    bool getNeedScroll() const;

    JourEntity indexToJour(const QModelIndex &index) const;
    QList<JourEntity> listIndexsToListJours(const QModelIndexList &listIndex) const;
    bool getEnabledReasonMeasure() const;
    void setEnabledReasonMeasure(bool newEnabledReasonMeasure);
    bool enable_updateListRecords();
signals:
    void needScrollToBottom();
    void selectedMsg(QList<JourEntity> listUN);
    void selectedMsg(JourEntity msg);
    void dataChangedReason(JourEntity msg);
    void dataChangedMeasures(JourEntity msg);
    void recalcSelectedMsg();



public slots:
    //обновление выборки
    void castomUpdateListRecords(QString sql);
    void updateAllRecords();
    void updateListRecords();
    void updateListRecords(JourEntity msg);
    void updateListRecords(const uint32_t idMSG);
    void updateRecord(const uint32_t idMSG);
    void setNeedScroll(bool value);
    void emitNeedScrollToBottom();
    void needResetModel();
    JourEntity clickedMsg(const QModelIndex &index);
    JourEntity selectOnedMsg(const JourEntity &msg);

};

#endif // SERVERTABLEMODELJOUR_H
