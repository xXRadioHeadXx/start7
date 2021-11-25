#include "MainWindowCFG.h"
#include "ui_MainWindowCFG.h"
#include <global.h>


#include "QFileDialog"
#include <QErrorMessage>
#include <QStorageInfo>
#include <QBrush>

#include <QCursor>
#include <QMouseEvent>

#include <QDateTime>
#include <QTimer>

#include <QEvent>
#include <QKeyEvent>

#include <QAbstractItemModel>

//#include "first_dialog.h"

#include <QInputDialog>
#include <QDate>

#include <QtCore>

//#include <control.h>


//refactoring





//#include <libusb-1.0/libusb.h>

#if (defined (_WIN32) || defined (_WIN64))
#include <Windows.h>
#endif


MainWindowCFG::MainWindowCFG(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowCFG)
{






    QStringList list;
    list<<str_system_RIF;
    list<<str_system_SSOI;

//    Если программа лежит в папке :/RIFx/ - открывать версию РИФ
//    Если программа лежит в папке :/SSOI/ - открывать версию ССОИ-М
//    Если ни там ни там - предлагать выбор версии





    QByteArray dir= QCoreApplication::applicationDirPath().toLocal8Bit();
    qDebug()<<"DIR "<<dir;

    QByteArray ar;
    for(int i=0;i<dir.size();i++)
    {
        qDebug()<<dir.at(i)<<" "<<(quint8)dir.at(i);
        ar.append((quint8)dir.at(i));
        if((quint8)dir.at(i)==47)
            ar.clear();


    }
    QString str=QString::fromLocal8Bit(ar);
    if(str=="RIFx")
        str_system=str_system_RIF;
    else if(str=="SSOI")
        str_system=str_system_SSOI;
    else
        str_system=QInputDialog::getItem(nullptr,"Настройка","Комплекс",list);

        qDebug()<<str_system;


    last_ini_patch="";



        ui->setupUi(this);



     //   w_SD_BL_IP=new Widget_SD_BL_IP(this);
     //   w_IU_BL_IP=new Widget_IU_BL_IP(this);

    //    this->ui->stack->addWidget(&w_IU_BL_IP);
    //    this->ui->stack->addWidget(w_SD_BL_IP);



        this->modelTreeUN = new TreeModelUnitNode(this);

        this->modelTreeUN->makeEmptyTree();

        modelTreeUN->setTypeApp(SubTypeApp::configurator);

        ui->treeView->setModel(this->modelTreeUN);


ui->RASTR_wgt->set_pointer(&mSerNum_Name);


w_GROUP=new Widget_GROUP(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_GROUP);


w_SD_BL_IP=new Widget_SD_BL_IP(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_SD_BL_IP);
w_IU_BL_IP=new Widget_IU_BL_IP(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_IU_BL_IP );

w_ADAM=new Widget_ADAM(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_ADAM);

w_KL=new Widget_KL(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_KL);
w_TG=new Widget_TG(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_TG);
w_RLM_KRL=new Widget_RLM_KRL(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_RLM_KRL);



w_RLM_C=new Widget_RLM_C(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_RLM_C);
w_STRAZH_IP=new Widget_STRAZH_IP(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_STRAZH_IP);
w_ONVIF=new Widget_ONVIF(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_ONVIF);
w_BOD_T4K_M=new Widget_BOD_T4K_M(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_BOD_T4K_M);
w_Y4_T4K_M=new Widget_Y4_T4K_M(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_Y4_T4K_M);
w_DD_T4K_M=new Widget_DD_T4K_M(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_DD_T4K_M);
w_BOD_SOTA=new Widget_BOD_SOTA(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_BOD_SOTA);

w_Y4_SOTA=new Widget_Y4_SOTA(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_Y4_SOTA);
w_DD_SOTA=new Widget_DD_SOTA(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_DD_SOTA);


w_NET_DEV=new Widget_NET_DEV(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_NET_DEV);
w_SSOI_SD=new Widget_SSOI_SD(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_SSOI_SD);
w_SSOI_IU=new Widget_SSOI_IU(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_SSOI_IU);
w_TOROS=new Widget_TOROS(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_TOROS);
w_DEVLINE=new Widget_DEVLINE(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_DEVLINE);
w_INFO_TABLO=new Widget_INFO_TABLO(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_INFO_TABLO);

w_RASTRMTV=new Widget_RASTRMTV(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index, &mSerNum_Name);  l_UnitWidgets.append(w_RASTRMTV);

w_SSOI_IP_SD=new Widget_SSOI_IP_SD(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_SSOI_IP_SD);
w_SSOI_IP_IU=new Widget_SSOI_IP_IU(this,this->ui->communicationType,this->ui->coord,modelTreeUN,&current_index);  l_UnitWidgets.append(w_SSOI_IP_IU);



   //

     foreach(UnitWidget* wgt, l_UnitWidgets){

      ui->stack->addWidget(wgt);
      connect(wgt,SIGNAL(updateName(QString)),this,SLOT(updateName(QString)));
     }

     ui->uType_combobox->setCurrentIndex(0);
     ui->communicationType->setVisible(false);
     ui->coord->setVisible(false);

//connect(&w_IU_BL_IP,SIGNAL(updateName(QString)),this,SLOT(updateName(QString)));
//connect(w_SD_BL_IP,SIGNAL(updateName(QString)),this,SLOT(updateName(QString)));









QDate date = QLocale(QLocale::C).toDate(QString(__DATE__).simplified(), QLatin1String("MMM d yyyy"));
        if(str_system==str_system_RIF)
        {
         this->setWindowTitle("Настройка комплекса РИФ+ b." + date.toString("dd.MM.yyyy"));
        }
        if(str_system==str_system_SSOI)
        {


          this->ui->tabWidget->removeTab(3);
          this->ui->tabWidget->removeTab(5);

     //   this->ui->Subsystem_RIF->setHidden(true);
     //   this->ui->Subsystem_ADAM->setHidden(true);
         //  this->ui->Subsystem_RIF->setVisible(false);
         //   this->ui->Subsystem_ADAM->setVisible(false);
            this->ui->DevLine_groupbox->setVisible(false);
            this->setWindowTitle("Настройка комплекса ССОИ-М b." + date.toString("dd.MM.yyyy"));


        }





    db_f=new DBform(this,str_system);

    unitFinder_f=new UnitFinder(this);
    unitFinder_f->setVisible(false);

    this->ui->tabWidget->setCurrentIndex(0);


//    this->ui->ipadress_combobox->setValidator( new QRegExpValidator( QRegExp( "[0-1][0-9][0-9]\\.[0-1][0-9][0-9]" ) ) );

//ui->ipadress_combobox->setInputMask( "000.000.000.000" );

    this->ui->SQL_password_lineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    ui->tableView->verticalHeader()->setVisible(false);
    rif_model = new rif_widget_model();
    this->ui->tableView->setModel(rif_model);
    rif_dlgt = new rif_widget_delegate();
    this->ui->tableView->setItemDelegate(rif_dlgt);





    this->setMouseTracking(true);
    this->ui->centralwidget->setMouseTracking(true);
//    this->ui->tabWidget->setMouseTracking(true);





//default_options();
   ui->tableWidget->verticalHeader()->setVisible(false);
//   ui->tableWidget_2->verticalHeader()->setVisible(false);













    this->ui->SQL_server_lineEdit->setText("localhost");





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




 //   map_PARAMS_PlanType[0]="план";
 //   map_PARAMS_PlanType[1]="граф.модуль";
 //   map_PARAMS_PlanType[2]="не использовать";

    map_PARAMS_PlanType.insert(1," граф.модуль");
    map_PARAMS_PlanType.insert(2," не использовать");



     foreach (QString str, map_PARAMS_PlanType)
     {

     this->ui->PlanType_comboBox->addItem(str);
     }




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




//  this->ui->RifPort_comboBox->addItem(" ВЫКЛ"," ВЫКЛ");

//   ComPort* port = new ComPort();
//   comports.append(port);



    default_RIF();





default_OPERATORS();

if(str_system==str_system_RIF)
{
    qSort(l_Unittype_rif.begin(), l_Unittype_rif.end(), [](const QVariant &v1,
                                                   const QVariant &v2)
                                                                ->bool
                                                     {  return v1<v2;}
                                                                    );


    ////qDebug()<<"Unittype.indexOf(ГРУППА)"<<l_Unittype_rif.indexOf(str_GROUP);
    ////qDebug()<<"l_Unittype_rif.count(ГРУППА);"<<l_Unittype_rif.count(str_GROUP);
    l_Unittype_rif.move(l_Unittype_rif.indexOf(str_GROUP),0);
    l_Unittype_rif.move(l_Unittype_rif.indexOf(str_Y4_SOTA),(l_Unittype_rif.indexOf(str_BOD_SOTA)+1));
    l_Unittype_rif.move(l_Unittype_rif.indexOf(str_DD_SOTA),(l_Unittype_rif.indexOf(str_BOD_SOTA)+2));
    l_Unittype_rif.move(l_Unittype_rif.indexOf(str_Y4_T4K_M),(l_Unittype_rif.indexOf(str_Y4_T4K_M)-1));
    l_Unittype_rif.move(l_Unittype_rif.indexOf(str_Y4_T4K_M),(l_Unittype_rif.indexOf(str_BOD_T4K_M)+1));
    l_Unittype_rif.move(l_Unittype_rif.indexOf(str_DD_T4K_M),(l_Unittype_rif.indexOf(str_BOD_T4K_M)+2));



    foreach(QString str, l_Unittype_rif)
    {
    this->ui->uType_combobox->addItem(str);
    }
}
else
if(str_system==str_system_SSOI)
{
    foreach(QString str, l_Unittype_ssoi)
    {
    this->ui->uType_combobox->addItem(str);
    }

}

this->ui->uType_combobox->setCurrentIndex(0);






  //  this->current_index=nullptr;


 //   QString patch="C:/WORK1/start7/rifx.ini";



    dlgt = new Delegate(this);
    this->ui->treeView->setItemDelegate(dlgt);

    ui->treeView->setColumnWidth(0,220);
    ui->treeView->setColumnWidth(1,40);
    ui->treeView->setColumnWidth(2,65);
    ui->treeView->setColumnWidth(3,60);




  //  ui->treeView->installEventFilter(this);



     ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

     menu = new QMenu(ui->treeView);
     menu->addAction("hello");
     menu->addAction("world");

 //   QString patch=QFileDialog::getOpenFileName(this, "open file","","*.ini");
 //    //qDebug()<<"patch = "<<patch;
 //   this->modelTreeUN->loadSettings(patch);

    operators.clear();

     //    this->ui->tableWidget->insertRow(0);
     //    this->ui->tableWidget->insertRow(1);
     //    this->ui->tableWidget->insertRow(2);
     //    this->ui->tableWidget->insertRow(3);
     //    this->ui->tableWidget->insertRow(4);
     //    this->ui->tableWidget->insertRow(5);










    this->ui->textEdit->clear();


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

        connect(this->db_f, SIGNAL(create_db(QString)  ) , this,SLOT     (create_db(QString)));
        connect(this->db_f, SIGNAL(  drop_db(QString)  ) , this,SLOT     (  drop_db(QString)));
        connect(this->db_f, SIGNAL(   use_db(QString)  ) , this,SLOT     (   use_db(QString)));
        connect(this->ui->treeView, SIGNAL(   new_current_index(QModelIndex)) , this,SLOT     (   slot_to_get_options(QModelIndex)));




        connect(this->unitFinder_f,SIGNAL(options_to_find(QList<QString>)),this,SLOT(find_from_options(QList<QString>)));

        connect(this->unitFinder_f,SIGNAL(next()),this,SLOT(next()));
        connect(this->unitFinder_f,SIGNAL(prev()),this,SLOT(prev()));

        connect(this->unitFinder_f,SIGNAL(clear_list_equals()),this,SLOT(clear_list_equals()));

        timer = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
            timer->setInterval(10); // Задаем интервал таймера
            connect(timer, SIGNAL(timeout()), this, SLOT(update())); // Подключаем сигнал таймера к нашему слоту
            timer->start(); // Запускаем таймер



        this->on_actionCreate_triggered();

       //     QRegExpValidator*  validator = new QRegExpValidator(QRegExp ("[^!""|@#$%^&*()_]{0,50}"));
      //      "[A-Za-z\\d]+"
//QRegExpValidator*  validator = new QRegExpValidator(QRegExp ( "[а-яА-ЯёЁa-zA-Z0-9]{0,50}"));

     //           this->ui->uName_combobox->setValidator(validator);

}

MainWindowCFG::~MainWindowCFG()
{
    ui->stack->setCurrentWidget(w_GROUP);
    foreach(UnitWidget* wgt, l_UnitWidgets){

     ui->stack->removeWidget(wgt);

    }

    delete ui;
}

