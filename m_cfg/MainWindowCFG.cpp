#include "MainWindowCFG.h"
#include "ui_MainWindowCFG.h"

#include "QFileDialog"
#include <QErrorMessage>



MainWindowCFG::MainWindowCFG(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowCFG)
{
    ui->setupUi(this);
  //  this->current_index=nullptr;


 //   QString patch="C:/WORK1/start7/rifx.ini";

    this->modelTreeUN = new TreeModelUnitNode(this);

    modelTreeUN->setTypeApp(SubTypeApp::configurator);

    ui->treeView->setModel(this->modelTreeUN);

    ui->treeView->setColumnWidth(0,1000);
    ui->treeView->setColumnWidth(1,1000);
    ui->treeView->setColumnWidth(2,1000);
 //   QString patch=QFileDialog::getOpenFileName(this, "open file","","*.ini");
 //    qDebug()<<"patch = "<<patch;
 //   this->modelTreeUN->loadSettings(patch);



    for(int i=1;i<100;i++)
    {
    this->ui->BOD_T4K_M_comboBox_Num1->addItem(QString::number(i));
    this->ui->Y4_T4K_M_comboBox_Num1->addItem(QString::number(i));
    this->ui->Y4_T4K_M_comboBox_Num2->addItem(QString::number(i));
    this->ui->DD_Sota_M_combobox->addItem(QString::number(i));
    }


    connect(this->map.scene,SIGNAL(select(QString)),this,SLOT(select(QString)));

    connect(this->map.scene,SIGNAL(point(QString,int,int)),this,SLOT(set_x_y(QString,int,int)));

    this->ui->textEdit->clear();

    this->ui->stackedWidget->setCurrentWidget(this->ui->empty_space_groupbox);
  //  this->ui->textEdit->setText("1111111\n 22222");


    dialog.showMessage("this it the test message");
    dialog.exec();
}

MainWindowCFG::~MainWindowCFG()
{
    delete ui;
}

bool MainWindowCFG::load(QString patch)
{
    bool res=true;






    return res;
}

void MainWindowCFG::select(QString Name)
{

foreach(UnitNode* un,this->modelTreeUN->listItemUN)
{
    if(un->getName()==Name)
    {
        get_option(un);
        this->ui->treeView->setCurrentIndex( this->modelTreeUN->findeIndexUN(un));
    }


}

}

void MainWindowCFG::set_x_y(QString Name, int x, int y)
{

    foreach(UnitNode* un,this->modelTreeUN->listItemUN)
    {
        if(un->getName()==Name)
        {
        un->setX(x);
        un->setY(y);
        get_option(un);
        }


    }
  /*  */
}


void MainWindowCFG::on_treeView_clicked(const QModelIndex &index)
{
    current_index=index;
    UnitNode *unit = static_cast<UnitNode*>(index.internalPointer());


this->get_option(unit);
}


