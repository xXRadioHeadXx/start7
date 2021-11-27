#include "widget_devline.h"
#include "ui_widget_devline.h"

Widget_DEVLINE::Widget_DEVLINE(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
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
    ui->Num1->setValue(unit->getNum1());
    ui->OutType->setCurrentText(QString::number(unit->getOutType()));

    coord->get_options(unit);
}

void Widget_DEVLINE::get_default()
{
    ui->Num1->setValue(0);
    ui->OutType->setCurrentIndex(0);

    coord->get_options(nullptr);
}



void Widget_DEVLINE::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->value());
    unit->setOutType(ui->OutType->currentText().toInt());
    coord->set_options(unit);

}

void Widget_DEVLINE::update_name()
{

    QString Name("");
    Name.append("ТВ-Камера ");
    Name.append(QString::number(this->ui->Num1->value()));
    Name.append(" (Поток ");
    Name.append(this->ui->OutType->currentText());
    Name.append(")");

    emit updateName(Name);

}

void Widget_DEVLINE::setEnabled_option_menu(bool val)
{

}

bool Widget_DEVLINE::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}


    //Не может быть добавлен к юнитам следующего типа
    if((parent->getType()==TypeUnitNode::STRAZH_IP)||
       (parent->getType()==TypeUnitNode::ONVIF)||
       (parent->getType()==TypeUnitNode::DEVLINE)||
       (parent->getType()==TypeUnitNode::RASTRMTV)||
       (parent->getType()==TypeUnitNode::INFO_TABLO)||
       (parent->getType()==TypeUnitNode::SSOI_IU) ||
       (parent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }

//не должен повторяться у одного родителя
    return 
already_on_the_branch(unit);

    return false;
}

bool Widget_DEVLINE::equal(UnitNode *un, UnitNode *unit)
{

    if(un->getType()==unit->getType())
    if(un->getNum1()==unit->getNum1())
    if(un->getOutType()==unit->getOutType())
    return  true;
    return false;


}

QString Widget_DEVLINE::get_string(UnitNode *unit)
{
    QString string1;
    string1="";

    string1.append("ТВ-камера DevLine: ");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");
    string1.append("Поток: ");
    string1.append(QString::number(unit->getOutType()));

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
