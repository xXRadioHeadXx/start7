#include "MainWindowCFG.h"
#include "ui_MainWindowCFG.h"
#include <global.hpp>

#include "QFileDialog"
#include <QErrorMessage>
#include <QStorageInfo>

#ifdef _WIN32 || _WIN_64
#include <Windows.h>
#endif


MainWindowCFG::MainWindowCFG(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowCFG)
{

    ui->setupUi(this);
this->ui->groupBox_4->setVisible(false);

    for (auto volume : QStorageInfo::mountedVolumes()) {
           qDebug() << "Name:" << volume.name();
           qDebug() << "Display name:" << volume.displayName();
           qDebug() << "Device:" << volume.device();
           qDebug() << "Root path:" << volume.rootPath();
           qDebug() << "File system type:" << volume.fileSystemType();
           qDebug() << "Is valid?" << (volume.isValid() ? "yes" : "no");
           qDebug() << "Is root?" << (volume.isRoot() ? "yes" : "no");
           qDebug() << "Is ready?" << (volume.isReady() ? "yes" : "no");
           qDebug() << "Is read only?" << (volume.isReadOnly() ? "yes" : "no");
           qDebug() << "Bytes available:" << volume.bytesAvailable();
           qDebug() << "Bytes free:" << volume.bytesFree();
           qDebug() << "Bytes total:" << volume.bytesTotal() << endl;
       }


#ifdef _WIN32 || _WIN_64

qDebug()<<"[0]";
    LPWSTR lpbuffer;

    lpbuffer = new TCHAR[255];

qDebug()<<"[1]";
    for( int i = 0; i < 255; i++ ) lpbuffer[i] = 0;
    char dr[10];
   for( int i = 0; i < 10; i++ ) dr[i] = 0;
qDebug()<<"[2]";
    GetLogicalDriveStringsW(255,lpbuffer);

qDebug()<<"[3]";

    for( int i = 0; i < 255; i++ )
    {
     //   qDebug()<<"[4]";
       if( lpbuffer[i] == ':' )
       {
       dr[0] = lpbuffer[i-1];
       dr[1] = lpbuffer[i];
       dr[2] = lpbuffer[i+1];
  //     dr[3] = lpbuffer[i+2];


       QString str = dr;
       LPCWSTR path = (const wchar_t*) str.utf16();

       qDebug()<<"str: "<<str;

//GetDriveTypeW()
    if( GetDriveTypeW(path) == DRIVE_REMOVABLE )
    {
       qDebug()<<"[PROFIT] str: "<<str;
    this->ui->AdmAud_comboBox->addItem(str);
    }
       }
    }


#else
    qDebug()<<"[LINUX]";
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {

    qDebug() << storage.rootPath();
    if (storage.isReadOnly())
    qDebug() << "isReadOnly:" << storage.isReadOnly();

    qDebug() << "name:" << storage.name();
    qDebug() << "fileSystemType:" << storage.fileSystemType();
    qDebug() << "size:" << storage.bytesTotal()/1000/1000 << "MB";
    qDebug() << "availableSize:" << storage.bytesAvailable()/1000/1000 << "MB";
    }
#endif
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



  this->ui->RifPort_comboBox->addItem(" ВЫКЛ"," ВЫКЛ");
   for(int i(1), n(100); i < n; i++)
   {
       qDebug()<<"i= "<<i;
       QString str(" COM%1");
       str = str.arg(i);
       this->ui->RifPort_comboBox->addItem(str,str);

       ComPort* port = new ComPort();
       comports.append(port);
   }


    default_RIF();



    this->ui->RifPortSpeed_comboBox->addItem("4800");
    this->ui->RifPortSpeed_comboBox->addItem("9600");
    this->ui->RifPortSpeed_comboBox->addItem("19200");
    this->ui->RifPortSpeed_comboBox->addItem("38400");
    this->ui->RifPortSpeed_comboBox->addItem("57600");
    this->ui->RifPortSpeed_comboBox->addItem("115200");
    this->ui->RifPortSpeed_comboBox->addItem("250000");



default_OPERATORS();

    str_GROUP=" Группа";
    str_SD_BL_IP=" БЛ-IP СД";
    str_IU_BL_IP=" БЛ-IP ИУ";
    str_KL = " КЛ1 (концентратор) СД";
    str_TG =" Точка/Гарда";
    str_RLM_KRL = " РИФ-РЛМ/КРЛ/Трасса";
    str_RLM_C = " РИФ-РЛМ-С";
    str_STRAZH_IP = " ТВ+тепловиз.Страж-IP";
    str_NET_DEV = " Сетевое устройство";
    str_ONVIF = " ТВ-камера ONVIF";
    str_BOD_T4K_M = " Точка-М/Гарда БОД";
    str_Y4_T4K_M = " Точка-М/Гарда Участок";
    str_DD_T4K_M = " Точка-М/Гарда ДД";
    str_BOD_SOTA = " Сота/Сота-М БОД";
    str_Y4_SOTA = " Сота/Сота-М Участок";
    str_DD_SOTA = " Сота/Сота-М ДД";


    this->ui->uType_combobox->addItem(str_GROUP);
    this->ui->uType_combobox->addItem(str_IU_BL_IP);
    this->ui->uType_combobox->addItem(str_SD_BL_IP);
    this->ui->uType_combobox->addItem(str_KL);
    this->ui->uType_combobox->addItem(str_RLM_KRL);
    this->ui->uType_combobox->addItem(str_RLM_C);
    this->ui->uType_combobox->addItem(str_NET_DEV);
    this->ui->uType_combobox->addItem(str_BOD_SOTA);
    this->ui->uType_combobox->addItem(str_Y4_SOTA);
    this->ui->uType_combobox->addItem(str_DD_SOTA);
    this->ui->uType_combobox->addItem(str_STRAZH_IP);
    this->ui->uType_combobox->addItem(str_ONVIF);
    this->ui->uType_combobox->addItem(str_TG);
    this->ui->uType_combobox->addItem(str_BOD_T4K_M);
    this->ui->uType_combobox->addItem(str_Y4_T4K_M);
    this->ui->uType_combobox->addItem(str_DD_T4K_M);














    str_RIF_RLM=" РИФ-РЛМ";
    str_RIF_RLM_24=" РИФ-РЛМ24";
    str_RIF_RLM_B=" РИФ-РЛМ(Б)";
    str_RIF_KRL=" РИФ-КРЛ";
    str_Razriv=" Разрыв";
    str_trassa1l=" Трасса-1л";

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
    this->ui->tableWidget->setColumnWidth(1,70);
    this->ui->tableWidget->setColumnWidth(2,70);
    this->ui->tableWidget->setColumnWidth(3,70);
    this->ui->tableWidget->setColumnWidth(4,70);
    this->ui->tableWidget->setColumnWidth(5,70);
    this->ui->tableWidget->setColumnWidth(6,70);
  //  this->ui->textEdit->setText("1111111\n 22222");


//    dialog.showMessage("this it the test message");
//    dialog.exec();


    action_setDK = new QAction(trUtf8("Выполнять команду ДК"), this);
    action_YZ_MONOLIT = new QAction(trUtf8("УЗ Монолит"), this);
    action_setAlarmMsgOn  =new QAction(trUtf8("Выдавать сообщение при тревогах"), this);

    action_setDK->setCheckable(true);
    action_YZ_MONOLIT->setCheckable(true);
    action_setAlarmMsgOn->setCheckable(true);

    action_setAdamOff_off = new QAction(trUtf8("выкл"), this);
    action_setAdamOff_5_sec = new QAction(trUtf8("5 сек"), this);
    action_setAdamOff_10_sec= new QAction(trUtf8("10 сек"), this);
    action_setAdamOff_30_sec= new QAction(trUtf8("30 сек"), this);
    action_setAdamOff_1_min= new QAction(trUtf8("1 мин"), this);
    action_setAdamOff_5_min= new QAction(trUtf8("5 мин"), this);
    action_setAdamOff_10_min= new QAction(trUtf8("10 мин"), this);
    action_setAdamOff_20_min= new QAction(trUtf8("20 мин"), this);
    action_setAdamOff_30_min= new QAction(trUtf8("30 мин"), this);
    action_setAdamOff_1_hour= new QAction(trUtf8("1 час"), this);

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

        connect(&this->db_f, SIGNAL(create_db(QString)  ) , this,SLOT     (create_db(QString)));
        connect(&this->db_f, SIGNAL(  drop_db(QString)  ) , this,SLOT     (  drop_db(QString)));
        connect(&this->db_f, SIGNAL(   use_db(QString)  ) , this,SLOT     (   use_db(QString)));



        this->on_actionCreate_triggered();
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

void MainWindowCFG::unitNameChanged(QStandardItem *item)
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
    current_index=index;
    if(index.isValid())
    {
        qDebug()<<"[+]";
    UnitNode *unit = static_cast<UnitNode*>(index.internalPointer());


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
       this->ui->groupBox_4->setVisible(false);
    switch(selected_type)
    {
    case TypeUnitNode::GROUP:
    this->get_option_GROUP(unit);
    break;

    case TypeUnitNode::SD_BL_IP:
    this->get_option_SD_BL_IP(unit);
    coordinate_menu(true,true,unit->getLan(),unit->getLon(),unit->getDescription());
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



QString MainWindowCFG::Type_from_int_to_string(int int_Type)
{
    QString Type;
    Type.clear();

    switch(int_Type)
    {
    case TypeUnitNode::GROUP:
    Type.append(str_GROUP);
    break;

    case TypeUnitNode::SD_BL_IP:
    Type.append(str_SD_BL_IP);
    break;

    case TypeUnitNode::IU_BL_IP:
    Type.append(str_IU_BL_IP);
    break;

    case TypeUnitNode::TG:
    Type.append(str_TG);
    break;

    case TypeUnitNode::RLM_KRL:
    Type.append(str_RLM_KRL);
    break;

    case TypeUnitNode::RLM_C:
    Type.append(str_RLM_C);
    break;

    case TypeUnitNode::BOD_T4K_M:
    Type.append(str_BOD_T4K_M);
    break;

    case TypeUnitNode::Y4_T4K_M:
    Type.append("Участок Точка-М/Гарда");
    break;

    case TypeUnitNode::DD_T4K_M:
    Type.append(str_DD_T4K_M);
    break;

    case TypeUnitNode::BOD_SOTA:
    Type.append(str_BOD_SOTA);
    break;

    case TypeUnitNode::Y4_SOTA:
    Type.append(str_Y4_SOTA);
    break;

    case TypeUnitNode::DD_SOTA:
    Type.append(str_DD_SOTA);
    break;

    case TypeUnitNode::KL:
    Type.append(str_KL);

    case TypeUnitNode::NET_DEV:
    Type.append(str_NET_DEV);

    case TypeUnitNode::STRAZH_IP:
    Type.append(str_STRAZH_IP);

    case TypeUnitNode::ONVIF:
    Type.append(str_ONVIF);

    break;



 /*
    if(arg1==str_BOD_SOTA)
    this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_Sota_M_groupbox);
    else
    if(arg1==str_Y4_SOTA)
    this->ui->stackedWidget->setCurrentWidget(this->ui->U4_Sota_M_groupbox);
        else
    if(arg1==str_DD_SOTA)
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

    if(Type==str_GROUP)
        return TypeUnitNode::GROUP;

    if(Type==str_SD_BL_IP)
        return TypeUnitNode::SD_BL_IP;

    if(Type==str_IU_BL_IP)
        return TypeUnitNode::IU_BL_IP;

    if(Type==str_BOD_SOTA)
        return TypeUnitNode::BOD_SOTA;

    if(Type==str_Y4_SOTA)
        return TypeUnitNode::Y4_SOTA;

    if(Type==str_DD_SOTA)
        return TypeUnitNode::DD_SOTA;

    if(Type==str_BOD_T4K_M)
        return TypeUnitNode::BOD_T4K_M;

    if(Type==str_Y4_T4K_M)
        return TypeUnitNode::Y4_T4K_M;

    if(Type==str_DD_T4K_M)
        return TypeUnitNode::DD_T4K_M;

    if(Type==str_TG)
        return TypeUnitNode::TG;


    if(Type==str_RLM_KRL)
        return TypeUnitNode::RLM_KRL;


    if(Type==str_KL)
        return TypeUnitNode::KL;

    if(Type==str_NET_DEV)
        return TypeUnitNode::NET_DEV;

    if(Type==str_STRAZH_IP)
        return TypeUnitNode::STRAZH_IP;

    if(Type==str_ONVIF)
        return TypeUnitNode::ONVIF;

    if(Type==str_RLM_C)
        return TypeUnitNode::RLM_C;

    /*
    case TypeUnitNode::GROUP:
break;


    Type.append(str_GROUP);
    break;

    case TypeUnitNode::SD_BL_IP:
    Type.append(str_SD_BL_IP);
    break;

    case TypeUnitNode::IU_BL_IP:
    Type.append(str_IU_BL_IP);
    break;

    case TypeUnitNode::TG:
    Type.append(str_TG);
    break;

    case TypeUnitNode::RLM_KRL:
    Type.append(str_RLM_KRL);
    break;

    case TypeUnitNode::RLM_C:
    Type.append(str_RLM_C);
    break;

    case TypeUnitNode::BOD_T4K_M:
    Type.append(str_BOD_T4K_M);
    break;

    case TypeUnitNode::Y4_T4K_M:
    Type.append("Участок Точка-М/Гарда");
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
    this->ui->UDP_RS485_Widget->setVisible(false);
    this->ui->type_pxm_label->clear();
    this->ui->groupBox_4->setVisible(false);
    if(arg1==str_GROUP){
    this->ui->stackedWidget->setCurrentWidget(this->ui->Group_groupbox);
    }

    else
    if(arg1==str_SD_BL_IP){
    qDebug()<<"[!!!!!!!!!!!!!!!!!!!!!!!!!!!CD!!!]";
    this->ui->type_pxm_label->setPixmap(QPixmap(":images/SD.png"));
    this->ui->stackedWidget->setCurrentWidget(this->ui->SD_BL_IP_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
    this->ui->timeout_doubleSpinBox->setValue(50);
        coordinate_menu(true,false,0,0,"");

    }
    else
    if(arg1==str_IU_BL_IP)
    {
        this->ui->UDP_RS485_Widget->setVisible(true);
        this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
        this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
        this->ui->timeout_doubleSpinBox->setValue(50);
        this->ui->stackedWidget->setCurrentWidget(this->ui->IU_BL_IP_groupbox);
    }
    else
    if(arg1==str_TG)
    {

        this->ui->stackedWidget->setCurrentWidget(this->ui->TG_groupbox);
        this->ui->UDP_RS485_Widget->setVisible(true);
        this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
        this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
        this->ui->timeout_doubleSpinBox->setValue(75);
    }
    else
    if(arg1==str_RLM_KRL)
    {

        this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_KRL_groupbox);
        this->ui->UDP_RS485_Widget->setVisible(true);
        this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
        this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
        this->ui->timeout_doubleSpinBox->setValue(50);
    }
    else
    if(arg1==str_RLM_C)
    {

    this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_C_groupbox);
        this->ui->UDP_RS485_Widget->setVisible(true);
        this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
        this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
                this->ui->timeout_doubleSpinBox->setValue(50);
    }
    else
    if(arg1==str_BOD_T4K_M)
    {

    this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_T4K_M_groupbox);
        this->ui->UDP_RS485_Widget->setVisible(true);
        this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
        this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
                this->ui->timeout_doubleSpinBox->setValue(200);
    }
    else
    if(arg1==str_Y4_T4K_M)
    {

    this->ui->stackedWidget->setCurrentWidget(this->ui->Y4_T4K_M_groupbox);
    }
    else
    if(arg1==str_DD_T4K_M)
    {

    this->ui->stackedWidget->setCurrentWidget(this->ui->DD_T4K_M_groupbox);

    }
    else
    if(arg1==str_BOD_SOTA)
    {
        this->ui->type_pxm_label->setPixmap(QPixmap(":images/BOD_T4K_M.png"));
     this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_Sota_M_groupbox);
        this->ui->UDP_RS485_Widget->setVisible(true);
        this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
        this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
        this->ui->timeout_doubleSpinBox->setValue(300);
    }
    else
    if(arg1==str_Y4_SOTA)
    {
        this->ui->type_pxm_label->setPixmap(QPixmap(":images/Y4_SOTA.png"));
        this->ui->stackedWidget->setCurrentWidget(this->ui->U4_Sota_M_groupbox);
    }
    else
    if(arg1==str_DD_SOTA)
    {
        this->ui->stackedWidget->setCurrentWidget(this->ui->DD_Sota_M_groupbox);
    }
    else
    if(arg1==str_KL)
    {
        this->ui->stackedWidget->setCurrentWidget(this->ui->KL_groupbox);
        this->ui->UDP_RS485_Widget->setVisible(true);
        this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
        this->ui->UDP_RS485_combobox->setCurrentText(" RS485");
        this->ui->timeout_doubleSpinBox->setValue(50);
    }
    else
    if(arg1==str_ONVIF)
    {
    this->ui->stackedWidget->setCurrentWidget(this->ui->ONVIF_groupbox);

    }
    else
    if(arg1==str_STRAZH_IP)
    {
    this->ui->stackedWidget->setCurrentWidget(this->ui->STRAZH_IP_groupbox);

    }
    else
    if(arg1==str_NET_DEV)
    {
    this->ui->stackedWidget->setCurrentWidget(this->ui->NET_DEV_groupbox);

    }


    else
    {
        qDebug()<<"EMPTY";
    this->ui->stackedWidget->setCurrentWidget(this->ui->empty_space_groupbox);
    }



//Участок Точка-М/Гряда
//   БОД Точка-М/Гряда

    //РИФ-РЛМ-С

  //  РИФ-РЛМ/КРЛ/Трасса

}



void MainWindowCFG::on_pushButton_4_clicked()
{
    qDebug()<<"rename_unit()";
    QModelIndex index=this->ui->treeView->currentIndex();
    if(index.isValid())
    {
        UnitNode* un = static_cast<UnitNode*>(index.internalPointer());
        un->setName(this->ui->uName_lineedit->text());

    }
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

    //По умолчанию - если не является устройством, которое подключается по RS-485 к БЛ-IP
    //если является - то значение Num1 присвоится далее в одной из функций
    unit->setNum1(0);
    unit->setNum2(0);

    qDebug()<<"[set_option]";
int type=this->Type_from_string_to_int(this->ui->uType_combobox->currentText());
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
       this->set_option_Y4_T4K_M(unit);
       break;

       case TypeUnitNode::DD_T4K_M:
       this->set_option_DD_T4K_M(unit,parent);
       break;

       case TypeUnitNode::BOD_SOTA:
       this->set_option_BOD_SOTA(unit);
       break;

       case TypeUnitNode::Y4_SOTA:
       this->set_option_Y4_SOTA(unit);
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

    default_PARAMS();
    default_OPERATORS();
    default_RIF();
    default_INTEGRATION();
    default_SQL();
    default_BACKUP();
}

void MainWindowCFG::on_actionOpen_triggered()
{
     qDebug()<<"[Open]";
     this->modelTreeUN->rootItemUN->deleteAll();
     QString patch=QFileDialog::getOpenFileName(this, "open file","","*.ini");
      qDebug()<<"patch = "<<patch;
      if(patch!="")
      {
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

void MainWindowCFG::on_treeView_activated(const QModelIndex &index)
{
    qDebug()<<"activated";
}

void MainWindowCFG::on_pushButton_clicked()
{
   add_unit();
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

void MainWindowCFG::update_operators_table()
{
      ui->tableWidget->setRowCount(0);
    qDebug()<<"количество операторов "<<operators.count();
    int cnt;
    foreach(Operator* op, operators)
    {

        qDebug()<<op->getN1()<<" "<<op->getN2()<<" "<<op->getFN();

        cnt=this->ui->tableWidget->rowCount();
        this->ui->tableWidget->insertRow(cnt);
        this->ui->tableWidget->setItem(cnt,1, new QTableWidgetItem(op->getFN()));
        this->ui->tableWidget->setItem(cnt,2, new QTableWidgetItem(op->getN1()));
        this->ui->tableWidget->setItem(cnt,3, new QTableWidgetItem(op->getN2()));

    }
}

QString MainWindowCFG::get_unit_name(int type)
{

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

return true;
}

bool MainWindowCFG::pass_to_add_SD_BL_IP(UnitNode *unit, UnitNode *parrent)
{
    //СД может быть добавлен только к группе или к системе
        if((parrent->getType()!=TypeUnitNode::GROUP)&&(parrent->getType()!=TypeUnitNode::SYSTEM))
        {
            dialog.showMessage("СД может быть добавлен только к группе или к системе");
            dialog.exec();
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
                dialog.showMessage("Такой обьект уже существует");
                dialog.exec();
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

                 dialog.showMessage("Такой обьект уже существует");
                 dialog.exec();
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
    //ИУ может быть добавлен только к группе или к системе
        if((parrent->getType()!=TypeUnitNode::GROUP)&&(parrent->getType()!=TypeUnitNode::SYSTEM))
        {
            dialog.showMessage("ИУ может быть добавлен только к группе или к системе");
            dialog.exec();
            return false;

        }

        //Num2 от нуля до четырех
         if(unit->getNum2()<0||unit->getNum2()>4)

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
                     dialog.showMessage("Такой обьект уже существует");
                     dialog.exec();
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

                      dialog.showMessage("Такой обьект уже существует");
                      dialog.exec();
                      return false;
                  }
                 }
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
                QList<UnitNode *> List1;
                this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
                foreach(UnitNode *un, List1 )
                {

            qDebug()<<QString::number(un->getNum3())<<" "<<QString::number(unit->getNum3());
                 if((un->getNum3()==unit->getNum3()))
                 if((un->getNum1()==unit->getNum1()))
                 {

                     dialog.showMessage("Такой обьект уже существует");
                     dialog.exec();
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

                     dialog.showMessage("Такой обьект уже существует");
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
         dialog.showMessage("Такой обьект уже существует");
         dialog.exec();
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
        dialog.showMessage("ДД может быть добавлен только к участку !");
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


                    dialog.showMessage("Такой обьект уже существует");
                    dialog.exec();
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


                    dialog.showMessage("Такой обьект уже существует");
                    dialog.exec();
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
        if(parrent->getType()!=TypeUnitNode::GROUP)
        {
            dialog.showMessage("БОД может быть добавлен только к группе");
            dialog.exec();
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

                     dialog.showMessage("Такой обьект уже существует");
                     dialog.exec();
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

                     dialog.showMessage("этот IP адрес уже  занят");
                     dialog.exec();
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
        dialog.showMessage("Участок может быть добавлен только к БОД Точка-М/Гарда-М !");
        dialog.exec();
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
         dialog.showMessage("Такой обьект уже существует");
         dialog.exec();
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
        dialog.showMessage("ДД может быть добавлен только к участку !");
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


                    dialog.showMessage("Такой обьект уже существует");
                    dialog.exec();
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


                    dialog.showMessage("Такой обьект уже существует");
                    dialog.exec();
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
         dialog.showMessage("ЧЭ от одного до четырех !");
         dialog.exec();
         return false;

     }
   //только к группе
    if(parrent->getType()!=TypeUnitNode::GROUP)
    {
        dialog.showMessage("устройство Точка/Гарда может быть добавлено только к группе !");
        dialog.exec();
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

                     dialog.showMessage("Такой обьект уже существует");
                     dialog.exec();
                     return false;
                  }
                 if(un->getType()==unit->getType()) //если на этом адресе этого порта есть ЧЭ - проверить на номер ЧЭ
                  {
                     if(un->getNum2()==unit->getNum2())
                     {
                         dialog.showMessage("Такой обьект уже существует");
                         dialog.exec();
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

                 dialog.showMessage("Такой обьект уже существует");
                 dialog.exec();
                 return false;
              }
             if(un->getType()==unit->getType()) //если на этом адресе этого порта есть ЧЭ - проверить на номер ЧЭ
              {
                 if(un->getNum2()==unit->getNum2())
                 {
                     dialog.showMessage("Такой обьект уже существует");
                     dialog.exec();
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
            dialog.showMessage(" может быть добавлен только к группе");
            dialog.exec();
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

                     dialog.showMessage("Такой обьект уже существует");
                     dialog.exec();
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

                     dialog.showMessage("Такой обьект уже существует");
                     dialog.exec();
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
        dialog.showMessage(" может быть добавлен только к группе");
        dialog.exec();
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

                 dialog.showMessage("Такой обьект уже существует");
                 dialog.exec();
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

                 dialog.showMessage("Такой обьект уже существует");
                 dialog.exec();
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
          dialog.showMessage("СД от одного до четырех !");
          dialog.exec();
          return false;

      }


    // может быть добавлен только к группе
        if(parrent->getType()!=TypeUnitNode::GROUP)
        {
            dialog.showMessage(" может быть добавлен только к группе");
            dialog.exec();
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

                         dialog.showMessage("Такой обьект уже существует");
                         dialog.exec();
                         return false;
                      }
                     if(un->getType()==unit->getType()) //если на этом адресе этого порта есть СД - проверить на номер СД
                      {
                    //       qDebug()<<"[4]";
                         if(un->getNum2()==unit->getNum2())
                         {
                               qDebug()<<"[5]";
                             dialog.showMessage("Такой обьект уже существует");
                             dialog.exec();
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

                     dialog.showMessage("Такой обьект уже существует");
                     dialog.exec();
                     return false;
                  }
                 if(un->getType()==unit->getType()) //если на этом адресе этого порта есть СД - проверить на номер СД
                  {
                     if(un->getNum2()==unit->getNum2())
                     {
                         dialog.showMessage("Такой обьект уже существует");
                         dialog.exec();
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
    if(parrent->getType()!=TypeUnitNode::GROUP)
    if(parrent->getType()!=TypeUnitNode::SYSTEM)
    {
        dialog.showMessage("БОД может быть добавлен только к группе");
        dialog.exec();
        return false;

    }

    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
    foreach(UnitNode *un, List1 )
    {
     if(un->getType()==unit->getType())
     if(un->getIcon1Path()==unit->getIcon1Path())
     {
         dialog.showMessage("Такой обьект уже существует");
         dialog.exec();
         return false;

     }

    }
        return true;
}

bool MainWindowCFG::pass_to_add_STRAZH_IP(UnitNode *unit, UnitNode *parrent)
{
    if(parrent->getType()!=TypeUnitNode::GROUP)
    if(parrent->getType()!=TypeUnitNode::SYSTEM)
    {
        dialog.showMessage("БОД может быть добавлен только к группе");
        dialog.exec();
        return false;

    }

    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
    foreach(UnitNode *un, List1 )
    {

     if(un->getType()==unit->getType())

     if((un->getIcon1Path()==unit->getIcon1Path())||
        (un->getIcon4Path()==unit->getIcon4Path()))
     {
         dialog.showMessage("Такой обьект уже существует");
         dialog.exec();
         return false;

     }

    }

        return true;
}

bool  MainWindowCFG::pass_to_add_NET_DEV(UnitNode *unit, UnitNode *parrent)
{
    if(parrent->getType()!=TypeUnitNode::GROUP)
    if(parrent->getType()!=TypeUnitNode::SYSTEM)
    {
        dialog.showMessage("БОД может быть добавлен только к группе");
        dialog.exec();
        return false;

    }

    QList<UnitNode *> List1;
    this->modelTreeUN->getListFromModel(List1,this->modelTreeUN->rootItemUN);
 /*   foreach(UnitNode *un, List1 )
    {
     if(un->getType()==unit->getType())
     if(un->getIcon1Path()==unit->getIcon1Path())
     {
         dialog.showMessage("Такой обьект уже есть");
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


    int type=this->Type_from_string_to_int(this->ui->uType_combobox->currentText());

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

    if(this->ui->groupBox_4->isVisible())
    {
        unit->setLan(this->ui->coordinate_X_doubleSpinBox->value());
        unit->setLon(this->ui->coordinate_Y_doubleSpinBox->value());
        unit->setDescription(ui->Dop_info_description_lineedit->text());

    }

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
    qDebug()<<"[+]"<<string1;
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

void MainWindowCFG::get_option_BL_IP(UnitNode *unit)
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
    get_RASTR(filename);
    get_SOLID(filename);
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


        dialog.showMessage(msg);
        dialog.exec();

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


        dialog.showMessage(msg);
        dialog.exec();

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
    this->ui->SoundType_comboBox->setCurrentText(map_PARAMS_SoundType.value(2));
    this->ui->PARAMS_AutoStart_comboBox->setCurrentText(map_PARAMS_AutoStart.value(0));
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
        ComPort* port=comports.at(i);


      QString str_RifPortSpeed("RifPortSpeed%1");
      str_RifPortSpeed = str_RifPortSpeed.arg(i);

      int RifPortSpeed = settings.value(str_RifPortSpeed,-1).toInt();

      if(RifPortSpeed!=-1)
      {
          qDebug()<<str_RifPortSpeed<<" "<<QString::number(RifPortSpeed);
                  port->set_RifPortSpeed(RifPortSpeed);

      }

      QString str_RifPortInterval("RifPortInterval%1");
      str_RifPortInterval = str_RifPortInterval.arg(i);

      int RifPortInterval = settings.value(str_RifPortInterval,-1).toInt();

      if(RifPortInterval!=-1)
      {
          qDebug()<<str_RifPortInterval<<" "<<QString::number(RifPortInterval);
          port->set_RifPortInterval(RifPortInterval);

      }



    }

    this->ui->RIF_AutoDK_comboBox->setCurrentIndex(settings.value("AutoDK",-1).toInt());
    this->ui->RIF_TochkaDirectionInterval_doubleSpinBox->setValue(settings.value("TochkaDirectionInterval",-1).toDouble());

//    settings.setValue("AutoDK", autoDK);
//    settings.setValue("TochkaDirectionInterval", TochkaDirectionInterval);

    settings.endGroup();
}

void MainWindowCFG::set_RIF(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
  #if (defined (_WIN32) || defined (_WIN64))
      settings.setIniCodec( "Windows-1251" );
  #else
      settings.setIniCodec( "UTF-8" );
  #endif

    settings.beginGroup("RIF");

    for(int i=0; i<comports.count();i++)
    {
        ComPort *port = comports.at(i);
        int speed = port->get_RifPortSpeed();
        int interval = port->get_RifPortInterval();

        if(speed!=4800)
        {
            QString str="RifPortSpeed%1";
            str=str.arg(i);
        settings.setValue(str,speed);
        }

        if(interval!=50)
        {
            QString str="RifPortInterval%1";
            str=str.arg(i);
        settings.setValue(str,interval);
        }



    }

    settings.setValue("AutoDK", this->ui->RIF_AutoDK_comboBox->currentIndex());
    settings.setValue("TochkaDirectionInterval", this->ui->RIF_TochkaDirectionInterval_doubleSpinBox->value());

    settings.endGroup();
}

void MainWindowCFG::default_RIF()
{
    qDebug()<<"comports.count "<<comports.count();
    for(int i(0), n(100); i < n; i++)
    {
qDebug()<<"---"<<i;
        if(i<comports.count())
        {
        comports.at(i)->set_RifPortSpeed(4800);
        comports.at(i)->set_RifPortInterval(50);
        }
    }
    this->ui->RifPort_comboBox->setCurrentIndex(0);

    this->ui->RifPortSpeed_comboBox->setCurrentText(QString::number(comports.at(0)->get_RifPortSpeed()));
    this->ui->RifPortInterval_doubleSpinBox->setValue(comports.at(0)->get_RifPortInterval());


    this->ui->RIF_AutoDK_comboBox->setCurrentIndex(0);
    this->ui->RIF_TochkaDirectionInterval_doubleSpinBox->setValue(20);
}

void MainWindowCFG::get_SSOI(QString filename)
{

}

void MainWindowCFG::set_SSOI(QString filename)
{

}

void MainWindowCFG::default_SSOI()
{

}

void MainWindowCFG::get_RASTRMTV(QString filename)
{

}

void MainWindowCFG::set_RASTRMTV(QString filename)
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

      settings.endGroup();
}

void MainWindowCFG::default_INTEGRATION()
{
    this->ui->INTEGRATION_Use_comboBox->setCurrentText(map_INTEGRATION_Use.value(0));
    this->ui->INTEGRATION_Host_lineEdit->setText("");
    this->ui->INTEGRATION_Port_doubleSpinBox->setValue(0);
    this->ui->INTEGRATION_Port2_doubleSpinBox->setValue(0);
    this->ui->INTEGRATION_KeepAliveInterval_doubleSpinBox->setValue(0);
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
              this->ui->SQL_password_lineEdit->setText(settings.value("Password",-1).toString());
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
    this->ui->SQL_server_lineEdit->setText("");
    this->ui->SQL_port_doubleSpinBox->setValue(0);
    this->ui->SQL_login_lineEdit->setText("");
    this->ui->SQL_password_lineEdit->setText("");
    this->ui->SQL_database_lineEdit->setText("");


       this->ui->SQL_P1_checkBox->setChecked(false);


       this->ui->SQL_P2_checkBox->setChecked(false);


       this->ui->SQL_AutoDbStart_checkBox->setChecked(false);

    this->ui->SQL_AutoDbStartHour_doubleSpinBox->setValue(0);
    this->ui->SQL_AutoDbStartMinute_doubleSpinBox->setValue(0);
}

void MainWindowCFG::get_RASTR(QString filename)
{

}

void MainWindowCFG::set_RASTR(QString filename)
{

}

void MainWindowCFG::default_RASTR()
{

}

void MainWindowCFG::get_SOLID(QString filename)
{

}

void MainWindowCFG::set_SOLID(QString filename)
{

}

void MainWindowCFG::default_SOLID()
{

}

void MainWindowCFG::get_ADAM4068(QString filename)
{

}

void MainWindowCFG::set_ADAM4068(QString filename)
{

}

void MainWindowCFG::default_ADAM4068()
{

}

void MainWindowCFG::get_TABLO(QString filename)
{

}

void MainWindowCFG::set_TABLO(QString filename)
{

}

void MainWindowCFG::default_TABLO()
{

}

void MainWindowCFG::get_RASTRMSSOI(QString filename)
{

}

void MainWindowCFG::set_RASTRMSSOI(QString filename)
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
int res=0;

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
int res=0;

    settings.beginGroup("BACKUP");

    settings.setValue("BackupPath",this->ui->BACKUP_BackupPath_lineedit->text());
    settings.setValue("MaxBdStringCnt",map_BACKUP_MaxBdStringCnt.key(this->ui->BACKUP_MaxBdStringCnt_comboBox->currentText()));


    settings.endGroup();
}

void MainWindowCFG::default_BACKUP()
{
    this->ui->BACKUP_BackupPath_lineedit->setText("");
    this->ui->BACKUP_MaxBdStringCnt_comboBox->setCurrentText(map_BACKUP_MaxBdStringCnt.value(10));
}

void MainWindowCFG::get_PORT(QString filename)
{

}

void MainWindowCFG::set_PORT(QString filename)
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

void MainWindowCFG::get_ASOOSD(QString filename)
{

}

void MainWindowCFG::set_ASOOSD(QString filename)
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

void MainWindowCFG::set_option_Y4_T4K_M(UnitNode *unit)
{
unit->setNum2(this->ui->Y4_T4K_M_combobox->currentText().toInt()*100);
}

void MainWindowCFG::set_option_DD_T4K_M(UnitNode *unit,UnitNode *parent)
{
    int val=parent->getNum2();


    unit->setNum2(this->ui->DD_T4K_M_combobox->currentText().toInt()+val-1);
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

void MainWindowCFG::set_option_Y4_SOTA(UnitNode *unit)
{
unit->setNum2(this->ui->U4_Sota_M_combobox->currentText().toInt()*100);
}

void MainWindowCFG::set_option_DD_SOTA(UnitNode *unit,UnitNode *parent)
{
   int val=parent->getNum2();


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
//    unit->setIcon1Path(this->ui->ONVIF_lineEdit__IPaddr->text());
//    unit->setIcon2Path(this->ui->ONVIF_lineEdit__login->text());
//    unit->setIcon3Path(this->ui->ONVIF_lineEdit__password->text());

}

void MainWindowCFG::set_option_STRAZH_IP(UnitNode *unit)
{
//    unit->setIcon1Path(this->ui->STRAZH_IP_lineEdit__IPaddr->text());
//    unit->setIcon2Path(this->ui->STRAZH_IP_lineEdit__login->text());
//    unit->setIcon3Path(this->ui->STRAZH_IP_lineEdit__password->text());
//    unit->setIcon4Path(this->ui->STRAZH_IP_lineEdit__IPaddres_rotary_device->text());
}

void MainWindowCFG::set_option_NET_DEV(UnitNode *unit)
{
//    unit->setIcon1Path(this->ui->NET_DEV_IP_lineEdit->text());
}

void MainWindowCFG::save_ini(QString filename)
{
    qDebug()<<"save ini";

    QSettings settings(filename,QSettings::IniFormat);
    settings.setIniCodec( QTextCodec::codecForLocale() );
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
        set_SOLID(filename);
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

settings.beginGroup("RIF");
for(int i=0; i<comports.count();i++){
    ComPort *port = comports.at(i);
    int speed = port->get_RifPortSpeed();
    int interval = port->get_RifPortInterval();
    if(speed!=4800){
        QString str="RifPortSpeed%1";
        str=str.arg(i);
    settings.setValue(str,speed);
    }
    if(interval!=50){
        QString str="RifPortInterval%1";
        str=str.arg(i);
    settings.setValue(str,interval);
    }
}
settings.setValue("AutoDK", this->ui->RIF_AutoDK_comboBox->currentIndex());
settings.setValue("TochkaDirectionInterval", this->ui->RIF_TochkaDirectionInterval_doubleSpinBox->value());
settings.endGroup();

settings.beginGroup("INTEGRATION");
settings.setValue("Use",map_INTEGRATION_Use.key(this->ui->INTEGRATION_Use_comboBox->currentText()));
settings.setValue("Host",this->ui->INTEGRATION_Host_lineEdit->text());
settings.setValue("Port",this->ui->INTEGRATION_Port_doubleSpinBox->value());
settings.setValue("Port2",this->ui->INTEGRATION_Port2_doubleSpinBox->value());
settings.setValue("KeepAliveInterval",this->ui->INTEGRATION_KeepAliveInterval_doubleSpinBox->value());
settings.endGroup();

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


    settings.beginGroup("BACKUP");
    settings.setValue("BackupPath",this->ui->BACKUP_BackupPath_lineedit->text());
    settings.setValue("MaxBdStringCnt",map_BACKUP_MaxBdStringCnt.key(this->ui->BACKUP_MaxBdStringCnt_comboBox->currentText()));
    settings.endGroup();

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
            if(un->getType()==TypeUnitNode::SD_BL_IP)
            {
             menu->addAction(action_setDK);
    //         connect (action_setDK, SIGNAL(triggered()) , this, SLOT(setDK()));

             qDebug()<<un->getName();

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
            }
            if(un->getType()==TypeUnitNode::IU_BL_IP)
            {
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

            }
            menu->exec(ui->treeView->viewport()->mapToGlobal(pos));

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
  Operator* op = new Operator();
   opt_tbl_request=1;
    op_f.clear_operator_data_on_form();
   op_f.show();
 //   op->setN1("Ivan");
 //   op->setN2("Ivanovich");
 //   op->setFN("Ivanoff");
 //   operators.append(op);

 //   update_operators_table();
}

void MainWindowCFG::on_tableWidget_cellClicked(int row, int column)
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


    op_f.set_operator_data_on_form(operators.at(index)->getFN(),
                                   operators.at(index)->getN1(),
                                   operators.at(index)->getN2(),
                                   operators.at(index)->getPW());
    op_f.show();
}



void MainWindowCFG::on_RifPort_comboBox_currentIndexChanged(int index)
{


int ind = this->ui->RifPort_comboBox->currentIndex();
if(ind<comports.count())
    {

        ComPort* port = comports.at(ind);
        this->ui->RifPortSpeed_comboBox->setCurrentText(QString::number(port->get_RifPortSpeed()));
        this->ui->RifPortInterval_doubleSpinBox->setValue(static_cast<double>(port->get_RifPortInterval()));
        qDebug()<<"["<<ind<<"]"<<QString::number(port->get_RifPortSpeed())<<" "<<QString::number(port->get_RifPortInterval());

    }

}




void MainWindowCFG::on_RifPortSpeed_comboBox_currentTextChanged(const QString &arg1)
{
    int ind = this->ui->RifPort_comboBox->currentIndex();
    if(ind<comports.count())
        {

    ComPort* port = comports.at(ind);
    port->set_RifPortSpeed(arg1.toInt());
    qDebug()<<"["<<ind<<"]"<<QString::number(port->get_RifPortSpeed())<<" "<<QString::number(port->get_RifPortInterval());

    }
}

void MainWindowCFG::on_RifPortInterval_doubleSpinBox_valueChanged(const QString &arg1)
{
      int ind = this->ui->RifPort_comboBox->currentIndex();
    if(ind<comports.count())
        {


    ComPort* port = comports.at(ind);
    port->set_RifPortInterval(this->ui->RifPortInterval_doubleSpinBox->value());
qDebug()<<QString::number(port->get_RifPortInterval());

            qDebug()<<"["<<ind<<"]"<<QString::number(port->get_RifPortSpeed())<<" "<<QString::number(port->get_RifPortInterval());
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
    if (!db_mysql.open()){
        qDebug()<<db_mysql.lastError().text();
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

void MainWindowCFG::on_AdmAud_Create_pushButton_clicked()
{
    /*
    Edit4->Text = "";
    Edit5->Text = "";

    TAdmAudit *AdmAud;
    AdmAud = new TAdmAudit;
    AdmAud->Version = 2.00;
    AdmAud->CreateDt = Now();
    AdmAud->Crc = AdmAud->Version + AdmAud->CreateDt;

    AnsiString str = ComboBox9->Text;

    unsigned int errmode = SetErrorMode ( SEM_FAILCRITICALERRORS );

    if( DirectoryExists(str) )
    {
       str = str + "auidit.adm";

       if( AdmAud->Save(str) )MessageBox (NULL,"Файл аудита создан","Информация",MB_OK|MB_ICONINFORMATION);
       else MessageBox (NULL,"Ошибка создания файла аудита!","Ошибка",MB_OK|MB_ICONERROR);
    }
    else MessageBox (NULL,"Диск не найден!","Ошибка",MB_OK|MB_ICONERROR);

    SetErrorMode ( errmode );

    delete AdmAud;
    */
}

void MainWindowCFG::coordinate_menu(bool visible, bool active, int x, int y,QString text)
{
    this->ui->groupBox_4->setVisible(visible);
    if(visible)
    {
        this->ui->coordinate_X_doubleSpinBox->setValue(x);
        this->ui->coordinate_Y_doubleSpinBox->setValue(y);
        this->ui->Dop_info_description_lineedit->setText(text);

        this->ui->pushButton_5->setEnabled(active);
    }
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
