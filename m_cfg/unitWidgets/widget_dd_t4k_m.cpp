#include "widget_dd_t4k_m.h"
#include "ui_widget_dd_t4k_m.h"

Widget_DD_T4K_M::Widget_DD_T4K_M(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_DD_T4K_M)
{
    ID=TypeUnitNode::DD_T4K_M;
    ui->setupUi(this);

    for(int i=1;i<27;i++){
        ui->Num2->addItem(QString::number(i));
    }
}

Widget_DD_T4K_M::~Widget_DD_T4K_M()
{
    delete ui;
}

void Widget_DD_T4K_M::get_from(UnitNode *unit)
{
    ui->Num2->setCurrentText(QString::number(unit->getNum2()));
}

void Widget_DD_T4K_M::get_default()
{
ui->Num2->setCurrentIndex(0);
}



void Widget_DD_T4K_M::set_to(UnitNode *unit)
{
    qDebug()<<"set_to "<<m_TypeUnitNode_d.value(unit->getType());
    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer());

    if(parent){


    int val=parent->getNum2();


    unit->setNum2(this->ui->Num2->currentText().toInt()+val);


    unit->setNum1(parent->getNum1());
    unit->setNum3(parent->getNum3());

    unit->setUdpUse(parent->getUdpUse());
    unit->setUdpPort(parent->getUdpPort());
    unit->setUdpAdress(parent->getUdpAdress());
    unit->setUdpTimeout(parent->getUdpTimeout());

    qDebug()<<"end set_to "<<m_TypeUnitNode_d.value(unit->getType());
    }
}

void Widget_DD_T4K_M::update_name()
{
    QString Name;
    Name.clear();

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer());
    if(parent){


    Name.append(" ДД");
    if(parent){
        Name.append(QString::number(parent->getNum2()/100));
    Name.append("-");
    }
    Name.append(this->ui->Num2->currentText());

    emit updateName(Name);
    }

}

void Widget_DD_T4K_M::setEnabled_option_menu(bool val)
{
    ui->Num2->setEnabled(val);
}

bool Widget_DD_T4K_M::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{

qDebug()<<"accepted "<<m_TypeUnitNode_d.value(unit->getType());
bool res=true;

if(!current){
return false;



}


UnitNode* parent;
parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}

if(!parent){
return false;

}

//добавлять только к участку Сота
if(parent->getType()!=TypeUnitNode::Y4_T4K_M)
{
 //    QMessageBox::critical(0,"Ошибка","ДД может быть добавлен только к участку !");
       return false;
}



//Формируем список всех ДД этого БОДа

QList<UnitNode*> List;

    //Ищем нужный БОД. Это родитель родителя.

    QModelIndex ind = modelTreeUN->findeIndexUN(parent);
    QModelIndex BOD_ind = modelTreeUN->parent(ind);
//    UnitNode* BOD=static_cast<UnitNode*>(BOD_ind.internalPointer());

    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);

    foreach(UnitNode *un, List1 )
    {
        //qDebug()<<".";
        //qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
         QModelIndex index=modelTreeUN->findeIndexUN(un);
        QModelIndex parent_index= modelTreeUN->parent(index);

        QModelIndex BOD_index= modelTreeUN->parent(parent_index);
        //если юнит является ДД и принадлежит к одномцу из участков того БОДа что и участок к которому добавляем

        if(BOD_index==BOD_ind)       {
            //qDebug()<<"Name: "<<un->getName();
            List.append(un);
        }
    }

//  Ищем номер участка ДД
int numberArea=0;
numberArea=parent->getNum2()/100;


qDebug()<<"номер участка"<<numberArea;

if(numberArea==1){

//Если номер участка 1 - дд должно быть меньше чем наименьший ДД с участка 2

//Находим наименьший ДД участка 2

int min=100;
foreach(UnitNode *un, List )
    {
        //его индекс
        QModelIndex ind = modelTreeUN->findeIndexUN(un);
        //индекс его родителя
        QModelIndex parent_ind =  modelTreeUN->parent(ind);
        //юнит его родителя
        UnitNode *parent = static_cast<UnitNode*>(parent_ind.internalPointer());
    //если участок 2

        if(parent->getNum2()/100==2){
            qDebug()<<"юнит на участке 2";
            qDebug()<<"dd  "<<QString::number((un->getNum2()-parent->getNum2()));

            if(un->getNum2()-parent->getNum2()<min){

                min = un->getNum2()-parent->getNum2();
            }
        }
    }

    qDebug()<<"min "<<min;
    qDebug()<<"dd  "<<QString::number(unit->getNum2()-numberArea*100);
    if(!(unit->getNum2()-numberArea*100<min))
        res=false;

}