bool MainWindowCFG::load(QString)
{
    bool res=true;






    return res;
}

void MainWindowCFG::show_equals(UnitNode *unit)
{
    QList<UnitNode *> List1;


    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN

    qDebug()<<"-- Ищу устрйоство ---";
//    qDebug()<<"тип: "<< m_TypeUnitNode.value( unit->getType());
    qDebug()<<"Актуальные параметры:";

    modelTreeUN->list_Equals.clear();
    modelTreeUN->updateUNs();

    qDebug()<<"---------------------------------------";
    foreach(UnitNode *un, List1 )
    {
    //    qDebug()<<"------";
    //    qDebug()<<unit->getName();
    //    qDebug()<<un->getName();



        bool res=compare(unit,un);

        if(res==true)
        {

        qDebug()<<res;
        modelTreeUN->list_Equals.append(modelTreeUN->findeIndexUN(un));
        }
   }
    if(modelTreeUN->list_Equals.count()>0)
    {   if(modelTreeUN->list_Equals.count()>1)
         this->ui->stackedWidget_3->setCurrentIndex(1);

        qDebug()<<"Найдены:";
        foreach(QModelIndex ind, modelTreeUN->list_Equals_for_chanell )
        {
        this->ui->treeView->update(ind);
            UnitNode *un = static_cast<UnitNode*>(ind.internalPointer());
            qDebug()<<un->getName();
        }


    //  this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals.at(0));

        }

}

void MainWindowCFG::updateName(QString name)
{
    if(this->ui->checkBox->isChecked())
    {
//    qDebug()<<"update: ";
    this->ui->uName_combobox->setCurrentText(name);
    }
}

void MainWindowCFG::clear_list_equals()
{
//    qDebug()<<"PROFIT";
    modelTreeUN->list_Equals_for_chanell.clear();
       modelTreeUN->updateUNs();
}

void MainWindowCFG::prev()
{
    if(modelTreeUN->list_Equals_for_chanell.count()>0)
    {
                bool res=false;
    for(int i=0;i<(modelTreeUN->list_Equals_for_chanell.count());i++)
    {
        QModelIndex ind=modelTreeUN->list_Equals_for_chanell.at(i);
        if(this->ui->treeView->currentIndex()==ind){
          if(i>0)
           this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals_for_chanell.at(i-1));

            else
          this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals_for_chanell.at(modelTreeUN->list_Equals_for_chanell.count()-1));
           break;
        }

    }
    if(res==false)
          this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals_for_chanell.at(0));
    }
    else
        if(modelTreeUN->list_Equals.count()>0)
        {
        for(int i=0;i<(modelTreeUN->list_Equals.count());i++)
        {
            QModelIndex ind=modelTreeUN->list_Equals.at(i);
            if(this->ui->treeView->currentIndex()==ind){
              if(i>0)
               this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals.at(i-1));

                else
              this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals.at(modelTreeUN->list_Equals.count()-1));
               break;
            }

        }
        }




    //    modelTreeUN->list_Equals_for_chanell.
    //    this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
    UnitNode *unit = static_cast<UnitNode*>(this->ui->treeView->currentIndex().internalPointer());
    this->get_option(unit);
}

void MainWindowCFG::next()
{
    if(modelTreeUN->list_Equals_for_chanell.count()>0)
    {
        bool res=false;
        for(int i=0;i<(modelTreeUN->list_Equals_for_chanell.count());i++)
        {
            QModelIndex ind=modelTreeUN->list_Equals_for_chanell.at(i);
            if(this->ui->treeView->currentIndex()==ind){
                res=true;
                qDebug()<<i;
                if(i<(modelTreeUN->list_Equals_for_chanell.count()-1))
                {
                 qDebug()<<"[1]";
               this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals_for_chanell.at(i+1));
                }
                else
                {
                 qDebug()<<"[2]";
               this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals_for_chanell.at(0));
                }
               break;
            }

        }
        if(res==false)
          this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals_for_chanell.at(0));

    }
    else
    if(modelTreeUN->list_Equals.count()>0)
    {
        for(int i=0;i<(modelTreeUN->list_Equals.count());i++)
        {
            QModelIndex ind=modelTreeUN->list_Equals.at(i);
            if(this->ui->treeView->currentIndex()==ind){
                qDebug()<<i;
                if(i<(modelTreeUN->list_Equals.count()-1))
                {
                 qDebug()<<"[1]";
               this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals.at(i+1));
                }
                else
                {
                 qDebug()<<"[2]";
               this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals.at(0));
                }
               break;
            }

        }

    }
    UnitNode *unit = static_cast<UnitNode*>(this->ui->treeView->currentIndex().internalPointer());
    this->get_option(unit);
}

void MainWindowCFG::find_from_options(QList<QString> list)
{


    qDebug()<<"find_from_options";

    modelTreeUN->list_Equals.clear();
    modelTreeUN->updateUNs();


    foreach(QString name,list)
    {
    //    qDebug()<<name<<": "<<this->ui->unitFinder->get_value(name);
    }

    QList<UnitNode *> List1;


    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN

  //  qDebug()<<"-- Ищу устрйоство ---";
//    qDebug()<<"тип: "<< m_TypeUnitNode.value( unit->getType());
 //   qDebug()<<"Актуальные параметры:";

    modelTreeUN->list_Equals_for_chanell.clear();

 //   qDebug()<<"---------------------------------------";
    foreach(UnitNode *un, List1 )
    {
    //    qDebug()<<"------";
    //    qDebug()<<unit->getName();
    //    qDebug()<<un->getName();

        bool res=true;
qDebug()<<"[1]";
foreach(QString name,list)
 {
    QString value = this->unitFinder_f->get_value(name);

        if(name=="Type")
        {
         if(un->getType()!=value.toInt())
             res=false;
        }

        if(name=="Num1")
        {
            if(un->getNum1()!=value.toInt())
                res=false;
        }

        if(name=="Num2")
        {
            if(un->getNum2()!=value.toInt())
                res=false;
        }

        if(name=="Num3")
        {
            if(un->getNum3()!=value.toInt())
                res=false;
        }

        if(name=="DK")
        {
            if(un->getDK()!=value.toInt())
                res=false;
        }

        if(name=="Bazalt")
        {
            if(un->getBazalt()!=value.toInt())
                res=false;
        }

        if(name=="Metka")
        {
            if(un->getMetka()!=value.toInt())
                res=false;
        }

        if(name=="Razriv")
        {
            if(un->getRazriv()!=value.toInt())
                res=false;
        }

        if(name=="AdamOff")
        {
            if(un->getAdamOff()!=value.toInt())
                res=false;
        }

        if(name=="AlarmMsgOn")
        {
            if(un->getAlarmMsgOn()!=value.toInt())
                res=false;
        }

        if(name=="ConnectBlock")
        {
            if(un->getConnectBlock()!=value.toInt())
                res=false;
        }

        if(name=="OutType")
        {
            if(un->getOutType()!=value.toInt())
                res=false;
        }

        if(name=="UdpUse")
        {
            if(un->getUdpUse()!=value.toInt())
                res=false;
        }

        if(name=="UdpAdress")
        {
            if(un->getUdpAdress()!=value)
                res=false;
        }

        if(name=="UdpPort")
        {
            if(un->getUdpPort()!=value.toInt())
                res=false;
        }

        if(name=="UdpTimeout")
        {
            if(un->getUdpTimeout()!=value.toInt())
                res=false;
        }

        if(name=="Icon1Path")
        {
            if(un->getIcon1Path()!=value)
                res=false;
        }

        if(name=="Icon2Path")
        {
            if(un->getIcon2Path()!=value)
                res=false;
        }

        if(name=="Icon3Path")
        {
            if(un->getIcon3Path()!=value)
                res=false;
        }

        if(name=="Icon4Path")
        {
            if(un->getIcon4Path()!=value)
                res=false;
        }
 }
qDebug()<<"[2]";
        /*
        if(UdpUse==0)
        if(un->getUdpUse()==UdpUse)
        if(un->getNum3()==RS485_port) //ищем юниты котрые всият на одном порте с нашим
        res=true;
                    //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

        if(UdpUse==1)
        if(un->getUdpUse()==UdpUse)
        if(un->getUdpAdress()==UdpAdress)//ищем юниты котрые всият на одном адресе с нашим
        if(un->getUdpPort()==UdpPort)
        res=true;
        */

        if(res==true)
        {

        qDebug()<<res;
        modelTreeUN->list_Equals_for_chanell.append(modelTreeUN->findeIndexUN(un));
        }
}

    if(modelTreeUN->list_Equals_for_chanell.count()>0)
    {
        if(modelTreeUN->list_Equals_for_chanell.count()>1)
         this->ui->stackedWidget_3->setCurrentIndex(1);
        qDebug()<<"Найдены:";
        foreach(QModelIndex ind, modelTreeUN->list_Equals_for_chanell)
        {
        this->ui->treeView->update(ind);
            UnitNode *un = static_cast<UnitNode*>(ind.internalPointer());
            qDebug()<<un->getName();
        }


      this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals_for_chanell.at(0));

        }


}

void MainWindowCFG::double_unit_slot(UnitNode *un)
{
    qDebug()<<"[double_unit_slot]";
    this->ui->treeView->setCurrentIndex(this->modelTreeUN->findeIndexUN(un));
}

void MainWindowCFG::slot_to_get_options(QModelIndex index)
{
UnitNode *unit = static_cast<UnitNode*>(index.internalPointer());
this->get_option(unit);
}

void MainWindowCFG::unitNameChanged(QStandardItem */*item*/)
{
    //qDebug()<<"[unitNameChanged]";
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
    qDebug()<<"[on_treeView_clicked]";

 this->ui->stackedWidget_3->setCurrentIndex(0);
 current_wgt()->setEnabled(true);

this->ui->edit_unit_button->setDisabled(true);
    current_index=index;
    if(current_index.isValid())
    {
     this->ui->tabWidget->setCurrentIndex(2);

   //     this->ui->stackedWidget->setCurrentWidget()
   //     //qDebug()<<"[+]";
    UnitNode *unit = static_cast<UnitNode*>(index.internalPointer());
  //  this->object_menu_change(unit->getType());

this->get_option(unit);

show_equals(unit);


    }
    else
    {
   //qDebug()<<"!!!";

    }

}


void MainWindowCFG::get_option(UnitNode* unit)
{
   this->ui->textEdit->clear();
    //qDebug()<<"get option";
    unit->show();
    selected_type=unit->getType();

    foreach(UnitWidget* wgt,l_UnitWidgets){
        if(wgt->getID()==selected_type){

     wgt->get_string(unit);
     this->ui->textEdit->append(wgt->get_string(unit));

        }
    }

  //  current_wgt()->get_option(unit);

//       this->ui->stackedWidget_2->setCurrentWidget(this->ui->nothing);
    /*
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
    break;

    case TypeUnitNode::RASTRMTV:
    this->get_option_RASTRMTV(unit);
    break;

    case TypeUnitNode::INFO_TABLO:
    this->get_option_INFO_TABLO(unit);
    break;

    case TypeUnitNode::KL:
    this->get_option_KL(unit);
    break;

    }
*/

}

void MainWindowCFG::get_option_GROUP(UnitNode *unit)
{
    unit->setNum1(-1);
    unit->setNum2(-1);
    unit->setNum3(-1);

    this->ui->textEdit->clear();
    QString string1;
   //     string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append(" ");//  Группа</b> ");
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b>");//
    string1.append(unit->getName());
    this->ui->textEdit->append(string1);
}




bool MainWindowCFG::this_name_is_free(QString Name)
{


    foreach(UnitNode *un, this->modelTreeUN->listItemUN )
    {
     //qDebug()<< un->getName()<<" "<< Name ;
     if(un->getName()==Name)
     {
         //qDebug()<<"уже есть такое имя";
         return false;
     }


    }


    return true;
}



