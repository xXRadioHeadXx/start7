#include "widget_devline.h"
#include "ui_widget_devline.h"

Widget_DEVLINE::Widget_DEVLINE(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN) :
    UnitWidget(parent,comm,coord,modelTreeUN),
    ui(new Ui::Widget_DEVLINE)
{
    ID=TypeUnitNode::DEVLINE;
    ui->setupUi(this);
    coord_mode=coordinateWigget_mode::devline;
}

Widget_DEVLINE::~Widget_DEVLINE()
{
    delete ui;
}

void Widget_DEVLINE::get_from(UnitNode *unit)
{

}

void Widget_DEVLINE::get_default()
{

}



void Widget_DEVLINE::set_to(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_DEVLINE::update_name()
{
    emit updateName("Группа ");

}

void Widget_DEVLINE::setEnabled(bool val)
{

}

QString Widget_DEVLINE::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}

void Widget_DEVLINE::on_Num1_valueChanged(const QString &arg1)
{
    update_name();
}

void Widget_DEVLINE::on_OutType_currentIndexChanged(const QString &arg1)
{
    update_name();
}
