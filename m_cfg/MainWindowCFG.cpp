#include "MainWindowCFG.h"
#include "ui_MainWindowCFG.h"
#include <global.hpp>


#include "QFileDialog"
#include <QErrorMessage>
#include <QStorageInfo>
#include <QBrush>

#include <QCursor>
#include <QMouseEvent>

#include <QDateTime>
#include <QTimer>







//#include <libusb-1.0/libusb.h>

#if (defined (_WIN32) || defined (_WIN64))
#include <Windows.h>
#endif


MainWindowCFG::MainWindowCFG(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowCFG)
{



    ui->setupUi(this);

    QString str="QWERTY12345";
    QString crypts;
    QString res;
    crypts.append(XOR_Crypt(str));
    res.append(XOR_Crypt(crypts));
    qDebug()<<"crypts"<<crypts;
    qDebug()<<"res"<<res;



    this->ui->tabWidget->setCurrentIndex(0);
    /* Создаем строку для регулярного выражения */
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";


    QString str1="([0-1][0-9][0-9])";
    /* Создаем регулярное выражение с применением строки, как
     * повторяющегося элемента
     */
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    /* Создаем Валидатор регулярного выражения с применением
     * созданного регулярного выражения
     */
    ipValidator = new QRegExpValidator(ipRegex, this);
    /* Устанавливаем Валидатор на QLineEdit */

    this->ui->ipadress_lineedit->setValidator(ipValidator);
//    this->ui->ipadress_lineedit->setValidator( new QRegExpValidator( QRegExp( "[0-1][0-9][0-9]\\.[0-1][0-9][0-9]" ) ) );

//ui->ipadress_lineedit->setInputMask( "000.000.000.000" );

    this->ui->SQL_password_lineEdit->setEchoMode(QLineEdit::Password);

    ui->tableView->verticalHeader()->setVisible(false);
    rif_model = new rif_widget_model();
    this->ui->tableView->setModel(rif_model);
    rif_dlgt = new rif_widget_delegate();
    this->ui->tableView->setItemDelegate(rif_dlgt);





    this->setMouseTracking(true);
    this->ui->centralwidget->setMouseTracking(true);
//    this->ui->tabWidget->setMouseTracking(true);


    QString filepath="C:/Program Files/RIFx/rastrmtv_cfg.ini" ;
    QFileInfo info(this->ui->RASTR_wgt->rastrmtv_cfg__path());
    if(info.exists())
    {
        QSettings settings(filepath, QSettings::IniFormat);
      #if (defined (_WIN32) || defined (_WIN64))
          settings.setIniCodec( "Windows-1251" );
      #else
          settings.setIniCodec( "UTF-8" );
      #endif


          for(int index = 0; index < 4; index++)
          {
              QString strGroup("DEVICE_%1");
              strGroup = strGroup.arg(index);
              if(settings.childGroups().contains(strGroup))
              {
                  settings.beginGroup(strGroup);

                  QString SerNum = settings.value("SerNum","").toString();
                  QString Name = settings.value("Name","").toString();
                  if((SerNum!="")&&(Name!=""))
                  {
                      QString str;
                      str.clear();
                      str.append(Name);
                      str.append(" (");
                      str.append(SerNum);
                      str.append(")");
                      this->ui->RASTRMTV_Name_SerNum->addItem(str);
                      SerNum_Name snn;
                      snn.SerNum=SerNum;
                      snn.Name=Name;
                      mSerNum_Name.insert(str,snn);

                  }
                  settings.endGroup();
              }
          }
//Смотрим четыре группы DEVICE
//Смотрим параметр SerNum
//Если он не равен нулю
//Добавляем его в Combobox




    }
    else
    {

        QMessageBox::critical(0,"Ошибка","Файл rastrmtv_cfg.ini не найден");


        this->ui->RASTRMTV_Name_SerNum->addItem("не определено");
//        this->ui->Use->setCurrentIndex(0);
    }


for(int i=1;i<5;i++)
{
    this->ui->Y4_T4K_M_combobox->addItem(QString::number(i));
    this->ui->U4_Sota_M_combobox->addItem(QString::number(i));
}


for(int i=1;i<129;i++)
{
    QString str;
    str.clear();
    if(i/10<1)
        str.append("0");
    str.append(QString::number(i));
    this->ui->RASTRMTV_Num3->addItem(str);


}

//default_options();
   ui->tableWidget->verticalHeader()->setVisible(false);
//   ui->tableWidget_2->verticalHeader()->setVisible(false);

for(int i=1;i<5;i++)
{
    this->ui->SSOI_IU_Num1->addItem(QString::number(i));

    this->ui->SSOI_SD_Num1->addItem(QString::number(i));
}

for(int i=1;i<100;i++)
{
QString str;
str.clear();
if(i/10<1)
    str.append("0");
str.append(QString::number(i));
this->ui->SSOI_IU_Num2->addItem(str);
this->ui->SSOI_SD_Num2->addItem(str);

}

for(int i=0;i<8;i++)
{

this->ui->ADAM_Num2->addItem(QString::number(i));

}

for(int i=1;i<256;i++)
{
QString str;
str.clear();
if(i/10<1)
    str.append("0");
if(i/100<1)
    str.append("0");
str.append(QString::number(i));
this->ui->ADAM_Num1->addItem(str);


}

for(int i=1;i<100;i++)
{
QString str;
str.clear();
if(i/10<1)
    str.append("0");
if(i/100<1)
    str.append("0");
str.append(QString::number(i));
this->ui->TOROS_Num1->addItem(str);


}
for(int i=1;i<1000;i++)
{
    QString str;

  //  qDebug()<<"i/10 "<<QString::number(i/10)<<" i/100 "<<QString::number(i/100);

    if(i/10<1)
    {

            str.append("0");
    }

    if(i/100<1)
    {

        str.append("0");
    }

    str.append(QString::number(i));
    qDebug()<<str;
    this->ui->TABLO_Num2->addItem(str);
}

foreach(QString str, SSOI_IU_Num3)
{
    this->ui->SSOI_IU_Num3->addItem(str);

}


foreach(QString str, SSOI_SD_Num3)
{
    this->ui->SSOI_SD_Num3->addItem(str);

}

this->ui->stackedWidget_2->setCurrentWidget(this->ui->nothing);

    this->ui->SQL_server_lineEdit->setText("localhost");

    foreach(QString str, m_SSOI_SD_OutType)
    {
        this->ui->SSOI_SD_OutType->addItem(str);
    }



 /*   */

 /*
AnsiString str;

   char pwchar[255];
   for( int i = 0; i < 255; i++ ) pwchar[i] = 0;
   char dr[10];

   GetLogicalDriveStrings(255,pwchar);
   for( int i = 0; i < 255; i++ )
   {
      if( pwchar[i] == ':' )
      dr[0] = pwchar[i-1];
      dr[1] = pwchar[i];
      dr[2] = pwchar[i+1];
      dr[3] = pwchar[i+2];

      AnsiString str = dr;

      if( GetDriveType(dr) == DRIVE_REMOVABLE )

   */


    map_BACKUP_MaxBdStringCnt.insert(0,"1 000 000");
    map_BACKUP_MaxBdStringCnt.insert(1,"2 000 000");
    map_BACKUP_MaxBdStringCnt.insert(2,"3 000 000");
    map_BACKUP_MaxBdStringCnt.insert(3,"4 000 000");
    map_BACKUP_MaxBdStringCnt.insert(4,"5 000 000");
    map_BACKUP_MaxBdStringCnt.insert(5,"6 000 000");
    map_BACKUP_MaxBdStringCnt.insert(6,"7 000 000");
    map_BACKUP_MaxBdStringCnt.insert(7,"8 000 000");
    map_BACKUP_MaxBdStringCnt.insert(8,"9 000 000");
    map_BACKUP_MaxBdStringCnt.insert(9,"10 000 000");
    map_BACKUP_MaxBdStringCnt.insert(10,"-");

    foreach (QString str, map_BACKUP_MaxBdStringCnt)
    {
    this->ui->BACKUP_MaxBdStringCnt_comboBox->addItem(str);

    }


    map_INTEGRATION_Use.insert(0,"Выкл");
    map_INTEGRATION_Use.insert(1,"Вкл");
    foreach (QString str, map_INTEGRATION_Use)
    {
    this->ui->INTEGRATION_Use_comboBox->addItem(str);

    }


    map_PARAMS_AutoStart.insert(0,"Ручной");
    map_PARAMS_AutoStart.insert(1,"Автозагрузка");
    foreach (QString str, map_PARAMS_AutoStart)
    {
    this->ui->PARAMS_AutoStart_comboBox->addItem(str);

    }



 //   map_PARAMS_PlanType[0]="план";
 //   map_PARAMS_PlanType[1]="граф.модуль";
 //   map_PARAMS_PlanType[2]="не использовать";

    map_PARAMS_PlanType.insert(1," граф.модуль");
    map_PARAMS_PlanType.insert(2," не использовать");



     foreach (QString str, map_PARAMS_PlanType)
     {

     this->ui->PlanType_comboBox->addItem(str);
     }

 /*   for(int i=1;i<map_PARAMS_PlanType.count();i++)
    {
        this->ui->PlanType_comboBox->addItem(map_PARAMS_PlanType[i]);
    }
*/


    map_PARAMS_SoundType[0]=" звуковая карта";
    map_PARAMS_SoundType[1]=" системный динамик";
    map_PARAMS_SoundType[2]=" без звука";

    for(int i=0;i<map_PARAMS_SoundType.count();i++)
    {
        this->ui->SoundType_comboBox->addItem(map_PARAMS_SoundType[i]);
    }

   db_mysql = QSqlDatabase::addDatabase("QMYSQL");
   db_psql = QSqlDatabase::addDatabase("QPSQL");


   this->ui->SQL_server_lineEdit->setText("localhost");
//   this->ui->SQL_login_lineEdit->setText("root");
   this->ui->SQL_password_lineEdit->setText("123456");

   this->ui->SQL_login_lineEdit->setText("postgres");

//    this->ui->SQL_server_lineEdit->setReadOnly(true);
    this->ui->UDP_RS485_Widget->setVisible(false);



//  this->ui->RifPort_comboBox->addItem(" ВЫКЛ"," ВЫКЛ");

//   ComPort* port = new ComPort();
//   comports.append(port);



    default_RIF();





default_OPERATORS();

qSort(l_Unittype.begin(), l_Unittype.end(), [](const QVariant &v1,
                                               const QVariant &v2)
                                                            ->bool
                                                 {  return v1<v2;}
                                                                );


qDebug()<<"Unittype.indexOf(ГРУППА)"<<l_Unittype.indexOf(str_GROUP);
qDebug()<<"l_Unittype.count(ГРУППА);"<<l_Unittype.count(str_GROUP);
l_Unittype.move(l_Unittype.indexOf(str_GROUP),0);
l_Unittype.move(l_Unittype.indexOf(str_Y4_SOTA),(l_Unittype.indexOf(str_BOD_SOTA)+1));
l_Unittype.move(l_Unittype.indexOf(str_DD_SOTA),(l_Unittype.indexOf(str_BOD_SOTA)+2));
l_Unittype.move(l_Unittype.indexOf(str_Y4_T4K_M),(l_Unittype.indexOf(str_Y4_T4K_M)-1));
l_Unittype.move(l_Unittype.indexOf(str_Y4_T4K_M),(l_Unittype.indexOf(str_BOD_T4K_M)+1));
l_Unittype.move(l_Unittype.indexOf(str_DD_T4K_M),(l_Unittype.indexOf(str_BOD_T4K_M)+2));
foreach(QString str, l_Unittype)
{
this->ui->uType_combobox->addItem(str);
}


this->ui->RLM_KRL_type_comboBox->addItem(str_RIF_RLM);
this->ui->RLM_KRL_type_comboBox->addItem(str_RIF_RLM_24);
this->ui->RLM_KRL_type_comboBox->addItem(str_RIF_RLM_B);
this->ui->RLM_KRL_type_comboBox->addItem(str_RIF_KRL);
this->ui->RLM_KRL_type_comboBox->addItem(str_Razriv);
this->ui->RLM_KRL_type_comboBox->addItem(str_trassa1l);


  //  this->current_index=nullptr;


 //   QString patch="C:/WORK1/start7/rifx.ini";

    this->modelTreeUN = new TreeModelUnitNode(this);

    this->modelTreeUN->makeEmptyTree();

    modelTreeUN->setTypeApp(SubTypeApp::configurator);

    ui->treeView->setModel(this->modelTreeUN);

    Delegate* dlgt = new Delegate(this);
    this->ui->treeView->setItemDelegate(dlgt);

    ui->treeView->setColumnWidth(0,1000);
    ui->treeView->setColumnWidth(1,1000);
    ui->treeView->setColumnWidth(2,1000);




     ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
     menu = new QMenu(ui->treeView);
     menu->addAction("hello");
     menu->addAction("world");

 //   QString patch=QFileDialog::getOpenFileName(this, "open file","","*.ini");
 //    qDebug()<<"patch = "<<patch;
 //   this->modelTreeUN->loadSettings(patch);

    operators.clear();

     //    this->ui->tableWidget->insertRow(0);
     //    this->ui->tableWidget->insertRow(1);
     //    this->ui->tableWidget->insertRow(2);
     //    this->ui->tableWidget->insertRow(3);
     //    this->ui->tableWidget->insertRow(4);
     //    this->ui->tableWidget->insertRow(5);
    for(int i=1;i<256;i++)
        {


        this->ui->port_combobox->addItem(QString::number(i));


        }

    for(int i=1;i<101;i++)
    {

        this->ui->DD_Sota_M_combobox->addItem(QString::number(i));

    }

    for(int i=1;i<100;i++)
        {

        this->ui->RLM_KRL_adress_combobox->addItem(QString::number(i));
        this->ui->KL_adress_combobox->addItem(QString::number(i));
        this->ui->TG_adress_combobox->addItem(QString::number(i));
        this->ui->BOD_T4K_M_adress_combobox->addItem(QString::number(i));
        this->ui->BOD_SOTA_M_adress_combobox->addItem(QString::number(i));
        this->ui->RLM_C_adress_combobox->addItem(QString::number(i));

        }


     for(int i=1;i<27;i++)
        {

        this->ui->DD_T4K_M_combobox->addItem(QString::number(i));

        }





    connect(this->map.scene,SIGNAL(select(QString)),this,SLOT(select(QString)));

    connect(this->map.scene,SIGNAL(point(QString,int,int)),this,SLOT(set_x_y(QString,int,int)));

    this->ui->textEdit->clear();

    this->ui->stackedWidget->setCurrentWidget(this->ui->empty_space_groupbox);

    this->ui->tableWidget->setColumnWidth(0,10);
    this->ui->tableWidget->setColumnWidth(1,140);
    this->ui->tableWidget->setColumnWidth(2,130);
    this->ui->tableWidget->setColumnWidth(3,130);
    this->ui->tableWidget->setColumnWidth(4,130);
    this->ui->tableWidget->setColumnWidth(5,130);
    this->ui->tableWidget->setColumnWidth(6,130);
  //  this->ui->textEdit->setText("1111111\n 22222");

    this->ui->tableView->setColumnWidth(0,140);
    this->ui->tableView->setColumnWidth(1,190);
    this->ui->tableView->setColumnWidth(2,170);

 //   QMessageBox::critical(0,"Ошибка","Тестовый вывод сообщения");



    action_setDK = new QAction(tr("Выполнять команду ДК"), this);
    action_YZ_MONOLIT = new QAction(tr("УЗ Монолит"), this);
    action_setAlarmMsgOn  =new QAction(tr("Выдавать сообщение при тревогах"), this);

    action_open_device_tree = new QAction(tr("Развернуть дерево объектов"), this);
    action_close_device_tree = new QAction(tr("Свернуть дерево объектов"), this);
    action_open_edit_menu =  new QAction(tr("Редактировать"), this);

    action_setDK->setCheckable(true);
    action_YZ_MONOLIT->setCheckable(true);
    action_setAlarmMsgOn->setCheckable(true);

    action_setAdamOff_off = new QAction(tr("выкл"), this);
    action_setAdamOff_5_sec = new QAction(tr("5 сек"), this);
    action_setAdamOff_10_sec= new QAction(tr("10 сек"), this);
    action_setAdamOff_30_sec= new QAction(tr("30 сек"), this);
    action_setAdamOff_1_min= new QAction(tr("1 мин"), this);
    action_setAdamOff_5_min= new QAction(tr("5 мин"), this);
    action_setAdamOff_10_min= new QAction(tr("10 мин"), this);
    action_setAdamOff_20_min= new QAction(tr("20 мин"), this);
    action_setAdamOff_30_min= new QAction(tr("30 мин"), this);
    action_setAdamOff_1_hour= new QAction(tr("1 час"), this);

    action_setAdamOff_off->setCheckable(true);
    action_setAdamOff_5_sec->setCheckable(true);
    action_setAdamOff_10_sec->setCheckable(true);
    action_setAdamOff_30_sec->setCheckable(true);
    action_setAdamOff_1_min->setCheckable(true);
    action_setAdamOff_5_min->setCheckable(true);
    action_setAdamOff_10_min->setCheckable(true);
    action_setAdamOff_20_min->setCheckable(true);
    action_setAdamOff_30_min->setCheckable(true);
    action_setAdamOff_1_hour->setCheckable(true);




    menuAdamOff = new QMenu(menu);
    menuAdamOff->setTitle("Автовыключение");
    menuAdamOff->addAction(this->action_setAdamOff_off);
    menuAdamOff->addAction(this->action_setAdamOff_5_sec);
    menuAdamOff->addAction(this->action_setAdamOff_10_sec);
    menuAdamOff->addAction(this->action_setAdamOff_30_sec);
    menuAdamOff->addAction(this->action_setAdamOff_1_min);
    menuAdamOff->addAction(this->action_setAdamOff_10_min);
    menuAdamOff->addAction(this->action_setAdamOff_20_min);
    menuAdamOff->addAction(this->action_setAdamOff_30_min);
    menuAdamOff->addAction(this->action_setAdamOff_1_hour);




    menu->addMenu(menuAdamOff);


connect(&op_f, SIGNAL(res(QString,QString,QString,QString  )) , this, SLOT     (get_from_op_f(QString,QString,QString,QString))  );

connect (action_open_edit_menu, SIGNAL(triggered()  ) , this,SLOT     (open_edit_menu())  );

    connect (action_setDK, SIGNAL(triggered()  ) , this,SLOT     (setDK())  );
    connect (action_YZ_MONOLIT, SIGNAL(triggered()  ) , this,SLOT     (YZ_MONOLIT())  );
    connect (action_setAlarmMsgOn, SIGNAL(triggered()  ) , this,SLOT     (setAlarmMsgOn())  );

        connect (action_setAdamOff_off, SIGNAL(triggered()  ) , this,SLOT     (setAdamOff_off())  );
        connect (action_setAdamOff_5_sec, SIGNAL(triggered()  ) , this,SLOT     (setAdamOff_5_sec())  );
        connect (action_setAdamOff_10_sec, SIGNAL(triggered()  ) , this,SLOT     (setAdamOff_10_sec())  );
        connect (action_setAdamOff_30_sec, SIGNAL(triggered()  ) , this,SLOT     (setAdamOff_30_sec())  );
        connect (action_setAdamOff_1_min, SIGNAL(triggered()  ) , this,SLOT     (setAdamOff_1_min())  );
        connect (action_setAdamOff_10_min, SIGNAL(triggered()  ) , this,SLOT     (setAdamOff_10_min())  );
        connect (action_setAdamOff_20_min, SIGNAL(triggered()  ) , this,SLOT     (setAdamOff_20_min())  );
        connect (action_setAdamOff_30_min, SIGNAL(triggered()  ) , this,SLOT     (setAdamOff_30_min())  );
        connect (action_setAdamOff_1_hour, SIGNAL(triggered()  ) , this,SLOT     (setAdamOff_1_hour())  );

        connect (action_open_device_tree, SIGNAL(triggered()) , this, SLOT(open_device_tree()));
        connect (action_close_device_tree, SIGNAL(triggered()) , this, SLOT(close_device_tree()));

        connect(&this->db_f, SIGNAL(create_db(QString)  ) , this,SLOT     (create_db(QString)));
        connect(&this->db_f, SIGNAL(  drop_db(QString)  ) , this,SLOT     (  drop_db(QString)));
        connect(&this->db_f, SIGNAL(   use_db(QString)  ) , this,SLOT     (   use_db(QString)));

        timer = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
            timer->setInterval(10); // Задаем интервал таймера
            connect(timer, SIGNAL(timeout()), this, SLOT(update())); // Подключаем сигнал таймера к нашему слоту
            timer->start(); // Запускаем таймер

        this->on_actionCreate_triggered();
}

MainWindowCFG::~MainWindowCFG()
{
    delete ui;
}

bool MainWindowCFG::load(QString /*patch*/)
{
    bool res=true;






    return res;
}

