#ifndef TABLEMODELARCHIVEMSG_H
#define TABLEMODELARCHIVEMSG_H

#include <QAbstractItemModel>

#include <DataBaseManager.h>

class TableModelMSG : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModelMSG(QObject *parent = nullptr);
    ~TableModelMSG();

    QList<JourEntity *> m_listMSG;
    quint32 newRecordMSG;
    quint32 updRecordMSG;
    bool needScroll;

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

signals:
    void needScrollToBottom();
    void selectedMsg(QList<JourEntity *> listUN);
    void selectedMsg(JourEntity* msg);

public slots:
    //обновление выборки
    void castomUpdateListRecords(QString sql);
    void updateListRecords();
    void updateListRecords(const quint32 idMSG);
    void updateRecord(const quint32 idMSG);
    void setNeedScroll(bool value);
    void emitNeedScrollToBottom();
    void needResetModel();
    JourEntity *clickedMsg(const QModelIndex &index);
    inline QModelIndex index(int row, int column, const QModelIndex &parent) const { return hasIndex(row, column, parent) ? createIndex(row, column, m_listMSG[row]) : QModelIndex(); }
    inline QModelIndex parent(const QModelIndex &) const { return QModelIndex(); }

};

#endif // TABLEMODELARCHIVEMSG_H
