#ifndef WIDGET_KL_H
#define WIDGET_KL_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_KL;
}

class Widget_KL : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_KL(QWidget *parent = nullptr);
    ~Widget_KL();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_KL *ui;
};


#endif // WIDGET_KL_H