void MainWindowCFG::unitNameChanged(QStandardItem */*item*/)
{
    qDebug()<<"[unitNameChanged]";
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

this->ui->pushButton_4->setDisabled(true);
    current_index=index;
    if(index.isValid())
    {
     this->ui->tabWidget->setCurrentIndex(2);

   //     this->ui->stackedWidget->setCurrentWidget()
        qDebug()<<"[+]";
    UnitNode *unit = static_cast<UnitNode*>(index.internalPointer());
  //  this->change_object_menu(unit->getType());
    this->object_menu_set_enabled_for_edit(false);
this->get_option(unit);
    }
    else
    {
   qDebug()<<"!!!";

    }

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
<<"; UdpTimeout "<<unit->getUdpTimeout()
<<"; Icon1Path "<<unit->getIcon1Path()
<<"; Icon2Path "<<unit->getIcon2Path()
<<"; Icon3Path "<<unit->getIcon3Path()
<<"; Icon4Path "<<unit->getIcon4Path();
;
    selected_type=unit->getType();

       this->ui->stackedWidget_2->setCurrentWidget(this->ui->nothing);
    switch(selected_type)
    {
    case TypeUnitNode::GROUP:
    this->get_option_GROUP(unit);
    break;

    case TypeUnitNode::SD_BL_IP:
    this->get_option_SD_BL_IP(unit);
//   coordinate_menu(true,true,unit->getLan(),unit->getLon(),unit->getDescription());
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

    case TypeUnitNode::DD_SOTA:
    this->get_option_DD_SOTA(unit);
    break;

    case TypeUnitNode::ONVIF:
    this->get_option_ONVIF(unit);
    break;

    case TypeUnitNode::NET_DEV:
    this->get_option_NET_DEV(unit);
    break;

    case TypeUnitNode::STRAZH_IP:
    this->get_option_STRAZH_IP(unit);
    break;

    case TypeUnitNode::BL_IP:
    this->get_option_BL_IP(unit);
    break;

    case TypeUnitNode::SSOI_SD:
    this->get_option_SSOI_SD(unit);
    break;

    case TypeUnitNode::SSOI_IU:
    this->get_option_SSOI_IU(unit);
    break;

    case TypeUnitNode::ADAM:
    this->get_option_ADAM(unit);
    break;

    case TypeUnitNode::TOROS:
    this->get_option_TOROS(unit);
    break;

    case TypeUnitNode::DEVLINE:
    this->get_option_DEVLINE(unit);
//    coordinate_devline(true,unit->getNum2(),unit->getNum3(),unit->getX(),unit->getY());
    break;

    case TypeUnitNode::RASTRMTV:
    this->get_option_RASTRMTV(unit);
    break;

    case TypeUnitNode::INFO_TABLO:
    this->get_option_INFO_TABLO(unit);
    break;

    }


}

void MainWindowCFG::get_option_GROUP(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);

    this->ui->textEdit->clear();
    QString string1;
    string1.append("Группа: ");
    string1.append(unit->getName());
    this->ui->textEdit->append(string1);
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

void MainWindowCFG::update_rif_comport_table()
{
/*

    ui->tableWidget_2->setRowCount(0);
  qDebug()<<"количество операторов "<<comports.count();
  int cnt;



for(int i=0;i<comports.count();i++)
{
        ComPort* port=comports.at(i);
   //    qDebug()<<" "<<i <<" "<<port->get_RifPortSpeed()<<" "<<port->get_RifPortInterval();

      cnt=this->ui->tableWidget_2->rowCount();
   //   qDebug()<<"/"<<cnt;
      this->ui->tableWidget_2->insertRow(cnt);

      this->ui->tableWidget_2->setItem(cnt,0, new QTableWidgetItem(QString::number(port->get_RifPortSpeed())));
      this->ui->tableWidget_2->item(cnt,0)->setFlags(this->ui->tableWidget_2->item(cnt,0)->flags() ^ Qt::ItemIsEditable);
      if(port->get_RifPortSpeed()!=4800)
      this->ui->tableWidget_2->item(cnt,0)->setBackground(Qt::green);

      this->ui->tableWidget_2->setItem(cnt,1, new QTableWidgetItem(QString::number(port->get_RifPortInterval())));
      this->ui->tableWidget_2->item(cnt,1)->setFlags(this->ui->tableWidget_2->item(cnt,1)->flags() ^ Qt::ItemIsEditable);
      if(port->get_RifPortInterval()!=50)
      this->ui->tableWidget_2->item(cnt,1)->setBackground(Qt::green);
}
*/
}

void MainWindowCFG::update()
{
    QPoint mouseLoc = QCursor::pos();

    this->ui->mouse_X->setText(QString::number(mouseLoc.x()));
    this->ui->mouse_Y->setText(QString::number(mouseLoc.y()));

    timer->start(10);
}















void MainWindowCFG::on_pushButton_4_clicked()
{
    qDebug()<<"rename_unit()";
    QModelIndex index=this->ui->treeView->currentIndex();
    if(index.isValid())
    {
        UnitNode* unit = static_cast<UnitNode*>(index.internalPointer());


    if(m_TypeUnitNode.key(this->ui->uType_combobox->currentText())==unit->getType())
    {
    qDebug()<<"[PRODIT]";
    unit->setName(this->ui->uName_lineedit->text());

    switch(unit->getType())
        {
        case TypeUnitNode::GROUP:

        break;

        case TypeUnitNode::SD_BL_IP:

        unit->setNum2(this->ui->SD_BL_IP_num_combobox->currentText().toInt());
        unit->setUdpAdress(this->ui->ipadress_lineedit->text());

        unit->setLan(this->ui->coordinate_X_doubleSpinBox->value());
        unit->setLon(this->ui->coordinate_Y_doubleSpinBox->value());
        unit->setDescription(ui->Dop_info_description_lineedit->text());

        break;
        }
    this->get_option(unit);

    }

    else
    {
    qDebug()<<"[FALSE]";

    }

    }

//   change_unit();

    this->ui->pushButton_4->setDisabled(true);

}

bool MainWindowCFG::set_option(UnitNode *unit, UnitNode* parent)
{

/*
if(this_name_is_free(this->ui->uName_lineedit->text())==false)
{
    qDebug()<<"[ERROR]";
    return false;
}*/

    //По умолчанию - если не является устройством, которое подключается по RS-485 к БЛ-IP
    //если является - то значение Num1 присвоится далее в одной из функций
    unit->setNum1(0);
    unit->setNum2(0);

    qDebug()<<"[set_option]";
int type=this->m_TypeUnitNode.key(this->ui->uType_combobox->currentText());
       switch(type)
       {

       case TypeUnitNode::SD_BL_IP:
       this->set_option_SD_BL_IP(unit);
       break;

       case TypeUnitNode::IU_BL_IP:
       this->set_option_IU_BL_IP(unit);
       break;

       case TypeUnitNode::TG:
       this->set_option_TG(unit);
       break;

       case TypeUnitNode::RLM_KRL:
       this->set_option_RLM_KRL(unit);
       break;

       case TypeUnitNode::RLM_C:
       this->set_option_RLM_C(unit);
       break;

       case TypeUnitNode::BOD_T4K_M:
       this->set_option_BOD_T4K_M(unit);
       break;

       case TypeUnitNode::Y4_T4K_M:
       this->set_option_Y4_T4K_M(unit,parent);
       break;

       case TypeUnitNode::DD_T4K_M:
       this->set_option_DD_T4K_M(unit,parent);
       break;

       case TypeUnitNode::BOD_SOTA:
       this->set_option_BOD_SOTA(unit);
       break;

       case TypeUnitNode::Y4_SOTA:
       this->set_option_Y4_SOTA(unit,parent);
       break;

       case TypeUnitNode::DD_SOTA:
       this->set_option_DD_SOTA(unit,parent);
       break;

       case TypeUnitNode::KL:
       this->set_option_KL(unit);
       break;/**/

       case TypeUnitNode::ONVIF:
       this->set_option_ONVIF(unit);
       break;/**/

       case TypeUnitNode::STRAZH_IP:
       this->set_option_STRAZH_IP(unit);
       break;/**/

       case TypeUnitNode::NET_DEV:
       this->set_option_NET_DEV(unit);
       break;/**/

       case TypeUnitNode::INFO_TABLO:
       this->set_option_INFO_TABLO(unit);
       break;/**/

       case TypeUnitNode::SSOI_IU:
       this->set_option_SSOI_IU(unit);
       break;/**/

       case TypeUnitNode::SSOI_SD:
       this->set_option_SSOI_SD(unit);
       break;/**/

       case TypeUnitNode::RASTRMTV:
       this->set_option_RASTRMTV(unit);
       break;/**/

       case TypeUnitNode::TOROS:
       this->set_option_TOROS(unit);
       break;/**/

       case TypeUnitNode::ADAM:
       this->set_option_ADAM(unit);
       break;/**/

       case TypeUnitNode::DEVLINE:
       this->set_option_DEVLINE(unit);
       break;/**/

       case TypeUnitNode::BL_IP:
  //     this->get_option_BL_IP(unit);
       break;






       }
return true;

}

void MainWindowCFG::set_option_GROUP(UnitNode */*unit*/)
{

}






void MainWindowCFG::on_actionCreate_triggered()
{
    default_options();


}

void MainWindowCFG::on_actionOpen_triggered()
{
     qDebug()<<"[Open]";

     QString patch=QFileDialog::getOpenFileName(this, "open file","","*.ini");
      qDebug()<<"patch = "<<patch;
      if(patch!="")
      {
          this->modelTreeUN->rootItemUN->deleteAll();
          this->modelTreeUN->loadSettings(patch);

          if(modelTreeUN->rowCount()==0)
          {
          this->modelTreeUN->makeEmptyTree();
          }

           this->default_OPERATORS();
           this->default_RIF();
           this->load_other_options_from_ini_file(patch);

           this->update_map();

      }

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

void MainWindowCFG::on_treeView_activated(const QModelIndex &/*index*/)
{
    qDebug()<<"activated";
}




void MainWindowCFG::operator_add(Operator * op)
{
   qDebug()<<"operator_add";
   operators.append(op);
   update_operators_table();
}

void MainWindowCFG::operator_edit(Operator *op)
{
   qDebug()<<"operator_edit";
   int row=this->ui->tableWidget->currentRow();
   Operator* true_op = operators.at(row);
   true_op->setFN(op->getFN());
   true_op->setN1(op->getN1());
   true_op->setN2(op->getN2());
   true_op->setPW(op->getPW());
   update_operators_table();



}

void MainWindowCFG::operator_delete()
{
   qDebug()<<"operator_delete";

}

QString MainWindowCFG::XOR_Crypt(QString src)
{
        qDebug()<<"[XOR_Crypt]";
    QByteArray ar=src.toLocal8Bit();
qDebug()<<"src "<<src;
QString key="start7";

    QByteArray pw=key.toLocal8Bit();

    qDebug()<<pw.size();
    QByteArray res;
    res.clear();
    for (int x=1;x<ar.size()+1;x++)
    {
    qDebug()<<"---"<<x<<"-------------";

           int val1=  pw[(x)%pw.size()] * 2;

         int inx=ar[x-1];
        qDebug()<<" val1 "<<val1<<"inx "<<inx;

         int val2= inx ^ val1;
         char chr = (char)val2;
         qDebug()<<chr;
 //         OutputDebugString(&in[x]);
 //         OutputDebugString(&pass[x%pass.Length()+1]);
 //         OutputDebugString(&chr);
 //          OutputDebugString("----------------");
 //      out +=  chr; /// ??????? * 2 ? ????? ?????????? ?????????
         res.append(chr);
    }
    QString str_res = QString::fromLocal8Bit(res);
    qDebug()<<"res "<<str_res;
return str_res;

}

void MainWindowCFG::update_operators_table()
{
      ui->tableWidget->setRowCount(0);
 //   qDebug()<<"количество операторов "<<operators.count();
    int cnt;
    foreach(Operator* op, operators)
    {

   //     qDebug()<<op->getN1()<<" "<<op->getN2()<<" "<<op->getFN();

        cnt=this->ui->tableWidget->rowCount();
        this->ui->tableWidget->insertRow(cnt);
        this->ui->tableWidget->setItem(cnt,0, new QTableWidgetItem(QString::number(cnt+1)));
        this->ui->tableWidget->setItem(cnt,1, new QTableWidgetItem(op->getFN()));
        this->ui->tableWidget->setItem(cnt,2, new QTableWidgetItem(op->getN1()));
        this->ui->tableWidget->setItem(cnt,3, new QTableWidgetItem(op->getN2()));

        if(op->getPW()!="")
        this->ui->tableWidget->setItem(cnt,4, new QTableWidgetItem("+"));

        this->ui->tableWidget->item(cnt,0)->setFlags(this->ui->tableWidget->item(cnt,0)->flags() ^ Qt::ItemIsEditable);
        this->ui->tableWidget->item(cnt,1)->setFlags(this->ui->tableWidget->item(cnt,1)->flags() ^ Qt::ItemIsEditable);
        this->ui->tableWidget->item(cnt,2)->setFlags(this->ui->tableWidget->item(cnt,2)->flags() ^ Qt::ItemIsEditable);
        this->ui->tableWidget->item(cnt,3)->setFlags(this->ui->tableWidget->item(cnt,3)->flags() ^ Qt::ItemIsEditable);

    }
}

QString MainWindowCFG::get_unit_name(int /*type*/)
{
    return QString();
}

bool MainWindowCFG::find_equal_unit(UnitNode *unit, bool (*is_equal)(UnitNode *unit, UnitNode *un))
{
    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
    foreach(UnitNode *un, List1 )
    {

        if(is_equal(unit,un))
        {
            this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
            QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");


            return false;
        }
    }

    return true;
}



void MainWindowCFG::setDK()
{
//    qDebug()<<"[!!!!!!!!!!!!!!!!!!!!!!]";
QModelIndex index = this->ui->treeView->currentIndex();
UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
qDebug()<<un->getName();

if(un->getDK()==0)
{

    qDebug()<<"[0]";
    un->setDK(true);
    qDebug()<<"[1]";
}
else
{
    qDebug()<<"[1]";
    un->setDK(false);
    qDebug()<<"[0]";
}


}

void MainWindowCFG::YZ_MONOLIT()
{

    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    qDebug()<<un->getName();

    qDebug()<<"YZ_MONOLIT()";
    if(un->getBazalt()==0)
    {

        qDebug()<<"[0]";
        un->setBazalt(true);
        qDebug()<<"[1]";
    }
    else
    {
        qDebug()<<"[1]";
        un->setBazalt(false);
        qDebug()<<"[0]";
    }
}

void MainWindowCFG::setAlarmMsgOn()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    qDebug()<<un->getName();

    qDebug()<<"YZ_MONOLIT()";
    if(un->getAlarmMsgOn()==0)
    {

        qDebug()<<"[0]";
        un->setAlarmMsgOn(true);
        qDebug()<<"[1]";
    }
    else
    {
        qDebug()<<"[1]";
        un->setAlarmMsgOn(false);
        qDebug()<<"[0]";
    }
}

void MainWindowCFG::setAdamOff()
{
    qDebug()<<QString::number(val_for_setAdamoff);
}

void MainWindowCFG::setAdamOff_off()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(0);
}

void MainWindowCFG::setAdamOff_5_sec()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(1);
}

void MainWindowCFG::setAdamOff_10_sec()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(2);
}

void MainWindowCFG::setAdamOff_30_sec()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(3);
}

void MainWindowCFG::setAdamOff_1_min()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(4);
}

void MainWindowCFG::setAdamOff_5_min()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(5);
}

void MainWindowCFG::setAdamOff_10_min()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(6);
}

void MainWindowCFG::setAdamOff_20_min()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(7);
}

void MainWindowCFG::setAdamOff_30_min()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(8);
}

void MainWindowCFG::setAdamOff_1_hour()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(9);
}

void MainWindowCFG::open_edit_menu()
{
    this->ui->tabWidget->setCurrentIndex(2);
    this->ui->pushButton_4->setEnabled(true);
    qDebug()<<"edit menu";

    QModelIndex index =this->ui->treeView->currentIndex();
    UnitNode *unit = static_cast<UnitNode*>(index.internalPointer());

    this->ui->uType_combobox->setCurrentText(this->m_TypeUnitNode.value(unit->getType()));

    this->object_menu_set_settings_from(unit);
    this->object_menu_set_enabled_for_edit(true);
   // unit_wgt.show();
    //имя
    //описание
    //айпи адрес. только если режим - 485.
    //координаты

}

void MainWindowCFG::open_device_tree()
{
  qDebug()<<"open";

  expandChildren(this->modelTreeUN->index(0,0,QModelIndex()));


}

void MainWindowCFG::close_device_tree()
{
  qDebug()<<"close";
   this->ui->treeView->collapse(this->modelTreeUN->index(0,0,QModelIndex()));
}

bool MainWindowCFG::can_i_add_or_not(int /*type_parrent*/, int /*type_child*/)
{
    return true;
}

