#include "widget_ssoi_iu.h"
#include "ui_widget_ssoi_iu.h"

Widget_SSOI_IU::Widget_SSOI_IU(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_SSOI_IU)
{
    ID=TypeUnitNode::SSOI_IU;
    ui->setupUi(this);


    for(int i=1;i<5;i++)                     {
        ui->Num1->addItem(QString::number(i));
    }

    for(int i=1;i<100;i++)                     {
    this->ui->Num2->addItem(QString::number(i));
    }

    foreach(QString str, m_SSOI_IU_Num3)    {
        this->ui->Num3->addItem(str);

    }


}

Widget_SSOI_IU::~Widget_SSOI_IU()
{
    delete ui;
}

void Widget_SSOI_IU::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
    ui->Num3->setCurrentText(m_SSOI_IU_Num3.value(unit->getNum3()));
}

void Widget_SSOI_IU::get_default()
{
    ui->Num1->setCurrentIndex(0);
    ui->Num2->setCurrentIndex(0);
    ui->Num3->setCurrentIndex(0);
}



void Widget_SSOI_IU::set_to(UnitNode *unit)
{
    unit->setNum1(this->ui->Num1->currentText().toInt());
    unit->setNum2(this->ui->Num2->currentText().toInt());
    unit->setNum3(m_SSOI_IU_Num3.key(this->ui->Num3->currentText()));

}

void Widget_SSOI_IU::update_name()
{
    QString Name("");
    Name.append("Канал");

    Name+=ui->Num1->currentText();
    Name+=" БЛ";
    Name+=ui->Num2->currentText();
    Name+=" ";
    Name+=ui->Num3->currentText();
    emit updateName(Name);

}

void Widget_SSOI_IU::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
    ui->Num3->setEnabled(val);
}

bool Widget_SSOI_IU::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer());
    if(!parent)
        return false;

        //может быть добавлен к любому датчику группе системе сморти ссои конфигуратор
        if((parent->getType()==TypeUnitNode::STRAZH_IP)||
           (parent->getType()==TypeUnitNode::ONVIF)||
           (parent->getType()==TypeUnitNode::DEVLINE)||
           (parent->getType()==TypeUnitNode::RASTRMTV)||
           (parent->getType()==TypeUnitNode::INFO_TABLO)||
           (parent->getType()==TypeUnitNode::SSOI_IU) ||
           (parent->getType()==TypeUnitNode::IU_BL_IP)||
           (parent->getType()==TypeUnitNode::SSOI_IP_IU) ||
           (parent->getType()==TypeUnitNode::ADAM)||
           (parent->getType()==TypeUnitNode::BOD_SOTA)||
           (parent->getType()==TypeUnitNode::BOD_T4K_M)||
           (parent->getType()==TypeUnitNode::Y4_SOTA)||
           (parent->getType()==TypeUnitNode::Y4_T4K_M))

        {

            return false;

        }


        if(already_on_the_branch(unit,modelTreeUN,current))
            return false;


    return true;

}

bool Widget_SSOI_IU::equal(UnitNode *un, UnitNode *unit)
{
    if(un->getType()==unit->getType())
    if(un->getNum1()==unit->getNum1())
    if(un->getNum2()==unit->getNum2())
    if(un->getNum3()==unit->getNum3())
        return true;

    return false;
}

QString Widget_SSOI_IU::get_string(UnitNode *unit)
{

    QString str;





    str.append(" : Канал");


    str.append(QString::number(unit->getNum1()));

    str.append(" : БЛ");
    str.append(QString::number(unit->getNum2()));

    str.append(" : ");
    str.append(m_SSOI_IU_Num3.value(unit->getNum3()));
   return str;
}

void Widget_SSOI_IU::on_Num1_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_SSOI_IU::on_Num2_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_SSOI_IU::on_Num3_currentIndexChanged(const QString &arg1)
{
    update_name();
}