void MainWindowCFG::update_rif_comport_table()
{
/*

    ui->_2->setRowCount(0);
  //qDebug()<<"количество операторов "<<comports.count();
  int cnt;



for(int i=0;i<comports.count();i++)
{
        ComPort* port=comports.at(i);
   //    //qDebug()<<" "<<i <<" "<<port->get_RifPortSpeed()<<" "<<port->get_RifPortInterval();

      cnt=this->ui->tableWidget_2->rowCount();
   //   //qDebug()<<"/"<<cnt;
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

    //this->ui->mouse_X->setText(QString::number(mouseLoc.x()));
   // this->ui->mouse_Y->setText(QString::number(mouseLoc.y()));

    timer->start(10);
}

















bool MainWindowCFG::set_option(UnitNode *unit, UnitNode* parent)
{



current_wgt()->set_option(unit);


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
     //qDebug()<<"[Open]";
     QString dir= QCoreApplication::applicationDirPath() + "/rifx.ini";

         //qDebug()<<dir;

     QString patch=QFileDialog::getOpenFileName(this, "open file",dir,"*.ini");
      qDebug()<<"patch = "<<patch;
      if(patch!="")
      {
          this->ui->label_filepath->setText(patch);
          last_ini_patch=patch;
          this->modelTreeUN->rootItemUN->deleteAll();
          this->modelTreeUN->loadSettings(patch);


//----------------------------------------------------------

          QList<UnitNode *> List;
          this->modelTreeUN->getListFromModel(List,modelTreeUN->rootItemUN);//this->modelTreeUN->rootItemUN
          foreach(UnitNode *un, List )
          {
              un->setBroken(false);
              foreach(UnitWidget* wgt,l_UnitWidgets){


                  if(un->getType()==wgt->getID()){

                  QModelIndex index=this->modelTreeUN->findeIndexUN(un);
                  current_index= this->modelTreeUN->parent(index);

                  un->setBroken(!(wgt->accepted(un)));


                  }

              }
          }





//----------------------------------------------------------

          if(modelTreeUN->rowCount()==0)
          {
          this->modelTreeUN->makeEmptyTree();
          }

           this->default_OPERATORS();
           this->default_RIF();
           this->load_other_options_from_ini_file(patch);


            open_device_tree();
      }

 //    this->modelTreeUN->updateUNStructure();

}


void MainWindowCFG::on_actionSave_triggered()
{



        QString dir="";

        if(last_ini_patch=="")
            dir= QCoreApplication::applicationDirPath() + "/rifx.ini";
        else
            dir=last_ini_patch;

        qDebug()<<"dir "<<dir;

       QString path=QFileDialog::getSaveFileName(this, "save file",dir,"*.ini");




       QFile file(path);
       if(file.open(QIODevice::WriteOnly | QIODevice::Text))
       {
         QTextStream out(&file);
         out << "This file is generated by Qt\n";

         // optional, as QFile destructor will already do it:
         file.close();


    this->save_ini(path);
    My_settings my(path);
         for(int i=0;i<operators.count();i++)
             {
             Operator* op=operators.at(i);
             QString strGroup("Operator_%1");
             strGroup=strGroup.arg(i);

     QByteArray ar=(this->XOR_Crypt(op->getPW(),"start7")).toLocal8Bit().toHex();

             my.set_value(strGroup, "PW", &ar);
             }
//     my->save_ini(path);

         qDebug()<<"пароль 3 "<<ui->SQL_password_lineEdit->text();


                  if(this->ui->SQL_type_comboBox->currentText()!="Выкл")
                  {



                  //Set SQL password value
                  QByteArray ar=(this->XOR_Crypt(this->ui->SQL_password_lineEdit->text(),"start7")).toLocal8Bit().toHex();


                      if(this->ui->SQL_type_comboBox->currentText()=="MySQL")
                      {
                        my.set_value("MYSQL", "Password", &ar);

                      }
                      if(this->ui->SQL_type_comboBox->currentText()=="PostgresSQL")
                      {
                        my.set_value("PostgresSQL", "Password", &ar);
                      }

                  //Set operators value

                      for(int i=0;i<operators.count();i++)
                          {
                          Operator* op=operators.at(i);
                          QString strGroup("Operator_%1");
                          strGroup=strGroup.arg(i);

                  QByteArray ar=(this->XOR_Crypt(op->getPW(),"start7")).toLocal8Bit().toHex();

                          my.set_value(strGroup, "PW", &ar);
                          }

                  //Save
 //                     my->save_ini(path);
                      qDebug()<<"[02]";      /*   */



                  }
/*
                  //Везде где есть lan и lon убираем кавычки
QList<UnitNode *> List;
this->modelTreeUN->getListFromModel(List);
for(int i=1;i<List.count();i++)
{
UnitNode* unit=List.at(i);
QString strGroup("Obj_%1");
strGroup=strGroup.arg(i);
my.beginGroup(strGroup);

QByteArray lan= my.get_value( "lan");
QByteArray lon= my.get_value( "lon");
my.endGroup();

qDebug()<<strGroup;
qDebug()<<"lan "<<lan;
qDebug()<<"lan "<<lon;

QByteArray true_lan;
true_lan.clear();

for(int i=0;i<lan.size();i++)
{

 qDebug()<<i<<"....."<<(quint8(lan[i]));

 if(quint8(lan[i])!=34)
 true_lan.append(lan[i]);
}

qDebug()<<"--------------";
QByteArray true_lon;
true_lon.clear();
for(int i=0;i<lon.size();i++)
{
 qDebug()<<i<<"....."<<(quint8(lon[i]));
  if(quint8(lon[i])!=34)
 true_lon.append(lon[i]);
}

true_lan=true_lan.toHex();
true_lon=true_lon.toHex();
qDebug()<<"true_lan "<<true_lan;
qDebug()<<"true_lon "<<true_lon;



 //my.set_value(strGroup, "lan", &true_lan);
// my.set_value(strGroup, "lon", &true_lon);

}
*/




//delete my;
}
}

void MainWindowCFG::on_treeView_activated(const QModelIndex &/*index*/)
{
    //qDebug()<<"activated";
}





bool MainWindowCFG::eventFilter(QObject *obj, QEvent *event)
{
    /*
    if (obj == ui->treeView)
    {
        QModelIndex qmi = ui->treeView->currentIndex();
        //qDebug()<<qmi.row();
        if (event->type() == QEvent::KeyPress )
        {
           QKeyEvent* key_ev = dynamic_cast<QKeyEvent*>(event);
                QModelIndex qmi = ui->treeView->currentIndex();

           QModelIndex new_ind;
           UnitNode *unit;

           switch(key_ev->key())
           {
           case Qt::Key_Down:
        //    //qDebug()<<"[Down]";


         //   unit = static_cast<UnitNode*>(new_ind.internalPointer());

         //   this->get_option(unit);


           break;

           case Qt::Key_Up:
        //    //qDebug()<<"[Up]";

          //  unit = static_cast<UnitNode*>(new_ind.internalPointer());


          //  this->get_option(unit);



           break;
           }



        }
    }
    */

}

UnitWidget *MainWindowCFG::current_wgt()
{
    return dynamic_cast<UnitWidget*>(this->ui->stack->currentWidget());
}

bool MainWindowCFG::compare(UnitNode *unit, UnitNode *un)
{

    foreach(UnitWidget* wgt,l_UnitWidgets){
        if(wgt->getID()==unit->getType()){

        if (wgt->equal(unit,un)){
            return true;
        }

        }
    }

    return false;
}



void MainWindowCFG::operator_add(Operator * op)
{
   //qDebug()<<"operator_add";
   operators.append(op);
   update_operators_table();
}

void MainWindowCFG::operator_edit(Operator *op)
{
   //qDebug()<<"operator_edit";
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
   //qDebug()<<"operator_delete";

}


QString MainWindowCFG::XOR_Crypt(QString src,QString key)
{
        //qDebug()<<"[XOR_Crypt]";
    QByteArray ar=src.toLocal8Bit();
    //qDebug()<<src<<" "<<ar.toHex();
//qDebug()<<"src "<<src;
//QString key="start7";

    QByteArray pw=key.toLocal8Bit();

    //qDebug()<<pw.size();
    QByteArray res;
    res.clear();
    for (int x=1;x<ar.size()+1;x++)
    {
    //qDebug()<<"---"<<x<<"-------------";

           int val1=  pw[(x)%pw.size()] * 2;

         int inx=ar[x-1];
        //qDebug()<<" val1 "<<val1<<"inx "<<inx;

         int val2= inx ^ val1;
         char chr = (char)val2;
         //qDebug()<<chr;
 //         OutputDebugString(&in[x]);
 //         OutputDebugString(&pass[x%pass.Length()+1]);
 //         OutputDebugString(&chr);
 //          OutputDebugString("----------------");
 //      out +=  chr; /// ??????? * 2 ? ????? ?????????? ?????????
         res.append(chr);
    }
    QString str_res = QString::fromLocal8Bit(res);
    //qDebug()<<"res "<<str_res<<" "<<str_res.toLocal8Bit().toHex();
            //qDebug()<<"[end XOR_Crypt]";
return str_res;

}

void MainWindowCFG::update_operators_table()
{
      ui->tableWidget->setRowCount(0);
 //   //qDebug()<<"количество операторов "<<operators.count();
    int cnt;
    foreach(Operator* op, operators)
    {

   //     //qDebug()<<op->getN1()<<" "<<op->getN2()<<" "<<op->getFN();

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
        this->ui->tableWidget->item(cnt,4)->setFlags(this->ui->tableWidget->item(cnt,4)->flags() ^ Qt::ItemIsEditable);
    }
}

QString MainWindowCFG::get_unit_name(int /*type*/)
{
    return QString();
}




void MainWindowCFG::setDK()
{
//    //qDebug()<<"[!!!!!!!!!!!!!!!!!!!!!!]";
QModelIndex index = this->ui->treeView->currentIndex();
UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
//qDebug()<<un->getName();

if(un->getDK()==0)
{

    //qDebug()<<"[0]";
    un->setDK(true);
    //qDebug()<<"[1]";
}
else
{
    //qDebug()<<"[1]";
    un->setDK(false);
    //qDebug()<<"[0]";
}


}

void MainWindowCFG::YZ_MONOLIT()
{

    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    //qDebug()<<un->getName();

    //qDebug()<<"YZ_MONOLIT()";
    if(un->getBazalt()==0)
    {

        //qDebug()<<"[0]";
        un->setBazalt(true);
        //qDebug()<<"[1]";
    }
    else
    {
        //qDebug()<<"[1]";
        un->setBazalt(false);
        //qDebug()<<"[0]";
    }
}

void MainWindowCFG::setAlarmMsgOn()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    //qDebug()<<un->getName();

    //qDebug()<<"YZ_MONOLIT()";
    if(un->getAlarmMsgOn()==0)
    {

        //qDebug()<<"[0]";
        un->setAlarmMsgOn(true);
        //qDebug()<<"[1]";
    }
    else
    {
        //qDebug()<<"[1]";
        un->setAlarmMsgOn(false);
        //qDebug()<<"[0]";
    }
}

bool MainWindowCFG::set_AdamOff_for_all_IU_BL_IP_instances(UnitNode *unit)
{

   qDebug()<<"Посмотри - это список дубликатов:";

   int val=unit->getAdamOff();
   foreach(QModelIndex ind, modelTreeUN->list_Equals)
   {
     UnitNode *un = static_cast<UnitNode*>(ind.internalPointer());

    qDebug()<< un->getName();
    un->setAdamOff(val);



   }


}



void MainWindowCFG::setAdamOff()
{
    //qDebug()<<QString::number(val_for_setAdamoff);
}




void MainWindowCFG::keyPressEvent(QKeyEvent *event)
{
  //  qDebug()<<ui->tabWidget->currentIndex();

    if(ui->tabWidget->currentIndex()==2){

            qDebug()<<event->key();
       if(event->key()==16777220)        {

            qDebug()<<"PROFIT";
            add_unit();


        }


    }
}

void MainWindowCFG::setAdamOff_off()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(0);
    set_AdamOff_for_all_IU_BL_IP_instances(un);
}

void MainWindowCFG::setAdamOff_5_sec()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(1);
    set_AdamOff_for_all_IU_BL_IP_instances(un);
}

void MainWindowCFG::setAdamOff_10_sec()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(2);
    set_AdamOff_for_all_IU_BL_IP_instances(un);
}

void MainWindowCFG::setAdamOff_30_sec()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(3);
    set_AdamOff_for_all_IU_BL_IP_instances(un);
}

void MainWindowCFG::setAdamOff_1_min()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(4);
    set_AdamOff_for_all_IU_BL_IP_instances(un);
}

void MainWindowCFG::setAdamOff_5_min()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(5);
    set_AdamOff_for_all_IU_BL_IP_instances(un);
}

void MainWindowCFG::setAdamOff_10_min()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(6);
    set_AdamOff_for_all_IU_BL_IP_instances(un);
}

void MainWindowCFG::setAdamOff_20_min()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(7);
    set_AdamOff_for_all_IU_BL_IP_instances(un);
}

void MainWindowCFG::setAdamOff_30_min()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(8);
    set_AdamOff_for_all_IU_BL_IP_instances(un);
}

void MainWindowCFG::setAdamOff_1_hour()
{
    QModelIndex index = this->ui->treeView->currentIndex();
    UnitNode *un = static_cast<UnitNode*>(index.internalPointer());
    un->setAdamOff(9);
    set_AdamOff_for_all_IU_BL_IP_instances(un);
}

