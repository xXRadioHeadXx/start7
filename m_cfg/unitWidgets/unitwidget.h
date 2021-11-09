#ifndef UNITWIDGET_H
#define UNITWIDGET_H

#include <QWidget>
#include <UnitNode.h>

namespace Ui {
class UnitWidget;
}

class UnitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnitWidget(QWidget *parent = nullptr);
    ~UnitWidget();

    int getID();

protected:
int ID;


private:
    Ui::UnitWidget *ui;

};

#endif // UNITWIDGET_H
