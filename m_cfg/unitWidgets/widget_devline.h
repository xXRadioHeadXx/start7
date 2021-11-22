#ifndef WIDGET_DEVLINE_H
#define WIDGET_DEVLINE_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_DEVLINE;
}

class Widget_DEVLINE : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_DEVLINE(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);

    ~Widget_DEVLINE();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;

    bool accepted(UnitNode* unit) override;
    bool equal(UnitNode* one,UnitNode* secons) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Num1_valueChanged(const QString &arg1);

    void on_OutType_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget_DEVLINE *ui;
};

#endif // WIDGET_DEVLINE_H
