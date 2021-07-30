#include <QByteArray>

#include "ServerTableModelJour.h"
#include "DataBaseManager.h"
#include "SignalSlotCommutator.h"
#include "Icons.h"
#include "ServerSettingUtils.h"

std::list<JourEntity> ServerTableModelJour::m_listJour = std::list<JourEntity>();


QFont ServerTableModelJour::getFont() const
{
    return font;
}

void ServerTableModelJour::setFont(const QFont &value)
{
    font = value;
}

std::list<JourEntity> ServerTableModelJour::getListJour()
{
    return m_listJour;
}

bool ServerTableModelJour::getForegroundRoleFlag() const
{
    return foregroundRoleFlag;
}

void ServerTableModelJour::setForegroundRoleFlag(bool value)
{
    foregroundRoleFlag = value;
}

bool ServerTableModelJour::getDecorationRoleFlag() const
{
    return decorationRoleFlag;
}

void ServerTableModelJour::setDecorationRoleFlag(bool value)
{
    decorationRoleFlag = value;
}

bool ServerTableModelJour::getNeedScroll() const
{
    return needScroll;
}

ServerTableModelJour::ServerTableModelJour(QObject *parent) :
    QAbstractTableModel(parent)
{
    needScroll = true;
    m_listJour = DataBaseManager::getOneMSGRecord();

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

void ServerTableModelJour::needResetModel()
{
    this->beginResetModel();
    this->endResetModel();
}

ServerTableModelJour::~ServerTableModelJour()
{
    newRecordMSG = 0;
    needScroll = false;
    m_listJour.clear();
}

// количество строк. Устанавливаем так, чтобы скроллер отображался корректно
int ServerTableModelJour::rowCount(const QModelIndex &index) const
{
    if(index.isValid())
    {
        return m_listJour.size();
    }
    return m_listJour.size();
}

// устанавливаем количество столбцов.
int ServerTableModelJour::columnCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
#ifdef QT_DEBUG
    return 9;
#endif
    return 7;
}

// функция для передачи данных пользователю
QVariant ServerTableModelJour::data(const QModelIndex &index, int role) const
{

    QVariant result;



    int row(index.row());
    if(row + 1 > m_listJour.size())
    {
        return result;
    }
    auto it = std::next(m_listJour.begin(), row);
    const JourEntity msgRecord = *it;

    // закрасим строчку по io признаку
    if (role == Qt::BackgroundRole && (4 == index.column() || 5 == index.column()))
    {
        QColor resultColor(Qt::white);

        int needReason = ServerSettingUtils::getValueSettings("P1", "PostgresSQL").toInt();
        int needMeasure = ServerSettingUtils::getValueSettings("P2", "PostgresSQL").toInt();
        if(0 != needReason || 0 != needMeasure) {
            if(0 != needReason && 4 == index.column() && ServerSettingUtils::getPriorityJoutTyper().end() != ServerSettingUtils::getPriorityJoutTyper().find(msgRecord.getType()) && msgRecord.getReason().isEmpty()) {
                resultColor.setRgb(0xF0E68C);
            } else if (0 != needMeasure && 5 == index.column() && ServerSettingUtils::getPriorityJoutTyper().end() != ServerSettingUtils::getPriorityJoutTyper().find(msgRecord.getType()) && msgRecord.getMeasures().isEmpty()) {
                resultColor.setRgb(0xF0E68C);
            }
        }

        result = resultColor;
        return result;
    }

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
        #ifdef QT_DEBUG
            if(7 == index.column()) {
                return msgRecord.getFlag();
            } else if(8 == index.column()) {
                return msgRecord.getType();
            } else {
                return msgRecord.data(index.column());
            }
        #else
            return msgRecord.data(index.column());
        #endif
    }

    return result;
}

// Функция для приёма данных от пользователя
bool ServerTableModelJour::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto it = std::next(m_listJour.begin(), index.row());
    if (role == Qt::EditRole) {
        if (index.column() == 4) {
            (*it).setReason(value.toString());
        } else if (index.column() == 5) {
            (*it).setMeasures(value.toString());
        } else {
            return false;
        }

//        m_listMSG.replace(index.row(), item);

        DataBaseManager::updateJourMsg((*it));
        emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole << Qt::EditRole);

        if (index.column() == 4)
                emit dataChangedReason(indexToJour(index));
        else if (index.column() == 5)
                emit dataChangedMeasures(indexToJour(index));
        emit recalcSelectedMsg();
        return true;
    }
    return false;
}

