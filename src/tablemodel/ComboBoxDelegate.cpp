#include "ComboBoxDelegate.h"

#include <DataBaseManager.h>
#include <JourEntity.h>
#include <QComboBox>
#include<TableModelMSG.h>

ComboBoxDelegate::ComboBoxDelegate(QString field, QObject *parent) : QItemDelegate(parent), field(field) { }

QWidget* ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    QComboBox *comboBox = new QComboBox(parent);
    auto jour = TableModelMSG::getListMSG().value(index.row(), JourEntity());
    QList<QString> items;

    if("reason" == field)
        items = DataBaseManager::getReasonGroup();
    else if("measures" == field)
        items = DataBaseManager::getMeasuresGroup();

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
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentText());
}
