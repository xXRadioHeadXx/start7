#include "unit_finder_delegate.h"
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QDebug>
unit_finder_delegate::unit_finder_delegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *unit_finder_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 1:
    {
        qDebug()<<"0001";
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
        qDebug()<<"0002";
     QDoubleSpinBox* editor = new QDoubleSpinBox(parent);


     editor->setMinimum(50);
     editor->setSingleStep(5);
     editor->setMaximum(5000);
     editor->setContextMenuPolicy(Qt::NoContextMenu);
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
    qDebug()<<"0003";
       QComboBox* combobox =static_cast<QComboBox*>(editor);

       combobox->setCurrentText(QString::number(index.model()->data(index,Qt::DisplayRole).toInt()));
    }
    break;


    case 2:
    {
    qDebug()<<"0004";
    QDoubleSpinBox* DoubleSpinBox =static_cast<QDoubleSpinBox*>(editor);

    DoubleSpinBox->setValue(index.model()->data(index,Qt::DisplayRole).toInt());
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
    qDebug()<<"0005";
       QComboBox* combobox =static_cast<QComboBox*>(editor);

       model->setData(index,combobox->currentText().toInt());
    }
    break;


    case 2:
    {
    qDebug()<<"0006";
    QDoubleSpinBox* DoubleSpinBox =static_cast<QDoubleSpinBox*>(editor);

    model->setData(index,DoubleSpinBox->value());
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
