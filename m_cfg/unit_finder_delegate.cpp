#include "unit_finder_delegate.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QApplication>
#include "UnitNode.h"


QString str_GROUP=          " ГРУППА";
QString str_SD_BL_IP=       " БЛ-IP СД";
QString str_IU_BL_IP=       " БЛ-IP ИУ";
QString str_KL =            " КЛ1 (концентратор) СД";
QString str_TG =            " Точка/Гарда";
QString str_RLM_KRL =       " РИФ-РЛМ/КРЛ/Трасса";
QString str_RLM_C =         " РИФ-РЛМ-С";
QString str_STRAZH_IP =     " ТВ-камера+тепловиз.Страж";
QString str_NET_DEV =       " Сетевое устройство";
QString str_ONVIF =         " ТВ-камера ONVIF";
QString str_BOD_T4K_M =     " Точка-М/Гарда БОД";
QString str_Y4_T4K_M =      " Точка-М/Гарда Участок";
QString str_DD_T4K_M =      " Точка-М/Гарда ДД";
QString str_BOD_SOTA =      " Сота/Сота-М БОД";
QString str_Y4_SOTA =       " Сота/Сота-М Участок";
QString str_DD_SOTA =       " Сота/Сота-М ДД";

QString str_RIF_RLM=        " РИФ-РЛМ";
QString str_RIF_RLM_24=     " РИФ-РЛМ24";
QString str_RIF_RLM_B=      " РИФ-РЛМ(Б)";
QString str_RIF_KRL=        " РИФ-КРЛ";
QString str_Razriv=         " Разрыв";
QString str_trassa1l=       " Трасса-1л";

QString str_SSOI_SD =       " ССОИ СД";
QString str_SSOI_IU =       " ССОИ ИУ";
QString str_ADAM =          " ADAM";
QString str_TOROS =         " Торос";
QString str_DEVLINE =       " ТВ-камера DevLine";
QString str_RASTRMTV =      " ТВ-камера РАСТР-М-ТВ";
QString str_INFO_TABLO =    " информационное табло";

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

QMap <int,QString> m_TypeUnitNode_d{
{TypeUnitNode::GROUP, str_GROUP},
{TypeUnitNode::KL ,str_KL },
{TypeUnitNode::SD_BL_IP ,str_SD_BL_IP },
{TypeUnitNode::IU_BL_IP ,str_IU_BL_IP },
{TypeUnitNode::TG ,str_TG },
{TypeUnitNode::RLM_KRL ,str_RLM_KRL },
{TypeUnitNode::RLM_C ,str_RLM_C },
{TypeUnitNode::STRAZH_IP ,str_STRAZH_IP },
{TypeUnitNode::ONVIF ,str_ONVIF },
{TypeUnitNode::BOD_T4K_M ,str_BOD_T4K_M },
{TypeUnitNode::Y4_T4K_M ,str_Y4_T4K_M },
{TypeUnitNode::DD_T4K_M ,str_DD_T4K_M },
{TypeUnitNode::BOD_SOTA ,str_BOD_SOTA },
{TypeUnitNode::Y4_SOTA ,str_Y4_SOTA },
{TypeUnitNode::DD_SOTA ,str_DD_SOTA },
{TypeUnitNode::NET_DEV ,str_NET_DEV },

{TypeUnitNode::SSOI_SD ,str_SSOI_SD },
{TypeUnitNode::SSOI_IU ,str_SSOI_IU },
{TypeUnitNode::ADAM ,str_ADAM },
{TypeUnitNode::TOROS ,str_TOROS },
{TypeUnitNode::DEVLINE ,str_DEVLINE },
{TypeUnitNode::RASTRMTV ,str_RASTRMTV },
{TypeUnitNode::INFO_TABLO ,str_INFO_TABLO },

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
  QLineEdit* editor = new QLineEdit(parent);
        return editor;
    }



    break;
    }
    case 2:
    {
    QComboBox* editor = new QComboBox(parent);
    editor->addItem(" ");
    editor->addItem("искать");
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
        QLineEdit* lineedit =static_cast < QLineEdit*>(editor);
        lineedit->setText(index.model()->data(index,Qt::DisplayRole).toString());
        }
    }
    break;

    case 2:
    {
         QComboBox* combobox = static_cast < QComboBox*>(editor);
         if(index.model()->data(index,Qt::DisplayRole).toBool())
         combobox->setCurrentText("искать");
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
        if(index.model()->data(index.model()->index(index.row(),0,QModelIndex()),Qt::DisplayRole).toString()=="Type")
        {
        QComboBox* combobox = static_cast < QComboBox*>(editor);
        model->setData(index,m_TypeUnitNode_d.key(combobox->currentText()));

        }

            else
        {
       QLineEdit* lineedit =static_cast < QLineEdit*>(editor);
       model->setData(index,lineedit->text());
        }
    }
    break;

    case 2:
    {

       QComboBox* combobox = static_cast < QComboBox*>(editor);
       if(combobox->currentText()=="искать")
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
