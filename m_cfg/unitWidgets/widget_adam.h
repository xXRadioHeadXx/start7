#ifndef WIDGET_ADAM_H
#define WIDGET_ADAM_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_ADAM;
}

class Widget_ADAM : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_ADAM(QWidget *parent = nullptr);
    ~Widget_ADAM();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void enable() override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_ADAM *ui;
};

#endif // WIDGET_ADAM_H









