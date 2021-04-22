#ifndef my_combobox_H
#define my_combobox_H


#include <QComboBox>

#include <QWidget>

class my_combobox : public QComboBox
{
    Q_OBJECT
public:
    my_combobox(QWidget *parent = 0);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

signals:

};

#endif // my_combobox_H
