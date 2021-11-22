#ifndef COORDINATEWIDGET_H
#define COORDINATEWIDGET_H

#include <UnitNode.h>
#include <QWidget>
#include <QTimer>

enum coordinateWigget_mode
{
    nothing,
    for_all, // BLACK находится в глобальном пространстве имен
    devline
};

namespace Ui {
class coordinateWidget;
}

class coordinateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit coordinateWidget(QWidget *parent = nullptr);
    ~coordinateWidget();

    void get_options(UnitNode *unit);
    void set_options(UnitNode *unit);

    void set_mode(int mode);

private slots:
    void update_coordinates();

private:
    Ui::coordinateWidget *ui;
    int mode;
    QTimer* timer;
};

#endif // COORDINATEWIDGET_H
