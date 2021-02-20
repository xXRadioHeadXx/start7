#ifndef DELEGATE_H
#define DELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include<QLineEdit>
#include <my_lineedit.h>

class Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit Delegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void	setEditorData(QWidget *editor, const QModelIndex &index) const;

    void	setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void	updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void	paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const ;



signals:

};

#endif // DELEGATE_H
