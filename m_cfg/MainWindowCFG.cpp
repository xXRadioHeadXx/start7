#include "MainWindowCFG.h"
#include "ui_MainWindowCFG.h"

#include "QFileDialog"



MainWindowCFG::MainWindowCFG(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowCFG)
{
    ui->setupUi(this);


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
    UnitNode *unit = static_cast<UnitNode*>(index.internalPointer());
    QString Name=unit->getName();
    QString Type=this->Type_from_int_to_string(unit->getType());




    qDebug()<<"Name: "<<Name<<" Type:"<<Type;
}

QString MainWindowCFG::Type_from_int_to_string(int int_Type)
{
    QString Type;
    Type.clear();

    switch(int_Type)
    {
    case GROUP:
    Type.append("GROUP");
    break;

    case SD_BL_IP:
    Type.append("SD_BL_IP");
    break;

    case IU_BL_IP:
    Type.append("IU_BL_IP");
    break;

    case BL_IP:
    Type.append("BL_IP");
    break;
    }
    return Type;
}











