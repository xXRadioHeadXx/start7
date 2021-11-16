#ifndef WIDGET_TG_H
#define WIDGET_TG_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>
#include <unitWidgets/communicationtypewidget.h>

namespace Ui {
class Widget_TG;
}

class Widget_TG : public UnitWidget
{
    Q_OBJECT

public:

    communicationTypeWidget* comm;

    explicit Widget_TG(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);
    ~Widget_TG();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;

    QString get_string(UnitNode* unit) override;
private:
    Ui::Widget_TG *ui;
};

#endif // WIDGET_TG_H
