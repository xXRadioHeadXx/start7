#include "widget_group.h"
#include "ui_widget_group.h"

Widget_GROUP::Widget_GROUP(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_GROUP)
{
    ID=TypeUnitNode::GROUP;
    ui->setupUi(this);
    comm->setVisible(false);
}

Widget_GROUP::~Widget_GROUP()
{
    delete ui;
}

void Widget_GROUP::get_from(UnitNode *unit)
{

}

void Widget_GROUP::get_default()
{

}


void Widget_GROUP::set_to(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_GROUP::update_name()
{
    emit updateName("Группа ");

}

void Widget_GROUP::setEnabled_option_menu(bool val)
{

}

QString Widget_GROUP::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}
