#ifndef COORDINATEWIDGET_H
#define COORDINATEWIDGET_H

#include <QWidget>

namespace Ui {
class coordinateWidget;
}

class coordinateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit coordinateWidget(QWidget *parent = nullptr);
    ~coordinateWidget();

private:
    Ui::coordinateWidget *ui;
};

#endif // COORDINATEWIDGET_H
