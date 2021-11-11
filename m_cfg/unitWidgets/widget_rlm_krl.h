#ifndef WIDGET_RLM_KRL_H
#define WIDGET_RLM_KRL_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_RLM_KRL;
}

class Widget_RLM_KRL : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_RLM_KRL(QWidget *parent = nullptr);
    ~Widget_RLM_KRL();

    void get_option(UnitNode* unit) override;
    void set_option(UnitNode* unit) override;
    void update_name() override;
    void enable() override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_RLM_KRL *ui;
};

#endif // WIDGET_RLM_KRL_H
