#ifndef WIDGET_SSOI_IU_H
#define WIDGET_SSOI_IU_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_SSOI_IU;
}

class Widget_SSOI_IU : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_SSOI_IU(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr);
    ~Widget_SSOI_IU();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Num1_currentIndexChanged(const QString &arg1);

    void on_Num2_currentIndexChanged(const QString &arg1);

    void on_Num3_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget_SSOI_IU *ui;
};


#endif // WIDGET_SSOI_IU_H
