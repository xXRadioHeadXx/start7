#ifndef WIDGET_Y4_SOTA_H
#define WIDGET_Y4_SOTA_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_Y4_SOTA;
}

class Widget_Y4_SOTA : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_Y4_SOTA(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);
    ~Widget_Y4_SOTA();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;

    bool accepted(UnitNode* unit) override;
    bool equal(UnitNode* one,UnitNode* secons) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Num2_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget_Y4_SOTA *ui;
};

#endif // WIDGET_Y4_SOTA_H
