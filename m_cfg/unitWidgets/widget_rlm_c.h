#ifndef WIDGET_RLM_C_H
#define WIDGET_RLM_C_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_RLM_C;
}

class Widget_RLM_C : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_RLM_C(QWidget *parent = nullptr);
    ~Widget_RLM_C();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void enable() override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_RLM_C *ui;
};

#endif // WIDGET_RLM_C_H
