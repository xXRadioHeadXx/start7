#include "widget_net_dev.h"
#include "ui_widget_net_dev.h"

Widget_NET_DEV::Widget_NET_DEV(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_NET_DEV)
{
    ID=TypeUnitNode::NET_DEV;
    ui->setupUi(this);

}

Widget_NET_DEV::~Widget_NET_DEV()
{
    delete ui;
}

void Widget_NET_DEV::get_from(UnitNode *unit)
{
    ui->Icon1Path->setCurrentText(unit->getIcon1Path());
}

void Widget_NET_DEV::get_default()
{
    ui->Icon1Path->setCurrentText("");
}



void Widget_NET_DEV::set_to(UnitNode *unit)
{
    unit->setIcon1Path(ui->Icon1Path->currentText());
}

void Widget_NET_DEV::update_name()
{
    QString Name;
    Name.append("Сетевое ");
    Name.append(this->ui->Icon1Path->currentText());
    emit updateName(Name);

}

void Widget_NET_DEV::setEnabled_option_menu(bool val)
{

}

bool Widget_NET_DEV::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}
    if(parent->getType()!=TypeUnitNode::GROUP)
    if(parent->getType()!=TypeUnitNode::SYSTEM)
    {
   //     QMessageBox::critical(0,"Ошибка","БОД может быть добавлен только к группе");
        return false;

    }

    QList<UnitNode *> List1;
    modelTreeUN->getListFromModel(List1,modelTreeUN->rootItemUN);

    return true;
}

bool Widget_NET_DEV::equal(UnitNode *un, UnitNode *unit)
{
    if(un->getType()==unit->getType())
    if(un->getIcon1Path()==unit->getIcon1Path())
    return true;
    return false;
}

QString Widget_NET_DEV::get_string(UnitNode *unit)
{
    QString string1;

        string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Сетевое устройство</b> ");
    string1.append(unit->getIcon1Path());
   return string1;
}



void Widget_NET_DEV::on_Icon1Path_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_NET_DEV::on_Icon1Path_currentTextChanged(const QString &arg1)
{
    update_name();
}
