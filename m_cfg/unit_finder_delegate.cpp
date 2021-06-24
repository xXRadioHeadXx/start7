#include "unit_finder_delegate.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QApplication>
unit_finder_delegate::unit_finder_delegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *unit_finder_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 1:
    {
  QLineEdit* editor = new QLineEdit(parent);


     return editor;

    break;
    }
    case 2:
    {
    QComboBox* editor = new QComboBox(parent);
    editor->addItem(" ");
    editor->addItem("используется");
    return editor;
    }
    break;

    }
}

void unit_finder_delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 1:
    {
        QLineEdit* lineedit =static_cast < QLineEdit*>(editor);
        lineedit->setText(index.model()->data(index,Qt::DisplayRole).toString());
    }
    break;

    case 2:
    {
         QComboBox* combobox = static_cast < QComboBox*>(editor);
         if(index.model()->data(index,Qt::DisplayRole).toBool())
         combobox->setCurrentText("используется");
         else
         combobox->setCurrentText(" ");

    }
    break;

    }
}

void unit_finder_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 1:
    {

       QLineEdit* lineedit =static_cast < QLineEdit*>(editor);
       model->setData(index,lineedit->text());
    }
    break;

    case 2:
    {

       QComboBox* combobox = static_cast < QComboBox*>(editor);
       if(combobox->currentText()=="используется")
       model->setData(index,true);
       else
       model->setData(index,false);
    }
    break;

    }
}

void unit_finder_delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);

}

void unit_finder_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

QStyledItemDelegate::paint(painter,option,index);


}