void MainWindowCFG::get_option(UnitNode* unit)
{
   this->ui->textEdit->clear();
    qDebug()<<"get option";
qDebug()
<<"; Name "<< unit->getName()
<<"; Type "<<unit->getType()
<<"; Num1 "<<QString::number(unit->getNum1())
<<"; Num2 "<<QString::number(unit->getNum2())
<<"; Num3 "<<QString::number(unit->getNum3())
<<"; Level "<<QString::number(unit->getLevel())
//<<"IconVisible "<<unit->getIconVisible()
<<"; X "<<QString::number(unit->getX())
<<"; Y "<<QString::number(unit->getY())
<<"; DK "<<QString::number(unit->getDK())
<<"; Bazalt "<<QString::number(unit->getBazalt())
<<"; Metka "<<QString::number(unit->getMetka())
<<"; Razriv "<<QString::number(unit->getRazriv())
<<"; AdamOff "<<QString::number(unit->getAdamOff())
<<"; AlarmMsgOn "<<QString::number(unit->getAlarmMsgOn())
<<"; ConnectBlock "<<QString::number(unit->getConnectBlock())
<<"; OutType "<<QString::number(unit->getOutType())
<<"; asoosd_kk "<<QString::number(unit->getAsoosd_kk())
<<"; asoosd_nn "<<QString::number(unit->getAsoosd_nn())
<<"; Description "<<unit->getDescription()
<<"; lan "<<QString::number(unit->getLan())
<<"; lon "<<QString::number(unit->getLon())
<<"; UdpUse "<<QString::number(unit->getUdpUse())
<<"; UdpAdress "<<unit->getUdpAdress()
<<"; UdpPort "<<unit->getUdpPort()
<<"; UdpTimeout "<<unit->getUdpTimeout();
    selected_type=unit->getType();
/*QString Name=unit->getName();

    this->ui->uName_lineedit->setText(Name);

    selected_type=unit->getType();

    QString Type=this->Type_from_int_to_string(selected_type);

  //  this->ui->uType_combobox->setTe
    this->ui->CD_comboBox_Num2->setCurrentText("");
    this->ui->CD_DK_checkBox->setChecked(false);
    this->ui->CD_Bazalt_checkBox->setChecked(false);
    this->ui->CD_connectblock_checkBox->setChecked(false);

    this->ui->uType_combobox->setCurrentText("");
    this->ui->stackedWidget->setCurrentWidget(this->ui->Empty_space);




    this->ui->IU_comboBox_Num2->setCurrentText("");


    this->ui->TG_comboBox_Num1->setCurrentText("");
    this->ui->TG_comboBox_Num2->setCurrentText("");
    this->ui->TG_UdpUse_checkBox->setChecked(false);

    int UdpUse=0;
    QString UdpAdress;
    int UdpPort;

        this->ui->uType_combobox->setCurrentText(Type);

*/
    switch(selected_type)
    {
    case TypeUnitNode::GROUP:
    this->get_option_GROUP(unit);
    break;

    case TypeUnitNode::SD_BL_IP:
    this->get_option_SD_BL_IP(unit);
    break;

    case TypeUnitNode::IU_BL_IP:
    this->get_option_IU_BL_IP(unit);
    break;

    case TypeUnitNode::TG:
    this->get_option_TG(unit);
    break;

    case TypeUnitNode::RLM_KRL:
    this->get_option_RLM_KRL(unit);
    break;

    case TypeUnitNode::RLM_C:
    this->get_option_RLM_C(unit);
    break;

    case TypeUnitNode::BOD_T4K_M:
    this->get_option_BOD_T4K_M(unit);
    break;

    case TypeUnitNode::Y4_T4K_M:
    this->get_option_Y4_T4K_M(unit);
    break;

    case TypeUnitNode::DD_T4K_M:
    this->get_option_DD_T4K_M(unit);
    break;

    case TypeUnitNode::BOD_SOTA:
    this->get_option_BOD_SOTA(unit);
    break;

    case TypeUnitNode::Y4_SOTA:
    this->get_option_Y4_SOTA(unit);
    break;
/*
    case TypeUnitNode::DD_SOTA:
    this->get_option_DD_SOTA(unit);
    break;*/

    case TypeUnitNode::BL_IP:
    this->get_option_BL_IP(unit);
    break;



    }


}

void MainWindowCFG::get_option_GROUP(UnitNode *unit)
{
    unit->setNum1(0);
    unit->setNum2(0);
    unit->setNum3(0);
}



QString MainWindowCFG::Type_from_int_to_string(int int_Type)
{
    QString Type;
    Type.clear();

    switch(int_Type)
    {
    case TypeUnitNode::GROUP:
    Type.append("Группа");
    break;

    case TypeUnitNode::SD_BL_IP:
    Type.append("СД БЛ-IP");
    break;

    case TypeUnitNode::IU_BL_IP:
    Type.append("ИУ БЛ-IP");
    break;

    case TypeUnitNode::TG:
    Type.append("Точка/Гарда");
    break;

    case TypeUnitNode::RLM_KRL:
    Type.append("РИФ-РЛМ/КРЛ/Трасса");
    break;

    case TypeUnitNode::RLM_C:
    Type.append("РИФ-РЛМ-С");
    break;

    case TypeUnitNode::BOD_T4K_M:
    Type.append("БОД Точка-М/Гряда");
    break;

    case TypeUnitNode::Y4_T4K_M:
    Type.append("Участок Точка-М/Гряда");
    break;

    case TypeUnitNode::BOD_SOTA:
    Type.append("БОД Сота/Сота-М");
    break;

    case TypeUnitNode::Y4_SOTA:
    Type.append("Участок Сота/Сота-М");
    break;

    case TypeUnitNode::DD_SOTA:
    Type.append("ДД Сота/Сота-М");
    break;
 /*
    if(arg1=="БОД Сота/Сота-М")
    this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_Sota_M_groupbox);
    else
    if(arg1=="Участок Сота/Сота-М")
    this->ui->stackedWidget->setCurrentWidget(this->ui->U4_Sota_M_groupbox);
        else
    if(arg1=="ДД Сота/Сота-М")
    this->ui->stackedWidget->setCurrentWidget(this->ui->DD_Sota_M_groupbox);
*/

//Участок Точка-М/Гряда
//БОД Точка-М/Гряда
    /*
    case BL_IP:
    Type.append("BL_IP");
    break;
    */

    }
    return Type;
}

