#ifndef adm_aud_combobox_H
#define adm_aud_combobox_H


#include <QComboBox>

#include <QWidget>

class adm_aud_combobox : public QComboBox
{
    Q_OBJECT
public:
    adm_aud_combobox(QWidget *parent = 0);

     virtual void showPopup();

signals:

};

#endif // adm_aud_combobox_H
