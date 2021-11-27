#ifndef WIDGET_ONVIF_H
#define WIDGET_ONVIF_H

#include <QWidget>
#include <unitWidgets/unitwidget.h>

namespace Ui {
class Widget_ONVIF;
}

class Widget_ONVIF : public UnitWidget
{
    Q_OBJECT

public:
    explicit Widget_ONVIF(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr);
    ~Widget_ONVIF();

    void get_from(UnitNode* unit) override;
    void get_default() override;
    void set_to(UnitNode* unit) override;
    void update_name() override;
    void setEnabled_option_menu(bool) override;

    bool accepted(UnitNode* unit,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr) override;
    bool equal(UnitNode* one,UnitNode* secons) override;

    QString get_string(UnitNode* unit) override;
private slots:

    void on_Icon1Path_currentIndexChanged(const QString &arg1);

    void on_Icon1Path_currentTextChanged(const QString &arg1);

private:
    Ui::Widget_ONVIF *ui;
};

#endif // WIDGET_ONVIF_H
