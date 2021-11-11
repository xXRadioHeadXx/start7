#ifndef WIDGET_INFO_TABLO_H
#define WIDGET_INFO_TABLO_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_INFO_TABLO;
}

class Widget_INFO_TABLO : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_INFO_TABLO(QWidget *parent = nullptr);
    ~Widget_INFO_TABLO();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void enable() override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_INFO_TABLO *ui;
};

#endif // WIDGET_INFO_TABLO_H

