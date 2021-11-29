#include "widget_onvif.h"
#include "ui_widget_onvif.h"

Widget_ONVIF::Widget_ONVIF(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_ONVIF)
{
    ID=TypeUnitNode::ONVIF;
    ui->setupUi(this);
}

Widget_ONVIF::~Widget_ONVIF()
{
    delete ui;
}

void Widget_ONVIF::get_from(UnitNode *unit)
{
    ui->Icon1Path->setCurrentText(unit->getIcon1Path());
    ui->Icon2Path->setText(unit->getIcon2Path());
    ui->Icon3Path->setText(unit->getIcon2Path());
}

void Widget_ONVIF::get_default()
{
    ui->Icon1Path->setCurrentText("");
    ui->Icon2Path->setText("");
    ui->Icon3Path->setText("");
}



void Widget_ONVIF::set_to(UnitNode *unit)
{
    unit->setIcon1Path(ui->Icon1Path->currentText());
    unit->setIcon2Path(ui->Icon2Path->text());
    unit->setIcon3Path(ui->Icon3Path->text());
}

void Widget_ONVIF::update_name()
{
    QString Name("");
    Name.append("Камера ONVIF ");
    Name.append(" ");
    Name.append(this->ui->Icon1Path->currentText());
    emit updateName(Name);

}

void Widget_ONVIF::setEnabled_option_menu(bool val)
{
    ui->Icon1Path->setEnabled(val);
    ui->Icon2Path->setEnabled(val);
    ui->Icon3Path->setEnabled(val) ;
}

bool Widget_ONVIF::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}


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


    if(!UnitWidget::ip_is_valid(unit->getIcon1Path()))
        return false;


return 
already_on_the_branch(unit,modelTreeUN,current);

}

bool Widget_ONVIF::equal(UnitNode *un, UnitNode *unit)
{
     return(un->getIcon1Path()==unit->getIcon1Path());
}

QString Widget_ONVIF::get_string(UnitNode *unit)
{
    QString string1;
    string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  ONVIF-камера</b> ");
    string1.append(unit->getIcon1Path());
    return string1;
}


void Widget_ONVIF::on_Icon1Path_currentIndexChanged(const QString &arg1)
{
    update_name();
}

void Widget_ONVIF::on_Icon1Path_currentTextChanged(const QString &arg1)
{
    update_name();
}