if(numberArea==2){

//Если номер участка 2 - дд должно быть больше чем наибольший ДД с участка 1

//Находим наименьший ДД участка 1

int max=0;
foreach(UnitNode *un, List )
    {
        //его индекс
        QModelIndex ind = modelTreeUN->findeIndexUN(un);
        //индекс его родителя
        QModelIndex parent_ind =  modelTreeUN->parent(ind);
        //юнит его родителя
        UnitNode *parent = static_cast<UnitNode*>(parent_ind.internalPointer());
    //если участок 2

        if(parent->getNum2()/100==1){
            qDebug()<<"юнит на участке 1";
            qDebug()<<"dd  "<<QString::number(un->getNum2()-parent->getNum2());
            if(un->getNum2()-parent->getNum2()>max){

                max = un->getNum2()-parent->getNum2();
            }
        }
    }
qDebug()<<"max "<<max;
qDebug()<<"dd  "<<QString::number(unit->getNum2()-numberArea*100);

    if(!(unit->getNum2()-numberArea*100>max))
        res=false;

}

if(numberArea==3){

//Если номер участка 3 - дд должно быть меньше чем наименьший ДД с участка 4

//Находим наименьший ДД участка 4

int min=100;
foreach(UnitNode *un, List )
    {
        //его индекс
        QModelIndex ind = modelTreeUN->findeIndexUN(un);
        //индекс его родителя
        QModelIndex parent_ind =  modelTreeUN->parent(ind);
        //юнит его родителя
        UnitNode *parent = static_cast<UnitNode*>(parent_ind.internalPointer());
    //если участок 4

        if(parent->getNum2()/100==4){
            qDebug()<<"юнит на участке 2";
            qDebug()<<"dd  "<<QString::number((un->getNum2()-parent->getNum2()));

            if(un->getNum2()-parent->getNum2()<min){

                min = un->getNum2()-parent->getNum2();
            }
        }
    }

    qDebug()<<"min "<<min;
    qDebug()<<"dd  "<<QString::number(unit->getNum2()-numberArea*100);
    if(!(unit->getNum2()-numberArea*100<min))
        res=false;

}


if(numberArea==4){

//Если номер участка 4 - дд должно быть больше чем наибольший ДД с участка 3

//Находим наименьший ДД участка 1

int max=0;
foreach(UnitNode *un, List )
    {
        //его индекс
        QModelIndex ind = modelTreeUN->findeIndexUN(un);
        //индекс его родителя
        QModelIndex parent_ind =  modelTreeUN->parent(ind);
        //юнит его родителя
        UnitNode *parent = static_cast<UnitNode*>(parent_ind.internalPointer());
    //если участок 3

        if(parent->getNum2()/100==3){
            qDebug()<<"юнит на участке 1";
            qDebug()<<"dd  "<<QString::number(un->getNum2()-parent->getNum2());
            if(un->getNum2()-parent->getNum2()>max){

                max = un->getNum2()-parent->getNum2();
            }
        }
    }
qDebug()<<"max "<<max;
qDebug()<<"dd  "<<QString::number(unit->getNum2()-numberArea*100);

    if(!(unit->getNum2()-numberArea*100>max))
        res=false;

}



if(res==true)
    return
!already_on_the_branch(unit,modelTreeUN,current);


    return false;
}

bool Widget_DD_T4K_M::equal(UnitNode *un, UnitNode *unit)
{
    if(un->getNum2()==unit->getNum2())
    return true;


    return false;
}

QString Widget_DD_T4K_M::get_string(UnitNode *unit)
{

    QString str;
    QModelIndex ind = this->modelTreeUN->findeIndexUN(unit);
    QModelIndex ind_Y4 = this->modelTreeUN->parent(ind);
    UnitNode* Y4= static_cast<UnitNode*>(ind_Y4.internalPointer());

    QModelIndex ind_BOD = this->modelTreeUN->parent(ind_Y4);



    UnitNode* BOD= static_cast<UnitNode*>(ind_BOD.internalPointer());

    str+=" : БОД ";



    str+=QString::number(BOD->getNum1());

    str+=" : Участок ";

    str+=QString::number(Y4->getNum2()/100);

    str+=" : ДД ";

    str+=UnitWidget::get_dd(unit);

    return str;
}



void Widget_DD_T4K_M::on_Num2_currentIndexChanged(const QString &arg1)
{
    update_name();
}
