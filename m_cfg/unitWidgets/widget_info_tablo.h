#ifndef WIDGET_INFO_TABLO_H
#define WIDGET_INFO_TABLO_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_INFO_TABLO;
}

class Widget_INFO_TABLO : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_INFO_TABLO(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);
    ~Widget_INFO_TABLO();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;

    QString get_string(UnitNode* unit) override;
private slots:
    void on_Num2_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget_INFO_TABLO *ui;
};

#endif // WIDGET_INFO_TABLO_H

