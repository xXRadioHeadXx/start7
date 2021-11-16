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
    explicit Widget_KL(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);
    ~Widget_KL();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Num1_currentIndexChanged(const QString &arg1);

    void on_Num2_currentIndexChanged(const QString &arg1);


private:
    Ui::Widget_KL *ui;
};


#endif // WIDGET_KL_H
