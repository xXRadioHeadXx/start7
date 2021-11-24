#include "widget_ssoi_ip_sd.h"
#include "ui_widget_ssoi_ip_sd.h"

Widget_SSOI_IP_SD::Widget_SSOI_IP_SD(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_SSOI_IP_SD)
{
    ID=TypeUnitNode::SSOI_IP_SD;
    ui->setupUi(this);
    comm_is_needed=true;
    coord_mode=coordinateWigget_mode::for_all;

    for (int i=1;i<100;i++)
        ui->Num1->addItem(QString::number(i));

    for(int i=0;i<m_SSOI_SD_OutType.size();i++)
    {
        this->ui->OutType->insertItem(i,m_SSOI_SD_OutType.value(i));
    }

    foreach(QString str, m_SSOI_SD_Num3){
        this->ui->Num2->addItem(str);

    }

}

Widget_SSOI_IP_SD::~Widget_SSOI_IP_SD()
{
    delete ui;
}

void Widget_SSOI_IP_SD::get_from(UnitNode *unit)
{
    qDebug()<<"Widget_SD_BL_IP::get_from";

    ui->Num1->setCurrentText(QString::number(unit->getNum1()));
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
    ui->OutType->setCurrentText(m_SSOI_SD_OutType.value(unit->getOutType()));
}

void Widget_SSOI_IP_SD::get_default()
{
    qDebug()<<"Widget_SD_BL_IP::get_default";
    ui->Num1->setCurrentIndex(0);
    ui->Num2->setCurrentIndex(0);
    comm->set_udpTimeout(50*ui->Num1->currentText().toInt());
    ui->OutType->setCurrentText(m_SSOI_SD_OutType.value(0));
}

void Widget_SSOI_IP_SD::set_to(UnitNode *unit)
{
    unit->setNum1(ui->Num1->currentText().toInt());
    unit->setNum2(ui->Num2->currentText().toInt());
    //Set OutType
    int key=m_SD_BL_IP_OutType.key(ui->OutType->currentText());

        unit->setOutType(key);
    if(key<8)
    {

        unit->setBazalt(0);
        unit->setConnectBlock(0);
    }
    else if(key==8)
    {

        unit->setBazalt(1);
        unit->setConnectBlock(0);
        unit->setDK(0);
    }

//    unit->setUdpTimeout(unit->getNum1()*50);

}

void Widget_SSOI_IP_SD::update_name()
{
    QString name;

    name.append("CCOИ IP ");


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

   name.append(" Канал ");
   name.append(ui->Num1->currentText());

    name.append(" СД");
    name.append("-");

    //if(this->ui->SD_BL_IP_num_combobox->currentText().toInt()<10)
    //name.append("0");

    name.append(this->ui->Num2->currentText());


  //  updater->updateName(name);
    emit updateName(name);
}

void Widget_SSOI_IP_SD::setEnabled_option_menu(bool val)
{
    ui->Num1->setEnabled(val);
    ui->Num2->setEnabled(val);
    comm->setEnabled(val);
}

bool Widget_SSOI_IP_SD::timeout_brother(UnitNode *unit,UnitNode *un)
{
    if(unit->getNum1()==un->getNum1())
    {
        if(un->getType()==TypeUnitNode::SSOI_IP_IU)
            return true;
        if(un->getType()==TypeUnitNode::SSOI_IP_SD)
            return true;
    }

    return false;
}

bool Widget_SSOI_IP_SD::accepted(UnitNode *unit)
{
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}


    if((unit->getUdpPort()!=4001)&&
            (unit->getUdpPort()!=4002)&&
            (unit->getUdpPort()!=4003)&&
            (unit->getUdpPort()!=4004))
        return false;

    if((parent->getType()!=TypeUnitNode::GROUP)&&(parent->getType()!=TypeUnitNode::SYSTEM))
    {

//        QMessageBox::critical(0,"Ошибка","СД может быть добавлен только к группе или к системе");

        return false;

    }
//Num2 от нуля до восьми
if(unit->getNum2()<0||unit->getNum2()>8)
    return false;

//Не должен повторяться в дереве
return no_equal_unit(unit);
}

bool Widget_SSOI_IP_SD::equal(UnitNode *unit, UnitNode *un)
{


    if(un->getType()==unit->getType())
    if(un->getNum1()==unit->getNum1())
    if(un->getNum2()==unit->getNum2())

    return true;


    return false;
}

QString Widget_SSOI_IP_SD::get_string(UnitNode *unit)
{

    QString UdpAdress=unit->getUdpAdress();
    QString str;
    str.append("<b>");str.append("ССОИ IP");str.append("</b> ");//  БЛ-IP</b> ");
    str.append(" ");




    if(unit->getUdpUse()==0)
    {
        str.append(QString::number(unit->getNum3()));

    if(unit->getUdpAdress()!="")
    {
        str.append(" (");
        str.append(unit->getUdpAdress());
        str.append(")");
    }
    }
    if(unit->getUdpUse()==1)
    {
        str.append(unit->getUdpAdress());
        str.append("::");
        str.append(QString::number(unit->getUdpPort()));

        str.append("\n");
        str.append(" Канал ");
        str.append(QString::number(unit->getNum1()));

        str.append(" СД:");
        str.append(QString::number(unit->getNum2()));

        if(unit->getBazalt()==1)
        {
            str.append(" +");
            str.append(" ИУ:");
            str.append(QString::number(unit->getNum2()));
        }


        str.append("\n");
        str.append("Таймаут: ");
        str.append(QString::number(unit->getUdpTimeout()));
        str.append("\n");
    }

        str.append(" ");
    if(unit->getBazalt())
    {
        str.append(m_SD_BL_IP_OutType.value(8));
    }
    else
    {
        int val = unit->getOutType();
        if(val)
        str.append(m_SD_BL_IP_OutType.value(unit->getOutType()));
    }
    return str;
}

void Widget_SSOI_IP_SD::on_Num1_currentIndexChanged(const QString &arg1)
{
    update_name();
    qDebug()<<ui->Num1->currentText();
    comm->set_udpTimeout(50*ui->Num1->currentText().toInt());

}

void Widget_SSOI_IP_SD::on_Num2_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_SSOI_IP_SD::on_OutType_currentIndexChanged(const QString &arg1)
{
    update_name();
}
