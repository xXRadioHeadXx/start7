#ifndef WIDGET_DD_SOTA_H
#define WIDGET_DD_SOTA_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_DD_SOTA;
}

class Widget_DD_SOTA : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_DD_SOTA(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);

    ~Widget_DD_SOTA();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;


    bool accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr) override;
    bool equal(UnitNode* one,UnitNode* secons) override;


    QString get_string(UnitNode* unit) override;
private slots:

    void on_Num2_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget_DD_SOTA *ui;
};


#endif // WIDGET_DD_SOTA_H
