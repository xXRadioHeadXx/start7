#include "unit_finder_delegate.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QApplication>
#include "UnitNode.h"
#include <my_lineedit.h>

#include <my_config.h>




QList<QString> l_Unittype_rif={
    str_GROUP,
    str_SD_BL_IP,
    str_IU_BL_IP,
    str_KL,
    str_TG,
    str_RLM_KRL,
    str_RLM_C,
    str_STRAZH_IP,
    str_NET_DEV,
    str_ONVIF,
    str_BOD_T4K_M,
    str_Y4_T4K_M,
    str_DD_T4K_M,
    str_BOD_SOTA,
    str_Y4_SOTA,
    str_DD_SOTA,


    str_SSOI_SD,
    str_SSOI_IU,
    str_ADAM,
    str_TOROS,
    str_DEVLINE,
    str_RASTRMTV,
    str_INFO_TABLO
};



unit_finder_delegate::unit_finder_delegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *unit_finder_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column())
    {
    case 1:
    {
      QComboBox* editor;
    if(index.model()->data(index.model()->index(index.row(),0,QModelIndex()),Qt::DisplayRole).toString()=="Type")
    {
    QComboBox* editor = new QComboBox(parent);
    foreach(QString str, l_Unittype_rif)
    {
    editor->addItem(str);
    }
         return editor;
    }

        else
    {
  My_lineEdit* editor = new My_lineEdit(parent);
        return editor;
    }



    break;
    }
    case 2:
    {
    QComboBox* editor = new QComboBox(parent);
    editor->addItem(" ");
    editor->addItem("да");
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
        if(index.model()->data(index.model()->index(index.row(),0,QModelIndex()),Qt::DisplayRole).toString()=="Type")
        {
        QComboBox* combobox = static_cast < QComboBox*>(editor);
        combobox->setCurrentText(m_TypeUnitNode_d.value(index.model()->data(index,Qt::DisplayRole).toInt()));

        }

            else
        {
        My_lineEdit* lineedit =static_cast < My_lineEdit*>(editor);
        lineedit->setText(index.model()->data(index,Qt::DisplayRole).toString());
        }
    }
    break;

    case 2:
    {
         QComboBox* combobox = static_cast < QComboBox*>(editor);
         if(index.model()->data(index,Qt::DisplayRole).toBool())
         combobox->setCurrentText("да");
         else
         combobox->setCurrentText("");

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
        if(index.model()->data(index.model()->index(index.row(),0,QModelIndex()),Qt::DisplayRole).toString()=="Type")
        {
        QComboBox* combobox = static_cast < QComboBox*>(editor);
        model->setData(index,m_TypeUnitNode_d.key(combobox->currentText()));

        }

            else
        {
       My_lineEdit* lineedit =static_cast < My_lineEdit*>(editor);
       model->setData(index,lineedit->text());
        }
    }
    break;

    case 2:
    {

       QComboBox* combobox = static_cast < QComboBox*>(editor);
       if(combobox->currentText()=="да")
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


