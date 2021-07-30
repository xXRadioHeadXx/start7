#include <QByteArray>

#include "TableModelMSG.h"
#include "DataBaseManager.h"
#include "SignalSlotCommutator.h"
#include "Icons.h"

std::list<JourEntity> TableModelMSG::m_listMSG = std::list<JourEntity>();


QFont TableModelMSG::getFont() const
{
    return font;
}

void TableModelMSG::setFont(const QFont &value)
{
    font = value;
}

std::list<JourEntity> TableModelMSG::getListMSG()
{
    return m_listMSG;
}

bool TableModelMSG::getForegroundRoleFlag() const
{
    return foregroundRoleFlag;
}

void TableModelMSG::setForegroundRoleFlag(bool value)
{
    foregroundRoleFlag = value;
}

bool TableModelMSG::getDecorationRoleFlag() const
{
    return decorationRoleFlag;
}

void TableModelMSG::setDecorationRoleFlag(bool value)
{
    decorationRoleFlag = value;
}

TableModelMSG::TableModelMSG(QObject *parent) :
    QAbstractTableModel(parent)
{
    needScroll = true;
    m_listMSG = DataBaseManager::getOneMSGRecord();

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

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(updJourMSG()),
            this,
            SLOT(updateAllRecords()));

    connect(SignalSlotCommutator::getInstance(),
            SIGNAL(updAllJourMSG()),
            this,
            SLOT(updateAllRecords()));

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

    QVariant result;


    // закрасим строчку по io признаку
    if (role == Qt::BackgroundRole)
    {
        QColor resultColor(Qt::white);
        result = resultColor;
        return result;
    }

    int row(index.row());
    if(row + 1 > m_listMSG.size())
    {
        return result;
    }
    auto it = std::next(m_listMSG.begin(), row);
    const JourEntity msgRecord = *it;

    if(Qt::FontRole == role) {
        QFont font = getFont();

        return font;
    }

    if (Qt::ForegroundRole == role && getForegroundRoleFlag()) {
        if(0 != msgRecord.getFlag()) {
            return msgRecord.getColor();
        }
    }

    // выводим в консоль текущие значения параметров и считаем, сколько
    // раз вызывается метод TableModelArchiveMSG::data и для каких ролей



    // Если необходимо отобразить картинку - ловим роль Qt::DecorationRole
    if (index.isValid() && role == Qt::DecorationRole && getDecorationRoleFlag()) {
        switch(index.column())
        {
            case 0:
            {
                if(0 != msgRecord.getFlag()) {
                    return msgRecord.getPxm();
                }
                return result;
            };
            default:
                return result;
        }
    }
//    // Если хотим отобразить CheckBox, используем роль Qt::CheckStateRole
//    // если текущий вызов не относится к роли отображения, завершаем
//    if (!index.isValid() || role != Qt::DisplayRole)
//        return result;

    if ((role == Qt::DisplayRole || role == Qt::EditRole))
    {
        // устанавливаем соответствие между номером столбца и полем записи
        return msgRecord.data(index.column());
    }

    return result;
}

// Функция для приёма данных от пользователя
bool TableModelMSG::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto it = std::next(m_listMSG.begin(), index.row());
    if (role == Qt::EditRole) {
        if (index.column() == 4)
                (*it).setReason(value.toString());
        else if (index.column() == 5)
                (*it).setMeasures(value.toString());
        else
            return false;

//        m_listMSG.replace(index.row(), item);

        DataBaseManager::updateJourMsg(*it);
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole << Qt::EditRole);
        return true;
    }
    return false;
}

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
                return tr("Дата"); //"Дата";
            case 2:
                return tr("Сообщение"); //"Сообщение";
            case 3:
                return tr("Объект"); //"Объект";
            case 4:
                return tr("Причина"); //"Причина";
            case 5:
                return tr("Принятые меры"); //"Принятые меры"
            case 6:
                return tr("Оператор"); //"Оператор"
            default:
                return QVariant();
        }
    }

    return QVariant();
};

// возможность редактирования элемента
Qt::ItemFlags TableModelMSG::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    // разрешаем редактирование
    if(4 == index.column() || 5 == index.column())
        result |= Qt::ItemIsEditable;
    return result;
}

//добавление строки
bool TableModelMSG::insertRows(int row, int count, const QModelIndex &parent)
{
    if(1 == count)
    {
        this->beginInsertRows(parent, row, row);

        auto tmp = DataBaseManager::getOneMSGRecord(newRecordMSG);
        if(!tmp.empty()) {
            auto it = std::next(m_listMSG.begin(), row);
            m_listMSG.insert(it, tmp.front());
        }

        this->endInsertRows();
        return true;
    }
    return false;
}

void TableModelMSG::castomUpdateListRecords(QString sql)
{
//    int lastRecordMSG = -1;

    auto newRecords(DataBaseManager::getQueryMSGRecord(sql));


    this->beginResetModel();

    m_listMSG = newRecords;
//    if(!newRecords.isEmpty()) {
//        lastRecordMSG = m_listMSG.last()->getId();
//    }

    this->endResetModel();

    emitNeedScrollToBottom();
}

void TableModelMSG::updateAllRecords()
{
    auto newRecords(DataBaseManager::getMSGRecordAfter(DataBaseManager::getIdStartLastDuty() - 1));

    if(newRecords.empty())
        return;

    this->beginResetModel();

    m_listMSG = newRecords;

    this->endResetModel();

    emitNeedScrollToBottom();
}


//обновление выборки
void TableModelMSG::updateListRecords()
{
    int lastRecordMSG = -1;
    if(!m_listMSG.empty())
        lastRecordMSG = m_listMSG.back().getId();


    auto newRecords(DataBaseManager::getMSGRecordAfter(lastRecordMSG));

    if(newRecords.empty())
        return;

    this->beginInsertRows(QModelIndex(), m_listMSG.size(), m_listMSG.size() + newRecords.size() - 1);

    m_listMSG.insert(m_listMSG.end(), newRecords.begin(), newRecords.end());

    this->endInsertRows();

    emitNeedScrollToBottom();
}

void TableModelMSG::updateListRecords(const quint32 idMSG)
{
    newRecordMSG = idMSG;
//    auto newRecords(DataBaseManager::getOneMSGRecord(idMSG));

    this->insertRows(this->rowCount());

    emitNeedScrollToBottom();
}

void TableModelMSG::updateRecord(const quint32 idMSG)
{
    updRecordMSG = idMSG;
    auto updRecord(DataBaseManager::getOneMSGRecord(idMSG));

    if(updRecord.empty())
        return;

    int i = 0;
    for(auto it = m_listMSG.begin(); it != m_listMSG.end(); it++, i++) {
        auto &target = *it;
        if(target.getId() == updRecord.front().getId()) {
            target = updRecord.front();
            emit this->dataChanged(this->index(i, 0, QModelIndex()), this->index(i, 6, QModelIndex()));
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
    m_listMSG = DataBaseManager::getOneMSGRecord();
    this->endResetModel();
}

JourEntity TableModelMSG::clickedMsg(const QModelIndex &index)
{
    if (!index.isValid())
        return nullptr;

    const JourEntity item = *std::next(m_listMSG.begin(), index.row());

//    JourEntity item = static_cast<JourEntity>(index.internalPointer());
    if(0 != item.getId())
    {
        emit selectedMsg(item);
        return item;
    }
    return nullptr;
}
