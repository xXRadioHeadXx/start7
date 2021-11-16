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
    void set_option(UnitNode* unit);

    void setUdpTimeout_for_BL_IP(UnitNode* unit);

    QModelIndex* current;
 //   comm->set_options(unit);
 //   coord->set_options(unit);

protected:
    int ID;
    communicationTypeWidget* comm;
    coordinateWidget* coord;
    bool comm_is_needed;
    int coord_mode;
    TreeModelUnitNode *modelTreeUN = nullptr;

//MainWindowCFG* wnd;


private:
    Ui::UnitWidget *ui;


signals:
    void updateName(QString);

};

#endif // UNITWIDGET_H
