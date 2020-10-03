#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QObject>
<<<<<<< HEAD

class MyTreeView
{
public:
    MyTreeView();
=======
#include <QTreeView>

class MyTreeView : public QTreeView
{
public:
    MyTreeView(QWidget *parent = 0);
>>>>>>> 91046e7... .
};

#endif // MYTREEVIEW_H
