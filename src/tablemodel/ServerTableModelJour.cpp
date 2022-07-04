#include "../src/utils/IniFileService.h"
#include <QByteArray>

#include "../src/tablemodel/ServerTableModelJour.h"
#include "../src/database/DataBaseManager.h"
#include "../src/utils/SignalSlotCommutator.h"
#include "../src/utils/Icons.h"
#include "../src/utils/ServerSettingUtils.h"

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

SwitchOffCondition ServerTableModelJour::getForegroundRoleFlag() const
{
    return foregroundRoleFlag;
}

void ServerTableModelJour::setForegroundRoleFlag(SwitchOffCondition value)
{
    foregroundRoleFlag = value;
}

SwitchOffCondition ServerTableModelJour::getDecorationRoleFlag() const
{
    return decorationRoleFlag;
}

void ServerTableModelJour::setDecorationRoleFlag(SwitchOffCondition value)
{
    decorationRoleFlag = value;
}

bool ServerTableModelJour::getNeedScroll() const
{
    return needScroll;
}

bool ServerTableModelJour::getEnabledReasonMeasure() const
{
    return enabledReasonMeasure;
}

void ServerTableModelJour::setEnabledReasonMeasure(bool newEnabledReasonMeasure)
{
    enabledReasonMeasure = newEnabledReasonMeasure;
}

bool ServerTableModelJour::enable_updateListRecords()
{
    connect(&SignalSlotCommutator::instance(),
            SIGNAL(insNewJourMSG(uint32_t)),
            this,
            SLOT(updateListRecords(uint32_t)));

    updateListRecords();
}

ServerTableModelJour::ServerTableModelJour(QObject *parent, bool firstLoad) :
    QAbstractTableModel(parent)
{
    needScroll = true;
    if(firstLoad)
        m_listJour = DataBaseManager::getOneMSGRecord();


/*
    connect(&SignalSlotCommutator::instance(),
            SIGNAL(insNewJourMSG(uint32_t)),
            this,
            SLOT(updateListRecords(uint32_t)));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(insNewJourMSG()),
            this,
            SLOT(updateListRecords()));
*/

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(insNewJourMSG(JourEntity)),
            this,
            SLOT(updateListRecords(JourEntity)));



    connect(&SignalSlotCommutator::instance(),
            SIGNAL(updJourMSG(uint32_t)),
            this,
            SLOT(updateRecord(uint32_t)));

    connect(&SignalSlotCommutator::instance(),
            SIGNAL(updJourMSG()),
            this,
            SLOT(updateAllRecords()));

    connect(&SignalSlotCommutator::instance(),
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
    const JourEntity msgRecord = m_listJour.at(row);

    // закрасим строчку по io признаку
    if (role == Qt::BackgroundRole && (4 == index.column() || 5 == index.column()))
    {
        QColor resultColor(Qt::white);

        int needReason = IniFileService::getValueBySectionKey("PostgresSQL", "P1", "0").toInt();
        int needMeasure = IniFileService::getValueBySectionKey("PostgresSQL", "P2", "0").toInt();
        if(0 != needReason || 0 != needMeasure) {
            if(0 != needReason && 4 == index.column() && ServerSettingUtils::getPriorityJoutTyper().contains(msgRecord.getType()) && msgRecord.getReason().isEmpty()) {
                resultColor.setRgb(0xF0E68C);
            } else if (0 != needMeasure && 5 == index.column() && ServerSettingUtils::getPriorityJoutTyper().contains(msgRecord.getType()) && msgRecord.getMeasures().isEmpty()) {
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

    if (Qt::ForegroundRole == role && (SwitchOffCondition::AlvaysOn == getForegroundRoleFlag() || SwitchOffCondition::RegularOn == getForegroundRoleFlag())) {
        if(0 != msgRecord.getFlag() || SwitchOffCondition::AlvaysOn == getForegroundRoleFlag()) {
            return msgRecord.getColor();
        }
    }

    // выводим в консоль текущие значения параметров и считаем, сколько
    // раз вызывается метод TableModelArchiveMSG::data и для каких ролей



    // Если необходимо отобразить картинку - ловим роль Qt::DecorationRole
    if (index.isValid() && role == Qt::DecorationRole && (SwitchOffCondition::AlvaysOn == getDecorationRoleFlag() || SwitchOffCondition::RegularOn == getDecorationRoleFlag())) {
        switch(index.column())
        {
            case 0:
            {
                if(0 != msgRecord.getFlag() || SwitchOffCondition::AlvaysOn == getDecorationRoleFlag()) {
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
    if(getEnabledReasonMeasure() && (4 == index.column() || 5 == index.column()))
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

bool ServerTableModelJour::insertRows(JourEntity msg, int row, int count, const QModelIndex &parent)
{
    qDebug()<<"ServerTableModelJour::insertRows(JourEntity msg, ...)";


    if(1 == count)
    {
        if(m_listJour.count()>0)
        msg.setId(m_listJour.last().getId()+1);
        else
        msg.setId(0);

        qDebug()<<"                          ";

        qDebug()<<"msg.getId(): "<<msg.getId();
        qDebug()<<msg.getCdate();
        qDebug()<<msg.getComment();
        qDebug()<<msg.getDirection();
        qDebug()<<msg.getReason();
        qDebug()<<msg.getStatus();
        qDebug()<<msg.getType();

        this->beginInsertRows(parent, row, row);


           m_listJour.insert(row, msg);


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
    qDebug() << QTime::currentTime() << "ServerTableModelJour::updateListRecords() -->";
    int lastRecordMSG = -1;
    if(!m_listJour.isEmpty())
        lastRecordMSG = m_listJour.last().getId();

    qDebug() << QTime::currentTime() << "ServerTableModelJour::updateListRecords() -- lastRecordMSG " << lastRecordMSG;

    QList<JourEntity> newRecords(DataBaseManager::getMSGRecordAfter(lastRecordMSG));

    if(newRecords.isEmpty()) {
        qDebug() << QTime::currentTime() << "ServerTableModelJour::updateListRecords() <--";

        return;
    }
    qDebug() << QTime::currentTime() << "ServerTableModelJour::updateListRecords() -- newRecords.size() " << newRecords.size();

    this->beginInsertRows(QModelIndex(), m_listJour.size(), m_listJour.size() + newRecords.size() - 1);

    m_listJour.append(newRecords);

    this->endInsertRows();

    emitNeedScrollToBottom();
    qDebug() << QTime::currentTime() << "ServerTableModelJour::updateListRecords() <--";

}

void ServerTableModelJour::updateListRecords(JourEntity msg)
{
    //   newRecordMSG = idMSG;
       qDebug() << QTime::currentTime() << "ServerTableModelJour::updateListRecords(JourEntity msg) -->";
   //    QList<JourEntity> newRecords(DataBaseManager::getOneMSGRecord(idMSG));

       this->insertRows(msg,this->rowCount());

       emitNeedScrollToBottom();
}

void ServerTableModelJour::updateListRecords(const uint32_t idMSG)
{
    newRecordMSG = idMSG;
//    QList<JourEntity> newRecords(DataBaseManager::getOneMSGRecord(idMSG));

    this->insertRows(this->rowCount());

    emitNeedScrollToBottom();
}

void ServerTableModelJour::updateRecord(const uint32_t idMSG)
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
