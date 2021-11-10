#ifndef COMMUNICATIONTYPEWIDGET_H
#define COMMUNICATIONTYPEWIDGET_H

#include <QWidget>
#include <UnitNode.h>

namespace Ui {
class communicationTypeWidget;
}

class communicationTypeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit communicationTypeWidget(QWidget *parent = nullptr);
    ~communicationTypeWidget();

    void get_options(UnitNode* Unit);
    void set_options(UnitNode* Unit);

private:
    Ui::communicationTypeWidget *ui;
};

#endif // COMMUNICATIONTYPEWIDGET_H
