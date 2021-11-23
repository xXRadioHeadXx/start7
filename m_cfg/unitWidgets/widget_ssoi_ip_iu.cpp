#include "widget_ssoi_ip_iu.h"
#include "ui_widget_ssoi_ip_iu.h"

Widget_SSOI_IP_IU::Widget_SSOI_IP_IU(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_SSOI_IP_IU)
{
    ID=TypeUnitNode::SSOI_IP_IU;
    ui->setupUi(this);
    comm_is_needed=true;
}

Widget_SSOI_IP_IU::~Widget_SSOI_IP_IU()
{
    delete ui;
}

void Widget_SSOI_IP_IU::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
}

void Widget_SSOI_IP_IU::get_default()
{
    ui->Num1->setCurrentIndex(0);
    ui->Num2->setCurrentIndex(0);
}

void Widget_SSOI_IP_IU::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());
    unit->setNum2(ui->Num2->currentText().toInt());
}

void Widget_SSOI_IP_IU::update_name()
{

    QString name;

    name.append("ССОИ IP ");


    QString ip_str=comm->get_udpAdress();

    QStringList myStringList = ip_str.split(".");

    if(myStringList.count()==4)
    {
        ip_str=myStringList[3];
        if(ip_str.toInt()<100)
            ip_str="0"+ip_str;
        if(ip_str.toInt()<10)
            ip_str="0"+ip_str;
    }
    else
        ip_str="-IP";

    //разделить на подстроки через символ точку
    //четвертая подстрока. если менше сотни - ноль; меньше десяти - два нуля

    name.append(ip_str);


    name.append(" ИУ");
    name.append("-");

    //if(this->ui->SD_BL_IP_num_combobox->currentText().toInt()<10)
    //name.append("0");

    name.append(this->ui->Num2->currentText());


  //  updater->updateName(name);
    emit updateName(name);
}

void Widget_SSOI_IP_IU::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
    comm->setEnabled(val);
}

bool Widget_SSOI_IP_IU::accepted(UnitNode *unit)
{
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}

    //может быть добавлен к любому датчику группе системе сморти ссои конфигуратор
    if((parent->getType()==TypeUnitNode::STRAZH_IP)||
       (parent->getType()==TypeUnitNode::ONVIF)||
       (parent->getType()==TypeUnitNode::DEVLINE)||
       (parent->getType()==TypeUnitNode::RASTRMTV)||
       (parent->getType()==TypeUnitNode::INFO_TABLO)||
       (parent->getType()==TypeUnitNode::SSOI_IU) ||
       (parent->getType()==TypeUnitNode::IU_BL_IP)||
        (parent->getType()==TypeUnitNode::ADAM))
    {

        return false;

    }



        //Num2 от нуля до четырех
         if(unit->getNum2()<0||unit->getNum2()>4)

             return false;
//Может повторяться в дереве. Не должен повторяться у одного предка.
         return UnitWidget::no_equal_unit_from_one_parent(unit);

}

bool Widget_SSOI_IP_IU::equal(UnitNode *origin, UnitNode *current)
{

if(origin->getType()==current->getType())
if(origin->getNum1()==current->getNum1())
if(origin->getNum2()==current->getNum2())
return true;


return false;
}

QString Widget_SSOI_IP_IU::get_string(UnitNode *unit)
{

    QString str;

    str.append("<b>");str.append(m_TypeUnitNode_d.value(unit->getType()));str.append("</b> ");//  БЛ-IP</b> ");
            str.append(": Кан:");


    if(unit->getUdpUse()==0)
    {
    str.append(QString::number(unit->getNum3()));
    str.append(" ССОИ IP ИУ:");
    str.append(QString::number(unit->getNum2()));

    if(unit->getUdpAdress()!="")
    {
    str.append(" ");
    str.append("(");
    str.append(unit->getUdpAdress());
    str.append(")");
    }
    }
    if(unit->getUdpUse()==1)
    {
    str.append(unit->getUdpAdress());
    str.append("::");
    str.append(QString::number(unit->getUdpPort()));
    str.append(" ");
    str.append("ИУ:");
    str.append(QString::number(unit->getNum2()));
    str.append("\n");
    str.append("Таймаут: ");
    str.append(QString::number(unit->getUdpTimeout()));
    str.append("\n");
    }

    return str;
}
