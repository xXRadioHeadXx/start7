#include "MainWindowCFG.h"
#include "ui_MainWindowCFG.h"

#include "QFileDialog"



MainWindowCFG::MainWindowCFG(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowCFG)
{
    ui->setupUi(this);
  //  this->current_index=nullptr;


    QString patch="C:/WORK1/start7/rifx.ini";
//   QString patch=QFileDialog::getOpenFileName(this, "open file","","*.ini");
//qDebug()<<"patch = "<<patch;
    this->modelTreeUN = new TreeModelUnitNode(this);

    ui->treeView->setModel(this->modelTreeUN);

    this->modelTreeUN->loadSettings(patch);



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


void MainWindowCFG::on_treeView_clicked(const QModelIndex &index)
{
this->select_unit(index);
}


void MainWindowCFG::select_unit(QModelIndex index)
{
    current_index=index;
    UnitNode *unit = static_cast<UnitNode*>(index.internalPointer());
    QString Name=unit->getName();


    this->ui->uName_lineedit->setText(Name);

    selected_type=unit->getType();

    QString Type=this->Type_from_int_to_string(selected_type);

  //  this->ui->uType_combobox->setTe


    if(selected_type==SD_BL_IP)
    {
        this->ui->uType_combobox->setCurrentText(Type);

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

        this->ui->CD_comboBox_Num2->setCurrentText("");
        this->ui->CD_DK_checkBox->setChecked(false);
        this->ui->CD_Bazalt_checkBox->setChecked(false);
        this->ui->CD_connectblock_checkBox->setChecked(false);
        this->ui->CD_UdpUse_checkBox->setChecked(false);


        this->ui->CD_comboBox_Num2->setCurrentText(QString::number(Num2));


        this->ui->CD_DK_checkBox->setChecked(DK);
        this->ui->CD_Bazalt_checkBox->setChecked(Bazalt);
        this->ui->CD_connectblock_checkBox->setChecked(connectblock);
        this->ui->CD_UdpUse_checkBox->setChecked(UdpUse);
        this->ui->UpdPort_lineEdit->setText(QString::number(UdpPort));
        this->ui->UdpAdress_lineEdit->setText(UdpAdress);
    }
    else
    qDebug()<<"Name: "<<Name
            <<" Type:"<<Type;


}

QString MainWindowCFG::Type_from_int_to_string(int int_Type)
{
    QString Type;
    Type.clear();

    switch(int_Type)
    {
    case GROUP:

    Type.append("Группа");
    break;

    case SD_BL_IP:
    Type.append("СД БЛ-IP");
    break;

    case IU_BL_IP:
    Type.append("ИУ БЛ-IP");
    break;

    /*
    case BL_IP:
    Type.append("BL_IP");
    break;
    */

    }
    return Type;
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
    this->ui->stackedWidget->setCurrentWidget(this->ui->Empty_space);

}



void MainWindowCFG::on_pushButton_4_clicked()
{
    if(current_index.isValid())
    {
       UnitNode *unit = static_cast<UnitNode*>(current_index.internalPointer());
       if(unit->getType()==SD_BL_IP)
       {

           unit->setName(this->ui->uName_lineedit->text());
           unit->setNum2(this->ui->CD_comboBox_Num2->currentText().toInt());
           unit->setDK(this->ui->CD_DK_checkBox->isChecked()?1:0);
           unit->setBazalt(this->ui->CD_Bazalt_checkBox->isChecked()?1:0);
           unit->setConnectBlock(this->ui->CD_connectblock_checkBox->isChecked()?1:0);
           unit->setUdpUse(this->ui->CD_UdpUse_checkBox->isChecked()?1:0);
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
         /*  */
       }

    }
    else
        qDebug()<<"[ERROR][Index not valid]";
}


