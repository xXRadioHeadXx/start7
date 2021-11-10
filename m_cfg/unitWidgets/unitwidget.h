#ifndef UNITWIDGET_H
#define UNITWIDGET_H

#include <QWidget>
#include <UnitNode.h>
#include <my_config.h>

namespace Ui {
class UnitWidget;
}

class UnitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnitWidget(QWidget *parent = nullptr);
    ~UnitWidget();

    int getID();


    virtual void get_option(UnitNode* unit);
    virtual void set_option(UnitNode* unit);



protected:
int ID;


private:
    Ui::UnitWidget *ui;

};

#endif // UNITWIDGET_H
