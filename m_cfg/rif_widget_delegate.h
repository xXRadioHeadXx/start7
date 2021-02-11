#ifndef RIF_WIDGET_DELEGATE_H
#define RIF_WIDGET_DELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include<QLineEdit>


class rif_widget_delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit rif_widget_delegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void	setEditorData(QWidget *editor, const QModelIndex &index) const;

    void	setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void	updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void	paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const ;


signals:

};

#endif // RIF_WIDGET_DELEGATE_H
