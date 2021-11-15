#include "widget_onvif.h"
#include "ui_widget_onvif.h"

Widget_ONVIF::Widget_ONVIF(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN) :
    UnitWidget(parent,comm,coord,modelTreeUN),
    ui(new Ui::Widget_ONVIF)
{
    ID=TypeUnitNode::ONVIF;
    ui->setupUi(this);
}

Widget_ONVIF::~Widget_ONVIF()
{
    delete ui;
}

void Widget_ONVIF::get_from(UnitNode *unit)
{

}

void Widget_ONVIF::get_default()
{

}



void Widget_ONVIF::set_to(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_ONVIF::update_name()
{
    emit updateName("Группа ");

}

void Widget_ONVIF::setEnabled(bool val)
{

}

QString Widget_ONVIF::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}

void Widget_ONVIF::on_ONVIF_IPaddr_combobox_currentTextChanged(const QString &arg1)
{
    update_name();
}