int MainWindowCFG::Type_from_string_to_int(QString Type)
{

    if(Type=="Группа")
        return TypeUnitNode::GROUP;

    if(Type=="СД БЛ-IP")
        return TypeUnitNode::SD_BL_IP;

    if(Type=="БОД Сота/Сота-М")
        return TypeUnitNode::BOD_SOTA;

    if(Type=="Участок Сота/Сота-М")
        return TypeUnitNode::Y4_SOTA;

    if(Type=="ДД Сота/Сота-М")
        return TypeUnitNode::DD_SOTA;
    /*
    case TypeUnitNode::GROUP:
break;


    Type.append("Группа");
    break;

    case TypeUnitNode::SD_BL_IP:
    Type.append("СД БЛ-IP");
    break;

    case TypeUnitNode::IU_BL_IP:
    Type.append("ИУ БЛ-IP");
    break;

    case TypeUnitNode::TG:
    Type.append("Точка/Гарда");
    break;

    case TypeUnitNode::RLM_KRL:
    Type.append("РИФ-РЛМ/КРЛ/Трасса");
    break;

    case TypeUnitNode::RLM_C:
    Type.append("РИФ-РЛМ-С");
    break;

    case TypeUnitNode::BOD_T4K_M:
    Type.append("БОД Точка-М/Гряда");
    break;

    case TypeUnitNode::Y4_T4K_M:
    Type.append("Участок Точка-М/Гряда");
    break;
    */
}

bool MainWindowCFG::this_name_is_free(QString Name)
{


    foreach(UnitNode *un, this->modelTreeUN->listItemUN )
    {
     qDebug()<< un->getName()<<" "<< Name ;
     if(un->getName()==Name)
     {
         qDebug()<<"уже есть такое имя";
         return false;
     }


    }


    return true;
}

void MainWindowCFG::update_map()
{

    foreach(UnitNode* un, this->modelTreeUN->listItemUN)
    {

       if(false==map.find(un->getName()))
       {
           map.Add(un->getName(),un->getPxm(SubTypeApp::configurator),un->getX(),un->getY());



       }

    }
}












void MainWindowCFG::on_uType_combobox_currentTextChanged(const QString &arg1)
{



    if(arg1=="Группа")
    this->ui->stackedWidget->setCurrentWidget(this->ui->Group_groupbox);
    else
    if(arg1=="СД БЛ-IP")
    this->ui->stackedWidget->setCurrentWidget(this->ui->CD_BL_IP_groupbox);
    else
    if(arg1=="ИУ БЛ-IP")
    this->ui->stackedWidget->setCurrentWidget(this->ui->IU_BL_IP_groupbox);
    else
    if(arg1=="Точка/Гарда")
    this->ui->stackedWidget->setCurrentWidget(this->ui->TG_groupbox);
    else
    if(arg1=="РИФ-РЛМ/КРЛ/Трасса")
    this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_KRL_groupbox);
    else
    if(arg1=="РИФ-РЛМ-С")
    this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_C_groupbox);
    else
    if(arg1=="БОД Точка-М/Гряда")
    this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_T4K_M_groupbox);
    else
    if(arg1=="Участок Точка-М/Гряда")
    this->ui->stackedWidget->setCurrentWidget(this->ui->Y4_T4K_M_groupbox);

    if(arg1=="БОД Сота/Сота-М")
     {
    this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_Sota_M_groupbox);
            this->ui->BOD_SOTA_M_type_combobox->setCurrentText("RS485");
 //   this->ui->BOD_UDP_RS485_stacked->setCurrentWidget(this->ui->BOD_RS485);
     }
    else
    if(arg1=="Участок Сота/Сота-М")
    this->ui->stackedWidget->setCurrentWidget(this->ui->U4_Sota_M_groupbox);
    else
    if(arg1=="ДД Сота/Сота-М")
    this->ui->stackedWidget->setCurrentWidget(this->ui->DD_Sota_M_groupbox);


    else
    this->ui->stackedWidget->setCurrentWidget(this->ui->empty_space_groupbox);


//Участок Точка-М/Гряда
//   БОД Точка-М/Гряда

    //РИФ-РЛМ-С

  //  РИФ-РЛМ/КРЛ/Трасса

}



void MainWindowCFG::on_pushButton_4_clicked()
{
    qDebug()<<"rename_unit()";
//   change_unit();



}

bool MainWindowCFG::set_option(UnitNode *unit, UnitNode* parent)
{

/*
if(this_name_is_free(this->ui->uName_lineedit->text())==false)
{
    qDebug()<<"[ERROR]";
    return false;
}*/

    qDebug()<<"[set_option]";
int type=this->Type_from_string_to_int(this->ui->uType_combobox->currentText());
       switch(type)
       {

       case TypeUnitNode::SD_BL_IP:
       this->set_option_SD_BL_IP(unit);
       break;

       case TypeUnitNode::IU_BL_IP:
       this->get_option_IU_BL_IP(unit);
       break;

       case TypeUnitNode::TG:
  //     this->get_option_TG(unit);
       break;

       case TypeUnitNode::RLM_KRL:
  //     this->get_option_RLM_KRL(unit);
       break;

       case TypeUnitNode::RLM_C:
  //     this->get_option_RLM_C(unit);
       break;

       case TypeUnitNode::BOD_T4K_M:
  //     this->get_option_BOD_T4K_M(unit);
       break;

       case TypeUnitNode::Y4_T4K_M:
  //     this->get_option_Y4_T4K_M(unit);
       break;

       case TypeUnitNode::DD_T4K_M:
  //     this->get_option_DD_T4K_M(unit);
       break;

       case TypeUnitNode::BOD_SOTA:
       this->set_option_BOD_SOTA(unit);
       break;

       case TypeUnitNode::Y4_SOTA:
       this->set_option_Y4_SOTA(unit);
       break;

       case TypeUnitNode::DD_SOTA:
       this->set_option_DD_SOTA(unit,parent);
       break;/**/

       case TypeUnitNode::BL_IP:
  //     this->get_option_BL_IP(unit);
       break;



       }
return true;

}

