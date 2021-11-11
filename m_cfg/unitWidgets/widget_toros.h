#ifndef WIDGET_TOROS_H
#define WIDGET_TOROS_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_TOROS;
}

class Widget_TOROS : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_TOROS(QWidget *parent = nullptr);
    ~Widget_TOROS();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void enable() override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_TOROS *ui;
};

#endif // WIDGET_TOROS_H
