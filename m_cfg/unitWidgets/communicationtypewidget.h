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

    void enable();

    QString get_udpAdress();





private slots:
    void on_udpUse_currentTextChanged(const QString &arg1);

private:

    int ID;

    Ui::communicationTypeWidget *ui;


};

#endif // COMMUNICATIONTYPEWIDGET_H
