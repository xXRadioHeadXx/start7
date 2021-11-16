#include "widget_bod_sota.h"
#include "ui_widget_bod_sota.h"

Widget_BOD_SOTA::Widget_BOD_SOTA(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current):
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_BOD_SOTA)
{
    ID=TypeUnitNode::BOD_SOTA;
    ui->setupUi(this);

    comm_is_needed=true;
    coord_mode=coordinateWigget_mode::for_all;

    for(int i=1;i<100;i++){
    ui->Num1->addItem(QString::number(i));
    }

}

Widget_BOD_SOTA::~Widget_BOD_SOTA()
{
    delete ui;
}

void Widget_BOD_SOTA::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
}

void Widget_BOD_SOTA::get_default()
{
    ui->Num1->setCurrentIndex(0);
}



void Widget_BOD_SOTA::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());




}

void Widget_BOD_SOTA::update_name()
{
    QString Name;
    Name.append("Сота: БОД");
    if(ui->Num1->currentText().toInt()<10)
    Name.append("0");
    Name.append(ui->Num1->currentText());

    emit updateName(Name);

}

void Widget_BOD_SOTA::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
}

bool Widget_BOD_SOTA::timeout_brother(UnitNode *un)
{
    if(un->getType()==TypeUnitNode::Y4_SOTA)
        return true;
    if(un->getType()==TypeUnitNode::DD_SOTA)
        return true;


    return false;
}

QString Widget_BOD_SOTA::get_string(UnitNode *unit)
{
    QString string1;


        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Сота/Сота-М</b> ");

    string1.append("Кан:");

    if(unit->getUdpUse()==0)
    {
        string1.append(QString::number(unit->getNum3()));


    }
    if(unit->getUdpUse()==1)
    {
        string1.append(unit->getUdpAdress());
        string1.append("::");
        string1.append(QString::number(unit->getUdpPort()));
        string1.append(" ");
        string1.append("\n");
        string1.append("Таймаут: ");
        string1.append(QString::number(unit->getUdpTimeout()));
        string1.append("\n");
    }



    string1.append(" БОД:");
    string1.append(QString::number(unit->getNum1()));

    if(unit->getUdpUse()==0)
    {


        if(unit->getUdpAdress()!="")
        {

            string1.append(" (");
            string1.append(unit->getUdpAdress());
            string1.append(")");

        }
    }
   return string1;
}

void Widget_BOD_SOTA::on_Num1_currentTextChanged(const QString &arg1)
{
    update_name();
}


