#include "MainWindowCFG.h"
#include "ui_MainWindowCFG.h"

MainWindowCFG::MainWindowCFG(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowCFG)
{
    ui->setupUi(this);
}

MainWindowCFG::~MainWindowCFG()
{
    delete ui;
}

