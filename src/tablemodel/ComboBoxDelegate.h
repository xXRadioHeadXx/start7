#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <list>

class QModelIndex;
class QWidget;
class QVariant;
class QComboBox;

class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT

    QString field;
public:
    ComboBoxDelegate(QString field, QObject *parent = nullptr);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:

public slots:
};

#endif // COMBOBOXDELEGATE_H
