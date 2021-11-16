#include "widget_y4_sota.h"
#include "ui_widget_y4_sota.h"

Widget_Y4_SOTA::Widget_Y4_SOTA(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN) :
    UnitWidget(parent,comm,coord,modelTreeUN),
    ui(new Ui::Widget_Y4_SOTA)
{
    ID=TypeUnitNode::Y4_SOTA;
    ui->setupUi(this);
}

Widget_Y4_SOTA::~Widget_Y4_SOTA()
{
    delete ui;
}

void Widget_Y4_SOTA::get_from(UnitNode *unit)
{

}

void Widget_Y4_SOTA::get_default()
{

}



void Widget_Y4_SOTA::set_to(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_Y4_SOTA::update_name()
{
    emit updateName("Группа ");

}

void Widget_Y4_SOTA::setEnabled_option_menu(bool val)
{

}

QString Widget_Y4_SOTA::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}

void Widget_Y4_SOTA::on_Num2_currentIndexChanged(const QString &arg1)
{

}