bool MainWindowCFG::  pass_to_add(UnitNode *unit, UnitNode *parrent)
{


qDebug()<<"[can_i_add_or_not?]";

if(unit->getName()=="")
{
    QMessageBox::critical(0,"Ошибка","Введите имя устройства");

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

if(unit->getType()==TypeUnitNode::SD_BL_IP)
{
if(false==this->pass_to_add_SD_BL_IP(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::IU_BL_IP)
{
if(false==this->pass_to_add_IU_BL_IP(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::BOD_T4K_M)
{
if(false==pass_to_add_BOD_T4K_M(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::Y4_T4K_M)
{
if(false==pass_to_add_Y4_T4K_M(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::DD_T4K_M)
{
if(false==pass_to_add_DD_T4K_M(unit,parrent))
    return false;
}


if(unit->getType()==TypeUnitNode::TG)
{
if(false==pass_to_add_TG(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::RLM_KRL)
{
if(false==pass_to_add_RLM_KRL(unit,parrent))
    return false;
}


if(unit->getType()==TypeUnitNode::RLM_C)
{
if(false==pass_to_add_RLM_C(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::KL)
{
if(false==pass_to_add_KL(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::NET_DEV)
{
if(false==pass_to_add_NET_DEV(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::ONVIF)
{
if(false==pass_to_add_ONVIF(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::STRAZH_IP)
{
if(false==pass_to_add_STRAZH_IP(unit,parrent))
    return false;
}
if(unit->getType()==TypeUnitNode::GROUP)
{
if(false==pass_to_add_GROUP(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::GROUP)
{
if(false==pass_to_add_GROUP(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::GROUP)
{
if(false==pass_to_add_GROUP(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::GROUP)
{
if(false==pass_to_add_GROUP(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::GROUP)
{
if(false==pass_to_add_GROUP(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::GROUP)
{
if(false==pass_to_add_GROUP(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::DEVLINE)
{
if(false==pass_to_add_DEVLINE(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::INFO_TABLO)
{
if(false==pass_to_add_INFO_TABLO(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::SSOI_IU)
{
if(false==pass_to_add_SSOI_IU(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::SSOI_SD)
{
if(false==pass_to_add_SSOI_SD(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::RASTRMTV)
{
if(false==pass_to_add_RASTRMTV(unit,parrent))
    return false;
}

if(unit->getType()==TypeUnitNode::TOROS)
{
if(false==pass_to_add_TOROS(unit,parrent))
    return false;
}
//pass_to_add_SSOI_SD


if(unit->getType()==TypeUnitNode::GROUP)
{
if(false==pass_to_add_GROUP(unit,parrent))
    return false;
}
        return true;
}

        bool MainWindowCFG::pass_to_add_GROUP(UnitNode *unit, UnitNode *parrent)
{
        //группа может быть добавлена только к системе
            if((parrent->getType()!=TypeUnitNode::SYSTEM))
            {
        //        QMessageBox::critical(0,"Ошибка",("Груп к системе");
        //        dialog.exec();
                return false;

            }
        return true;
}

void MainWindowCFG::expandChildren(const QModelIndex &index)
        {
            if (!index.isValid()) {
                return;
            }

            int childCount = index.model()->rowCount(index);
            for (int i = 0; i < childCount; i++) {
                const QModelIndex &child = index.child(i, 0);
                // Recursively call the function for each child node.
                expandChildren(child);
            }

            this->ui->treeView->expand(index);

        }

void MainWindowCFG::collapseChildren(const QModelIndex &index)
        {
            if (!index.isValid()) {
                return;
            }

            int childCount = index.model()->rowCount(index);
            for (int i = 0; i < childCount; i++) {
                const QModelIndex &child = index.child(i, 0);
                // Recursively call the function for each child node.
                expandChildren(child);
            }

            this->ui->treeView->collapse(index);

}

void MainWindowCFG::change_object_menu(int type)
{
    switch(type)
    {

    case TypeUnitNode::GROUP:
    this->ui->stackedWidget->setCurrentWidget(this->ui->Group_groupbox);
    break;

    case TypeUnitNode::SD_BL_IP:
    qDebug()<<"[!!!!!!!!!!!!!!!!!!!!!!!!!!!CD!!!]";

    this->ui->stackedWidget->setCurrentWidget(this->ui->SD_BL_IP_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    this->ui->timeout_doubleSpinBox->setValue(50);
    coordinate_menu(true,false,0,0,"");
    break;

    case TypeUnitNode::IU_BL_IP:
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    this->ui->timeout_doubleSpinBox->setValue(50);
    this->ui->stackedWidget->setCurrentWidget(this->ui->IU_BL_IP_groupbox);
    break;

    case TypeUnitNode::TG:
    this->ui->stackedWidget->setCurrentWidget(this->ui->TG_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    this->ui->timeout_doubleSpinBox->setValue(75);
    coordinate_menu(true,false,0,0,"");
    break;

    case TypeUnitNode::RLM_KRL:
    this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_KRL_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    this->ui->timeout_doubleSpinBox->setValue(50);
    coordinate_menu(true,false,0,0,"");

    break;

    case TypeUnitNode::RLM_C:
    this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_C_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    this->ui->timeout_doubleSpinBox->setValue(50);
    coordinate_menu(true,false,0,0,"");
    break;

    case TypeUnitNode::BOD_T4K_M:
    this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_T4K_M_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    this->ui->timeout_doubleSpinBox->setValue(200);
    coordinate_menu(true,false,0,0,"");
    break;

    case TypeUnitNode::Y4_T4K_M:
    this->ui->stackedWidget->setCurrentWidget(this->ui->Y4_T4K_M_groupbox);
    break;

    case TypeUnitNode::DD_T4K_M:
    this->ui->stackedWidget->setCurrentWidget(this->ui->DD_T4K_M_groupbox);
    break;

    case TypeUnitNode::BOD_SOTA:

    this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_Sota_M_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    this->ui->timeout_doubleSpinBox->setValue(300);
    coordinate_menu(true,false,0,0,"");
    break;

    case TypeUnitNode::Y4_SOTA:

    this->ui->stackedWidget->setCurrentWidget(this->ui->U4_Sota_M_groupbox);
    break;

    case TypeUnitNode::DD_SOTA:
    this->ui->stackedWidget->setCurrentWidget(this->ui->DD_Sota_M_groupbox);
    break;

    case TypeUnitNode::KL:
    this->ui->stackedWidget->setCurrentWidget(this->ui->KL_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    this->ui->timeout_doubleSpinBox->setValue(50);
    coordinate_menu(true,false,0,0,"");
    break;

    case TypeUnitNode::ONVIF:
    this->ui->stackedWidget->setCurrentWidget(this->ui->ONVIF_groupbox);
    break;

    case TypeUnitNode::STRAZH_IP:
    this->ui->stackedWidget->setCurrentWidget(this->ui->STRAZH_IP_groupbox);
    break;

    case TypeUnitNode::NET_DEV:
    this->ui->stackedWidget->setCurrentWidget(this->ui->NET_DEV_groupbox);
    break;

    case TypeUnitNode::SSOI_SD:
    this->ui->stackedWidget->setCurrentWidget(this->ui->SSOI_SD_groupbox);
    break;

    case TypeUnitNode::SSOI_IU:
    this->ui->stackedWidget->setCurrentWidget(this->ui->SSOI_IU_groupbox);
    break;

    case TypeUnitNode::ADAM:
    this->ui->stackedWidget->setCurrentWidget(this->ui->ADAM_groupbox);
    break;

    case TypeUnitNode::TOROS:
    this->ui->stackedWidget->setCurrentWidget(this->ui->TOROS_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    this->ui->timeout_doubleSpinBox->setValue(50);
    coordinate_menu(true,false,0,0,"");
    break;

    case TypeUnitNode::DEVLINE:
    this->ui->stackedWidget->setCurrentWidget(this->ui->DEVLINE_groupbox);
    this->ui->stackedWidget_2->setCurrentWidget(this->ui->devline_coordinates);
    coordinate_devline(false,0,0,0,0);
    break;

    case TypeUnitNode::RASTRMTV:
    this->ui->stackedWidget->setCurrentWidget(this->ui->RASTRMTV_groupbox);
    break;

    case TypeUnitNode::INFO_TABLO:
    this->ui->stackedWidget->setCurrentWidget(this->ui->INFO_TABLO_groupbox);
    break;

    default:
        qDebug()<<"EMPTY";
    this->ui->stackedWidget->setCurrentWidget(this->ui->empty_space_groupbox);
    break;
    }

}

void MainWindowCFG::object_menu_set_settings_default(int type)
{
        this->ui->uName_lineedit->setText("");
qDebug()<<"[object_menu_set_settings_default]";

switch(type)
{
case TypeUnitNode::GROUP:

break;

case TypeUnitNode::SD_BL_IP:


this->ui->stackedWidget->setCurrentWidget(this->ui->SD_BL_IP_groupbox);
this->RS485_UDP_set_default_with_timeout(50);
this->ui->SD_BL_IP_num_combobox->setCurrentIndex(0);

coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::IU_BL_IP:
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(50);
this->ui->stackedWidget->setCurrentWidget(this->ui->IU_BL_IP_groupbox);
break;

case TypeUnitNode::TG:
this->ui->stackedWidget->setCurrentWidget(this->ui->TG_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(75);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::RLM_KRL:
this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_KRL_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(50);
coordinate_menu(true,false,0,0,"");

break;

case TypeUnitNode::RLM_C:
this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_C_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(50);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::BOD_T4K_M:
this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_T4K_M_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(200);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::Y4_T4K_M:
this->ui->stackedWidget->setCurrentWidget(this->ui->Y4_T4K_M_groupbox);
break;

case TypeUnitNode::DD_T4K_M:
this->ui->stackedWidget->setCurrentWidget(this->ui->DD_T4K_M_groupbox);
break;

case TypeUnitNode::BOD_SOTA:

this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_Sota_M_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(300);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::Y4_SOTA:

this->ui->stackedWidget->setCurrentWidget(this->ui->U4_Sota_M_groupbox);
break;

case TypeUnitNode::DD_SOTA:
this->ui->stackedWidget->setCurrentWidget(this->ui->DD_Sota_M_groupbox);
break;

case TypeUnitNode::KL:
this->ui->stackedWidget->setCurrentWidget(this->ui->KL_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(50);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::ONVIF:
this->ui->stackedWidget->setCurrentWidget(this->ui->ONVIF_groupbox);
break;

case TypeUnitNode::STRAZH_IP:
this->ui->stackedWidget->setCurrentWidget(this->ui->STRAZH_IP_groupbox);
break;

case TypeUnitNode::NET_DEV:
this->ui->stackedWidget->setCurrentWidget(this->ui->NET_DEV_groupbox);
break;

case TypeUnitNode::SSOI_SD:
this->ui->stackedWidget->setCurrentWidget(this->ui->SSOI_SD_groupbox);
break;

case TypeUnitNode::SSOI_IU:
this->ui->stackedWidget->setCurrentWidget(this->ui->SSOI_IU_groupbox);
break;

case TypeUnitNode::ADAM:
this->ui->stackedWidget->setCurrentWidget(this->ui->ADAM_groupbox);
break;

case TypeUnitNode::TOROS:
this->ui->stackedWidget->setCurrentWidget(this->ui->TOROS_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(50);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::DEVLINE:
this->ui->stackedWidget->setCurrentWidget(this->ui->DEVLINE_groupbox);
this->ui->stackedWidget_2->setCurrentWidget(this->ui->devline_coordinates);
coordinate_devline(false,0,0,0,0);
break;

case TypeUnitNode::RASTRMTV:
this->ui->stackedWidget->setCurrentWidget(this->ui->RASTRMTV_groupbox);
break;

case TypeUnitNode::INFO_TABLO:
this->ui->stackedWidget->setCurrentWidget(this->ui->INFO_TABLO_groupbox);
break;

default:
    qDebug()<<"EMPTY";
this->ui->stackedWidget->setCurrentWidget(this->ui->empty_space_groupbox);
break;
}
}

void MainWindowCFG::object_menu_set_settings_from(UnitNode *unit)
{

qDebug()<<"[object_menu_set_settings_from(UnitNode *unit)]";

qDebug()<<"[object_menu_set_settings_default]";
this->ui->uName_lineedit->setText(unit->getName());
switch(unit->getType())
{
case TypeUnitNode::GROUP:

break;

case TypeUnitNode::SD_BL_IP:

this->RS485_UDP_set_from_unit(unit);

this->ui->SD_BL_IP_num_combobox->setCurrentText(QString::number(unit->getNum2()));
this->ui->stackedWidget->setCurrentWidget(this->ui->SD_BL_IP_groupbox);

coordinate_menu(true,true,unit->getLan(),unit->getLon(),unit->getDescription());

break;

case TypeUnitNode::IU_BL_IP:
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(50);
this->ui->stackedWidget->setCurrentWidget(this->ui->IU_BL_IP_groupbox);
break;

case TypeUnitNode::TG:
this->ui->stackedWidget->setCurrentWidget(this->ui->TG_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(75);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::RLM_KRL:
this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_KRL_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(50);
coordinate_menu(true,false,0,0,"");

break;

case TypeUnitNode::RLM_C:
this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_C_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(50);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::BOD_T4K_M:
this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_T4K_M_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(200);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::Y4_T4K_M:
this->ui->stackedWidget->setCurrentWidget(this->ui->Y4_T4K_M_groupbox);
break;

case TypeUnitNode::DD_T4K_M:
this->ui->stackedWidget->setCurrentWidget(this->ui->DD_T4K_M_groupbox);
break;

case TypeUnitNode::BOD_SOTA:

this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_Sota_M_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(300);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::Y4_SOTA:

this->ui->stackedWidget->setCurrentWidget(this->ui->U4_Sota_M_groupbox);
break;

case TypeUnitNode::DD_SOTA:
this->ui->stackedWidget->setCurrentWidget(this->ui->DD_Sota_M_groupbox);
break;

case TypeUnitNode::KL:
this->ui->stackedWidget->setCurrentWidget(this->ui->KL_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(50);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::ONVIF:
this->ui->stackedWidget->setCurrentWidget(this->ui->ONVIF_groupbox);
break;

case TypeUnitNode::STRAZH_IP:
this->ui->stackedWidget->setCurrentWidget(this->ui->STRAZH_IP_groupbox);
break;

case TypeUnitNode::NET_DEV:
this->ui->stackedWidget->setCurrentWidget(this->ui->NET_DEV_groupbox);
break;

case TypeUnitNode::SSOI_SD:
this->ui->stackedWidget->setCurrentWidget(this->ui->SSOI_SD_groupbox);
break;

case TypeUnitNode::SSOI_IU:
this->ui->stackedWidget->setCurrentWidget(this->ui->SSOI_IU_groupbox);
break;

case TypeUnitNode::ADAM:
this->ui->stackedWidget->setCurrentWidget(this->ui->ADAM_groupbox);
break;

case TypeUnitNode::TOROS:
this->ui->stackedWidget->setCurrentWidget(this->ui->TOROS_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->timeout_doubleSpinBox->setValue(50);
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::DEVLINE:
this->ui->stackedWidget->setCurrentWidget(this->ui->DEVLINE_groupbox);
this->ui->stackedWidget_2->setCurrentWidget(this->ui->devline_coordinates);
coordinate_devline(false,0,0,0,0);
break;

case TypeUnitNode::RASTRMTV:
this->ui->stackedWidget->setCurrentWidget(this->ui->RASTRMTV_groupbox);
break;

case TypeUnitNode::INFO_TABLO:
this->ui->stackedWidget->setCurrentWidget(this->ui->INFO_TABLO_groupbox);
break;

default:
    qDebug()<<"EMPTY";
this->ui->stackedWidget->setCurrentWidget(this->ui->empty_space_groupbox);
break;
}
}

void MainWindowCFG::object_menu_set_enabled_for_edit(bool enable)
{
qDebug()<<"[object_menu_set_enabled_for_edit:"<<enable<<"]";

if(enable==true)
{
    this->ui->pushButton_4->setEnabled(true);

//    case TypeUnitNode::GROUP:
    this->ui->SD_BL_IP_num_combobox->setDisabled(true);
    RS485_UDP_set_enabled_for_edit(true);
//    break;
/*
    case TypeUnitNode::SD_BL_IP:


    break;

    case TypeUnitNode::IU_BL_IP:

    break;

    case TypeUnitNode::TG:

    break;

    case TypeUnitNode::RLM_KRL:

    break;

    case TypeUnitNode::RLM_C:

    break;

    case TypeUnitNode::BOD_T4K_M:

    break;

    case TypeUnitNode::Y4_T4K_M:

    break;

    case TypeUnitNode::DD_T4K_M:

    break;

    case TypeUnitNode::BOD_SOTA:

    break;

    case TypeUnitNode::Y4_SOTA:

    break;

    case TypeUnitNode::DD_SOTA:

    break;

    case TypeUnitNode::KL:

    break;

    case TypeUnitNode::ONVIF:

    break;

    case TypeUnitNode::STRAZH_IP:

    break;

    case TypeUnitNode::NET_DEV:

    break;

    case TypeUnitNode::SSOI_SD:

    break;

    case TypeUnitNode::SSOI_IU:

    break;

    case TypeUnitNode::ADAM:

    break;

    case TypeUnitNode::TOROS:

    break;

    case TypeUnitNode::DEVLINE:

    break;

    case TypeUnitNode::RASTRMTV:

    break;

    case TypeUnitNode::INFO_TABLO:

    break;

    default:

    break;
    */
 }

else
{
this->ui->pushButton_4->setDisabled(true);

//    case TypeUnitNode::GROUP:
this->ui->SD_BL_IP_num_combobox->setEnabled(true);
RS485_UDP_set_enabled_for_edit(false);
//    break;


}
}
void MainWindowCFG::RS485_UDP_set_default_with_timeout(int timeout)
{
qDebug()<<"[RS485_UDP_set_default_with_timeout(int timeout)]";
this->ui->stackedWidget->setCurrentWidget(this->ui->SD_BL_IP_groupbox);
this->ui->UDP_RS485_Widget->setVisible(true);
this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
this->ui->ipadress_lineedit->setText("");
this->ui->port_combobox->setCurrentIndex(0);
this->ui->UdpPort_doubleSpinBox->setValue(4001);
this->ui->timeout_doubleSpinBox->setValue(timeout);
}

void MainWindowCFG::RS485_UDP_set_from_unit(UnitNode *unit)
{

qDebug()<<"[RS485_UDP_set_from_unit(int timeout)]";

this->ui->UDP_RS485_Widget->setVisible(true);
if(unit->getUdpUse()==1)
    {
            this->ui->UDP_RS485_combobox->setCurrentText(" UDP");
    }

else
    {
            this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    }

this->ui->ipadress_lineedit->setText(unit->getUdpAdress());
this->ui->timeout_doubleSpinBox->setValue(unit->getUdpTimeout());
this->ui->port_combobox->setCurrentText(QString::number(unit->getNum3()));
this->ui->UdpPort_doubleSpinBox->setValue(unit->getUdpPort());

}

void MainWindowCFG::RS485_UDP_set_enabled_for_edit(bool enable)
{
qDebug()<<"[RS485_UDP_set_enabled_for_edit:"<<enable<<"]";
if(enable==true)
{
    qDebug()<<"[RS485_UDP_set_from_unit(int timeout)]";

    this->ui->UDP_RS485_Widget->setVisible(true);
    if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
        {
          this->ui->ipadress_lineedit->setDisabled(true);
        }

    else
        {
          this->ui->ipadress_lineedit->setEnabled(true);
        }


    this->ui->timeout_doubleSpinBox->setDisabled(true);
    this->ui->port_combobox->setDisabled(true);
    this->ui->UdpPort_doubleSpinBox->setDisabled(true);
    this->ui->UDP_RS485_combobox->setDisabled(true);
}
else
{

    this->ui->UDP_RS485_combobox->setEnabled(true);
    this->ui->ipadress_lineedit->setEnabled(true);
    this->ui->timeout_doubleSpinBox->setEnabled(true);
    this->ui->port_combobox->setEnabled(true);
    this->ui->UdpPort_doubleSpinBox->setEnabled(true);
}
}

bool MainWindowCFG::pass_to_add_SD_BL_IP(UnitNode *unit, UnitNode *parrent)
{
    //СД может быть добавлен только к группе или к системе
        if((parrent->getType()!=TypeUnitNode::GROUP)&&(parrent->getType()!=TypeUnitNode::SYSTEM))
        {

            QMessageBox::critical(0,"Ошибка","СД может быть добавлен только к группе или к системе");

            return false;

        }
   //Num2 от нуля до восьми
    if(unit->getNum2()<0||unit->getNum2()>8)
        return false;

    //Если выбран RS-485
    if(unit->getUdpUse()==0)
    {
        qDebug()<<"[RS485]";
        //Контролируем отсутствие юнита с таким же Num2 и Num3

           QList<UnitNode *> List1;
           this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
           foreach(UnitNode *un, List1 )
           {
            if(un->getType()==unit->getType())
            if(un->getUdpUse()==unit->getUdpUse())
            if(un->getNum3()==unit->getNum3())
            if(un->getNum2()==unit->getNum2())
            {
       //         this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

                return false;
            }
           }

    }

    //Если выбран UDP
        if(unit->getUdpUse()==1)
        {
                    qDebug()<<"[UDP]";
         //Контролируем отсутствие юнита с таким же Num2 и Num3

               QList<UnitNode *> List1;
               this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
               foreach(UnitNode *un, List1 )
            {
                   if(un->getType()==unit->getType())
                   if(un->getUdpUse()==unit->getUdpUse())
                   if(un->getUdpAdress()==unit->getUdpAdress())
                   if(un->getNum2()==unit->getNum2())
             {
               //  this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                 this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                       QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

                 return false;
             }
            }
         }




        //Находим все СД с таким же UdpAdress
        //Контролируем отсутствие юнита с таким же Num2 и UdpAdress
        return true;
}

bool MainWindowCFG::pass_to_add_IU_BL_IP(UnitNode *unit, UnitNode *parrent)
{
  /*
    //ИУ может быть добавлен только к группе или к системе
if(
    (parrent->getType()!=TypeUnitNode::SYSTEM)&&
    (parrent->getType()!=TypeUnitNode::GROUP)&&
    (parrent->getType()!=TypeUnitNode::KL)&&
    (parrent->getType()!=TypeUnitNode::SD_BL_IP)&&
//    (parrent->getType()!=TypeUnitNode::IU_BL_IP)&&
    (parrent->getType()!=TypeUnitNode::TG)&&
    (parrent->getType()!=TypeUnitNode::RLM_KRL)&&
    (parrent->getType()!=TypeUnitNode::RLM_C)&&
//    (parrent->getType()!=TypeUnitNode::STRAZH_IP)&&
//    (parrent->getType()!=TypeUnitNode::ONVIF)&&
//    (parrent->getType()!=TypeUnitNode::BOD_T4K_M)&&
//    (parrent->getType()!=TypeUnitNode::Y4_T4K_M)&&
    (parrent->getType()!=TypeUnitNode::DD_T4K_M)&&
//    (parrent->getType()!=TypeUnitNode::BOD_SOTA)&&
//    (parrent->getType()!=TypeUnitNode::Y4_SOTA)&&
    (parrent->getType()!=TypeUnitNode::DD_SOTA)&&
//    (parrent->getType()!=TypeUnitNode::NET_DEV)&&
//    (parrent->getType()!=TypeUnitNode::BL_IP)&&
    (parrent->getType()!=TypeUnitNode::SSOI_SD)&&
//    (parrent->getType()!=TypeUnitNode::SSOI_IU)&&
    (parrent->getType()!=TypeUnitNode::ADAM)&&
    (parrent->getType()!=TypeUnitNode::TOROS)
//    (parrent->getType()!=TypeUnitNode::DEVLINE)&&
//    (parrent->getType()!=TypeUnitNode::RASTRMTV)&&
//    (parrent->getType()!=TypeUnitNode::INFO_TABLO)

)*/
    //может быть добавлен к любому датчику группе системе сморти ссои конфигуратор
    if((parrent->getType()==TypeUnitNode::STRAZH_IP)||
       (parrent->getType()==TypeUnitNode::ONVIF)||
       (parrent->getType()==TypeUnitNode::DEVLINE)||
       (parrent->getType()==TypeUnitNode::RASTRMTV)||
       (parrent->getType()==TypeUnitNode::INFO_TABLO)||
       (parrent->getType()==TypeUnitNode::SSOI_IU) ||
       (parrent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }



        //Num2 от нуля до четырех
         if(unit->getNum2()<0||unit->getNum2()>4)

             return false;

         QModelIndex ind = this->modelTreeUN->findeIndexUN(parrent);

         //Если выбран RS-485
         if(unit->getUdpUse()==0)
         {
             qDebug()<<"[RS485]";
             //Контролируем отсутствие юнита с таким же Num2 и Num3 у одного и того же родителя

                QList<UnitNode *> List1;
                this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
                foreach(UnitNode *un, List1 )
                {
                QModelIndex index=this->modelTreeUN->findeIndexUN(un);
                QModelIndex un_parent_index= this->modelTreeUN->parent(index);

                 if(ind==un_parent_index)
                 if(un->getType()==unit->getType())
                 if(un->getUdpUse()==unit->getUdpUse())
                 if(un->getNum3()==unit->getNum3())
                 if(un->getNum2()==unit->getNum2())
                 {
                     this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                     QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

                     return false;
                 }
                }

         }

         //Если выбран UDP
             if(unit->getUdpUse()==1)
             {
                         qDebug()<<"[UDP]";
              //Контролируем отсутствие юнита с таким же Num2 и Num3

                    QList<UnitNode *> List1;
                    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
                    foreach(UnitNode *un, List1 )
                 {
                        QModelIndex index=this->modelTreeUN->findeIndexUN(un);
                        QModelIndex un_parent_index= this->modelTreeUN->parent(index);

                        if(ind==un_parent_index)
                        if(un->getType()==unit->getType())
                        if(un->getUdpUse()==unit->getUdpUse())
                        if(un->getUdpAdress()==unit->getUdpAdress())
                        if(un->getNum2()==unit->getNum2())
                  {

                      this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                            QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

                      return false;
                  }
                 }
              }

        return true;

}

bool MainWindowCFG::pass_to_add_BOD_SOTA(UnitNode *unit, UnitNode *parrent)
{
    //БОД может быть добавлен только к группе
        if((parrent->getType()!=TypeUnitNode::GROUP)&&
           (parrent->getType()!=TypeUnitNode::SYSTEM)
                )
        {
            QMessageBox::critical(0,"Ошибка","БОД может быть добавлен только к группе");

            return false;

        }

    //    Если связь по RS485 - контроль по RS485 порту
    //    Если связь по UDP - контроль по IP адресу

     //     qDebug()<<"[BOD_SOTA]";




            if(unit->getUdpUse()==0)
                return find_equal_unit(unit,[](UnitNode *unit, UnitNode *un)
                                              ->bool
                                   {

                                    return ((un->getNum3()==unit->getNum3())&&
                                            (un->getNum1()==unit->getNum1()));
                                    }
                                                  );




            if(unit->getUdpUse()==1)

                return find_equal_unit(unit,[](UnitNode *unit, UnitNode *un)->bool
                                   {
                                    return ((un->getUdpAdress()==unit->getUdpAdress())&&
                                            (un->getNum1()==unit->getNum1()));
                                   }
                                );



            return true;
}

bool MainWindowCFG::pass_to_add_Y4_SOTA(UnitNode *unit, UnitNode *parrent)
{
    qDebug()<<"[pass_to_add_Y4_SOTA]";
    //Участок может быть добавлен только к БОД Сота/Сота-М
    if(parrent->getType()!=TypeUnitNode::BOD_SOTA)
    {
        QMessageBox::critical(0,"Ошибка","Участок может быть добавлен только к БОД Сота/Сота-М!");

        return false;

    }

    //В одном БОД Сота/Сота-М не должно быть "участков" с двумя одинаковыми участками

    //Составить лист участков этого БОДА
    QList<UnitNode*> List;

    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
    foreach(UnitNode *un, List1 )
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
         this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
         QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
         return false;
     }
    }
    //проконтролировать в нем отсутствие добавляемого участка

    return true;
}

bool MainWindowCFG::pass_to_add_DD_SOTA(UnitNode *unit, UnitNode *parrent) //номера ДД можно добавлять только один раз в участки 1-2 и 3-4
{
    //добавлять только к участку Сота
    if(parrent->getType()!=TypeUnitNode::Y4_SOTA)
    {
        QMessageBox::critical(0,"Ошибка","ДД может быть добавлен только к участку !");
        return false;

    }

    //В одном боде нет 2х одинаковых ДД

    //Формируем список всех ДД этого БОДа

    //Сравниваем ДД с добавляемым

    QList<UnitNode*> List;

    //Ищем нужный БОД. Это родитель родителя.

    QModelIndex ind = this->modelTreeUN->findeIndexUN(parrent);
    QModelIndex BOD_ind = this->modelTreeUN->parent(ind);
//    UnitNode* BOD=static_cast<UnitNode*>(BOD_ind.internalPointer());



    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);

    foreach(UnitNode *un, List1 )
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

    //номер ДД

    //его индекс


    int m_val = unit->getNum2()-parrent->getNum2();

    qDebug()<<QString::number(m_val);

    foreach(UnitNode *un, List )
    {
    qDebug()<<"Name: "<<un->getName();

    //номер ДД

    //его индекс
    QModelIndex ind = this->modelTreeUN->findeIndexUN(un);
    //индекс его родителя
    QModelIndex parent_ind =  this->modelTreeUN->parent(ind);
    //юнит его родителя
    UnitNode *parent = static_cast<UnitNode*>(parent_ind.internalPointer());

    qDebug()<<"Name: "<<un->getName()<<" участок "<<QString::number(parent->getNum2());

    if((100==parrent->getNum2())||((200==parrent->getNum2())))
        {
            if((100==parent->getNum2())||((200==parent->getNum2())))
            {
                int val = un->getNum2()-parent->getNum2();
                 qDebug()<<QString::number(m_val)<<" "<<QString::number(val);
                if(m_val==val)
                {


                    this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                    QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

                    return false;
                }
            }
        }
    if((300==parrent->getNum2())||((400==parrent->getNum2())))
        {
            if((300==parent->getNum2())||((400==parent->getNum2())))
            {
                int val = un->getNum2()-parent->getNum2();
                 qDebug()<<QString::number(m_val)<<" "<<QString::number(val);
                if(m_val==val)
                {


                    this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                    QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                    return false;
                }
            }
        }

    }



    return true;
}

bool MainWindowCFG::pass_to_add_BOD_T4K_M(UnitNode *unit, UnitNode *parrent)
{
    //БОД может быть добавлен только к группе
    if((parrent->getType()!=TypeUnitNode::GROUP)&&
       (parrent->getType()!=TypeUnitNode::SYSTEM)
            )
        {
            QMessageBox::critical(0,"Ошибка","БОД может быть добавлен только к группе");
            return false;

        }

    //    Если связь по RS485 - контроль по RS485 порту
    //    Если связь по UDP - контроль по IP адресу


            if(unit->getUdpUse()==0)
            {
          //            qDebug()<<"[getUdpUse()==0]";
                QList<UnitNode *> List1;
                this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
                foreach(UnitNode *un, List1 )
                {

            qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
                 if((un->getNum3()==unit->getNum3()))
                 if((un->getNum1()==unit->getNum1()))
                 {

                     this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                     QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                     return false;
                 }


                }
             //проконтроилровать отсутствие в дереве такого же порта

            }

            if(unit->getUdpUse()==1)
            {
              //проконтроилровать отсутствие в дереве такого же IP адреса
                QList<UnitNode *> List1;
                this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
                foreach(UnitNode *un, List1 )
                {
       //     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
                 if((un->getUdpAdress()==unit->getUdpAdress()))
                 if((un->getNum1()==unit->getNum1()))
                  {

                     QMessageBox::critical(0,"Ошибка","этот IP адрес уже  занят");
                     return false;
                  }
                }
            }
            return true;


}

bool MainWindowCFG::pass_to_add_Y4_T4K_M(UnitNode *unit, UnitNode *parrent)
{

    //Участок может быть добавлен только к БОД
    if(parrent->getType()!=TypeUnitNode::BOD_T4K_M)
    {
        QMessageBox::critical(0,"Ошибка","Участок может быть добавлен только к БОД Точка-М/Гарда-М !");
        return false;

    }

    //В одном БОД  не должно быть "участков" с двумя одинаковыми участками

    //Составить лист участков этого БОДА
    QList<UnitNode*> List;

    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
    foreach(UnitNode *un, List1 )
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
         this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
         QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

         return false;
     }
    }
    //проконтролировать в нем отсутствие добавляемого участка

    return true;

}

bool MainWindowCFG::pass_to_add_DD_T4K_M(UnitNode *unit, UnitNode *parrent)//номера ДД можно добавлять только один раз в участки 1-2 и 3-4
{
    //добавлять только к участку Сота
    if(parrent->getType()!=TypeUnitNode::Y4_T4K_M)
    {
        QMessageBox::critical(0,"Ошибка","ДД может быть добавлен только к участку !");
        return false;

    }

    //В одном боде нет 2х одинаковых ДД

    //Формируем список всех ДД этого БОДа

    //Сравниваем ДД с добавляемым

    QList<UnitNode*> List;

    //Ищем нужный БОД. Это родитель родителя.

    QModelIndex ind = this->modelTreeUN->findeIndexUN(parrent);
    QModelIndex BOD_ind = this->modelTreeUN->parent(ind);
//    UnitNode* BOD=static_cast<UnitNode*>(BOD_ind.internalPointer());



    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);

    foreach(UnitNode *un, List1 )
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

    int m_val = unit->getNum2()-parrent->getNum2();

    qDebug()<<QString::number(m_val);

    foreach(UnitNode *un, List )
    {
    qDebug()<<"Name: "<<un->getName();

    //номер ДД

    //его индекс
    QModelIndex ind = this->modelTreeUN->findeIndexUN(un);
    //индекс его родителя
    QModelIndex parent_ind =  this->modelTreeUN->parent(ind);
    //юнит его родителя
    UnitNode *parent = static_cast<UnitNode*>(parent_ind.internalPointer());

    qDebug()<<"Name: "<<un->getName()<<" участок "<<QString::number(parent->getNum2());

    if((100==parrent->getNum2())||((200==parrent->getNum2())))
        {
            if((100==parent->getNum2())||((200==parent->getNum2())))
            {
                int val = un->getNum2()-parent->getNum2();
                 qDebug()<<QString::number(m_val)<<" "<<QString::number(val);
                if(m_val==val)
                {


                    this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                    QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                    return false;
                }
            }
        }
    if((300==parrent->getNum2())||((400==parrent->getNum2())))
        {
            if((300==parent->getNum2())||((400==parent->getNum2())))
            {
                int val = un->getNum2()-parent->getNum2();
                 qDebug()<<QString::number(m_val)<<" "<<QString::number(val);
                if(m_val==val)
                {


                    this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                    QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                    return false;
                }
            }
        }

    }
    return true;
}

bool MainWindowCFG::pass_to_add_TG(UnitNode *unit, UnitNode *parrent)
{

   //ЧЭ от одного до четырех
     if(unit->getNum2()<0||unit->getNum2()>4)
     {
         QMessageBox::critical(0,"Ошибка","ЧЭ от одного до четырех !");
         return false;

     }
   //только к группе
    if(parrent->getType()!=TypeUnitNode::GROUP)
    {
        QMessageBox::critical(0,"Ошибка","устройство Точка/Гарда может быть добавлено только к группе !");
        return false;

    }

    //на свободный адрес этого ком порта
    if(unit->getUdpUse()==0)
    {
  //            qDebug()<<"[getUdpUse()==0]";
        QList<UnitNode *> List1;
        this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
        foreach(UnitNode *un, List1 )
        {

    qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
         if((un->getNum3()==unit->getNum3()))
             if((un->getNum1()==unit->getNum1()))
             {
                 if(un->getType()!=unit->getType())//если другое устройство (не ЧЭ) на этом адресе этого порта
                  {

                     this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                     QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                     return false;
                  }
                 if(un->getType()==unit->getType()) //если на этом адресе этого порта есть ЧЭ - проверить на номер ЧЭ
                  {
                     if(un->getNum2()==unit->getNum2())
                     {
                         this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                         QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                         return false;

                     }

                  }

             }


        }
     //проконтроилровать отсутствие в дереве такого же порта

    }

    if(unit->getUdpUse()==1)
    {
      //проконтроилровать отсутствие в дереве такого же IP адреса
        QList<UnitNode *> List1;
        this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
        foreach(UnitNode *un, List1 )
        {
//     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
         if((un->getUdpAdress()==unit->getUdpAdress()))
         if((un->getNum1()==unit->getNum1()))
         {
             if(un->getType()!=unit->getType())//если другое устройство (не ЧЭ) на этом адресе этого порта
              {

                 this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                 QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                 return false;
              }
             if(un->getType()==unit->getType()) //если на этом адресе этого порта есть ЧЭ - проверить на номер ЧЭ
              {
                 if(un->getNum2()==unit->getNum2())
                 {
                     this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                     QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

                     return false;

                 }

              }

         }

        }
    }

    return true;
}

bool MainWindowCFG::pass_to_add_RLM_KRL(UnitNode *unit, UnitNode *parrent)
{
    // может быть добавлен только к группе
        if(parrent->getType()!=TypeUnitNode::GROUP)
        if(parrent->getType()!=TypeUnitNode::SYSTEM)
        {
            QMessageBox::critical(0,"Ошибка"," может быть добавлен только к группе");
            return false;

        }

    //    Если связь по RS485 - контроль по RS485 порту
    //    Если связь по UDP - контроль по IP адресу


            if(unit->getUdpUse()==0)
            {
          //            qDebug()<<"[getUdpUse()==0]";
                QList<UnitNode *> List1;
                this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
                foreach(UnitNode *un, List1 )
                {

            qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
                 if((un->getNum3()==unit->getNum3()))
                 if((un->getNum1()==unit->getNum1()))
                 {

                     this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                     QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                     return false;
                 }


                }
             //проконтроилровать отсутствие в дереве такого же порта

            }

            if(unit->getUdpUse()==1)
            {
              //проконтроилровать отсутствие в дереве такого же IP адреса
                QList<UnitNode *> List1;
                this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
                foreach(UnitNode *un, List1 )
                {
       //     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
                 if((un->getUdpAdress()==unit->getUdpAdress()))
                 if((un->getNum1()==unit->getNum1()))
                  {

                     this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                     QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                     return false;
                  }
                }
            }
            return true;
}

bool MainWindowCFG::pass_to_add_RLM_C(UnitNode *unit, UnitNode *parrent)
{
    if(parrent->getType()!=TypeUnitNode::GROUP)
    if(parrent->getType()!=TypeUnitNode::SYSTEM)
    {
        QMessageBox::critical(0,"Ошибка"," может быть добавлен только к группе");
        return false;

    }

//    Если связь по RS485 - контроль по RS485 порту
//    Если связь по UDP - контроль по IP адресу


        if(unit->getUdpUse()==0)
        {
      //            qDebug()<<"[getUdpUse()==0]";
            QList<UnitNode *> List1;
            this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
            foreach(UnitNode *un, List1 )
            {

        qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
             if((un->getNum3()==unit->getNum3()))
             if((un->getNum1()==unit->getNum1()))
             {

                 this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                 QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                 return false;
             }


            }
         //проконтроилровать отсутствие в дереве такого же порта

        }

        if(unit->getUdpUse()==1)
        {
          //проконтроилровать отсутствие в дереве такого же IP адреса
            QList<UnitNode *> List1;
            this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
            foreach(UnitNode *un, List1 )
            {
   //     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
             if((un->getUdpAdress()==unit->getUdpAdress()))
             if((un->getNum1()==unit->getNum1()))
              {

                 this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                 QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                 return false;
              }
            }
        }
        return true;
}

bool MainWindowCFG::pass_to_add_KL(UnitNode *unit, UnitNode *parrent)
{
      qDebug()<<"[----------------------------------------------]";
    //СД от одного до четырех
      if(unit->getNum2()<0||unit->getNum2()>4)
      {
          QMessageBox::critical(0,"Ошибка","СД от одного до четырех !");
          return false;

      }


    // может быть добавлен только к группе
        if(parrent->getType()!=TypeUnitNode::GROUP)
        {
            QMessageBox::critical(0,"Ошибка"," может быть добавлен только к группе");
            return false;
        }

        //на свободный адрес этого ком порта
        if(unit->getUdpUse()==0)
        {
      //            qDebug()<<"[getUdpUse()==0]";
            QList<UnitNode *> List1;
            this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
            foreach(UnitNode *un, List1 )
            {
  qDebug()<<"[1]";
        qDebug()<<un->getName()<<" "<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
             if((un->getNum3()==unit->getNum3()))
                 if((un->getNum1()==unit->getNum1()))
                 {
                       qDebug()<<"[2]";
                     if(un->getType()!=unit->getType())//если другое устройство  на этом адресе этого порта
                      {
                           qDebug()<<"[3]";

                         this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                           QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                         return false;
                      }
                     if(un->getType()==unit->getType()) //если на этом адресе этого порта есть СД - проверить на номер СД
                      {
                    //       qDebug()<<"[4]";
                         if(un->getNum2()==unit->getNum2())
                         {
                               qDebug()<<"[5]";
                             this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                               QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                             return false;

                         }

                      }

                 }


            }
         //проконтроилровать отсутствие в дереве такого же порта

        }

        if(unit->getUdpUse()==1)
        {
          //проконтроилровать отсутствие в дереве такого же IP адреса
            QList<UnitNode *> List1;
            this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
            foreach(UnitNode *un, List1 )
            {
    //     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
             if((un->getUdpAdress()==unit->getUdpAdress()))
             if((un->getNum1()==unit->getNum1()))
             {
                 if(un->getType()!=unit->getType())//если другое устройство  на этом адресе этого порта
                  {

                     this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                     QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                     return false;
                  }
                 if(un->getType()==unit->getType()) //если на этом адресе этого порта есть СД - проверить на номер СД
                  {
                     if(un->getNum2()==unit->getNum2())
                     {
                         this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                         QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                         return false;

                     }

                  }

             }

            }
        }

        return true;
}

bool MainWindowCFG::pass_to_add_ONVIF(UnitNode *unit, UnitNode *parrent)
{
//добавляется в системе группе и любому датчику - у одной точке
//не более одной камеры с одним айпишником

    qDebug()<<"onvif";
    if((parrent->getType()==TypeUnitNode::STRAZH_IP)||
       (parrent->getType()==TypeUnitNode::ONVIF)||
       (parrent->getType()==TypeUnitNode::DEVLINE)||
       (parrent->getType()==TypeUnitNode::RASTRMTV)||
       (parrent->getType()==TypeUnitNode::INFO_TABLO)||
       (parrent->getType()==TypeUnitNode::SSOI_IU) ||
       (parrent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }




        //Если общий родитель
        QModelIndex ind = this->modelTreeUN->findeIndexUN(parrent);


        QList<UnitNode *> List1;
        this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);

        foreach(UnitNode *un, List1 )
        {

           qDebug()<<".";
    //     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
           QModelIndex index=this->modelTreeUN->findeIndexUN(un);
           QModelIndex un_parent_index= this->modelTreeUN->parent(index);

         if(ind==un_parent_index)
          {
             qDebug()<<"[+]";
             if(un->getType()==unit->getType())
             if(un->getIcon1Path()==unit->getIcon1Path())
             {
                 this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                 QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                 return false;

             }
          }
        }
/*
     if(un->getParentUN()==unit->getParentUN())
     if(un->getType()==unit->getType())
     if(un->getIcon1Path()==unit->getIcon1Path())
     {
         this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));QMessageBox::critical(0,"Ошибка",("Такой обьект уже существует");
         dialog.exec();
         return false;

     }
*/

        return true;
}

bool MainWindowCFG::pass_to_add_STRAZH_IP(UnitNode *unit, UnitNode *parrent)
{
    //может быть добавлен к любому датчику группе системе сморти ссои конфигуратор
    if((parrent->getType()==TypeUnitNode::STRAZH_IP)||
       (parrent->getType()==TypeUnitNode::ONVIF)||
       (parrent->getType()==TypeUnitNode::DEVLINE)||
       (parrent->getType()==TypeUnitNode::RASTRMTV)||
       (parrent->getType()==TypeUnitNode::INFO_TABLO)||
       (parrent->getType()==TypeUnitNode::SSOI_IU) ||
       (parrent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }



    QModelIndex ind = this->modelTreeUN->findeIndexUN(parrent);


    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);

    foreach(UnitNode *un, List1 )
    {

       qDebug()<<".";
//     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
       QModelIndex index=this->modelTreeUN->findeIndexUN(un);
       QModelIndex un_parent_index= this->modelTreeUN->parent(index);

     if(ind==un_parent_index)
      {
         qDebug()<<"[+]";
         if(un->getType()==unit->getType())
             if((un->getIcon1Path()==unit->getIcon1Path())||
             (un->getIcon4Path()==unit->getIcon4Path()))
         {
             this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                 QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");

             return false;

         }
      }
    }

 /*
    foreach(UnitNode *un, List1 )
    {

     if(un->getType()==unit->getType())

     if((un->getIcon1Path()==unit->getIcon1Path())||
        (un->getIcon4Path()==unit->getIcon4Path()))
     {
         this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));QMessageBox::critical(0,"Ошибка",("Такой обьект уже существует");
         dialog.exec();
         return false;

     }

    }
*/
        return true;
}

bool  MainWindowCFG::pass_to_add_NET_DEV(UnitNode */*unit*/, UnitNode *parrent)
{
    if(parrent->getType()!=TypeUnitNode::GROUP)
    if(parrent->getType()!=TypeUnitNode::SYSTEM)
    {
        QMessageBox::critical(0,"Ошибка","БОД может быть добавлен только к группе");
        return false;

    }

    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
 /*   foreach(UnitNode *un, List1 )
    {
     if(un->getType()==unit->getType())
     if(un->getIcon1Path()==unit->getIcon1Path())
     {
         QMessageBox::critical(0,"Ошибка",("Такой обьект уже есть");
         dialog.exec();
         return false;

     }

    }*/
    return true;
}


bool MainWindowCFG::add_unit()
{
    qDebug()<<"[add_unit()]";
    bool res=1;



    QModelIndex index=this->ui->treeView->currentIndex();
    UnitNode* parrent;
    if(index.isValid())
    {
    parrent = static_cast<UnitNode*>(index.internalPointer());
    }
    else
    {
    parrent = this->modelTreeUN->rootItemUN;
    this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(parrent));
    }


    int type=this->m_TypeUnitNode.key(this->ui->uType_combobox->currentText());

    /*
    QString type_srtring=this->ui->uType_combobox->currentText();
    if(type_srtring==str_GROUP)
    type=GROUP;
    else
    if(type_srtring==str_SD_BL_IP)
    type=SD_BL_IP;
    else
    if(type_srtring==str_IU_BL_IP)
    type=IU_BL_IP;
    else
    res=0;
*/
    qDebug()<<"[Type: "<<type<<"]";

    UnitNode *unit=new UnitNode();
    unit->setType(0);
    unit->setNum1(0);
    unit->setNum2(0);
    unit->setNum3(0);
    unit->setLevel(0);
    unit->setName("");
    unit->setIconVisible(0);
    unit->setX(0);
    unit->setY(0);
    unit->setDK(0);
    unit->setBazalt(0);
    unit->setMetka(0);
    unit->setRazriv(0);
    unit->setAdamOff(0);
    unit->setAlarmMsgOn(0);
    unit->setConnectBlock(0);
    unit->setOutType(0);
    unit->setAsoosd_kk(0);
    unit->setAsoosd_nn(0);
    unit->setDescription("");
    unit->setLan(0);
    unit->setLon(0);
    unit->setUdpUse(0);
    unit->setUdpAdress("");
    unit->setUdpPort(0);
    unit->setUdpTimeout(0);
    unit->setMetka1Time_0(0);
    unit->setMetka1Time_1(0);
    unit->setMetka2Time_0(0);
    unit->setMetka2Time_1(0);
    unit->setMetka3Time_0(0);
    unit->setMetka3Time_1(0);
    unit->setMetka4Time_0(0);
    unit->setMetka4Time_1(0);
    unit->setMetkaDopuskTime_0(0);
    unit->setMetkaDopuskTime_1(0);
    unit->setTimeIntervalStatusRequest(0);







    unit->setName(this->ui->uName_lineedit->text());
    unit->setType(type);





    unit->setLevel(parrent->getLevel()+1);

    if(this->ui->stackedWidget_2->currentWidget()==this->ui->coordinates_for_all)
    {

        unit->setLan(this->ui->coordinate_X_doubleSpinBox->value());
        unit->setLon(this->ui->coordinate_Y_doubleSpinBox->value());
        unit->setDescription(ui->Dop_info_description_lineedit->text());

    }

set_option(unit,parrent);
    //Проверить можно ли добавлять юнит к этому родителю
    //Определить тип родителя
//    int parrent_type;

    //Определить тип чайлда
//    int child_type;



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

//    bool res=true;

    if(origin_name!=new_name)
    {
        if(this->this_name_is_free(new_name)==false)
        {
//            res=false;
        }

    }

 //   if(res==true)
 //   set_option(unit);
    return true;
}

bool MainWindowCFG::delete_unit()
{
    QModelIndex index=this->ui->treeView->currentIndex();

//    UnitNode *unit = static_cast<UnitNode*>(current_index.internalPointer());

    if (index.isValid())
    {

              this->modelTreeUN->deleteUnit(index);

             return true;




     }

    return false;

}

void MainWindowCFG::show_the_tree()
{qDebug()<<"==============================";
    qDebug()<<"[TREE]";
    QList<UnitNode *> List;
    this->modelTreeUN->getListFromModel(List);
    qDebug()<<"[count] "<<List.count();
    foreach(UnitNode* unit,List)
    {
        qDebug()<<"---------------------------------------------------------------------------";
        qDebug()<<"Name:  "<<unit->getName()
        <<"/Type:  "<<this->m_TypeUnitNode.value(unit->getType())
        <<"/Level: "<<unit->getLevel();
    }

}

void MainWindowCFG::get_option_SD_BL_IP(UnitNode *unit)
{

//    int Num2=unit->getNum2();

//    bool DK=false;
//    if(unit->getDK())
//       DK=true;
//    int Bazalt=unit->getBazalt();
//    int connectblock=unit->getConnectBlock();

//    int UdpUse=unit->getUdpUse();

    QString UdpAdress=unit->getUdpAdress();

//    int UdpPort=unit->getUdpPort();

    qDebug()<<"Name: "<<unit->getName()
            <<" Type:"<<this->m_TypeUnitNode.value(unit->getType())
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

    this->ui->textEdit->clear();
    QString string1;




    if(unit->getBazalt()==1)
    {
        string1.append("БЛ-IP Уз");
        string1.append("Кан:");
    }
    if(unit->getBazalt()==0)
    {
        string1.append("БЛ-IP ");
        string1.append("Кан:");
    }

    if(unit->getUdpUse()==0)
    {
        string1.append(QString::number(unit->getNum3()));
        string1.append(" ");
        string1.append("СД:");
        string1.append(QString::number(unit->getNum2()));

        if(unit->getBazalt()==1)
        {
            string1.append(" - ");
            string1.append("ИУ");
            string1.append(QString::number(unit->getNum2()));
        }

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
        string1.append("СД:");
        string1.append(QString::number(unit->getNum2()));
    }


this->ui->textEdit->append(string1);



}

void MainWindowCFG::get_option_IU_BL_IP(UnitNode *unit)
{

    this->ui->textEdit->clear();
    QString string1;





        string1.append("БЛ-IP ");
        string1.append("Кан:");


    if(unit->getUdpUse()==0)
    {
        string1.append(QString::number(unit->getNum3()));
        string1.append(" ");
        string1.append("ИУ:");
        string1.append(QString::number(unit->getNum2()));



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
        string1.append("ИУ:");
        string1.append(QString::number(unit->getNum2()));
    }


this->ui->textEdit->append(string1);


}

void MainWindowCFG::get_option_TG(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;

    string1.append("Точка/Гарда: ");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");
    string1.append("ЧЭ: ");
    string1.append(QString::number(unit->getNum2()));
    string1.append(" ");
    string1.append("Кан: ");

    if(unit->getUdpUse()==0)
    {
   string1.append(QString::number(unit->getNum3()));
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

    }

    this->ui->textEdit->append(string1);

}

void MainWindowCFG::get_option_RLM_KRL(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;


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

    string1.append(":");

    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");


    string1.append("Кан:");

    string1.append(QString::number(unit->getNum3()));
    string1.append(" ");

    if(unit->getUdpUse()==0)
    {
  // string1.append(QString::number(unit->getNum3()));
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

    }

    this->ui->textEdit->append(string1);

}

void MainWindowCFG::get_option_RLM_C(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;





    string1.append("РИФ-РЛМ-С:");

    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");


    string1.append("Кан:");

    string1.append(QString::number(unit->getNum3()));
    string1.append(" ");

    if(unit->getUdpUse()==0)
    {
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

    }

    this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_BOD_T4K_M(UnitNode *unit)
{

    this->ui->textEdit->clear();
    QString string1;

    string1.append("Точка-М/Гарда-М ");

    string1.append("Кан:");

    if(unit->getUdpUse()==0)
    {
        string1.append(QString::number(unit->getNum3()));


    }
    if(unit->getUdpUse()==1)
    {
        string1.append(unit->getUdpAdress());
        string1.append("::");
        string1.append(QString::number(unit->getUdpPort()));
        string1.append(" ");
    }



    string1.append(" БОД:");
    string1.append(QString::number(unit->getNum1()));

    if(unit->getUdpUse()==0)
    {


        if(unit->getUdpAdress()!="")
        {

            string1.append(" (");
            string1.append(unit->getUdpAdress());
            string1.append(")");

        }
    }


    this->ui->textEdit->append(string1);
    qDebug()<<"[+]"<<string1;


}

void MainWindowCFG::get_option_Y4_T4K_M(UnitNode *unit)
{
    //Ищем его родительский БОД

    //Берем из этого БОДа Num3 - канал
    //                    Num1 - БОД
   QModelIndex ind = this->modelTreeUN->findeIndexUN(unit);
   QModelIndex ind_BOD = this->modelTreeUN->parent(ind);
   UnitNode* BOD= static_cast<UnitNode*>(ind_BOD.internalPointer());



   this->ui->textEdit->clear();
   QString string1;

   string1.append("Точка-М/Гарда-М ");

   string1.append("Кан:");

   string1.append(QString::number(BOD->getNum3()));

   string1.append(" БОД:");

   string1.append(QString::number(BOD->getNum1()));

   string1.append(" Участок:");

   string1.append(QString::number(unit->getNum2()/100));

   this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_DD_T4K_M(UnitNode *unit)
{
    //Ищем его родительский участок и БОД

    //Берем из этого БОДа Num3 - канал
    //                    Num1 - БОД

    //Из участка берем Num2 - участок
   QModelIndex ind = this->modelTreeUN->findeIndexUN(unit);
   QModelIndex ind_Y4 = this->modelTreeUN->parent(ind);
   UnitNode* Y4= static_cast<UnitNode*>(ind_Y4.internalPointer());

   QModelIndex ind_BOD = this->modelTreeUN->parent(ind_Y4);
   UnitNode* BOD= static_cast<UnitNode*>(ind_BOD.internalPointer());

   this->ui->textEdit->clear();
   QString string1;

   string1.append("Точка-М/Гарда-М ");

   string1.append("Кан:");

   string1.append(QString::number(BOD->getNum3()));

   string1.append(" БОД:");

   string1.append(QString::number(BOD->getNum1()));

   string1.append(" Участок:");

   string1.append(QString::number(Y4->getNum2()/100));

   string1.append(" ДД:");

   string1.append(QString::number(unit->getNum2()-Y4->getNum2()+1));



   this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_BOD_SOTA(UnitNode *unit)
{


this->ui->textEdit->clear();
QString string1;

string1.append("Сота/Сота-М ");

string1.append("Кан:");

if(unit->getUdpUse()==0)
{
    string1.append(QString::number(unit->getNum3()));


}
if(unit->getUdpUse()==1)
{
    string1.append(unit->getUdpAdress());
    string1.append("::");
    string1.append(QString::number(unit->getUdpPort()));
    string1.append(" ");
}



string1.append(" БОД:");
string1.append(QString::number(unit->getNum1()));

if(unit->getUdpUse()==0)
{


    if(unit->getUdpAdress()!="")
    {

        string1.append(" (");
        string1.append(unit->getUdpAdress());
        string1.append(")");

    }
}


this->ui->textEdit->append(string1);
qDebug()<<"[+]"<<string1;



}

void MainWindowCFG::get_option_Y4_SOTA(UnitNode *unit)
{

    //Ищем его родительский БОД

    //Берем из этого БОДа Num3 - канал
    //                    Num1 - БОД
   QModelIndex ind = this->modelTreeUN->findeIndexUN(unit);
   QModelIndex ind_BOD = this->modelTreeUN->parent(ind);
   UnitNode* BOD= static_cast<UnitNode*>(ind_BOD.internalPointer());



   this->ui->textEdit->clear();
   QString string1;

   string1.append("Сота/Сота-М ");

   string1.append("Кан:");

   string1.append(QString::number(BOD->getNum3()));

   string1.append(" БОД:");

   string1.append(QString::number(BOD->getNum1()));

   string1.append(" Участок:");

   string1.append(QString::number(unit->getNum2()/100));

   this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_DD_SOTA(UnitNode *unit)
{
    //Ищем его родительский участок и БОД

    //Берем из этого БОДа Num3 - канал
    //                    Num1 - БОД

    //Из участка берем Num2 - участок
   QModelIndex ind = this->modelTreeUN->findeIndexUN(unit);
   QModelIndex ind_Y4 = this->modelTreeUN->parent(ind);
   UnitNode* Y4= static_cast<UnitNode*>(ind_Y4.internalPointer());

   QModelIndex ind_BOD = this->modelTreeUN->parent(ind_Y4);
   UnitNode* BOD= static_cast<UnitNode*>(ind_BOD.internalPointer());

   this->ui->textEdit->clear();
   QString string1;

   string1.append("Сота/Сота-М ");

   string1.append("Кан:");

   string1.append(QString::number(BOD->getNum3()));

   string1.append(" БОД:");

   string1.append(QString::number(BOD->getNum1()));

   string1.append(" Участок:");

   string1.append(QString::number(Y4->getNum2()/100));

   string1.append(" ДД:");

   string1.append(QString::number(unit->getNum2()-Y4->getNum2()+1));



   this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_BL_IP(UnitNode */*unit*/)
{

}

void MainWindowCFG::get_option_KL(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;

    string1.append("Концентратор: ");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");
    string1.append("СД: ");
    string1.append(QString::number(unit->getNum2()));
    string1.append(" ");
    string1.append("Кан: ");

    if(unit->getUdpUse()==0)
    {
   string1.append(QString::number(unit->getNum3()));
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
    }
  this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_ONVIF(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;
    string1.append("ONVIF-камера: ");
    string1.append(unit->getIcon1Path());



   this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_STRAZH_IP(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;
    string1.append("Страж- IP: ");
    string1.append(unit->getIcon1Path());
    string1.append("; ");
    string1.append(unit->getIcon4Path());


   this->ui->textEdit->append(string1);

}

void MainWindowCFG::get_option_NET_DEV(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;
    string1.append("Сетевое устройство: ");
    string1.append(unit->getIcon1Path());



    this->ui->textEdit->append(string1);
}

void MainWindowCFG::load_other_options_from_ini_file(QString filename)
{
    get_PARAMS(filename);
    get_RIF(filename);
    get_SSOI(filename);
    get_RASTRMTV(filename);
    get_INTEGRATION(filename);
    get_SQL(filename);
    get_ADAM4068(filename);
    get_TABLO(filename);
    get_RASTRMSSOI(filename);
    get_BACKUP(filename);
    get_PORT(filename);
    get_OPERATORS(filename);
    get_ASOOSD(filename);






}

/*
  PlanType=0 - план
  PlanType=1 - граф.модуль
  PlanType=2 - не использовать

 */

void MainWindowCFG::get_PARAMS(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif

    settings.beginGroup("PARAMS");


    qDebug()<<"SoundType  "<<settings.value("SoundType",-1).toInt();

    int PlanType,SoundType;

    PlanType =settings.value("PlanType",-1).toInt();

    if(PlanType!=1 && PlanType!=2)
    {
        QString msg;
        msg.clear();
        msg.append("Параметр PlanType указан неверно !!! (допустимые значения:");

        foreach(QString str,map_PARAMS_PlanType)
        {
         msg.append(QString::number(map_PARAMS_PlanType.key(str)));
         msg.append(" - ");
         msg.append(str);
         msg.append(";");



        }


        QMessageBox::critical(0,"Ошибка",(msg));


    }

    SoundType =settings.value("SoundType",-1).toInt();

    if(SoundType!=1 && SoundType!=2 && SoundType!=0)
    {
        QString msg;
        msg.clear();
        msg.append("Параметр SoundType указан неверно !!! (допустимые значения:");

        foreach(QString str,map_PARAMS_SoundType)
        {
         msg.append(QString::number(map_PARAMS_SoundType.key(str)));
         msg.append(" - ");
         msg.append(str);
         msg.append("; ");



        }


        QMessageBox::critical(0,"Ошибка",(msg));


    }





       this->ui->PlanType_comboBox->setCurrentText(map_PARAMS_PlanType.value(settings.value("PlanType",-1).toInt()));
       this->ui->SoundType_comboBox->setCurrentText(map_PARAMS_SoundType.value(settings.value("SoundType",-1).toInt()));

       this->ui->PARAMS_AutoStart_comboBox->setCurrentText(map_PARAMS_AutoStart.value(settings.value("AutoStart",-1).toInt()));

    settings.endGroup();

}

void MainWindowCFG::set_PARAMS(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif


    settings.beginGroup("PARAMS");



         settings.setValue("PlanType",map_PARAMS_PlanType.key(this->ui->PlanType_comboBox->currentText()));




         settings.setValue("SoundType",map_PARAMS_SoundType.key(this->ui->SoundType_comboBox->currentText()));

         settings.setValue("AutoStart",map_PARAMS_AutoStart.key(this->ui->PARAMS_AutoStart_comboBox->currentText()));
 //   settings.setValue("PlanType",this->ui->PlanType_comboBox->currentIndex());
 //   settings.setValue("SoundType",this->ui->SoundType_comboBox->currentIndex());

    settings.endGroup();
}

void MainWindowCFG::default_PARAMS()
{
    /*
    map_PARAMS_PlanType.insert(1,"граф.модуль");
    map_PARAMS_PlanType.insert(2,"не использовать");



     foreach (QString str, map_PARAMS_PlanType)
     {

     this->ui->PlanType_comboBox->addItem(str);
     }
    */


    this->ui->PlanType_comboBox->setCurrentText(map_PARAMS_PlanType.value(2));
    this->ui->SoundType_comboBox->setCurrentText(map_PARAMS_SoundType.value(0));
    this->ui->PARAMS_AutoStart_comboBox->setCurrentText(map_PARAMS_AutoStart.value(0));
}

void MainWindowCFG::default_options()
{
    qDebug()<<"[Create]";
    this->modelTreeUN->makeEmptyTree();

    default_PARAMS();
    default_OPERATORS();
    default_RIF();
    default_INTEGRATION();
    default_SQL();
    default_BACKUP();

    default_SSOI();
    default_TABLO();
    this->ui->RASTR_wgt->default_options();
    this->ui->ADAM_wgt->default_options();
    this->ui->AdmAud_wgt->default_options();

    this->ui->uType_combobox->setCurrentText(m_TypeUnitNode.value(TypeUnitNode::GROUP));

}

void MainWindowCFG::get_RIF(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif


    settings.beginGroup("RIF");

    for(int i=0;i<99;i++)
    {



      QString str_RifPortSpeed("RifPortSpeed%1");
      str_RifPortSpeed = str_RifPortSpeed.arg(i+1);

      int RifPortSpeed = settings.value(str_RifPortSpeed,-1).toInt();

      if(RifPortSpeed!=-1)
      {





          QModelIndex index = this->rif_model->index(i,1,QModelIndex());

         qDebug()<<index.row()<<" "<<index.column()<<" "<<this->rif_model->data(index,Qt::DisplayRole);

         this->rif_model->setData(index, RifPortSpeed, Qt::EditRole);

      }

      QString str_RifPortInterval("RifPortInterval%1");
      str_RifPortInterval = str_RifPortInterval.arg(i+1);

      int RifPortInterval = settings.value(str_RifPortInterval,-1).toInt();

      if(RifPortInterval!=-1)
      {


          QModelIndex index = this->rif_model->index(i,2,QModelIndex());

            qDebug()<<index.row()<<" "<<index.column()<<" "<<this->rif_model->data(index,Qt::DisplayRole);

         this->rif_model->setData(index, RifPortInterval, Qt::EditRole);
      }



    }

    this->ui->RIF_AutoDK_comboBox->setCurrentIndex(settings.value("AutoDK",-1).toInt());
    this->ui->RIF_TochkaDirectionInterval_doubleSpinBox->setValue(settings.value("TochkaDirectionInterval",-1).toDouble());

//    settings.setValue("AutoDK", autoDK);
//    settings.setValue("TochkaDirectionInterval", TochkaDirectionInterval);
 this->update_rif_comport_table();
    settings.endGroup();
}

void MainWindowCFG::set_RIF(QString filename)
{

}

void MainWindowCFG::default_RIF()
{

    for(int i(0), n(100); i < n; i++)
    {



     //  QModelIndex index = this->ui->tableView->indexAt(QPoint(i,1));
        QModelIndex index = this->rif_model->index(i,1,QModelIndex());

       qDebug()<<index.row()<<" "<<index.column()<<" "<<this->rif_model->data(index,Qt::DisplayRole);

       this->rif_model->setData(index, 4800, Qt::EditRole);

        index = this->rif_model->index(i,2,QModelIndex());

          qDebug()<<index.row()<<" "<<index.column()<<" "<<this->rif_model->data(index,Qt::DisplayRole);

       this->rif_model->setData(index, 50, Qt::EditRole);


    /*      port->set_RifPortSpeed(50);

//qDebug()<<"---"<<i;
        if(i<comports.count())
        {
        comports.at(i)->set_RifPortSpeed(4800);
        comports.at(i)->set_RifPortInterval(50);
        }*/
    }
    update_rif_comport_table();


    this->ui->RIF_AutoDK_comboBox->setCurrentIndex(0);
    this->ui->RIF_TochkaDirectionInterval_doubleSpinBox->setValue(20);
}

void MainWindowCFG::get_SSOI(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif

    settings.beginGroup("SSOI");

    this->ui->SSOIwgt->set_Version(settings.value("Version",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_PortNum1(settings.value("SsoiM_PortNum1",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_Interval1(settings.value("SsoiM_Interval1",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_Interval_1(settings.value("SsoiM_Interval_1",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_MaxErrCnt1(settings.value("SsoiM_MaxErrCnt1",-1).toInt());

    this->ui->SSOIwgt->set_SsoiM_PortNum2(settings.value("SsoiM_PortNum2",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_Interval2(settings.value("SsoiM_Interval2",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_Interval_2(settings.value("SsoiM_Interval_2",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_MaxErrCnt2(settings.value("SsoiM_MaxErrCnt2",-1).toInt());

    this->ui->SSOIwgt->set_SsoiM_PortNum3(settings.value("SsoiM_PortNum3",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_Interval3(settings.value("SsoiM_Interval3",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_Interval_3(settings.value("SsoiM_Interval_3",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_MaxErrCnt3(settings.value("SsoiM_MaxErrCnt3",-1).toInt());

    this->ui->SSOIwgt->set_SsoiM_PortNum4(settings.value("SsoiM_PortNum4",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_Interval4(settings.value("SsoiM_Interval4",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_Interval_4(settings.value("SsoiM_Interval_4",-1).toInt());
    this->ui->SSOIwgt->set_SsoiM_MaxErrCnt4(settings.value("SsoiM_MaxErrCnt4",-1).toInt());


    this->ui->SSOIwgt->set_SsoiM_MaxErrCnt4(settings.value("SsoiM_MaxErrCnt4",-1).toInt());

    this->ui->SSOIwgt->set_SsoiAutoDkUse(settings.value("SsoiAutoDkUse",-1).toInt());
    this->ui->SSOIwgt->set_SsoiMOprosVariant(settings.value("SsoiMOprosVariant",-1).toInt());

    this->ui->SSOIwgt->set_SsoiM_PortSpeed(settings.value("SsoiM_PortSpeed",-1).toInt());

    /*
    Version=2
    SsoiM_PortNum1=1
    SsoiM_Interval1=1500
    SsoiM_Interval_1=100
    SsoiM_MaxErrCnt1=2
    SsoiM_PortNum2=2
    SsoiM_Interval2=1500
    SsoiM_Interval_2=100
    SsoiM_MaxErrCnt2=2
    SsoiM_PortNum3=3
    SsoiM_Interval3=1500
    SsoiM_Interval_3=100
    SsoiM_MaxErrCnt3=2
    SsoiM_PortNum4=4
    SsoiM_Interval4=1500
    SsoiM_Interval_4=100
    SsoiM_MaxErrCnt4=2
    SsoiAutoDkUse=0
    SsoiMOprosVariant=0
    SsoiFixNewWarning=0
    SsoiM_PortSpeed=4800*/

  //  int RifPortInterval = settings.value(str_RifPortInterval,-1).toInt();



    settings.endGroup();
}

void MainWindowCFG::set_SSOI(QString /*filename*/)
{



}

void MainWindowCFG::default_SSOI()
{
this->ui->SSOIwgt->default_options();
}

void MainWindowCFG::get_RASTRMTV(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif
      /*
      Use=0
      Name=localhost
      Port=1972
      Port2=1974
      KeepAliveInterval=20
      ThermostatUse=0
      dtInfoToJpg=0
      AutoDkPeriod=10*/
    settings.beginGroup("RASTRMTV");

    this->ui->RASTR_wgt->setUse((settings.value("Use",-1).toInt()));
    this->ui->RASTR_wgt->setName((settings.value("Name",-1).toString()));
    this->ui->RASTR_wgt->setPort((settings.value("Port",-1).toInt()));
    this->ui->RASTR_wgt->setPort2((settings.value("Port2",-1).toInt()));
    this->ui->RASTR_wgt->setKeepAliveInterval((settings.value("KeepAliveInterval",-1).toInt()));
    this->ui->RASTR_wgt->setThermostatUse((settings.value("ThermostatUse",-1).toInt()));
    this->ui->RASTR_wgt->setDtInfoToJpg((settings.value("dtInfoToJpg",-1).toInt()));
    this->ui->RASTR_wgt->setAutoDkPeriod((settings.value("AutoDkPeriod",-1).toInt()));

    settings.endGroup();
}

void MainWindowCFG::set_RASTRMTV(QString /*filename*/)
{

}

void MainWindowCFG::default_RASTRMTV()
{

}

void MainWindowCFG::get_INTEGRATION(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif

      settings.beginGroup("INTEGRATION");

      this->ui->INTEGRATION_Use_comboBox->setCurrentText(map_INTEGRATION_Use.value(settings.value("Use",-1).toInt()));
      this->ui->INTEGRATION_Host_lineEdit->setText(settings.value("Host",-1).toString());
      this->ui->INTEGRATION_Port_doubleSpinBox->setValue(settings.value("Port",-1).toInt());
      this->ui->INTEGRATION_Port2_doubleSpinBox->setValue(settings.value("Port2",-1).toInt());
      this->ui->INTEGRATION_KeepAliveInterval_doubleSpinBox->setValue(settings.value("KeepAliveInterval",-1).toInt());
      this->ui->INTEGRATION_DevLine_filepath_lineEdit->setText(settings.value("DevLine",-1).toString());



      settings.endGroup();

}

void MainWindowCFG::set_INTEGRATION(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif

      settings.beginGroup("INTEGRATION");

      settings.setValue("Use",map_INTEGRATION_Use.key(this->ui->INTEGRATION_Use_comboBox->currentText()));
      settings.setValue("Host",this->ui->INTEGRATION_Host_lineEdit->text());
      settings.setValue("Port",this->ui->INTEGRATION_Port_doubleSpinBox->value());
      settings.setValue("Port2",this->ui->INTEGRATION_Port2_doubleSpinBox->value());
      settings.setValue("KeepAliveInterval",this->ui->INTEGRATION_KeepAliveInterval_doubleSpinBox->value());
      settings.setValue("DevLine",this->ui->INTEGRATION_DevLine_filepath_lineEdit->text());


  //          this->ui->INTEGRATION_DevLine_filepath_lineEdit->setText(settings.value("DevLine",-1).toString());

      settings.endGroup();
}

void MainWindowCFG::default_INTEGRATION()
{
    this->ui->INTEGRATION_Use_comboBox->setCurrentText(map_INTEGRATION_Use.value(0));
    this->ui->INTEGRATION_Host_lineEdit->setText("localhost");
    this->ui->INTEGRATION_Port_doubleSpinBox->setValue(1973);
    this->ui->INTEGRATION_Port2_doubleSpinBox->setValue(1976);
    this->ui->INTEGRATION_KeepAliveInterval_doubleSpinBox->setValue(10);
    this->ui->INTEGRATION_DevLine_filepath_lineEdit->setText("C:/Program Files/DevLine/Line/observer.exe");
}

void MainWindowCFG::get_SQL(QString filename)
{
      qDebug()<< "[get_SQL]";
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif
      int res=0;


          if(settings.childGroups().contains("MYSQL"))
          {
            settings.beginGroup("MYSQL");
            if(settings.value("Use", -1).toInt()==1)
            {
                this->ui->SQL_type_comboBox->setCurrentText("MySQL");
                res=1;

            }
            else
            settings.endGroup();

          }

          if(settings.childGroups().contains("PostgresSQL"))
          {
             qDebug()<< "(settings.childGroups().contains(\"PostgresSQL\"))";
             settings.beginGroup("PostgresSQL");
             if(settings.value("Use", -1).toInt()==1)
             {
                 this->ui->SQL_type_comboBox->setCurrentText("PostgresSQL");
                 res=1;

             }
             else
             settings.endGroup();
          }

          if(res==1)
          {


              this->ui->SQL_server_lineEdit->setText(settings.value("Host",-1).toString());
              this->ui->SQL_port_doubleSpinBox->setValue(settings.value("Port",-1).toDouble());
              this->ui->SQL_login_lineEdit->setText(settings.value("Login",-1).toString());



           //   this->ui->SQL_password_lineEdit->setText(this->XOR_Crypt(settings.value("Password",-1).toString(),"start7"));
              this->ui->SQL_password_lineEdit->setText(this->XOR_Crypt(settings.value("Password",-1).toString()));

          //    this->ui->SQL_password_lineEdit->setText(settings.value("Password",-1).toString());
              this->ui->SQL_database_lineEdit->setText(settings.value("DbName",-1).toString());



                if(settings.value("P1",-1).toInt()==1)
                 this->ui->SQL_P1_checkBox->setChecked(true);

                if(settings.value("P1",-1).toInt()==0)
                 this->ui->SQL_P1_checkBox->setChecked(false);

                if(settings.value("P2",-1).toInt()==1)
                 this->ui->SQL_P2_checkBox->setChecked(true);

                if(settings.value("P2",-1).toInt()==0)
                 this->ui->SQL_P2_checkBox->setChecked(false);

                if(settings.value("AutoDbStart",-1).toInt()==1)
                 this->ui->SQL_AutoDbStart_checkBox->setChecked(true);

                if(settings.value("AutoDbStart",-1).toInt()==0)
                 this->ui->SQL_AutoDbStart_checkBox->setChecked(false);

              this->ui->SQL_AutoDbStartHour_doubleSpinBox->setValue(settings.value("AutoDbStartHour",-1).toDouble());
              this->ui->SQL_AutoDbStartMinute_doubleSpinBox->setValue(settings.value("AutoDbStartMinute",-1).toDouble());

              settings.endGroup();
          }
          else
                          this->ui->SQL_type_comboBox->setCurrentText("Выкл");

}

void MainWindowCFG::set_SQL(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif
int res=0;
    if(this->ui->SQL_type_comboBox->currentText()=="MySQL")
    {

      settings.beginGroup("PostgresSQL");
      settings.setValue("Use", 0);
      settings.endGroup();

      settings.beginGroup("MYSQL");
      settings.setValue("Use", 1);
      res=1;


    }
    if(this->ui->SQL_type_comboBox->currentText()=="PostgresSQL")
    {
      settings.beginGroup("MYSQL");
      settings.setValue("Use", 0);
      settings.endGroup();

      settings.beginGroup("PostgresSQL");
      settings.setValue("Use", 1);
      res=1;



    }
    if(res==1)
    {


      settings.setValue("Host", this->ui->SQL_server_lineEdit->text());
      settings.setValue("Port", this->ui->SQL_port_doubleSpinBox->text());
      settings.setValue("Login", this->ui->SQL_login_lineEdit->text());
      settings.setValue("Password", this->ui->SQL_password_lineEdit->text());
      settings.setValue("DbName", this->ui->SQL_database_lineEdit->text());

      if(this->ui->SQL_P1_checkBox->isChecked())
      settings.setValue("P1", 1);
      else
      settings.setValue("P1", 0);


      if(this->ui->SQL_P2_checkBox->isChecked())
      settings.setValue("P2", 1);
      else
      settings.setValue("P2", 0);

      if(this->ui->SQL_AutoDbStart_checkBox->isChecked())
      settings.setValue("AutoDbStart", 1);
      else
      settings.setValue("AutoDbStart", 0);


      settings.setValue("AutoDbStartHour",this->ui->SQL_AutoDbStartHour_doubleSpinBox->value() );
      settings.setValue("AutoDbStartMinute",this->ui->SQL_AutoDbStartMinute_doubleSpinBox->value() );

      settings.endGroup();




    }
    else
    {
        settings.beginGroup("MYSQL");
        settings.setValue("Use", 0);
        settings.endGroup();
        settings.beginGroup("PostgresSQL");
        settings.setValue("Use", 0);
        settings.endGroup();
    }
}

void MainWindowCFG::default_SQL()
{
this->ui->SQL_type_comboBox->setCurrentText("Выкл");
    this->ui->SQL_server_lineEdit->setText("localhost");
    this->ui->SQL_port_doubleSpinBox->setValue(3306);
    this->ui->SQL_login_lineEdit->setText("");
    this->ui->SQL_password_lineEdit->setText("");
    this->ui->SQL_database_lineEdit->setText("");


       this->ui->SQL_P1_checkBox->setChecked(false);


       this->ui->SQL_P2_checkBox->setChecked(false);


       this->ui->SQL_AutoDbStart_checkBox->setChecked(false);

    this->ui->SQL_AutoDbStartHour_doubleSpinBox->setValue(0);
    this->ui->SQL_AutoDbStartMinute_doubleSpinBox->setValue(0);
}








void MainWindowCFG::get_ADAM4068(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif
    //  Port=0
    //  Interval=100

    settings.beginGroup("ADAM4068");

    this->ui->ADAM_wgt->set_Port((settings.value("Port",-1).toInt()));
    this->ui->ADAM_wgt->set_Interval((settings.value("Interval",-1).toInt()));

    settings.endGroup();
}

void MainWindowCFG::set_ADAM4068(QString /*filename*/)
{

}

void MainWindowCFG::default_ADAM4068()
{

}

void MainWindowCFG::get_TABLO(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif
      int res=0;

   //   Port=0
  //    Blinking=0
      settings.beginGroup("TABLO");

     this->ui->SSOIwgt->setPort(settings.value("Port",-1).toInt());
     this->ui->SSOIwgt->setBlinking(settings.value("Blinking",-1).toInt());
      settings.endGroup();


}

void MainWindowCFG::set_TABLO(QString /*filename*/)
{

}

void MainWindowCFG::default_TABLO()
{
this->ui->SSOIwgt->default_options();
}

void MainWindowCFG::get_RASTRMSSOI(QString /*filename*/)
{

}

void MainWindowCFG::set_RASTRMSSOI(QString /*filename*/)
{

}

void MainWindowCFG::default_RASTRMSSOI()
{

}

void MainWindowCFG::get_BACKUP(QString filename)
{

    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif
//int res=0;

    settings.beginGroup("BACKUP");
    QString BackupPath=settings.value("BackupPath",-1).toString();
    this->ui->BACKUP_BackupPath_lineedit->setText(BackupPath);

    int MaxBdStringCnt =  settings.value("MaxBdStringCnt",-1).toInt();
    this->ui->BACKUP_MaxBdStringCnt_comboBox->setCurrentText(map_BACKUP_MaxBdStringCnt.value(MaxBdStringCnt));


    settings.endGroup();
}

void MainWindowCFG::set_BACKUP(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif
//int res=0;

    settings.beginGroup("BACKUP");

    settings.setValue("BackupPath",this->ui->BACKUP_BackupPath_lineedit->text());
    settings.setValue("MaxBdStringCnt",map_BACKUP_MaxBdStringCnt.key(this->ui->BACKUP_MaxBdStringCnt_comboBox->currentText()));


    settings.endGroup();
}

void MainWindowCFG::default_BACKUP()
{
    this->ui->BACKUP_BackupPath_lineedit->setText("C:/RIFx/Backup");
    this->ui->BACKUP_MaxBdStringCnt_comboBox->setCurrentText(map_BACKUP_MaxBdStringCnt.value(0));
}

void MainWindowCFG::get_PORT(QString /*filename*/)
{

}

void MainWindowCFG::set_PORT(QString /*filename*/)
{

}

void MainWindowCFG::default_PORT()
{

}

void MainWindowCFG::get_OPERATORS(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif


    settings.beginGroup("OPERATORS");

    if(0==settings.value("Use",-1).toInt()){
        this->ui->operators_use_combobox->setCurrentText(" Без операторов");
         qDebug()<<"OPERATORS Use = 0";
    }
    else
    {
        this->ui->operators_use_combobox->setCurrentText(" С операторами");

    }

        int Count=settings.value("Count",-1).toInt();

        qDebug()<<"OPERATORS Count = "<<Count;
        settings.endGroup();

        for(int i=0;i<Count;i++)
        {
            QString operatorGroup("Operator_%1");
            operatorGroup = operatorGroup.arg(i);
            qDebug()<<operatorGroup;
            if(settings.childGroups().contains(operatorGroup))
            {
                settings.beginGroup(operatorGroup);
                Operator* op = new Operator();
                op->setFN(settings.value("FN",-1).toString());
                op->setN1(settings.value("N1",-1).toString());
                op->setN2(settings.value("N2",-1).toString());
                op->setPW(settings.value("PW",-1).toString());
                operators.append(op);

                settings.endGroup();
            }

        }

        this->update_operators_table();

















}

void MainWindowCFG::set_OPERATORS(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif

    settings.beginGroup("OPERATORS");
    settings.setValue("Use",operators_use);
    settings.setValue("Count",operators.count());

        settings.endGroup();

    for(int i=0;i<operators.count();i++)
        {
           Operator* op=operators.at(i);

        QString strGroup("Operator_%1");
        strGroup=strGroup.arg(i);
        settings.beginGroup(strGroup);

        settings.setValue("FN",op->getFN());
        settings.setValue("N1",op->getN1());
        settings.setValue("N2",op->getN2());
        settings.setValue("PW",op->getPW());

        settings.endGroup();

        }
}

void MainWindowCFG::default_OPERATORS()
{
    this->operators.clear();
    this->update_operators_table();
    this->ui->operators_use_combobox->setCurrentText(" Без операторов");
    this->ui->tableWidget->setEnabled(false);
    this->ui->add_operator_button->setEnabled(false);
    this->ui->change_operator_button->setEnabled(false);
    this->ui->delete_operator_button->setEnabled(false);
    operators_use=0;
}

void MainWindowCFG::get_ASOOSD(QString /*filename*/)
{

}

void MainWindowCFG::set_ASOOSD(QString /*filename*/)
{

}

void MainWindowCFG::default_ASOOSD()
{

}







void MainWindowCFG::set_option_SD_BL_IP(UnitNode *unit)
{




    unit->setNum2(this->ui->SD_BL_IP_num_combobox->currentText().toInt());
    unit->setNum3(this->ui->port_combobox->currentText().toInt());

    if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
    {
            unit->setUdpUse(1);


    }

    else
    {
            unit->setUdpUse(0);
    }

    unit->setUdpAdress(this->ui->ipadress_lineedit->text());
    unit->setUdpPort(this->ui->UdpPort_doubleSpinBox->text().toInt());
    unit->setUdpTimeout(this->ui->timeout_doubleSpinBox->text().toInt());


    qDebug()<<"Name: "<<unit->getName()
            <<" Type:"<<this->m_TypeUnitNode.value(unit->getType())
            <<" Num2:"<<QString::number(unit->getNum2())
            <<" DK:"<<QString::number(unit->getDK())
            <<" Bazalt:"<<QString::number(unit->getBazalt())
            <<" connectblock:"<<QString::number(unit->getConnectBlock())
            <<" UdpUse:"<<QString::number(unit->getUdpUse())
            <<" UdpAdress:"<<unit->getUdpAdress();

}

void MainWindowCFG::set_option_IU_BL_IP(UnitNode *unit)
{

    unit->setNum2(this->ui->IU_BL_IP_num_combobox->currentText().toInt());
    unit->setNum3(this->ui->port_combobox->currentText().toInt());

    if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
    {
            unit->setUdpUse(1);
    }

    else
    {
            unit->setUdpUse(0);
    }

    unit->setUdpAdress(this->ui->ipadress_lineedit->text());
    unit->setUdpPort(this->ui->UdpPort_doubleSpinBox->text().toInt());
    unit->setUdpTimeout(this->ui->timeout_doubleSpinBox->text().toInt());


    unit->setUdpAdress(this->ui->ipadress_lineedit->text());
    unit->setUdpPort(this->ui->UdpPort_doubleSpinBox->text().toInt());
    unit->setUdpTimeout(this->ui->timeout_doubleSpinBox->text().toInt());
}

void MainWindowCFG::set_option_TG(UnitNode *unit)
{
unit->setNum1(this->ui->TG_adress_combobox->currentText().toInt());
unit->setNum2(this->ui->TG_U4_4A_combobox->currentText().toInt());
unit->setNum3(this->ui->port_combobox->currentText().toInt());

if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
    {
            unit->setUdpUse(1);
    }

else
    {
            unit->setUdpUse(0);
    }

unit->setUdpAdress(this->ui->ipadress_lineedit->text());
unit->setUdpPort(this->ui->UdpPort_doubleSpinBox->text().toInt());
unit->setUdpTimeout(this->ui->timeout_doubleSpinBox->text().toInt());


}

void MainWindowCFG::set_option_RLM_KRL(UnitNode *unit)
{
    unit->setNum1(this->ui->RLM_KRL_adress_combobox->currentText().toInt());

    unit->setNum3(this->ui->port_combobox->currentText().toInt());

    if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
        {
                unit->setUdpUse(1);
        }

    else
        {
                unit->setUdpUse(0);
        }

    unit->setUdpAdress(this->ui->ipadress_lineedit->text());
    unit->setUdpPort(this->ui->UdpPort_doubleSpinBox->text().toInt());
    unit->setUdpTimeout(this->ui->timeout_doubleSpinBox->text().toInt());

    if(this->ui->RLM_KRL_type_comboBox->currentText()==str_RIF_RLM)
    unit->setAdamOff(0);

    if(this->ui->RLM_KRL_type_comboBox->currentText()==str_RIF_RLM_24)
    unit->setAdamOff(1);

    if(this->ui->RLM_KRL_type_comboBox->currentText()==str_RIF_RLM_B)
    unit->setAdamOff(2);

    if(this->ui->RLM_KRL_type_comboBox->currentText()==str_RIF_KRL)
    unit->setAdamOff(3);

    if(this->ui->RLM_KRL_type_comboBox->currentText()==str_Razriv)
    unit->setAdamOff(4);

    if(this->ui->RLM_KRL_type_comboBox->currentText()==str_trassa1l)
    unit->setAdamOff(5);

}

void MainWindowCFG::set_option_RLM_C(UnitNode *unit)
{
    unit->setNum1(this->ui->RLM_C_adress_combobox->currentText().toInt());

    unit->setNum3(this->ui->port_combobox->currentText().toInt());

    if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
        {
                unit->setUdpUse(1);
        }

    else
        {
                unit->setUdpUse(0);
        }

    unit->setUdpAdress(this->ui->ipadress_lineedit->text());
    unit->setUdpPort(this->ui->UdpPort_doubleSpinBox->text().toInt());
    unit->setUdpTimeout(this->ui->timeout_doubleSpinBox->text().toInt());
}

void MainWindowCFG::set_option_BOD_T4K_M(UnitNode *unit)
{
    qDebug()<<"set_option_BOD_T4K_M";
    unit->setNum1(this->ui->BOD_T4K_M_adress_combobox->currentText().toInt());
    unit->setNum3(this->ui->port_combobox->currentText().toInt());

    if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
        unit->setUdpUse(1);
    else
        unit->setUdpUse(0);

    unit->setUdpPort(this->ui->UdpPort_doubleSpinBox->text().toInt());
    unit->setUdpAdress(this->ui->ipadress_lineedit->text());
    unit->setUdpTimeout(this->ui->timeout_doubleSpinBox->text().toInt());
}

void MainWindowCFG::set_option_Y4_T4K_M(UnitNode *unit, UnitNode* parent)
{
unit->setNum2(this->ui->Y4_T4K_M_combobox->currentText().toInt()*100);


unit->setNum1(parent->getNum1());
unit->setNum3(parent->getNum3());

}

void MainWindowCFG::set_option_DD_T4K_M(UnitNode *unit,UnitNode *parent)
{
    int val=parent->getNum2();


    unit->setNum2(this->ui->DD_T4K_M_combobox->currentText().toInt()+val-1);



    unit->setNum1(parent->getNum1());
    unit->setNum3(parent->getNum3());

}

void MainWindowCFG::set_option_BOD_SOTA(UnitNode *unit)
{
qDebug()<<"set_option_BOD_SOTA";
unit->setNum1(this->ui->BOD_SOTA_M_adress_combobox->currentText().toInt());
unit->setNum3(this->ui->port_combobox->currentText().toInt());

if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
    unit->setUdpUse(1);
else
    unit->setUdpUse(0);

unit->setUdpPort(this->ui->UdpPort_doubleSpinBox->text().toInt());
unit->setUdpAdress(this->ui->ipadress_lineedit->text());
unit->setUdpTimeout(this->ui->timeout_doubleSpinBox->text().toInt());
}

void MainWindowCFG::set_option_Y4_SOTA(UnitNode *unit, UnitNode* parent)
{
unit->setNum2(this->ui->U4_Sota_M_combobox->currentText().toInt()*100);



unit->setNum1(parent->getNum1());
unit->setNum3(parent->getNum3());

}

void MainWindowCFG::set_option_DD_SOTA(UnitNode *unit,UnitNode *parent)
{
   int val=parent->getNum2();


   unit->setNum2(this->ui->DD_Sota_M_combobox->currentText().toInt()+val-1);


   unit->setNum1(parent->getNum1());
   unit->setNum3(parent->getNum3());
//при добавлении ДД к участку к опции ДД добавляется
// 0 для участка 1
// 100 для участка 2
// 200 для участка 3
// 300 для участка 4

//Найти родителя

//Убедиться что это участок Сота-М

//Добавить значение как указано выше

}

void MainWindowCFG::set_option_BL_IP(UnitNode */*unit*/)
{

}

void MainWindowCFG::set_option_KL(UnitNode *unit)
{
    unit->setNum1(this->ui->KL_adress_combobox->currentText().toInt());
    unit->setNum2(this->ui->KL_CD_combobox->currentText().toInt());
    unit->setNum3(this->ui->port_combobox->currentText().toInt());

    if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
        unit->setUdpUse(1);
    else
        unit->setUdpUse(0);

    unit->setUdpPort(this->ui->UdpPort_doubleSpinBox->text().toInt());
    unit->setUdpAdress(this->ui->ipadress_lineedit->text());
    unit->setUdpTimeout(this->ui->timeout_doubleSpinBox->text().toInt());
}

void MainWindowCFG::set_option_ONVIF(UnitNode *unit)
{
    unit->setIcon1Path(this->ui->ONVIF_lineEdit__IPaddr->text());
    unit->setIcon2Path(this->ui->ONVIF_lineEdit__login->text());
    unit->setIcon3Path(this->ui->ONVIF_lineEdit__password->text());

}

void MainWindowCFG::set_option_STRAZH_IP(UnitNode *unit)
{
    unit->setIcon1Path(this->ui->STRAZH_IP_lineEdit__IPaddr->text());
    unit->setIcon2Path(this->ui->STRAZH_IP_lineEdit__login->text());
    unit->setIcon3Path(this->ui->STRAZH_IP_lineEdit__password->text());
    unit->setIcon4Path(this->ui->STRAZH_IP_lineEdit__IPaddres_rotary_device->text());
}

void MainWindowCFG::set_option_NET_DEV(UnitNode */*unit*/)
{
    //    unit->setIcon1Path(this->ui->NET_DEV_IP_lineEdit->text());
}

void MainWindowCFG::get_option_SSOI_SD(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString str;



    str.append("ССОИ CД");

    str.append(" Канал: ");
    str.append(QString::number(unit->getNum1()));

    str.append(" БЛ: ");
    str.append(QString::number(unit->getNum2()));


    if(unit->getNum3()==9)
    {
        str.append(" Вскрытие");

    }
    else
    {
        str.append(" СД ");
        str.append(QString::number(unit->getNum3()));

        str.append(" ");
        str.append(m_SSOI_SD_OutType.value(unit->getOutType()));

    }



    this->ui->textEdit->append(str);
}

void MainWindowCFG::set_option_SSOI_SD(UnitNode *unit)
{
    unit->setNum1(this->ui->SSOI_SD_Num1->currentText().toInt());
    unit->setNum2(this->ui->SSOI_SD_Num2->currentText().toInt());
    unit->setNum3(SSOI_SD_Num3.key(this->ui->SSOI_SD_Num3->currentText()));
    unit->setOutType(m_SSOI_SD_OutType.key(this->ui->SSOI_SD_OutType->currentText()));
}

bool MainWindowCFG::pass_to_add_SSOI_SD(UnitNode *unit, UnitNode *parrent)
{
    //СД может быть добавлен только к группе или к системе
        if((parrent->getType()!=TypeUnitNode::GROUP)&&(parrent->getType()!=TypeUnitNode::SYSTEM))
        {
            QMessageBox::critical(0,"Ошибка","СД может быть добавлен только к группе или к системе");
            return false;

        }
   //Num2 от нуля до восьми
    if(unit->getNum2()<0||unit->getNum2()>8)
        return false;


        qDebug()<<"[RS485]";
        //Контролируем отсутствие юнита с таким же Num1 Num2 и Num3

           QList<UnitNode *> List1;
           this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
           foreach(UnitNode *un, List1 )
           {
            if(un->getType()==unit->getType())
            if(un->getNum1()==unit->getNum1())
            if(un->getNum2()==unit->getNum2())
            if(un->getNum3()==unit->getNum3())
            {
                this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
                QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
                return false;
            }
           }
           return true;


}

void MainWindowCFG::get_option_SSOI_IU(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString str;



    str.append("ССОИ ИУ");

    str.append(" Канал: ");
    str.append(QString::number(unit->getNum1()));

    str.append(" БЛ: ");
    str.append(QString::number(unit->getNum2()));

    str.append(" ");
    str.append(SSOI_IU_Num3.value(unit->getNum3()));


    this->ui->textEdit->append(str);
}

void MainWindowCFG::set_option_SSOI_IU(UnitNode *unit)
{
unit->setNum1(this->ui->SSOI_IU_Num1->currentText().toInt());
unit->setNum2(this->ui->SSOI_IU_Num2->currentText().toInt());
unit->setNum3(SSOI_IU_Num3.key(this->ui->SSOI_IU_Num3->currentText()));
}

bool MainWindowCFG::pass_to_add_SSOI_IU(UnitNode *unit, UnitNode *parent)
{
    //может быть добавлен к любому датчику группе системе сморти ссои конфигуратор
    if((parent->getType()==TypeUnitNode::STRAZH_IP)||
       (parent->getType()==TypeUnitNode::ONVIF)||
       (parent->getType()==TypeUnitNode::DEVLINE)||
       (parent->getType()==TypeUnitNode::RASTRMTV)||
       (parent->getType()==TypeUnitNode::INFO_TABLO)||
       (parent->getType()==TypeUnitNode::SSOI_IU) ||
       (parent->getType()==TypeUnitNode::IU_BL_IP))

    {

        return false;

    }

    return true;

    //
}

void MainWindowCFG::get_option_ADAM(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;

    string1.append("Адам-406х/4168:");

    if(unit->getNum1()/10<1)
    string1.append("0");
    if(unit->getNum1()/100<1)
    string1.append("0");
    string1.append(QString::number(unit->getNum1()));
    string1.append("-");
    string1.append(QString::number(unit->getNum2()));


    this->ui->textEdit->append(string1);
}

void MainWindowCFG::set_option_ADAM(UnitNode *unit)
{
unit->setNum1(this->ui->ADAM_Num1->currentText().toInt());
unit->setNum2(this->ui->ADAM_Num2->currentText().toInt());
}

void MainWindowCFG::get_option_TOROS(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;

    string1.append("Торос\n");
    string1.append("Трасса: ");
    string1.append(QString::number(unit->getNum1()));
    string1.append("\n");
    string1.append("Канал: ");
    string1.append(QString::number(unit->getUdpPort()));

    this->ui->textEdit->append(string1);

}

void MainWindowCFG::set_option_TOROS(UnitNode *unit)
{
    unit->setNum1(this->ui->TOROS_Num1->currentText().toInt());


    if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
    {
            unit->setUdpUse(1);


    }

    else
    {
            unit->setUdpUse(0);
    }

    unit->setUdpAdress(this->ui->ipadress_lineedit->text());
    unit->setUdpPort(this->ui->UdpPort_doubleSpinBox->text().toInt());
    unit->setUdpTimeout(this->ui->timeout_doubleSpinBox->text().toInt());
}

bool MainWindowCFG::pass_to_add_TOROS(UnitNode *unit, UnitNode *parrent)
{
    //может быть добавлен только к группе или к системе
        if((parrent->getType()!=TypeUnitNode::GROUP)&&(parrent->getType()!=TypeUnitNode::SYSTEM))
        {
//            QMessageBox::critical(0,"Ошибка",("может быть добавлен только к группе или к системе");
//            dialog.exec();
            return false;

        }
}

void MainWindowCFG::get_option_DEVLINE(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;

    string1.append("ТВ-камера DevLine: ");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");
    string1.append("Поток: ");
    string1.append(QString::number(unit->getOutType()));

    this->ui->textEdit->append(string1);

}

void MainWindowCFG::set_option_DEVLINE(UnitNode *unit)
{
    QString str;
    str.clear();
    str.append("ТВ-Камера ");
    str.append(QString::number(this->ui->DEVLINE_Num1->value()));
    str.append("(Поток");
    str.append(this->ui->DEVLINE_OutType->currentText());
    str.append(")");
    unit->setName(str);
    unit->setNum2(this->ui->coordinate_X_doubleSpinBox_2->value());
    unit->setNum3(this->ui->coordinate_X_doubleSpinBox_3->value());
    unit->setX(this->ui->coordinate_X_doubleSpinBox_4->value());
    unit->setY(this->ui->coordinate_X_doubleSpinBox_5->value());
    unit->setNum1(this->ui->DEVLINE_Num1->value());
    unit->setOutType(this->ui->DEVLINE_OutType->currentText().toInt());

}

bool MainWindowCFG::pass_to_add_DEVLINE(UnitNode *unit, UnitNode *parrent)
{
    if((parrent->getType()==TypeUnitNode::STRAZH_IP)||
       (parrent->getType()==TypeUnitNode::ONVIF)||
       (parrent->getType()==TypeUnitNode::DEVLINE)||
       (parrent->getType()==TypeUnitNode::RASTRMTV)||
       (parrent->getType()==TypeUnitNode::INFO_TABLO)||
       (parrent->getType()==TypeUnitNode::SSOI_IU) ||
       (parrent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }

    //Если общий родитель
    QModelIndex ind = this->modelTreeUN->findeIndexUN(parrent);


    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);

    foreach(UnitNode *un, List1 )
    {

       qDebug()<<".";
//     qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
       QModelIndex index=this->modelTreeUN->findeIndexUN(un);
       QModelIndex un_parent_index= this->modelTreeUN->parent(index);

     if(ind==un_parent_index)
      {
         qDebug()<<"[+]";

    //     unit->setNum1(this->ui->DEVLINE_Num1->value());
    //     unit->setOutType(this->ui->DEVLINE_OutType->currentText().toInt());
         if(un->getType()==unit->getType())
         if(un->getNum1()==unit->getNum1())
         if(un->getOutType()==unit->getOutType())
         {
             this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
             QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
             return false;

         }
      }
    }

    return true;
}

void MainWindowCFG::get_option_RASTRMTV(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString str;

    str.append("камера РАСТР-М-ТВ ");
    str.append("\n");
    str.append(unit->getIcon2Path());
    str.append("(");
    str.append(unit->getIcon1Path());
    str.append(")");
    str.append(" - ");
    str.append(QString::number(unit->getNum3()));


    this->ui->textEdit->append(str);

}

void MainWindowCFG::set_option_RASTRMTV(UnitNode *unit)
{
unit->setIcon1Path(mSerNum_Name.value(this->ui->RASTRMTV_Name_SerNum->currentText()).SerNum);
unit->setIcon2Path(mSerNum_Name.value(this->ui->RASTRMTV_Name_SerNum->currentText()).Name);
unit->setNum3(this->ui->RASTRMTV_Num3->currentText().toInt());
}

bool MainWindowCFG::pass_to_add_RASTRMTV(UnitNode *unit, UnitNode *parrent)
{
    qDebug()<<"RASTRMTV";
    if((parrent->getType()==TypeUnitNode::STRAZH_IP)||
       (parrent->getType()==TypeUnitNode::ONVIF)||
       (parrent->getType()==TypeUnitNode::DEVLINE)||
       (parrent->getType()==TypeUnitNode::RASTRMTV)||
       (parrent->getType()==TypeUnitNode::INFO_TABLO)||
       (parrent->getType()==TypeUnitNode::SSOI_IU) ||
       (parrent->getType()==TypeUnitNode::IU_BL_IP))
    {

        return false;

    }

    if(this->ui->RASTRMTV_Name_SerNum->currentText()=="не определено")
    {
        QMessageBox::critical(0,"Ошибка","Устройство не определено");
        return false;

    }




    return true;
}

void MainWindowCFG::get_option_INFO_TABLO(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;

    string1.append("Инф. табло");

    string1.append(" Кан:");

    string1.append(QString::number(this->ui->SSOIwgt->getPort()));

    string1.append(" Участок: ");

    string1.append(QString::number( unit->getNum2()));



    this->ui->textEdit->append(string1);
    qDebug()<<"[+]"<<string1;
}

void MainWindowCFG::set_option_INFO_TABLO(UnitNode *unit)
{
    unit->setNum2(this->ui->TABLO_Num2->currentText().toInt());
    QString name;
    name.clear();
    name.append("Участок: ");
    name.append(this->ui->TABLO_Num2->currentText());
    unit->setName(name);
}

bool MainWindowCFG::pass_to_add_INFO_TABLO(UnitNode *unit, UnitNode *parrent)
{
    if(parrent->getType()!=TypeUnitNode::GROUP)
    if(parrent->getType()!=TypeUnitNode::SYSTEM)
    {
        QMessageBox::critical(0,"Ошибка"," может быть добавлен только к группе");
        return false;

    }
    //проверка по участку (Num2)
    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
    foreach(UnitNode *un, List1 )
    {

     if((un->getNum2()==unit->getNum2()))
     {

         this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
         QMessageBox::critical(0,"Ошибка","Такой обьект уже существует");
         return false;
     }


    }
}

void MainWindowCFG::save_ini(QString filename)
{
    qDebug()<<"save ini";

    QSettings settings(filename,QSettings::IniFormat);

#if (defined (_WIN32) || defined (_WIN64))
    settings.setIniCodec( "Windows-1251" );
#else
  //  settings.setIniCodec( "UTF-8" );
    settings.setIniCodec( QTextCodec::codecForLocale() );
#endif
 //   settings.setIniCodec( QTextCodec::codecForLocale() );
    /*
#if (defined (_WIN32) || defined (_WIN64))
    settings.setIniCodec( "Windows-1251" );
#else
    settings.setIniCodec( "UTF-8" );
#endif
    */
//   foreach(UnitNode* unit,this->modelTreeUN->listItemUN)
    QList<UnitNode *> List;
    this->modelTreeUN->getListFromModel(List);

    qDebug()<<"[count] "<<List.count();




    /*
        set_PARAMS(filename);
        set_RIF(filename);
        set_SSOI(filename);
        set_RASTRMTV(filename);
        set_INTEGRATION(filename);
        set_SQL(filename);
        set_RASTR(filename);
        set_ADAM4068(filename);
        set_TABLO(filename);
        set_RASTRMSSOI(filename);
        set_BACKUP(filename);
        set_PORT(filename);
        set_OPERATORS(filename);
        set_ASOOSD(filename);

        */

settings.beginGroup("PARAMS");
settings.setValue("PlanType",map_PARAMS_PlanType.key(this->ui->PlanType_comboBox->currentText()));
settings.setValue("SoundType",map_PARAMS_SoundType.key(this->ui->SoundType_comboBox->currentText()));
settings.setValue("AutoStart",map_PARAMS_AutoStart.key(this->ui->PARAMS_AutoStart_comboBox->currentText()));
settings.endGroup();

    qDebug()<<"PARAMS";

settings.beginGroup("RIF");
for(int i=0; i<this->rif_model->rowCount();i++){

 //   ComPort* port= static_cast< ComPort*>(index.internalPointer());
    QModelIndex index = this->rif_model->index(i,1,QModelIndex());
    int speed = this->rif_model->data(index,Qt::DisplayRole).toInt();
    index = this->rif_model->index(i,2,QModelIndex());
    int interval = this->rif_model->data(index,Qt::DisplayRole).toInt();
    if(speed!=4800){
        QString str="RifPortSpeed%1";
        str=str.arg(i+1);
    settings.setValue(str,speed);
    }
    if(interval!=50){
        QString str="RifPortInterval%1";
        str=str.arg(i+1);
    settings.setValue(str,interval);
    }
}
settings.setValue("AutoDK", this->ui->RIF_AutoDK_comboBox->currentIndex());
settings.setValue("TochkaDirectionInterval", this->ui->RIF_TochkaDirectionInterval_doubleSpinBox->value());
settings.endGroup();

    qDebug()<<"RIF";

settings.beginGroup("SSOI");
settings.setValue("Version",this->ui->SSOIwgt->get_Version());




settings.setValue("SsoiM_PortNum1",this->ui->SSOIwgt->get_SsoiM_PortNum1());
settings.setValue("SsoiM_Interval1",this->ui->SSOIwgt->get_SsoiM_Interval1());
settings.setValue("SsoiM_Interval_1",this->ui->SSOIwgt->get_SsoiM_Interval_1());
settings.setValue("SsoiM_MaxErrCnt1",this->ui->SSOIwgt->get_SsoiM_MaxErrCnt1());

settings.setValue("SsoiM_PortNum2",this->ui->SSOIwgt->get_SsoiM_PortNum2());
settings.setValue("SsoiM_Interval2",this->ui->SSOIwgt->get_SsoiM_Interval2());
settings.setValue("SsoiM_Interval_2",this->ui->SSOIwgt->get_SsoiM_Interval_2());
settings.setValue("SsoiM_MaxErrCnt2",this->ui->SSOIwgt->get_SsoiM_MaxErrCnt2());

settings.setValue("SsoiM_PortNum3",this->ui->SSOIwgt->get_SsoiM_PortNum3());
settings.setValue("SsoiM_Interval3",this->ui->SSOIwgt->get_SsoiM_Interval3());
settings.setValue("SsoiM_Interval_3",this->ui->SSOIwgt->get_SsoiM_Interval_3());
settings.setValue("SsoiM_MaxErrCnt3",this->ui->SSOIwgt->get_SsoiM_MaxErrCnt3());

settings.setValue("SsoiM_PortNum4",this->ui->SSOIwgt->get_SsoiM_PortNum4());
settings.setValue("SsoiM_Interval4",this->ui->SSOIwgt->get_SsoiM_Interval4());
settings.setValue("SsoiM_Interval_4",this->ui->SSOIwgt->get_SsoiM_Interval_4());
settings.setValue("SsoiM_MaxErrCnt4",this->ui->SSOIwgt->get_SsoiM_MaxErrCnt4());

settings.setValue("SsoiAutoDkUse",this->ui->SSOIwgt->get_SsoiAutoDkUse());
settings.setValue("SsoiMOprosVariant",this->ui->SSOIwgt->get_SsoiMOprosVariant());
settings.setValue("SsoiFixNewWarning",this->ui->SSOIwgt->get_SsoiFixNewWarning());
settings.setValue("SsoiM_PortSpeed",this->ui->SSOIwgt->get_SsoiM_PortSpeed());


settings.endGroup();
    qDebug()<<"SSOI";

settings.beginGroup("RASTRMTV");
settings.setValue("Use",this->ui->RASTR_wgt->getUse());
settings.setValue("Name",this->ui->RASTR_wgt->getName());
settings.setValue("Port",this->ui->RASTR_wgt->getPort());
settings.setValue("Port2",this->ui->RASTR_wgt->getPort2());
settings.setValue("KeepAliveInterval",this->ui->RASTR_wgt->getKeepAliveInterval());
settings.setValue("ThermostatUse",this->ui->RASTR_wgt->getThermostatUse());
settings.setValue("dtInfoToJpg",this->ui->RASTR_wgt->getDtInfoToJpg());
settings.setValue("AutoDkPeriod",this->ui->RASTR_wgt->getAutoDkPeriod());


settings.endGroup();
    qDebug()<<"RASTRMTV";

settings.beginGroup("INTEGRATION");
settings.setValue("Use",map_INTEGRATION_Use.key(this->ui->INTEGRATION_Use_comboBox->currentText()));
settings.setValue("Host",this->ui->INTEGRATION_Host_lineEdit->text());
settings.setValue("Port",this->ui->INTEGRATION_Port_doubleSpinBox->value());
settings.setValue("Port2",this->ui->INTEGRATION_Port2_doubleSpinBox->value());
settings.setValue("KeepAliveInterval",this->ui->INTEGRATION_KeepAliveInterval_doubleSpinBox->value());
settings.setValue("DevLine",this->ui->INTEGRATION_DevLine_filepath_lineEdit->text());
settings.endGroup();
   qDebug()<<"INTEGRATION";

int res=0;
    if(this->ui->SQL_type_comboBox->currentText()=="MySQL")
    {
      settings.beginGroup("PostgresSQL");
      settings.setValue("Use", 0);
      settings.endGroup();

      settings.beginGroup("MYSQL");
      settings.setValue("Use", 1);
      res=1;
    }
    if(this->ui->SQL_type_comboBox->currentText()=="PostgresSQL")
    {
      settings.beginGroup("MYSQL");
      settings.setValue("Use", 0);
      settings.endGroup();

      settings.beginGroup("PostgresSQL");
      settings.setValue("Use", 1);
      res=1;



    }
    if(res==1)
    {


      settings.setValue("Host", this->ui->SQL_server_lineEdit->text());
      settings.setValue("Port", this->ui->SQL_port_doubleSpinBox->text());
      settings.setValue("Login", this->ui->SQL_login_lineEdit->text());
      settings.setValue("Password", this->XOR_Crypt(this->ui->SQL_password_lineEdit->text()));
      settings.setValue("DbName", this->ui->SQL_database_lineEdit->text());

      if(this->ui->SQL_P1_checkBox->isChecked())
      settings.setValue("P1", 1);
      else
      settings.setValue("P1", 0);


      if(this->ui->SQL_P2_checkBox->isChecked())
      settings.setValue("P2", 1);
      else
      settings.setValue("P2", 0);

      if(this->ui->SQL_AutoDbStart_checkBox->isChecked())
      settings.setValue("AutoDbStart", 1);
      else
      settings.setValue("AutoDbStart", 0);


      settings.setValue("AutoDbStartHour",this->ui->SQL_AutoDbStartHour_doubleSpinBox->value() );
      settings.setValue("AutoDbStartMinute",this->ui->SQL_AutoDbStartMinute_doubleSpinBox->value() );

      settings.endGroup();
    }
    else
    {
        settings.beginGroup("MYSQL");
        settings.setValue("Use", 0);
        settings.endGroup();
        settings.beginGroup("PostgresSQL");
        settings.setValue("Use", 0);
        settings.endGroup();
    }

   qDebug()<<"SQL";






    settings.beginGroup("ADAM4068");
    settings.setValue("Port",this->ui->ADAM_wgt->get_Port());
    settings.setValue("Interval",this->ui->ADAM_wgt->get_Interval());
    settings.endGroup();
       qDebug()<<"ADAM4068";

    settings.beginGroup("TABLO");
    settings.setValue("Port",this->ui->SSOIwgt->getPort());
    settings.setValue("Blinking",this->ui->SSOIwgt->getBlinking());
    settings.endGroup();
       qDebug()<<"TABLO";

    settings.beginGroup("BACKUP");
    settings.setValue("BackupPath",this->ui->BACKUP_BackupPath_lineedit->text());
    settings.setValue("MaxBdStringCnt",map_BACKUP_MaxBdStringCnt.key(this->ui->BACKUP_MaxBdStringCnt_comboBox->currentText()));
    settings.endGroup();
       qDebug()<<"BACKUP";


    settings.beginGroup("OPERATORS");
    settings.setValue("Use",operators_use);
    settings.setValue("Count",operators.count());

        settings.endGroup();


    for(int i=0;i<operators.count();i++)
        {
        Operator* op=operators.at(i);
        QString strGroup("Operator_%1");
        strGroup=strGroup.arg(i);
        settings.beginGroup(strGroup);
        settings.setValue("FN",op->getFN());
        settings.setValue("N1",op->getN1());
        settings.setValue("N2",op->getN2());
        settings.setValue("PW",op->getPW());
        settings.endGroup();
        }
       qDebug()<<"OPERATORS";

    settings.beginGroup("TREE");
    settings.setValue("Count",List.count()-1);

    settings.endGroup();


for(int i=1;i<List.count();i++)
    {
    UnitNode* unit=List.at(i);

        QString strGroup("Obj_%1");
        strGroup=strGroup.arg(i);

        settings.beginGroup(strGroup);

        settings.setValue("Type",unit->getType());

        settings.setValue("Num1", QString::number(unit->getNum1()));
        settings.setValue("Num2", QString::number(unit->getNum2()));
        settings.setValue("Num3", QString::number(unit->getNum3()));

        settings.setValue("Level",unit->getLevel());

        settings.setValue("Name", unit->getName());

        settings.setValue("IconVisible", QString::number(unit->getIconVisible()));

         settings.setValue("X", QString::number(unit->getX()));
         settings.setValue("Y", QString::number(unit->getY()));

        settings.setValue("DK", QString::number(unit->getDK()));
        settings.setValue("Bazalt", QString::number(unit->getBazalt()));
        settings.setValue("Metka", QString::number(unit->getMetka()));

        settings.setValue("Razriv", QString::number(unit->getRazriv()));

        settings.setValue("AdamOff", QString::number(unit->getAdamOff()));
        settings.setValue("AlarmMsgOn", QString::number(unit->getAlarmMsgOn()));

        settings.setValue("ConnectBlock", QString::number(unit->getConnectBlock()));
        settings.setValue("OutType", QString::number(unit->getOutType()));
        settings.setValue("asoosd_kk", QString::number(unit->getAsoosd_kk()));
        settings.setValue("asoosd_nn", QString::number(unit->getAsoosd_nn()));

        settings.setValue("Description", unit->getDescription());

        settings.setValue("lan",QString::number(unit->getLan()));
        settings.setValue("lon", unit->getLon());

        settings.setValue("UdpUse", QString::number(unit->getUdpUse()));
        settings.setValue("UdpAdress", unit->getUdpAdress());

        settings.setValue("UpdPort", QString::number(unit->getUdpPort()));
        settings.setValue("UdpTimeout", QString::number(unit->getUdpTimeout()));

        if(unit->getIcon1Path()!="")
             settings.setValue("Icon1Path", unit->getIcon1Path());

        if(unit->getIcon2Path()!="")
             settings.setValue("Icon2Path", unit->getIcon2Path());

        if(unit->getIcon3Path()!="")
             settings.setValue("Icon3Path", unit->getIcon3Path());

        if(unit->getIcon4Path()!="")
             settings.setValue("Icon4Path", unit->getIcon4Path());
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

    if(unit->getIcon1Path()!="")
         settings->setValue("Icon1Path", unit->getIcon1Path());

    if(unit->getIcon2Path()!="")
         settings->setValue("Icon2Path", unit->getIcon2Path());

    if(unit->getIcon3Path()!="")
         settings->setValue("Icon3Path", unit->getIcon3Path());

    if(unit->getIcon4Path()!="")
         settings->setValue("Icon4Path", unit->getIcon4Path());

}

void MainWindowCFG::save_option_SD_BL_IP(QSettings* settings, UnitNode *unit)
{
          settings->setValue("Num2", QString::number(unit->getNum2()));
          settings->setValue("DK", QString::number(unit->getDK()));
          settings->setValue("Bazalt", QString::number(unit->getBazalt()));
          settings->setValue("connectblock", QString::number(unit->getConnectBlock()));
          settings->setValue("UdpUse", QString::number(unit->getUdpUse()));
          settings->setValue("UdpAdress", unit->getUdpAdress());



}

void MainWindowCFG::save_option_BOD_SOTA(QSettings */*settings*/, UnitNode */*unit*/)
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
/*
void MainWindowCFG::on_BOD_SOTA_M_type_combobox_currentTextChanged(const QString &arg1)
{

    if(this->ui->UDP_RS485_combobox->currentText()==" UDP")
     this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->UDP);
    else
     this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->BOD_RS485);

}*/

void MainWindowCFG::on_pushButton_9_clicked()
{
QList<UnitNode *> List;
this->modelTreeUN->getListFromModel(List, this->modelTreeUN->rootItemUN);



}

void MainWindowCFG::on_pushButton_moveUp_clicked()
{
    QModelIndex current=this->ui->treeView->currentIndex();
    int current_row=this->ui->treeView->currentIndex().row();
    qDebug()<<QString::number(current_row);

this->modelTreeUN->moveUNUp(current);





}

void MainWindowCFG::on_pushButton_moveDown_clicked()
{
    QModelIndex current=this->ui->treeView->currentIndex();
    int current_row=this->ui->treeView->currentIndex().row();
    qDebug()<<QString::number(current_row);


        this->modelTreeUN->moveUNDown(current);

}



void MainWindowCFG::on_treeView_customContextMenuRequested(const QPoint &pos)
{

    menu->clear();
    qDebug()<<"[ContextMenuRequested]";
    QModelIndex index = ui->treeView->indexAt(pos);
        if (index.isValid()) {
            UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
            this->get_option(un);
            if(un->getType()!=TypeUnitNode::SYSTEM)
            if(un->getType()!=TypeUnitNode::GROUP)
            menu->addAction(action_open_edit_menu);

            switch(un->getType())
            {
            case TypeUnitNode::SYSTEM:
                menu->addAction(action_open_device_tree);
                menu->addAction(action_close_device_tree);

                menu->exec(ui->treeView->viewport()->mapToGlobal(pos));
            break;

            case TypeUnitNode::SD_BL_IP:

                menu->addAction(action_setDK);
                if(un->getDK()==0)
                {
                    qDebug()<<"[0]";
                    action_setDK->setChecked(false);
                }
                else
                {
                    qDebug()<<"[1]";
                   action_setDK->setChecked(true);
                }
               if(un->getNum2()==1||un->getNum2()==2||un->getNum2()==3)
                menu->addAction(action_YZ_MONOLIT);

               if(un->getBazalt()==0)
               {
                   qDebug()<<"[0]";
                   action_YZ_MONOLIT->setChecked(false);
               }
               else
               {
                   qDebug()<<"[1]";
                  action_YZ_MONOLIT->setChecked(true);
               }

               menu->addAction(action_setAlarmMsgOn);

                  if(un->getAlarmMsgOn()==0)
                  {
                      qDebug()<<"[0]";
                      action_setAlarmMsgOn->setChecked(false);
                  }
                  else
                  {
                      qDebug()<<"[1]";
                   }
               menu->exec(ui->treeView->viewport()->mapToGlobal(pos));

            break;

            case TypeUnitNode::IU_BL_IP:
                action_setAlarmMsgOn->setChecked(true);
                action_setAdamOff_off->setChecked(false);
                action_setAdamOff_5_sec->setChecked(false);
                action_setAdamOff_10_sec->setChecked(false);
                action_setAdamOff_30_sec->setChecked(false);
                action_setAdamOff_1_min->setChecked(false);
                action_setAdamOff_5_min->setChecked(false);
                action_setAdamOff_10_min->setChecked(false);
                action_setAdamOff_20_min->setChecked(false);
                action_setAdamOff_30_min->setChecked(false);
                action_setAdamOff_1_hour->setChecked(false);
                menu->addMenu(menuAdamOff);
                switch(un->getAdamOff())
                {
                case 0:
                action_setAdamOff_off->setChecked(true);
                break;

                case 1:
                action_setAdamOff_5_sec->setChecked(true);
                break;

                case 2:
                action_setAdamOff_10_sec->setChecked(true);
                break;

                case 3:
                action_setAdamOff_30_sec->setChecked(true);
                break;

                case 4:
                action_setAdamOff_1_min->setChecked(true);
                break;

                case 5:
                action_setAdamOff_5_min->setChecked(true);
                break;

                case 6:
                action_setAdamOff_10_min->setChecked(true);
                break;

                case 7:
                action_setAdamOff_20_min->setChecked(true);
                break;

                case 8:
                action_setAdamOff_30_min->setChecked(true);
                break;

                case 9:
                action_setAdamOff_1_hour->setChecked(true);
                break;
                }
               menu->exec(ui->treeView->viewport()->mapToGlobal(pos));

            break;

            default:
                if(un->getType()!=TypeUnitNode::SYSTEM)
                if(un->getType()!=TypeUnitNode::GROUP)
                menu->exec(ui->treeView->viewport()->mapToGlobal(pos));
            break;
            }








        }
}





void MainWindowCFG::on_operators_use_combobox_currentTextChanged(const QString &arg1)
{
    if(arg1==" Без операторов")
    {

      qDebug()<<"[без операторов]";
      this->ui->tableWidget->setEnabled(false);
      this->ui->add_operator_button->setEnabled(false);
      this->ui->change_operator_button->setEnabled(false);
      this->ui->delete_operator_button->setEnabled(false);
      operators_use=0;
    }
    if(arg1==" С операторами")
    {
      qDebug()<<"[с операторами]";
            this->ui->tableWidget->setEnabled(true);
      this->ui->add_operator_button->setEnabled(true);
      this->ui->change_operator_button->setEnabled(true);
      this->ui->delete_operator_button->setEnabled(true);
      operators_use=1;
    }

}




void MainWindowCFG::on_add_operator_button_clicked()
{
//  Operator* op = new Operator();
   opt_tbl_request=1;
    op_f.clear_operator_data_on_form();
   op_f.show();
 //   op->setN1("Ivan");
 //   op->setN2("Ivanovich");
 //   op->setFN("Ivanoff");
 //   operators.append(op);

 //   update_operators_table();
}

void MainWindowCFG::on_tableWidget_cellClicked(int /*row*/, int /*column*/)
{

}

void MainWindowCFG::on_delete_operator_button_clicked()
{
    int row = this->ui->tableWidget->currentRow();
    operators.removeAt(row);
    update_operators_table();

}

void MainWindowCFG::get_from_op_f(QString FN, QString N1, QString N2, QString ps)
{

    Operator* op=new Operator();
    op->setFN(FN);
    op->setN1(N1);
    op->setN2(N2);
    op->setPW(ps);

    switch(opt_tbl_request)
    {
    case 1:
    operator_add(op);
    break;

    case 2:
    operator_edit(op);
    break;

    case 3:
    operator_delete();
    break;


    }

}

void MainWindowCFG::on_change_operator_button_clicked()
{
    opt_tbl_request=2;


    int index = this->ui->tableWidget->currentRow();
    qDebug()<<index;
    if(0<=index<operators.size())
    {
        op_f.set_operator_data_on_form(operators.at(index)->getFN(),
                                       operators.at(index)->getN1(),
                                       operators.at(index)->getN2(),
                                       operators.at(index)->getPW());
        op_f.show();

    }



}











/*



void MainWindowCFG::on_RLM_C_UDP_RS485_combobox_currentTextChanged(const QString &arg1)
{
    if(this->ui->RLM_C_UDP_RS485_combobox->currentText()==" UDP")
     this->ui->RLM_C_UDP_RS485_stacked->setCurrentWidget(this->ui->RLM_C_UDP);
    else
    {
        qDebug()<<"[!!!!!!!!!!!!!!!]";
     this->ui->RLM_C_UDP_RS485_stacked->setCurrentWidget(this->ui->RLM_C_RS485);
    }
}
*/
void MainWindowCFG::on_UDP_RS485_combobox_currentTextChanged(const QString &arg1)
{
    qDebug()<<"[!!!!!!!!!!!!!!!]";
    if(arg1==" UDP")
     this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->UDP);
    else
    {

     this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    }
}


void MainWindowCFG::on_SQL_find_server_pushButton_clicked()
{
    this->ui->SQL_server_lineEdit->setText(QHostInfo::localHostName());
}

void MainWindowCFG::on_SQL_connect_pushButton_clicked()
{
    if(this->ui->SQL_type_comboBox->currentText()=="MySQL")
    {
    qDebug()<<"connect to MySQL";
    db_mysql = QSqlDatabase::addDatabase("QMYSQL");
    qDebug()<<"db_mysql.driver() "<<db_mysql.driver()<<"; db_mysql.driverName() "<<db_mysql.driverName();
    db_mysql.setHostName(this->ui->SQL_server_lineEdit->text());
//    db.setDatabaseName("QWERTY");
    db_mysql.setUserName(this->ui->SQL_login_lineEdit->text());
    db_mysql.setPassword(this->ui->SQL_password_lineEdit->text());
    qDebug()<<"password "<<this->ui->SQL_password_lineEdit->text();
    if (!db_mysql.open()){
        QString err =db_mysql.lastError().text();
        QString drv;
        drv.append(err);
        drv.append("; ");
        qDebug()<<err;

  QStringListIterator it(db_mysql.drivers());
       while(it.hasNext()) {
               drv.append(it.next());
               drv.append(";");
           }
        QMessageBox::critical(0,"Ошибка",(drv));

     //   return false;

    }
    else{
        qDebug()<<"PROFIT";
        this->db_f.find_rif_db(db_mysql);
        db_f.show();
    }





    }
    if(this->ui->SQL_type_comboBox->currentText()=="PostgresSQL")
    {
    qDebug()<<"connect to PostgresSQL";

    db_psql = QSqlDatabase::addDatabase("QPSQL");
    qDebug()<<"db_mysql.driver() "<<db_psql.driver()<<"; db_mysql.driverName() "<<db_psql.driverName();
    db_psql.setHostName(this->ui->SQL_server_lineEdit->text());
//    db.setDatabaseName("QWERTY");
    db_psql.setUserName(this->ui->SQL_login_lineEdit->text());
    db_psql.setPassword(this->ui->SQL_password_lineEdit->text());
    db_psql.setDatabaseName("postgres");
    if (!db_psql.open()){
        qDebug()<<db_psql.lastError().text();
    }
    else{
        qDebug()<<"PROFIT";
        this->db_f.find_rif_db(db_psql);
        db_f.show();
    }
    }
}

void MainWindowCFG::create_db(QString db_name)
{
    qDebug()<<"[create_db]";
    if(this->ui->SQL_type_comboBox->currentText()=="MySQL")
    {
    qDebug()<<"[mysql]";

    QSqlQuery query(db_mysql);



    QString sql_cmd="CREATE DATABASE ";
    sql_cmd.append(db_name);

    query.prepare(sql_cmd);
    query.exec();
    this->db_f.find_rif_db(db_mysql);
    }
    if(this->ui->SQL_type_comboBox->currentText()=="PostgresSQL")
    {
        qDebug()<<"[psql]";
        QSqlQuery query(db_psql);



        QString sql_cmd="CREATE DATABASE ";
        sql_cmd.append(db_name);
       sql_cmd.append(";");
        query.prepare(sql_cmd);

        qDebug()<<sql_cmd;
        query.exec(sql_cmd);
        this->db_f.find_rif_db(db_psql);

    }

}

void MainWindowCFG::drop_db(QString db_name)
{
if(this->ui->SQL_type_comboBox->currentText()=="MySQL")
{
qDebug()<<"drop "<<db_name;
QSqlQuery query(db_mysql);

QString sql_cmd="DROP DATABASE ";
sql_cmd.append(db_name);

query.prepare(sql_cmd);
query.exec();
  this->db_f.find_rif_db(db_mysql);


}
if(this->ui->SQL_type_comboBox->currentText()=="PostgresSQL")
{
QSqlQuery query(db_psql);

QString sql_cmd="DROP DATABASE ";
sql_cmd.append(db_name);
sql_cmd.append(";");
query.prepare(sql_cmd);

qDebug()<<sql_cmd;
query.exec(sql_cmd);
  this->db_f.find_rif_db(db_psql);


}


if(this->ui->SQL_database_lineEdit->text()==db_name){
   this->ui->SQL_database_lineEdit->setText("");
}


}

void MainWindowCFG::use_db(QString db_name)
{
MySQL_unit.SQL_database=db_name;
this->ui->SQL_database_lineEdit->setText(db_name);
}

void MainWindowCFG::on_INTEGRATION_pushButton_clicked()
{
        this->ui->INTEGRATION_Host_lineEdit->setText(QHostInfo::localHostName());
}

void MainWindowCFG::on_BACKUP_pushButton_clicked()
{
    QString patch=QFileDialog::getExistingDirectory(this, "Выбрать каталог","");
     qDebug()<<"patch = "<<patch;
     this->ui->BACKUP_BackupPath_lineedit->setText(patch);
}



void MainWindowCFG::coordinate_menu(bool visible, bool active, int x, int y, QString text)
{

    if(visible)
    this->ui->stackedWidget_2->setCurrentWidget(this->ui->coordinates_for_all);
    else
    this->ui->stackedWidget_2->setCurrentWidget(this->ui->nothing);
    if(visible)
    {
        this->ui->coordinate_X_doubleSpinBox->setValue(x);
        this->ui->coordinate_Y_doubleSpinBox->setValue(y);
        this->ui->Dop_info_description_lineedit->setText(text);


    }
}

void MainWindowCFG::coordinate_devline(bool active, int x, int y, int x1, int y1)
{

    this->ui->stackedWidget_2->setCurrentWidget(this->ui->devline_coordinates);

this->ui->coordinate_X_doubleSpinBox_2->setValue(x);
this->ui->coordinate_X_doubleSpinBox_3->setValue(y);
this->ui->coordinate_X_doubleSpinBox_4->setValue(x1);
this->ui->coordinate_X_doubleSpinBox_5->setValue(y1);

        this->ui->devline_xy_pushButton->setEnabled(active);

}

/*
QList<udev_device*> listDevices()
{
    struct udev_enumerate *enu = ::udev_enumerate_new(m_udev);
    struct udev_list_entry *cur;
    ::udev_enumerate_add_match_subsystem(enu, "block");
    ::udev_enumerate_add_match_property(enu, "ID_BUS", "usb");
    QList<udev_device*> list;

    ::udev_enumerate_scan_devices(enu);
    udev_list_entry_foreach(cur, ::udev_enumerate_get_list_entry(enu)) {
        struct udev_device* device = ::udev_device_new_from_syspath(m_udev, ::udev_list_entry_get_name(cur));
        if(device != Q_NULLPTR) {
        // для определения точки монтирования (/dev/sdb, /dev/sdb1, ...)
            // const auto* devname = ::udev_device_get_property_value(device, "DEVNAME");
            list << device;
        }
    }
    ::udev_enumerate_unref(enu);
    return list;
}
*/

void MainWindowCFG::on_pushButton_5_clicked()
{
    QModelIndex ind = this->ui->treeView->currentIndex();

    if(ind.isValid())
    {
    UnitNode *unit = static_cast<UnitNode*>(ind.internalPointer());
    unit->setLan(this->ui->coordinate_X_doubleSpinBox->value());
    unit->setLon(this->ui->coordinate_Y_doubleSpinBox->value());
    unit->setDescription(ui->Dop_info_description_lineedit->text());
    }
}

void MainWindowCFG::on_uType_combobox_activated(const QString &arg1)
{
    qDebug()<<"[activated]";

    this->ui->stackedWidget_2->setCurrentWidget(this->ui->nothing);
    this->ui->UDP_RS485_Widget->setVisible(false);

    int type=m_TypeUnitNode.key(arg1);
    this->change_object_menu(type);
    this->object_menu_set_settings_default(type);
    this->object_menu_set_enabled_for_edit(false);

}

void MainWindowCFG::on_SQL_type_comboBox_currentTextChanged(const QString &arg1)
{
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!";


        if(arg1=="MySQL")
        {

            this->ui->SQL_server_lineEdit->setText("localhost");


            this->ui->SQL_port_doubleSpinBox->setValue(3306);

            this->ui->SQL_login_lineEdit->setText("root");

            this->ui->SQL_password_lineEdit->setText("");


        }
        if(arg1=="PostgresSQL")
        {
            this->ui->SQL_server_lineEdit->setText("localhost");


            this->ui->SQL_port_doubleSpinBox->setValue(5432);

            this->ui->SQL_login_lineEdit->setText("postgres");

            this->ui->SQL_password_lineEdit->setText("");
        }
        if(arg1=="Выкл")
        {
            this->ui->SQL_server_lineEdit->setText("");


            this->ui->SQL_port_doubleSpinBox->setValue(0);

            this->ui->SQL_login_lineEdit->setText("");

            this->ui->SQL_password_lineEdit->setText("");
        }

}


void MainWindowCFG::on_INTEGRATION_DevLine_pushButton_clicked()
{
    QString patch=QFileDialog::getOpenFileName(this, "open file","","*observer.exe");
     qDebug()<<"patch = "<<patch;
     if(patch!="")
     {
         qDebug()<<"[PROFIT]";
         this->ui->INTEGRATION_DevLine_filepath_lineEdit->setText(patch);

     }

}

void MainWindowCFG::on_pushButton_6_clicked()
{
    qDebug()<<"++++++++++++++++++++++++";
   add_unit();
}

void MainWindowCFG::on_devline_xy_pushButton_clicked()
{
    QModelIndex ind = this->ui->treeView->currentIndex();
    if(ind.isValid())
    {
    UnitNode *unit = static_cast<UnitNode*>(ind.internalPointer());
    if(unit->getType()==TypeUnitNode::DEVLINE)
    {
        unit->setNum2(this->ui->coordinate_X_doubleSpinBox_2->value());
        unit->setNum3(this->ui->coordinate_X_doubleSpinBox_3->value());
        unit->setX(this->ui->coordinate_X_doubleSpinBox_4->value());
        unit->setY(this->ui->coordinate_X_doubleSpinBox_5->value());
    }


    }
}

























void MainWindowCFG::on_uType_combobox_currentTextChanged(const QString &arg1)
{
        qDebug()<<"[currentTextChanged]";
    this->ui->pushButton_4->setDisabled(true);
    this->ui->stackedWidget_2->setCurrentWidget(this->ui->nothing);
    this->ui->UDP_RS485_Widget->setVisible(false);

    int type=m_TypeUnitNode.key(arg1);
    this->change_object_menu(type);


}
