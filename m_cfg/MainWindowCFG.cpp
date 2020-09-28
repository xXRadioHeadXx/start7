#include "MainWindowCFG.h"
#include "ui_MainWindowCFG.h"

#include "QFileDialog"

MainWindowCFG::MainWindowCFG(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowCFG)
{
    ui->setupUi(this);


    QString patch="C:/start7-master/rifx.ini";
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

