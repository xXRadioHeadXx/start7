#include "rif_widget_delegate.h"
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QDebug>

rif_widget_delegate::rif_widget_delegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *rif_widget_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 1:
    {
    QComboBox* editor = new QComboBox(parent);

    editor->addItem("4800");
    editor->addItem("9600");
    editor->addItem("19200");
    editor->addItem("38400");
    editor->addItem("57600");
    editor->addItem("115200");
    editor->addItem("250000");

    return editor;
    }
    break;


    case 2:
    {

     QDoubleSpinBox* editor = new QDoubleSpinBox(parent);


     editor->setMinimum(50);
     editor->setSingleStep(5);
     editor->setMaximum(5000);
     return editor;

    }
    break;

    }
}

void rif_widget_delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 1:
    {
       QComboBox* combobox =static_cast<QComboBox*>(editor);

       combobox->setCurrentText(QString::number(index.model()->data(index,Qt::DisplayRole).toInt()));
    }
    break;


    case 2:
    {
    QDoubleSpinBox* DoubleSpinBox =static_cast<QDoubleSpinBox*>(editor);

    DoubleSpinBox->setValue(index.model()->data(index,Qt::DisplayRole).toInt());
    }
    break;

    }
}

void rif_widget_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 1:
    {
       QComboBox* combobox =static_cast<QComboBox*>(editor);

       model->setData(index,combobox->currentText().toInt());
    }
    break;


    case 2:
    {
    QDoubleSpinBox* DoubleSpinBox =static_cast<QDoubleSpinBox*>(editor);

    model->setData(index,DoubleSpinBox->value());
    }
    break;

    }


}

void rif_widget_delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void rif_widget_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


QStyledItemDelegate::paint(painter,option,index);

}
