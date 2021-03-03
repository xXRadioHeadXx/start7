#ifndef MY_COMBOBOX_H
#define MY_COMBOBOX_H


#include <QComboBox>

#include <QWidget>

class My_combobox : public QComboBox
{
    Q_OBJECT
public:
    My_combobox(QWidget *parent = 0);

     virtual void showPopup();

signals:

};

#endif // MY_COMBOBOX_H
