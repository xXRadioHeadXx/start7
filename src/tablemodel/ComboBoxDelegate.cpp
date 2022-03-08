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
    auto jour = ServerTableModelJour::getListJour().value(index.row(), JourEntity());
    QList<QString> items;

    if("reason" == field)
        items = ServerSettingUtils::getReasonTemplate();
    else if("measures" == field)
        items = ServerSettingUtils::getMeasureTemplate();

    int currentIndex = 0;

    if("reason" == field && !jour.getReason().isEmpty())
        currentIndex = items.indexOf(jour.getReason());
    else if("measures" == field && !jour.getMeasures().isEmpty())
        currentIndex = items.indexOf(jour.getMeasures());

    comboBox->addItems(items);
    comboBox->setCurrentIndex(currentIndex);
    comboBox->setEditable(true);
    return comboBox;
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    const auto& comboBox = dynamic_cast<QComboBox*>(editor);
    if(nullptr != comboBox)
        model->setData(index, comboBox->currentText());
}
