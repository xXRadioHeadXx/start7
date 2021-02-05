#ifndef ADMAUD_WIDGET_H
#define ADMAUD_WIDGET_H

#include <QWidget>
#include "admkeygenerator.h"

namespace Ui {
class AdmAud_widget;
}

class AdmAud_widget : public QWidget
{
    Q_OBJECT

public:
    explicit AdmAud_widget(QWidget *parent = nullptr);
    ~AdmAud_widget();

    void default_options();
    void default_combobox();

private slots:


    void on_Create_clicked();

    void on_ChekIn_clicked();

    void on_comboBox_highlighted(int index);

    void on_pushButton_clicked();

private:
    Ui::AdmAud_widget *ui;

    AdmKeyGenerator AdmKey;

public slots:
    void usb_update();
};

#endif // ADMAUD_WIDGET_H
