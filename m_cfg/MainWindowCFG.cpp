#include "MainWindowCFG.h"
#include "ui_MainWindowCFG.h"

#include "QFileDialog"



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

    this->ui->UdpUse_checkBox->setVisible(false);
    this->ui->UdpUse_checkBox->setChecked(false);

    for(int i=1;i<100;i++)
    {
    this->ui->BOD_T4K_M_comboBox_Num1->addItem(QString::number(i));
    this->ui->Y4_T4K_M_comboBox_Num1->addItem(QString::number(i));
    this->ui->Y4_T4K_M_comboBox_Num2->addItem(QString::number(i));
    }


    connect(this->map.scene,SIGNAL(select(QString)),this,SLOT(select(QString)));

    connect(this->map.scene,SIGNAL(point(QString,int,int)),this,SLOT(set_x_y(QString,int,int)));
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

}


void MainWindowCFG::on_treeView_clicked(const QModelIndex &index)
{
    current_index=index;
    UnitNode *unit = static_cast<UnitNode*>(index.internalPointer());


this->get_option(unit);
}


void MainWindowCFG::get_option(UnitNode* unit)
{
    qDebug()<<"get option";

QString Name=unit->getName();

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


    this->ui->UdpUse_checkBox->setVisible(false);
    this->ui->UdpUse_checkBox->setChecked(false);
    this->ui->UpdPort_label->setVisible(false);
    this->ui->UdpAdress_label->setVisible(false);
    this->ui->UpdPort_lineEdit->setVisible(false);
    this->ui->UdpAdress_lineEdit->setVisible(false);
    this->ui->UpdPort_lineEdit->setText("");
    this->ui->UdpAdress_lineEdit->setText("");


    this->ui->IU_comboBox_Num2->setCurrentText("");


    this->ui->TG_comboBox_Num1->setCurrentText("");
    this->ui->TG_comboBox_Num2->setCurrentText("");
    this->ui->TG_UdpUse_checkBox->setChecked(false);

    int UdpUse=0;
    QString UdpAdress;
    int UdpPort;

        this->ui->uType_combobox->setCurrentText(Type);


    switch(selected_type)
    {
        case TypeUnitNode::SD_BL_IP:
        qDebug()<<"[!!!!!!!!!!!]";
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
    /*
    if(selected_type==TypeUnitNode::SD_BL_IP)
    {




    }
    else
    if(selected_type==TypeUnitNode::IU_BL_IP)
    {
        this->ui->uType_combobox->setCurrentText(Type);
        this->ui->UdpUse_checkBox->setVisible(true);
        int Num2=unit->getNum2();
        UdpUse=unit->getUdpUse();
        UdpAdress=unit->getUdpAdress();
        UdpPort=unit->getUdpPort();

        qDebug()<<"Name: "<<unit->getName()
                <<" Type:"<<this->Type_from_int_to_string(unit->getType())
                <<" Num2:"<<QString::number(unit->getNum2())
         //       <<" DK:"<<QString::number(unit->getDK())
         //       <<" Bazalt:"<<QString::number(unit->getBazalt())
         //       <<" connectblock:"<<QString::number(unit->getConnectBlock())
                <<" UdpUse:"<<QString::number(unit->getUdpUse())
                <<" UdpAdress:"<<unit->getUdpAdress();


        this->ui->uType_combobox->setCurrentText(Type);
        this->ui->IU_comboBox_Num2->setCurrentText(QString::number(Num2));
        this->ui->UdpUse_checkBox->setChecked(UdpUse);

    }
    if(selected_type==TypeUnitNode::TG)
    {
        this->ui->uType_combobox->setCurrentText(Type);
        this->ui->UdpUse_checkBox->setVisible(true);
        int Num1=unit->getNum1();
        int Num2=unit->getNum2();
        UdpUse=unit->getUdpUse();
        UdpAdress=unit->getUdpAdress();
        UdpPort=unit->getUdpPort();

        qDebug()<<"Name: "<<unit->getName()
                <<" Type:"<<this->Type_from_int_to_string(unit->getType())
                <<" Num1:"<<QString::number(unit->getNum1())
                <<" Num2:"<<QString::number(unit->getNum2())
         //       <<" DK:"<<QString::number(unit->getDK())
         //       <<" Bazalt:"<<QString::number(unit->getBazalt())
         //       <<" connectblock:"<<QString::number(unit->getConnectBlock())
                <<" UdpUse:"<<QString::number(unit->getUdpUse())
                <<" UdpAdress:"<<unit->getUdpAdress();

        this->ui->TG_comboBox_Num1->setCurrentText(QString::number(Num1));
        this->ui->TG_comboBox_Num2->setCurrentText(QString::number(Num2));
        this->ui->TG_UdpUse_checkBox->setChecked(UdpUse);
    }
    if(selected_type==TypeUnitNode::RLM_KRL)
    {
     this->ui->uType_combobox->setCurrentText(Type);
     this->ui->UdpUse_checkBox->setVisible(true);
     int Num1=unit->getNum1();

     bool DK=false;
     if(unit->getDK())
        DK=true;

     UdpUse=unit->getUdpUse();
     UdpAdress=unit->getUdpAdress();
     UdpPort=unit->getUdpPort();

     qDebug()<<"Name: "<<unit->getName()
             <<" Type:"<<this->Type_from_int_to_string(unit->getType())
             <<" Num1:"<<QString::number(unit->getNum1())
      //       <<" Num2:"<<QString::number(unit->getNum2())
             <<" DK:"<<QString::number(unit->getDK())
      //       <<" Bazalt:"<<QString::number(unit->getBazalt())
      //       <<" connectblock:"<<QString::number(unit->getConnectBlock())
             <<" UdpUse:"<<QString::number(unit->getUdpUse())
             <<" UdpAdress:"<<unit->getUdpAdress();

     this->ui->RLM_KRL_comboBox_Num1->setCurrentText(QString::number(Num1));

     this->ui->RLM_KRL_DK_checkBox->setChecked(DK);

     this->ui->UdpUse_checkBox->setChecked(UdpUse);

    }
    if(selected_type==TypeUnitNode::RLM_C)
    {
        this->ui->uType_combobox->setCurrentText(Type);
        this->ui->UdpUse_checkBox->setVisible(true);
        int Num1=unit->getNum1();
        bool DK=false;
        if(unit->getDK())
           DK=true;

        UdpUse=unit->getUdpUse();
        UdpAdress=unit->getUdpAdress();
        UdpPort=unit->getUdpPort();

        qDebug()<<"Name: "<<unit->getName()
                <<" Type:"<<this->Type_from_int_to_string(unit->getType())
                <<" Num1:"<<QString::number(unit->getNum1())
         //       <<" Num2:"<<QString::number(unit->getNum2())
                <<" DK:"<<QString::number(unit->getDK())
         //       <<" Bazalt:"<<QString::number(unit->getBazalt())
         //       <<" connectblock:"<<QString::number(unit->getConnectBlock())
                <<" UdpUse:"<<QString::number(unit->getUdpUse())
                <<" UdpAdress:"<<unit->getUdpAdress();


        this->ui->RLM_C_comboBox_Num1->setCurrentText(QString::number(Num1));

        this->ui->RLM_C_DK_checkBox->setChecked(DK);

        this->ui->UdpUse_checkBox->setChecked(UdpUse);

    }
    if(selected_type==TypeUnitNode::BOD_T4K_M)
    {
        this->ui->uType_combobox->setCurrentText(Type);
        this->ui->UdpUse_checkBox->setVisible(true);

        int Num1=unit->getNum1();

        qDebug()<<"Name: "<<unit->getName()
                <<" Type:"<<this->Type_from_int_to_string(unit->getType())
                <<" Num1:"<<QString::number(unit->getNum1())
         //       <<" Num2:"<<QString::number(unit->getNum2())
         //       <<" DK:"<<QString::number(unit->getDK())
         //       <<" Bazalt:"<<QString::number(unit->getBazalt())
         //       <<" connectblock:"<<QString::number(unit->getConnectBlock())
                <<" UdpUse:"<<QString::number(unit->getUdpUse())
                <<" UdpAdress:"<<unit->getUdpAdress();

        this->ui->BOD_T4K_M_comboBox_Num1->setCurrentText(QString::number(Num1));


        UdpUse=unit->getUdpUse();
        UdpAdress=unit->getUdpAdress();
        UdpPort=unit->getUdpPort();


    }
    if(selected_type==TypeUnitNode::Y4_T4K_M)
    {
        this->ui->uType_combobox->setCurrentText(Type);
        this->ui->UdpUse_checkBox->setVisible(true);

        int Num1=unit->getNum1();
        int Num2=unit->getNum2();

        qDebug()<<"Name: "<<unit->getName()
                <<" Type:"<<this->Type_from_int_to_string(unit->getType())
                <<" Num1:"<<QString::number(unit->getNum1())
                <<" Num2:"<<QString::number(unit->getNum2())
         //       <<" DK:"<<QString::number(unit->getDK())
         //       <<" Bazalt:"<<QString::number(unit->getBazalt())
         //       <<" connectblock:"<<QString::number(unit->getConnectBlock())
                <<" UdpUse:"<<QString::number(unit->getUdpUse())
                <<" UdpAdress:"<<unit->getUdpAdress();

        this->ui->Y4_T4K_M_comboBox_Num1->setCurrentText(QString::number(Num1));
        this->ui->Y4_T4K_M_comboBox_Num2->setCurrentText(QString::number(Num2));


        UdpUse=unit->getUdpUse();
        UdpAdress=unit->getUdpAdress();
        UdpPort=unit->getUdpPort();
    }
    if(UdpUse)
    {

    this->ui->UpdPort_label->setVisible(true);
    this->ui->UdpAdress_label->setVisible(true);
    this->ui->UpdPort_lineEdit->setVisible(true);
    this->ui->UdpAdress_lineEdit->setVisible(true);

    this->ui->UpdPort_lineEdit->setText(QString::number(UdpPort));
    this->ui->UdpAdress_lineEdit->setText(UdpAdress);
    }
 //   TG_groupbox

    qDebug()<<"Name: "<<Name
            <<" Type:"<<Type;

*/
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


    if(Type=="СД БЛ-IP")
        return TypeUnitNode::SD_BL_IP;
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
{int x=0;
    int y=0;
    foreach(UnitNode* un, this->modelTreeUN->listItemUN)
    {

       if(false==map.find(un->getName()))
       {
           map.Add(un->getName(),un->getPxm(),x,y);

           x=x+30;
           y=y+30;

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
    else
    this->ui->stackedWidget->setCurrentWidget(this->ui->Empty_space);


//Участок Точка-М/Гряда
//   БОД Точка-М/Гряда

    //РИФ-РЛМ-С

  //  РИФ-РЛМ/КРЛ/Трасса

}



void MainWindowCFG::on_pushButton_4_clicked()
{
   change_unit();



}

bool MainWindowCFG::set_option(UnitNode *unit)
{

/*
if(this_name_is_free(this->ui->uName_lineedit->text())==false)
{
    qDebug()<<"[ERROR]";
    return false;
}*/

    qDebug()<<"[PROFIT]";
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
  //     this->get_option_BOD_SOTA(unit);
       break;

       case TypeUnitNode::Y4_SOTA:
  //     this->get_option_Y4_SOTA(unit);
       break;
   /*
       case TypeUnitNode::DD_SOTA:
       this->get_option_DD_SOTA(unit);
       break;*/

       case TypeUnitNode::BL_IP:
  //     this->get_option_BL_IP(unit);
       break;



       }
return true;

}






void MainWindowCFG::on_actionCreate_triggered()
{
    qDebug()<<"[Create]";
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

    int type;
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

    UnitNode *unit=new UnitNode();
    unit->setName(this->ui->uName_lineedit->text());
    unit->setType(type);

    set_option(unit);

    QModelIndex index=this->ui->treeView->currentIndex();
    UnitNode *parrent = static_cast<UnitNode*>(index.internalPointer());
    unit->setLevel(parrent->getLevel()+1);


    //Проверить можно ли добавлять юнит к этому родителю
    //Определить тип родителя
    int parrent_type;

    //Определить тип чайлда
    int child_type;



    if (index.isValid())
    {
        if(can_i_add_or_not(parrent_type,child_type))
        if(this_name_is_free(unit->getName()))
            if(false==this->map.find(unit->getName()))
        {
      this->modelTreeUN->appendNewUNInStructure(index,unit);
        map.Add(unit->getName(),unit->getPxm(),unit->getX(),unit->getY());
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

    if(res==true)
    set_option(unit);
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
         if(un->getName()==unit->getName())
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
{
    qDebug()<<"[TREE]";
    this->modelTreeUN->listItemUN;
    foreach(UnitNode* unit,modelTreeUN->listItemUN)
    {
        qDebug()<<"-----------------";
        qDebug()<<"Name:  "<<unit->getName();
        qDebug()<<"Type:  "<<this->Type_from_int_to_string(unit->getType());
        qDebug()<<"Level: "<<unit->getLevel();
    }

}

void MainWindowCFG::get_option_SD_BL_IP(UnitNode *unit)
{
    this->ui->UdpUse_checkBox->setVisible(true);

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
    this->ui->UdpUse_checkBox->setChecked(UdpUse);

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
    unit->setUdpUse(this->ui->UdpUse_checkBox->isChecked()?1:0);
    unit->setUdpAdress(this->ui->UdpAdress_lineEdit->text());
    unit->setUdpPort(this->ui->UpdPort_lineEdit->text().toInt());

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

}

void MainWindowCFG::set_option_Y4_SOTA(UnitNode *unit)
{

}

void MainWindowCFG::set_option_DD_SOTA(UnitNode *unit)
{

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
    /*
        case TypeUnitNode::DD_SOTA:
        this->get_option_DD_SOTA(unit);
        break;*/

        case TypeUnitNode::BL_IP:
   //     this->get_option_BL_IP(unit);
        break;



        }

        settings.endGroup();

    }

    settings.beginGroup("TREE");
    settings.setValue("Count",this->modelTreeUN->listItemUN.count()-1);

    settings.endGroup();

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