void MainWindowCFG::set_option_GROUP(UnitNode *unit)
{

}






void MainWindowCFG::on_actionCreate_triggered()
{
    qDebug()<<"[Create]";
    this->modelTreeUN->makeEmptyTree();
}

void MainWindowCFG::on_actionOpen_triggered()
{
     qDebug()<<"[Open]";
     this->modelTreeUN->rootItemUN->deleteAll();
     QString patch=QFileDialog::getOpenFileName(this, "open file","","*.ini");
      qDebug()<<"patch = "<<patch;
     this->modelTreeUN->loadSettings(patch);
      this->update_map();
 //    this->modelTreeUN->updateUNStructure();

}


void MainWindowCFG::on_actionSave_triggered()
{
   QString path=QFileDialog::getSaveFileName(this, "save file","","*.ini");

       QFile file(path);
       file.open(QIODevice::WriteOnly | QIODevice::Text);
         QTextStream out(&file);
         out << "This file is generated by Qt\n";

         // optional, as QFile destructor will already do it:
         file.close();
    this->save_ini(path);
}

void MainWindowCFG::on_treeView_activated(const QModelIndex &index)
{
    qDebug()<<"activated";
}

void MainWindowCFG::on_pushButton_clicked()
{
   add_unit();
}


bool MainWindowCFG::can_i_add_or_not(int type_parrent, int type_child)
{
    return true;
}

