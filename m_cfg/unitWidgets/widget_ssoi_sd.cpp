#include "widget_ssoi_sd.h"
#include "ui_widget_ssoi_sd.h"

Widget_SSOI_SD::Widget_SSOI_SD(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN) :
    UnitWidget(parent,comm,coord,modelTreeUN),
    ui(new Ui::Widget_SSOI_SD)
{
    ID=TypeUnitNode::SSOI_SD;
    ui->setupUi(this);
    comm->setVisible(true);
}

Widget_SSOI_SD::~Widget_SSOI_SD()
{
    delete ui;
}

void Widget_SSOI_SD::get_from(UnitNode *unit)
{

}

void Widget_SSOI_SD::get_default()
{

}



void Widget_SSOI_SD::set_to(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);
}

void Widget_SSOI_SD::update_name()
{
    emit updateName("Группа ");

}

void Widget_SSOI_SD::setEnabled_option_menu(bool val)
{

}

QString Widget_SSOI_SD::get_string(UnitNode *unit)
{
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
   return string1;
}

void Widget_SSOI_SD::on_Num1_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_SSOI_SD::on_Num2_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_SSOI_SD::on_Num3_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_SSOI_SD::on_OutType_currentIndexChanged(const QString &arg1)
{
    update_name();
}
