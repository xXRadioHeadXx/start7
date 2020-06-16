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
//    virtual  bool  setData(QModelIndex index, QVariant value, int role);
    // отображение   названий   столбцов
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role) const;
    // возможность редактирования элемента
    virtual Qt::ItemFlags flags(QModelIndex index);
    // добавление новой строки
    virtual bool insertRows(int row, int count = 1, const QModelIndex &parent = QModelIndex());

signals:
    void needScrollToBottom();
    void selectedMsg(QList<JourEntity *> listUN);
    void selectedMsg(JourEntity* msg);

public slots:
    //обновление выборки
    void updateListRecords();
    void updateListRecords(const quint32 idMSG);
    void updateRecord(const quint32 idMSG);
    void setNeedScroll(bool value);
    void emitNeedScrollToBottom();
    void needResetModel();
    JourEntity *clickedMsg(const QModelIndex &index);

};

#endif // TABLEMODELARCHIVEMSG_H