bool MainWindowCFG::pass_to_add(UnitNode *unit, UnitNode *parrent)
{

qDebug()<<"[can_i_add_or_not?]";

if(unit->getName()=="")
{
    dialog.showMessage("Введите имя устройства");
    dialog.exec();
    return false;

}


//Если БОД Сота-М, то:
if(unit->getType()==TypeUnitNode::BOD_SOTA)
{
if(false==pass_to_add_BOD_SOTA(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::Y4_SOTA)
{
if(false==pass_to_add_Y4_SOTA(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::DD_SOTA)
{
if(false==pass_to_add_DD_SOTA(unit,parrent))
    return false;
}

return true;
}

bool MainWindowCFG::pass_to_add_BOD_SOTA(UnitNode *unit, UnitNode *parrent)
{
    //БОД может быть добавлен только к группе
        if(parrent->getType()!=TypeUnitNode::GROUP)
        {
            dialog.showMessage("БОД может быть добавлен только к группе");
            dialog.exec();
            return false;

        }

    //    Если связь по RS485 - контроль по RS485 порту
    //    Если связь по UDP - контроль по IP адресу

     //     qDebug()<<"[BOD_SOTA]";
            if(unit->getUdpUse()==0)
            {
          //            qDebug()<<"[getUdpUse()==0]";
                foreach(UnitNode *un, this->modelTreeUN->listItemUN )
                {

            qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
                 if((un->getNum3()==unit->getNum3()))
                 {

                     dialog.showMessage("этот COM порт  уже  занят");
                     dialog.exec();
                     return false;
                 }


                }
             //проконтроилровать отсутствие в дереве такого же порта

            }
            if(unit->getUdpUse()==1)
            {
              //проконтроилровать отсутствие в дереве такого же IP адреса
                foreach(UnitNode *un, this->modelTreeUN->listItemUN )
                {
       //     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
                 if((un->getUdpAdress()==unit->getUdpAdress()))
                  {

                     dialog.showMessage("этот IP адрес уже  занят");
                     dialog.exec();
                     return false;
                  }
                }
            }
            return true;
}

bool MainWindowCFG::pass_to_add_Y4_SOTA(UnitNode *unit, UnitNode *parrent)
{
    qDebug()<<"[pass_to_add_Y4_SOTA]";
    //Участок может быть добавлен только к БОД Сота/Сота-М
    if(parrent->getType()!=TypeUnitNode::BOD_SOTA)
    {
        dialog.showMessage("Участок может быть добавлен только к БОД Сота/Сота-М!");
        dialog.exec();
        return false;

    }

    //В одном БОД Сота/Сота-М не должно быть "участков" с двумя одинаковыми участками

    //Составить лист участков этого БОДА
    QList<UnitNode*> List;

    foreach(UnitNode *un, this->modelTreeUN->listItemUN )
    {
       qDebug()<<".";
//     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
       QModelIndex index=this->modelTreeUN->findeIndexUN(un);
       QModelIndex parent_index= this->modelTreeUN->parent(index);


     if(this->modelTreeUN->findeIndexUN(parrent)==parent_index)
      {
 //       qDebug()<<"Name: "<<un->getName();
        List.append(un);
      }
    }

    foreach(UnitNode *un, List )
    {
     qDebug()<<"Name: "<<un->getName();
     if(un->getNum2()==unit->getNum2())
     {
         dialog.showMessage("У этого БОДа такой участок уже существует!");
         dialog.exec();
         return false;
     }
    }
    //проконтролировать в нем отсутствие добавляемого участка

    return true;
}

bool MainWindowCFG::pass_to_add_DD_SOTA(UnitNode *unit, UnitNode *parrent)
{
    //добавлять только к участку Сота
    if(parrent->getType()!=TypeUnitNode::Y4_SOTA)
    {
        dialog.showMessage("Участок может быть добавлен только к БОД Сота/Сота-М!");
        dialog.exec();
        return false;

    }

    //В одном боде нет 2х одинаковых ДД

    //Формируем список всех ДД этого БОДа

    //Сравниваем ДД с добавляемым

    QList<UnitNode*> List;

    //Ищем нужный БОД. Это родитель родителя.

    QModelIndex ind = this->modelTreeUN->findeIndexUN(parrent);
    QModelIndex BOD_ind = this->modelTreeUN->parent(ind);
    UnitNode* BOD=static_cast<UnitNode*>(BOD_ind.internalPointer());





    foreach(UnitNode *un, this->modelTreeUN->listItemUN )
    {

       qDebug()<<".";
//     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
       QModelIndex index=this->modelTreeUN->findeIndexUN(un);
       QModelIndex parent_index= this->modelTreeUN->parent(index);

       QModelIndex BOD_index= this->modelTreeUN->parent(parent_index);

//если юнит является ДД и принадлежит к одномцу из участков того БОДа что и участок к которому добавляем


     if(BOD_index==BOD_ind)
      {
 //       qDebug()<<"Name: "<<un->getName();
        List.append(un);
      }
    }

    foreach(UnitNode *un, List )
    {
     qDebug()<<"Name: "<<un->getName();
     if(un->getNum2()==unit->getNum2())
     {
         dialog.showMessage("У этого БОДа такой участок уже существует!");
         dialog.exec();
         return false;
     }
    }
}

bool MainWindowCFG::add_unit()
{
    qDebug()<<"[add_unit()]";
    bool res=1;
    QModelIndex current=this->ui->treeView->currentIndex();
    if (!current_index.isValid())
    {
        res=0;
    qDebug()<<"[no current index]";
    }

    int type=this->Type_from_string_to_int(this->ui->uType_combobox->currentText());

    /*
    QString type_srtring=this->ui->uType_combobox->currentText();
    if(type_srtring=="Группа")
    type=GROUP;
    else
    if(type_srtring=="СД БЛ-IP")
    type=SD_BL_IP;
    else
    if(type_srtring=="ИУ БЛ-IP")
    type=IU_BL_IP;
    else
    res=0;
*/
    qDebug()<<"[Type: "<<type<<"]";

    UnitNode *unit=new UnitNode();
    unit->setName(this->ui->uName_lineedit->text());
    unit->setType(type);



    QModelIndex index=this->ui->treeView->currentIndex();
    UnitNode *parrent = static_cast<UnitNode*>(index.internalPointer());
    unit->setLevel(parrent->getLevel()+1);

set_option(unit,parrent);
    //Проверить можно ли добавлять юнит к этому родителю
    //Определить тип родителя
    int parrent_type;

    //Определить тип чайлда
    int child_type;



    if (index.isValid())
    {
        if(pass_to_add(unit,parrent))
        {
      this->modelTreeUN->appendNewUNInStructure(index,unit);
  //      map.Add(unit->getName(),unit->getPxm(SubTypeApp::configurator),unit->getX(),unit->getY());
        }
        else
            qDebug()<<"Нельзя добавить юнит к этому родителю";
    }

    ui->treeView->setCurrentIndex(index);
    this->ui->treeView->expand(index);




    return res;

}

bool MainWindowCFG::change_unit()
{
    UnitNode *unit = static_cast<UnitNode*>(current_index.internalPointer());
    //проверка имени
    //Взять имя юнита
    //найти номер юнита в списке по его имени
    //перебрать все остальные юниты по номерам кроме этого номера
    //



    QString origin_name=unit->getName();
    QString new_name=    this->ui->uName_lineedit->text();

    bool res=true;

    if(origin_name!=new_name)
    {
        if(this->this_name_is_free(new_name)==false)
        {
            res=false;
        }

    }

 //   if(res==true)
 //   set_option(unit);
}

bool MainWindowCFG::delete_unit()
{
    QModelIndex index=this->ui->treeView->currentIndex();

    UnitNode *unit = static_cast<UnitNode*>(current_index.internalPointer());

    if (index.isValid())
    {
        int i=0;
     foreach(UnitNode* un,this->modelTreeUN->listItemUN)
     {
         if(this->modelTreeUN->findeIndexUN(un)==this->modelTreeUN->findeIndexUN(unit))
         {
             qDebug()<<"delete";
              this->modelTreeUN->deleteUnit(index);
             modelTreeUN->listItemUN.removeAt(i);
             return true;

         }
         i++;

     }



    }
    return false;


/*
    qDebug()<<"============УДАЛЕНИЕ=========";
            QModelIndex current=this->current_index;


        //    if(model->next(current_index).isValid())
      //      QModelIndex test=model->index(current_index.row(),0,model->parent(current_index));

      //      current_index=model->index(current_index.row()+1,0,model->parent(current_index));

    MyItem *item = static_cast<MyItem*>(current.internalPointer());

    //this->map.remove(item->ID);



     model->the_way(&List, current);
   //  QList<QModelIndex> list= model->the_way(current_index);
    foreach(QModelIndex index,List)
     {
        MyItem *item = static_cast<MyItem*>(index.internalPointer());
        qDebug()<<"ID: "<<item->ID<<" Name: "<<item->Name;
        this->map.remove(item->ID);

     }

model->delete_item(model->index(current.row(),0,current.parent()));
current_index=this->ui->treeView->currentIndex();

*/
}

void MainWindowCFG::show_the_tree()
{qDebug()<<"==============================";
    qDebug()<<"[TREE]";
    this->modelTreeUN->listItemUN;
    foreach(UnitNode* unit,modelTreeUN->listItemUN)
    {
        qDebug()<<"---------------------------------------------------------------------------";
        qDebug()<<"Name:  "<<unit->getName()
        <<"/Type:  "<<this->Type_from_int_to_string(unit->getType())
        <<"/Level: "<<unit->getLevel();
    }

}

void MainWindowCFG::get_option_SD_BL_IP(UnitNode *unit)
{

    int Num2=unit->getNum2();

    bool DK=false;
    if(unit->getDK())
       DK=true;
    int Bazalt=unit->getBazalt();
    int connectblock=unit->getConnectBlock();

    int UdpUse=unit->getUdpUse();

    QString UdpAdress=unit->getUdpAdress();

    int UdpPort=unit->getUdpPort();

    qDebug()<<"Name: "<<unit->getName()
            <<" Type:"<<this->Type_from_int_to_string(unit->getType())
            <<" Num2:"<<QString::number(unit->getNum2())
            <<" DK:"<<QString::number(unit->getDK())
            <<" Bazalt:"<<QString::number(unit->getBazalt())
            <<" connectblock:"<<QString::number(unit->getConnectBlock())
            <<" UdpUse:"<<QString::number(unit->getUdpUse())
            <<" UdpAdress:"<<unit->getUdpAdress();
/*
    qDebug()<<"Name: "<<Name
            <<" Type:"<<Type
            <<" Num2:"<<QString::number(Num2)
            <<" DK:"<<QString::number(DK)
            <<" Bazalt:"<<QString::number(Bazalt)
            <<" connectblock:"<<QString::number(connectblock)
            <<" UdpUse:"<<QString::number(UdpUse)
            <<" UdpAdress:"<<UdpAdress;
*/




    this->ui->CD_comboBox_Num2->setCurrentText(QString::number(unit->getNum2()));


    this->ui->CD_DK_checkBox->setChecked(DK);
    this->ui->CD_Bazalt_checkBox->setChecked(Bazalt);
    this->ui->CD_connectblock_checkBox->setChecked(connectblock);

}

void MainWindowCFG::get_option_IU_BL_IP(UnitNode *unit)
{

}

void MainWindowCFG::get_option_TG(UnitNode *unit)
{

}

void MainWindowCFG::get_option_RLM_KRL(UnitNode *unit)
{

}

void MainWindowCFG::get_option_RLM_C(UnitNode *unit)
{

}

void MainWindowCFG::get_option_BOD_T4K_M(UnitNode *unit)
{

}

void MainWindowCFG::get_option_Y4_T4K_M(UnitNode *unit)
{

}

void MainWindowCFG::get_option_DD_T4K_M(UnitNode *unit)
{

}

void MainWindowCFG::get_option_BOD_SOTA(UnitNode *unit)
{


this->ui->textEdit->clear();
QString string1;

string1.append("Тип: Сота/Сота-М ");

string1.append("Кан: ");

if(unit->getUdpUse()==0)
{
    string1.append(QString::number(unit->getNum3()));

    if(unit->getUdpAdress()!="")
    {

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
}



string1.append("БОД:");
string1.append(QString::number(unit->getNum1()));
this->ui->textEdit->append(string1);
qDebug()<<"[+]"<<string1;



}

void MainWindowCFG::get_option_Y4_SOTA(UnitNode *unit)
{

}

void MainWindowCFG::get_option_DD_SOTA(UnitNode *unit)
{

}

void MainWindowCFG::get_option_BL_IP(UnitNode *unit)
{

}

void MainWindowCFG::set_option_SD_BL_IP(UnitNode *unit)
{
    unit->setName(this->ui->uName_lineedit->text());
    unit->setNum2(this->ui->CD_comboBox_Num2->currentText().toInt());
    unit->setDK(this->ui->CD_DK_checkBox->isChecked()?1:0);
    unit->setBazalt(this->ui->CD_Bazalt_checkBox->isChecked()?1:0);
    unit->setConnectBlock(this->ui->CD_connectblock_checkBox->isChecked()?1:0);

    qDebug()<<"Name: "<<unit->getName()
            <<" Type:"<<this->Type_from_int_to_string(unit->getType())
            <<" Num2:"<<QString::number(unit->getNum2())
            <<" DK:"<<QString::number(unit->getDK())
            <<" Bazalt:"<<QString::number(unit->getBazalt())
            <<" connectblock:"<<QString::number(unit->getConnectBlock())
            <<" UdpUse:"<<QString::number(unit->getUdpUse())
            <<" UdpAdress:"<<unit->getUdpAdress();
}

void MainWindowCFG::set_option_IU_BL_IP(UnitNode *unit)
{

}

void MainWindowCFG::set_option_TG(UnitNode *unit)
{

}

void MainWindowCFG::set_option_RLM_KRL(UnitNode *unit)
{

}

void MainWindowCFG::set_option_RLM_C(UnitNode *unit)
{

}

void MainWindowCFG::set_option_BOD_T4K_M(UnitNode *unit)
{

}

void MainWindowCFG::set_option_Y4_T4K_M(UnitNode *unit)
{

}

void MainWindowCFG::set_option_DD_T4K_M(UnitNode *unit)
{

}

void MainWindowCFG::set_option_BOD_SOTA(UnitNode *unit)
{
qDebug()<<"set_option_BOD_SOTA";
unit->setNum1(this->ui->BOD_SOTA_M_adress_combobox->currentText().toInt());
unit->setNum3(this->ui->BOD_SOTA_M_port_combobox->currentText().toInt());

if(this->ui->BOD_SOTA_M_type_combobox->currentText()=="UDP")
    unit->setUdpUse(1);
else
    unit->setUdpUse(0);

unit->setUdpPort(this->ui->BOD_SOTA_MUdpPort_lineedit->text().toInt());
unit->setUdpAdress(this->ui->BOD_SOTA_M_ipadress_lineedit->text());
unit->setUdpTimeout(this->ui->BOD_SOTA_M_timeout_lineedit->text().toInt());
}

void MainWindowCFG::set_option_Y4_SOTA(UnitNode *unit)
{
unit->setNum2(this->ui->U4_Sota_M_combobox->currentText().toInt()*100);
}

void MainWindowCFG::set_option_DD_SOTA(UnitNode *unit,UnitNode *parent)
{
   int val=parent->getNum2()-100;


   unit->setNum2(this->ui->DD_Sota_M_combobox->currentText().toInt()+val-1);
//при добавлении ДД к участку к опции ДД добавляется
// 0 для участка 1
// 100 для участка 2
// 200 для участка 3
// 300 для участка 4

//Найти родителя

//Убедиться что это участок Сота-М

//Добавить значение как указано выше

}

void MainWindowCFG::set_option_BL_IP(UnitNode *unit)
{

}

void MainWindowCFG::save_ini(QString path)
{
    qDebug()<<"save ini";

    QSettings settings(path,QSettings::IniFormat);
    settings.setIniCodec( QTextCodec::codecForLocale() );
//   foreach(UnitNode* unit,this->modelTreeUN->listItemUN)
for(int i=1;i<this->modelTreeUN->listItemUN.count();i++)
    {
    UnitNode* unit=modelTreeUN->listItemUN.at(i);

        QString strGroup("Obj_%1");
        strGroup=strGroup.arg(i);

        settings.beginGroup(strGroup);
        settings.setValue("Name", unit->getName());
        settings.setValue("Type",unit->getType());
        settings.setValue("Level",unit->getLevel());

        this->save_option(&settings, unit);
        /*
        switch(unit->getType())
        {
 //save_option_SD_BL_IP(QSettings  settings,UnitNode*  unit);
        case TypeUnitNode::SD_BL_IP:
        this->save_option_SD_BL_IP(&settings, unit);
        break;

        case TypeUnitNode::IU_BL_IP:
    //    this->get_option_IU_BL_IP(unit);
        break;

        case TypeUnitNode::TG:
   //     this->get_option_TG(unit);
        break;

        case TypeUnitNode::RLM_KRL:
   //     this->get_option_RLM_KRL(unit);
        break;

        case TypeUnitNode::RLM_C:
   //     this->get_option_RLM_C(unit);
        break;

        case TypeUnitNode::BOD_T4K_M:
   //     this->get_option_BOD_T4K_M(unit);
        break;

        case TypeUnitNode::Y4_T4K_M:
   //     this->get_option_Y4_T4K_M(unit);
        break;

        case TypeUnitNode::DD_T4K_M:
   //     this->get_option_DD_T4K_M(unit);
        break;

        case TypeUnitNode::BOD_SOTA:
   //     this->get_option_BOD_SOTA(unit);
        break;

        case TypeUnitNode::Y4_SOTA:
   //     this->get_option_Y4_SOTA(unit);
        break;

        case TypeUnitNode::DD_SOTA:
        this->get_option_DD_SOTA(unit);
        break;

        case TypeUnitNode::BL_IP:
   //     this->get_option_BL_IP(unit);
        break;



        }
*/
        settings.setValue("X", unit->getX());
        settings.setValue("Y",unit->getY());

        settings.endGroup();

    }

    settings.beginGroup("TREE");
    settings.setValue("Count",this->modelTreeUN->listItemUN.count()-1);

    settings.endGroup();

}

void MainWindowCFG::save_option(QSettings *settings, UnitNode *unit)
{
    settings->setValue("Num1", QString::number(unit->getNum1()));
    settings->setValue("Num2", QString::number(unit->getNum2()));
    settings->setValue("Num3", QString::number(unit->getNum3()));

    settings->setValue("IconVisible", QString::number(unit->getIconVisible()));

     settings->setValue("X", QString::number(unit->getX()));
     settings->setValue("Y", QString::number(unit->getY()));

    settings->setValue("DK", QString::number(unit->getDK()));
    settings->setValue("Bazalt", QString::number(unit->getBazalt()));
    settings->setValue("Metka", QString::number(unit->getMetka()));

    settings->setValue("Razriv", QString::number(unit->getRazriv()));

    settings->setValue("AdamOff", QString::number(unit->getAdamOff()));
    settings->setValue("AlarmMsgOn", QString::number(unit->getAlarmMsgOn()));

    settings->setValue("ConnectBlock", QString::number(unit->getConnectBlock()));
    settings->setValue("OutType", QString::number(unit->getOutType()));
    settings->setValue("asoosd_kk", QString::number(unit->getAsoosd_kk()));
    settings->setValue("asoosd_nn", QString::number(unit->getAsoosd_nn()));

    settings->setValue("Description", unit->getDescription());

    settings->setValue("lan",QString::number(unit->getLan()));
    settings->setValue("lon", unit->getLon());

    settings->setValue("UdpUse", QString::number(unit->getUdpUse()));
    settings->setValue("UdpAdress", unit->getUdpAdress());

    settings->setValue("UpdPort", QString::number(unit->getUdpPort()));
    settings->setValue("UdpTimeout", QString::number(unit->getUdpTimeout()));
}

void MainWindowCFG::save_option_SD_BL_IP(QSettings* settings, UnitNode *unit)
{
          settings->setValue("Num2", QString::number(unit->getNum2()));
          settings->setValue("DK", QString::number(unit->getDK()));
          settings->setValue("Bazalt", QString::number(unit->getBazalt()));
          settings->setValue("connectblock", QString::number(unit->getConnectBlock()));
          settings->setValue("UdpUse", QString::number(unit->getUdpUse()));
          settings->setValue("UdpAdress", unit->getUdpAdress());


          /*
          qDebug()<<"Name: "<<unit->getName()
                  <<" Type:"<<this->Type_from_int_to_string(unit->getType())
                  <<" Num2:"<<QString::number(unit->getNum2())
                  <<" DK:"<<QString::number(unit->getDK())
                  <<" Bazalt:"<<QString::number(unit->getBazalt())
                  <<" connectblock:"<<QString::number(unit->getConnectBlock())
                  <<" UdpUse:"<<QString::number(unit->getUdpUse())
                  <<" UdpAdress:"<<unit->getUdpAdress();
          */
}

void MainWindowCFG::save_option_BOD_SOTA(QSettings *settings, UnitNode *unit)
{
    /*
    Type=29
    Num1=1
    Num2=0
    Num3=37
    Level=2
    Name=БЛ087 Сота: БОД1
    IconVisible=1
    X=40
    Y=40
    DK=1
    Bazalt=0
    Metka=0
    Razriv=0
    AdamOff=0
    AlarmMsgOn=0
    ConnectBlock=0
    OutType=0
    asoosd_kk=0
    asoosd_nn=0
    Description=
    lan=0
    lon=0
    UdpUse=0
    UdpAdress=192.168.0.87
    UpdPort=50
    UdpTimeout=50
    */
}



void MainWindowCFG::on_pushButton_2_clicked()
{
delete_unit();
}

void MainWindowCFG::on_pushButton_7_clicked()
{
    if(this->map.isVisible())
        this->map.hide();
    else
        this->map.show();
}



void MainWindowCFG::on_pushButton_8_clicked()
{
    show_the_tree();

}

void MainWindowCFG::on_BOD_SOTA_M_type_combobox_currentTextChanged(const QString &arg1)
{

    if(this->ui->BOD_SOTA_M_type_combobox->currentText()=="UDP")
     this->ui->BOD_UDP_RS485_stacked->setCurrentWidget(this->ui->BOD_UDP);
    else
     this->ui->BOD_UDP_RS485_stacked->setCurrentWidget(this->ui->BOD_RS485);

}
