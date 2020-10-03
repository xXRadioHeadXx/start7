#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QObject>
#include <QTreeView>



class MyTreeView : public QTreeView {

  Q_OBJECT

  public:
    MyTreeView(QWidget *parent = 0);

};

#endif // MYTREEVIEW_H
