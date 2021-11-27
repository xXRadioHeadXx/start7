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
    explicit Widget_RASTRMTV(QWidget *parent = nullptr,communicationTypeWidget* comm=nullptr,coordinateWidget* coord=nullptr,TreeModelUnitNode *modelTreeUN=nullptr,QModelIndex* current=nullptr,QMap<QString, SerNum_Name>* mSerNum_Name=nullptr);
    ~Widget_RASTRMTV();

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

    void on_Num3_currentIndexChanged(const QString &arg1);

    void get_cameras();

private:
    Ui::Widget_RASTRMTV *ui;

 QMap <QString, SerNum_Name>* mSerNum_Name;
};

#endif // WIDGET_RASTRMTV_H
