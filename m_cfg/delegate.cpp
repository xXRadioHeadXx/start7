#include "delegate.h"
#include <QDebug>


Delegate::Delegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<"[createEditor]";
    QLineEdit* editor = new QLineEdit(parent);
    return editor;



}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
        qDebug()<<"[setEditorData]";
    QLineEdit* linedit =static_cast<QLineEdit*>(editor);

    linedit->setText(index.model()->data(index,Qt::DisplayRole).toString());



}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug()<<"[setModelData]";
    QLineEdit* linedit =static_cast<QLineEdit*>(editor);
    model->setData(index, linedit->text());
}

void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<"[updateEditorGeometry]";
    editor->setGeometry(option.rect);
}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<"[paint]";

    QStyledItemDelegate::paint(painter,option,index);
}


