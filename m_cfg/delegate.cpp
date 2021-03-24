#include "delegate.h"
#include <QDebug>
#include <QRect>


Delegate::Delegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //qDebug()<<"[createEditor]";
    My_lineEdit* editor = new My_lineEdit(parent);
    return editor;



}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
        //qDebug()<<"[setEditorData]";
    My_lineEdit* linedit =static_cast<My_lineEdit*>(editor);

    linedit->setText(index.model()->data(index,Qt::DisplayRole).toString());



}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //qDebug()<<"[setModelData]";
    My_lineEdit* linedit =static_cast<My_lineEdit*>(editor);
    model->setData(index, linedit->text());
}

void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //qDebug()<<"[updateEditorGeometry]";

   editor->setGeometry(option.rect.x()+20,
                       option.rect.y()-1,
                       option.rect.width(),
                       option.rect.height()+1);
}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize sz = QStyledItemDelegate::sizeHint(option, index);
    sz.setHeight(sz.height() - 6);//накидываем 10 пикселей по 5 сверху и снизу
    return sz;
}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
 //   //qDebug()<<"[paint]";

    QStyledItemDelegate::paint(painter,option,index);
}


