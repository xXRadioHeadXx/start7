#ifndef UNITWIDGET_H
#define UNITWIDGET_H

#include <QWidget>
#include <UnitNode.h>
#include <my_config.h>
#include <unitWidgets/communicationtypewidget.h>
#include "unitWidgets/coordinatewidget.h"

namespace Ui {
class UnitWidget;
}

class UnitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnitWidget(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr);
    ~UnitWidget();
    int getID();




    virtual void get_from(UnitNode* unit){};
    virtual void get_default(){};

    virtual void set_option(UnitNode* unit);

    virtual void update_name(){};
    virtual void setEnabled(bool){};
    virtual QString get_string(UnitNode* unit){return "";};

    void get_option(UnitNode* unit);
protected:
    int ID;
    communicationTypeWidget* comm;
    coordinateWidget* coord;
    bool comm_is_needed;
    int coord_mode;

//MainWindowCFG* wnd;


private:
    Ui::UnitWidget *ui;


signals:
    void updateName(QString);

};

#endif // UNITWIDGET_H