// отображение   названий   столбцов
QVariant ServerTableModelJour::headerData(int section, Qt::Orientation orientation, int role) const
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
Qt::ItemFlags ServerTableModelJour::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    // разрешаем редактирование
    if(4 == index.column() || 5 == index.column())
        result |= Qt::ItemIsEditable;
    return result;
}

//добавление строки
bool ServerTableModelJour::insertRows(int row, int count, const QModelIndex &parent)
{
    if(1 == count)
    {
        this->beginInsertRows(parent, row, row);

        auto tmp = DataBaseManager::getOneMSGRecord(newRecordMSG);
        if(!tmp.empty()) {
            auto it = std::next(m_listJour.begin(), row);
            m_listJour.insert(it, tmp.front());
        }
        this->endInsertRows();
        return true;
    }
    return false;
}

void ServerTableModelJour::castomUpdateListRecords(QString sql)
{
//    int lastRecordMSG = -1;

    auto newRecords(DataBaseManager::getQueryMSGRecord(sql));


    this->beginResetModel();

    m_listJour = newRecords;
//    if(!newRecords.isEmpty()) {
//        lastRecordMSG = m_listMSG.last()->getId();
//    }

    this->endResetModel();

    emitNeedScrollToBottom();
}

void ServerTableModelJour::updateAllRecords()
{
    auto newRecords(DataBaseManager::getMSGRecordAfter(DataBaseManager::getIdStartLastDuty() - 1));

    if(newRecords.empty())
        return;

    this->beginResetModel();

    m_listJour = newRecords;

    this->endResetModel();

    emitNeedScrollToBottom();
}


//обновление выборки
void ServerTableModelJour::updateListRecords()
{
    int lastRecordMSG = -1;
    if(!m_listJour.empty())
        lastRecordMSG = m_listJour.back().getId();


    auto newRecords(DataBaseManager::getMSGRecordAfter(lastRecordMSG));

    if(newRecords.empty())
        return;

    this->beginInsertRows(QModelIndex(), m_listJour.size(), m_listJour.size() + newRecords.size() - 1);

    m_listJour.insert(m_listJour.end(), newRecords.begin(), newRecords.end());

    this->endInsertRows();

    emitNeedScrollToBottom();
}

void ServerTableModelJour::updateListRecords(const quint32 idMSG)
{
    newRecordMSG = idMSG;
//    auto newRecords(DataBaseManager::getOneMSGRecord(idMSG));

    this->insertRows(this->rowCount());

    emitNeedScrollToBottom();
}

void ServerTableModelJour::updateRecord(const quint32 idMSG)
{
    updRecordMSG = idMSG;
    auto updRecord(DataBaseManager::getOneMSGRecord(idMSG));

    if(updRecord.empty())
        return;

    auto it = m_listJour.begin();
    for(int i = 0, n = m_listJour.size(); i < n; i++, it++) {
        JourEntity &target = *it;
        if(target.getId() == updRecord.front().getId()) {
            target = updRecord.front();
#ifdef QT_DEBUG
            emit this->dataChanged(this->index(i, 0, QModelIndex()), this->index(i, 8, QModelIndex()));
#else
            emit this->dataChanged(this->index(i, 0, QModelIndex()), this->index(i, 6, QModelIndex()));
#endif

            break;
        }
        ++it;
    }
}


void ServerTableModelJour::setNeedScroll(bool value)
{
    needScroll = value;
    emitNeedScrollToBottom();
}

void ServerTableModelJour::emitNeedScrollToBottom()
{
    if(needScroll)
    {
        emit this->needScrollToBottom();
    }
}

void ServerTableModelJour::updateListRecordsMSG()
{
    this->beginResetModel();
    m_listJour = DataBaseManager::getOneMSGRecord();
    this->endResetModel();
}

std::list<JourEntity> ServerTableModelJour::listIndexsToListJours(const QModelIndexList &listIndex) const {
    std::list<JourEntity> list;
    for(const auto index : listIndex) {
        list.push_back(indexToJour(index));
    }

    return list;
}

JourEntity ServerTableModelJour::indexToJour(const QModelIndex &index) const {
    if (!index.isValid())
        return nullptr;

    auto it = std::next(m_listJour.begin(), index.row());
    const JourEntity item = *it;

    return item;
}


JourEntity ServerTableModelJour::clickedMsg(const QModelIndex &index)
{
    if (!index.isValid())
        return JourEntity();

    const JourEntity item = indexToJour(index);

    selectOnedMsg(item);

    return item;
}

JourEntity ServerTableModelJour::selectOnedMsg(const JourEntity &msg)
{
    if(0 != msg.getId())
    {
        emit selectedMsg(msg);
    }
    return msg;
}
