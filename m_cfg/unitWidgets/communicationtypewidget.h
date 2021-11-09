#ifndef COMMUNICATIONTYPEWIDGET_H
#define COMMUNICATIONTYPEWIDGET_H

#include <QWidget>

namespace Ui {
class communicationTypeWidget;
}

class communicationTypeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit communicationTypeWidget(QWidget *parent = nullptr);
    ~communicationTypeWidget();

private:
    Ui::communicationTypeWidget *ui;
};

#endif // COMMUNICATIONTYPEWIDGET_H
