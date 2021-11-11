#ifndef WIDGET_TG_H
#define WIDGET_TG_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_TG;
}

class Widget_TG : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_TG(QWidget *parent = nullptr);
    ~Widget_TG();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void enable() override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_TG *ui;
};

#endif // WIDGET_TG_H
