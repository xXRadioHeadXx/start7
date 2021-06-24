#ifndef UNIT_FINDER_DELEGATE_H
#define UNIT_FINDER_DELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include<QLineEdit>
class unit_finder_delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit unit_finder_delegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void	setEditorData(QWidget *editor, const QModelIndex &index) const;

    void	setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void	updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void	paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const ;


signals:

};

#endif // UNIT_FINDER_DELEGATE_H
