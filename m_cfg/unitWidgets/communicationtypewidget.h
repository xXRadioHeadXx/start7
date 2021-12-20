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

    void get_options(UnitNode* Unit,int ID);
    void set_options(UnitNode* Unit);

    void set_udpTimeout(int val);



    //Доступен для изменения настроек
    void setEnabled(bool);



    QString get_udpAdress();





    void setID(int value);

private slots:
    void on_udpUse_currentTextChanged(const QString &arg1);

    void on_udpAdress_currentTextChanged(const QString &arg1);

private:


    int ID;


    Ui::communicationTypeWidget *ui;

signals:
    void updateIP(int ID);


};

#endif // COMMUNICATIONTYPEWIDGET_H
