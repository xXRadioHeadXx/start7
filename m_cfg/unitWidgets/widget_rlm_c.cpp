#include "widget_rlm_c.h"
#include "ui_widget_rlm_c.h"

Widget_RLM_C::Widget_RLM_C(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_RLM_C)
{
    ID=TypeUnitNode::RLM_C;
    ui->setupUi(this);

    comm_is_needed=true;
    coord_mode=coordinateWigget_mode::for_all;

    for(int i=1;i<100;i++)        {
        ui->Num1->addItem(QString::number(i));
    }

}

Widget_RLM_C::~Widget_RLM_C()
{
    delete ui;
}

void Widget_RLM_C::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));

}

void Widget_RLM_C::get_default()
{
    ui->Num1->setCurrentIndex(0);
}



void Widget_RLM_C::set_to(UnitNode *unit)
{
unit->setNum1(ui->Num1->currentText().toInt());
}

void Widget_RLM_C::update_name()
{
    QString Name;
    Name.append("РИФ-РЛМ-С-");
    if(ui->Num1->currentText().toInt()<10)
    Name.append("0");
    Name.append(ui->Num1->currentText());
    emit updateName(Name);

}

void Widget_RLM_C::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
}

QString Widget_RLM_C::get_string(UnitNode *unit)
{
    QString string1;





        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  РИФ-РЛМ-С</b>");
        string1.append(":");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");




    if(unit->getUdpUse()==0)
    {
        string1.append("Кан:");

        string1.append(QString::number(unit->getNum3()));
        string1.append(" ");

 //  string1.append(QString::number(unit->getNum3()));
   if(unit->getUdpAdress()!="")
   {
       string1.append(" ");
       string1.append("(");
       string1.append(unit->getUdpAdress());
       string1.append(")");
   }


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
   return string1;
}

void Widget_RLM_C::on_Num1_currentIndexChanged(const QString &arg1)
{
    update_name();
}
