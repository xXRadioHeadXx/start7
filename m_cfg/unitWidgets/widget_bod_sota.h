#ifndef WIDGET_BOD_SOTA_H
#define WIDGET_BOD_SOTA_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_BOD_SOTA;
}

class Widget_BOD_SOTA : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_BOD_SOTA(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);

    ~Widget_BOD_SOTA();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;
    bool timeout_brother(UnitNode *unit,UnitNode* un) override;

    bool accepted(UnitNode* unit) override;
    bool equal(UnitNode* one,UnitNode* secons) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Num1_currentTextChanged(const QString &arg1);



private:
    Ui::Widget_BOD_SOTA *ui;
};

#endif // WIDGET_BOD_SOTA_H



