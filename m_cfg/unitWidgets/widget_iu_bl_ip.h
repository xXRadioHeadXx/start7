#ifndef WIDGET_IU_BL_IP_H
#define WIDGET_IU_BL_IP_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>
namespace Ui {
class Widget_IU_BL_IP;
}

class Widget_IU_BL_IP : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_IU_BL_IP(QWidget *parent = nullptr);
    ~Widget_IU_BL_IP();

    virtual void get_option(UnitNode* unit){};
    virtual void set_option(UnitNode* unit){};

private:
    Ui::Widget_IU_BL_IP *ui;
};

#endif // WIDGET_IU_BL_IP_H
