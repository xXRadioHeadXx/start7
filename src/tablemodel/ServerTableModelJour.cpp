#include <QByteArray>

#include <ServerTableModelJour.h>
#include <DataBaseManager.h>
#include <SignalSlotCommutator.h>
#include <Icons.h>
#include <ServerSettingUtils.h>

QList<JourEntity> ServerTableModelJour::m_listJour = QList<JourEntity>();


QFont ServerTableModelJour::getFont() const
{
    return font;
}

void ServerTableModelJour::setFont(const QFont &value)
{
    font = value;
}

QList<JourEntity> ServerTableModelJour::getListJour()
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
#ifdef QT_DEBUG
    Q_UNUSED(index)
    return 9;
#endif
    if(index.isValid())
    {
        return 7;
    }
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
    const JourEntity msgRecord = m_listJour.at(row);

    // закрасим строчку по io признаку
    if (role == Qt::BackgroundRole && (4 == index.column() || 5 == index.column()))
    {
        QColor resultColor(Qt::white);

        int needReason = ServerSettingUtils::getValueSettings("P1", "PostgresSQL").toInt();
        int needMeasure = ServerSettingUtils::getValueSettings("P2", "PostgresSQL").toInt();
        if(0 != needReason || 0 != needMeasure) {
            if(0 != needReason && 4 == index.column() && 1 == msgRecord.getFlag() && ServerSettingUtils::getPriorityJoutTyper().contains(msgRecord.getType()) && msgRecord.data(index.column()).toString().isEmpty()) {
                resultColor.setRgb(0xF0E68C);
            } else if (0 != needMeasure && 5 == index.column() && 1 == msgRecord.getFlag() && ServerSettingUtils::getPriorityJoutTyper().contains(msgRecord.getType()) && msgRecord.data(index.column()).toString().isEmpty()) {
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
    if (role == Qt::EditRole) {
        if (index.column() == 4)
                m_listJour[index.row()].setReason(value.toString());
        else if (index.column() == 5)
                m_listJour[index.row()].setMeasures(value.toString());
        else
            return false;

//        m_listMSG.replace(index.row(), item);

        DataBaseManager::updateJourMsg(m_listJour[index.row()]);
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

        QList<JourEntity> tmp = DataBaseManager::getOneMSGRecord(newRecordMSG);
        if(!tmp.isEmpty())
            m_listJour.insert(row, tmp.first());

        this->endInsertRows();
        return true;
    }
    return false;
}

void ServerTableModelJour::castomUpdateListRecords(QString sql)
{
//    int lastRecordMSG = -1;

    QList<JourEntity> newRecords(DataBaseManager::getQueryMSGRecord(sql));


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
    QList<JourEntity> newRecords(DataBaseManager::getMSGRecordAfter(DataBaseManager::getIdStartLastDuty() - 1));

    if(newRecords.isEmpty())
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
    if(!m_listJour.isEmpty())
        lastRecordMSG = m_listJour.last().getId();


    QList<JourEntity> newRecords(DataBaseManager::getMSGRecordAfter(lastRecordMSG));

    if(newRecords.isEmpty())
        return;

    this->beginInsertRows(QModelIndex(), m_listJour.size(), m_listJour.size() + newRecords.size() - 1);

    m_listJour.append(newRecords);

    this->endInsertRows();

    emitNeedScrollToBottom();
}

void ServerTableModelJour::updateListRecords(const quint32 idMSG)
{
    newRecordMSG = idMSG;
//    QList<JourEntity> newRecords(DataBaseManager::getOneMSGRecord(idMSG));

    this->insertRows(this->rowCount());

    emitNeedScrollToBottom();
}

void ServerTableModelJour::updateRecord(const quint32 idMSG)
{
    updRecordMSG = idMSG;
    QList<JourEntity> updRecord(DataBaseManager::getOneMSGRecord(idMSG));

    if(updRecord.isEmpty())
        return;

    for(int i = 0, n = m_listJour.size(); i < n; i++) {
        JourEntity target = m_listJour.at(i);
        if(target.getId() == updRecord.first().getId()) {
            m_listJour[i] = updRecord.first();
#ifdef QT_DEBUG
            emit this->dataChanged(this->index(i, 0, QModelIndex()), this->index(i, 8, QModelIndex()));
#else
            emit this->dataChanged(this->index(i, 0, QModelIndex()), this->index(i, 6, QModelIndex()));
#endif

            break;
        }
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

QList<JourEntity> ServerTableModelJour::listIndexsToListJours(const QModelIndexList &listIndex) const {
    QList<JourEntity> list;
    for(const auto index : listIndex) {
        list.append(indexToJour(index));
    }

    return list;
}

JourEntity ServerTableModelJour::indexToJour(const QModelIndex &index) const {
    if (!index.isValid())
        return nullptr;

    const JourEntity item = m_listJour.at(index.row());

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
