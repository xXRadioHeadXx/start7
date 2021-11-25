#ifndef UNITWIDGET_H
#define UNITWIDGET_H

#include <QWidget>
#include <UnitNode.h>
#include <my_config.h>
#include <unitWidgets/communicationtypewidget.h>
#include "unitWidgets/coordinatewidget.h"
#include <TreeModelUnitNode.h>

namespace Ui {
class UnitWidget;
}

class UnitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnitWidget(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);
    ~UnitWidget();
    int getID();




    virtual void get_from(UnitNode* unit){};
    virtual void get_default(){};

    virtual void set_to(UnitNode* unit);

    virtual void update_name(){};

    virtual QString get_string(UnitNode* unit){return "";};

    virtual void setEnabled_option_menu(bool){};

    void setEnabled(bool);
    void get_option(UnitNode* unit);
    bool set_option(UnitNode* unit);

    //Проверка на допустимость вводимых параметров для каждого юнита
    virtual bool accepted(UnitNode* unit);

    virtual bool equal(UnitNode* one,UnitNode* second){return true;};

    bool no_equal_unit(UnitNode* unit);
    bool no_equal_unit_from_one_parent(UnitNode* unit);

    QString get_dd(UnitNode* unit);

    void set_timeouts(UnitNode* unit);
    virtual bool timeout_brother(UnitNode *unit,UnitNode* un){return false;};

    bool ip_is_valid(QString ip);

    QModelIndex* current;
 //   comm->set_options(unit);
 //   coord->set_options(unit);


    QModelIndex getDouble_unit_index();

protected:
    int ID;
    communicationTypeWidget* comm;
    coordinateWidget* coord;
    bool comm_is_needed;
    int coord_mode;
    TreeModelUnitNode *modelTreeUN = nullptr;
    QModelIndex double_unit_index;
//MainWindowCFG* wnd;


private:
    Ui::UnitWidget *ui;

public slots:
    void updateName_slot();

signals:
    void updateName(QString);
//    void double_unit_signal(UnitNode *un);
};

#endif // UNITWIDGET_H
