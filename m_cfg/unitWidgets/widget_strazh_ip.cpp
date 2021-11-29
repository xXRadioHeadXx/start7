#include "widget_strazh_ip.h"
#include "ui_widget_strazh_ip.h"

Widget_STRAZH_IP::Widget_STRAZH_IP(QWidget *parent, communicationTypeWidget *comm, coordinateWidget* coord,TreeModelUnitNode *modelTreeUN,QModelIndex* current) :
    UnitWidget(parent,comm,coord,modelTreeUN,current),
    ui(new Ui::Widget_STRAZH_IP)
{
    ID=TypeUnitNode::STRAZH_IP;
    ui->setupUi(this);
}

Widget_STRAZH_IP::~Widget_STRAZH_IP()
{
    delete ui;
}

void Widget_STRAZH_IP::get_from(UnitNode *unit)
{
ui->Icon1Path->setCurrentText(unit->getIcon1Path());
ui->Icon2Path->setText(unit->getIcon2Path());
ui->Icon3Path->setText(unit->getIcon3Path());
ui->Icon4Path->setText(unit->getIcon4Path());
}

void Widget_STRAZH_IP::get_default()
{
    ui->Icon1Path->setCurrentText("");
    ui->Icon2Path->setText("");
    ui->Icon3Path->setText("");
    ui->Icon4Path->setText("");
}



void Widget_STRAZH_IP::set_to(UnitNode *unit)
{
unit->setIcon1Path(ui->Icon1Path->currentText());
unit->setIcon2Path(ui->Icon2Path->text());
unit->setIcon3Path(ui->Icon3Path->text());
unit->setIcon4Path(ui->Icon4Path->text());

}

void Widget_STRAZH_IP::update_name()
{
    QString Name("Страж-IP ");
    Name.append(this->ui->Icon1Path->currentText());
    emit updateName(Name);

}

void Widget_STRAZH_IP::setEnabled_option_menu(bool val)
{
    ui->Icon1Path->setEnabled(val);
    ui->Icon2Path->setEnabled(val);
    ui->Icon3Path->setEnabled(val);
    ui->Icon4Path->setEnabled(val);
}

bool Widget_STRAZH_IP::accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN,QModelIndex* current)
{

    UnitNode* parent;
    parent = static_cast<UnitNode*>(current->internalPointer()); if(!parent){return false;}

    //Проверка на адекватность айпишников.
    if(!UnitWidget::ip_is_valid(unit->getIcon1Path()))
        return false;

    if(!UnitWidget::ip_is_valid(unit->getIcon4Path()))
        return false;


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

    return 
already_on_the_branch(unit,modelTreeUN,current);
}

bool Widget_STRAZH_IP::equal(UnitNode *un, UnitNode *unit)
{
    if(un->getType()==unit->getType())
    if(un->getIcon1Path()==unit->getIcon1Path())
    if(un->getIcon4Path()==unit->getIcon4Path())
    return true;
    return false;
}

QString Widget_STRAZH_IP::get_string(UnitNode *unit)
{
    QString string1;
    string1.append("<b>");string1.append(m_TypeUnitNode_d.value(unit->getType()));string1.append("</b> ");//  Страж- IP</b> ");
    string1.append(unit->getIcon1Path());
    string1.append("; ");
    string1.append(unit->getIcon4Path());

   return string1;
}

void Widget_STRAZH_IP::on_Icon1Path_currentTextChanged(const QString &arg1)
{
    update_name();
}
