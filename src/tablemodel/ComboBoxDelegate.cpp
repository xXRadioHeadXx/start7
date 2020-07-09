#include "ComboBoxDelegate.h"

#include <DataBaseManager.h>
#include <JourEntity.h>
#include <QComboBox>

ComboBoxDelegate::ComboBoxDelegate(QString field, QObject *parent) : QItemDelegate(parent), field(field) { }

QWidget* ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    QComboBox *comboBox = new QComboBox(parent);
    JourEntity *n = static_cast<JourEntity*>(index.internalPointer());
    QList<QString> items;

    if("reason" == field)
        items = DataBaseManager::getReasonGroup();
    else if("measures" == field)
        items = DataBaseManager::getMeasuresGroup();

    int currentIndex = 0;

    if("reason" == field && !n->getReason().isEmpty())
        currentIndex = items.indexOf(n->getReason());
    else if("measures" == field && !n->getMeasures().isEmpty())
        currentIndex = items.indexOf(n->getMeasures());

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
