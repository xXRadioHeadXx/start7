#include <QByteArray>

#include <TableModelMSG.h>
#include <SignalSlotCommutator.h>

TableModelMSG::TableModelMSG(QObject *parent) :
    QAbstractTableModel(parent)
{
    needScroll = true;
    m_listMSG = DataBaseManager::getMSGRecord();

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(insNewJourMSG(const quint32)),
            this,
            SLOT(updateListRecords(const quint32)));

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(insNewJourMSG()),
            this,
            SLOT(updateListRecords()));

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(updJourMSG(const quint32)),
            this,
            SLOT(updateRecord(const quint32)));
}

void TableModelMSG::needResetModel()
{
    this->beginResetModel();
    this->endResetModel();
}

TableModelMSG::~TableModelMSG()
{
    newRecordMSG = 0;
    needScroll = false;
    m_listMSG.clear();
}

// количество строк. Устанавливаем так, чтобы скроллер отображался корректно
int TableModelMSG::rowCount(const QModelIndex &index) const
{
    if(index.isValid())
    {
        return m_listMSG.size();
    }
    return m_listMSG.size();
}

// устанавливаем количество столбцов.
int TableModelMSG::columnCount(const QModelIndex &index) const
{
    if(index.isValid())
    {
        return 7;
    }
    return 7;
}

// функция для передачи данных пользователю
QVariant TableModelMSG::data(const QModelIndex &index, int role) const
{
    int row(index.row());
    QVariant result;
    if(row + 1 > m_listMSG.size())
    {
        return result;
    }
    JourEntity * msgRecord = m_listMSG.at(row);


    // выводим в консоль текущие значения параметров и считаем, сколько
    // раз вызывается метод TableModelArchiveMSG::data и для каких ролей

    // закрасим строчку по io признаку
    if (role == Qt::BackgroundRole)
    {
        QColor resultColor(Qt::white);
        result = resultColor;
        return result;
    }
    // Если необходимо отобразить картинку - ловим роль Qt::DecorationRole
    if (index.isValid() && role == Qt::DecorationRole) {
        switch(index.column())
        {
            case 0:
            {
                if(msgRecord->getStatus().isEmpty()) {
                    return result;
                }
                return result;
            };
            default:
                return result;
        }
    }
    // Если хотим отобразить CheckBox, используем роль Qt::CheckStateRole
    // если текущий вызов не относится к роли отображения, завершаем
    if (!index.isValid() || role != Qt::DisplayRole)
        return result;

    if (index.isValid() && role == Qt::DisplayRole)
    {
        // устанавливаем соответствие между номером столбца и полем записи
        return msgRecord->data(index.column());
    }

    return result;
}

// Функция для приёма данных от пользователя
//bool TableModelArchiveMSG::setData(QModelIndex index, QVariant value, int role)
//{
//    if(index.isValid() && value.isValid() && (-1 != role))
//        return false;
//    return false;
//}

// отображение   названий   столбцов
QVariant TableModelMSG::headerData(int section, Qt::Orientation orientation, int role) const
{
    // Для любой роли, кроме запроса на отображение, прекращаем обработку
    if (role != Qt::DisplayRole)
        return QVariant();

    // формируем заголовки по номуру столбца
    if (orientation == Qt::Horizontal)
    {
        switch(section)
        {
            case 0:
                return "№/#";
            case 1:
                return trUtf8("Дата"); //"Дата";
            case 2:
                return trUtf8("Сообщение"); //"Сообщение";
            case 3:
                return trUtf8("Объект"); //"Объект";
            case 4:
                return trUtf8("Причина"); //"Причина";
            case 5:
                return trUtf8("Принятые меры"); //"Принятые меры"
            case 6:
                return trUtf8("Оператор"); //"Оператор"
            default:
                return QVariant();
        }
    }

    return QVariant();
};

// возможность редактирования элемента
Qt::ItemFlags TableModelMSG::flags(QModelIndex index)
{
    Qt::ItemFlags result;
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    // разрешаем редактирование всего, кроме первого столбца
    result = QAbstractTableModel::flags(index);
    result |= Qt::ItemIsEditable;
    return result;
}

//добавление строки
bool TableModelMSG::insertRows(int row, int count, const QModelIndex &parent)
{
    if(1 == count)
    {
        this->beginInsertRows(parent, row, row);

        QList<JourEntity *> tmp = DataBaseManager::getMSGRecord(newRecordMSG);
        if(!tmp.isEmpty())
            m_listMSG.insert(row, tmp.first());

        this->endInsertRows();
        return true;
    }
    return false;
}


//обновление выборки
void TableModelMSG::updateListRecords()
{
    int lastRecordMSG = m_listMSG.last()->getId();

    QList<JourEntity *> newRecords(DataBaseManager::getMSGRecordAfter(lastRecordMSG));

    if(newRecords.isEmpty())
        return;

    this->beginInsertRows(QModelIndex(), m_listMSG.size(), m_listMSG.size() + newRecords.size() - 1);

    m_listMSG.append(newRecords);

    this->endInsertRows();

    emitNeedScrollToBottom();
}

void TableModelMSG::updateListRecords(const quint32 idMSG)
{
    newRecordMSG = idMSG;
    QList<JourEntity *> newRecords(DataBaseManager::getMSGRecord(idMSG));

    this->insertRows(this->rowCount());

    emitNeedScrollToBottom();
}

void TableModelMSG::updateRecord(const quint32 idMSG)
{
    updRecordMSG = idMSG;
    QList<JourEntity *> updRecord(DataBaseManager::getMSGRecord(idMSG));

    if(updRecord.isEmpty())
        return;

    for(int i = 0, n = m_listMSG.size(); i < n; i++) {
        JourEntity * target = m_listMSG.at(i);
        if(target->getId() == updRecord.first()->getId()) {
            *target = *updRecord.first();
            emit this->dataChanged(this->index(i, 0), this->index(i, 6));
            break;
        }
    }
}


void TableModelMSG::setNeedScroll(bool value)
{
    needScroll = value;
}

void TableModelMSG::emitNeedScrollToBottom()
{
    if(needScroll)
    {
        emit this->needScrollToBottom();
    }
}

void TableModelMSG::updateListRecordsMSG()
{
    this->beginResetModel();
    m_listMSG = DataBaseManager::getMSGRecord();
    this->endResetModel();
}

JourEntity * TableModelMSG::clickedMsg(const QModelIndex &index)
{
    if (!index.isValid())
        return nullptr;

    JourEntity *item = m_listMSG.at(index.row());

//    JourEntity *item = static_cast<JourEntity*>(index.internalPointer());
    if(item)
    {
        emit selectedMsg(item);
        return item;
    }
    return nullptr;
}
