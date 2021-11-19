#include "widget_ssoi_sd.h"
#include "ui_widget_ssoi_sd.h"

Widget_SSOI_SD::Widget_SSOI_SD(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_SSOI_SD)
{
    ID=TypeUnitNode::SSOI_SD;
    ui->setupUi(this);
    comm->setVisible(true);

    for(int i=1;i<5;i++)                     {
        ui->Num1->addItem(QString::number(i));

    }

    for(int i=1;i<100;i++)                   {
        ui->Num2->addItem(QString::number(i));
    }

    foreach(QString str, m_SSOI_SD_Num3){
        this->ui->Num3->addItem(str);

    }

    for(int i=0;i<9;i++)                                           {
        this->ui->OutType->insertItem(i,m_SSOI_SD_OutType.value(i));
    }

}

Widget_SSOI_SD::~Widget_SSOI_SD()
{
    delete ui;
}

void Widget_SSOI_SD::get_from(UnitNode *unit)
{
    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
    ui->Num2->setCurrentText(m_SSOI_SD_Num3.value(unit->getNum3()));
    ui->OutType->setCurrentText(m_SSOI_SD_OutType.value(unit->getOutType()));
}

void Widget_SSOI_SD::get_default()
{
    ui->Num1->setCurrentIndex(0);
    ui->Num2->setCurrentIndex(0);
    ui->Num2->setCurrentIndex(0);
    ui->OutType->setCurrentIndex(0);
}



void Widget_SSOI_SD::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());
    unit->setNum2(ui->Num1->currentText().toInt());
    unit->setNum3(m_SSOI_SD_Num3.key(ui->Num3->currentText()));
    unit->setOutType(m_SSOI_SD_OutType.key(ui->OutType->currentText()));
}

void Widget_SSOI_SD::update_name()
{
    emit updateName("Группа ");

}

void Widget_SSOI_SD::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
    ui->Num3->setEnabled(val);

}

bool Widget_SSOI_SD::accepted(UnitNode *unit)
{

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer());
    //СД может быть добавлен только к группе или к системе
        if((parent->getType()!=TypeUnitNode::GROUP)&&(parent->getType()!=TypeUnitNode::SYSTEM))
        {
   //         QMessageBox::critical(0,"Ошибка","СД может быть добавлен только к группе или к системе");
            return false;

        }
   //Num2 от нуля до 99
    if(unit->getNum2()<0||unit->getNum2()>99)
        return false;



           return no_equal_unit(unit);




}



bool Widget_SSOI_SD::equal(UnitNode *un, UnitNode *unit)
{
    if(un->getType()==unit->getType())
    if(un->getNum1()==unit->getNum1())
    if(un->getNum2()==unit->getNum2())
    if(un->getNum3()==unit->getNum3())
        return true;
        return false;
}

QString Widget_SSOI_SD::get_string(UnitNode *unit)
{
    QString string1;
    QString UdpAdress=unit->getUdpAdress();

    string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  БЛ-IP</b> ");

    //Канал
    string1.append(" Кан:");

    if(unit->getUdpUse()==0)
    {
        string1.append(QString::number(unit->getNum1()));


            if(unit->getUdpAdress()!="")
        {
            string1.append(" (");
            string1.append(unit->getUdpAdress());
            string1.append(")");
        }
    }
    if(unit->getUdpUse()==1)
    {
        string1.append(unit->getUdpAdress());
        string1.append("::");
        string1.append(QString::number(unit->getUdpPort()));


        string1.append("\n");
        string1.append("Таймаут: ");
        string1.append(QString::number(unit->getUdpTimeout()));
        string1.append("\n");
    }
    //БЛ

    string1.append(" БЛ:");
    string1.append(QString::number(unit->getNum2()));
    string1.append(" ");

    //СД


    string1.append(" СД:");
    int val=unit->getNum3();
            if(val==9)
    string1.append("Вскрытие ");
            else
    string1.append(QString::number(unit->getNum3()));

    if(unit->getBazalt()==1)
        {
            string1.append(" +");
            string1.append(" ИУ:");
            string1.append(QString::number(unit->getNum3()));
        }
    else
    if(unit->getConnectBlock()==1)
        {
            string1.append(" +");
            string1.append(" ИУ:");
            string1.append(QString::number(unit->getNum3()-3));
        }

    string1.append("  ");





    if(unit->getBazalt())
    {

        string1.append(m_SSOI_SD_OutType.value(8));
    }
    else if(unit->getConnectBlock())
    {

        string1.append(m_SSOI_SD_OutType.value(9));
    }
    else
    {

        int val = unit->getOutType();
        if(val)
        string1.append(m_SSOI_SD_OutType.value(unit->getOutType()));
    }




   return string1;
}

void Widget_SSOI_SD::on_Num1_currentIndexChanged(const QString &arg1)
{
    QString Name("");
    Name.append("Канал");
    Name.append(this->ui->Num1->currentText());
    Name.append("-БЛ");
    Name.append(this->ui->Num2->currentText());


    Name.append("-СД");
    if(this->ui->Num3->currentText()=="вскрытие")
    Name.append("-Вскрытие");
    else
    Name.append(this->ui->Num3->currentText());


    if(this->ui->OutType->currentIndex()>0)
    {
    Name.append(" тип:");
    Name.append(this->ui->OutType->currentText());
    }

    emit updateName(Name);
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
