#include "widget_rlm_krl.h"
#include "ui_widget_rlm_krl.h"

Widget_RLM_KRL::Widget_RLM_KRL(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_RLM_KRL)
{
    ID=TypeUnitNode::RLM_KRL;
    ui->setupUi(this);

    comm_is_needed=true;
    coord_mode=coordinateWigget_mode::for_all;

    for(int i=1;i<100;i++) {

    ui->Num1->addItem(QString::number(i));
    }

    for(int i=0;i<m_RLM_KRL_type.size();i++)    {
    ui->AdamOff->addItem(m_RLM_KRL_type.value(i));
    }


}

Widget_RLM_KRL::~Widget_RLM_KRL()
{
    delete ui;
}

void Widget_RLM_KRL::get_from(UnitNode *unit)
{
ui->Num1->setCurrentText(QString::number(unit->getNum1()));
ui->AdamOff->setCurrentText(m_RLM_KRL_type.value(unit->getAdamOff()));
}

void Widget_RLM_KRL::get_default()
{

}



void Widget_RLM_KRL::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());
    unit->setAdamOff(m_RLM_KRL_type.key(this->ui->AdamOff->currentText()));

}

void Widget_RLM_KRL::update_name()
{
    QString Name;
    Name.clear();
    Name.append(ui->AdamOff->currentText());
    Name.append("-");
    if(ui->Num1->currentText().toInt()<10)
    Name.append("0");
    Name.append(this->ui->Num1->currentText());
    emit updateName(Name);

}

void Widget_RLM_KRL::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
    ui->AdamOff->setEnabled(val);
}

QString Widget_RLM_KRL::get_string(UnitNode *unit)
{
    QString string1;

    string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));//  ");
    if(0==unit->getAdamOff())
    string1.append(str_RIF_RLM);

    if(1==unit->getAdamOff())
    string1.append(str_RIF_RLM_24);

    if(2==unit->getAdamOff())
    string1.append(str_RIF_RLM_B);

    if(3==unit->getAdamOff())
    string1.append(str_RIF_KRL);

    if(4==unit->getAdamOff())
    string1.append(str_Razriv);

    if(5==unit->getAdamOff())
    string1.append(str_trassa1l);

    string1.append("</b>");
    string1.append(" : ");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");
   return string1;
}

void Widget_RLM_KRL::on_Num1_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_RLM_KRL::on_AdamOff_currentIndexChanged(const QString &arg1)
{
    update_name();
}
