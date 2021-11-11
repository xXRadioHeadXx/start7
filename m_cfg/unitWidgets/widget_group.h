#ifndef WIDGET_GROUP_H
#define WIDGET_GROUP_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_GROUP;
}

class Widget_GROUP : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_GROUP(QWidget *parent = nullptr);
    ~Widget_GROUP();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_GROUP *ui;
};

#endif // WIDGET_GROUP_H
