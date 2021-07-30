#include "ComboBoxDelegate.h"

#include "JourEntity.h"
#include <QComboBox>
#include "ServerSettingUtils.h"
#include "ServerTableModelJour.h"

ComboBoxDelegate::ComboBoxDelegate(QString field, QObject *parent) : QItemDelegate(parent), field(field) { }

QWidget* ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    QComboBox *comboBox = new QComboBox(parent);
    auto it = std::next(ServerTableModelJour::getListJour().begin(), index.row());
    auto jour = *it;

    QStringList items = (
            (("reason" == field) ?
                ServerSettingUtils::getReasonTemplate() :
                (("measures" == field) ?
                    ServerSettingUtils::getMeasureTemplate() :
                    QStringList() )));

    QString val;
    if("reason" == field && !jour.getReason().isEmpty())
        val = jour.getReason();
    else if("measures" == field && !jour.getMeasures().isEmpty())
        val = jour.getMeasures();

    int currentIndex = 0;
    for(auto itr = items.begin(); itr != items.end(); itr++, currentIndex++) {
        if(*itr == val)
            break;
    }

    comboBox->addItems(items);
    comboBox->setCurrentIndex(currentIndex);
    comboBox->setEditable(true);
    return comboBox;
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentText());
}
