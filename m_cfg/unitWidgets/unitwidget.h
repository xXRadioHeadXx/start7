#ifndef UNITWIDGET_H
#define UNITWIDGET_H

#include <QWidget>

namespace Ui {
class UnitWidget;
}

class UnitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnitWidget(QWidget *parent = nullptr);
    ~UnitWidget();

private:
    Ui::UnitWidget *ui;
};

#endif // UNITWIDGET_H
