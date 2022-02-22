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
   //     this->ui->OutType->insertItem(i,m_SSOI_SD_OutType.value(i));
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
    ui->Num3->setCurrentText(m_SSOI_SD_Num3.value(unit->getNum3()));
    ui->OutType->setCurrentText(m_SSOI_SD_OutType.value(unit->getOutType()));
}

void Widget_SSOI_SD::get_default()
{
    ui->Num1->setCurrentIndex(0);
    ui->Num2->setCurrentIndex(0);
    ui->Num3->setCurrentIndex(0);
    ui->OutType->setCurrentIndex(0);
}



void Widget_SSOI_SD::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());
    unit->setNum2(ui->Num2->currentText().toInt());
    unit->setNum3(m_SSOI_SD_Num3.key(ui->Num3->currentText()));
    unit->setOutType(m_SSOI_SD_OutType.key(ui->OutType->currentText()));

    int key=m_SSOI_SD_OutType.key(ui->OutType->currentText());

        unit->setOutType(key);
        if(key<8)
        {

            unit->setBazalt(0);
            unit->setConnectBlock(0);
        }
        else if(key==8)
        {
     //       unit->setOutType(0);
            unit->setBazalt(1);
            unit->setConnectBlock(0);
            unit->setDK(0);
        }
        else if(key=9)
        {
    //        unit->setOutType(0);
            unit->setBazalt(0);
            unit->setConnectBlock(1);
            unit->setDK(0);
        }
}

void Widget_SSOI_SD::update_name()
{
    QString Name("");
    Name+="Канал";


    Name+=this->ui->Num1->currentText();
    Name+=" БЛ";
    Name+=this->ui->Num2->currentText();


    Name+=" ";
    if(this->ui->Num3->currentText()!="Вскрытие"){
    Name+="СД";
    }
    Name+=this->ui->Num3->currentText();


    if(this->ui->OutType->currentIndex()>0)
    {
    Name+=" ";
    Name+=this->ui->OutType->currentText();
    }

    emit updateName(Name);

}

void Widget_SSOI_SD::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
    ui->Num3->setEnabled(val);

}

bool Widget_SSOI_SD::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer());
    //СД может быть добавлен только к группе или к системе


    if(!parent)
    return false;

        if((parent->getType()!=TypeUnitNode::GROUP)&&(parent->getType()!=TypeUnitNode::SYSTEM))
        {
   //         QMessageBox::critical(0,"Ошибка","СД может быть добавлен только к группе или к системе");
            return false;

        }
   //Num2 от нуля до 99
    if(unit->getNum2()<0||unit->getNum2()>99)
        return false;



    if(already_in_the_tree(unit,modelTreeUN,current))
        return false;


   return true;

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
    QString str;
    QString UdpAdress=unit->getUdpAdress();


    str.append(" : Канал");

    str.append(QString::number(unit->getNum1()));


    str.append(" : БЛ");
    str.append(QString::number(unit->getNum2()));
    str.append(" : ");

    //СД




    if(unit->getNum3()==9){
    str+="Вскрытие";
    }else{

    str+=" СД";
    str+=QString::number(unit->getNum3());
    }

    if(unit->getBazalt()==1)
        {
            str.append("+");
            str.append("ИУ");
            str.append(QString::number(unit->getNum3()));
        }
    else
    if(unit->getConnectBlock()==1)
        {
            str.append("+");
            str.append("ИУ");
            str.append(QString::number(unit->getNum3()-3));
        }

    str.append("  ");





    if(unit->getBazalt())
    {

        str.append(m_SSOI_SD_OutType.value(8));
    }
    else if(unit->getConnectBlock())
    {

        str.append(m_SSOI_SD_OutType.value(9));
    }
    else
    {

        int val = unit->getOutType();
        if(val)
        str.append(m_SSOI_SD_OutType.value(unit->getOutType()));
    }




   return str;
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
    ui->OutType->clear();




    if(arg1=="Вскрытие"){
        ui->OutType->setCurrentIndex(0);
        ui->OutType->setVisible(false);
        ui->label_111->setVisible(false);

    }else{




        for(int i=0;i<8;i++)    {
            ui->OutType->insertItem(i,m_SSOI_SD_OutType.value(i));
        }
        switch(arg1.toInt())
        {
        case 1:
        case 2:
        case 3:
        ui->OutType->insertItem(8,m_SSOI_SD_OutType.value(8));

            break;

        case 4:
        case 5:
        case 6:
    this->ui->OutType->insertItem(9,m_SSOI_SD_OutType.value(9));

        break;

        }

        ui->OutType->setVisible(true);
        ui->label_111->setVisible(true);



    }
     update_name();

}

void Widget_SSOI_SD::on_OutType_currentIndexChanged(const QString &arg1)
{
    update_name();
}