void MainWindowCFG::open_edit_menu()
{
    qDebug()<<"[open_edit_menu]";
    this->ui->tabWidget->setCurrentIndex(2);

    //qDebug()<<"edit menu";

    QModelIndex index =this->ui->treeView->currentIndex();
    UnitNode *unit = static_cast<UnitNode*>(index.internalPointer());

    object_menu_change(unit->getType());
    current_wgt()->get_option(unit);
    this->ui->uType_combobox->setCurrentText(m_TypeUnitNode.value(unit->getType()));
    this->ui->edit_unit_button->setEnabled(true);

}

void MainWindowCFG::open_device_tree()
{
  //qDebug()<<"open";

  expandChildren(this->modelTreeUN->index(0,0,QModelIndex()));


}

void MainWindowCFG::close_device_tree()
{
  //qDebug()<<"close";
   this->ui->treeView->collapse(this->modelTreeUN->index(0,0,QModelIndex()));
}

bool MainWindowCFG::can_i_add_or_not(int /*type_parrent*/, int /*type_child*/)
{
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

void MainWindowCFG::object_menu_change(int type)
{
    foreach(UnitWidget* wgt, l_UnitWidgets){
        if(wgt->getID()==type){
            this->ui->stack->setCurrentWidget(wgt);
             wgt->setVisible(true);


        }else{
        wgt->setVisible(false);
        }

    }

    /*
    this->ui->stackedWidget_2->setCurrentWidget(this->ui->nothing);
    this->ui->UDP_RS485_Widget->setVisible(false);
    switch(type)
    {

    case TypeUnitNode::GROUP:
    this->ui->stackedWidget->setCurrentWidget(this->ui->Group_groupbox);
    break;

    case TypeUnitNode::SD_BL_IP:
    //qDebug()<<"[!!!!!!!!!!!!!!!!!!!!!!!!!!!CD!!!]";

    this->ui->stackedWidget->setCurrentWidget(this->ui->SD_BL_IP_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" UDP");
    this->ui->timeout_doubleSpinBox->setMinimum(timeouts.value(type));
    this->ui->timeout_doubleSpinBox->setValue(timeouts.value(type));
    coordinate_menu(true,false,0,0,"");
    break;

    case TypeUnitNode::IU_BL_IP:
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" UDP");

    this->ui->timeout_doubleSpinBox->setMinimum(timeouts.value(type));
    this->ui->timeout_doubleSpinBox->setValue(timeouts.value(type));

    this->ui->stackedWidget->setCurrentWidget(this->ui->IU_BL_IP_groupbox);
    break;

    case TypeUnitNode::TG:
    this->ui->stackedWidget->setCurrentWidget(this->ui->TG_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" UDP");
    this->ui->timeout_doubleSpinBox->setMinimum(timeouts.value(type));
    this->ui->timeout_doubleSpinBox->setValue(timeouts.value(type));
    coordinate_menu(true,false,0,0,"");
    break;

    case TypeUnitNode::RLM_KRL:
    this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_KRL_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" UDP");
    this->ui->timeout_doubleSpinBox->setMinimum(timeouts.value(type));
    this->ui->timeout_doubleSpinBox->setValue(timeouts.value(type));
    coordinate_menu(true,false,0,0,"");

    break;

    case TypeUnitNode::RLM_C:
    this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_C_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" UDP");
    this->ui->timeout_doubleSpinBox->setMinimum(timeouts.value(type));
    this->ui->timeout_doubleSpinBox->setValue(timeouts.value(type));
    coordinate_menu(true,false,0,0,"");
    break;

    case TypeUnitNode::BOD_T4K_M:
    this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_T4K_M_groupbox);
    this->ui->UDP_RS485_Widget->setVisible(true);
    this->ui->UDP_RS485_stacked->setCurrentWidget(this->ui->RS485);
    this->ui->UDP_RS485_combobox->setCurrentText(" UDP");
    this->ui->timeout_doubleSpinBox->setMinimum(timeouts.value(type));
    this->ui->timeout_doubleSpinBox->setValue(timeouts.value(type));
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
    this->ui->UDP_RS485_combobox->setCurrentText(" UDP");
    this->ui->timeout_doubleSpinBox->setMinimum(timeouts.value(type));
    this->ui->timeout_doubleSpinBox->setValue(timeouts.value(type));
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
    this->ui->UDP_RS485_combobox->setCurrentText(" UDP");
    this->ui->timeout_doubleSpinBox->setMinimum(timeouts.value(type));
    this->ui->timeout_doubleSpinBox->setValue(timeouts.value(type));
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
    coordinate_menu(true,false,0,0,"");
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
    this->ui->UDP_RS485_combobox->setCurrentText(" UDP");
    this->ui->timeout_doubleSpinBox->setMinimum(timeouts.value(type));
    this->ui->timeout_doubleSpinBox->setValue(timeouts.value(type));
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
        //qDebug()<<"EMPTY";
    this->ui->stackedWidget->setCurrentWidget(this->ui->empty_space_groupbox);
    break;
    }

    */
}

void MainWindowCFG::object_menu_set_settings_default(int type)
{


     //   this->ui->uName_combobox->setCurrentText("");
    this->ui->uName_combobox->setCurrentText("");
//qDebug()<<"[object_menu_set_settings_default]";

current_wgt()->get_option(nullptr);
/*
switch(type)
{
case TypeUnitNode::GROUP:

break;

case TypeUnitNode::SD_BL_IP:


this->ui->stackedWidget->setCurrentWidget(this->ui->SD_BL_IP_groupbox);
this->RS485_UDP_set_default_with_timeout(timeouts.value(type));
this->ui->SD_BL_IP_num_combobox->setCurrentIndex(0);
this->ui->SD_BL_IP_OutType->setCurrentText(m_SD_BL_IP_OutType.value(0));

coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::IU_BL_IP:
RS485_UDP_set_default_with_timeout(timeouts.value(type));
this->ui->stackedWidget->setCurrentWidget(this->ui->IU_BL_IP_groupbox);
break;

case TypeUnitNode::TG:
this->ui->stackedWidget->setCurrentWidget(this->ui->TG_groupbox);
RS485_UDP_set_default_with_timeout(timeouts.value(type));
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::RLM_KRL:
this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_KRL_groupbox);
RS485_UDP_set_default_with_timeout(timeouts.value(type));
coordinate_menu(true,false,0,0,"");

break;

case TypeUnitNode::RLM_C:
this->ui->stackedWidget->setCurrentWidget(this->ui->RLM_C_groupbox);
RS485_UDP_set_default_with_timeout(timeouts.value(type));
coordinate_menu(true,false,0,0,"");
break;

case TypeUnitNode::BOD_T4K_M:
this->ui->stackedWidget->setCurrentWidget(this->ui->BOD_T4K_M_groupbox);
RS485_UDP_set_default_with_timeout(timeouts.value(type));
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
RS485_UDP_set_default_with_timeout(timeouts.value(type));
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
RS485_UDP_set_default_with_timeout(timeouts.value(type));
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


this->ui->SSOI_SD_Num1->setCurrentIndex(0);
this->ui->SSOI_SD_Num2->setCurrentIndex(0);
this->ui->SSOI_SD_Num3->setCurrentIndex(0);
this->ui->SSOI_SD_OutType->setCurrentText(m_SSOI_SD_OutType.value(0));
break;

case TypeUnitNode::SSOI_IU:
this->ui->stackedWidget->setCurrentWidget(this->ui->SSOI_IU_groupbox);
break;

case TypeUnitNode::ADAM:
this->ui->stackedWidget->setCurrentWidget(this->ui->ADAM_groupbox);
break;

case TypeUnitNode::TOROS:
this->ui->stackedWidget->setCurrentWidget(this->ui->TOROS_groupbox);
RS485_UDP_set_default_with_timeout(timeouts.value(type));
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
    //qDebug()<<"EMPTY";
this->ui->stackedWidget->setCurrentWidget(this->ui->empty_space_groupbox);
break;
}
*/
}


void MainWindowCFG::object_menu_set_settings_from(UnitNode *unit)
{

this->ui->uName_combobox->setCurrentText(unit->getName());

}


void MainWindowCFG::Name_update()
{

  UnitNode *parent = static_cast<UnitNode*>(current_index.internalPointer());

    if(this->ui->checkBox->isChecked())
    {
 /*   QString Name;
    Name.clear();
    int type=m_TypeUnitNode.key(this->ui->uType_combobox->currentText());
//    Name.append(this->ui->uType_combobox->currentText());
    QString ip_str;
    QStringList myStringList;



    //current_wgt()

    switch(type)
    {

    case TypeUnitNode::GROUP:
Name.append("Группа ");
    break;

    case TypeUnitNode::SD_BL_IP:
Name.append("БЛ");
ip_str=this->ui->ipadress_combobox->currentText();
myStringList = ip_str.split(".");
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

Name.append(ip_str);
Name.append(" СД");
Name.append("-");

//if(this->ui->SD_BL_IP_num_combobox->currentText().toInt()<10)
//Name.append("0");

Name.append(this->ui->SD_BL_IP_num_combobox->currentText());


    break;

    case TypeUnitNode::IU_BL_IP:
        Name.append("БЛ");
        ip_str=this->ui->ipadress_combobox->currentText();
        myStringList = ip_str.split(".");
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

        Name.append(ip_str);
        Name.append(" ИУ");
Name.append("-");
//if(this->ui->IU_BL_IP_num_combobox->currentText().toInt()<10)
//Name.append("0");
Name.append(this->ui->IU_BL_IP_num_combobox->currentText());

    break;

    case TypeUnitNode::TG:
Name.append("Точка-");
if(this->ui->TG_adress_combobox->currentText().toInt()<10)
Name.append("0");
Name.append(this->ui->TG_adress_combobox->currentText());
Name.append("-ЧЭ");
Name.append(this->ui->TG_U4_4A_combobox->currentText());
    break;

    case TypeUnitNode::RLM_KRL:
Name.append(this->ui->RLM_KRL_type_comboBox->currentText());
Name.append("-");
if(this->ui->RLM_KRL_adress_combobox->currentText().toInt()<10)
Name.append("0");
Name.append(this->ui->RLM_KRL_adress_combobox->currentText());
    break;

    case TypeUnitNode::RLM_C:
Name.append("РИФ-РЛМ-С-");
if(this->ui->RLM_C_adress_combobox->currentText().toInt()<10)
Name.append("0");
Name.append(this->ui->RLM_C_adress_combobox->currentText());
    break;

    case TypeUnitNode::BOD_T4K_M:
Name.append("Точка-М: БОД");
if(this->ui->BOD_T4K_M_adress_combobox->currentText().toInt()<10)
Name.append("0");
Name.append(this->ui->BOD_T4K_M_adress_combobox->currentText());
    break;

    case TypeUnitNode::Y4_T4K_M:
        if(parent){
            Name.append("БОД");
            if(parent->getNum1()<10)
            Name.append("0");
            Name.append(QString::number(parent->getNum1()));
                        Name.append(" ");
        }
        Name.append("Участок ");
        Name.append(this->ui->Y4_T4K_M_combobox->currentText());
    break;

    case TypeUnitNode::DD_T4K_M:

Name.append(" ДД");
if(parent){
    Name.append(QString::number(parent->getNum2()/100));
Name.append("-");
}
Name.append(this->ui->DD_T4K_M_combobox->currentText());
    break;

    case TypeUnitNode::BOD_SOTA:
Name.append("Сота: БОД");
if(this->ui->BOD_SOTA_M_adress_combobox->currentText().toInt()<10)
Name.append("0");
Name.append(this->ui->BOD_SOTA_M_adress_combobox->currentText());
    break;

    case TypeUnitNode::Y4_SOTA:

        if(parent){
            Name.append("БОД");
            if(parent->getNum1()<100)
            Name.append("0");
            Name.append(QString::number(parent->getNum1()));
                        Name.append(" ");
        }
Name.append("Участок ");
Name.append(this->ui->U4_Sota_M_combobox->currentText());
    break;

    case TypeUnitNode::DD_SOTA:

Name.append(" ДД");
if(parent){
    Name.append(QString::number(parent->getNum2()/100));
Name.append("-");
}
Name.append(this->ui->DD_Sota_M_combobox->currentText());
    break;

    case TypeUnitNode::ONVIF:
//Name.append(this->ui->uType_combobox->currentText());
Name.append("Камера ONVIF ");
Name.append(" ");
Name.append(this->ui->ONVIF_IPaddr_combobox->currentText());

    break;

    case TypeUnitNode::NET_DEV:
Name.append("Сетевое ");
Name.append(this->ui->NET_DEV_IP_combobox->currentText());
    break;

    case TypeUnitNode::STRAZH_IP:
Name.append("Страж-IP ");
Name.append(this->ui->STRAZH_IP__IPaddr_combobox->currentText());
    break;

    case TypeUnitNode::BL_IP:

    break;

    case TypeUnitNode::SSOI_SD:

Name.append("Канал");
Name.append(this->ui->SSOI_SD_Num1->currentText());
Name.append("-БЛ");
Name.append(this->ui->SSOI_SD_Num2->currentText());


Name.append("-СД");
if(this->ui->SSOI_SD_Num3->currentText()=="Вскрытие")
Name.append("-Вскрытие");
else
Name.append(this->ui->SSOI_SD_Num3->currentText());


//if(this->ui->SSOI_SD_OutType->currentIndex()>0)
//{
//Name.append(" тип:");
//Name.append(this->ui->SSOI_SD_OutType->currentText());
//}

    break;

    case TypeUnitNode::SSOI_IU:
Name.append("Канал");
Name.append(this->ui->SSOI_IU_Num1->currentText());
Name.append("-БЛ");
Name.append(this->ui->SSOI_IU_Num2->currentText());
Name.append("-");
Name.append(this->ui->SSOI_IU_Num3->currentText());
    break;

    case TypeUnitNode::ADAM:
Name.append("ADAM ");
Name.append(this->ui->ADAM_Num1->currentText());
Name.append("-");
Name.append(this->ui->ADAM_Num2->currentText());
    break;

    case TypeUnitNode::TOROS:
Name.append("Торос-");
Name.append(this->ui->TOROS_Num1->currentText());
    break;

    case TypeUnitNode::DEVLINE:
Name.append("ТВ-Камера ");
Name.append(QString::number(this->ui->DEVLINE_Num1->value()));
Name.append(" (Поток ");
Name.append(this->ui->DEVLINE_OutType->currentText());
Name.append(")");
    break;

    case TypeUnitNode::RASTRMTV:
    Name.append("Камера-");



    Name.append(this->ui->RASTRMTV_Num3->currentText());

    break;

    case TypeUnitNode::INFO_TABLO:
        Name.append("Участок: ");
        Name.append(this->ui->TABLO_Num2->currentText());
    break;

    case TypeUnitNode::KL:
    Name.append("КЛ-");
    if(this->ui->KL_adress_combobox->currentText().toInt()<10)
    Name.append("0");
    Name.append(this->ui->KL_adress_combobox->currentText());
    Name.append(" СД");
    Name.append(this->ui->KL_CD_combobox->currentText());

    break;

    }

*/
this->ui->uName_combobox->setCurrentText("");
    }
}

void MainWindowCFG::func_to_edit_unit()
{
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    qDebug()<<"edit_unit()";
    QModelIndex index=this->ui->treeView->currentIndex();
    if(index.isValid())
    {
        UnitNode* unit = static_cast<UnitNode*>(index.internalPointer());


    if(m_TypeUnitNode.key(this->ui->uType_combobox->currentText())==unit->getType())
    {
    //qDebug()<<"[PROFIT]";
    unit->setName(this->ui->uName_combobox->currentText());

    current_wgt()->set_option(unit);
    current_wgt()->set_timeouts(unit);

    this->get_option(unit);

    }

    else
    {
    //qDebug()<<"[FALSE]";

    }

    }

//   change_unit();

    this->ui->edit_unit_button->setDisabled(true);
}

QString MainWindowCFG::get_dd(UnitNode* unit)
{
    QModelIndex ind = modelTreeUN->findeIndexUN(unit);
    QModelIndex ind_Y4 = modelTreeUN->parent(ind);
    UnitNode* Y4= static_cast<UnitNode*>(ind_Y4.internalPointer());




    QString str;
    str.clear();
    str.append(QString::number(unit->getNum2()-Y4->getNum2()+1));
    return str;
}

QString MainWindowCFG::get_y4(UnitNode *unit)
{
    QModelIndex ind = this->modelTreeUN->findeIndexUN(unit);
    QModelIndex ind_BOD = this->modelTreeUN->parent(ind);
    UnitNode* BOD= static_cast<UnitNode*>(ind_BOD.internalPointer());

    return QString::number(unit->getNum2()/100);
}




bool MainWindowCFG::add_unit()
{

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


    int type=m_TypeUnitNode.key(this->ui->uType_combobox->currentText());

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
    //qDebug()<<"[Type: "<<type<<"]";

    UnitNode *unit=new UnitNode();

    unit->setBroken(false);

    unit->setType(0);
    unit->setNum1(255);
    unit->setNum2(0);
    unit->setNum3(0);
    unit->setLevel(0);
    unit->setName(" ");
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







    unit->setName(this->ui->uName_combobox->currentText());
    unit->setType(type);

 qDebug()<<"его имя "<<this->ui->uName_combobox->currentText();
 qDebug()<<"его имя "<<unit->getName();


    unit->setLevel(parrent->getLevel()+1);



//current_wgt()->set_option(unit);
    //Проверить можно ли добавлять юнит к этому родителю
    //Определить тип родителя
//    int parrent_type;

    //Определить тип чайлда
//    int child_type;



    if (index.isValid())
    {

        if(current_wgt()->set_option(unit))
        {
            qDebug()<<"его имя "<<unit->getName();
      this->modelTreeUN->appendNewUNInStructure(index,unit);
  //      map.Add(unit->getName(),unit->getPxm(SubTypeApp::configurator),unit->getX(),unit->getY());
      ui->treeView->setCurrentIndex(index);
      this->ui->treeView->expand(index);
        }
        else
        {
            /*
            QModelIndex double_index=find_Double_unit_index();
            UnitNode* un= static_cast<UnitNode*>(double_index.internalPointer());
            if(un)
            {
                get_option(un);
                qDebug()<<"двойник "<<un->getName();
                this->ui->treeView->setCurrentIndex(double_index);

            }


        //qDebug()<<"Нельзя добавить юнит к этому родителю";
            */
        }

    }







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
    QString new_name=    this->ui->uName_combobox->currentText();

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
{//qDebug()<<"==============================";
    //qDebug()<<"[TREE]";
    QList<UnitNode *> List;
    this->modelTreeUN->getListFromModel(List);
    //qDebug()<<"[count] "<<List.count();
    foreach(UnitNode* unit,List)
    {
        //qDebug()<<"---------------------------------------------------------------------------";
        qDebug()<<"Name:  "<<unit->getName()
        <<"/Type:  "<<m_TypeUnitNode.value(unit->getType())
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
/*
    qDebug()<<"Name: "<<unit->getName()
            <<" Type:"<<m_TypeUnitNode.value(unit->getType())
            <<" Num2:"<<QString::number(unit->getNum2())
            <<" DK:"<<QString::number(unit->getDK())
            <<" Bazalt:"<<QString::number(unit->getBazalt())
            <<" connectblock:"<<QString::number(unit->getConnectBlock())
            <<" UdpUse:"<<QString::number(unit->getUdpUse())
            <<" UdpAdress:"<<unit->getUdpAdress();

    //qDebug()<<"Name: "<<Name
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




    string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  БЛ-IP</b> ");



    string1.append(" :");
    string1.append(" СД:");
    string1.append(QString::number(unit->getNum2()));

    if(unit->getBazalt()==1)
        {
            string1.append(" +");
            string1.append(" ИУ:");
            string1.append(QString::number(unit->getNum2()));
        }


    string1.append("\n");

        string1.append(" Кан:");

    if(unit->getUdpUse()==0)
    {
        string1.append(QString::number(unit->getNum3()));


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

    string1.append(" ");
    if(unit->getBazalt())
    {

        string1.append(m_SD_BL_IP_OutType.value(8));
    }
    else
    {
        int val = unit->getOutType();
        if(val)
        string1.append(m_SD_BL_IP_OutType.value(unit->getOutType()));


    }
this->ui->textEdit->append(string1);



}

void MainWindowCFG::get_option_IU_BL_IP(UnitNode *unit)
{

    this->ui->textEdit->clear();
    QString string1;





            string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  БЛ-IP</b> ");
        string1.append(": Кан:");


    if(unit->getUdpUse()==0)
    {
        string1.append(QString::number(unit->getNum3()));
        string1.append(" ИУ:");
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
        string1.append("\n");
        string1.append("Таймаут: ");
        string1.append(QString::number(unit->getUdpTimeout()));
        string1.append("\n");


    }


this->ui->textEdit->append(string1);


}

void MainWindowCFG::get_option_TG(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;

        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Точка/Гарда</b> ");
            string1.append(" : ");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" : ");
    string1.append("ЧЭ: ");
    string1.append(QString::number(unit->getNum2()));
    string1.append("\r\n");
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
        string1.append("\r\n");
        string1.append("Таймаут: ");
        string1.append(QString::number(unit->getUdpTimeout()));
        string1.append("\r\n");
    }
    //qDebug()<<string1;
    this->ui->textEdit->append(string1);

}

void MainWindowCFG::get_option_RLM_KRL(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;

    string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));//  ");
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

    string1.append("</b>");
    string1.append(" : ");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");




    if(unit->getUdpUse()==0)
    {

        string1.append("Кан:");

        string1.append(QString::number(unit->getNum3()));
        string1.append(" ");

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
        string1.append("\n");
        string1.append("Таймаут: ");
        string1.append(QString::number(unit->getUdpTimeout()));
        string1.append("\n");

    }

    this->ui->textEdit->append(string1);

}

void MainWindowCFG::get_option_RLM_C(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;





        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  РИФ-РЛМ-С</b>");
        string1.append(":");
    string1.append(QString::number(unit->getNum1()));
    string1.append(" ");




    if(unit->getUdpUse()==0)
    {
        string1.append("Кан:");

        string1.append(QString::number(unit->getNum3()));
        string1.append(" ");

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
        string1.append("\n");
        string1.append("Таймаут: ");
        string1.append(QString::number(unit->getUdpTimeout()));
        string1.append("\n");

    }

    this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_BOD_T4K_M(UnitNode *unit)
{

    this->ui->textEdit->clear();
    QString string1;

        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Точка-М/Гарда-М</b> ");

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
        string1.append("\n");
        string1.append("Таймаут: ");
        string1.append(QString::number(unit->getUdpTimeout()));
        string1.append("\n");
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
    //qDebug()<<"[+]"<<string1;


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

       string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Точка-М/Гарда-М</b> ");

   string1.append("Кан:");

   string1.append(QString::number(BOD->getNum3()));

   string1.append(" БОД:");

   string1.append(QString::number(BOD->getNum1()));

   string1.append(" Участок:");

   string1.append( get_y4(unit));

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

       string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Точка-М/Гарда-М</b> ");

   string1.append("Кан:");

   string1.append(QString::number(BOD->getNum3()));

   string1.append(" БОД:");

   string1.append(QString::number(BOD->getNum1()));

   string1.append(" Участок:");

   string1.append(QString::number(Y4->getNum2()/100));

   string1.append(" ДД:");

   string1.append(get_dd(unit));



   this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_BOD_SOTA(UnitNode *unit)
{


this->ui->textEdit->clear();
QString string1;

    string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Сота/Сота-М</b> ");

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
    string1.append("\n");
    string1.append("Таймаут: ");
    string1.append(QString::number(unit->getUdpTimeout()));
    string1.append("\n");
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
//qDebug()<<"[+]"<<string1;



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

       string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Сота/Сота-М</b> ");

   string1.append("Кан:");

   string1.append(QString::number(BOD->getNum3()));

   string1.append(" БОД:");

   string1.append(QString::number(BOD->getNum1()));

   string1.append(" Участок:");

   string1.append(get_y4(unit));

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

       string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Сота/Сота-М</b> ");

   string1.append("Кан:");

   string1.append(QString::number(BOD->getNum3()));

   string1.append(" БОД:");

   string1.append(QString::number(BOD->getNum1()));

   string1.append(" Участок:");

   string1.append(QString::number(Y4->getNum2()/100));

   string1.append(" ДД:");

   string1.append(get_dd(unit));



   this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_BL_IP(UnitNode */*unit*/)
{

}

void MainWindowCFG::get_option_KL(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;

        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Концентратор</b> ");
            string1.append(" : ");
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
        string1.append("\n");
        string1.append("Таймаут: ");
        string1.append(QString::number(unit->getUdpTimeout()));
        string1.append("\n");
    }
  this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_ONVIF(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ONVIF-камера</b> ");
    string1.append(unit->getIcon1Path());



   this->ui->textEdit->append(string1);
}

void MainWindowCFG::get_option_STRAZH_IP(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Страж- IP</b> ");
    string1.append(unit->getIcon1Path());
    string1.append("; ");
    string1.append(unit->getIcon4Path());


   this->ui->textEdit->append(string1);

}

void MainWindowCFG::get_option_NET_DEV(UnitNode *unit)
{
    this->ui->textEdit->clear();
    QString string1;
        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Сетевое устройство</b> ");
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
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);

    settings.beginGroup("PARAMS");


    //qDebug()<<"SoundType  "<<settings.value("SoundType",-1).toInt();

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
    last_ini_patch="";
    //qDebug()<<"[Create]";
    this->modelTreeUN->makeEmptyTree();
//    this->ui->ipadress_combobox->clear();
    default_PARAMS();
    default_OPERATORS();
    default_RIF();
    default_INTEGRATION();
    default_SQL();
    default_BACKUP();

    default_SSOI();
    default_TABLO();

    default_ASOOSD();
    this->ui->RASTR_wgt->default_options();
    this->ui->ADAM_wgt->default_options();
    this->ui->AdmAud_wgt->default_options();

    this->ui->uType_combobox->setCurrentText(m_TypeUnitNode.value(TypeUnitNode::GROUP));

}

void MainWindowCFG::get_RIF(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);


    settings.beginGroup("RIF");

    for(int i=0;i<99;i++)
    {



      QString str_RifPortSpeed("RifPortSpeed%1");
      str_RifPortSpeed = str_RifPortSpeed.arg(i+1);

      int RifPortSpeed = settings.value(str_RifPortSpeed,-1).toInt();

      if(RifPortSpeed!=-1)
      {





          QModelIndex index = this->rif_model->index(i,1,QModelIndex());

         //qDebug()<<index.row()<<" "<<index.column()<<" "<<this->rif_model->data(index,Qt::DisplayRole);

         this->rif_model->setData(index, RifPortSpeed, Qt::EditRole);

      }

      QString str_RifPortInterval("RifPortInterval%1");
      str_RifPortInterval = str_RifPortInterval.arg(i+1);

      int RifPortInterval = settings.value(str_RifPortInterval,-1).toInt();

      if(RifPortInterval!=-1)
      {


          QModelIndex index = this->rif_model->index(i,2,QModelIndex());

            //qDebug()<<index.row()<<" "<<index.column()<<" "<<this->rif_model->data(index,Qt::DisplayRole);

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



       this->rif_model->setData(index, 4800, Qt::EditRole);

        index = this->rif_model->index(i,2,QModelIndex());



       this->rif_model->setData(index, 50, Qt::EditRole);


    /*      port->set_RifPortSpeed(50);

////qDebug()<<"---"<<i;
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
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);

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
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);

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
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);

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
      //qDebug()<< "[get_SQL]";
    QSettings settings(filename, QSettings::IniFormat);

    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);

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
             //qDebug()<< "(settings.childGroups().contains(\"PostgresSQL\"))";
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



  this->ui->SQL_password_lineEdit->setText(this->XOR_Crypt(settings.value("Password",-1).toString(),"start7"));
              qDebug()<<"загрузил пароль "<<this->ui->SQL_password_lineEdit->text();

           //   this->ui->SQL_password_lineEdit->setText(this->XOR_Crypt(settings.value("Password",-1).toString(),"start7"));
           //   this->ui->SQL_password_lineEdit->setText(this->XOR_Crypt(settings.value("Password",-1).toString()));

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


                if(settings.value("allow_fix_data",-1).toInt()==1)
                 this->ui->SQL_allow_fix_data->setChecked(true);

                if(settings.value("allow_fix_data",-1).toInt()==0)
                 this->ui->SQL_allow_fix_data->setChecked(false);




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

    this->ui->SQL_allow_fix_data->setChecked(false);

    this->ui->SQL_P1_checkBox->setChecked(false);

    this->ui->SQL_P2_checkBox->setChecked(false);


       this->ui->SQL_AutoDbStart_checkBox->setChecked(false);

    this->ui->SQL_AutoDbStartHour_doubleSpinBox->setValue(0);
    this->ui->SQL_AutoDbStartMinute_doubleSpinBox->setValue(0);
}








void MainWindowCFG::get_ADAM4068(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);
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
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);
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
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);
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
    if(str_system==str_system_RIF)
    this->ui->BACKUP_BackupPath_lineedit->setText("C:/RIFx/Backup");
    else
    if(str_system==str_system_SSOI)
    this->ui->BACKUP_BackupPath_lineedit->setText("C:/SSOI/Backup");



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
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);


    settings.beginGroup("OPERATORS");

    if(0==settings.value("Use",-1).toInt()){
        this->ui->operators_use_combobox->setCurrentText(" Без операторов");
         //qDebug()<<"OPERATORS Use = 0";
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

                op->setPW(this->XOR_Crypt(settings.value("PW",-1).toString(),"start7"));
                qDebug()<<"пароль "<<op->getPW();
                operators.append(op);

                settings.endGroup();
            }

        }

        this->update_operators_table();

















}

void MainWindowCFG::set_OPERATORS(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);

    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);

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
    QSettings settings(filename, QSettings::IniFormat);
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);
    settings.beginGroup("ASOOSD");

      this->ui->ASOOSD_Use->setCurrentText(m_ASOOSD_use.value(settings.value("Use",0).toInt()));
      this->ui->ASOOSD_Host->setText(settings.value("Host","").toString());
      this->ui->ASOOSD_Port->setValue(settings.value("Port",0).toInt());




  settings.endGroup();
}

void MainWindowCFG::set_ASOOSD(QString /*filename*/)
{

}

void MainWindowCFG::default_ASOOSD()
{
    foreach(QString str,m_ASOOSD_use)
        this->ui->ASOOSD_Use->addItem(str);


    this->ui->ASOOSD_Use->setCurrentText(m_ASOOSD_use.value(0));
    this->ui->ASOOSD_Host->setText("localhost");
    this->ui->ASOOSD_Port->setValue(1975);

}







bool MainWindowCFG::setUdpTimeout_for_BL_IP(UnitNode *unit)
{
    qDebug()<<"setUdpTimeout_for_BL_IP ";
    if(unit->getType()!=TypeUnitNode::SD_BL_IP)
    if(unit->getType()!=TypeUnitNode::IU_BL_IP)
      return false;

    int val=unit->getUdpTimeout();

    qDebug()<<"timeout "<<val;

    auto is_equal = [](UnitNode *my,UnitNode *unit)->bool
       {
        if(unit->getType()==TypeUnitNode::SD_BL_IP)
            return true;
        if(unit->getType()==TypeUnitNode::IU_BL_IP)
            return true;

        return false;
       };

    QList<UnitNode *>  list;
    modelTreeUN->getListFromModel(list,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN


    if(unit->getUdpUse()==0)
    {
 qDebug()<<"---------------------";
        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN
        foreach(UnitNode *un, List1 )
        {
      //      qDebug()<<"------";
      //    qDebug()<<unit->getName();


         if((un->getNum3()==unit->getNum3())) //ищем юниты котрые всият на одном порте с нашим
         if(is_equal(unit,un))//проверяем не идентичны ли они
         {
            qDebug()<<un->getName();
            un->setUdpTimeout(val);
             //this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));

             return false;
         }


        }


    }
    //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

    if(unit->getUdpUse()==1)
    {

        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
        foreach(UnitNode *un, List1 )
        {

         if((un->getUdpAdress()==unit->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
         if((un->getUdpPort()==unit->getUdpPort()))
         if(is_equal(unit,un))//проверяем не идентичны ли они
          {

             un->setUdpTimeout(val);
          }
        }
    }

    return true;


    //find all bl ip items





}

bool MainWindowCFG::setUdpTimeout_for_TG(UnitNode *unit)
{
    if(unit->getType()!=TypeUnitNode::TG)
      return false;

    int val=unit->getUdpTimeout();

    auto is_equal = [](UnitNode *my,UnitNode *unit)->bool
       {
        if(unit->getType()==TypeUnitNode::TG)
        if(my->getNum1()==unit->getNum1())
    //    ша(гтше)
            return true;


        return false;
       };

    QList<UnitNode *>  list;
    modelTreeUN->getListFromModel(list,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN


    if(unit->getUdpUse()==0)
    {
 qDebug()<<"---------------------";
        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN
        foreach(UnitNode *un, List1 )
        {
      //      qDebug()<<"------";
      //    qDebug()<<unit->getName();
      //      qDebug()<<un->getName();

         if((un->getNum3()==unit->getNum3())) //ищем юниты котрые всият на одном порте с нашим
         if(is_equal(unit,un))//проверяем не идентичны ли они
         {

            un->setUdpTimeout(val);
             //this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));

             return false;
         }


        }


    }
    //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

    if(unit->getUdpUse()==1)
    {

        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
        foreach(UnitNode *un, List1 )
        {

         if((un->getUdpAdress()==unit->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
         if((un->getUdpPort()==unit->getUdpPort()))
         if(is_equal(unit,un))//проверяем не идентичны ли они
          {

             un->setUdpTimeout(val);
          }
        }
    }

    return true;
}

bool MainWindowCFG::setUdpTimeout_for_KL(UnitNode *unit)
{
    qDebug()<<"setUdpTimeout_for_BL_IP ";
    if(unit->getType()!=TypeUnitNode::KL)
      return false;

    int val=unit->getUdpTimeout();

    qDebug()<<"timeout "<<val;

    auto is_equal = [](UnitNode *my,UnitNode *unit)->bool
       {
        if(unit->getType()==TypeUnitNode::KL)

            return true;

        return false;
       };

    QList<UnitNode *>  list;
    modelTreeUN->getListFromModel(list,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN


    if(unit->getUdpUse()==0)
    {
 qDebug()<<"---------------------";
        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN
        foreach(UnitNode *un, List1 )
        {
      //      qDebug()<<"------";
      //    qDebug()<<unit->getName();


         if((un->getNum3()==unit->getNum3())) //ищем юниты котрые всият на одном порте с нашим
         if(is_equal(unit,un))//проверяем не идентичны ли они
         {
            qDebug()<<un->getName();
            un->setUdpTimeout(val);
             //this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));

             return false;
         }


        }


    }
    //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

    if(unit->getUdpUse()==1)
    {

        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
        foreach(UnitNode *un, List1 )
        {

         if((un->getUdpAdress()==unit->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
         if((un->getUdpPort()==unit->getUdpPort()))
         if(is_equal(unit,un))//проверяем не идентичны ли они
          {

             un->setUdpTimeout(val);
          }
        }
    }

    return true;



}

bool MainWindowCFG::setUdpTimeout_for_BOD_SOTA(UnitNode *unit)
{
    qDebug()<<"setUdpTimeout_for_BL_IP ";
    if(unit->getType()!=TypeUnitNode::BOD_SOTA)
      return false;

    int val=unit->getUdpTimeout();

    qDebug()<<"timeout "<<val;

    auto is_equal = [](UnitNode *my,UnitNode *unit)->bool
       {
        if(unit->getType()==TypeUnitNode::Y4_SOTA)
            return true;

        if(unit->getType()==TypeUnitNode::DD_SOTA)
            return true;

        return false;
       };

    QList<UnitNode *>  list;
    modelTreeUN->getListFromModel(list,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN


    if(unit->getUdpUse()==0)
    {
 qDebug()<<"---------------------";
        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN
        foreach(UnitNode *un, List1 )
        {
      //      qDebug()<<"------";
      //    qDebug()<<unit->getName();


         if((un->getNum3()==unit->getNum3())) //ищем юниты котрые всият на одном порте с нашим
         if(is_equal(unit,un))//проверяем не идентичны ли они
         {
            qDebug()<<un->getName();
            un->setUdpTimeout(val);
             //this->ui->treeView->setCurrentIndex(modelTreeUN->findeIndexUN(un));

             return false;
         }


        }


    }
    //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

    if(unit->getUdpUse()==1)
    {

        QList<UnitNode *> List1;
        modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);
        foreach(UnitNode *un, List1 )
        {

         if((un->getUdpAdress()==unit->getUdpAdress()))//ищем юниты котрые всият на одном адресе с нашим
         if((un->getUdpPort()==unit->getUdpPort()))
         if(is_equal(unit,un))//проверяем не идентичны ли они
          {

             un->setUdpTimeout(val);
          }
        }
    }

    return true;
}



void MainWindowCFG::save_ini(QString filename)
{
    //qDebug()<<"save ini";

    QSettings settings(filename,QSettings::IniFormat);


    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForLocale(codec);
    settings.setIniCodec(codec);

//   foreach(UnitNode* unit,this->modelTreeUN->listItemUN)
    QList<UnitNode *> List;
    this->modelTreeUN->getListFromModel(List);

    //qDebug()<<"[count] "<<List.count();




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

    //qDebug()<<"PARAMS";

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

    //qDebug()<<"RIF";

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
    //qDebug()<<"SSOI";

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
    //qDebug()<<"RASTRMTV";

settings.beginGroup("INTEGRATION");
settings.setValue("Use",map_INTEGRATION_Use.key(this->ui->INTEGRATION_Use_comboBox->currentText()));
settings.setValue("Host",this->ui->INTEGRATION_Host_lineEdit->text());
settings.setValue("Port",this->ui->INTEGRATION_Port_doubleSpinBox->value());
settings.setValue("Port2",this->ui->INTEGRATION_Port2_doubleSpinBox->value());
settings.setValue("KeepAliveInterval",this->ui->INTEGRATION_KeepAliveInterval_doubleSpinBox->value());
settings.setValue("DevLine",this->ui->INTEGRATION_DevLine_filepath_lineEdit->text());
settings.endGroup();
   //qDebug()<<"INTEGRATION";

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
 // //qDebug()<<"пароль 1"<<ui->SQL_password_lineEdit->text();
//пароль после.
 // //qDebug()<<"пароль 2"<<ui->SQL_password_lineEdit->text();
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

      if(this->ui->SQL_allow_fix_data->isChecked())
      settings.setValue("allow_fix_data", 1);
      else
      settings.setValue("allow_fix_data", 0);



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

   //qDebug()<<"SQL";






    settings.beginGroup("ADAM4068");
    settings.setValue("Port",this->ui->ADAM_wgt->get_Port());
    settings.setValue("Interval",this->ui->ADAM_wgt->get_Interval());
    settings.endGroup();
       //qDebug()<<"ADAM4068";

    settings.beginGroup("TABLO");
    settings.setValue("Port",this->ui->SSOIwgt->getPort());
    settings.setValue("Blinking",this->ui->SSOIwgt->getBlinking());
    settings.endGroup();
       //qDebug()<<"TABLO";

    settings.beginGroup("BACKUP");
    settings.setValue("BackupPath",this->ui->BACKUP_BackupPath_lineedit->text());
    settings.setValue("MaxBdStringCnt",map_BACKUP_MaxBdStringCnt.key(this->ui->BACKUP_MaxBdStringCnt_comboBox->currentText()));
    settings.endGroup();
       //qDebug()<<"BACKUP";


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
       //qDebug()<<"OPERATORS";


       settings.beginGroup("ASOOSD");
//       settings.setValue("Count",List.count()-1);

settings.setValue("Use",m_ASOOSD_use.key(this->ui->ASOOSD_Use->currentText()));
settings.setValue("Host",this->ui->ASOOSD_Host->text());
settings.setValue("Port",this->ui->ASOOSD_Port->value());

       settings.endGroup();





       settings.beginGroup("ASOOSD");
//       settings.setValue("Count",List.count()-1);

settings.setValue("Use",m_ASOOSD_use.key(this->ui->ASOOSD_Use->currentText()));
settings.setValue("Host",this->ui->ASOOSD_Host->text());
settings.setValue("Port",this->ui->ASOOSD_Port->value());

       settings.endGroup();




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




        settings.setValue("lan",QString::number(unit->getLan(),'g',7));



        settings.setValue("lon",QString::number(unit->getLon(),'g',7));





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
    //qDebug()<<QString::number(current_row);

this->modelTreeUN->moveUNUp(current);





}

void MainWindowCFG::on_pushButton_moveDown_clicked()
{
    QModelIndex current=this->ui->treeView->currentIndex();
    int current_row=this->ui->treeView->currentIndex().row();
    //qDebug()<<QString::number(current_row);


        this->modelTreeUN->moveUNDown(current);

}



void MainWindowCFG::on_treeView_customContextMenuRequested(const QPoint &pos)
{

    menu->clear();
    //qDebug()<<"[ContextMenuRequested]";
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

             //   menu->exec(ui->treeView->viewport()->mapToGlobal(pos));
            break;

            case TypeUnitNode::SD_BL_IP:
            case TypeUnitNode::SSOI_SD:


                if(un->getBazalt()==0)
                if(un->getConnectBlock()==0)
                {
                    menu->addAction(action_setDK);
                    if(un->getDK()==0)
                    {
                        //qDebug()<<"[0]";
                        action_setDK->setChecked(false);
                    }
                    else
                    {
                        //qDebug()<<"[1]";
                       action_setDK->setChecked(true);
                    }

                }



               menu->addAction(action_setAlarmMsgOn);

                  if(un->getAlarmMsgOn()==0)
                  {
                      //qDebug()<<"[0]";
                      action_setAlarmMsgOn->setChecked(false);
                  }
                  else
                  {
                      //qDebug()<<"[1]";
                  }
             //  menu->exec(ui->treeView->viewport()->mapToGlobal(pos));

            break;

            case TypeUnitNode::KL:
                menu->addAction(action_setDK);
                if(un->getDK()==0)
                {
                    //qDebug()<<"[0]";
                    action_setDK->setChecked(false);
                }
                else
                {
                    //qDebug()<<"[1]";
                   action_setDK->setChecked(true);
                }


            break;

            case TypeUnitNode::IU_BL_IP:

            case TypeUnitNode::SSOI_IU:
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
            //   menu->exec(ui->treeView->viewport()->mapToGlobal(pos));

            break;

            default:
                if(un->getType()!=TypeUnitNode::SYSTEM)
                if(un->getType()!=TypeUnitNode::GROUP)
            //    menu->exec(ui->treeView->viewport()->mapToGlobal(pos));
            break;
            }

   //        Для всех интерфейсных датчиков в контекстном меню должна быть опция "Выдавать сообщение при тревогах" (Как для СД БЛ-IP)
            /*
            КЛ1
            РИФ-РЛМ-С
            Точка/Гарда
            РИФ-РЛМ/КРЛ/Трасса
            РИФ- РЛМ-С
            ДД Точка-М/Гарда
            ДД Сота
            Торос
                    */
            switch(un->getType())
            {
            case TypeUnitNode::KL:
            case TypeUnitNode::RLM_C:
            case TypeUnitNode::TG:
            case TypeUnitNode::RLM_KRL:
            case TypeUnitNode::TOROS:
            case TypeUnitNode::DD_SOTA:
            case TypeUnitNode::DD_T4K_M:
                menu->addAction(action_setAlarmMsgOn);

                   if(un->getAlarmMsgOn()==0)
                   {
                       //qDebug()<<"[0]";
                       action_setAlarmMsgOn->setChecked(false);
                   }

            break;

            }

            if(menu->actions().count()>0)
                menu->exec(ui->treeView->viewport()->mapToGlobal(pos));









        }
}





void MainWindowCFG::on_operators_use_combobox_currentTextChanged(const QString &arg1)
{
    if(arg1==" Без операторов")
    {

      //qDebug()<<"[без операторов]";
      this->ui->tableWidget->setEnabled(false);
      this->ui->add_operator_button->setEnabled(false);
      this->ui->change_operator_button->setEnabled(false);
      this->ui->delete_operator_button->setEnabled(false);
      operators_use=0;
    }
    if(arg1==" С операторами")
    {
      //qDebug()<<"[с операторами]";
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
    qDebug()<<operators.size();
    if((0<=index)&&(index<operators.size()))
    {
        qDebug()<<"[1]";
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
        //qDebug()<<"[!!!!!!!!!!!!!!!]";
     this->ui->RLM_C_UDP_RS485_stacked->setCurrentWidget(this->ui->RLM_C_RS485);
    }
}
*/


void MainWindowCFG::on_SQL_find_server_pushButton_clicked()
{
    this->ui->SQL_server_lineEdit->setText(QHostInfo::localHostName());
}

void MainWindowCFG::on_SQL_connect_pushButton_clicked()
{
    if(this->ui->SQL_type_comboBox->currentText()=="MySQL")
    {
    //qDebug()<<"connect to MySQL";
    db_mysql = QSqlDatabase::addDatabase("QMYSQL");
    //qDebug()<<"db_mysql.driver() "<<db_mysql.driver()<<"; db_mysql.driverName() "<<db_mysql.driverName();
    db_mysql.setHostName(this->ui->SQL_server_lineEdit->text());
//    db.setDatabaseName("QWERTY");
    db_mysql.setUserName(this->ui->SQL_login_lineEdit->text());
    db_mysql.setPassword(this->ui->SQL_password_lineEdit->text());
    //qDebug()<<"password "<<this->ui->SQL_password_lineEdit->text();
    if (!db_mysql.open()){
        QString err =db_mysql.lastError().text();
        QString drv;
        drv.append(err);
        drv.append("; ");
        //qDebug()<<err;

  QStringListIterator it(db_mysql.drivers());
       while(it.hasNext()) {
               drv.append(it.next());
               drv.append(";");
           }
        QMessageBox::critical(0,"Ошибка",(drv));

     //   return false;

    }
    else{
        //qDebug()<<"PROFIT";
        this->db_f->find_rif_db(db_mysql);
        db_f->show();
    }





    }
    if(this->ui->SQL_type_comboBox->currentText()=="PostgresSQL")
    {
    //qDebug()<<"connect to PostgresSQL";

    db_psql = QSqlDatabase::addDatabase("QPSQL");
    //qDebug()<<"db_mysql.driver() "<<db_psql.driver()<<"; db_mysql.driverName() "<<db_psql.driverName();
    db_psql.setHostName(this->ui->SQL_server_lineEdit->text());
//    db.setDatabaseName("QWERTY");
    db_psql.setUserName(this->ui->SQL_login_lineEdit->text());
    db_psql.setPassword(this->ui->SQL_password_lineEdit->text());
    db_psql.setDatabaseName("postgres");
    if (!db_psql.open()){
        //qDebug()<<db_psql.lastError().text();
    }
    else{
        //qDebug()<<"PROFIT";
        this->db_f->find_rif_db(db_psql);
        db_f->show();
    }
    }
}

void MainWindowCFG::create_db(QString db_name)
{

    //qDebug()<<"[create_db]";
    if(this->ui->SQL_type_comboBox->currentText()=="MySQL")
    {
    //qDebug()<<"[mysql]";

    QSqlQuery query(db_mysql);



    QString sql_cmd="CREATE DATABASE ";
    sql_cmd.append(db_name);

    query.prepare(sql_cmd);
    query.exec();



    query.clear();
    query.prepare("CREATE TABLE IF NOT EXISTS " +  db_name + ".events(\
                  event_num INT UNSIGNED,\
                  event_dt DATETIME NOT NULL,\
                  event_code INT UNSIGNED DEFAULT '0',\
                  event_name VARCHAR(30) DEFAULT '',\
                  dev_type INT UNSIGNED DEFAULT '0',\
                  dev_num1 INT UNSIGNED DEFAULT '0',\
                  dev_num2 INT UNSIGNED DEFAULT '0',\
                  dev_num3 INT UNSIGNED DEFAULT '0',\
                  dev_name VARCHAR(25) DEFAULT '',\
                  comment1 VARCHAR(25) DEFAULT '',\
                  comment2 VARCHAR(25) DEFAULT '',\
                  local_operator_fn VARCHAR(15) DEFAULT '',\
                  local_operator_n1 VARCHAR(15) DEFAULT '',\
                  local_operator_n2 VARCHAR(15) DEFAULT '',\
                  client_operator_fn VARCHAR(15) DEFAULT '',\
                  client_operator_n1 VARCHAR(15) DEFAULT '',\
                  client_operator_n2 VARCHAR(15) DEFAULT '',\
                  out_dev_type INT UNSIGNED DEFAULT '0',\
                  PRIMARY KEY(event_num),\
                  INDEX(event_dt),\
                  INDEX(event_code),\
                  INDEX(dev_num1),\
                  INDEX(dev_num2),\
                  INDEX(dev_num3),\
                  INDEX(dev_type,dev_num1,dev_num2,dev_num3),\
                  INDEX(out_dev_type,dev_type,dev_num1,dev_num2,dev_num3),\
                  INDEX(local_operator_fn,local_operator_n1,local_operator_n2),\
                  INDEX(client_operator_fn,client_operator_n1,client_operator_n2))");


    query.exec();



    this->db_f->find_rif_db(db_mysql);
    }
    if(this->ui->SQL_type_comboBox->currentText()=="PostgresSQL")
    {
        QSqlDatabase db_psql = QSqlDatabase::addDatabase("QPSQL");

       db_psql.setHostName("localhost");
       db_psql.setUserName("postgres");
       db_psql.setPassword("Start7");
       db_psql.setDatabaseName("postgres");
       if (!db_psql.open())
       {
           qDebug()<<db_psql.lastError().text();
       }
       else
           {
               qDebug()<<"PROFIT connect postgres db";

           //    QString db_name="zigert_db_1";
               QSqlQuery query(db_psql);
               QString sql_cmd;
               sql_cmd.clear();

               sql_cmd.append("CREATE DATABASE "+ db_name);
               query.exec(sql_cmd);
               QSqlError error=query.lastError();
               sql_cmd.clear();
               if(error.isValid())
               {
               qDebug()<<query.lastError();
               }
               else
               {
                   qDebug()<<"PROFIT create db "<<db_name;

               }

               QSqlDatabase current = QSqlDatabase::addDatabase("QPSQL");
               current.setHostName("localhost");
               current.setUserName("postgres");
               current.setPassword("Start7");
               current.setDatabaseName(db_name);
               if (!current.open())
               {
                   qDebug()<<current.lastError().text();
               }
               else
               {
               qDebug()<<"PROFIT open "<<db_name;
               }

                QSqlQuery query_current(current);




               sql_cmd.clear();

               sql_cmd.append("CREATE SEQUENCE public.jour_id_seq ");
               sql_cmd.append("INCREMENT 1 ");
               sql_cmd.append("MINVALUE 1 ");
               sql_cmd.append("MAXVALUE 9223372036854775807 ");
               sql_cmd.append("START 124646 ");
               sql_cmd.append("CACHE 1; ");
          //     sql_cmd.append("ALTER TABLE public.jour_id_seq ");
          //     sql_cmd.append("OWNER TO root;");







               query_current.prepare(sql_cmd);
               query_current.exec(sql_cmd);
               error=query_current.lastError();
               if(error.isValid())
               qDebug()<<error.text();
               else
               qDebug()<<"PROFIT create jour_id_seq ";


                       sql_cmd.clear();

                       sql_cmd.append("CREATE TABLE public.jour");
                       sql_cmd.append("(id integer NOT NULL DEFAULT nextval('jour_id_seq'::regclass),");
                       sql_cmd.append("cdate timestamp without time zone NOT NULL DEFAULT now(),");
                       sql_cmd.append("mdate timestamp without time zone NOT NULL DEFAULT now(),");
                       sql_cmd.append("objectid integer,");
                       sql_cmd.append("object character varying(128),");
                       sql_cmd.append("comment character varying(256) NOT NULL,");
                       sql_cmd.append("reason character varying(256),");
                       sql_cmd.append("measures character varying(256),");
                       sql_cmd.append("operator character varying(256),");
                       sql_cmd.append("operatorid character varying(256),");
                       sql_cmd.append("status character varying(32),");
                       sql_cmd.append("direction character varying(32),");
                       sql_cmd.append("type bigint,");
                       sql_cmd.append("flag bigint,");
                       sql_cmd.append("d1 bigint,");
                       sql_cmd.append("d2 bigint,");
                       sql_cmd.append("d3 bigint,");
                       sql_cmd.append("d4 bigint,");
                       sql_cmd.append("objecttype bigint)");

                       query_current.prepare(sql_cmd);

                       query_current.exec(sql_cmd);

                       error=query_current.lastError();
                               sql_cmd.clear();
                               if(error.isValid())
                               {
                               qDebug()<<error.text();
                               }
                               else
                               {
                                   qDebug()<<"PROFIT create jour";

                               }








           }




        this->db_f->find_rif_db(db_psql);

  /*
- Table: public.jour

-- DROP TABLE public.jour;

CREATE TABLE public.jour
(
  id integer NOT NULL DEFAULT nextval('jour_id_seq'::regclass),
  cdate timestamp without time zone NOT NULL DEFAULT now(),
  mdate timestamp without time zone NOT NULL DEFAULT now(),
  objectid integer,
  object character varying(128),
  comment character varying(256) NOT NULL,
  reason character varying(256),
  measures character varying(256),
  operator character varying(256),
  operatorid character varying(256),
  status character varying(32),
  direction character varying(32),
  type bigint,
  flag bigint,
  d1 bigint,
  d2 bigint,
  d3 bigint,
  d4 bigint,
  objecttype bigint
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.jour
  OWNER TO root;




  */
    }


}

void MainWindowCFG::drop_db(QString db_name)
{
    qDebug()<<"drop db "<<db_name;
if(this->ui->SQL_type_comboBox->currentText()=="MySQL")
{
//qDebug()<<"drop "<<db_name;
QSqlQuery query(db_mysql);

QString sql_cmd="DROP DATABASE ";
sql_cmd.append(db_name);

query.prepare(sql_cmd);
query.exec();


  this->db_f->find_rif_db(db_mysql);


}
if(this->ui->SQL_type_comboBox->currentText()=="PostgresSQL")
{
QSqlQuery query(db_psql);

QString sql_cmd="DROP DATABASE ";
sql_cmd.append(db_name);
sql_cmd.append(";");
query.prepare(sql_cmd);

//qDebug()<<sql_cmd;
query.exec(sql_cmd);


QSqlError error=query.lastError();
if(error.isValid())
    qDebug()<<error.text();

  this->db_f->find_rif_db(db_psql);


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
     //qDebug()<<"patch = "<<patch;
     this->ui->BACKUP_BackupPath_lineedit->setText(patch);
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

void MainWindowCFG::on_uType_combobox_activated(const QString &arg1)
{
    //qDebug()<<"[activated]";

//    this->ui->stackedWidget_2->setCurrentWidget(this->ui->nothing);


    int type=m_TypeUnitNode.key(arg1);
    this->object_menu_change(type);
    this->object_menu_set_settings_default(type);


    current_wgt()->update_name();
   //Name_update();

}

void MainWindowCFG::on_SQL_type_comboBox_currentTextChanged(const QString &arg1)
{
    //qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!";


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
     //qDebug()<<"patch = "<<patch;
     if(patch!="")
     {
         //qDebug()<<"[PROFIT]";
         this->ui->INTEGRATION_DevLine_filepath_lineEdit->setText(patch);

     }

}

void MainWindowCFG::on_pushButton_6_clicked()
{
    //qDebug()<<"++++++++++++++++++++++++";
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
   //     unit->setNum2(this->ui->coordinate_X_doubleSpinBox_2->value());
  //      unit->setNum3(this->ui->coordinate_X_doubleSpinBox_3->value());
   //     unit->setX(this->ui->coordinate_X_doubleSpinBox_4->value());
   //     unit->setY(this->ui->coordinate_X_doubleSpinBox_5->value());
    }


    }
}

























void MainWindowCFG::on_uType_combobox_currentTextChanged(const QString &arg1)
{
        //qDebug()<<"[currentTextChanged]";
    this->ui->edit_unit_button->setDisabled(true);
//    this->ui->stackedWidget_2->setCurrentWidget(this->ui->nothing);


    int type=m_TypeUnitNode.key(arg1);
    this->object_menu_change(type);


}









void MainWindowCFG::on_pushButton_3_clicked()
{

//    QModelIndex index = this->ui->treeView->currentIndex();
//---------
//   UnitNode *unit =  static_cast<UnitNode*>(index.internalPointer());
    UnitNode *unit=new UnitNode();

    unit->setType(0);
    unit->setNum1(255);
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


    unit->setType(m_TypeUnitNode.key(this->ui->uType_combobox->currentText()));




 UnitNode *parrent=new UnitNode();
set_option(unit,parrent);



//---------
        int UdpUse,UdpPort,RS485_port;
        QString UdpAdress;


    QList<UnitNode *> List1;


    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);//modelTreeUN->rootItemUN

    qDebug()<<"-- Ищу устрйоство ---";
//    qDebug()<<"тип: "<< m_TypeUnitNode.value( unit->getType());
    qDebug()<<"Актуальные параметры:";

    modelTreeUN->list_Equals_for_chanell.clear();

    qDebug()<<"---------------------------------------";
    foreach(UnitNode *un, List1 )
    {
    //    qDebug()<<"------";
    //    qDebug()<<unit->getName();
    //    qDebug()<<un->getName();

        bool res=false;


        res=compare(unit,un);
        /*
        if(UdpUse==0)
        if(un->getUdpUse()==UdpUse)
        if(un->getNum3()==RS485_port) //ищем юниты котрые всият на одном порте с нашим
        res=true;
                    //Если тип связи UDP, на одном сетевом адресе с портом не должно висеть двух юнитов с одинаковыми параметрами

        if(UdpUse==1)
        if(un->getUdpUse()==UdpUse)
        if(un->getUdpAdress()==UdpAdress)//ищем юниты котрые всият на одном адресе с нашим
        if(un->getUdpPort()==UdpPort)
        res=true;
        */

        if(res==true)
        {

        qDebug()<<res;
        modelTreeUN->list_Equals_for_chanell.append(modelTreeUN->findeIndexUN(un));
        }
}
    if(modelTreeUN->list_Equals_for_chanell.count()>0)
    {
        if(modelTreeUN->list_Equals_for_chanell.count()>1)
         this->ui->stackedWidget_3->setCurrentIndex(1);
        qDebug()<<"Найдены:";
        foreach(QModelIndex ind, modelTreeUN->list_Equals_for_chanell )
        {
        this->ui->treeView->update(ind);
            UnitNode *un = static_cast<UnitNode*>(ind.internalPointer());
            qDebug()<<un->getName();
        }


      this->ui->treeView->setCurrentIndex(modelTreeUN->list_Equals_for_chanell.at(0));

        }





}

void MainWindowCFG::on_findButton_reset_clicked()
{
    modelTreeUN->list_Equals_for_chanell.clear();
    modelTreeUN->updateUNs();
    this->ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindowCFG::on_findButton_prev_clicked()
{
prev();

}

void MainWindowCFG::on_pushButton_next_clicked()
{
next();
}

void MainWindowCFG::on_IU_BL_IP_num_combobox_currentIndexChanged(int index)
{
   Name_update();
}

void MainWindowCFG::on_ADAM_Num1_currentIndexChanged(const QString &arg1)
{
   Name_update();
}

void MainWindowCFG::on_ADAM_Num2_currentIndexChanged(const QString &arg1)
{
   Name_update();
}

void MainWindowCFG::on_TABLO_Num2_currentIndexChanged(const QString &arg1)
{
   Name_update();
}

void MainWindowCFG::on_KL_adress_combobox_currentIndexChanged(const QString &arg1)
{
   Name_update();
}

void MainWindowCFG::on_KL_CD_combobox_currentIndexChanged(const QString &arg1)
{
   Name_update();
}

void MainWindowCFG::on_RLM_C_adress_combobox_currentIndexChanged(const QString &arg1)
{
   Name_update();
}

void MainWindowCFG::on_RLM_KRL_adress_combobox_currentIndexChanged(const QString &arg1)
{
  Name_update();
}


void MainWindowCFG::on_NET_DEV_IP_combobox_currentTextChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_BOD_SOTA_M_adress_combobox_currentIndexChanged(int index)
{
  Name_update();
}

void MainWindowCFG::on_U4_Sota_M_combobox_currentIndexChanged(int index)
{
  Name_update();
}

void MainWindowCFG::on_DD_Sota_M_combobox_currentIndexChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_SSOI_IU_Num1_currentIndexChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_SSOI_IU_Num2_currentIndexChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_SSOI_IU_Num3_currentTextChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_SSOI_SD_Num1_currentIndexChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_SSOI_SD_Num2_currentIndexChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_SSOI_SD_Num3_currentIndexChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_SSOI_SD_OutType_currentIndexChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_DEVLINE_Num1_valueChanged(double arg1)
{
  Name_update();
}

void MainWindowCFG::on_DEVLINE_OutType_currentIndexChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_ONVIF_IPaddr_combobox_currentTextChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_STRAZH_IP__IPaddr_combobox_currentTextChanged(const QString &arg1)
{
  Name_update();
}

void MainWindowCFG::on_TOROS_Num1_currentIndexChanged(int index)
{
  Name_update();
}

void MainWindowCFG::on_BOD_T4K_M_adress_combobox_currentIndexChanged(int index)
{
  Name_update();
}

void MainWindowCFG::on_Y4_T4K_M_combobox_currentIndexChanged(int index)
{
  Name_update();
}

void MainWindowCFG::on_DD_T4K_M_combobox_currentIndexChanged(int index)
{
  Name_update();
}

void MainWindowCFG::on_TG_adress_combobox_currentIndexChanged(int index)
{
  Name_update();
}

void MainWindowCFG::on_TG_U4_4A_combobox_currentIndexChanged(int index)
{
  Name_update();
}

void MainWindowCFG::on_edit_unit_button_clicked()
{
    qDebug()<<"[on_edit_unit_button_clicked]";
    this->func_to_edit_unit();
}

void MainWindowCFG::on_ipadress_combobox_currentTextChanged(const QString &arg1)
{
   Name_update();
}

void MainWindowCFG::on_RASTRMTV_Num3_currentIndexChanged(int index)
{
   Name_update();
}

void MainWindowCFG::on_RLM_KRL_type_comboBox_currentIndexChanged(const QString &arg1)
{
   Name_update();
}

void MainWindowCFG::on_findButton_clicked()
{
    qDebug()<<"[on_findButton_clicked]";
    unitFinder_f->show();
}






