#ifndef WIDGET_RASTRMTV_H
#define WIDGET_RASTRMTV_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_RASTRMTV;
}

class Widget_RASTRMTV : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_RASTRMTV(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr);
    ~Widget_RASTRMTV();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled(bool) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Icon1Path_currentIndexChanged(const QString &arg1);

    void on_Num3_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget_RASTRMTV *ui;
};

#endif // WIDGET_RASTRMTV_H
