#ifndef WIDGET_DD_T4K_M_H
#define WIDGET_DD_T4K_M_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_DD_T4K_M;
}

class Widget_DD_T4K_M : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_DD_T4K_M(QWidget *parent = nullptr);
    ~Widget_DD_T4K_M();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void enable() override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_DD_T4K_M *ui;
};


#endif // WIDGET_DD_T4K_M_H
